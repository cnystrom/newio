/******************************************************************************
 *
 *    check_home.c
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

#define NIO_DIR  "/.d0/"
#define CACHE_DIR  "cache/"
#define LOG_DIR  "logs/"

void check_home_dir(void)
{
	path nio_dir;
	path cache_dir;
	path log_dir;

	get_home_dir(nio_dir);

	pathcat(nio_dir, NIO_DIR);
	check_dir(nio_dir);

	pathcpy(cache_dir, nio_dir);
	pathcat(cache_dir, CACHE_DIR);
	check_dir(cache_dir);

	pathcpy(log_dir, nio_dir);
	pathcat(log_dir, LOG_DIR);
	check_dir(log_dir);

//  printf("nio_dir = %s\n", nio_dir);
//  printf("cache_dir = %s\n", cache_dir);
//  printf("log_dir = %s\n", log_dir);
}
