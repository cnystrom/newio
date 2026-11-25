/******************************************************************************
 *
 *    term_lib.h
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
 *    Blog:   http://conversazione.blogspot.com
 *    AIM:    nystromchris
 *
 *    Soli Deo Gloria
 *
 */

#ifndef _TERM_LIB_H
#define _TERM_LIB_H

#ifndef PRIVATE
#define PRIVATE static
#endif				/*  */

#ifndef PUBLIC
#define PUBLIC
#endif				/*  */

#ifndef _BYTE_H
#define _BYTE_H
typedef char byte;
#endif				// _BYTE_H

#ifndef FALSE
#define FALSE  (0)
#endif				/*  */

#ifndef TRUE
#define TRUE  !FALSE
#endif				/*  */

#ifndef EOF
#define EOF       (-1)
#endif				/*  */

/* ASCII Key Codes */
#ifndef NUL
#define NUL       (0)
#endif				/*  */

#ifndef BS
#define BS        (8)
#endif				/*  */

#ifndef LF
#define LF        (10)
#endif				/*  */

#ifndef RET
#define RET       (10)
#endif				/*  */

#ifndef CR
#define CR        (13)
#endif				/*  */

#ifndef ESC
#define ESC       (27)
#endif				/*  */

#ifndef BUFSIZ
#define BUFSIZ    (8192)
#endif				/*  */

#ifndef MAX
#define MAX(a,b) (a>b ? a : b)
#endif				/*  */

#define MAXROW  (128)
#define MAXCOL  (512)
#define DEFAULT_FG_COLOR  "white"
#define DEFAULT_BG_COLOR  "black"

struct term_char_struct {
//  int fg_color;
//  int bg_color;
	int c;
};

typedef struct term_char_struct term_char;

struct term_line_struct {
	term_char tc[MAXCOL];
	int len;
};

typedef struct term_line_struct term_line;

typedef term_line term_screen[MAXROW];

PUBLIC void term_init(int fn, int bg_color, int x_home_in, int y_home_in,
		      int maxrow_in, int maxcol_in);
PUBLIC void increment_row(void);
PUBLIC void term_clear(void);
PUBLIC void term_put_char(int c);
PUBLIC void term_draw_char(int row, int col);
PUBLIC void term_reverse_video(void);
PUBLIC void term_print(char *s);
PUBLIC void term_show_cursor(void);
PUBLIC void term_clear_cursor(void);
PUBLIC void term_set_location(int x, int y);

#endif				// _TERM_LIB_H
