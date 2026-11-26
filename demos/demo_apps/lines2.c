/******************************************************************************
 *
 *    lines2.c
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
 *
 *    Soli Deo Gloria
 *
 */

#ifdef UNIX
#include <unistd.h>
#endif
#include "nio_lib.h"

int main(int argc, char *argv[])
{
    int i, j, font;
    color black, white;

    nio_app_init("lines2", "0.1");

    black = nio_get_color("black");
    white = nio_get_color("white");

    nio_set_screen(640, 480, black);

    font = nio_load_sys_font(NIO_DEFAULT_FONT,
			     NIO_DEFAULT_PTSIZE,
			     NIO_STYLE_NORMAL, white, black);

    nio_term_init(font, black, 10, 10, 24, 80);

    nio_send();

    j = 0;

    for (i = 0; i < 10000; i++) {

	int x1, y1, x2, y2;

	x1 = nio_rand_int(640);
	y1 = nio_rand_int(480);
	x2 = nio_rand_int(640);
	y2 = nio_rand_int(480);

	nio_draw_line_rand(x1, y1, x2, y2, NO_ALPHA);

	if (j++ == 100) {
	    nio_paint();
	    nio_send();

	    j = 0;
	}
    }

    nio_print_at(23, 0, "Hit any key to exit...");
    nio_paint();
    nio_send();

    nio_get_char();

    nio_free_font(font);
    nio_exit();
    exit(0);
}
