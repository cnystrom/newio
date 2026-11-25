/******************************************************************************
 *
 *    line_test3.c
 *
 *    Copyright (C) 2002, 2005  Chris Nystrom
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
 *    E-Mail: cnystrom@gmail.com
 *    Blog:   http://conversazione.blogspot.com
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
    int i;
    color black;

    nio_app_init("lines3", "0.1");

    black = nio_get_color("black");

    nio_set_screen(640, 480, black);

    nio_send();

    i = 0;

    while (1) {

	int key;
	int x1, y1, x2, y2;

	x1 = nio_rand_int(640);
	y1 = nio_rand_int(480);
	x2 = nio_rand_int(640);
	y2 = nio_rand_int(480);

	nio_draw_line_rand(x1, y1, x2, y2, NO_ALPHA);

	if (i++ == 100) {
	    nio_paint();
	    nio_send();

	    i = 0;

	    usleep(50000);
	}

	key = nio_get_key();

	if (key == ESC) {
	    nio_exit();
	    exit(0);
	}
    }

    nio_exit();
    exit(0);
}
