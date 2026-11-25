/******************************************************************************
 *
 *    file_xfr.c
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
 *    Blog:   http://conversazione.blogspot.com
 *    AIM:    nystromchris
 *
 *    Soli Deo Gloria
 *
 */

#include <stdio.h>
#include <string.h>
#ifdef WIN32
#include <io.h>
#include <sys/stat.h>
#else
#include <unistd.h>
#endif
#include <fcntl.h>
#include "SDL.h"
#include "str_lib.h"
#include "file_io_lib/file_io_lib.h"
#include "ssh2_lib/ssh2_lib.h"
#include "file_xfr.h"
#include "nio_events.h"

#define NAME_SIZE (256)
#define LOGIN_SIZE (16)

PRIVATE int copy_file(const char *filename, const char *filepath);

PRIVATE char server[NAME_SIZE];
PRIVATE char app_name[NAME_SIZE];
PRIVATE char app_ver[NAME_SIZE];
PRIVATE path cwd;

PRIVATE path niodir;		// NIO cache dir
PRIVATE path dirname;
PRIVATE path filepath;

int open_resource(const char *filepath);
int write_resource(char *buf, int count);
void close_resource();


PUBLIC void
init_file_loader(const char *an, const char *av, const char *dir)
{
	strlcpy(app_name, an, NAME_SIZE);
	strlcpy(app_ver, av, NAME_SIZE);
	pathcpy(cwd, (const char_ptr) dir);

//      printf("init_file_loader(): cwd = %s\n", cwd);

	get_home_dir(niodir);
	pathcat(niodir, "/.d0/cache/");
	pathcpy(dirname, niodir);
	check_dir(dirname);

//      printf("init_file_loader(): server = |%s|\n", server);

	pathcat(dirname, server);
	pathcat(dirname, "/");
	check_dir(dirname);

	pathcat(dirname, app_name);
	pathcat(dirname, "/");
	check_dir(dirname);

	pathcat(dirname, app_ver);
	pathcat(dirname, "/");
	check_dir(dirname);

//      printf("init_file_loader(): dirname = %s\n", dirname);
}

PUBLIC void init_file_xfer(const char *s)
{
	strlcpy(server, s, NAME_SIZE);

}

PUBLIC char *load_file(const char *filename)
{
	int len;
	char *f;
	path file;

	len = (int) strlen(filename);

	if (len > PATH_SIZE) {
		fprintf(stderr, "load_file(): filename too big.\n");
		return (NULL);
	}

	pathcpy(file, (const char_ptr) filename);

	f = niobasename(file);

//      printf("load_file(): filename = %s\n", filename);

	pathcpy(filepath, dirname);
	pathcat(filepath, f);

	printf("load_file(): filepath = %s\n", filepath);

//resource load command on server waits for client response.  client checks to see if file exists, 
//sends message to server to indicate file send or not.  If sent, send in 16k 
//packets until finished.  
	if (file_exists(filepath) == FALSE) {
		printf("File %s does not exist in cache.\n", f);
		printf("Copying...\n");
		copy_file(filename, filepath);
	} else {
		SDL_Event ev;
		printf("Dont need to copy...\n");
		ev.type = SDL_USEREVENT;
		ev.user.code = NIO_FILE_XFER_STATUS;
		ev.user.data1 = (void *) FALSE;
		ev.user.data2 = NULL;

		SDL_PushEvent(&ev);
	}
	return (filepath);
}

PUBLIC char *get_filepath(const char *filename)
{
	int len;
	char *f;
	path file;

	len = (int) strlen(filename);

	if (len > PATH_SIZE) {
		fprintf(stderr, "get_filepath(): filename too big.\n");
		return (NULL);
	}

	pathcpy(file, (const char_ptr) filename);

	f = niobasename(file);

	pathcpy(filepath, dirname);
	pathcat(filepath, f);

	printf("get_filepath(): filepath = %s\n", filepath);

	return (filepath);
}

PRIVATE int copy_file(const char *filename, const char *filepath)
{
	if (open_resource(filepath) < 0) {
		fprintf(stderr, "copy_file(): Failed.\n");
		return (-1);
	} else {
		SDL_Event ev;
		ev.type = SDL_USEREVENT;
		ev.user.code = NIO_FILE_XFER_STATUS;
		ev.user.data1 = (void *) TRUE;
		ev.user.data2 = NULL;

		SDL_PushEvent(&ev);
		return 0;
	}
	if (!file_exists(filepath)) {
		fprintf(stderr, "copy_file(): Failed.\n");
		return (-1);
	}

	return 0;
}

static int fd;
int open_resource(const char *filepath)
{
	printf("open_resource: %s", filepath);
#ifdef WIN32
	fd = open(filepath, _O_WRONLY | _O_CREAT | _O_BINARY | _O_TRUNC,
		  _S_IREAD | _S_IWRITE);
#else
	fd = open(filepath, O_CREAT | O_WRONLY | O_TRUNC,
		  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
#endif
	if (fd == -1) {
		printf("Error opening %s\n", filepath);
		return -1;
	}
	printf("Opened %s fd: %d", filepath, fd);
	return 0;
}


int write_resource(char *buf, int count)
{
	int bytes_written = write(fd, buf, count);
	if (bytes_written != count) {
		printf("Error writing resource fd %d", fd);
		return -1;
	}
	return 0;
}


void close_resource()
{
	SDL_Event ev;
	close(fd);

	ev.type = SDL_USEREVENT;
	ev.user.code = NIO_FILE_XFER_END;
	ev.user.data1 = (void *) TRUE;
	ev.user.data2 = NULL;

	SDL_PushEvent(&ev);
}
