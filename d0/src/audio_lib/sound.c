/******************************************************************************
 *
 *    sound.c
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

#include <stdio.h>
#include "SDL.h"
#include "SDL_mixer.h"
#include "audio_lib.h"

extern int file_exists(const char *s);

PRIVATE Mix_Chunk *sound[MAX_NUM_SOUNDS] = { NULL };	// Pointer to data
PRIVATE int f_loaded[MAX_NUM_SOUNDS] = { FALSE };	// Sound slot loaded for use
PRIVATE int channel[MAX_NUM_SOUNDS] = { 0 };	// Channel allocated
PRIVATE int f_playing[MAX_NUM_SOUNDS] = { FALSE };	// Sound playing
PRIVATE int f_loop[MAX_NUM_SOUNDS] = { FALSE };

PRIVATE int sound_volume;

PUBLIC int next_free_sound_num(void)
{
	int i_num;

	for (i_num = 0; i_num < MAX_NUM_SOUNDS; i_num++) {
		if (FALSE == f_loaded[i_num]) {
			f_loaded[i_num] = TRUE;
			f_playing[i_num] = FALSE;
			f_loop[i_num] = FALSE;
			channel[i_num] = -1;
			return (i_num);
		}
	}

	fprintf(stderr,
		"next_free_sound_num(): No more sounds available.\n");

	return (-1);
}

PUBLIC int load_sound(const char *filename)
{
	int i;

	if (!audio_avail()) {
		fprintf(stderr, "load_sound(): audio not initialized.\n");
		return (-1);
	}

	if (!file_exists(filename)) {
		fprintf(stderr, "load_sound(): file not available.\n");
		return (-2);
	}

	i = next_free_sound_num();

	if (i < 0) {
		fprintf(stderr,
			"load_sound(): no sound slots available.\n");
		return (i);
	}

	sound[i] = Mix_LoadWAV(filename);

	if (NULL == sound[i]) {
		fprintf(stderr, "load_sound(): %s\n", Mix_GetError());
		fflush(stderr);
		return (-1);
	}

	return (i);
}

PUBLIC void sound_channel_callback(int channel_num)
{
	int i;

	for (i = 0; i < MAX_NUM_SOUNDS; i++) {
		if (channel[i] == channel_num) {
			if (f_loaded[i] == FALSE) {
				if (sound[i]) {
					Mix_FreeChunk(sound[i]);
					sound[i] = 0;
				}
			}
			f_playing[i] = FALSE;
			f_loop[i] = FALSE;
			channel[i] = -1;
			return;
		}
	}

	fprintf(stderr,
		"sound_channel_callback(): channel_num %d not found.\n",
		channel_num);
}

// Notes: loops == -1 is infinite loops.
//        loops == 1 plays the sample twice (1 loop). 
PUBLIC int play_sound(int i, int loops)
{
	int channel_num = -1;

	if (!audio_avail()) {
		fprintf(stderr, "play_sound(): audio not initialized.\n");
		return (-1);
	}

	Mix_ChannelFinished(sound_channel_callback);

	if (i < 0 || i >= MAX_NUM_SOUNDS) {
		fprintf(stderr, "play_sound(): bad sound file number.\n");
		return (-2);
	}

	if (FALSE == f_loaded[i]) {
		fprintf(stderr, "play_sound(): sound file not loaded.\n");
		return (-3);
	}

	if (TRUE == f_playing[i]) {
		return (-4);
	}

	channel_num = Mix_PlayChannel(-1, sound[i], loops);

	if (-1 == channel_num) {
		fprintf(stderr, "play_sound(): %s\n", Mix_GetError());
		fflush(stderr);
		return (-5);
	}

	channel[i] = channel_num;
	f_playing[i] = TRUE;
	f_loop[i] = loops == -1;

	return (channel_num);
}

int PUBLIC sound_playing(int i)
{
	if (!audio_avail()) {
		fprintf(stderr,
			"sound_playing(): audio not initialized.\n");
		return (-1);
	}

	if (i < 0 || i >= MAX_NUM_SOUNDS) {
		fprintf(stderr,
			"sound_playing(): bad sound file number.\n");
		return (-2);
	}

	return (f_playing[i]);
}

PUBLIC void delete_sound(int i)
{
	if (!audio_avail()) {
		fprintf(stderr,
			"sound_playing(): audio not initialized.\n");
		return;
	}

	if (i < 0 || i >= MAX_NUM_SOUNDS) {
		fprintf(stderr, "delete_sound(): bad sound number: %d.\n",
			i);
		return;
	}

	if (f_loaded[i]) {
		f_loaded[i] = FALSE;
		if (!f_playing[i]) {
			if (sound[i]) {
				Mix_FreeChunk(sound[i]);
				sound[i] = 0;
			}
		} else {
			if (f_loop[i]) {
				Mix_HaltChannel(channel[i]);
			}
		}
	}
}

PUBLIC void delete_all_sounds(void)
{
	int i;

	if (!audio_avail()) {
		fprintf(stderr,
			"sound_playing(): audio not initialized.\n");
		return;
	}

	for (i = 0; i < MAX_NUM_SOUNDS; i++) {
		delete_sound(i);
	}
}

PUBLIC void set_sound_volume(int v)
{
	int i;

	if (!audio_avail()) {
		fprintf(stderr,
			"set_sound_volume(): audio not initialized.\n");
		return;
	}

	if (v < 0)
		v = 0;

	// Note MIX_MAX_VOLUME defined in SDL_mixer.h 
	if (v > MIX_MAX_VOLUME)
		v = MIX_MAX_VOLUME;

	sound_volume = v;

	for (i = 0; i < MAX_NUM_SOUNDS; i++) {
		if (NULL != sound[i]) {
			Mix_VolumeChunk(sound[i], sound_volume);
		}
	}
}

PUBLIC int get_sound_volume(void)
{
	if (!audio_avail()) {
		fprintf(stderr,
			"sound_playing(): audio not initialized.\n");
		return (-1);
	}

	return (sound_volume);
}

PUBLIC int stop_sound(int i)
{
	if (!audio_avail()) {
		fprintf(stderr, "play_sound(): audio not initialized.\n");
		return (-1);
	}

	if (i < 0 || i >= MAX_NUM_SOUNDS) {
		fprintf(stderr, "play_sound(): bad sound file number.\n");
		return (-2);
	}

	if (FALSE == f_loaded[i]) {
		fprintf(stderr, "play_sound(): sound file not loaded.\n");
		return (-3);
	}

	if (f_loop[i] && f_playing[i]) {
		Mix_HaltChannel(channel[i]);
	}

	return (channel[i]);
}
