/******************************************************************************
 *
 *    movie_lib.h
 *
 *    Copyright (C) 2006  Chris Nystrom
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
 *
 *    Soli Deo Gloria
 *
 */

#ifndef _MOVIE_LIB_H
#define _MOVIE_LIB_H

#ifndef PRIVATE
#define PRIVATE static
#endif				/*  */

#ifndef PUBLIC
#define PUBLIC
#endif				/*  */

#ifndef FALSE
#define FALSE  (0)
#endif				/*  */

#ifndef TRUE
#define TRUE  !FALSE
#endif				/*  */

#ifndef OFF
#define OFF  (0)
#endif				/*  */

#ifndef ON
#define ON   (!OFF)
#endif				/*  */

PUBLIC int movie_load(const char *filename);
PUBLIC void movie_play(void);
PUBLIC void movie_quit_event();
PUBLIC void movie_alloc_event(void *data1);
PUBLIC void movie_refresh_event(void *data1);

#endif				// _MOVIE_LIB_H
