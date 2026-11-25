/******************************************************************************
 *
 *    text_box.h
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

#ifndef _NIO_TEXT_BOX_H
#define _NIO_TEXT_BOX_H

#ifndef PRIVATE
#define PRIVATE static
#endif

#ifndef PUBLIC
#define PUBLIC
#endif

#define TB_MAX_COL  (80)

typedef struct {
	char str[TB_MAX_COL + 1];
	int box_size;
	int index;
	int x_home;
	int y_home;
	int font_num;
	int font_height;
	int font_width;
	int fg_color;
	int bg_color;
	int pw_flag;
	int pos;
} text_box_t;

typedef text_box_t *text_box_ptr;

PUBLIC int text_box(text_box_ptr tb);

#endif				/* _NIO_TEXT_BOX_H */
