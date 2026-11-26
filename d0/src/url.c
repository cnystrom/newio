/******************************************************************************
 *
 *    url.c
 *
 *    Copyright (C) 2002, 2005  Chris Nystrom
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
 *    Blog:   http://conversazione.blogspot.com
 *    AIM:    nystromchris
 *
 *    Soli Deo Gloria
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "str_lib.h"
#include "url.h"

PUBLIC void parse_url(const char *s, url * url)
{
	int check_for_port = 0;
	int check_for_extension = 0;
	int check_for_username = 0;
	int i, j, index;

	init_url(url);

	index = 0;

	for (i = 0; i < (MAX_SERVICE_LEN - 1); i++) {
		if (s[index] == ':')
			break;
		else {
			url->service[i] = s[index];
			index++;
		}
	}

	url->service[i] = NUL;

	index++;		// :
	index++;		// /
	index++;		// /

	j = index;

	for (i = 0; i < (MAX_USERNAME_LEN - 1); i++) {
		if (s[j] == '@') {
			check_for_username = 1;
			index = j;
			break;
		} else {
			url->username[i] = s[j];
			j++;
		}
	}

	if (check_for_username) {
		url->username[i++] = NUL;
		index++;	// @
	} else {
		url->username[0] = NUL;
	}

	get_userpass(s, url);

	for (i = 0; i < (MAX_SERVER_LEN - 1); i++) {
		if (s[index] == ':') {
			check_for_port = 1;
			break;
		} else if (s[index] == '/')
			break;
		else if (s[index] == NUL) {
			url->server[i] = NUL;
			return;
		} else {
			url->server[i] = s[index];
			index++;
		}
	}

	url->server[i++] = NUL;

	index++;		// ; or /

	if (check_for_port) {
		for (i = 0; i < MAX_PORT_LEN; i++) {
			if (s[index] == '/')
				break;
			else if (s[index] == NUL) {
				url->port[i] = NUL;
				return;
			} else {
				url->port[i] = s[index];
				index++;
			}
		}
		url->port[i] = NUL;
		index++;	// /
	} else {
		/* FIX (2026): strncpy(url->port, "0", 1) left port without a NUL terminator. */
		strcpy(url->port, "0");
	}

	for (i = 0; i < (MAX_LINE_LEN - 1); i++) {
		if (s[index] == '/')
			break;
		if (s[index] == '.') {
			check_for_extension = 1;
			break;
		}
		if (s[index] == NUL) {
			url->program[i] = NUL;
			strclean(url->program);
			return;
		} else {
			url->program[i] = s[index];
			index++;
		}
	}

	url->program[i] = NUL;

	index++;		// .

	for (i = 0; i < (MAX_EXT_LEN - 1); i++) {
		if (s[index] == NUL) {
			url->extension[i] = NUL;
			return;
		} else {
			url->extension[i] = s[index];
			index++;
		}
	}

	url->extension[i++] = NUL;
}

PUBLIC void init_url(url * url)
{
	url->service[0] = NUL;
	url->username[0] = NUL;
	url->password[0] = NUL;
	url->server[0] = NUL;
	url->port[0] = NUL;
	url->program[0] = NUL;
	url->extension[0] = NUL;
}


PUBLIC void print_url(const url * url)
{
	printf("--\n");
	printf("service   = |%s|\n", url->service);
	printf("username  = |%s|\n", url->username);
	printf("password  = |%s|\n", url->password);
	printf("server    = |%s|\n", url->server);
	printf("port      = |%s|\n", url->port);
	printf("program   = |%s|\n", url->program);
	printf("extension = |%s|\n\n", url->extension);

	fflush(stdout);
}
