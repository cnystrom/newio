/******************************************************************************
 *
 *    reply.c
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

#include "event.h"
#include "../common/nio_types.h"
#include "../common/nio.h"
#include "reply.h"

COMMANDREPLY cmdreply[_NUM_NIO_COMMANDS_] = {
	{0, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_INIT, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_EXIT, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_CHAR_TO_STDOUT, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_STRING_TO_STDOUT, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_INT_TO_STDOUT, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_PUT_CHAR, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_SYSTEM_LOCAL, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_LOAD_FONT, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_LOAD_SYS_FONT, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_FREE_FONT, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_DRAW_TEXT, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_SET_SCREEN, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_CLEAR_SCREEN, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_DRAW_RECTANGLE_RGB, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_DRAW_POINT_RGB, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_DRAW_LINE_RGB, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_DRAW_ARC_RGB, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_SOUND, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_BEEP, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_LOAD_MUSIC, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_PLAY_MUSIC, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_STOP_MUSIC, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_LOAD_SOUND, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_PLAY_SOUND, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_FREE_SOUND, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_LOAD_MOVIE, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_PLAY_MOVIE, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_LOAD_IMAGE, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_DRAW_IMAGE, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_FREE_IMAGE, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_TERM_INIT, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_PRINT, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_PRINT_AT, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_PAINT, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_CURSOR, FALSE, FALSE, NULL, NULL, -1}
	,
	{NIO_OUT_DRAW_IMAGE_SRC, FALSE, FALSE, NULL, NULL, -1}
	,
};

void init_replys()
{
	int i;
	for (i = 0; i < _NUM_NIO_COMMANDS_; i++) {
		if (cmdreply[i].enable) {
			cmdreply[i].mutex = SDL_CreateMutex();
			cmdreply[i].cond = SDL_CreateCond();
			cmdreply[i].waiting = FALSE;
			cmdreply[i].value = -1;
		}
	}
}

void handle_reply(int32 cmdnumber, int32 value)
{
	int32 waiting = FALSE;
	if (cmdreply[cmdnumber].enable) {
		SDL_mutexP(cmdreply[cmdnumber].mutex);
		waiting = cmdreply[cmdnumber].waiting;
		SDL_mutexV(cmdreply[cmdnumber].mutex);
		if (waiting) {
			cmdreply[cmdnumber].value = value;
			SDL_CondSignal(cmdreply[cmdnumber].cond);
		}
	}
}

int32 wait_reply(int32 cmdnumber)
{
	int32 ret = -1;
	int32 res;
	if (cmdreply[cmdnumber].enable) {
		SDL_mutexP(cmdreply[cmdnumber].mutex);
		cmdreply[cmdnumber].waiting = TRUE;
		// wait 10 msecs for wire??
		res =
		    SDL_CondWaitTimeout(cmdreply[cmdnumber].cond,
					cmdreply[cmdnumber].mutex, 10);
		if (res == 0) {
			ret = cmdreply[cmdnumber].value;
		} else
			ret = -1;
		cmdreply[cmdnumber].waiting = FALSE;
		SDL_mutexV(cmdreply[cmdnumber].mutex);
	}
	return ret;
}

void destroy_replys()
{
	int i;
	for (i = 0; i < _NUM_NIO_COMMANDS_; i++) {
		if (cmdreply[i].enable) {
			SDL_DestroyMutex(cmdreply[i].mutex);
			SDL_DestroyCond(cmdreply[i].cond);
			cmdreply[i].mutex = NULL;
			cmdreply[i].cond = NULL;
			cmdreply[i].waiting = FALSE;
			cmdreply[i].value = -1;
		}
	}
}
