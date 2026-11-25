/******************************************************************************
 *
 *    audio_lib.h
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

#ifndef _AUDIO_LIB_H
#define _AUDIO_LIB_H

#ifndef _SDL_H
#include "SDL.h"
#endif				/*  */

#ifndef _MIXER_H
#include "SDL_mixer.h"
#endif				/*  */

#ifndef PRIVATE
#define PRIVATE static
#endif				/*  */

#ifndef PUBLIC
#define PUBLIC
#endif				/*  */

#ifndef FALSE
#define FALSE  (0)
#endif

#ifndef TRUE
#define TRUE  !(FALSE)
#endif

#ifndef OFF
#define OFF  (0)
#endif				/*  */

#ifndef ON
#define ON   (!OFF)
#endif				/*  */

#define MAX_NUM_CHANNELS (32)
#define MAX_NUM_SOUNDS   (32)

PUBLIC int init_audio(void);
PUBLIC void close_audio(void);
PUBLIC int audio_avail(void);
PUBLIC int load_sound(const char *filename);
PUBLIC int play_sound(int i, int loops);
PUBLIC int sound_playing(int i);
PUBLIC void delete_sound(int i);
PUBLIC void delete_all_sounds(void);
PUBLIC int load_music(const char *filename);
PUBLIC void play_music(int loops);
PUBLIC void stop_music(void);
PUBLIC int music_playing(void);
PUBLIC void set_sound_volume(int v);
PUBLIC int get_sound_volume(void);
PUBLIC void set_music_volume(int v);
PUBLIC int get_music_volume(void);
PUBLIC int stop_sound(int i);

#endif				// _AUDIO_LIB_H
