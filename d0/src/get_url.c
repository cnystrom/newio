/******************************************************************************
 *
 *    get_url.c
 *
 *    Copyright (C) 2002, 2005  Chris Nystrom
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but without any warranty whatsoever.
 *
 *    For more license information see:
 *
 *      http://www.gnu.org/copyleft/gpl.html
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
#include "SDL.h"
#include "str_lib.h"
#include "font_lib/font_lib.h"
#include "screen_lib/screen_lib.h"
#include "sdl_lib/sdl_lib.h"
#include "color_lib/color_lib.h"
#include "text_box.h"

#define CAPTION  "Welcome to the Dreadnought Application Browser"
#define WHITE    "white"
#define BLACK    "black"
#define URL      "URL:"

extern void get_url_loop(text_box_ptr tb);

void get_url(char *sURL)
{
	int font_0, font_1, fw;
	Uint32 fg, bg;
	glyphFont gf0, gf1;
	SDL_Rect r;
	text_box_t tb;
	init_screen(640, 32, SDL_ANYFORMAT);

	set_window_caption(CAPTION);

	fg = get_color_rgb(255, 255, 255);
	bg = get_color_rgb(0, 0, 0);

	font_0 = load_sys_font(NIO_DEFAULT_FONT,
			       NIO_DEFAULT_PTSIZE,
			       NIO_STYLE_NORMAL, fg, bg);

	font_1 = load_sys_font(NIO_DEFAULT_FONT,
			       NIO_DEFAULT_PTSIZE,
			       NIO_STYLE_NORMAL, bg, fg);

	gf0 = get_font(font_0);
	gf1 = get_font(font_1);

	text_size(&gf0, "X", &r);

	fw = r.w;		// font width

	draw_text(&gf0, URL, fw * 3, 6);

	strlcpy(tb.str, sURL, TB_MAX_COL);
	tb.box_size = 64;
	tb.x_home = fw * 8;
	tb.y_home = 6;
	tb.font_num = font_1;
	tb.fg_color = fg;
	tb.bg_color = bg;
	tb.pw_flag = FALSE;

	text_box(&tb);

	strlcpy(sURL, tb.str, TB_MAX_COL);

//      printf("sURL = |%s|\n", sURL);

	free_font(font_0);
	free_font(font_1);
}
