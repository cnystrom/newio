/******************************************************************************
 *
 *    niod.c
 *
 *    Copyright (C) 2002-2007  Chris Nystrom
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
 *    E-Mail: cnystrom@newio.org
 *    Blog:   http://newio.blogspot.com
 *    AIM:    nystromchris
 *
 *    Soli Deo Gloria
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef UNIX
#include <unistd.h>
#endif
#ifdef WIN32
#include "win32_lib.h"
#include "winsock2.h"
#endif
#include "newio_version.h"
#include "nio_log.h"
#include "str_lib.h"
#include "file_io_lib.h"

#define HOSTNAME_LEN  (256)

int my_getline(char *line);
void strip_nl(char *s);
void print_string(const char *s);

int main(int argc, char *argv[])
{
//	char hostname[HOSTNAME_LEN];
	char s[BUFSIZ] = "";
//	path home_dir;
	path command1;

	nio_log_open("niod.log");

	nio_log_print("Log file started!\n");

//	get_home_dir(home_dir);
//	nio_log_print("home dir = |%s|\n", home_dir);

//	gethostname(hostname, HOSTNAME_LEN);
//	nio_log_print("hostname = |%s|\n", hostname);

	snprintf(s, BUFSIZ, "NIOd Test Server 0.12");

	nio_log_print("main(): welcome = |%s|\n", s);

	usleep(10000);

	printf(s);
	fflush(stdout);

	nio_log_print("Welcome sent...\n");

	// get subsytem (used to do version checking here)

	if (my_getline(s) <= 0) {
		nio_log_print("no input. exiting.\n");
		nio_log_close();
		exit(0);
	}

	nio_log_print("s = |%s|\n", s);
	strip_nl(s);
	nio_log_print("s = |%s|\n", s);

	if (strncmp(s, NEWIO_SUBSYSTEM, strlen(NEWIO_SUBSYSTEM))) {
		printf(NEWIO_SUBSYSTEM);
		fflush(stdout);
		nio_log_print("Subsystem not found.\n");

		nio_log_print("Exiting.\n");
		nio_log_close();
		exit(0);
	} else {
		nio_log_print("Correct subsystem.\n");
		printf("0");
		fflush(stdout);
	}

	//
	// get command
	//

	nio_log_print("Getting command...\n");
	my_getline(s);

	nio_log_print("s = |%s|\n", s);
	strip_nl(s);
	nio_log_print("s = |%s|\n", s);


#ifdef WIN32
	pathcpy(command1, "C:/cygwin/usr/local/nio/bin/");
#else
	pathcpy(command1, "/usr/local/nio/bin/");
#endif
	pathcat(command1, s);

#ifdef WIN32
	pathcat(command1, ".exe");
#else
	pathcat(command1, ".nio");
#endif

	nio_log_print("command1 = |%s|\n", command1);

	//
	// if file exists, run it
	//

	if (file_exists(command1)) {
		int ret;

		nio_log_print("File |%s| exists.\n", command1);

		printf("0");
		fflush(stdout);
		nio_log_print("Return code sent.\n");

		nio_log_print("Running |%s|...\n", command1);
		ret = system(command1);
		nio_log_print("back from system() call...\n");
		nio_log_print("ret = %d\n", ret);
		nio_log_print("Exiting.\n");
		nio_log_close();
		exit(0);
	}

	nio_log_print("File |%s| does not exist.\n", command1);

	// used to also look in home dir for executables
/*
		pathcpy(command2, home_dir);
		pathcat(command2, "/nio/");
		pathcat(command2, s);

		wlog("command2 = |%s|\n", command2);

		if (file_exists(command2)) {
			wlog("File |%s| exists in home dir.\n", command2);
			printf("0");
			fflush(stdout);
			wlog("Return code sent.\n");

			wlog("Running |%s|...\n", command2);
			system(command2);
			wlog("back from system() call...\n");

			wlog("Exiting.\n");
			wlog_close();
			exit(0);
		} else {
			wlog("File |%s| does not exist in home dir.\n", command2);
		}
*/
	nio_log_print("Sending return code: -1\n");
	printf("-1");
	fflush(stdout);
	nio_log_print("Return code sent.\n");

	nio_log_print("Exiting.\n");
	nio_log_close();
	exit(0);
}

int my_getline(char *line)
{
	if (fgets(line, BUFSIZ, stdin) == NULL)
		return 0;
	else
		return strlen(line);
}

void strip_nl(char *s)
{
	int i, len;

//      wlog("s = |%s|\n", s);
//      print_string(s);

	len = strlen(s);

//      wlog("len = %d\n", len);

	for (i = 0; i < len; i++) {
		if (s[i] < 14) {
			s[i] = 0;
			break;
		}
	}

//      print_string(s);
//      wlog("s = |%s|\n", s);
}

/*
void print_string(const char *s)
{
	int i, len;

	len = strlen(s);

	for (i = 0; i < len; i++) {
		wlog("s[%d] = %d %c\n", i, s[i], s[i]);
	}
}
*/
