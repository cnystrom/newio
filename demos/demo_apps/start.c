/******************************************************************************
 *
 *    start.c
 *
 *    Copyright (C)  2005-2007  Chris Nystrom
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

#include <string.h>
#include "nio_lib.h"

void list(color c);

int main(int argc, char *argv[])
{
    color black, white;
    int font;

    nio_app_init("start", "0.1");

    black = nio_get_color("black");
    white = nio_get_color("white");

    font = nio_load_sys_font(NIO_DEFAULT_FONT,
			     NIO_DEFAULT_PTSIZE,
			     NIO_STYLE_NORMAL, white, black);

    nio_term_init(font, black, 10, 10, 24, 80);

    nio_print("NIO Start version 0.01");

    list(black);

    while (TRUE) {
	nio_string s;

	nio_print("PROGRAM> ");
	nio_get_string(s, MAX_STR_LEN);

	if (strncmp(s, "exit", 4) == 0) {
	    break;
	}

	system(s);

	list(black);
    }

    nio_free_font(font);
    nio_exit();
    exit(0);
}

void list(color c)
{
    nio_clear_screen(c);
    nio_print("Programs available:");

    nio_system_remote("cd /home/nio/nio; ls -1 *.nio | sed 's/.nio//g'");
}
