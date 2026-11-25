/******************************************************************************
 *
 *    keyboard.c
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

#include <SDL/SDL.h>
#include "../common/nio_types.h"
#include "../common/msg_lib/msg_lib.h"
#include "keysym.h"
#include "keyboard.h"
#include "event.h"

static Uint16 NIO_ModState = 0;

PUBLIC int keyevent_to_char(SDL_Event * e)
{
	int c;
	int mod;

	if (e->type != SDL_KEYDOWN) {
		return (0);
	}

	c = e->key.keysym.sym;

	// Do not want the modifier keys by themselves
	if (c >= NIOK_NUMLOCK && c <= NIOK_COMPOSE) {
		return (0);
	}

	mod = e->key.keysym.mod;

	if ((mod & KMOD_LSHIFT) || (mod & KMOD_RSHIFT)
	    || (mod & KMOD_CAPS)) {

		// Get upper case
		if (c >= NIOK_a && c <= NIOK_z) {
			c = c - 32;
		} else if (c == NIOK_BACKQUOTE) {
			c = '~';
		} else if (c == NIOK_1) {
			c = NIOK_EXCLAIM;
		} else if (c == NIOK_2) {
			c = NIOK_AT;
		} else if (c == NIOK_3) {
			c = NIOK_HASH;
		} else if (c == NIOK_4) {
			c = NIOK_DOLLAR;
		} else if (c == NIOK_5) {
			c = '%';
		} else if (c == NIOK_6) {
			c = NIOK_CARET;
		} else if (c == NIOK_7) {
			c = NIOK_AMPERSAND;
		} else if (c == NIOK_8) {
			c = NIOK_ASTERISK;
		} else if (c == NIOK_9) {
			c = NIOK_LEFTPAREN;
		} else if (c == NIOK_0) {
			c = NIOK_RIGHTPAREN;
		} else if (c == NIOK_MINUS) {
			c = NIOK_UNDERSCORE;
		} else if (c == NIOK_EQUALS) {
			c = NIOK_PLUS;
		} else if (c == NIOK_LEFTBRACKET) {
			c = '{';
		} else if (c == NIOK_RIGHTBRACKET) {
			c = '}';
		} else if (c == NIOK_SEMICOLON) {
			c = NIOK_COLON;
		} else if (c == NIOK_QUOTE) {
			c = NIOK_QUOTEDBL;
		} else if (c == NIOK_COMMA) {
			c = NIOK_LESS;
		} else if (c == NIOK_PERIOD) {
			c = NIOK_GREATER;
		} else if (c == NIOK_SLASH) {
			c = NIOK_QUESTION;
		} else if (c == NIOK_BACKSLASH) {
			c = '|';
		}
	}
	// control keys
	if ((mod & KMOD_LCTRL) || (mod & KMOD_RCTRL)) {
		if (c >= NIOK_a && c <= NIOK_z) {
			c = c - 96;
		}
	}
	// numeric key pad
	if (c == NIOK_KP_DIVIDE) {
		c = NIOK_SLASH;
	} else if (c == NIOK_KP_MULTIPLY) {
		c = NIOK_ASTERISK;
	} else if (c == NIOK_KP_MINUS) {
		c = NIOK_MINUS;
	} else if (c == NIOK_KP_PLUS) {
		c = NIOK_PLUS;
	} else if (c == NIOK_KP_ENTER) {
		c = NIOK_RETURN;
	}

	if (mod & KMOD_NUM) {
		if (c == NIOK_KP0) {
			c = NIOK_0;
		} else if (c == NIOK_KP1) {
			c = NIOK_1;
		} else if (c == NIOK_KP2) {
			c = NIOK_2;
		} else if (c == NIOK_KP3) {
			c = NIOK_3;
		} else if (c == NIOK_KP4) {
			c = NIOK_4;
		} else if (c == NIOK_KP5) {
			c = NIOK_5;
		} else if (c == NIOK_KP6) {
			c = NIOK_6;
		} else if (c == NIOK_KP7) {
			c = NIOK_7;
		} else if (c == NIOK_KP8) {
			c = NIOK_8;
		} else if (c == NIOK_KP9) {
			c = NIOK_9;
		} else if (c == NIOK_KP_PERIOD) {
			c = NIOK_PERIOD;
		}
	} else {
		if (c == NIOK_KP0) {
			c = NIOK_INSERT;
		} else if (c == NIOK_KP1) {
			c = NIOK_END;
		} else if (c == NIOK_KP2) {
			c = NIOK_DOWN;
		} else if (c == NIOK_KP3) {
			c = NIOK_PAGEDOWN;
		} else if (c == NIOK_KP4) {
			c = NIOK_LEFT;
		} else if (c == NIOK_KP5) {
			c = 0;
		} else if (c == NIOK_KP6) {
			c = NIOK_RIGHT;
		} else if (c == NIOK_KP7) {
			c = NIOK_HOME;
		} else if (c == NIOK_KP8) {
			c = NIOK_UP;
		} else if (c == NIOK_KP9) {
			c = NIOK_PAGEUP;
		} else if (c == NIOK_KP_PERIOD) {
			c = NIOK_DELETE;
		}
	}

	return (c);
}

void handle_key_press(SDL_Event * event)
{
	Uint16 modstate;

	if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP) {
		modstate = (Uint16) NIO_ModState;
		if (event->type == SDL_KEYDOWN) {
			switch (event->key.keysym.sym) {
			case SDLK_UNKNOWN:
				break;
			case SDLK_NUMLOCK:
				modstate ^= KMOD_NUM;
				break;
			case SDLK_CAPSLOCK:
				modstate ^= KMOD_CAPS;
				break;
			case SDLK_LCTRL:
				modstate |= KMOD_LCTRL;
				break;
			case SDLK_RCTRL:
				modstate |= KMOD_RCTRL;
				break;
			case SDLK_LSHIFT:
				modstate |= KMOD_LSHIFT;
				break;
			case SDLK_RSHIFT:
				modstate |= KMOD_RSHIFT;
				break;
			case SDLK_LALT:
				modstate |= KMOD_LALT;
				break;
			case SDLK_RALT:
				modstate |= KMOD_RALT;
				break;
			case SDLK_LMETA:
				modstate |= KMOD_LMETA;
				break;
			case SDLK_RMETA:
				modstate |= KMOD_RMETA;
				break;
			case SDLK_MODE:
				modstate |= KMOD_MODE;
				break;
			default:
				break;
			}
		} else {
			switch (event->key.keysym.sym) {
			case SDLK_UNKNOWN:
				break;
			case SDLK_NUMLOCK:
			case SDLK_CAPSLOCK:
				/* Only send keydown events */
				return;
			case SDLK_LCTRL:
				modstate &= ~KMOD_LCTRL;
				break;
			case SDLK_RCTRL:
				modstate &= ~KMOD_RCTRL;
				break;
			case SDLK_LSHIFT:
				modstate &= ~KMOD_LSHIFT;
				break;
			case SDLK_RSHIFT:
				modstate &= ~KMOD_RSHIFT;
				break;
			case SDLK_LALT:
				modstate &= ~KMOD_LALT;
				break;
			case SDLK_RALT:
				modstate &= ~KMOD_RALT;
				break;
			case SDLK_LMETA:
				modstate &= ~KMOD_LMETA;
				break;
			case SDLK_RMETA:
				modstate &= ~KMOD_RMETA;
				break;
			case SDLK_MODE:
				modstate &= ~KMOD_MODE;
				break;
			default:
				break;
			}
		}
		NIO_ModState = (SDLMod) modstate;
	}
}

SDLMod nio_GetModState(void)
{
	return (NIO_ModState);
}

PUBLIC int32 get_key(void)
{
	int c = 0;
	SDL_Event event;

	if (nio_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			c = keyevent_to_char(&event);
		}
		if (event.type == SDL_QUIT) {
			c = -1;
		}

	}
	return (c);
}
