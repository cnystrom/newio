/******************************************************************************
 *
 *    event_lib.c
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

#ifndef _EVENT_LIB_H
#define _EVENT_LIB_H

#ifndef _SDL_H
#include "SDL.h"
#endif				/*  */

#ifndef PRIVATE
#define PRIVATE static
#endif				/*  */

#ifndef PUBLIC
#define PUBLIC
#endif				/*  */

#ifndef NUL
#define NUL  (0)
#endif				/*  */

#ifndef BS
#define BS   (8)
#endif				/*  */

#ifndef LF
#define LF   (10)
#endif				/*  */

#ifndef RET
#define RET  (10)
#endif				/*  */

#ifndef ESC
#define ESC  (27)
#endif				/*  */
PUBLIC void handle_events(void);
PUBLIC int get_char(void);
typedef struct {
    int x;
    int y;
} point_t;
enum { PRESSED = 0x01, RELEASED = 0x00 };

#ifndef OFF
#define OFF  (0)
#endif				/*  */
#ifndef ON
#define ON   (!OFF)
#endif				/*  */
PUBLIC void mouse_button_handler(Uint8 type, Uint8 button);
PUBLIC void mouse_move_handler(int x, int y);
PUBLIC void mouse_cursor(void);
PUBLIC void reset_event_control();

#endif				// _EVENT_LIB_H
