/******************************************************************************
 *
 *    msg_lib.c
 *
 *    Copyright (C) 2005  Dreadnought Incorporated
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU Lessor General Public License as published
 *    by the Free Software Foundation; either version 2.1 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but without any warranty whatsoever.
 *
 *    For more license information see:
 *
 *      http://www.gnu.org/copyleft/lessor.html
 *
 *    Contact Author at:
 *
 *    Chris Nystrom
 *
 *    E-Mail: cnystrom@gmail.com
 *
 *    Soli Deo Gloria
 *
 */

/*
#include <stdio.h>
#ifndef WIN32
#include <netinet/tcp.h>
#include"win32_lib.h"
#endif
#include "SDL.h"
#include "nio_log.h"
#include "buffer.h"
*/

#include <stdio.h>
#include <stdlib.h>
#if defined(UNIX) || defined(__MINGW32__)
#include <unistd.h>
#endif
#include "nio_log.h"
#include "bitqueue.h"
#include "msg_lib.h"
#include "buffer.h"

#define WAIT_TIME (100)

PRIVATE int fd_in;
PRIVATE int fd_out;

PRIVATE buffer_t b_in;
PRIVATE buffer_t b_out;
PRIVATE buffer_t b_in_temp;
PRIVATE buffer_t b_out_temp;

PRIVATE int b_server = FALSE;

PRIVATE int f_done_read = FALSE;	// Are we done reading yet? flag
PRIVATE int f_done_write = FALSE;	// Are we done writing yet? flag
PRIVATE int f_done_data = FALSE;	// Are we done processing data?

PRIVATE int f_exit = FALSE;	// exit recvd flag - used only by client

PRIVATE msg_num_t msg_num;

PRIVATE SDL_Thread *thr2;
PRIVATE SDL_Thread *thr3;
PRIVATE SDL_Thread *thr4;

INTERTHREADQUEUE itq;
INTERTHREADQUEUE itq2;

#define MSG_LIB_ERR1 " message buffer full\n"
#define MSG_LIB_ERR2 " no data left in message buffer\n"
#define MSG_LIB_ERR3 " read error\n"
#define MSG_LIB_ERR4 " write error\n"
#define MSG_LIB_ERR5 " BoundedInterthreadQueueCreate() failed\n"
#define MSG_LIB_ERR6 " SDL_CreateThread() failed\n"

PRIVATE int data_in(void *dummy)
{
	while (!f_done_data) {

		BoundedInterthreadQueueGet(&itq2, &b_in);

//              nio_log_print("data_in(): b_in =\n");
//              print_buffer(&b_in);

		do_data_in();	// external function
	}

	return (0);
}

// when the network has a problem we do this for now..
// FIX ME
PRIVATE void netloops_error_exit()
{
	f_done_read = TRUE;
	f_done_write = TRUE;
	f_done_data = TRUE;

	nio_log_error("netloops_error_exit():", " exiting...\n");
}

PRIVATE int read_incoming(void *unused)
{
	while (!f_done_read) {
		int i;
		int len, len2;
		char buffer_len[BUF_SIZE_LEN + 1];

		reset_buf(&b_in_temp);

//              nio_log_print("read_incoming(): b_in_temp(1) = \n");
//              print_buffer(&b_in_temp);

		if (f_done_read) {
//                      nio_log_print("read_incoming(): f_done_read exit\n");
			goto leave_read_incoming;
		}

		i = read_data(fd_in, buffer_len, BUF_SIZE_LEN, TRUE);

		if (i <= 0) {
//                      nio_log_error("read_incoming():", MSG_LIB_ERR3);
			netloops_error_exit();
			goto leave_read_incoming;
		}

		len = b_in_temp.len = atoi(buffer_len);

//              nio_log_print("read_incoming(): len = %d\n", len);

		i = 0, len2 = 0;

		while (len2 < len) {

			if (f_done_read) {
//                              nio_log_print("read_incoming(): f_done_read exit\n");
				goto leave_read_incoming;
			}

			i = read_data(fd_in,
				      (char *) b_in_temp.data + len2,
				      len - len2, TRUE);

//                      nio_log_print("read_incoming(): chars read = %d\n", i);

			if (i <= 0) {
//                              nio_log_error("read_incoming():", MSG_LIB_ERR3);
				netloops_error_exit();
				goto leave_read_incoming;
			}

			len2 += i;
		}

		b_in_temp.data[b_in_temp.len] = 0;

//              nio_log_print("read_incoming(): b_in_temp(2) = \n");
//              print_buffer(&b_in_temp);

		// check for MSG_STOP control message
		if (MSG_STOP == atoi((char *) b_in_temp.data)) {
			nio_log_print("read_incoming(): got MSG_STOP\n");
			f_done_read = TRUE;
			BoundedInterthreadQueuePut(&itq2, &b_in_temp);
			goto leave_read_incoming;
		}

		BoundedInterthreadQueuePut(&itq2, &b_in_temp);
	}

      leave_read_incoming:

	return (0);
}

PRIVATE int write_outgoing(void *unused)
{
	while (!f_done_write) {
		int i;
		int pos;
		char buffer_len[BUF_SIZE_LEN + 1];

		BoundedInterthreadQueueGet(&itq, &b_out_temp);

		if (f_done_write) {
			goto leave_write_outgoing;
		}
//              len = htonl(b_out_temp.len);

		sprintf(buffer_len, "%5.5d", b_out_temp.len);

//              nio_log_print("b_out_temp.len = %5.5d\n", b_out_temp.len);

		i = write_data(fd_out, buffer_len, BUF_SIZE_LEN);

		if (i == -1) {
//                      nio_log_error("write_outgoing():", MSG_LIB_ERR4);
			netloops_error_exit();
			goto leave_write_outgoing;
		}
//              nio_log_print("write_outgoing(): OUT> %s\n", b_out_temp.data);

		for (pos = 0; pos < b_out_temp.len;) {

			i = write_data(fd_out,
				       (char *) b_out_temp.data + pos,
				       b_out_temp.len - pos);

//                      nio_log_print("write_outgoing(): num chars written = %d\n", i);

			if (i == -1) {
//                              nio_log_error("write_outgoing():", MSG_LIB_ERR4);
				netloops_error_exit();
				goto leave_write_outgoing;
			}

			pos += i;
		}
	}

      leave_write_outgoing:

	return (0);
}

PRIVATE int msg_init(void)
{
	reset_buf(&b_in);
	reset_buf(&b_out);

	f_done_read = FALSE;
	f_done_write = FALSE;
	f_done_data = FALSE;

	if (BoundedInterthreadQueueCreate(&itq)) {
		nio_log_error("msg_init():", MSG_LIB_ERR5);
		return (-1);
	}

	if (BoundedInterthreadQueueCreate(&itq2)) {
		nio_log_error("msg_init():", MSG_LIB_ERR5);
		return (-1);
	}

	thr2 = SDL_CreateThread(read_incoming, NULL);

	if (thr2 == NULL) {
		nio_log_error("msg_init():", MSG_LIB_ERR6);
		return (-1);
	}

	thr3 = SDL_CreateThread(write_outgoing, NULL);

	if (thr3 == NULL) {
		nio_log_error("msg_init():", MSG_LIB_ERR6);
		return (-1);
	}

	thr4 = SDL_CreateThread(data_in, NULL);

	if (thr4 == NULL) {
		nio_log_error("msg_init():", MSG_LIB_ERR6);
		return (-1);
	}

	return (0);
}

PRIVATE void msg_stop(void)
{
	int status;

	usleep(WAIT_TIME);

	nio_log_print("msg_stop(): destroying queues...\n");

	BoundedInterthreadQueueDestroy(&itq);
	BoundedInterthreadQueueDestroy(&itq2);

	usleep(WAIT_TIME);

	nio_log_print("msg_stop(): waiting for threads to die...\n");

	SDL_WaitThread(thr2, &status);
	SDL_WaitThread(thr3, &status);
	SDL_WaitThread(thr4, &status);

	nio_log_print("msg_stop(): done\n");
}

//////////////////////////////////////////////////////////////////////////////
//
//                      PUBLIC PROCEDURES BELOW
//
//////////////////////////////////////////////////////////////////////////////

// Note: inetd handles networking, so the inetd server uses stdio
// Note: You can also use this for a ssh subsystem server, since sshd handles
//       everything for you.
PUBLIC int msg_init_server(int in, int out)
{
	fd_in = in;
	fd_out = out;

	b_server = TRUE;

	return (msg_init());
}

PUBLIC int msg_init_client(int in, int out)
{
	fd_in = in;
	fd_out = out;

	f_exit = FALSE;

	return (msg_init());
}

PUBLIC void msg_stop_server(void)
{

	nio_log_print("entering msg_stop_server()...\n");

//      msg_send();

	while (!BoundedInterthreadQueueEmpty(&itq)) {
		usleep(WAIT_TIME);
	}

	while (!BoundedInterthreadQueueEmpty(&itq2)) {
		usleep(WAIT_TIME);
	}

	nio_log_print("msg_stop_server(): sending MSG_STOP...\n");

	// tell client we are done
	msg_set_num(MSG_STOP);
	msg_send();

	// make sure exit msg sent
	while (!BoundedInterthreadQueueEmpty(&itq)) {
		usleep(WAIT_TIME);
	}

	f_done_write = TRUE;

	nio_log_print("msg_stop_server(): waiting for f_done_read...\n");

	// wait until exit message returns
	// set in msg_get_num()
	while (!f_done_read) {
		usleep(WAIT_TIME);
	}

	f_done_data = TRUE;

	nio_log_print("msg_stop_server(): f_done_data = TRUE\n");

	msg_stop();
}

PUBLIC void msg_stop_client(void)
{
	while (!BoundedInterthreadQueueEmpty(&itq2)) {
		usleep(WAIT_TIME);
	}

	while (!BoundedInterthreadQueueEmpty(&itq)) {
		usleep(WAIT_TIME);
	}

	nio_log_print("msg_stop_client(): waiting for f_exit...\n");

	// wait for server to tell us to quit
	// This flag should be set by client getting a MSG_STOP
	while (!f_exit) {
		usleep(WAIT_TIME);
	}

//      printf("msg_stop_client(): confirmed f_exit set\n");

//      printf("msg_stop_client(): f_done_read = TRUE\n");

	f_done_read = TRUE;
	f_done_data = TRUE;

	nio_log_print("msg_stop_client(): sending MSG_STOP to server...\n");

//      printf("msg_stop_client(): out buffer:");
//      print_buffer(&b_out);

	// Send MSG_STOP back to server to ack
	msg_set_num(MSG_STOP);

//      printf("msg_stop_client(): out buffer:");
//      print_buffer(&b_out);

	msg_send();

	while (!BoundedInterthreadQueueEmpty(&itq)) {
		usleep(WAIT_TIME);
	}

	nio_log_print("msg_stop_client(): setting f_done_write flag...\n");

	// now we are done. shutdown io threads
	f_done_write = TRUE;

//      nio_log_print("msg_stop_client(): f_done_write set\n");

	msg_stop();
}

/*
PUBLIC void msg_stop_ssh_client(void)
{
//	int status;

	nio_log_print("msg_stop_ssh_client(): entering...\n");

	if (!f_ssh_fatal) {
		while (!BoundedInterthreadQueueEmpty(&itq2)) {
			usleep(WAIT_TIME);
		}

		while (!BoundedInterthreadQueueEmpty(&itq)) {
			usleep(WAIT_TIME);
		}

		nio_log_print("msg_stop_ssh_client(): waiting for f_exit\n");

		// wait for server to tell us to quit
		// This flag should be set by client getting a MSG_STOP
		while (!f_exit) {
			usleep(WAIT_TIME);
		}

		nio_log_print("msg_stop_ssh_client(): recv f_exit\n");

		// Send MSG_STOP back to server to ack
		msg_set_num(MSG_STOP);
		msg_send();

		nio_log_print("msg_stop_ssh_client(): sending MSG_STOP\n");

		while (!BoundedInterthreadQueueEmpty(&itq)) {
			usleep(WAIT_TIME);
		}

		nio_log_print("msg_stop_ssh_client(): itq empty\n");
		
		// now we are done. shutdown io threads
		f_done_read = TRUE;
		f_done_write = TRUE;

		// lets MSG_STOP get through apparently
		usleep(100000);
	}

	msg_stop();


	BoundedInterthreadQueueDestroy(&itq);
	BoundedInterthreadQueueDestroy(&itq2);

	usleep(WAIT_TIME);

	if (!f_ssh_fatal) {
		SDL_WaitThread(thr2, &status);
		SDL_WaitThread(thr3, &status);
		SDL_WaitThread(thr4, &status);
	} else {
		SDL_KillThread(thr4);
	}

//#ifdef WIN32
//	DeleteCriticalSection(&cs);
//#endif
}
*/

PUBLIC void msg_send(void)
{
	if (b_out.len == 0) {
//              nio_log_print("msg_send(): nothing to send\n");
		return;
	}

	BoundedInterthreadQueuePut(&itq, &b_out);

//      printf("msg_send(): out buffer:");
//      print_buffer(&b_out);

	reset_buf(&b_out);

//      nio_log_print("msg_send(): out buffer reset\n");

//      printf("msg_send(): out buffer:");
//      print_buffer(&b_out);
}

PUBLIC void msg_set_num(msg_num_t mn)
{
	msg_pack_int32(mn);
}

PUBLIC msg_num_t msg_get_num(void)
{
	msg_num = msg_unpack_int32();

	// check for MSG_STOP control message
	if (MSG_STOP == msg_num) {
//              nio_log_print("msg_get_num(): MSG_STOP recv\n");
		if (b_server) {
//                      nio_log_print("msg_get_num(): f_done_read = TRUE\n");
			// we got response from client. shutdown read thread
			f_done_read = TRUE;
		} else {
//                      nio_log_print("msg_get_num(): f_exit = TRUE\n");
			// server says shut it down
			// client may being shutdown process if ready
			f_exit = TRUE;
		}
	}

	return (msg_num);
}

PUBLIC void msg_pack_string(const char *s)
{
	if (pack_string(&b_out, s) == -1) {
		nio_log_print(MSG_LIB_ERR1);
	}
}

PUBLIC void msg_unpack_string(char *s, int str_size)
{
	if (unpack_string(&b_in, s, str_size) == -1) {
		nio_log_print(MSG_LIB_ERR2);
	}
}

PUBLIC void msg_pack_int32(int32 i32)
{
	if (pack_int32(&b_out, i32) == -1) {
		nio_log_print(MSG_LIB_ERR1);
	}
}

PUBLIC int32 msg_unpack_int32(void)
{
	return (unpack_int32(&b_in));
}

PUBLIC void msg_pack_int16(int16 i16)
{
	if (pack_int16(&b_out, i16) == -1) {
		nio_log_print(MSG_LIB_ERR1);
	}
}

PUBLIC int16 msg_unpack_int16(void)
{
	return (unpack_int16(&b_in));
}

PUBLIC void msg_pack_int8(int8 i8)
{
	if (pack_int8(&b_out, i8) == -1) {
		nio_log_print(MSG_LIB_ERR1);
	}
}

PUBLIC int8 msg_unpack_int8(void)
{
	return (unpack_int8(&b_in));
}

PUBLIC void msg_pack_bytes(byte * s, uint32 str_size)
{
	if (pack_bytes(&b_out, s, str_size) == -1) {
		nio_log_print(MSG_LIB_ERR1);
	}
}

PUBLIC void msg_unpack_bytes(byte * s, uint32 * str_size)
{
	if (unpack_bytes(&b_in, s, str_size) == -1) {
		nio_log_print(MSG_LIB_ERR2);
	}
}
