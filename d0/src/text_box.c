/******************************************************************************
 *
 *    text_box.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include "font_lib/font_lib.h"
#include "screen_lib/screen_lib.h"
#include "color_lib/color_lib.h"
#include "ascii_codes.h"
#include "text_box.h"

PRIVATE void text_box_insert_char(text_box_ptr tb, int c);
PRIVATE void text_box_loop(text_box_ptr tb);
PRIVATE void draw_text_box(text_box_ptr tb);
PRIVATE void text_box_show_cursor(text_box_ptr tb, int color);
PRIVATE char *get_mask_string(text_box_ptr tb);

PRIVATE char mask_string[TB_MAX_COL + 1];

PUBLIC int text_box(text_box_ptr tb)
{
	SDL_Rect r;
	glyphFont gf;

	if (tb->box_size > TB_MAX_COL) {
		fprintf(stderr, "draw_text_box(): size too big.\n");
		return (-1);
	}

	tb->pos = tb->index = strlen(tb->str);


	if (tb->index > tb->box_size) {
		fprintf(stderr, "draw_text_box(): ");
		fprintf(stderr, "default entry larger than text box.\n");
		return (-2);
	}

	gf = get_font(tb->font_num);
	text_size(&gf, "X", &r);
	tb->font_width = r.w;
	tb->font_height = gf.height;

	draw_text_box(tb);
	text_box_loop(tb);

	return (0);
}

void draw_cursor(text_box_ptr tb)
{
	int color = get_rand_color();
	text_box_show_cursor(tb, color);
	update_screen();
}

void erase_cursor_at_current_position(text_box_ptr tb)
{
#ifdef WIN32
	draw_rectangle(tb->x_home +
		       ((tb->pos + 1) * (tb->font_width)) - 0,
		       tb->y_home, 1, tb->font_height, tb->fg_color,
		       NO_ALPHA, FILL);
	draw_rectangle(tb->x_home +
		       ((tb->pos + 1) * (tb->font_width)) - 0,
		       tb->y_home + tb->font_height, 1,
		       20 - tb->font_height, tb->bg_color, NO_ALPHA, FILL);
#else
	draw_rectangle(tb->x_home +
		       ((tb->pos + 1) * (tb->font_width - 1)) + 1,
		       tb->y_home, 1, tb->font_height, tb->fg_color,
		       NO_ALPHA, FILL);
	draw_rectangle(tb->x_home +
		       ((tb->pos + 1) * (tb->font_width - 1)) + 1,
		       tb->y_home + tb->font_height, 1,
		       20 - tb->font_height, tb->bg_color, NO_ALPHA, FILL);
#endif
}

PRIVATE void text_box_insert_char(text_box_ptr tb, int c)
{
	char *temp = tb->str;
	int len = strlen(tb->str);
	int i;

	if (c == BS) {
		if (tb->pos > 0) {
			erase_cursor_at_current_position(tb);
			if (tb->pos != len) {
				for (i = tb->pos - 1; i < len; i++)
					temp[i] = temp[i + 1];
				tb->pos--;
				tb->index--;
			} else {
				tb->str[--tb->index] = '\0';
				tb->pos--;
			}
			draw_text_box(tb);
		}
	} else if (c == 0x7f) {
		if (tb->pos != len) {
			for (i = tb->pos; i < len; i++)
				temp[i] = temp[i + 1];
			tb->index--;
			draw_text_box(tb);
		}
	} else if (tb->index < tb->box_size) {
		erase_cursor_at_current_position(tb);

		for (i = len + 1; i >= tb->pos; i--)
			temp[i + 1] = temp[i];

		tb->str[tb->pos++] = c;
		tb->index++;
		draw_text_box(tb);
	}

}

PRIVATE void text_box_loop(text_box_ptr tb)
{
	int key;
	SDL_Event ev;

	while (SDL_WaitEvent(&ev)) {
		switch (ev.type) {

		case SDL_KEYDOWN:
			if (ev.key.keysym.sym == SDLK_LEFT
			    || (ev.key.keysym.sym == SDLK_KP4
				&& !(ev.key.keysym.mod & KMOD_NUM))) {
				if (tb->pos) {
					erase_cursor_at_current_position
					    (tb);
					--tb->pos;
					draw_cursor(tb);
				}
			} else if (ev.key.keysym.sym == SDLK_HOME
				   || (ev.key.keysym.sym == SDLK_KP7
				       && !(ev.key.keysym.
					    mod & KMOD_NUM))) {
				erase_cursor_at_current_position(tb);
				tb->pos = 0;
				draw_cursor(tb);
			} else if (ev.key.keysym.sym == SDLK_END
				   || (ev.key.keysym.sym == SDLK_KP1
				       && !(ev.key.keysym.
					    mod & KMOD_NUM))) {
				erase_cursor_at_current_position(tb);
				tb->pos = strlen(tb->str);
				draw_cursor(tb);
			} else if (ev.key.keysym.sym == SDLK_RIGHT
				   || (ev.key.keysym.sym == SDLK_KP6
				       && !(ev.key.keysym.
					    mod & KMOD_NUM))) {
				if (tb->pos < strlen(tb->str)) {
					erase_cursor_at_current_position
					    (tb);
					++tb->pos;
					draw_cursor(tb);
				}
			} else {
				key = ev.key.keysym.unicode & 0x7F;

				if (ev.key.keysym.sym == SDLK_DELETE
				    || (ev.key.keysym.sym == SDLK_KP_PERIOD
					&& !(ev.key.keysym.
					     mod & KMOD_NUM))) {
					key = 0x7f;	// DEL
				}

				if (ev.key.keysym.sym == SDLK_BACKSPACE &&
				    ev.key.keysym.unicode == SDLK_DELETE) {
					key = BS;
				}

				if (ESC == key) {
					exit(0);
				}

				if (CR == key) {
					erase_cursor_at_current_position
					    (tb);
					return;
				}
				if (NUL != key) {
					text_box_insert_char(tb, key);
				}
			}
			break;

		case SDL_QUIT:
			SDL_Quit();
			exit(0);
			break;
		}
	}
}

PRIVATE void draw_text_box(text_box_ptr tb)
{
	Uint32 color;
	glyphFont gf;

	gf = get_font(tb->font_num);

	draw_rectangle(tb->x_home, tb->y_home,
		       (tb->font_width - 1) * (tb->box_size + 2),
		       tb->font_height, tb->fg_color, NO_ALPHA, FILL);

	if (tb->pw_flag) {
		draw_text(&gf, get_mask_string(tb),
			  tb->x_home + tb->font_width, tb->y_home);
	} else {
		draw_text(&gf, tb->str,
			  tb->x_home + tb->font_width, tb->y_home);
	}

	color = get_rand_color();
	text_box_show_cursor(tb, color);
	update_screen();
}

PRIVATE void text_box_show_cursor(text_box_ptr tb, int color)
{
//#ifdef WIN32
	draw_rectangle(tb->x_home +
		       ((tb->pos + 1) * (tb->font_width)) - 0,
		       tb->y_home, 1, 15, color, NO_ALPHA, FILL);
//#else
//	draw_rectangle(tb->x_home +
//		       ((tb->pos + 1) * (tb->font_width - 1)) + 1,
//		       tb->y_home, 1, 20, color, NO_ALPHA, FILL);
//endif
}

PRIVATE char *get_mask_string(text_box_ptr tb)
{
	int i, len;

	len = strlen(tb->str);

	for (i = 0; i < len; i++) {
		mask_string[i] = '*';
	}

	mask_string[len] = '\0';

	return (mask_string);
}
