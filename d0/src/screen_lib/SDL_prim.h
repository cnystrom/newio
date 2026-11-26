/******************************************************************************
 *
 *    SDL_prim.h
 *
 *    New original replacement, added 2026 after the previous third-party
 *    SDL_prim drawing library was omitted from the published NewIO tree. This file is not
 *    derived from that source. It provides the functions the d0 client
 *    calls, under the same names.
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

#ifndef _SDL_PRIM_H
#define _SDL_PRIM_H

#include "SDL.h"

/* flags */
#define SDL_TG_ALPHA		0x01	/* blend with the given alpha */
#define SDL_TG_ANTIALIAS	0x02	/* smooth lines */
#define SDL_TG_FILL		0x04	/* fill circles and triangles */

/*
 * Draw on surface s, which the caller has locked if it needs locking.
 * color is a pixel value for s's format. alpha is 0 (clear) to 255
 * (solid) and is used when SDL_TG_ALPHA is set.
 */
void SDL_drawLine_TG(SDL_Surface * s, int x1, int y1, int x2, int y2,
		     Uint32 color, Uint8 alpha, Uint8 flags);
void SDL_drawCircle_TG(SDL_Surface * s, int x, int y, int r,
		       Uint32 color, Uint8 alpha, Uint8 flags);
void SDL_drawTriangle_TG(SDL_Surface * s, int x1, int y1, int x2, int y2,
			 int x3, int y3, Uint32 color, Uint8 alpha,
			 Uint8 flags);

#endif				/* _SDL_PRIM_H */
