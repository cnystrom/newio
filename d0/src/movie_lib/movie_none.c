/******************************************************************************
 *
 *    movie_none.c
 *
 *    Added 2026. The FFmpeg movie player (movie_lib.c) was written for
 *    the FFmpeg API of 2009 and has been removed. d0 is built with these
 *    stand-ins: a program that asks for a movie gets a message on stderr
 *    and no movie.
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

#include <stdio.h>
#include "movie_lib.h"

PUBLIC int movie_load(const char *filename)
{
	fprintf(stderr, "movie_load(): movies are not supported in this "
		"build of d0 (%s).\n", filename != NULL ? filename : "");
	return (-1);
}

PUBLIC void movie_play(void)
{
}

PUBLIC void movie_quit_event()
{
}

PUBLIC void movie_alloc_event(void *data1)
{
	(void) data1;
}

PUBLIC void movie_refresh_event(void *data1)
{
	(void) data1;
}
