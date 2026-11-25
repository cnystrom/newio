/******************************************************************************
 *
 *    color_lib.c
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

#include <stdlib.h>
#include "SDL.h"
#include "color_lib.h"

extern SDL_PixelFormat *get_pixel_format(void);

PUBLIC Uint32 get_color_rgb(int red, int green, int blue)
{
	SDL_PixelFormat *pf;

	pf = get_pixel_format();

	if (red >= 0 && green >= 0 && blue >= 0)
		return (SDL_MapRGB(pf, red, green, blue));
	else {
		fprintf(stderr, "get_color_rgb(): invalid input\n");
		return (0.0);
	}
}

PUBLIC Uint32 get_rand_color(void)
{
	SDL_PixelFormat *pf;
	Uint32 red, green, blue;

	pf = get_pixel_format();

	red = (int) ((rand() % 254) + .5);
	green = (int) ((rand() % 254) + .5);
	blue = (int) ((rand() % 254) + .5);

	return (SDL_MapRGB(pf, red, green, blue));
}
