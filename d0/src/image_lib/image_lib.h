/******************************************************************************
 *
 *    image_lib.h
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

#ifndef _IMAGE_LIB_H
#define _IMAGE_LIB_H

#ifndef _SDL_H
#include "SDL.h"
#endif				/*  */

#ifndef _IMG_H
#include "SDL_image.h"
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

#define MAX_IMAGES    (50)

PUBLIC int load_image(const char *file_name, int f_color_key, Uint8 r,
		      Uint8 g, Uint8 b);
PUBLIC SDL_Surface *get_image(int i_num);
PUBLIC void free_image(int i_num);
PUBLIC void free_all_images(void);

#endif				// _IMAGE_LIB_H
