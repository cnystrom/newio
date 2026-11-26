/******************************************************************************
 *
 *    loading.c
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

static int font;

void nio_loading(void)
{
    color black, white;

    black = nio_get_color("black");
    white = nio_get_color("white");

    font = nio_load_sys_font(NIO_MONO_BOLD,
			     NIO_DEFAULT_PTSIZE,
			     NIO_STYLE_NORMAL, white, black);

    nio_draw_text(font, 10, 10, "Loading resources...");

    nio_paint();
}

void nio_done_loading(void)
{
    nio_free_font(font);
}
