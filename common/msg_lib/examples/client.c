/******************************************************************************
 *
 *    client.c
 *
 *    Copyright (C) 2005  Chris Nystrom
 *
 *    This program is public domain software
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
#include "sock_lib.h"
#include "msg_lib.h"

#define PORT (32662)

#define STR_SIZE (12)

#define SEND_STRING (0)

static int done = 0;

void do_data_in(void)
{
	msg_num_t mn;
	char string[STR_SIZE];

	if (done) {
//		nio_log_print("do_data_in(): already done. returning.\n");
		return;
	}

	mn = msg_get_num();

//	nio_log_print("*** do_data_in(): mn = %d\n", mn);

	if (mn == MSG_STOP) {
		nio_log_print("do_data_in(): MSG_STOP received\n");
		// server says stop: process no more messages
		done = 1;
		return;
	}

	if (mn == MSG_BUF_EMPTY) {
		nio_log_print("do_data_in(): MSG_BUF_EMPTY\n");
		return;
	}

	while (mn != MSG_BUF_EMPTY) {

		if (SEND_STRING == mn) {
			msg_unpack_string(string, STR_SIZE);

			printf("IN> |%s|\n", string);
			fflush(stdout);
		} else {
			fprintf(stderr,
				"do_data_in(): bad function number: %d\n",
				mn);
		}

		mn = msg_get_num();

//		nio_log_print("*** do_data_in(): mn = %d\n", mn);

		if (mn == MSG_STOP) {
			nio_log_print("do_data_in(): MSG_STOP received\n");
			// server says stop: process no more messages
			done = 1;
			return;
		}
	}
}

void test_write(const char *s)
{
	msg_set_num(SEND_STRING);	// msg_num
	msg_pack_string(s);

	printf("OUT> |%s|\n", s);
	fflush(stdout);
}

int main(void)
{
	int i = 0;
	int j = 0;
	char string[12];
	SOCKET s;

	nio_log_use_stdout(TRUE);

	s = init_tcp_client("localhost", PORT);

	if (s < 0) {
		nio_log_error("main():"," init_tcp_client() failed.\n");
		exit(-1);
	}

	if (msg_init_client(s, s)) {
		nio_log_error("main():", " msg_init_client() failed.\n");
		exit(-2);
	}

	while (!done) {

		sprintf(string, "Test C%d", i);

		//printf("|%s|\n", string);

		test_write(string);

		i++;

		j++;
		if (j == 10) {

			msg_send();

			j = 0;
		}
	}

	msg_stop_client();

	exit(0);
}
