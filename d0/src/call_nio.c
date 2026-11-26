/******************************************************************************
 *
 *    call_nio.c
 *
 *    Copyright (C) 2002, 2005  Chris Nystrom
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but without any warranty whatsoever.
 *
 *    For more license information see:
 *
 *      http://www.gnu.org/copyleft/gpl.html
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

#include "SDL.h"
#include "sock_lib/sock_lib.h"
#include "msg_lib/msg_lib.h"
#include "sdl_lib/sdl_lib.h"
#include "screen_lib/screen_lib.h"
#include "event_lib/event_lib.h"
#include "font_lib/font_lib.h"
#include "audio_lib/audio_lib.h"
#include "image_lib/image_lib.h"
#include "str_lib.h"
#include "ssh2_lib/ssh2_lib.h"
#include "url.h"
#include "done.h"
#ifndef WIN32
#include <netinet/tcp.h>
#endif
#include "../newio_version.h"

//#define NIO_FILE_EXTENSION ".exe\n"
#define NIO_PORT  (22)
#define ERR0  "error: no response from server.\n"
#define ERR1  "error: program not available.\n"
#define ERR2  "error: unknown return code.\n"

extern void nio_client_main_loop(void);
extern void open_data_in(void);

int call_nio(url myurl)
{
	char server[MAX_LINE_LEN];
	char program[MAX_LINE_LEN];
	char command[MAX_LINE_LEN * 3];
	int ret;
	int port_num = NIO_PORT;
	char str[BUFSIZ];
//      char version[] = "0.11_bin_066\n";
	SOCKET s;
	int status = 1;

	set_window_caption(myurl.program);

	strlcpy(server, myurl.server, MAX_LINE_LEN);
	strlcpy(program, myurl.program, MAX_LINE_LEN);

	strlcpy(command, program, MAX_LINE_LEN * 3);
//      strlcat(command, NIO_FILE_EXTENSION, MAX_LINE_LEN * 3);
	strlcat(command, "\n", MAX_LINE_LEN * 3);

	if (atoi(myurl.port) != 0) {
		port_num = atoi(myurl.port);
	}

	s = init_tcp_client(server, port_num);

	if (setsockopt
	    (s, IPPROTO_TCP, TCP_NODELAY, (const char *) &status, sizeof(status)) == -1) {
		fprintf(stderr, "setsockopt TCP_NODELAY failed\n");
	}

	if (s < 0) {
		fprintf(stderr, "call_nio(): init_tcp_client() failed.\n");
		return 0;
	}

	if (init_session(s, myurl.username, myurl.password) != 0) {
		close_socket(s);
		return (-1);
	}

	if (request_subsystem(NEWIO_SUBSYSTEM)) {
		printf("Remote subsystem failed. (%s)\n", NEWIO_SUBSYSTEM);
		free_session();
		close_socket(s);
		return (-1);
	} else {
		printf("Remote subsystem succeeded.\n");
	}

	// This section talk to niod
	// *** Comment out this section to talk directly to an app
	// to use debugger on the server side app.
	gets_channel(str, BUFSIZ);

	puts_channel(NEWIO_SUBSYSTEM);
	puts_channel("\n");

	gets_channel(str, BUFSIZ);

	// No longer doing versioning in the subsystem request so this is broken
	if (strlen(str) > 1) {
		// 2026: no longer downloads and installs an update script
		printf("Old browser version. Please install a newer d0.\n");
		exit(0);
	}

	puts_channel(command);
	gets_channel(str, BUFSIZ);

	ret = atoi(str);

	if (strlen(str) <= 0) {
		fprintf(stderr, ERR0);
	} else if (-1 == ret) {
		fprintf(stderr, ERR1);

	} else if (0 != ret) {
		fprintf(stderr, ERR2);
	} else
		// *** END comment out section
	{
		set_done(FALSE);
		open_data_in();
		msg_init_client(-1, -1);

		while (!done()) {
			handle_events();
		}

		printf("call_nio(): calling msg_stop_ssh_client...\n");

		msg_stop_client();
	}

	close_socket(s);

	free_all_fonts();
	delete_all_sounds();
	free_all_images();

	return 0;
}
