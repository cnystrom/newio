/******************************************************************************
 *
 *    print_func.c
 *
 *    Copyright (C) 2002, 2005  Chris Nystrom
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but without any warranty whatsoever.
 *
 *    For more license information see:
 *
 *      http://www.gnu.org/copyleft/gpl.html
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

#include <stdio.h>
#include "nio.h"

void print_func(int fn)
{
	if (fn == NIO_OUT_INIT) {
		printf("nio_init()\n");
	} else if (fn == NIO_OUT_EXIT) {
		printf("nio_exit()\n");
	} else if (fn == NIO_OUT_CHAR_TO_STDOUT) {
		printf("nio_char_to_stdout()\n");
	} else if (fn == NIO_OUT_STRING_TO_STDOUT) {
		printf("nio_string_to_stdout()\n");
	} else if (fn == NIO_OUT_INT_TO_STDOUT) {
		printf("nio_int_to_stdout()\n");
//      } else if (fn == NIO_OUT_PUT_CHAR) {
//              printf("nio_put_char()\n");
//      } else if (fn == NIO_OUT_SYSTEM_LOCAL) {
//              printf("nio_system_local()\n");
	} else if (fn == NIO_OUT_LOAD_FONT) {
		printf("nio_load_font()\n");
	} else if (fn == NIO_OUT_LOAD_SYS_FONT) {
		printf("nio_load_sys_font()\n");
	} else if (fn == NIO_OUT_FREE_FONT) {
		printf("nio_free_font()\n");
	} else if (fn == NIO_OUT_DRAW_TEXT) {
		printf("nio_draw_text()\n");
	} else if (fn == NIO_OUT_SET_SCREEN) {
		printf("nio_set_screen()\n");
	} else if (fn == NIO_OUT_CLEAR_SCREEN) {
		printf("nio_clear_screen()\n");
	} else if (fn == NIO_OUT_DRAW_RECTANGLE_RGB) {
		printf("nio_draw_rectangle_rgb()\n");
	} else if (fn == NIO_OUT_DRAW_POINT_RGB) {
		printf("nio_draw_point_rgb()\n");
	} else if (fn == NIO_OUT_DRAW_LINE_RGB) {
		printf("nio_draw_line_rgb()\n");
	} else if (fn == NIO_OUT_DRAW_ARC_RGB) {
		printf("nio_draw_arc_rgb()\n");
	} else if (fn == NIO_OUT_SOUND) {
		printf("nio_sound()\n");
	} else if (fn == NIO_OUT_BEEP) {
		printf("nio_beep()\n");
	} else if (fn == NIO_OUT_LOAD_MUSIC) {
		printf("nio_load_music()\n");
	} else if (fn == NIO_OUT_PLAY_MUSIC) {
		printf("nio_play_music()\n");
	} else if (fn == NIO_OUT_STOP_MUSIC) {
		printf("nio_stop_music()\n");
	} else if (fn == NIO_OUT_LOAD_SOUND) {
		printf("nio_load_sound()\n");
	} else if (fn == NIO_OUT_PLAY_SOUND) {
		printf("nio_play_sound()\n");
	} else if (fn == NIO_OUT_FREE_SOUND) {
		printf("nio_free_sound()\n");
	} else if (fn == NIO_OUT_LOAD_IMAGE) {
		printf("nio_load_image()\n");
	} else if (fn == NIO_OUT_DRAW_IMAGE) {
		printf("nio_draw_image()\n");
	} else if (fn == NIO_OUT_FREE_IMAGE) {
		printf("nio_free_image()\n");
//      } else if (fn == NIO_OUT_TERM_INIT) {
//              printf("nio_term_init()\n");
//      } else if (fn == NIO_OUT_PRINT) {
//              printf("nio_print()\n");
//      } else if (fn == NIO_OUT_PRINT_AT) {
//              printf("nio_print_at()\n");
	} else if (fn == NIO_OUT_PAINT) {
		printf("nio_paint()\n");
	} else if (fn == NIO_OUT_LOAD_MOVIE) {
		printf("nio_out_load_movie()\n");
	} else if (fn == NIO_OUT_PLAY_MOVIE) {
		printf("nio_out_play_movie()\n");
	} else if (fn == NIO_OUT_CURSOR) {
		printf("nio_out_cursor()\n");
	} else if (fn == NIO_OUT_DRAW_IMAGE_SRC) {
		;		//printf("nio_out_draw_image_src()\n");
	} else if (fn == NIO_OUT_STOP_SOUND) {
		printf("nio_out_stop_sound()\n");
	} else if (fn == NIO_OUT_ACTIVATION_EVENT_CONTROL) {
		printf("nio_out_activation_event_control()\n");
	} else if (fn == NIO_OUT_KEY_EVENT_CONTROL) {
		printf("nio_out_key_event_control()\n");
	} else if (fn == NIO_OUT_JOYSTICK_EVENT_CONTROL) {
		printf("nio_out_joystick_event_control()\n");
	} else if (fn == NIO_OUT_MOUSE_EVENT_CONTROL) {
		printf("nio_out_mouse_event_control()\n");
	} else if (fn == NIO_SEND_FILE_CHUNK) {
		printf("nio_send_file_chunk()\n");
	} else if (fn == NIO_CLOSE_FILE) {
		printf("nio_close_file()\n");
	} else if (fn == NIO_LOAD_RESOURCE) {
		printf("nio_load_resource()\n");
	} else {
		printf("unknown function: %d\n", fn);
	}
}
