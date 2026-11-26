/******************************************************************************
 *
 *    image_lib.c
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
#include <SDL.h>
#include <SDL_image.h>
#include "image_lib.h"

extern int file_exists(const char *s);

PRIVATE int next_free_image_num(void);
PRIVATE SDL_Surface *image[MAX_IMAGES];
PRIVATE int i_flag[MAX_IMAGES] = {
	FALSE
};

PRIVATE int next_free_image_num(void)
{
	int i_num;
	for (i_num = 0; i_num < MAX_IMAGES; i_num++) {
		if (FALSE == i_flag[i_num]) {
			i_flag[i_num] = TRUE;
			return (i_num);
		}
	}
	fprintf(stderr,
		"next_free_image_num(): No more images available.\n");
	return (-1);
}

PUBLIC int load_image(const char *file_name, int f_color_key, Uint8 r,
		      Uint8 g, Uint8 b)
{
	int i_num;
	SDL_Surface *s0, *s1;
	i_num = next_free_image_num();
	if (i_num < 0) {
		fprintf(stderr, "load_image(): no image slots left.\n");
		return (i_num);
	}
	if (file_exists(file_name)) {
		s0 = IMG_Load(file_name);
	} else {
		fprintf(stderr,
			"load_image(): Unable to load image file.\n");
		return -1;
	}
	if (NULL == s0) {
		fprintf(stderr,
			"load_image(): Unable to load image file.\n");
		return -1;
	}
	s1 = SDL_DisplayFormat(s0);
	if (NULL == s1) {
		fprintf(stderr,
			"load_image(): Unable to convert image file.\n");
		return -1;
	}
	if (f_color_key) {
		SDL_SetColorKey(s1,
				(SDL_SRCCOLORKEY | SDL_RLEACCEL),
				SDL_MapRGB(s1->format, r, g, b));
	}
	image[i_num] = s1;
	SDL_FreeSurface(s0);
	return (i_num);
}

PUBLIC SDL_Surface *get_image(int i_num)
{
	if (i_num < 0 && i_num >= MAX_IMAGES) {
		fprintf(stderr, "get_image(): bad image number: %d.\n",
			i_num);
		return (NULL);
	}
	if (NULL == image[i_num]) {
		fprintf(stderr, "get_image(): image %d not loaded.\n",
			i_num);
		return (NULL);
	}
	return (image[i_num]);
}

PUBLIC void free_image(int i_num)
{
	if (i_num < 0 || i_num >= MAX_IMAGES) {
		fprintf(stderr, "free_image(): bad image number: %d.\n",
			i_num);
		return;
	}
	SDL_FreeSurface(image[i_num]);
	i_flag[i_num] = FALSE;
}

PUBLIC void free_all_images(void)
{
	int i;
	for (i = 0; i < MAX_IMAGES; i++) {
		if (i_flag[i]) {
			free_image(i);
		}
	}
}
