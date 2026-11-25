/******************************************************************************
 *
 *    music.c
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
 *    Blog:   http://newio.blogspot.com
 *    AIM:    nystromchris
 *
 *    Soli Deo Gloria
 *
 */

#include <stdlib.h>
#include "SDL.h"
#include "SDL_thread.h"
#include "SDL_mixer.h"
#include "audio_lib.h"
#include "nio_events.h"

extern int file_exists(const char *s);

PRIVATE Mix_Music *song;
PRIVATE int music_volume;
PRIVATE int music_thread(void *unused);
PRIVATE SDL_Thread *mthread = NULL;

PUBLIC int load_music(const char *filename)
{
	if (!audio_avail()) {
		fprintf(stderr, "load_music(): audio not initialized.\n");
		return (-1);
	}

	if (!file_exists(filename)) {
		fprintf(stderr, "load_music(): file not available.\n");
		return (-2);
	}

	stop_music();

	song = Mix_LoadMUS(filename);

	if (NULL == song) {
		fprintf(stderr, "load_song(): %s\n", Mix_GetError());
		return (-1);
	}

	return (0);
}

// Notes: loops == -1 is infinite loops.
//        loops == 1 plays the sample twice (1 loop).
PUBLIC void play_music(int loops)
{
	SDL_Event ev;

	if (!audio_avail()) {
		fprintf(stderr, "play_music(): audio not initialized.\n");
		return;
	}

	if (-1 == Mix_PlayMusic(song, loops)) {
		fprintf(stderr, "play_music(): %s\n", Mix_GetError());
		fflush(stderr);
		return;
	}

	ev.type = SDL_USEREVENT;
	ev.user.code = NIO_MUSIC_STATUS;
	ev.user.data1 = (void *) TRUE;
	ev.user.data2 = NULL;

	SDL_PushEvent(&ev);

	SDL_Delay(1000);

	mthread = SDL_CreateThread(music_thread, NULL);

	if (mthread == NULL) {
		fprintf(stderr,
			"play_music(): could not start monitoring thread.\n");
		return;
	}
}

PUBLIC void stop_music(void)
{
	int status;

	if (!audio_avail()) {
		fprintf(stderr, "stop_music(): audio not initialized.\n");
		return;
	}

	Mix_HaltMusic();

	if (mthread != NULL) {
		SDL_WaitThread(mthread, &status);
		mthread = NULL;
	}
}

PUBLIC int music_playing(void)
{
	if (!audio_avail()) {
		fprintf(stderr,
			"music_playing(): audio not initialized.\n");
		return (FALSE);
	}

	return (Mix_PlayingMusic());
}

PUBLIC void set_music_volume(int v)
{
	if (!audio_avail()) {
		fprintf(stderr,
			"set_music_volume(): audio not initialized.\n");
		return;
	}

	if (v < 0) {
		v = 0;
	}
	// Note MIX_MAX_VOLUME defined in SDL_mixer.h 
	if (v > MIX_MAX_VOLUME) {
		v = MIX_MAX_VOLUME;
	}

	music_volume = v;

	Mix_VolumeMusic(music_volume);
}

PUBLIC int get_music_volume(void)
{
	return (music_volume);
}

PRIVATE int music_thread(void *unused)
{
	SDL_Event ev;

	fprintf(stdout, "music_thread loop\n");

	while (1) {
		SDL_Delay(100);
		if (audio_avail()) {
			if (!Mix_PlayingMusic())
				break;
		} else {
			return 0;
		}
	}

	fprintf(stdout, "music_thread loop end\n");

	ev.type = SDL_USEREVENT;
	ev.user.code = NIO_MUSIC_STATUS;
	ev.user.data1 = (void *) FALSE;
	ev.user.data2 = NULL;

	SDL_PushEvent(&ev);

	return 0;
}
