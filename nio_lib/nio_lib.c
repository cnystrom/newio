/******************************************************************************
 *
 *    nio_lib.c
 *
 *    Copyright (C) 2002, 2005, 2007  Chris Nystrom
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
 *    E-Mail: cnystrom@newio.org
 *
 *    Soli Deo Gloria
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdarg.h>
#include <time.h>

#ifdef UNIX
#include <sys/param.h>
#include <unistd.h>
#endif

#ifdef WIN32
#include <winsock2.h>
#include "win32_lib.h"
#endif

#include "nio.h"
#include "ascii_codes.h"
#include "nio_log.h"
#include "file_io_lib.h"
#include "str_lib.h"
#include "msg_lib.h"
#include "keyboard.h"
#include "joystick.h"
#include "event.h"
#include "mouse.h"
#include "colors.h"
#include "nio_lib.h"
#include "font.h"
#include "term.h"

#define SYSTEM_BUFFER    (24*80*10)	// 10 Terminals full enough?

#ifndef BUFSIZ
#define BUFSIZ (8192)
#endif

#ifndef STDIN
#define STDIN  (0)
#endif				/*  */

#ifndef STDOUT
#define STDOUT  (1)
#endif				/*  */

PRIVATE int done = FALSE;

PRIVATE int font_num = 0;
PRIVATE int sound_num = 0;
PRIVATE int image_num = 0;
PRIVATE int music_num = 0;

PRIVATE void load_resource(const char *filename);

// Control Functions

#ifdef UNIX
PRIVATE void sig_usr(int signo)
{
	if (signo == SIGUSR1) {
		nio_log_print("received SIGUSR1\n");

		msg_stop_server();
//              msg_kill_server();
		nio_StopEventQueue();
		nio_log_print("calling nio_log_close()...\n");
		nio_log_close();
		exit(0);
	}
}
#endif

#define NIO_DIR  "/.nio/"

void nio_app_init(const char *app_name, const char *app_ver)
{
	char nio_ver[8] = NIO_LIB_VER;
	char hostname[MAXHOSTNAMELEN];
	char cwd[256];
	char s[BUFSIZ];
//      path nio_log;

	/*
	   get_home_dir(nio_log);    // Get home dir
	   pathcat(nio_log, NIO_DIR);   // append nio dir
	   check_dir(nio_log);    // make sure we can write to it

	   // create log file name
	 */

	snprintf(s, BUFSIZ, "%s.%s.log", app_name, app_ver);

	nio_log_open(s);

	/*
	   // append log file name to path
	   pathcat(nio_log, s);

	   // open the log file
	   nio_log_open(nio_log);
	 */

#ifdef UNIX
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
		nio_log_print("can't catch SIGUSR1\n");
#endif

//      nio_log_print("nio_app_init(): log file |%s| opened.\n", nio_log);
	nio_log_print("nio_app_init(): log file |%s| opened.\n", s);

#ifdef WIN32
	init_winsock();
#endif

	nio_StartEventQueue();

	nio_log_print("nio_app_init(): Event queue started.\n", s);

	msg_init_server(STDIN, STDOUT);

	nio_log_print("nio_app_init(): msg_init_stdio_server() done.\n");

	gethostname(hostname, MAXHOSTNAMELEN);

	getcwd(cwd, 256);

	msg_set_num(NIO_OUT_INIT);

	nio_log_print("nio_app_init(): msg_set_num() done.\n");

	msg_pack_string(nio_ver);
	msg_pack_string(hostname);
	msg_pack_string(app_name);
	msg_pack_string(app_ver);
	msg_pack_string(cwd);
//      msg_send();

	nio_log_print("nio_app_init(): Done packing message.\n");

	randomize();
}

void nio_exit(void)
{
	nio_log_print("nio_exit()\n");

	msg_set_num(NIO_OUT_EXIT);
	msg_send();

	nio_log_print("nio_exit(): msg_stop_server() called.\n");

	msg_stop_server();

//      nio_log_print("msg_kill_server() called.\n");
//      msg_kill_server();

	done = TRUE;

	nio_StopEventQueue();

	nio_log_print("nio_exit(): calling nio_log_close()...\n");

	nio_log_close();
	exit(0);
}

void nio_send(void)
{
	nio_log_print("nio_send()\n");

	msg_send();
}

// stdio Functions

void nio_char_to_stdout(int c)
{
	msg_set_num(NIO_OUT_CHAR_TO_STDOUT);
	msg_pack_int32(c);
	msg_send();
}

void nio_string_to_stdout(const char *s)
{
	msg_set_num(NIO_OUT_STRING_TO_STDOUT);
	msg_pack_string(s);
	msg_send();
}

void nio_int_to_stdout(int i)
{
	msg_set_num(NIO_OUT_INT_TO_STDOUT);
	msg_pack_int32(i);
	msg_send();
}

void nio_printf_to_stdout(char *format, ...)
{
	nio_string s;
	va_list ap;

	va_start(ap, format);
	vsnprintf(s, MAX_STR_LEN, format, ap);
	va_end(ap);

	nio_string_to_stdout(s);
}

void nio_put_char(int c)
{
	term_put_char(c);
}

void nio_paint(void)
{
	nio_log_print("nio_paint()\n");

	msg_set_num(NIO_OUT_PAINT);
	msg_send();
}

void nio_print(const char *s)
{
	nio_log_print("nio_print()\n");

	nio_log_print("nio_print(): s = |%s|\n", s);

	_nio_print(s);
}

void nio_printf(char *format, ...)
{
	nio_string s;
	va_list ap;

	va_start(ap, format);
	vsnprintf(s, MAX_STR_LEN, format, ap);
	va_end(ap);

	nio_print(s);
}

void nio_print_at(int x, int y, const char *s)
{
	_nio_print_at(x, y, s);
}

void nio_printf_at(int x, int y, char *format, ...)
{
	nio_string s;
	va_list ap;

	va_start(ap, format);
	vsnprintf(s, MAX_STR_LEN, format, ap);
	va_end(ap);

	nio_print_at(x, y, s);
}



/*
void nio_system_local(const char *s)
{
	msg_set_num(NIO_OUT_SYSTEM_LOCAL);
	msg_pack_string(s);
//      msg_send();
}
*/

#define STR_LEN  (512)
#define COMMAND_LEN (SYSTEM_BUFFER + 64)

void nio_system_remote(const char *s)
{
	int fd, n;
	char s2[COMMAND_LEN];

	char file_name[STR_LEN];

#ifdef UNIX
	strlcpy(file_name, "/var/tmp/nioXXXXXX", STR_LEN);
#else
	strlcpy(file_name, "c:/cygwin/var/tmp/nioXXXXXX", STR_LEN);
#endif

	mkstemp(file_name);
	strlcpy(s2, s, COMMAND_LEN);

	strlcat(s2, " > ", COMMAND_LEN);

	strlcat(s2, file_name, COMMAND_LEN);

	nio_log_print("s2 = |%s|\n", s2);

	// run command sending output to tmp file
	system(s2);

	// reset buffer
	s2[0] = 0x00;

	fd = open(file_name, O_RDONLY, 0);

	// read file into buffer
	n = read(fd, &s2, SYSTEM_BUFFER);

	// close file
	close(fd);

	// terminate buffer
	s2[n] = 0x00;

	// print it out via nio
	nio_print(s2);

	// remote tmp file
	remove(file_name);
}

// Color Functions

color nio_get_color(const char *s)
{
	nio_log_print("nio_get_color()\n");

	return (get_color(s));
}

color nio_get_color_rgb(int red, int green, int blue)
{
	color c;

	c.r = red;
	c.g = green;
	c.b = blue;

	return (c);
}

color nio_get_rand_color(void)
{
	return (get_rand_color());
}

int nio_color_equal(color c1, color c2)
{
	if (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b) {
		return (TRUE);
	} else {
		return (FALSE);
	}
}

// Font Functions

int
nio_load_font(const char *filename, int point_size, int style,
	      color fg, color bg)
{
	load_resource(filename);

	msg_set_num(NIO_OUT_LOAD_FONT);
	msg_pack_string(filename);
	msg_pack_int32(point_size);
	msg_pack_int32(style);
	msg_pack_int32(fg.r);
	msg_pack_int32(fg.g);
	msg_pack_int32(fg.b);
	msg_pack_int32(bg.r);
	msg_pack_int32(bg.g);
	msg_pack_int32(bg.b);
	msg_pack_int32(font_num);
//      msg_send();

	load_glyph_metrics(filename, point_size, style, font_num);
	return (font_num++);
}

int
nio_load_sys_font(int system_font, int point_size, int style,
		  color fg, color bg)
{
	nio_log_print("nio_load_sys_font()\n");

	msg_set_num(NIO_OUT_LOAD_SYS_FONT);
	msg_pack_int32(system_font);
	msg_pack_int32(point_size);
	msg_pack_int32(style);
	msg_pack_int32(fg.r);
	msg_pack_int32(fg.g);
	msg_pack_int32(fg.b);
	msg_pack_int32(bg.r);
	msg_pack_int32(bg.g);
	msg_pack_int32(bg.b);
	msg_pack_int32(font_num);

	load_system_glyph_metrics(system_font, point_size, style,
				  font_num);
	return (font_num++);
}

void nio_free_font(int i)
{
	nio_log_print("nio_free_font()\n");

	msg_set_num(NIO_OUT_FREE_FONT);
	msg_pack_int32(i);
}

void nio_draw_text(int font_num, int x, int y, const char *s)
{
	msg_set_num(NIO_OUT_DRAW_TEXT);
	msg_pack_int32(font_num);
	msg_pack_int32(x);
	msg_pack_int32(y);
	msg_pack_string(s);
}

void nio_draw_textf(int font_num, int x, int y, char *format, ...)
{
	nio_string s;
	va_list ap;

	va_start(ap, format);
	vsnprintf(s, MAX_STR_LEN, format, ap);
	va_end(ap);

	nio_draw_text(font_num, x, y, s);
}

// Screen Functions

nio_point nio_get_screen_size(void)
{
	nio_point p;

	p.x = 640;
	p.y = 480;

	return (p);
}

void nio_set_screen(int x, int y, color bg)
{
	nio_log_print("nio_set_screen()\n");

	msg_set_num(NIO_OUT_SET_SCREEN);
	msg_pack_int32(x);
	msg_pack_int32(y);
	msg_pack_int32(bg.r);
	msg_pack_int32(bg.g);
	msg_pack_int32(bg.b);
}

void nio_clear_screen(color bg)
{
	msg_set_num(NIO_OUT_CLEAR_SCREEN);
	msg_pack_int32(bg.r);
	msg_pack_int32(bg.g);
	msg_pack_int32(bg.b);
}

// Drawing Functions

void nio_draw_rectangle(int x, int y, int width, int height,
			const char *col, int alpha, int fill)
{
	color c = get_color(col);
	nio_draw_rectangle_rgb(x, y, width, height, c, alpha, fill);
}

void nio_draw_rectangle_rgb(int x, int y, int width, int height, color c,
			    int alpha, int fill)
{
	msg_set_num(NIO_OUT_DRAW_RECTANGLE_RGB);
	msg_pack_int32(x);
	msg_pack_int32(y);
	msg_pack_int32(width);
	msg_pack_int32(height);
	msg_pack_int32(c.r);
	msg_pack_int32(c.g);
	msg_pack_int32(c.b);
	msg_pack_int32(alpha);
	msg_pack_int32(fill);
}

void nio_draw_rectangle_rand(int x, int y, int width, int height,
			     int alpha, int fill)
{
	color c = get_rand_color();
	nio_draw_rectangle_rgb(x, y, width, height, c, alpha, fill);
}

void nio_draw_point(int x, int y, const char *col)
{
	color c = get_color(col);
	nio_draw_point_rgb(x, y, c);
}

void nio_draw_point_rgb(int x, int y, color c)
{
	msg_set_num(NIO_OUT_DRAW_POINT_RGB);
	msg_pack_int32(x);
	msg_pack_int32(y);
	msg_pack_int32(c.r);
	msg_pack_int32(c.g);
	msg_pack_int32(c.b);
}

void nio_draw_point_rand(int x, int y)
{
	color c = get_rand_color();
	nio_draw_point_rgb(x, y, c);
}

void nio_draw_line(int x1, int y1, int x2, int y2, const char *col,
		   int alpha)
{
	color c = get_color(col);
	nio_draw_line_rgb(x1, y1, x2, y2, c, alpha);
}

void nio_draw_line_rgb(int x1, int y1, int x2, int y2, color c, int alpha)
{
	msg_set_num(NIO_OUT_DRAW_LINE_RGB);
	msg_pack_int32(x1);
	msg_pack_int32(y1);
	msg_pack_int32(x2);
	msg_pack_int32(y2);
	msg_pack_int32(c.r);
	msg_pack_int32(c.g);
	msg_pack_int32(c.b);
	msg_pack_int32(alpha);
}

void nio_draw_line_rand(int x1, int y1, int x2, int y2, int alpha)
{
	color c = get_rand_color();
	nio_draw_line_rgb(x1, y1, x2, y2, c, alpha);
}

void nio_draw_arc(int x, int y, int radius, const char *col, int alpha,
		  int fill)
{
	color c = get_color(col);
	nio_draw_arc_rgb(x, y, radius, c, alpha, fill);
}

void nio_draw_arc_rgb(int x, int y, int radius, color c, int alpha,
		      int fill)
{
	msg_set_num(NIO_OUT_DRAW_ARC_RGB);
	msg_pack_int32(x);
	msg_pack_int32(y);
	msg_pack_int32(radius);
	msg_pack_int32(c.r);
	msg_pack_int32(c.g);
	msg_pack_int32(c.b);
	msg_pack_int32(alpha);
	msg_pack_int32(fill);
}

void nio_draw_arc_rand(int x, int y, int radius, int alpha, int fill)
{
	color c = get_rand_color();
	nio_draw_arc_rgb(x, y, radius, c, alpha, fill);
}

// Sound Functions

void nio_sound(int status)
{
	msg_set_num(NIO_OUT_SOUND);
	msg_pack_int32(status);	// status = 0, 1
}

void nio_beep(void)
{
	msg_set_num(NIO_OUT_BEEP);
}

int32 nio_load_music(const char *filename)
{
	load_resource(filename);

	msg_set_num(NIO_OUT_LOAD_MUSIC);
	msg_pack_string(filename);
	msg_pack_int32(music_num);

	return (music_num++);
}

void nio_play_music(int music_number, int loops)
{
	msg_set_num(NIO_OUT_PLAY_MUSIC);
	msg_pack_int32(music_number);
	msg_pack_int32(loops);
}

void nio_stop_music(int music_number)
{
	msg_set_num(NIO_OUT_STOP_MUSIC);
	msg_pack_int32(music_number);
}

int nio_music_playing(void)
{
	return (get_music_status());
}

int nio_load_sound(const char *filename)
{
	nio_log_print("nio_load_sound()\n");

	load_resource(filename);

	msg_set_num(NIO_OUT_LOAD_SOUND);
	msg_pack_string(filename);
	msg_pack_int32(sound_num);

	return (sound_num++);
}

void nio_play_sound(int sound_num, int loops)
{
	nio_log_print("nio_play_sound()\n");

	msg_set_num(NIO_OUT_PLAY_SOUND);
	msg_pack_int32(sound_num);
	msg_pack_int32(loops);
}

void nio_stop_sound(int sound_num)
{
	msg_set_num(NIO_OUT_STOP_SOUND);
	msg_pack_int32(sound_num);
}

void nio_free_sound(int sound_num)
{
	nio_log_print("nio_free_sound()\n");

	msg_set_num(NIO_OUT_FREE_SOUND);
	msg_pack_int32(sound_num);
}

// Movie Functions

void nio_load_movie(const char *filename, int x, int y)
{
	load_resource(filename);

	msg_set_num(NIO_OUT_LOAD_MOVIE);
	msg_pack_string(filename);
	msg_pack_int32(x);
	msg_pack_int32(y);
}

void nio_play_movie(void)
{
	msg_set_num(NIO_OUT_PLAY_MOVIE);
}

// Image Functions

int nio_load_image(const char *filename)
{
	int i;
	color c;

	nio_log_print("nio_load_image()\n");

	c.r = 0;
	c.g = 0;
	c.b = 0;

	i = nio_load_image_colorkey(filename, FALSE, c);

	return (i);
}

int nio_load_image_colorkey(const char *filename, int color_key, color c)
{
	load_resource(filename);

	msg_set_num(NIO_OUT_LOAD_IMAGE);
	msg_pack_string(filename);
	msg_pack_int32(color_key);
	msg_pack_int32(c.r);
	msg_pack_int32(c.g);
	msg_pack_int32(c.b);
	msg_pack_int32(image_num);

	return (image_num++);
}

void nio_draw_image(int image_num, int x, int y)
{
	nio_log_print("nio_draw_image()\n");

	msg_set_num(NIO_OUT_DRAW_IMAGE);
	msg_pack_int32(image_num);
	msg_pack_int16(x);
	msg_pack_int16(y);
}

void nio_draw_image_src(int image_num, int xsrc, int ysrc, int xsize,
			int ysize, int xdst, int ydst)
{
	msg_set_num(NIO_OUT_DRAW_IMAGE_SRC);
	msg_pack_int32(image_num);
	msg_pack_int16(xdst);
	msg_pack_int16(ydst);
	msg_pack_int16(xsrc);
	msg_pack_int16(ysrc);
	msg_pack_int16(xsize);
	msg_pack_int16(ysize);
}

void nio_free_image(int image_num)
{
	nio_log_print("nio_free_image()\n");

	msg_set_num(NIO_OUT_FREE_IMAGE);
	msg_pack_int32(image_num);
}

void nio_term_init(int font_num, color c, int x_home, int y_home,
		   int maxrow, int maxcol)
{
	nio_log_print("nio_term_init()\n");
	term_init(font_num, c, x_home, y_home, maxrow, maxcol);
}

void nio_cursor(int status)
{
	msg_set_num(NIO_OUT_CURSOR);
	msg_pack_int32(status);
}

void nio_activation_event(int32 enable)
{
	msg_set_num(NIO_OUT_ACTIVATION_EVENT_CONTROL);
	msg_pack_int32(enable);
}

void nio_keyboard_event(int32 enable)
{
	msg_set_num(NIO_OUT_KEY_EVENT_CONTROL);
	msg_pack_int32(enable);
}

void nio_mouse_event(int32 enable)
{
	msg_set_num(NIO_OUT_MOUSE_EVENT_CONTROL);
	msg_pack_int32(enable);
}

void nio_joystick_event(int32 enable)
{
	msg_set_num(NIO_OUT_JOYSTICK_EVENT_CONTROL);
	msg_pack_int32(enable);
}

void nio_antialiasing_control(int32 enable)
{
	msg_set_num(NIO_OUT_ANTIALIASING_CONTROL);
	msg_pack_int32(enable);
}

/********************************************************************/

/* Seed the randomizer with the timer */
void randomize(void)
{
	time_t timer;
	srand((unsigned) time(&timer));
}

/* Returns an integer from 0 to i */
int nio_rand_int(int i)
{
	if (i <= 0) {
#ifdef DEBUG
//    printf("Error: nio_rand_int i <= 0.\n");
#endif
		return (0);
	} else
		return ((int) (rand() % i) + .5);
}

int nio_rand_bool(void)
{
	int b;

	if (nio_rand_int(100) < 50)
		b = TRUE;
	else
		b = FALSE;

	return (b);
}

//#define SEND_STRING (0)

PUBLIC void nio_delay(int32 ms)
{
	return SDL_Delay(ms);
}

PUBLIC int nio_get_ticks(void)
{
	return SDL_GetTicks();
}

// Joystick Functions
PUBLIC void nio_get_relative_joyball_state(int which, int ball, int *x,
					   int *y)
{
	nio_GetRelativeJoyBallState(which, ball, x, y);
	return;
}

PUBLIC Uint8 nio_get_joystick_state(int which, int *x, int *y, int *z)
{
	return nio_GetJoyStickState(which, x, y, z);
}

PUBLIC Uint8 nio_get_joyhat_state(int which, int hat, Uint8 * left,
				  Uint8 * right)
{
	return nio_GetJoyHatState(which, hat, left, right);
}

// Mouse Functions
PUBLIC Uint8 nio_get_relative_mouse_state(int *x, int *y)
{
	return nio_GetRelativeMouseState(x, y);
}

PUBLIC Uint8 nio_get_mouse_state(int *x, int *y)
{
	return nio_GetMouseState(x, y);
}

mouse_state nio_mouse_state(void)
{
	mouse_state ms;

	ms = get_mouse_state();

	return (ms);
}

mouse_state nio_mouse_click(void)
{
	mouse_state ms;

	ms = get_mouse_click();

	return (ms);
}

mouse_state nio_mouse_info(void)
{
	mouse_state ms;
	int key;

	ms = get_mouse_info(&key);

	return (ms);
}

mouse_state nio_mouse_and_key_info(int *key)
{
	mouse_state ms;

	ms = get_mouse_info(key);

	return (ms);
}

// Keyboard Functions
PUBLIC int nio_get_key_mod_state(void)
{
	return nio_GetModState();
}

int nio_get_char(void)
{
	int c = NUL;

	c = get_key();

	// wait for key press
	while (NUL == c) {
		c = get_key();
		if (c == NUL)
			nio_delay(10);
	}
/*
	if (b == TRUE) {
		nio_put_char(c);
	}
*/
	return (c);
}

int nio_get_key(void)
{
	return (get_key());
}

/*
int nio_get_current_key(void)
{
	return (get_key());
}
*/

int nio_get_string(char *s, int lim)
{
	int c, i = 0;

	c = nio_get_char();

	while (lim > 0 && c != EOF && c != CR) {
		if (c == BS) {
			if (i != 0) {
				lim++;
				s[i--] = '\0';
			}
		} else {
			lim--;
			s[i++] = c;
		}
		c = nio_get_char();
	}

	s[i] = '\0';

	return i;
}

PUBLIC int nio_poll_event(SDL_Event * event)
{
	return nio_PollEvent(event);
}

PUBLIC int nio_peek_event(SDL_Event * event)
{
	return nio_PeekEvent(event);
}

void nio_pause(const char *s)
{
	nio_log_print("nio_pause()\n");

	nio_print(s);
	nio_paint();
	nio_send();
	nio_get_char();
}

void do_data_in(void)
{
	msg_num_t mn;

	if (done) {
		nio_log_print("do_data_in(): done. returning...\n");
		return;
	}

	mn = msg_get_num();

//      nio_log_print("do_data_in(): mn = %d\n", mn);

	if (mn == MSG_STOP) {
		done = 1;
		return;
	}

	while (mn > MSG_BUF_EMPTY) {

		if (NIO_IN_EVENT == mn) {
//                      nio_log_print("do_data_in(): sending to handle_event()...\n");
			handle_event();
		} else {
			nio_log_print
			    ("do_data_in(): bad function number: %d\n",
			     mn);
		}

		mn = msg_get_num();

		if (mn == MSG_STOP) {
			done = 1;
			return;
		}
	}
}

#define XFER_BUF_SIZE 12288
#define XFER_BUF_SIZE2 58368
PRIVATE void file_xfer(const char *filepath, uint32 filesize)
{
	int res;
	int fd;
	int count = 500;
	int32 totalbytes = 0;
	byte buffer[0x13000];
#ifdef WIN32
	char fnbuf[256];
#endif
	int32 xfer_size = XFER_BUF_SIZE;

	if (filesize >= 1048576)
		xfer_size = XFER_BUF_SIZE2;

	nio_log_print("waiting\n");
	while ((res = get_file_xfer_status()) == -1 && count) {
		SDL_Delay(100);
		count--;
	}
	if (res == 1 && count) {
#ifdef WIN32
		strcpy(fnbuf, "c:/cygwin");
		strcat(fnbuf, filepath);
		fd = _open(fnbuf, _O_RDONLY | _O_BINARY, _S_IREAD);
#else
		fd = open(filepath, O_RDONLY);
#endif
		nio_log_print("starting transfer filesize: %d\n", filesize);

		if (fd == -1) {
			nio_log_print("Error opening %s\n", filepath);

			return;
		}
		nio_log_print("Opened %s fd: %d\n", filepath, fd);

		do {
			res = read(fd, buffer, xfer_size);
			nio_log_print("read %d bytes\n", res);

			if (res != 0 && res != -1) {
				totalbytes += res;
				msg_set_num(NIO_SEND_FILE_CHUNK);
				msg_pack_bytes(buffer, res);
				nio_send();
			}
		} while (res != -1 && res != 0);

		reset_file_xfer_end();

		msg_set_num(NIO_CLOSE_FILE);
		nio_send();
		close(fd);

		nio_log_print("waiting end\n");
		count = 500;
		while (get_file_xfer_end() == -1 && count) {
			SDL_Delay(100);
			count--;
		}
	}
}

PRIVATE void load_resource(const char *filename)
{
	uint32 filesize;
	filesize = file_size(filename);

	reset_file_xfer_status();

	msg_set_num(NIO_LOAD_RESOURCE);
	msg_pack_string(filename);

	nio_log_print("%s size is %d\n", filename, filesize);

	msg_pack_int32(filesize);
	nio_send();

	file_xfer(filename, filesize);
}
