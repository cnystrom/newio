/******************************************************************************
 *
 *    mouse.c
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

#include "nio_lib.h"

void update_screen(mouse_state ms);

color black;
int font;

int main(int argc, char *argv[])
{
    int update = 0;
    color white;
    mouse_state ms, ms_new;

    nio_app_init("mouse", "0.1");

    black = nio_get_color("black");
    white = nio_get_color("white");

    nio_set_screen(640, 480, black);

    font = nio_load_sys_font(NIO_DEFAULT_FONT,
			     NIO_DEFAULT_PTSIZE,
			     NIO_STYLE_NORMAL, white, black);

    nio_term_init(font, black, 10, 10, 24, 80);

    nio_send();

    ms = nio_mouse_state();

    while (1) {

	ms_new = nio_mouse_state();

	if (ms.b1 != ms_new.b1) {
	    update = 1;
	}

	if (ms.b2 != ms_new.b2) {
	    update = 1;
	}

	if (ms.b3 != ms_new.b3) {
	    update = 1;
	}

	if (ms.x != ms_new.x) {
	    update = 1;
	}

	if (ms.y != ms_new.y) {
	    update = 1;
	}

	if (update) {
	    ms = ms_new;
	    update_screen(ms);
	    update = 0;
	}
    }

    nio_exit();
    exit(0);
}

void update_screen(mouse_state ms)
{
    nio_clear_screen(black);
    nio_print_at(2, 2, "NIO Mouse Test (version 0.01)");

    if (ms.b1 == PRESSED) {
	nio_print_at(6, 2, "MOUSE BUTTON 1 PRESSED");
    }

    if (ms.b2 == PRESSED) {
	nio_print_at(8, 2, "MOUSE BUTTON 2 PRESSED");
    }

    if (ms.b3 == PRESSED) {
	nio_free_font(font);
	nio_exit();
	exit(0);
    }

    nio_printf_at(10, 2, "MOUSE X = %d", ms.x);
    nio_printf_at(12, 2, "MOUSE Y = %d", ms.y);

    nio_paint();
    nio_send();
}
