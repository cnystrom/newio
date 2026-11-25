/******************************************************************************
 *
 *    url.h
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

#ifndef _URL_H
#define _URL_H

#ifndef PRIVATE
#define PRIVATE static
#endif

#ifndef PUBLIC
#define PUBLIC
#endif

#ifndef NUL
#define NUL  (0)
#endif

#ifndef MAX_LINE_LEN
#define MAX_LINE_LEN	 (81)
#endif

#define MAX_SERVICE_LEN  (6)
#define MAX_USERNAME_LEN (16)
#define MAX_PASSWORD_LEN (16)
#define MAX_SERVER_LEN   (80)
#define MAX_PORT_LEN     (8)
#define MAX_EXT_LEN      (5)

#define MAX_USERNAME_LEN_TXT "15"
#define MAX_PASSWORD_LEN_TXT "15"

typedef struct {
	char service[MAX_SERVICE_LEN];
	char username[MAX_USERNAME_LEN];
	char password[MAX_PASSWORD_LEN];
	char server[MAX_LINE_LEN];
	char port[MAX_PORT_LEN];
	char program[MAX_LINE_LEN];
	char extension[MAX_EXT_LEN];
} url;

PUBLIC void parse_url(const char *s, url *);
PUBLIC void init_url(url * url);
PUBLIC void print_url(const url *);
PUBLIC void get_userpass(const char *s, const url * url);

#endif				// _URL_H
