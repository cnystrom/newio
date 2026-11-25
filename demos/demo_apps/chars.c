/******************************************************************************
 *
 *    chars.c
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

#include <stdio.h>
#include "nio_lib.h"

int main(int argc, char *argv[])
{
    int c, font;
    color black, white;

    nio_app_init("chars", "0.1");

    black = nio_get_color("black");
    white = nio_get_color("white");

    nio_set_screen(640, 480, white);

    font = nio_load_sys_font(NIO_DEFAULT_FONT,
			     NIO_DEFAULT_PTSIZE,
			     NIO_STYLE_NORMAL, black, white);

    nio_term_init(font, white, 1, 1, 24, 80);

    nio_print("NIO Char Test version 0.01");

    nio_print_at(2, 0, "Hit any key [ ESC to quit ] ...");

    nio_print_at(4, 0, "");

    nio_paint();
    nio_send();

    c = nio_get_char();

    while (c != EOF) {
	if (c == NIOK_ESCAPE) {
	    nio_free_font(font);
	    nio_exit();
	    exit(0);
	}

	nio_put_char(c);
	nio_paint();
	nio_send();

	c = nio_get_char();
    }

    nio_exit();
    exit(0);
}
