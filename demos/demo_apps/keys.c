/******************************************************************************
 *
 *    keys.c
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

int main(int argc, char *argv[])
{
    int key, font;
    color black, white;

    nio_app_init("keys", "0.1");

    black = nio_get_color("black");
    white = nio_get_color("white");

    nio_set_screen(640, 480, white);

    font = nio_load_sys_font(NIO_DEFAULT_FONT,
			     NIO_DEFAULT_PTSIZE,
			     NIO_STYLE_NORMAL, black, white);

    nio_term_init(font, white, 10, 10, 24, 80);

    nio_printf_at(2, 2, "Key = ");

    nio_paint();
    nio_send();

    while (1) {

	key = nio_get_key();

	// sleep while waiting for input
	if (key == 0) {
	    nio_delay(1);
	    continue;
	}

	if (key == ESC) {
	    nio_free_font(font);
	    nio_exit();
	    exit(0);
	}

	nio_printf_at(2, 2, "Key = %3d", key);
	nio_paint();
	nio_send();
    }

    exit(0);
}
