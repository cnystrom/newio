/******************************************************************************
 *
 *    SDL_prim.c
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

#include <stdlib.h>
#include <math.h>

#include "SDL_prim.h"

static Uint32 read_pixel(SDL_Surface * s, int x, int y)
{
	int bpp = s->format->BytesPerPixel;
	Uint8 *p = (Uint8 *) s->pixels + y * s->pitch + x * bpp;

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
	default:
		return *(Uint32 *) p;
	}
}

static void write_pixel(SDL_Surface * s, int x, int y, Uint32 pixel)
{
	int bpp = s->format->BytesPerPixel;
	Uint8 *p = (Uint8 *) s->pixels + y * s->pitch + x * bpp;

	switch (bpp) {
	case 1:
		*p = (Uint8) pixel;
		break;
	case 2:
		*(Uint16 *) p = (Uint16) pixel;
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
	default:
		*(Uint32 *) p = pixel;
		break;
	}
}

/* Plot one pixel, clipped, blended at the given alpha (255 = solid). */
static void plot(SDL_Surface * s, int x, int y, Uint32 color, int alpha)
{
	Uint8 r, g, b, dr, dg, db;

	if (x < s->clip_rect.x || y < s->clip_rect.y ||
	    x >= s->clip_rect.x + s->clip_rect.w ||
	    y >= s->clip_rect.y + s->clip_rect.h || alpha <= 0)
		return;

	if (alpha >= 255) {
		write_pixel(s, x, y, color);
		return;
	}

	SDL_GetRGB(color, s->format, &r, &g, &b);
	SDL_GetRGB(read_pixel(s, x, y), s->format, &dr, &dg, &db);
	dr += ((r - dr) * alpha) / 255;
	dg += ((g - dg) * alpha) / 255;
	db += ((b - db) * alpha) / 255;
	write_pixel(s, x, y, SDL_MapRGB(s->format, dr, dg, db));
}

static void hspan(SDL_Surface * s, int x1, int x2, int y, Uint32 color,
		  int alpha)
{
	int x;

	if (x1 > x2) {
		x = x1;
		x1 = x2;
		x2 = x;
	}
	for (x = x1; x <= x2; x++)
		plot(s, x, y, color, alpha);
}

static void line_plain(SDL_Surface * s, int x1, int y1, int x2, int y2,
		       Uint32 color, int alpha)
{
	int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
	int dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
	int err = dx + dy, e2;

	for (;;) {
		plot(s, x1, y1, color, alpha);
		if (x1 == x2 && y1 == y2)
			break;
		e2 = 2 * err;
		if (e2 >= dy) {
			err += dy;
			x1 += sx;
		}
		if (e2 <= dx) {
			err += dx;
			y1 += sy;
		}
	}
}

/* Smooth line: each step covers two pixels, shared by distance. */
static void line_smooth(SDL_Surface * s, int x1, int y1, int x2, int y2,
			Uint32 color, int alpha)
{
	int steep = abs(y2 - y1) > abs(x2 - x1);
	int t, x;
	double grad, y;

	if (steep) {
		t = x1; x1 = y1; y1 = t;
		t = x2; x2 = y2; y2 = t;
	}
	if (x1 > x2) {
		t = x1; x1 = x2; x2 = t;
		t = y1; y1 = y2; y2 = t;
	}

	grad = (x2 == x1) ? 0.0 : (double) (y2 - y1) / (double) (x2 - x1);
	y = y1;

	for (x = x1; x <= x2; x++) {
		int yi = (int) floor(y);
		double f = y - yi;
		int a1 = (int) (alpha * (1.0 - f) + 0.5);
		int a2 = (int) (alpha * f + 0.5);

		if (steep) {
			plot(s, yi, x, color, a1);
			plot(s, yi + 1, x, color, a2);
		} else {
			plot(s, x, yi, color, a1);
			plot(s, x, yi + 1, color, a2);
		}
		y += grad;
	}
}

static int use_alpha(Uint8 alpha, Uint8 flags)
{
	return (flags & SDL_TG_ALPHA) ? alpha : 255;
}

void SDL_drawLine_TG(SDL_Surface * s, int x1, int y1, int x2, int y2,
		     Uint32 color, Uint8 alpha, Uint8 flags)
{
	int a = use_alpha(alpha, flags);

	if (s == NULL)
		return;
	if ((flags & SDL_TG_ANTIALIAS) && x1 != x2 && y1 != y2)
		line_smooth(s, x1, y1, x2, y2, color, a);
	else
		line_plain(s, x1, y1, x2, y2, color, a);
}

void SDL_drawCircle_TG(SDL_Surface * s, int cx, int cy, int r,
		       Uint32 color, Uint8 alpha, Uint8 flags)
{
	int a = use_alpha(alpha, flags);
	int x, y, err;

	if (s == NULL || r < 0)
		return;

	if (flags & SDL_TG_FILL) {
		/* one span per row, so blended rows aren't drawn twice */
		for (y = -r; y <= r; y++) {
			int w = (int) floor(sqrt((double) r * r - (double) y * y)
					    + 0.5);
			hspan(s, cx - w, cx + w, cy + y, color, a);
		}
		return;
	}

	x = r;
	y = 0;
	err = 1 - r;
	while (x >= y) {
		plot(s, cx + x, cy + y, color, a);
		plot(s, cx + y, cy + x, color, a);
		plot(s, cx - y, cy + x, color, a);
		plot(s, cx - x, cy + y, color, a);
		plot(s, cx - x, cy - y, color, a);
		plot(s, cx - y, cy - x, color, a);
		plot(s, cx + y, cy - x, color, a);
		plot(s, cx + x, cy - y, color, a);
		y++;
		if (err < 0) {
			err += 2 * y + 1;
		} else {
			x--;
			err += 2 * (y - x) + 1;
		}
	}
}

void SDL_drawTriangle_TG(SDL_Surface * s, int x1, int y1, int x2, int y2,
			 int x3, int y3, Uint32 color, Uint8 alpha,
			 Uint8 flags)
{
	int a = use_alpha(alpha, flags);
	int t, y;

	if (s == NULL)
		return;

	if (!(flags & SDL_TG_FILL)) {
		SDL_drawLine_TG(s, x1, y1, x2, y2, color, alpha, flags);
		SDL_drawLine_TG(s, x2, y2, x3, y3, color, alpha, flags);
		SDL_drawLine_TG(s, x3, y3, x1, y1, color, alpha, flags);
		return;
	}

	/* sort the corners by y */
	if (y1 > y2) {
		t = x1; x1 = x2; x2 = t;
		t = y1; y1 = y2; y2 = t;
	}
	if (y2 > y3) {
		t = x2; x2 = x3; x3 = t;
		t = y2; y2 = y3; y3 = t;
	}
	if (y1 > y2) {
		t = x1; x1 = x2; x2 = t;
		t = y1; y1 = y2; y2 = t;
	}

	if (y1 == y3) {
		int lo = x1, hi = x1;
		if (x2 < lo) lo = x2;
		if (x3 < lo) lo = x3;
		if (x2 > hi) hi = x2;
		if (x3 > hi) hi = x3;
		hspan(s, lo, hi, y1, color, a);
		return;
	}

	for (y = y1; y <= y3; y++) {
		/* long edge 1-3, short edge 1-2 then 2-3 */
		int xa = x1 + (x3 - x1) * (y - y1) / (y3 - y1);
		int xb;

		if (y < y2 || y2 == y3) {
			xb = (y2 == y1) ? x2 :
			    x1 + (x2 - x1) * (y - y1) / (y2 - y1);
		} else {
			xb = x2 + (x3 - x2) * (y - y2) / (y3 - y2);
		}
		hspan(s, xa, xb, y, color, a);
	}
}
