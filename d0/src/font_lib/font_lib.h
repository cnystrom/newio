/******************************************************************************
 *
 *    font_lib.h
 *
 *    New original replacement, added 2026 after the previous third-party
 *    font helper (font_lib) was omitted from the published NewIO tree. This file is not
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

#ifndef _FONT_LIB_H
#define _FONT_LIB_H

#include "SDL.h"
#include "SDL_ttf.h"

#ifndef PRIVATE
#define PRIVATE static
#endif

#ifndef PUBLIC
#define PUBLIC
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef TRUE
#define TRUE (!FALSE)
#endif

/* System fonts: the same numbers as nio_lib/nio_font.h. The files are
 * GNU FreeFont TTFs in <install dir>/fonts/. */
#define NIO_MONO_BOLD_OBLIQUE	0
#define NIO_MONO_BOLD		1
#define NIO_MONO_OBLIQUE	2
#define NIO_MONO		3
#define NIO_SANS_BOLD_OBLIQUE	4
#define NIO_SANS_BOLD		5
#define NIO_SANS_OBLIQUE	6
#define NIO_SANS		7
#define NIO_SERIF_BOLD_ITALIC	8
#define NIO_SERIF_BOLD		9
#define NIO_SERIF_ITALIC	10
#define NIO_SERIF		11

#define MAX_SYS_FONT		11

#define NIO_DEFAULT_FONT	NIO_MONO
#define NIO_DEFAULT_PTSIZE	12

#define NIO_STYLE_NORMAL	TTF_STYLE_NORMAL
#define NIO_STYLE_BOLD		TTF_STYLE_BOLD
#define NIO_STYLE_ITALIC	TTF_STYLE_ITALIC
#define NIO_STYLE_UNDERLINE	TTF_STYLE_UNDERLINE

#define MAX_FONTS		(1024)

/* A loaded font and the colors it draws in. */
typedef struct {
	TTF_Font *font;
	int height;
	int ascent;
	int descent;
	int lineSkip;
	SDL_Color fg;
	SDL_Color bg;
} glyphFont;

/* fonts.c */
PUBLIC int font_init(void);
PUBLIC void font_quit(void);
PUBLIC int load_font(const char *filename, int point_size, int style,
		     Uint32 fg, Uint32 bg);
PUBLIC int load_sys_font(int sys_font, int point_size, int style,
			 Uint32 fg, Uint32 bg);
PUBLIC void free_font(int font_num);
PUBLIC void free_all_fonts(void);
PUBLIC glyphFont get_font(int font_num);
PUBLIC TTF_Font *open_sys_ttf(int sys_font, int point_size);

/* text.c */
PUBLIC void text_size(glyphFont * gf, const char *s, SDL_Rect * r);
PUBLIC void draw_text(glyphFont * gf, const char *s, int x, int y);
PUBLIC void draw_resource_text(const char *s);

#endif				/* _FONT_LIB_H */
