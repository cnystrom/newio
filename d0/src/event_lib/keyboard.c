/******************************************************************************
 *
 *    keyboard.c
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

#include "nio.h"
#include "msg_lib.h"
#include "event_lib.h"

void handle_key_event(SDL_KeyboardEvent * key)
{
    int key_state;
    int key_modifier;
    int key_val = 0;

    if (key->type == SDL_KEYUP) {
	key_state = 0;
    } else {
	key_state = 1;
    }

    key_modifier = key->keysym.mod;
    key_val = key->keysym.sym;

    msg_set_num(NIO_IN_KEY);
    msg_pack_int32(key_state);
    msg_pack_int32(key_modifier);
    msg_pack_int32(key_val);
    msg_send();
}
