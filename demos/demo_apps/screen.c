/******************************************************************************
 *
 *    screen.c
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

#include "nio_lib.h"
#include "msg_lib.h"

#define LINES (34)

int main(int argc, char *argv[])
{
    int i, font;
    color black, white;

    nio_app_init("screen", "0.1");

    black = nio_get_color("black");
    white = nio_get_color("white");

    nio_set_screen(640, 480, black);

    nio_clear_screen(black);

    font = nio_load_sys_font(NIO_DEFAULT_FONT,
			     NIO_DEFAULT_PTSIZE,
			     NIO_STYLE_NORMAL, white, black);

    nio_term_init(font, black, 0, 0, LINES, 80);

    for (i = 1; i < 10; i++)
	nio_printf
	    ("%d 3456789|123456789|123456789|123456789|123456789|123456789|123456789|1234567890",
	     i);

    for (i = 10; i <= LINES; i++)
	nio_printf
	    ("%d 456789|123456789|123456789|123456789|123456789|123456789|123456789|1234567890",
	     i);

    nio_paint();

    nio_pause("");

    nio_free_font(font);
    nio_exit();
    exit(0);
}
