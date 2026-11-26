/******************************************************************************
 *
 *    jukebox.c
 *
 *    Copyright (C) 2004-2007  Chris Nystrom
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
 *    E-Mail: cnystrom@newio.org
 *
 *    Soli Deo Gloria
 *
 */

#include <string.h>
#include "nio_lib.h"

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef TRUE
#define TRUE !FALSE
#endif

#define TOT_SONGS (17)

void jukebox_init(void);
void new_song(void);
void all_done(void);

struct song {
    char artist[32];
    char title[64];
    char filename[128];
} song[] = {
    {
    "Beastie Boys", "Now Get Busy", "beastie_boys__now_get_busy.ogg"}, {
    "David Byrne", "My Fair Lady", "david_byrne__my_fair_lady.ogg"}, {
    "Zap Mama", "Wadidyusay?", "zap_mama__wadidyusay.ogg"}, {
    "My Morning Jacket", "One Big Holiday",
	    "my_morning_jacket__one_big_holiday.ogg"}, {
    "Spoon", "Revenge", "spoon__revenge.ogg"}, {
    "Gilberto Gil", "Oslodum", "gilberto_gil__oslodum.ogg"}, {
    "Dan The Automator", "Relaxation Spa Treatment",
	    "dan_the_automator__relaxation_spa_treatment.ogg"}, {
    "Thievery Corporation", "DC 3000",
	    "thievery_corporation__dc_3000.ogg"}, {
    "Le Tigre", "Fake French", "le_tigre__fake_french.ogg"}, {
    "Paul Westerberg", "Looking Up In Heaven",
	    "paul_westerberg__looking_up_in_heaven.ogg"}, {
    "Chuck D With Fine Arts Militia", "No Meaning No",
	    "chuck_d_with_fine_arts_militia___no_meaning_no.ogg"}, {
    "The Rapture", "Sister Saviour (Blackstrobe Remix)",
	    "the_rapture__sister_saviour_blackstrobe_remix.ogg"}, {
    "Cornelius", "Wataridori 2", "cornelius__wataridori_2.ogg"}, {
    "Danger Mouse & Jemini", "What U Sittin' On",
	    "danger_mouse__jemini__what_u_sittin_on.ogg"}, {
    "DJ Dolores", "Oslodum 2004", "dj_dolores__oslodum_2004.ogg"}, {
    "Matmos", "Action At A Distance",
	    "matmos__action_at_a_distance.ogg"}, {
    "Rome_Italy", "Rome_Italy", "Rome_Italy.ogg"}
};

int song_count = TOT_SONGS;
int song_played[TOT_SONGS] = { FALSE };

int musicnum;

int main(int argc, char *argv[])
{
    int b1 = 0, b3 = 0;
    SDL_Event event;
    int key = 0;

    nio_app_init("jukebox", "0.1");

    jukebox_init();

    new_song();
    song_count--;

    while (1) {
#if 1
	if (!nio_music_playing()) {
	    if (song_count == 0) {
		all_done();
	    }
	    new_song();
	    song_count--;
	}
#endif
	while (nio_poll_event(&event)) {
	    switch (event.type) {
	    case SDL_MOUSEBUTTONDOWN:
		if (SDL_BUTTON_LEFT == event.button.button)
		    b1 = 1;
		if (SDL_BUTTON_RIGHT == event.button.button)
		    b3 = 1;
		break;
	    case SDL_MOUSEBUTTONUP:
		if (SDL_BUTTON_LEFT == event.button.button)
		    b1 = 0;
		if (SDL_BUTTON_RIGHT == event.button.button)
		    b3 = 0;
		break;
	    case SDL_KEYDOWN:
		key = event.key.keysym.sym;
		break;
	    case SDL_QUIT:
		key = ESC;
		break;
	    default:
		break;
	    }
	}
	if (b1 || key == CR) {
	    if (song_count == 0) {
		all_done();
	    }
	    new_song();
	    key = 0;
	    b1 = 0;
	    song_count--;
	}

	if (b3 || key == ESC) {
	    nio_stop_music(musicnum);
	    nio_exit();
	    exit(0);
	}
    }

    exit(0);
}

void jukebox_init(void)
{
    int font;
    color black, white;

    black = nio_get_color("black");
    white = nio_get_color("white");

    nio_set_screen(640, 480, black);
    nio_clear_screen(black);

    font = nio_load_sys_font(NIO_DEFAULT_FONT,
			     NIO_DEFAULT_PTSIZE,
			     NIO_STYLE_NORMAL, white, black);

    nio_term_init(font, black, 1, 1, 30, 80);

    nio_print("\n Jukebox Demo version 0.01\n\n");
    nio_print(" Left click = new song        Right click = exit\n\n");
    nio_print("     Artist                      Title\n");
    nio_paint();
    nio_send();
}

void new_song(void)
{
    int i, j;
    char filepath[256];

    i = nio_rand_int(TOT_SONGS);

    while (song_played[i] == TRUE) {
	i = nio_rand_int(TOT_SONGS);
    }

    song_played[i] = TRUE;

    nio_printf(" %s ", song[i].artist);

    for (j = (27 - strlen(song[i].artist)); j > 0; j--)
	nio_print(" ");

    nio_printf("%s\n", song[i].title);
    strcpy(filepath, "/usr/local/nio/lib/jukebox/");
    strcat(filepath, song[i].filename);

    musicnum = nio_load_music(filepath);
    nio_paint();
    nio_send();
    SDL_Delay(1000);
    nio_play_music(musicnum, 0);
    nio_send();
    SDL_Delay(1000);
}

void all_done(void)
{
    int i;

    for (i = 0; i < TOT_SONGS; i++) {
	song_played[i] = FALSE;
    }

    song_count = TOT_SONGS;
}
