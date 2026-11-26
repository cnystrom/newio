/******************************************************************************
 *
 *    term_lib.c
 *
 *    Copyright (C) 2002, 2005  Chris Nystrom
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU Lessor General Public License as published
 *    by the Free Software Foundation; either version 2.1 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but without any warranty whatsoever.
 *
 *    For more license information see:
 *
 *      http://www.gnu.org/copyleft/lessor.html
 *
 *    Contact Author at:
 *
 *    Chris Nystrom
 *
 *    E-Mail: cnystrom@gmail.com
 *
 *    Soli Deo Gloria
 *
 */

#include <stdio.h>
#include <string.h>
#ifndef WIN32
#include "SDL/SDL.h"
#else				/*  */
#include "SDL.h"
#endif				/*  */
#include "../screen_lib/screen_lib.h"
#include "../font_lib/font_lib.h"
#include "term_lib.h"

PRIVATE int x_offset(int col);
PRIVATE int y_offset(int row);
PRIVATE term_screen ts;
PRIVATE int row, col;
PRIVATE int maxrow = 24;
PRIVATE int maxcol = 80;
PRIVATE int x_home = 6;
PRIVATE int y_home = 3;
PRIVATE int char_width;
PRIVATE int char_height;
PRIVATE int horiz_space = 1;
PRIVATE int vert_space;
PRIVATE int clear_screen_flag = FALSE;
PRIVATE int font;
PRIVATE int bg;

PUBLIC void term_init(int fn, int bg_color, int x_home_in, int y_home_in,
		      int maxrow_in, int maxcol_in)
{
	int i, factor;

	if (fn < 0) {
		fprintf(stderr, "term_init(): bad font num - < 0\n");
		return;
	}

	if (bg_color < 0) {
		fprintf(stderr, "term_init(): bad bg color - < 0\n");
		return;
	}

	if (x_home < 0 || y_home < 0) {
		fprintf(stderr, "term_init(): bad parameter - x,y < 0\n");
		return;
	}

	if (x_home > 256 || y_home > 256) {
		fprintf(stderr,
			"term_init(): bad parameter - x,y > 256\n");
		return;
	}

	if (maxrow_in < 0 || maxcol_in < 0) {
		fprintf(stderr, "term_init(): bad parameter - max < 0\n");
		return;
	}

	if (maxrow_in > 256 || maxcol_in > 256) {
		fprintf(stderr,
			"term_init(): bad parameter . max > 256\n");
		fprintf(stderr, "maxrow_in = %d\n", maxrow_in);
		fprintf(stderr, "maxcol_in = %d\n", maxcol_in);
		return;
	}

	row = col = 0;

	x_home = x_home_in;
	y_home = y_home_in;

	maxrow = maxrow_in;
	maxcol = maxcol_in;

	for (i = 0; i < maxrow; i++)
		ts[i].len = 0;

	font = fn;
	bg = bg_color;

	char_height = get_font_height(font);
	char_width = get_font_width(font);

	factor = char_width / 2;

	char_height = char_height - factor;
	char_width = char_width - factor;

	vert_space = (factor / 2) + 1;
}


/*
PRIVATE void
term_debug(void)
{
  int i, j, len;

  printf("--\n");

  for (i = 0; i < maxrow; i++)
  {
    len = ts[i].len;

    for (j = 0; j < len; j++)
      putchar(ts[i].tc[j].c);

    printf("\n");
  }

  printf("--\n");
}
*/

PUBLIC void increment_row(void)
{
	row++;
	if (row > maxrow - 1) {
		clear_screen_flag = TRUE;
		return;
	}
	col = 0;
}

PUBLIC void term_clear(void)
{
	int i;
	row = col = 0;
	for (i = 0; i < maxrow; i++)
		ts[i].len = 0;
	draw_rectangle(x_home, y_home, (maxcol * (char_width + 1)),
		       (maxrow * (char_height + vert_space)), bg,
		       NO_ALPHA, FILL);
}

PUBLIC void term_put_char(int c)
{
	if (clear_screen_flag) {
		term_clear();
		clear_screen_flag = FALSE;
	}
	if (c == LF || c == CR) {
		increment_row();
		return;
	} else if (c == BS) {
		int x, y;
		if (row == 0 && col == 0)
			return;
		ts[row].len = ts[row].len - 1;
		col--;
		if (col < 0) {
			row--;
			col = maxcol - 1;
		}
		x = x_offset(col);
		y = y_offset(row);
		draw_rectangle(x, y, char_width, 19, bg, NO_ALPHA, FILL);
		return;
	} else {
		ts[row].tc[col].c = c;
		ts[row].len++;
		term_draw_char(row, col);
		col++;
		if (col >= maxcol)
			increment_row();
	}
}

PUBLIC void term_draw_char(int row, int col)
{
	int x, y;
	x = x_offset(col);
	y = y_offset(row);
	draw_rectangle(x, y + vert_space, char_width,
		       char_height + vert_space, bg, NO_ALPHA, FILL);
	draw_char(font, ts[row].tc[col].c, x, y);
}

PUBLIC void term_show_cursor(void)
{
	int x, y;
	x = x_offset(col);
	y = y_offset(row);
	draw_rectangle(x, y + 2, 2, 22, bg, NO_ALPHA, FILL);
}

PUBLIC void term_clear_cursor(void)
{
	int x, y;
	x = x_offset(col);
	y = y_offset(row);
	printf("x = %d\n", x);
	printf("y = %d\n", y);
	draw_rectangle(x, y + 2, 2, 22, bg, NO_ALPHA, FILL);
}

PUBLIC void term_set_max(int x, int y)
{
	if (x > 0 && x < MAXROW)
		maxrow = x;
	if (y > 0 && y < MAXCOL)
		maxcol = y;
}

PUBLIC void term_set_location(int x, int y)
{
	if (x >= 0 && x <= maxrow)
		row = x;
	if (y >= 0 && y <= maxcol)
		col = y;
}

PRIVATE int x_offset(int col)
{
	return (((char_width + horiz_space) * col) + x_home);
}

PRIVATE int y_offset(int row)
{
	return (((char_height + vert_space) * row) + y_home);
}

PUBLIC void term_print(char *s)
{
	int i, s_len;
	s_len = strlen(s);
	for (i = 0; i < s_len; i++)
		term_put_char(*s++);
}
