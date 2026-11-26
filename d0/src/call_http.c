/******************************************************************************
 *
 *    call_http.c
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

#include <stdlib.h>
#include "str_lib.h"

#ifndef BUFSIZ
#define BUFSIZ    (8192)
#endif

#define MOZILLA "mozilla "

void call_http(const char *sURL)
{
	char command[512] = MOZILLA;

	strlcat(command, sURL, BUFSIZ);	// add url string to mozilla command
	system(command);
}
