/******************************************************************************
 *
 *    rpc.c
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
 *
 *    Soli Deo Gloria
 *
 */

#include <stdlib.h>
#include <string.h>
#include "SDL.h"
#include "msg_lib/msg_lib.h"
#include "audio_lib/audio_lib.h"
#include "event_lib/event_lib.h"
#include "event_lib/user_event.h"
//#include "term_lib/term_lib.h"
#include "color_lib/color_lib.h"
#include "font_lib/font_lib.h"
#include "screen_lib/screen_lib.h"
#include "image_lib/image_lib.h"
#include "movie_lib/movie_lib.h"
#include "file_xfr.h"
#include "done.h"
#include "nio_events.h"
#include "rpc.h"

extern PUBLIC point_t get_mouse_loc(void);

static int sound = ON;

// Control Functions

void nio_app_init_1(void)
{
	char nio_ver[STR_LEN];
	char server[STR_LEN];
	char app_name[STR_LEN];
	char app_ver[STR_LEN];
	char cwd[STR_LEN];
//  printf("Initializing remote application...\n");

	printf("here 0\n");
	msg_unpack_string(nio_ver, STR_LEN);
	msg_unpack_string(server, STR_LEN);
	msg_unpack_string(app_name, STR_LEN);
	msg_unpack_string(app_ver, STR_LEN);
	msg_unpack_string(cwd, STR_LEN);

	printf("here 1\n");

	init_file_loader(app_name, app_ver, cwd);
	printf("here 2\n");

	// turn antialiasing on
	antialiasing_control(TRUE);
	reset_event_control();
	printf("here 3\n");

	printf("nio_init_1:\n");
	printf(" nio_ver = %s\n", nio_ver);
	printf(" server = %s\n", server);
	printf(" app_name = %s\n", app_name);
	printf(" app_ver = %s\n", app_ver);
	printf(" cwd = %s\n", cwd);
}

void nio_exit_1(void)
{
	SDL_Event ev;

	printf("nio_exit(): Program terminated at server.\n");
	fflush(stdout);

	set_done(TRUE);

	ev.type = SDL_USEREVENT;
	ev.user.code = NIO_EVENT_EXIT;
	ev.user.data1 = NULL;
	ev.user.data1 = NULL;

	SDL_PushEvent(&ev);
}

// STDIO Functions

void nio_char_to_stdout_1(void)
{
	int c;

	c = msg_unpack_int32();
	putchar(c);
	fflush(stdout);
}

void nio_string_to_stdout_1(void)
{
	char s[BUF_SIZE];

	msg_unpack_string(s, BUF_SIZE);

	printf(s);
	fflush(stdout);
}

void nio_int_to_stdout_1(void)
{
	int i;

	i = msg_unpack_int32();

	printf("%d", i);
	fflush(stdout);
}

/*
void nio_put_char_1(void)
{
	int i;

	i = msg_unpack_int32();

	term_put_char(i);
}
*/

// System Command Functions

/*
void nio_system_local_1(void)
{
	char s[BUF_SIZE];

	msg_unpack_string(s, BUF_SIZE);

	system(s);
	fflush(stdout);
}
*/

// Font Functions

void nio_load_font_1(void)
{
	char fontfile[BUF_SIZE];
	int point_size;
	int style;
	int r, g, b;
	int font_num;
	int fg_color;
	int bg_color;
	int server_font_num;

	msg_unpack_string(fontfile, BUF_SIZE);
	point_size = msg_unpack_int32();
	style = msg_unpack_int32();

	r = msg_unpack_int32();
	g = msg_unpack_int32();
	b = msg_unpack_int32();
	fg_color = get_color_rgb(r, g, b);

	r = msg_unpack_int32();
	g = msg_unpack_int32();
	b = msg_unpack_int32();
	bg_color = get_color_rgb(r, g, b);

	server_font_num = msg_unpack_int32();

	font_num =
	    load_font(get_filepath(fontfile), point_size, style, fg_color,
		      bg_color);
//      printf("loadfont: %s %d\n", fontfile, font_num);
}

void nio_load_sys_font_1(void)
{
	int sys_font;
	int point_size;
	int style;
	int r, g, b;
	int font_num;
	int fg_color;
	int bg_color;
	int server_font_num;

	sys_font = msg_unpack_int32();

	point_size = msg_unpack_int32();

	style = msg_unpack_int32();

	r = msg_unpack_int32();
	g = msg_unpack_int32();
	b = msg_unpack_int32();
	fg_color = get_color_rgb(r, g, b);

	r = msg_unpack_int32();
	g = msg_unpack_int32();
	b = msg_unpack_int32();
	bg_color = get_color_rgb(r, g, b);

	server_font_num = msg_unpack_int32();

	font_num =
	    load_sys_font(sys_font, point_size, style, fg_color, bg_color);
//      printf("loadfont: %d %d\n", sys_font, font_num);
}

void nio_free_font_1(void)
{
	int font_num;

	font_num = msg_unpack_int32();
	free_font(font_num);
//      printf("freefont: %d\n", font_num);
}

void nio_draw_text_1(void)
{
	int font_num, x, y;
	char s[BUF_SIZE];
	glyphFont gf;

	font_num = msg_unpack_int32();
	x = msg_unpack_int32();
	y = msg_unpack_int32();
	msg_unpack_string(s, BUF_SIZE);

	gf = get_font(font_num);

	draw_text(&gf, s, x, y);
}

// Screen Functions

void nio_set_screen_1(void)
{
	int x, y;
	int r, g, b;
	int color;
	int ret;
	SDL_Event ev;

	x = msg_unpack_int32();
	y = msg_unpack_int32();
	r = msg_unpack_int32();
	g = msg_unpack_int32();
	b = msg_unpack_int32();

	color = get_color_rgb(r, g, b);

	setup_screen_resize_event(x, y, color);

	ev.type = SDL_USEREVENT;
	ev.user.code = NIO_EVENT_RESIZE;
	ev.user.data1 = NULL;
	ev.user.data1 = NULL;

	ret = SDL_PushEvent(&ev);

	event_busy();
}

void nio_clear_screen_1(void)
{
	int r, g, b;
	int color;

	r = msg_unpack_int32();
	g = msg_unpack_int32();
	b = msg_unpack_int32();

	color = get_color_rgb(r, g, b);

	clear_screen(color);
}

// Drawing Functions

#define CURRENT_MOUSE_LOC  (-1)

void nio_draw_rectangle_rgb_1(void)
{
	int x, y, width, height, r, g, b, color, alpha, fill;

	x = msg_unpack_int32();
	y = msg_unpack_int32();
	width = msg_unpack_int32();
	height = msg_unpack_int32();

	r = msg_unpack_int32();
	g = msg_unpack_int32();
	b = msg_unpack_int32();

	alpha = msg_unpack_int32();
	fill = msg_unpack_int32();

	if (CURRENT_MOUSE_LOC == x) {
		point_t p;

		p = get_mouse_loc();

		x = p.x;
	}

	if (CURRENT_MOUSE_LOC == y) {
		point_t p;

		p = get_mouse_loc();

		y = p.y;
	}

	color = get_color_rgb(r, g, b);

	draw_rectangle(x, y, width, height, color, alpha, fill);
}

void nio_draw_point_rgb_1(void)
{
	int x, y, r, g, b, color;

	x = msg_unpack_int32();
	y = msg_unpack_int32();

	r = msg_unpack_int32();
	g = msg_unpack_int32();
	b = msg_unpack_int32();

	color = get_color_rgb(r, g, b);

	draw_point(x, y, color);
}

void nio_draw_line_rgb_1(void)
{
	int x1, y1, x2, y2, r, g, b, color, alpha;

	x1 = msg_unpack_int32();
	y1 = msg_unpack_int32();
	x2 = msg_unpack_int32();
	y2 = msg_unpack_int32();

	r = msg_unpack_int32();
	g = msg_unpack_int32();
	b = msg_unpack_int32();

	alpha = msg_unpack_int32();

//      printf("nio_draw_line_rgb(): x1, y1, x2, y2 = %d, %d %d, %d\n", x1, y1, x2, y2);
//      printf("nio_draw_line_rgb(): r, g, b = %d, %d, %d\n", r, g, b);
//      printf("nio_draw_line_rgb(): alpha = %d\n", alpha);

	color = get_color_rgb(r, g, b);

	draw_line(x1, y1, x2, y2, color, alpha, 0);
}

void nio_draw_arc_rgb_1(void)
{
	int x, y, radius, r, g, b, color, alpha, fill;

	x = msg_unpack_int32();
	y = msg_unpack_int32();
	radius = msg_unpack_int32();

	r = msg_unpack_int32();
	g = msg_unpack_int32();
	b = msg_unpack_int32();

	alpha = msg_unpack_int32();
	fill = msg_unpack_int32();

	color = get_color_rgb(r, g, b);

	draw_arc(x, y, radius, color, alpha, fill);
}

// Sound Functions

void nio_sound_1(void)
{
	sound = msg_unpack_int32();
}

void nio_beep_1(void)
{
	if (sound) {
		putchar(7);
		printf("beep - sound\n");
	} else {
		printf("beep - no sound\n");
	}
}

void nio_load_music_1(void)
{
	char filename[BUF_SIZE];
	int server_music_num;

	msg_unpack_string(filename, BUF_SIZE);
	server_music_num = msg_unpack_int32();

	if (audio_avail()) {
		load_music(get_filepath(filename));
	}
}

void nio_play_music_1(void)
{
	int loops;
	int server_music_num;

	server_music_num = msg_unpack_int32();
	loops = msg_unpack_int32();

	if (sound) {
		play_music(loops);
	} else
		printf("Sound is off...\n");
}

void nio_stop_music_1(void)
{
	int server_music_num;

	server_music_num = msg_unpack_int32();
	stop_music();
}

/*
void nio_music_playing_1(void)
{
	int b;

	reset_buf();
	b = music_playing();
	pack_int32(b);
	msg_send();
}
*/

void nio_load_sound_1(void)
{
	int sound_num;
	char filename[BUF_SIZE];
	int server_sound_num;

	msg_unpack_string(filename, BUF_SIZE);
	server_sound_num = msg_unpack_int32();

	if (audio_avail()) {
		sound_num = load_sound(get_filepath(filename));
	} else {
		sound_num = -1;
	}
//printf("RPC_LOADSOUND %d\n",sound_num);
}

void nio_play_sound_1(void)
{
	int channel, sound_num, loops;
//printf("RPC_PLAYSOUND enter\n");

	sound_num = msg_unpack_int32();
	loops = msg_unpack_int32();

	if (!sound) {
		printf("Sound is off...\n");
		return;
	}

	if (sound_num < 0 || sound_num >= MAX_NUM_SOUNDS) {
		fprintf(stderr, "nio_play_sound_1(): bad sound num %d\n",
			sound_num);
		return;
	}
//      if (sound_playing(sound_num)) {
//              return;
//      }

	channel = play_sound(sound_num, loops);

//printf("RPC_PLAYSOUND %d\n",sound_num);
	if (channel < 0 && channel != -4) {
		fprintf(stderr,
			"nio_play_sound_1(): sound num %d failed.\n",
			sound_num);
		return;
	}
}
void nio_stop_sound_1(void)
{
	int sound_num;
	sound_num = msg_unpack_int32();
	stop_sound(sound_num);
}

void nio_free_sound_1(void)
{
	int sound_num;

	sound_num = msg_unpack_int32();
//printf("RPC_FREESOUND %d\n",sound_num);

	delete_sound(sound_num);
}

// Movie Functions

void nio_load_movie_1(void)
{
	int x, y;
	char filename[BUF_SIZE];

	msg_unpack_string(filename, BUF_SIZE);
	x = msg_unpack_int32();
	y = msg_unpack_int32();

	movie_load(get_filepath(filename));

	//movie_set_display();
}

void nio_play_movie_1(void)
{
	movie_play();
}

// Image Functions

void nio_load_image_1(void)
{
	int image_num;
	int color_key;
	int r, g, b;
	char filename[BUF_SIZE];
	int server_image_num;

	msg_unpack_string(filename, BUF_SIZE);

	color_key = msg_unpack_int32();

	r = msg_unpack_int32();
	g = msg_unpack_int32();
	b = msg_unpack_int32();

	server_image_num = msg_unpack_int32();

	image_num = load_image(get_filepath(filename), color_key, r, g, b);
}

void nio_draw_image_1(void)
{
	int i_num, x, y;

	i_num = msg_unpack_int32();
	x = msg_unpack_int16();
	y = msg_unpack_int16();

	// FIXME: not sure why mouse stuff is here...
	if (CURRENT_MOUSE_LOC == x) {
		point_t p;

		p = get_mouse_loc();

		x = p.x;
	}

	if (CURRENT_MOUSE_LOC == y) {
		point_t p;

		p = get_mouse_loc();

		y = p.y;
	}
	// end mouse stuff

	draw_image(i_num, x, y);
}

void nio_draw_image_src_1(void)
{
	int i_num, x, y, xsrc, ysrc, xsiz, ysiz;

	i_num = msg_unpack_int32();

	x = msg_unpack_int16();
	y = msg_unpack_int16();

	xsrc = msg_unpack_int16();
	ysrc = msg_unpack_int16();
	xsiz = msg_unpack_int16();
	ysiz = msg_unpack_int16();

	if (CURRENT_MOUSE_LOC == x) {
		point_t p;

		p = get_mouse_loc();

		x = p.x;
	}

	if (CURRENT_MOUSE_LOC == y) {
		point_t p;

		p = get_mouse_loc();

		y = p.y;
	}

	draw_image_src(i_num, xsrc, ysrc, xsiz, ysiz, x, y);
}

void nio_free_image_1(void)
{
	int image_num;

	image_num = msg_unpack_int32();

	free_image(image_num);
}


/*
void nio_term_init_1(void)
{
	int font_num;
	int color;
	int r, g, b;
	int x_home, y_home;
	int maxrow, maxcol;

	font_num = msg_unpack_int32();

//        printf("nio_term_init(): font_num = %d\n", font_num);

	r = msg_unpack_int32();
	g = msg_unpack_int32();
	b = msg_unpack_int32();

//        printf("nio_term_init(): r, g, b = %d, %d, %d\n", r, g, b);

	x_home = msg_unpack_int32();
	y_home = msg_unpack_int32();
	maxrow = msg_unpack_int32();
	maxcol = msg_unpack_int32();

//        printf("nio_term_init(): x_home, y_home = %d, %d\n", x_home, y_home);
//        printf("nio_term_init(): maxrow, maxcol = %d, %d\n", maxrow, maxcol);

	color = get_color_rgb(r, g, b);

	term_init(font_num, color, x_home, y_home, maxrow, maxcol);
}

void nio_print_1(void)
{
	int i, s_len;
	char s[BUF_SIZE];

	msg_unpack_string(s, BUF_SIZE);

	s_len = strlen(s);

	for (i = 0; i < s_len; i++)
		term_put_char(s[i]);
}

void nio_print_at_1(void)
{
	int i, s_len, x, y;
	char s[BUF_SIZE];

	x = msg_unpack_int32();
	y = msg_unpack_int32();
	msg_unpack_string(s, BUF_SIZE);

	term_set_location(x, y);

	s_len = strlen(s);

	for (i = 0; i < s_len; i++)
		term_put_char(s[i]);
}
*/

void nio_paint_1(void)
{
	//printf("%08d: paint\n",SDL_GetTicks());
	update_screen();
}

void nio_cursor_1(void)
{
	int status;
	SDL_Event ev;

	status = msg_unpack_int32();

	setup_mouse_cursor_event(status);

	ev.type = SDL_USEREVENT;
	ev.user.code = NIO_EVENT_MOUSE_CURSOR;
	ev.user.data1 = NULL;
	ev.user.data1 = NULL;

	SDL_PushEvent(&ev);

	event_busy();

//      mouse_cursor(status);
}

void nio_activation_event_control_1(void)
{
	int32 enable;
	SDL_Event ev;
	enable = msg_unpack_int32();

	ev.type = SDL_USEREVENT;
	ev.user.code = NIO_ACTIVATION_EVENT_CONTROL;
	ev.user.data1 = (void *) enable;
	ev.user.data2 = NULL;

	SDL_PushEvent(&ev);
}

void nio_key_event_control_1(void)
{
	int32 enable;
	SDL_Event ev;
	enable = msg_unpack_int32();

	ev.type = SDL_USEREVENT;
	ev.user.code = NIO_KEY_EVENT_CONTROL;
	ev.user.data1 = (void *) enable;
	ev.user.data2 = NULL;

	SDL_PushEvent(&ev);
}

void nio_mouse_event_control_1(void)
{
	int32 enable;
	SDL_Event ev;
	enable = msg_unpack_int32();

	ev.type = SDL_USEREVENT;
	ev.user.code = NIO_MOUSE_EVENT_CONTROL;
	ev.user.data1 = (void *) enable;
	ev.user.data2 = NULL;

	SDL_PushEvent(&ev);
}

void nio_joystick_event_control_1(void)
{
	int32 enable;
	SDL_Event ev;
	enable = msg_unpack_int32();

	ev.type = SDL_USEREVENT;
	ev.user.code = NIO_JOYSTICK_EVENT_CONTROL;
	ev.user.data1 = (void *) enable;
	ev.user.data2 = NULL;

	SDL_PushEvent(&ev);
}

void nio_antialiasing_control_1(void)
{
	int32 enable;
	enable = msg_unpack_int32();
	antialiasing_control(enable);
}

#define DATA_SIZE 0x13000
PRIVATE int fsize;
char filename[BUF_SIZE];
PRIVATE int accumsize=0;

void nio_send_file_chunk()
{
	char buffer[DATA_SIZE];
	char buf[256];
	uint32 strsize = sizeof(buffer);
	msg_unpack_bytes((byte *) buffer, &strsize);
	printf("send file chunk %d\n", strsize);
	write_resource(buffer, strsize);
	accumsize += strsize;
	if ( fsize ) {
		printf("filesize: %d\n",fsize);
		printf("Loading %s...%02d%%\n",filename,100*accumsize/fsize);
		snprintf(buf,sizeof(buf),"%s...%02d%%",filename,100*accumsize/fsize);	/* FIX (2026): was sprintf into buf[256] */
		draw_resource_text(buf);
	}
}

void nio_close_file()
{
	printf("close file chunk\n");
	close_resource();
	//clear_resource_text();
}

void nio_load_resource(void)
{
	msg_unpack_string(filename, BUF_SIZE);
	fsize = msg_unpack_int32();
	printf("%s size is %d\n",filename,fsize);
	accumsize = 0;

	load_file(filename);
}

void nio_ui_init_1(void)
{
	;
}

void nio_ui_exit_1(void)
{
	;
}

void nio_server_script_1(void)
{
	;
}

void nio_client_script_1(void)
{
	;
}
