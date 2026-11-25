/******************************************************************************
 *
 *    event.h
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
 *    Blog:   http://conversazione.blogspot.com
 *    AIM:    nystromchris
 *
 *    Soli Deo Gloria
 *
 */

#ifndef _EVENT_H
#define _EVENT_H
#include <SDL/SDL.h>

int nio_PeekEvent(SDL_Event * event);
int nio_PollEvent(SDL_Event * event);
void nio_StartEventQueue();
void nio_StopEventQueue();
void handle_event();
int get_music_status();
void handle_file_xfer_status(int flag);
void reset_file_xfer_status();
int get_file_xfer_status();
void reset_file_xfer_end();
int get_file_xfer_end();

#endif				/* _KEYBAORD_H */
