/******************************************************************************
 *
 *    mouse.c
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
#include "nio.h"
#include "msg_lib.h"
#include "event_lib.h"

PRIVATE point_t mouse_loc;

PUBLIC void mouse_button_handler(Uint8 type, Uint8 button)
{
    int mouse_button = -1;
    int button_state = -1;

    if (SDL_BUTTON_LEFT == button) {
	mouse_button = 0;
    } else if (SDL_BUTTON_MIDDLE == button) {
	mouse_button = 1;
    } else if (SDL_BUTTON_RIGHT == button) {
	mouse_button = 2;
    }

    if (type == SDL_MOUSEBUTTONDOWN) {
	button_state = PRESSED;
    } else {
	button_state = RELEASED;
    }

    msg_set_num(NIO_IN_MOUSE_BUTTON);
    msg_pack_int32(mouse_button);
    msg_pack_int32(button_state);
    msg_send();
}

PUBLIC void mouse_move_handler(int x, int y)
{
    mouse_loc.x = x;
    mouse_loc.y = y;
    msg_set_num(NIO_IN_MOUSE_MOVE);
    msg_pack_int32(x);
    msg_pack_int32(y);
    msg_send();
}

PUBLIC point_t get_mouse_loc(void)
{
    return (mouse_loc);
}
