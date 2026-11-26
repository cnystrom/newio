/******************************************************************************
 *
 *    colors.h
 *
 *    New original replacement, added 2026 after the previous third-party
 *    colors.h (from Tcl/Tk) was omitted from the published NewIO tree. This file is not
 *    derived from that source.
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

#ifndef _NIO_COLORS_H
#define _NIO_COLORS_H

/* An RGB color, 0-255 per channel. */
typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} color;

/* Look up a color by name ("red", "darkblue", "light gray", ...).
 * Case and spaces are ignored. An unknown name gives black. */
color get_color(const char *name);

/* A random color. */
color get_rand_color(void);

#endif				/* _NIO_COLORS_H */
