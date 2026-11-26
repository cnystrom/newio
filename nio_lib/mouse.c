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

# include <SDL/SDL.h>
#include "../common/nio_types.h"
#include "../common/msg_lib/msg_lib.h"
#include "mouse.h"
#include "event.h"

#ifndef ESC
#define ESC  (27)
#endif

/* These are static for our mouse handling code */
static Sint16 NIO_MouseX = 0;
static Sint16 NIO_MouseY = 0;
static Sint16 NIO_DeltaX = 0;
static Sint16 NIO_DeltaY = 0;
static Uint8 NIO_ButtonState = 0;

PUBLIC void handle_mouse_button(SDL_Event * event)
{
	Uint8 buttonstate;
	if (event->type == SDL_MOUSEBUTTONDOWN
	    || event->type == SDL_MOUSEBUTTONUP) {
		/* Figure out which event to perform */
		buttonstate = NIO_ButtonState;
		switch (event->type) {
		case SDL_MOUSEBUTTONDOWN:
			buttonstate |= SDL_BUTTON(event->button.button);
			NIO_MouseX = event->button.x;
			NIO_MouseY = event->button.y;
			break;
		case SDL_MOUSEBUTTONUP:
			buttonstate &= ~SDL_BUTTON(event->button.button);
			NIO_MouseX = event->button.x;
			NIO_MouseY = event->button.y;
			break;
		default:
			/* Invalid state -- bail */
			return;
		}
		/* Update internal mouse state */
		NIO_ButtonState = buttonstate;
//      wlog("HANDLE MOUSE %x %x %x (%x)\n",NIO_MouseX,NIO_MouseY,NIO_ButtonState,event->button.button);
	}
	return;
}

PUBLIC void handle_mouse_move(SDL_Event * event)
{
	if (event->type == SDL_MOUSEMOTION) {
		NIO_ButtonState = event->motion.state;
		NIO_MouseX = event->motion.x;
		NIO_MouseY = event->motion.y;
		NIO_DeltaX += event->motion.xrel;
		NIO_DeltaY += event->motion.yrel;
	}
}

Uint8 nio_GetRelativeMouseState(int *x, int *y)
{
	if (x)
		*x = NIO_DeltaX;
	if (y)
		*y = NIO_DeltaY;
	NIO_DeltaX = 0;
	NIO_DeltaY = 0;
	return (NIO_ButtonState);
}


Uint8 nio_GetMouseState(int *x, int *y)
{
	if (x) {
		*x = NIO_MouseX;
	}
	if (y) {
		*y = NIO_MouseY;
	}
	return (NIO_ButtonState);
}


mouse_state get_mouse_state(void)
{
	mouse_state ms;

	int32 button = nio_GetMouseState(&ms.x, &ms.y);

	ms.b1 =
	    (SDL_BUTTON(SDL_BUTTON_LEFT) & button) ==
	    SDL_BUTTON(SDL_BUTTON_LEFT);
	ms.b2 =
	    (SDL_BUTTON(SDL_BUTTON_MIDDLE) & button) ==
	    SDL_BUTTON(SDL_BUTTON_MIDDLE);
	ms.b3 =
	    (SDL_BUTTON(SDL_BUTTON_RIGHT) & button) ==
	    SDL_BUTTON(SDL_BUTTON_RIGHT);

//      wlog("get_mouse_state %x %x %x\n",NIO_MouseX,NIO_MouseY,NIO_ButtonState);

	return (ms);
}

mouse_state get_mouse_click(void)
{
	int key;
	return get_mouse_info(&key);
}


mouse_state get_mouse_info(int *key)
{
	mouse_state ms;
	SDL_Event event;

	ms.b1 = 0;
	ms.b2 = 0;
	ms.b3 = 0;
	ms.x = 0;
	ms.y = 0;
	*key = 0;
	if (nio_PollEvent(&event)) {
		switch (event.type) {
		case SDL_MOUSEBUTTONDOWN:
//                      wlog("DOWN event.button.button: %x\n",event.button.button);
			if (SDL_BUTTON_LEFT == event.button.button)
				ms.b1 = 1;
			if (SDL_BUTTON_MIDDLE == event.button.button)
				ms.b2 = 1;
			if (SDL_BUTTON_RIGHT == event.button.button)
				ms.b3 = 1;
			ms.x = event.button.x;
			ms.y = event.button.y;
			break;
		case SDL_MOUSEBUTTONUP:
//                      wlog("UP event.button.button: %x\n",event.button.button);
			if (SDL_BUTTON_LEFT == event.button.button)
				ms.b1 = 0;
			if (SDL_BUTTON_MIDDLE == event.button.button)
				ms.b2 = 0;
			if (SDL_BUTTON_RIGHT == event.button.button)
				ms.b3 = 0;
			ms.x = event.button.x;
			ms.y = event.button.y;
			break;
		case SDL_MOUSEMOTION:
//                      wlog("MOTION event.motion.state: %x x: %d y: %d\n",event.motion.state,event.motion.x,event.motion.y);
			ms.b1 =
			    (SDL_BUTTON(SDL_BUTTON_LEFT) & event.motion.
			     state) == SDL_BUTTON(SDL_BUTTON_LEFT);
			ms.b2 =
			    (SDL_BUTTON(SDL_BUTTON_MIDDLE) & event.motion.
			     state) == SDL_BUTTON(SDL_BUTTON_MIDDLE);
			ms.b3 =
			    (SDL_BUTTON(SDL_BUTTON_RIGHT) & event.motion.
			     state) == SDL_BUTTON(SDL_BUTTON_RIGHT);
			ms.x = event.motion.x;
			ms.y = event.motion.y;
			break;
		case SDL_KEYDOWN:
			*key = event.key.keysym.sym;
			break;
		case SDL_QUIT:
			*key = ESC;
			break;
		default:
			break;
		}
	}
	return (ms);
}
