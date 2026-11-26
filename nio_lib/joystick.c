/******************************************************************************
 *
 *    joystick.c
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
#include "joystick.h"

/* These are static for our mouse handling code */
static Sint16 NIO_Joy[MAX_JOYSTICKS][MAX_JOYSTICK_AXES] = { {0} };
static Sint16 NIO_JoyBallXRel[MAX_JOYSTICKS][MAX_JOYSTICK_DEVICES] =
    { {0} };
static Sint16 NIO_JoyBallYRel[MAX_JOYSTICKS][MAX_JOYSTICK_DEVICES] =
    { {0} };
static Uint8 NIO_JoyHatState[MAX_JOYSTICKS][MAX_JOYSTICK_DEVICES] =
    { {0} };
static Uint8 NIO_JoyButtonState[MAX_JOYSTICKS] = { 0 };

void nio_GetRelativeJoyBallState(int which, int ball, int *x, int *y)
{
	if (x)
		*x = NIO_JoyBallXRel[which][ball];
	if (y)
		*y = NIO_JoyBallYRel[which][ball];
	NIO_JoyBallXRel[which][ball] = 0;
	NIO_JoyBallYRel[which][ball] = 0;
}


Uint8 nio_GetJoyStickState(int which, int *x, int *y, int *z)
{
	if (x) {
		*x = NIO_Joy[which][0];
	}
	if (y) {
		*y = NIO_Joy[which][1];
	}
	if (z) {
		*z = NIO_Joy[which][2];
	}
	return NIO_JoyButtonState[which];
}

Uint8 nio_GetJoyHatState(int which, int hat, Uint8 * left, Uint8 * right)
{
	if (left) {
		*left = NIO_JoyHatState[which][0];
	}
	if (right) {
		*right = NIO_JoyHatState[which][1];
	}
	return NIO_JoyHatState[which][hat];
}

void handle_joy_move(SDL_Event * event)
{
	if (event->type == SDL_JOYAXISMOTION) {
		NIO_Joy[event->jaxis.which][event->jaxis.axis] =
		    event->jaxis.value;
	}
}

void handle_joyball_move(SDL_Event * event)
{
	if (event->type == SDL_JOYBALLMOTION) {
		NIO_JoyBallXRel[event->jball.which][event->jball.ball] +=
		    event->jball.xrel;
		NIO_JoyBallYRel[event->jball.which][event->jball.ball] +=
		    event->jball.yrel;
	}
}

void handle_joyhat_move(SDL_Event * event)
{
	if (event->type == SDL_JOYHATMOTION) {
		NIO_JoyHatState[event->jhat.which][event->jhat.hat] =
		    event->jhat.value;
	}
}

void handle_joy_button(SDL_Event * event)
{
	Uint8 buttonstate;
	if (event->type == SDL_JOYBUTTONDOWN
	    || event->type == SDL_JOYBUTTONUP) {
		/* Figure out which event to perform */
		buttonstate = NIO_JoyButtonState[event->jbutton.which];
		switch (event->type) {
		case SDL_JOYBUTTONDOWN:
			buttonstate |= SDL_BUTTON(event->jbutton.button);
			break;
		case SDL_JOYBUTTONUP:
			buttonstate &= ~SDL_BUTTON(event->jbutton.button);
			break;
		default:
			/* Invalid state -- bail */
			return;
		}
		/* Update internal mouse state */
		NIO_JoyButtonState[event->jbutton.which] = buttonstate;
	}
	return;
}
