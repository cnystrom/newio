/******************************************************************************
 *
 *    example3.c
 *
 *    Copyright (C) 2005-2007  Chris Nystrom
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
#include "nio_lib.h"

typedef int bool;

#define INC_FACTOR (1)

static color black;
static color white;
static int xi = 1;
static int font_num;
static int image_num;

void draw_screen(void)
{
    nio_clear_screen(black);
#ifdef WIN32
    nio_print_at(0, 0, "\rEXAMPLE 3 version 0.01\r");
#else
    nio_print_at(0, 0, "\nEXAMPLE 3 version 0.01\n");
#endif
    nio_draw_image(image_num, xi, 450);
    nio_paint();
}

void example3_init(void)
{
    black = nio_get_color("black");
    white = nio_get_color("white");

    font_num = nio_load_sys_font(NIO_DEFAULT_FONT,
				 NIO_DEFAULT_PTSIZE,
				 NIO_STYLE_NORMAL, white, black);

    nio_term_init(font_num, black, 10, 10, 24, 80);

    nio_print_at(1, 0, "EXAMPLE 3 version 0.01");

    nio_print_at(3, 0, "Loading image file...");

    nio_paint();

    image_num = nio_load_image("/usr/local/nio/lib/example3/bumper.bmp");
}

int main(int argc, char *argv[])
{
    bool f_exit = FALSE;
    int xinc = INC_FACTOR;
    SDL_Event event;

    nio_app_init("example3", "0.1");
//      nio_set_write_wait(1000);

    nio_set_screen(640, 480, black);

    example3_init();

    while (!f_exit) {
	draw_screen();

	while (nio_poll_event(&event)) {
	    switch (event.type) {
	    case SDL_MOUSEBUTTONDOWN:
		if (SDL_BUTTON_LEFT == event.button.button) {
		    f_exit = TRUE;
		}
		break;
	    case SDL_KEYDOWN:
		if (event.key.keysym.sym == ESC) {
		    f_exit = TRUE;
		}
		break;
	    case SDL_QUIT:
		f_exit = TRUE;
		break;
	    default:
		break;
	    }
	}

	xi += xinc;

	if (xi > 540) {
	    xinc = -(INC_FACTOR);
	}

	if (xi < 1) {
	    xinc = INC_FACTOR;
	}
	nio_delay(20);
    }

    nio_free_image(image_num);
    nio_free_font(font_num);
    nio_exit();
    exit(0);
}
