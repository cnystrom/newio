/******************************************************************************
 *
 *    mouse.c
 *
 *    Copyright (C) 2005  Chris Nystrom
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

#ifndef _MOUSE_H
#define _MOUSE_H

typedef struct {
	int b1;
	int b2;
	int b3;
	int x;
	int y;
} mouse_state;

mouse_state get_mouse_state(void);
mouse_state get_mouse_click(void);
mouse_state get_mouse_info(int *key);

Uint8 nio_GetRelativeMouseState(int *x, int *y);
Uint8 nio_GetMouseState(int *x, int *y);

PUBLIC void handle_mouse_move(SDL_Event * event);
PUBLIC void handle_mouse_button(SDL_Event * event);

#endif				/* _MOUSE_H */
