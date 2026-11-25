/******************************************************************************
 *
 *    sdl_lib.c
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
 *    Blog:   http://conversazione.blogspot.com
 *    AIM:    nystromchris
 *
 *    Soli Deo Gloria
 *
 */

#include <stdlib.h>
#include <signal.h>
#include "SDL.h"
#include "sdl_lib.h"
extern int init_screen(int sw, int sh, int options);

PRIVATE void breakhandler(int a)
{
	SDL_Quit();
	exit(1);
}

PUBLIC void sdl_init(void)
{
	if ((SDL_Init(SDL_INIT_EVERYTHING) == -1)) {
		fprintf(stderr,
			"sdl_init(): Could not initialize SDL: %s.\n",
			SDL_GetError());
		exit(-1);
	}
	atexit(SDL_Quit);
	signal(SIGTERM, breakhandler);
	signal(SIGINT, breakhandler);
	SDL_EnableUNICODE(TRUE);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,
			    SDL_DEFAULT_REPEAT_INTERVAL);
	// Check for joystick
	if (SDL_NumJoysticks() > 0) {
		// Open joystick
		if (SDL_JoystickOpen(0)) {
			SDL_JoystickEventState(SDL_ENABLE);
		}
	}
}

PUBLIC void set_window_caption(char *s)
{
	SDL_WM_SetCaption(s, s);
}

PUBLIC void delay(int ticks)
{
	SDL_Delay(ticks);
}

PUBLIC int get_ticks(void)
{
	return (SDL_GetTicks());
}
