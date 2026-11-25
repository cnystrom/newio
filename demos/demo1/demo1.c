/******************************************************************************
 *
 *    demo1.c
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
 *    Blog:   http://newio.blogspot.com
 *    AIM:    nystromchris
 *
 *    Soli Deo Gloria
 *
 */

#ifdef UNIX
#include <unistd.h>
#endif
#ifdef WIN32
#include "win32_lib.h"
#endif
#include "nio_lib.h"

#define MAX_MODE    (2)

static int font;

void nio_loading(void)
{
    color black, white;

    black = nio_get_color("black");
    white = nio_get_color("white");

    font = nio_load_sys_font(NIO_MONO_BOLD,
			     NIO_DEFAULT_PTSIZE,
			     NIO_STYLE_NORMAL, white, black);

    nio_draw_text(font, 10, 10, "Loading resources...");

    nio_paint();

    nio_send();
}

void nio_done_loading(void)
{
    nio_free_font(font);
}

int main(int argc, char *argv[])
{
    int cls_flag = 1;
    int mode = 0;
    int mode_flag = 1;
    color black, white;
    int key = 0;
    SDL_Event event;
    int gotone;
    int mnum;


    nio_app_init("demo1", "0.1");

    black = nio_get_color("black");
    white = nio_get_color("white");

    nio_set_screen(640, 480, black);

    nio_loading();

    mnum = nio_load_music("/usr/local/nio/lib/demo1/Rome_Italy.ogg");

    nio_done_loading();

    nio_clear_screen(black);

    nio_play_music(mnum, 0);
    nio_send();

    while (1) {
	int x, y;
	int b1 = 0, b2 = 0, b3 = 0;
	int mousex = -1, mousey = -1;

	x = nio_rand_int(640);
	y = nio_rand_int(480);

	if (0 == mode) {
	    nio_draw_rectangle_rand(x, y, 10, 10, NO_ALPHA, FILL);
	}
	if (1 == mode) {
	    nio_draw_arc_rand(x, y, 10, NO_ALPHA, NO_FILL);
	}
	if (2 == mode) {
	    int x2, y2;

	    x2 = nio_rand_int(640);
	    y2 = nio_rand_int(480);

	    nio_draw_line_rand(x, y, x2, y2, NO_ALPHA);
	}

	nio_paint();

	gotone = FALSE;
	while (nio_poll_event(&event)) {
	    gotone = TRUE;
	    switch (event.type) {
	    case SDL_MOUSEBUTTONDOWN:
		if (SDL_BUTTON_LEFT == event.button.button)
		    b1 = 1;
		if (SDL_BUTTON_MIDDLE == event.button.button)
		    b2 = 1;
		if (SDL_BUTTON_RIGHT == event.button.button)
		    b3 = 1;
		mousex = event.button.x;
		mousey = event.button.y;
		break;
	    case SDL_MOUSEBUTTONUP:
		if (SDL_BUTTON_LEFT == event.button.button)
		    b1 = 0;
		if (SDL_BUTTON_MIDDLE == event.button.button)
		    b2 = 0;
		if (SDL_BUTTON_RIGHT == event.button.button)
		    b3 = 0;
		mousex = event.button.x;
		mousey = event.button.y;
		break;
	    case SDL_KEYDOWN:
		key = event.key.keysym.sym;
		break;
	    case SDL_KEYUP:
		key = 0;
		break;
	    case SDL_QUIT:
		key = ESC;
		break;
	    default:
		break;
	    }
	}

	if (b1 || key == CR) {
	    if (mode_flag) {
		mode++;

		if (mode > MAX_MODE) {
		    mode = 0;
		}

		mode_flag = 0;
	    }
	    b1 = 0;
	    cls_flag = 1;
	} else {
	    mode_flag = 1;
	}

	if (b2 || key == SPACEBAR) {
	    if (cls_flag) {
		nio_draw_rectangle_rand(0, 0, 640, 480, NO_ALPHA, FILL);

		nio_send();
		cls_flag = 0;
	    }
	    mode_flag = 1;
	    b2 = 0;
	} else {
	    cls_flag = 1;
	}

	if (b3 || key == ESC) {
	    nio_stop_music(mnum);
	    nio_exit();
	    exit(0);
	}

	usleep(50000);
    }
}
