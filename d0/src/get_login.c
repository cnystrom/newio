/******************************************************************************
 *
 *    get_login.c
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
 *    Blog:   http://conversazione.blogspot.com
 *    AIM:    nystromchris
 *
 *    Soli Deo Gloria
 *
 */

#include "SDL.h"
#include "str_lib.h"
#include "font_lib/font_lib.h"
#include "screen_lib/screen_lib.h"
#include "color_lib/color_lib.h"
#include "text_box.h"

#define WHITE  "white"
#define BLACK "black"
#define LOGIN "Login:"
#define PASSWD "Password:"

void get_login_info(char *username, char *password)
{
	int font_0, font_1;
	glyphFont gf0, gf1;
	int fw;			// font width
	Uint32 fg, bg;
	SDL_Rect r;
	text_box_t tb1, tb2;

	init_screen(640, 64, SDL_ANYFORMAT);

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
	fw = r.w;

	draw_text(&gf0, LOGIN, fw * 3, 6);
	draw_text(&gf0, PASSWD, fw * 3, 32);

	strlcpy(tb1.str, "", TB_MAX_COL);
	tb1.box_size = 16;
	tb1.x_home = fw * 12;
	tb1.y_home = 6;
	tb1.font_num = font_1;
	tb1.fg_color = fg;
	tb1.bg_color = bg;
	tb1.pw_flag = FALSE;

	text_box(&tb1);

	strlcpy(username, tb1.str, TB_MAX_COL);

	strlcpy(tb2.str, "", TB_MAX_COL);
	tb2.box_size = 16;
	tb2.x_home = fw * 12;
	tb2.y_home = 32;
	tb2.font_num = font_1;
	tb2.fg_color = fg;
	tb2.bg_color = bg;
	tb2.pw_flag = TRUE;

	text_box(&tb2);

	strlcpy(password, tb2.str, TB_MAX_COL);

	free_font(font_0);
	free_font(font_1);

//      printf("username = %s\n", username);
//      printf("password = %s\n", password);
}
