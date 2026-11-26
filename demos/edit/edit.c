/******************************************************************************
 *
 *    edit.c
 *
 *    Copyright (C) 2004-2007  Chris Nystrom
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
 *    E-Mail: cnystrom@newio.org
 *
 *    Soli Deo Gloria
 *
 */

#include "nio_lib.h"

#define PTSIZE  (14)

#define WIDTH  (640)
#define HEIGHT  (480)

#define COLS  (80)
#define LINES (34)

#define LINE_SIZE  (20)
#define HALF_LINE_SIZE  (LINE_SIZE / 2)

#define MAIN_MENU_STRING "  File   Edit  Search  View  Options  Help"
#define MAIN_MENU_UNDERL "  _      _     _       _     _        _   "

#define ICON_STRING "   New  Open  Save  Print  Cut  Copy  Paste Find"

#define HELP_STRING " F1=HELP"
#define LINE_STRING "Line:"
#define COL_STRING "Col:"

#define DEFAULT_FILENAME "Untitled1"

static int font1;
static int font2;

static color black;
static color white;

static color color1;
static color color2;

static int icon_new;
static int icon_open;
static int icon_save;
static int icon_print;
static int icon_cut;
static int icon_copy;
static int icon_paste;
static int icon_find;

static int font;

void nio_loading(void)
{
    color black, white;

    black = nio_get_color("black");
    white = nio_get_color("white");

    font = nio_load_sys_font(NIO_MONO_BOLD,
			     NIO_DEFAULT_PTSIZE,
			     NIO_STYLE_NORMAL, black, white);

    nio_draw_text(font, 10, 10, "Loading resources...");

    nio_paint();
}

void nio_done_loading(void)
{
    nio_free_font(font);
}

void init_edit(void)
{
    nio_app_init("edit", "0.1");

    black = nio_get_color("black");
    white = nio_get_color("white");

    color1 = nio_get_color("lightgray");
    color2 = nio_get_color("gray");	// dark

    nio_set_screen(640, 480, color2);

    nio_loading();

    icon_new =
	nio_load_image_colorkey
	("/usr/local/nio/lib/edit/stock_new_24.png", TRUE, black);
    icon_open =
	nio_load_image_colorkey
	("/usr/local/nio/lib/edit/stock_open_24.png", TRUE, black);
    icon_save =
	nio_load_image_colorkey
	("/usr/local/nio/lib/edit/stock_save_24.png", TRUE, black);
    icon_print =
	nio_load_image_colorkey
	("/usr/local/nio/lib/edit/stock_print_24.png", TRUE, black);
    icon_cut =
	nio_load_image_colorkey
	("/usr/local/nio/lib/edit/stock_cut_24.png", TRUE, black);
    icon_copy =
	nio_load_image_colorkey
	("/usr/local/nio/lib/edit/stock_copy_24.png", TRUE, black);
    icon_paste =
	nio_load_image_colorkey
	("/usr/local/nio/lib/edit/stock_paste_24.png", TRUE, black);
    icon_find =
	nio_load_image_colorkey
	("/usr/local/nio/lib/edit/stock_search_24.png", TRUE, black);

    font1 = nio_load_sys_font(NIO_DEFAULT_FONT,
			      PTSIZE, NIO_STYLE_BOLD, black, color2);

    font2 = nio_load_sys_font(NIO_DEFAULT_FONT,
			      PTSIZE, NIO_STYLE_BOLD, black, color1);

    nio_done_loading();

//      nio_term_init(font2, darkblue, 10, 10, (LINES - 2), (COLS - 2));
}

void draw_screen(void)
{
//      int file_name_len;

    nio_clear_screen(color2);

    nio_draw_text(font1, 0, 0, MAIN_MENU_STRING);
    nio_draw_text(font1, 0, 0, MAIN_MENU_UNDERL);

    nio_draw_rectangle_rgb(0, LINE_SIZE, WIDTH,
			   (HEIGHT - (LINE_SIZE * 2)), color1,
			   NO_ALPHA, FILL);

    nio_draw_image(icon_new, 30, 25);
    nio_draw_image(icon_open, 80, 25);
    nio_draw_image(icon_save, 135, 25);
    nio_draw_image(icon_print, 190, 25);
    nio_draw_image(icon_cut, 245, 25);
    nio_draw_image(icon_copy, 295, 25);
    nio_draw_image(icon_paste, 355, 25);
    nio_draw_image(icon_find, 405, 25);

    nio_draw_text(font2, 0, 50, ICON_STRING);

    nio_draw_line_rgb(9, 79, 624, 79, color2, NO_ALPHA);
    nio_draw_line_rgb(9, 79, 9, 439, color2, NO_ALPHA);
    nio_draw_line_rgb(9, 439, 624, 439, color2, NO_ALPHA);
    nio_draw_line_rgb(624, 79, 624, 439, color2, NO_ALPHA);

    nio_draw_rectangle_rgb(10, 80, 615, 360, white, NO_ALPHA, FILL);

/*
	file_name_len = strlen(DEFAULT_FILENAME);

//	nio_draw_rectangle(260, LINE_SIZE, ZZ
	nio_draw_text(font1, 260, LINE_SIZE, DEFAULT_FILENAME);
*/
    nio_draw_text(font1, 0, (HEIGHT - LINE_SIZE), HELP_STRING);
    nio_draw_text(font1, 400, (HEIGHT - LINE_SIZE), LINE_STRING);
    nio_draw_text(font1, 500, (HEIGHT - LINE_SIZE), COL_STRING);

    nio_paint();
}


int main(int argc, char *argv[])
{
    init_edit();

    draw_screen();

    while (1) {
	SDL_Event event;
	int gotone;

	gotone = FALSE;
	while (nio_poll_event(&event)) {
	    gotone = TRUE;
	    switch (event.type) {
	    case SDL_MOUSEBUTTONDOWN:
		if (SDL_BUTTON_RIGHT == event.button.button) {
		    nio_exit();
		    exit(0);
		}
		break;
	    case SDL_KEYDOWN:
		if (event.key.keysym.sym == ESC) {
		    nio_exit();
		    exit(0);
		}
		break;
	    case SDL_QUIT:
		nio_exit();
		exit(0);
		break;
	    default:
		break;
	    }
	}
    }
}
