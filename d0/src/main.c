/******************************************************************************
 *
 *    main.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef WIN32
#include <winsock2.h>
#endif
#ifndef WIN32
#include <unistd.h>
#endif
#include "SDL.h"
#include "nio_log.h"
#include "str_lib.h"
#include "font_lib/font_lib.h"
#include "sdl_lib/sdl_lib.h"
#include "audio_lib/audio_lib.h"
#include "screen_lib/screen_lib.h"
#include "color_lib/color_lib.h"
#include "rand.h"
#include "url.h"
#include "text_box.h"
#include "rpc.h"
#include "rpcui.h"
#include "file_xfr.h"
#include "install_dir.h"

#define MAX_URL_LEN     (64)

#define HTTP  "http"
#define NIO   "nio"

#define DEFAULT_URL  "nio://localhost/list"
//#define DEFAULT_URL  "nio://silver.newio.org/list.nio"
//#define DEFAULT_URL  "nio://appstest.newio.org/list.nio"
//#define DEFAULT_URL  "nio://apps.newio.org/list.nio"


extern void randomize(void);
extern void play_intro_sound(void);
extern void check_home_dir(void);
extern void get_url(char *s);
extern void get_login_info(char *username, char *password);
extern void call_http(const char *s);
extern int call_nio(url myurl);

void init_dnought(void);
void quit_dnought(void);

int main(int argc, char **argv)
{
	char username[MAX_LINE_LEN] = "";
	char password[MAX_LINE_LEN] = "";
	char sURL[MAX_URL_LEN + 1] = DEFAULT_URL;
	char oldserver[MAX_URL_LEN + 1] = { 0 };
	int first = TRUE;
	url myurl;

	nio_log_use_stdout(TRUE);
	//nio_log_open("c:\\d0.log");

	init_dnought();

	for (;;) {
		get_url(sURL);

		parse_url(sURL, &myurl);
		if (first) {
			strlcpy(oldserver, myurl.server, MAX_URL_LEN);
			first = FALSE;
		}

		if (strncmp(oldserver, myurl.server, MAX_URL_LEN) != 0) {
			username[0] = 0;
			password[0] = 0;
			strcpy(oldserver, myurl.server);
		}

		if (!strncmp(myurl.service, HTTP, 4)) {
			call_http(sURL);
		} else if (!strncmp(myurl.service, NIO, 4)) {
			if ((strlen(myurl.username) == 0)
			    && (strlen(myurl.password) == 0)) {
				if (username[0] == 0 || password[0] == 0) {
					get_login_info(username, password);
				}
				strlcpy(myurl.username, (char *) username,
					MAX_USERNAME_LEN);
				strlcpy(myurl.password, (char *) password,
					MAX_PASSWORD_LEN);
			} else {
				strlcpy(username, (char *) myurl.username,
					MAX_USERNAME_LEN);
				strlcpy(password, (char *) myurl.password,
					MAX_PASSWORD_LEN);
			}
			if ((strlen(username) != 0)
			    && (strlen(password) != 0)) {
				init_file_xfer(myurl.server);
				if (call_nio(myurl) == -1) {
					username[0] = 0;
					password[0] = 0;
				}
			} else {
				nio_log_print("Bad login or password.\n");
			}
		}
	}

	quit_dnought();
}

void init_dnought(void)
{
#ifdef WIN32
#define WINSOCK_VERSION (MAKEWORD (2, 0))
	WSADATA wsadata;

	WSAStartup(WINSOCK_VERSION, &wsadata);
#endif
	randomize();
	find_install_dir();
	check_home_dir();
	sdl_init();
	font_init();
	init_audio();
	play_intro_sound();
}

void quit_dnought(void)
{
#ifdef WIN32
	WSACleanup();
#endif
	font_quit();
	SDL_Quit();
	exit(0);
}
