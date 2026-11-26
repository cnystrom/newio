/******************************************************************************
 *
 *    reply.h
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

#ifndef REPLY_H
#define _REPLY_H
#include <SDL/SDL.h>

typedef struct commandreply {
	int32 cmdnumber;
	int32 enable;
	int32 waiting;
	SDL_mutex *mutex;
	SDL_cond *cond;
	int32 value;
} COMMANDREPLY;

void init_replys();
void handle_reply(int32 cmdnumber, int32 value);
int32 wait_reply(int32 cmdnumber);
void destroy_replys();

#endif				/* _KEYBAORD_H */
