/******************************************************************************
 *
 *    screen_lib.c
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

#include <SDL.h>
#include "SDL_prim.h"
#include "image_lib.h"
#include "screen_lib.h"

PRIVATE SDL_Surface *screen = NULL;
PRIVATE int antialiasing_enable = FALSE;

PUBLIC void antialiasing_control(int flag)
{
	antialiasing_enable = flag;
}

PUBLIC int init_screen(int sw, int sh, int options)
{
	screen = SDL_SetVideoMode(sw, sh, 0, options);

	if (screen == NULL) {
		fprintf(stderr, "Can not set video mode: %s\n",
			SDL_GetError());
		return (-1);
	}

	return (0);
}

PUBLIC int resize_screen(int w, int h)
{
	SDL_Surface *old_screen = NULL;

	old_screen = screen;

	screen = SDL_SetVideoMode(w, h,
				  screen->format->BitsPerPixel,
				  screen->flags);

	if (screen != old_screen) {
		return 1;
	}

	return 0;
}

SDL_Overlay *CreateYUVOverlay(int width, int height, int type)
{
	return SDL_CreateYUVOverlay(width, height, type, screen);
}

PUBLIC SDL_PixelFormat *get_pixel_format(void)
{
	return (screen->format);
}

PUBLIC void blit_screen(SDL_Surface * s, SDL_Rect * r)
{
	SDL_BlitSurface(s, NULL, screen, r);
}

PUBLIC void fill_rect(SDL_Rect * r, Uint32 color)
{
	SDL_FillRect(screen, r, color);
}

PUBLIC void clear_screen(Uint32 color)
{
	SDL_FillRect(screen, NULL, color);
}

PUBLIC void update_screen(void)
{
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}

PUBLIC void update_rectangle(int x, int y, int w, int h)
{
	int w1, h1;

	w1 = get_screen_width();
	h1 = get_screen_height();

	// If off screen just update whole screen
	if (((x + w) > w1) || ((y + h) > h1)) {
		update_screen();
	} else {
		SDL_UpdateRect(screen, x, y, w, h);
	}
}

PUBLIC void lockScreen(void)
{
	if (SDL_MUSTLOCK(screen)) {
		if (SDL_LockSurface(screen) < 0) {
			fprintf(stderr, "Can't lock screen: %s\n",
				SDL_GetError());
			return;
		}
	}
}

PUBLIC void unlockScreen(void)
{
	if (SDL_MUSTLOCK(screen)) {
		SDL_UnlockSurface(screen);
	}
}

PUBLIC int get_screen_width(void)
{
	if (screen == NULL) {
		fprintf(stderr, "get_screen_width(): screen not set.\n");
		return (1);
	}

	return (screen->w);
}

PUBLIC int get_screen_height(void)
{
	if (screen == NULL) {
		fprintf(stderr, "get_screen_height(): screen not set.\n");
		return (-1);
	}

	return (screen->h);
}

//============================================================

PUBLIC int draw_rectangle(int x, int y, int w, int h, Uint32 color,
			  int alpha, int fill)
{
	SDL_Rect dstrect;

	dstrect.x = x;
	dstrect.y = y;
	dstrect.w = w;
	dstrect.h = h;

	if (fill) {
		// Fix me: alpha not working with fill
		SDL_FillRect(screen, &dstrect, color);
	} else {
		draw_line(x, y, x, y + h, color, alpha, 0);
		draw_line(x, y, x + w, y, color, alpha, 0);
		draw_line(x, y + h, x + w, y + h, color, alpha, 0);
		draw_line(x + w, y, x + w, y + h, color, alpha, 0);
	}

	return (0);
}

PUBLIC void draw_line(int x1, int y1, int x2, int y2, Uint32 color,
		      int alpha, int fill)
{
	int flags = 0;
	int w, h;

	flags ^= SDL_TG_ALPHA;
	if (antialiasing_enable) {
		flags ^= SDL_TG_ANTIALIAS;
	}

	if (fill) {
		flags ^= SDL_TG_FILL;
	}

	w = get_screen_width();
	h = get_screen_height();

	if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0) {
		fprintf(stderr, "draw_line(): bad input\n");
		return;
	}

	if (x1 > w || x2 > w || y1 > h || y2 > h) {
		fprintf(stderr, "draw_line(): bad input\n");
		return;
	}

	if (color < 0.0) {
		fprintf(stderr, "draw_line(): color bad input\n");
		return;
	}

	if (alpha < 0 || alpha > 255) {
		fprintf(stderr, "draw_line(): alpha bad input\n");
		return;
	}

	lockScreen();
	SDL_drawLine_TG(screen, x1, y1, x2, y2, color, alpha, flags);
	unlockScreen();
}

PUBLIC void draw_arc(int x, int y, int r, Uint32 color, int alpha,
		     int fill)
{
	int flags = 0;

	flags ^= SDL_TG_ALPHA;
	if (antialiasing_enable) {
		flags ^= SDL_TG_ANTIALIAS;
	}

	if (fill) {
		flags ^= SDL_TG_FILL;
	}

	lockScreen();
	SDL_drawCircle_TG(screen, x, y, r, color, alpha, flags);
	unlockScreen();
}

PUBLIC void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3,
			  Uint32 color, int alpha, int fill)
{
	int flags = 0;

	flags ^= SDL_TG_ALPHA;
	if (antialiasing_enable) {
		flags ^= SDL_TG_ANTIALIAS;
	}

	if (fill) {
		flags ^= SDL_TG_FILL;
	}

	lockScreen();
	SDL_drawTriangle_TG(screen, x1, y1, x2, y2, x3, y3, color, alpha,
			    flags);
	unlockScreen();
}

PUBLIC int draw_image(int i_num, int x, int y)
{
	SDL_Surface *image;
	SDL_Rect dstrect;

	if (i_num < 0 || i_num >= MAX_IMAGES) {
		fprintf(stderr, "draw_image(): bad image number.\n");
		return (-1);
	}

	image = get_image(i_num);

	if (NULL == image) {
		fprintf(stderr,
			"draw_image(): no image available to draw.\n");
		return (-2);
	}

	dstrect.x = x;
	dstrect.y = y;
	dstrect.w = image->w;
	dstrect.h = image->h;

	if (SDL_BlitSurface(image, NULL, screen, &dstrect) == 0) {
		return (0);
	} else {
		fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
		return (-3);
	}
}

PUBLIC int draw_image_src(int i_num, int xsrc, int ysrc, int xsize,
			  int ysize, int xdst, int ydst)
{
	SDL_Surface *image;
	SDL_Rect srcrect, dstrect;

	if (i_num < 0 || i_num >= MAX_IMAGES) {
		fprintf(stderr, "draw_image(): bad image number.\n");
		return (-1);
	}

	image = get_image(i_num);

	if (NULL == image) {
		fprintf(stderr,
			"draw_image(): no image available to draw.\n");
		return (-2);
	}

	dstrect.x = xdst;
	dstrect.y = ydst;
	dstrect.w = xsize;
	dstrect.h = ysize;

	srcrect.x = xsrc;
	srcrect.y = ysrc;
	srcrect.w = xsize;
	srcrect.h = ysize;

//      dstrect.x = xdst;
//      dstrect.y = ydst;
//      dstrect.w = image->w;
//      dstrect.h = image->h;

	if (SDL_BlitSurface(image, &srcrect, screen, &dstrect) == 0) {
		return (0);
	} else {
		fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
		return (-3);
	}
}

PUBLIC void draw_point(int x, int y, Uint32 color)
{
	lockScreen();
	putpixel(x, y, color);
	unlockScreen();
}

//
//  Return the pixel value at (x, y)
//
//  NOTE: The surface must be locked before calling this!
//
PUBLIC Uint32 getpixel(int x, int y)
{
	int bpp = screen->format->BytesPerPixel;

	// Here p is the address to the pixel we want to retrieve 

	Uint8 *p = (Uint8 *) screen->pixels + y * screen->pitch + x * bpp;

	switch (bpp) {
	case 1:
		return *p;

	case 2:
		return *(Uint16 *) p;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;

	case 4:
		return *(Uint32 *) p;

	default:
		return 0;	// shouldn't happen, but avoids warnings 
	}
}

//
// Set the pixel at (x, y) to the given value
//
//   NOTE: The surface must be locked before calling this!
//
PUBLIC void putpixel(int x, int y, Uint32 pixel)
{
	int bpp = screen->format->BytesPerPixel;

	// Here p is the address to the pixel we want to set

	Uint8 *p = (Uint8 *) screen->pixels + y * screen->pitch + x * bpp;

	switch (bpp) {
	case 1:
		*p = pixel;
		break;

	case 2:
		*(Uint16 *) p = pixel;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		} else {
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;

	case 4:
		*(Uint32 *) p = pixel;
		break;
	}
}
