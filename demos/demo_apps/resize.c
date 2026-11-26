/******************************************************************************
 *
 *    resize.c
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

#include "nio_lib.h"

int main(int argc, char *argv[])
{
    int font1, font2;
    color black, white, dark_blue;

    nio_app_init("resize", "0.1");

    black = nio_get_color("black");
    white = nio_get_color("white");
    dark_blue = nio_get_color("darkblue");

    nio_set_screen(640, 480, black);

    font1 = nio_load_sys_font(NIO_DEFAULT_FONT,
			      NIO_DEFAULT_PTSIZE,
			      NIO_STYLE_NORMAL, white, black);

    font2 = nio_load_sys_font(NIO_DEFAULT_FONT,
			      NIO_DEFAULT_PTSIZE,
			      NIO_STYLE_NORMAL, white, dark_blue);

    nio_term_init(font1, black, 10, 10, 24, 80);

    nio_print("NIO Resize version 0.01");
    nio_paint();
    nio_send();

    nio_print_at(4, 0, "Hit any key to resize...");
    nio_paint();
    nio_send();

    nio_get_char();

    nio_set_screen(320, 240, dark_blue);

    nio_term_init(font2, dark_blue, 10, 10, 24, 80);

    nio_print_at(4, 0, "Hit any key to exit...");
    nio_paint();
    nio_send();

    nio_get_char();

    nio_exit();
    exit(0);
}
