/******************************************************************************
 *
 *    handler.c
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
#include "nio.h"
#include "nio_events.h"
#include "msg_lib.h"
#include "user_event.h"
#include "event_lib.h"
#include "movie_lib.h"

extern int init_screen(int sw, int sh, int options);
extern void handle_key_event(SDL_KeyboardEvent * key);

static int nio_activation_event_control_enable = TRUE;
static int nio_key_event_control_enable = TRUE;
static int nio_mouse_event_control_enable = TRUE;
static int nio_joystick_event_control_enable = TRUE;

PUBLIC void handle_events(void)
{
    SDL_Event event;
    int event_num;
    int got_one = FALSE;

    printf("handle_events(): entering...\n");

    while (1) {

	got_one = FALSE;

	while (SDL_PollEvent(&event)) {

	    got_one = TRUE;

	    switch (event.type) {
	    case SDL_ACTIVEEVENT:
//                              printf("SDL_ACTIVEEVENT\n");
		if (nio_activation_event_control_enable) {
		    msg_set_num(NIO_IN_EVENT);
		    msg_pack_int8(event.active.type);	// Uint 8
		    msg_pack_int8(event.active.gain);	// Uint 8
		    msg_pack_int8(event.active.state);	// Uint 8
		}
		break;

	    case SDL_KEYDOWN:
	    case SDL_KEYUP:
		if (nio_key_event_control_enable) {
		    msg_set_num(NIO_IN_EVENT);
		    msg_pack_int8(event.key.type);	// Uint8
		    msg_pack_int8(event.key.state);	// Uint8
		    msg_pack_int8(event.key.keysym.scancode);	// Uint8
		    msg_pack_int32((Uint32) event.key.keysym.sym);	// Uint32
		    msg_pack_int32((Uint32) event.key.keysym.mod);	// Uint32
		    msg_pack_int16(event.key.keysym.unicode);	// Uint16
		}
		break;

	    case SDL_MOUSEMOTION:
		if (nio_mouse_event_control_enable) {
		    msg_set_num(NIO_IN_EVENT);
		    msg_pack_int8(event.motion.type);	// Uint8 
		    msg_pack_int8(event.motion.state);	// Uint8 
		    msg_pack_int16(event.motion.x);	// Uint16
		    msg_pack_int16(event.motion.y);	// Uint16
		    msg_pack_int16(event.motion.xrel);	// Sint16
		    msg_pack_int16(event.motion.yrel);	// Sint16
		}
		break;

	    case SDL_MOUSEBUTTONDOWN:
	    case SDL_MOUSEBUTTONUP:
		if (nio_mouse_event_control_enable) {
		    msg_set_num(NIO_IN_EVENT);
		    msg_pack_int8(event.button.type);	// Uint8
		    msg_pack_int8(event.button.button);	// Uint8 
		    msg_pack_int8(event.button.state);	// Uint8 
		    msg_pack_int16(event.button.x);	// Uint16 
		    msg_pack_int16(event.button.y);	// Uint16 
		}
		break;

	    case SDL_JOYAXISMOTION:
		if (nio_joystick_event_control_enable) {
		    msg_set_num(NIO_IN_EVENT);
		    msg_pack_int8(event.jaxis.type);	// Uint8 
		    msg_pack_int8(event.jaxis.which);	// Uint8 
		    msg_pack_int8(event.jaxis.axis);	// Uint8 
		    msg_pack_int16(event.jaxis.value);	// Sint16
		}
		break;

	    case SDL_JOYBALLMOTION:
		if (nio_joystick_event_control_enable) {
		    msg_set_num(NIO_IN_EVENT);
		    msg_pack_int8(event.jball.type);	// Uint8  
		    msg_pack_int8(event.jball.which);	// Uint8  
		    msg_pack_int8(event.jball.ball);	// Uint8  
		    msg_pack_int16(event.jball.xrel);	// Sint16 
		    msg_pack_int16(event.jball.yrel);	// Sint16 
		}
		break;

	    case SDL_JOYHATMOTION:
		if (nio_joystick_event_control_enable) {
		    msg_set_num(NIO_IN_EVENT);
		    msg_pack_int8(event.jhat.type);	// Uint8 
		    msg_pack_int8(event.jhat.which);	// Uint8 
		    msg_pack_int8(event.jhat.hat);	// Uint8 
		    msg_pack_int8(event.jhat.value);	// Uint8 
		}
		break;

	    case SDL_JOYBUTTONDOWN:
	    case SDL_JOYBUTTONUP:
		if (nio_joystick_event_control_enable) {
		    msg_set_num(NIO_IN_EVENT);
		    msg_pack_int8(event.jbutton.type);	// Uint8 
		    msg_pack_int8(event.jbutton.which);	// Uint8 
		    msg_pack_int8(event.jbutton.button);	// Uint8 
		    msg_pack_int8(event.jbutton.state);	// Uint8 
		}
		break;

	    case SDL_QUIT:
		printf("SDL_QUIT\n");
		msg_set_num(NIO_IN_EVENT);
		msg_pack_int8(event.quit.type);	// Uint8  
		msg_send();
		movie_quit_event(event.user.data1);
		return;
		break;

	    case SDL_VIDEORESIZE:
		printf("SDL_VIDEORESIZE\n");
		init_screen(event.resize.w, event.resize.h,
			    SDL_ANYFORMAT | SDL_RESIZABLE);
#if 0
		msg_set_num(NIO_IN_EVENT);
		msg_pack_int8(event.resize.type);	// Uint8  
		msg_pack_int32(event.resize.w);	// Uint32 
		msg_pack_int32(event.resize.h);	// Uint32 
#endif
		break;

	    case SDL_USEREVENT:
		printf("SDL_USEREVENT\n");
		event_num = event.user.code;
		switch (event_num) {
		case NIO_EVENT_RESIZE:
		    printf("NIO_EVENT_RESIZE\n");
		    event_resize();
		    break;
		case NIO_EVENT_MOUSE_CURSOR:
		    mouse_cursor();
		    break;
		case NIO_EVENT_EXIT:
		    // turn mouse cursor on
		    setup_mouse_cursor_event(TRUE);
		    mouse_cursor();
		    printf("handle_events(): NIO_EVENT_EXIT\n");
		    return;
		    break;
		case NIO_ACTIVATION_EVENT_CONTROL:
		    nio_activation_event_control_enable
			= (int) event.user.data1;
		    break;
		case NIO_KEY_EVENT_CONTROL:
		    nio_key_event_control_enable = (int) event.user.data1;
		    break;
		case NIO_MOUSE_EVENT_CONTROL:
		    nio_mouse_event_control_enable =
			(int) event.user.data1;
		    break;
		case NIO_JOYSTICK_EVENT_CONTROL:
		    nio_joystick_event_control_enable =
			(int) event.user.data1;
		    break;
		default:
		    msg_set_num(NIO_IN_EVENT);
		    if (event.user.code == NIO_FILE_XFER_STATUS)
			printf
			    ("sending file status of %d\n",
			     (int) event.user.data1);
		    if (event.user.code == NIO_FILE_XFER_END)
			printf("sending file end\n");
		    msg_pack_int8(event.user.type);	// Uint8  
		    msg_pack_int32((Uint32) event.user.code);	// Uint32 
		    msg_pack_int32((Uint32) event.user.data1);	// Uint32 
		    msg_pack_int32((Uint32) event.user.data2);	// Uint32 
		    break;
		}
		break;
	    case MOVIE_ALLOC_EVENT:
		got_one = FALSE;
		movie_alloc_event(event.user.data1);
		break;
	    case MOVIE_REFRESH_EVENT:
		got_one = FALSE;
		movie_refresh_event(event.user.data1);
		break;
	    case MOVIE_QUIT_EVENT:
		got_one = FALSE;
		movie_quit_event(event.user.data1);
		break;
	    }
	}

	if (got_one) {
	    msg_send();
	}

	if (SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, SDL_ALLEVENTS)
	    == 0) {
	    SDL_Delay(1);
	}
    }
}

void reset_event_control()
{
    nio_activation_event_control_enable = TRUE;
    nio_key_event_control_enable = TRUE;
    nio_mouse_event_control_enable = TRUE;
    nio_joystick_event_control_enable = TRUE;
}
