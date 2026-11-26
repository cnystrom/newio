/******************************************************************************
 *
 *    sdl_lib.h
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
 *
 *    Soli Deo Gloria
 *
 */

#ifndef _SDL_LIB_H
#define _SDL_LIB_H

#ifndef _SDL_H
#include "SDL.h"
#endif				/*  */

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
#define TRUE (! FALSE)
#endif				/*  */
PUBLIC void sdl_init(void);
PUBLIC void set_window_caption(char *s);
PUBLIC void delay(int ticks);
PUBLIC int get_ticks(void);

#endif				/* _SDL_LIB_H */
