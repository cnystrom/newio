/******************************************************************************
 *
 *    bltsrc.c
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

int rightdown = FALSE;
int leftdown = FALSE;
int brunning = TRUE;

void GetInput()
{
    SDL_Event event;
    if (nio_poll_event(&event)) {
	if (event.type == SDL_KEYDOWN) {
	    if (event.key.keysym.sym == SDLK_LEFT)
		leftdown = TRUE;
	    if (event.key.keysym.sym == SDLK_RIGHT)
		rightdown = TRUE;
	    if (event.key.keysym.sym == ESC)
		brunning = FALSE;
	    if (event.key.keysym.sym == 'q')
		brunning = FALSE;
	}
	if (event.type == SDL_KEYUP) {
	    if (event.key.keysym.sym == SDLK_LEFT)
		leftdown = FALSE;
	    if (event.key.keysym.sym == SDLK_RIGHT)
		rightdown = FALSE;
	}
    }
}

int main(int argc, char *argv[])
{
    int xinc, font, image_num, xsave;
    color black, white;

    nio_app_init("bltsrc", "0.1");

    black = nio_get_color("black");
    white = nio_get_color("white");

    nio_set_screen(400, 400, black);

    font = nio_load_sys_font(NIO_DEFAULT_FONT,
			     NIO_DEFAULT_PTSIZE,
			     NIO_STYLE_NORMAL, white, black);

    nio_term_init(font, black, 10, 10, 24, 80);

    nio_send();

    // 3909x400
    image_num = nio_load_image("/usr/local/nio/lib/bltsrc/repeat.jpg");

    xsave = 1;
    xinc = 0;

    while (brunning) {

	if (xinc > 3908) {
	    xinc = 0;
	}
	if (xinc < 0) {
	    xinc = 3909 + xinc;
	}
	if (xinc != xsave) {
	    if (xinc > 3909 - 400) {
		int x1 = 3909 - xinc;
		int x2 = 400 - x1;
		nio_draw_image_src(image_num, xinc, 0, x1, 400, 0, 0);
		nio_draw_image_src(image_num, 0, 0, x2, 400, x1, 0);
	    } else {
		nio_draw_image_src(image_num, xinc, 0, 400, 400, 0, 0);
	    }

	    nio_printf_at(2, 2, "%d", xinc);
	    nio_paint();
	    nio_send();

	    xsave = xinc;
	}

	usleep(33000 / 4);
	GetInput();
	usleep(33000 / 4);
	GetInput();

	if (rightdown) {
	    xinc++;
	}
	if (leftdown) {
	    xinc--;
	}
    }

    nio_free_font(font);
    nio_exit();
    exit(0);
}
