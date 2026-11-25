/******************************************************************************
 *
 *    joystick.h
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

#ifndef _JOYSTICK_H
#define _JOYSTICK_H

#define MAX_JOYSTICKS 8
#define MAX_JOYSTICK_DEVICES 4
#define MAX_JOYSTICK_AXES 3

void nio_GetRelativeJoyBallState(int which, int ball, int *x, int *y);
Uint8 nio_GetJoyStickState(int which, int *x, int *y, int *z);
Uint8 nio_GetJoyHatState(int which, int hat, Uint8 * left, Uint8 * right);

void handle_joy_move(SDL_Event * event);
void handle_joyball_move(SDL_Event * event);
void handle_joyhat_move(SDL_Event * event);
void handle_joy_button(SDL_Event * event);
#endif
