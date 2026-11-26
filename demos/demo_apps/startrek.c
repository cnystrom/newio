/******************************************************************************
 *
 *    startrek.c
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

static int lfont;

void nio_loading(void)
{
    color black, white;

    black = nio_get_color("black");
    white = nio_get_color("white");

    lfont = nio_load_sys_font(NIO_MONO_BOLD,
			      NIO_DEFAULT_PTSIZE,
			      NIO_STYLE_NORMAL, white, black);

    nio_draw_text(lfont, 10, 10, "Loading resources...");

    nio_paint();
}

void nio_done_loading(void)
{
    nio_free_font(lfont);
}

int main(int argc, char *argv[])
{
//      int font;
    int image_num, sound_num;
    color black, white;

    nio_app_init("startrek", "0.1");

    black = nio_get_color("black");
    white = nio_get_color("white");

    nio_set_screen(640, 480, black);

    nio_loading();
/*
	font = nio_load_sys_font(NIO_DEFAULT_FONT,
				 NIO_DEFAULT_PTSIZE,
				 NIO_STYLE_NORMAL, white, black);

	nio_term_init(font, black, 10, 10, 24, 80);

	nio_print("NIO Star Trek version 0.01");

	nio_paint();
	nio_send();
*/
    image_num = nio_load_image("/usr/local/nio/lib/startrek/startrek.jpg");
    nio_send();

    sound_num = nio_load_sound("/usr/local/nio/lib/startrek/c604.wav");
    nio_send();

    nio_done_loading();

    nio_clear_screen(black);

    nio_draw_image(image_num, 300, 75);
    nio_send();

    nio_play_sound(sound_num, 0);
    nio_send();

    nio_paint();
    nio_send();

/*
	nio_print_at(23, 0, "Hit any key to exit...");
	nio_send();
*/
    nio_get_char();

    nio_free_image(image_num);
    nio_free_sound(sound_num);
//      nio_free_font(font);

    nio_exit();
    exit(0);
}
