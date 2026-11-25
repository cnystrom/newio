/******************************************************************************
 *
 *    list.c
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
#include "str_lib.h"
#include "newio_version.h"

#define STRING_SIZE  (512)

int main(int argc, char *argv[])
{
    color black, white;
    int font;
    int image0;
    char command[STRING_SIZE] = "";

    nio_app_init("list", "0.1");

    black = nio_get_color("black");
    white = nio_get_color("white");

    nio_set_screen(640, 480, black);

    font = nio_load_sys_font(NIO_MONO_BOLD,
			     NIO_DEFAULT_PTSIZE,
			     NIO_STYLE_NORMAL, white, black);

    image0 = nio_load_image("/usr/local/nio/lib/list/midas_top_logo2.jpg");

    nio_draw_image(image0, 0, 0);

    nio_term_init(font, black, 0, 50, 40, 80);

    nio_print_at(0, 0, "NIO List version 0.01");
    nio_print_at(2, 0, "Programs available:");

    nio_paint();

#ifdef WIN32
    strlcpy(command, "dir /b c:\\cygwin\\usr\\local\\nio\\bin\\*.exe",
	    STRING_SIZE);
#else
    strlcpy(command, "cd /usr/local/nio", STRING_SIZE);
//      strlcat(command, NEWIO_VERSION1, STRING_SIZE);
    strlcat(command, "/bin; ls -1 *.nio | sed 's/.nio//g'", STRING_SIZE);
#endif
    nio_print_at(3, 0, "");

    nio_system_remote(command);

    nio_paint();

    nio_pause("Hit any key to exit...");
    nio_free_font(font);

    nio_exit();
    exit(0);
}
