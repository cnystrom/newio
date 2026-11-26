/******************************************************************************
 *
 *    get_userpass.c
 *
 *    Added 2026. The Makefiles list get_userpass.c, and url.c calls
 *    get_userpass(), but the file was not in the NewIO 0.12 sources.
 *    url.c passes the url as const, so get_userpass() can't change it;
 *    parse_url() already fills in the user name. This version does
 *    nothing, so d0 links and behaves as parse_url() alone.
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but without any warranty whatsoever.
 *
 *****************************************************************************/

#include "url.h"

PUBLIC void get_userpass(const char *s, const url * url)
{
	(void) s;
	(void) url;
}
