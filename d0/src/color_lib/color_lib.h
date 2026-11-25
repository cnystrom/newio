/******************************************************************************
 *
 *    color_lib.h
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

#ifndef _COLOR_LIB_H
#define _COLOR_LIB_H

#ifndef _SDL_H
#include "SDL.h"
#endif				/*  */

#ifndef PRIVATE
#define PRIVATE static
#endif				/*  */

#ifndef PUBLIC
#define PUBLIC
#endif				/*  */

/*
typedef struct {
	Uint8 red;
	Uint8 green;
	Uint8 blue;
} color_t;
*/
//PUBLIC Uint32 get_color(const char *s);
PUBLIC Uint32 get_color_rgb(int red, int green, int blue);
PUBLIC Uint32 get_rand_color(void);

#endif				// _COLOR_LIB_H
