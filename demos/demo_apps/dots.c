/******************************************************************************
 *
 *    dots.c
 *
 *    Copyright (C) 2002-2007  Chris Nystrom
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

#define W (640)
#define H (480)

int main(int argc, char *argv[])
{
    int i, j, font;
    color black, white;

    nio_app_init("dots", "0.1");

    black = nio_get_color("black");
    white = nio_get_color("white");

    nio_set_screen(W, H, black);

    font = nio_load_sys_font(NIO_DEFAULT_FONT,
			     NIO_DEFAULT_PTSIZE,
			     NIO_STYLE_NORMAL, white, black);

    nio_term_init(font, black, 10, 10, 24, 80);

    nio_send();

    j = 0;

    for (i = 0; i < 10000; i++) {

	int key, x, y;

	x = nio_rand_int(W);
	y = nio_rand_int(H);

	nio_draw_point_rand(x, y);

	nio_printf_at(2, 2, "%5d: %3d,%3d", i + 1, x, y);

	if (j++ == 100) {
	    nio_paint();
	    nio_send();
	    j = 0;

	    key = nio_get_key();

	    if (key == ESC) {
		nio_free_font(font);
		nio_exit();
		exit(0);
	    }

	    nio_delay(50);
	}

    }

    nio_print_at(4, 4, "Hit any key to exit...");
    nio_paint();
    nio_send();

    nio_get_char();

    nio_free_font(font);
    nio_exit();
    exit(0);
}
