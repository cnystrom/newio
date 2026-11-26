/******************************************************************************
 *
 *    audio.c
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

#include <stdio.h>
#include "SDL.h"
#include "SDL_mixer.h"
#include "audio_lib.h"

PRIVATE int audio_init = FALSE;

PUBLIC int init_audio(void)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512) < 0) {
		fprintf(stderr, "init_audio(): %s\n", Mix_GetError());
		return (-1);
	}

	Mix_AllocateChannels(16);

	audio_init = TRUE;

	return (0);
}

PUBLIC void close_audio(void)
{
	if (audio_init) {
		Mix_CloseAudio();
	}

	audio_init = FALSE;
}

PUBLIC int audio_avail(void)
{
	return (audio_init);
}
