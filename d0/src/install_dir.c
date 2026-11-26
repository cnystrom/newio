/******************************************************************************
 *
 *    install_dir.c
 *
 *    Copyright (C) 2002, 2005  Chris Nystrom
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 *    For more license nformation see:
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

#include <stdio.h>
#include "./file_io_lib/file_io_lib.h"
#include "install_dir.h"

#define HOME_DIR_ADD "/.d0/"
#define SHARE_DIR "/usr/share/d0/"
#define CHECK_FILE "newio.wav"

PRIVATE char install_dir[PATH_SIZE];

PUBLIC void find_install_dir(void)
{
	char home_dir[PATH_SIZE];
	char share_dir[PATH_SIZE] = SHARE_DIR;
	char check[PATH_SIZE];

	get_home_dir(home_dir);

//  printf("home_dir = %s\n", home_dir);
//  printf("strlen(homedir) = %d\n", strlen(home_dir));

	pathcat(home_dir, HOME_DIR_ADD);

//  printf("home_dir = %s\n", home_dir);

	pathcpy(check, home_dir);
	pathcat(check, CHECK_FILE);

//  printf("check = %s\n", check);

	if (file_exists(check)) {
		pathcpy(install_dir, home_dir);
		return;
	}

	pathcpy(check, share_dir);
	pathcat(check, CHECK_FILE);

//  printf("check = %s\n", check);

	if (file_exists(check)) {
		pathcpy(install_dir, share_dir);
		return;
	}

	pathcpy(install_dir, "./");
	return;
}

PUBLIC char *get_install_dir(void)
{
	return (install_dir);
}
