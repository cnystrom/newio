/******************************************************************************
 *
 *    play_intro.c
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

#include "file_io_lib/file_io_lib.h"
#include "audio_lib/audio_lib.h"
#include "install_dir.h"

#define SOUND_FILE  "newio.wav"

void play_intro_sound(void)
{
	int sound_0;
	path sound_file;

	pathcpy(sound_file, get_install_dir());
	pathcat(sound_file, SOUND_FILE);

	sound_0 = load_sound(sound_file);
	play_sound(sound_0, 0);
	delete_sound(sound_0);
}
