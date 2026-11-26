/******************************************************************************
 *
 *    nio_lib.c
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
 *
 *    Soli Deo Gloria
 *
 */

#ifndef _NIO_LIB_H
#define _NIO_LIB_H

#include <stdlib.h>
#include <SDL/SDL.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _NIO_TYPES_H
#include "nio_types.h"
#endif

#ifndef _MOUSE_H
#include "mouse.h"
#endif

#ifndef _NIO_COLORS_H
#include "colors.h"
#endif

#ifndef _NIO_FONT_H
#include "nio_font.h"
#endif

#ifndef _ASCII_KEY_H
#include "ascii_codes.h"
#endif

#ifndef _KEYBOARD_H
#include "keyboard.h"
#endif

#ifndef _NIO_keysym_h
#include "keysym.h"
#endif

//#include "../common/platform.h"

#define NIO_LIB_VER  "0.04"

#ifndef EOF
#define EOF  (0)
#endif

#define MAX_STR_LEN   (256)

#define MAX_ALPHA (0)
#define NO_ALPHA (255)
#define NO_FILL (0)
#define FILL (1)
#define NO_UPDATE (0)
#define UPDATE (1)

#define CURRENT_MOUSE_LOC  (-1)

// Useful typedefs 

	typedef char nio_string[MAX_STR_LEN];

	typedef struct {
		int x;
		int y;
	} nio_point;

// *********** NIO Routines **********

// Control Functions

	void nio_app_init(const char *app_name, const char *app_ver);
	void nio_exit(void);
	void nio_send(void);

// stdio Functions

	void nio_char_to_stdout(int c);
	void nio_string_to_stdout(const char *s);
	void nio_int_to_stdout(int i);
	void nio_printf_to_stdout(char *format, ...);

// I/O Functions

	int nio_get_char(void);
	int nio_get_key(void);
	int nio_get_current_key(void);	// Warning: Not buffered. May miss input.
	void nio_put_char(int c);

	int nio_get_string(char *s, int lim);

	void nio_print(const char *s);
	void nio_printf(char *format, ...);

	void nio_print_at(int x, int y, const char *s);
	void nio_printf_at(int x, int y, char *format, ...);

	void nio_input(const char *s1, char *s2, int str_len);

	void nio_pause(const char *s);

	int nio_get_key_mod_state(void);

	int nio_poll_event(SDL_Event * event);

// System Command Functions

//      void nio_system_local(const char *s);
	void nio_system_remote(const char *s);

// Color Functions

	color nio_get_color(const char *s);
	color nio_get_color_rgb(int red, int green, int blue);
	color nio_get_rand_color(void);
	int nio_color_equal(color c1, color c2);

// Font Functions

	int nio_load_font(const char *filename, int point_size, int style,
			  color fg, color bg);

	int nio_load_sys_font(int system_font, int point_size, int style,
			      color fg, color bg);

	void nio_free_font(int font_num);

// Text Functions

	void nio_draw_text(int font_num, int x, int y, const char *s);
	void nio_draw_textf(int font_num, int x, int y, char *format, ...);

// Screen functions

	nio_point nio_get_screen_size(void);
	void nio_set_screen(int x, int y, color bg);
	void nio_clear_screen(color bg);

// Drawing functions

	void nio_paint(void);
	void nio_draw_rectangle(int x, int y, int width, int height,
				const char *color, int alpha, int fill);
	void nio_draw_rectangle_rgb(int x, int y, int width, int height,
				    color c, int alpha, int fill);
	void nio_draw_rectangle_rand(int x, int y, int width, int height,
				     int alpha, int fill);

	void nio_draw_point(int x, int y, const char *color);
	void nio_draw_point_rgb(int x, int y, color c);
	void nio_draw_point_rand(int x, int y);

	void nio_draw_line(int x1, int y1, int x2, int y2,
			   const char *color, int alpha);
	void nio_draw_line_rgb(int x1, int y1, int x2, int y2, color c,
			       int alpha);
	void nio_draw_line_rand(int x1, int y1, int x2, int y2, int alpha);

	void nio_draw_arc(int x, int y, int r, const char *color,
			  int alpha, int fill);
	void nio_draw_arc_rgb(int x, int y, int r, color c, int alpha,
			      int fill);
	void nio_draw_arc_rand(int x, int y, int r, int alpha, int fill);
	void nio_antialiasing_control(int32 enable);

// Sound functions

	void nio_sound(int status);

	void nio_beep(void);

	int32 nio_load_music(const char *filename);
	void nio_play_music(int music_number, int loops);
	void nio_stop_music(int music_number);
	int nio_music_playing(void);

	int nio_load_sound(const char *filename);
	void nio_play_sound(int sound_num, int loops);
	void nio_stop_sound(int sound_num);
	void nio_free_sound(int i);

// Movie functions

	void nio_load_movie(const char *filename, int x, int y);
	void nio_play_movie(void);

// Image functions

	int nio_load_image(const char *filename);
	int nio_load_image_colorkey(const char *filename, int color_key,
				    color c);
	void nio_draw_image(int image_num, int x, int y);
	void nio_free_image(int i);

	void nio_term_init(int font_num, color c, int x_home, int y_home,
			   int maxrow, int maxcol);

	void nio_cursor(int i);

	void nio_draw_image_src(int image_num, int xsrc, int ysrc,
				int xsize, int ysize, int xdst, int ydst);

// Joystick Functions
	void nio_get_relative_joyball_state(int which, int ball, int *x,
					    int *y);
	Uint8 nio_get_joystick_state(int which, int *x, int *y, int *z);
	Uint8 nio_get_joyhat_state(int which, int hat, Uint8 * left,
				   Uint8 * right);

// Mouse Functions
	Uint8 nio_get_relative_mouse_state(int *x, int *y);
	Uint8 nio_get_mouse_state(int *x, int *y);
	mouse_state nio_mouse_state(void);
	mouse_state nio_mouse_click(void);
	mouse_state nio_mouse_info(void);
	mouse_state nio_mouse_and_key_info(int *key);

// Event Functions
	int nio_poll_event(SDL_Event * event);
	int nio_peek_event(SDL_Event * event);
	void nio_activation_event(int32 enable);
	void nio_keyboard_event(int32 enable);
	void nio_mouse_event(int32 enable);
	void nio_joystick_event(int32 enable);

//      void nio_pause(const char *s);
	int nio_get_string(char *s, int lim);

//      void nio_set_write_wait(unsigned int i);

	PUBLIC void nio_delay(int32 ms);
	PUBLIC int nio_get_ticks(void);
/*********************/
/* NIO Rand Routines */
/*********************/

#ifndef RAND_MAX
#define RAND_MAX 32767
#endif

	void randomize(void);
	int nio_rand_int(int i);
	int nio_rand_bool(void);

// Tuneable

//#define DEFAULT_WRITE_WAIT  (20000)

//      PUBLIC void nio_set_write_wait(unsigned int i);

// Key/Button States

	enum { PRESSED = 0x01, RELEASED = 0x00 };

// Sound status

	enum { ON = 0x01, OFF = 0x00 };

	void nio_start_ticks(void);
	int nio_get_ticks(void);

#ifdef __cplusplus
}
#endif
#endif				/* _NIO_LIB */
