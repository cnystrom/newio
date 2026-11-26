/******************************************************************************
 *
 *    win32_lib.c
 *
 *    New original replacement, added 2026 after the previous third-party
 *    win32_lib.c (Downhill Project) was omitted from the published NewIO
 *    tree. This file is not derived from that source. MinGW-w64 already
 *    has gettimeofday() and usleep(); this adds the rest of win32_lib.h.
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published
 *    by the Free Software Foundation; either version 2.1 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but without any warranty whatsoever.
 *
 *****************************************************************************/

#ifdef WIN32

#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include "win32_lib.h"

void bzero(char *to, int count)
{
	memset(to, 0, count);
}

/* Start Winsock 2.2. Returns 0 on success. */
int init_winsock(void)
{
	WSADATA wsadata;

	return (WSAStartup(MAKEWORD(2, 2), &wsadata));
}

#ifndef __MINGW32__
#include <sys/timeb.h>

int gettimeofday(struct timeval *tv, void *tz)
{
	struct _timeb tb;

	(void) tz;
	_ftime(&tb);
	tv->tv_sec = (long) tb.time;
	tv->tv_usec = tb.millitm * 1000;
	return (0);
}

void usleep(unsigned int useconds)
{
	Sleep((useconds + 999) / 1000);
}
#endif				/* !__MINGW32__ */

#endif				/* WIN32 */
