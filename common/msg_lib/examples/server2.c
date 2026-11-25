/******************************************************************************
 *
 *    server2.c
 *
 *    Copyright (C) 2005  Chris Nystrom
 *
 *    This program is public domain software.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but without any warranty whatsoever.
 *
 *    Contact Author at:
 *
 *    Chris Nystrom
 *
 *    E-Mail: cnystrom@gmail.com
 *    Blog:   http://conversazione.blogspot.com
 *    AIM:    nystromchris
 *
 *    Soli Deo Gloria
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "nio_log.h"
#include "msg_lib.h"

#ifndef STDIN
#define STDIN  (0)
#endif                          /*  */

#ifndef STDOUT
#define STDOUT  (1)
#endif                          /*  */

#define STR_SIZE (12)

#define SEND_STRING (0)

void do_data_in()
{
	msg_num_t mn;
	char string[STR_SIZE];

	mn = msg_get_num();

	while (mn > MSG_BUF_EMPTY) {
		if (mn == SEND_STRING) {
			msg_unpack_string(string, STR_SIZE);

			nio_log_print("IN> |%s|\n", string);
		} else {
			nio_log_error("do_data_in():",
				" bad function number: %d\n", mn);
		}
		mn = msg_get_num();
	}
}

void test_write(const char *s)
{
	msg_set_num(SEND_STRING);	// msg_num
	msg_pack_string(s);
	msg_send();

	nio_log_print("OUT> |%s|\n", s);
}

int main(void)
{
	int i;
	char string[12];

	nio_log_open("server2.log");

	nio_log_print("server2 log opened.\n");

	// inetd handles networking, so this uses stdio
	msg_init_server(STDIN, STDOUT);

	for (i = 0; i < 100; i++) {
		sprintf(string, "Test S%d", i);
		test_write(string);
	}

	msg_stop_server();

	nio_log_print("closing server2 log file.\n");
	nio_log_close();

	exit(0);
}
