/******************************************************************************
 *
 *    misc_io.c
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
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#ifdef WIN32
#include <direct.h>
#else
#include <pwd.h>	/* FIX (2026): for get_home_dir() */
#include <unistd.h>
#endif
#include "str_lib.h"
#include "../nio_log/nio_log.h"
#include "file_io_lib.h"

#define PATH_SIZE  (256)

#ifdef WIN32

#include <tchar.h>
#include <shlobj.h>
#include <shlwapi.h>

/*
 * Following bit of code from (inspired by):

 * GLIB - Library of useful routines for C programming
 * Copyright (C) 1995-1998  Peter Mattis, Spencer Kimball and Josh MacDonald
 */

int get_special_folder(int csidl, TCHAR * sfp)
{
	HRESULT hr;
	LPITEMIDLIST pidl = NULL;
	BOOL b = 0;

	hr = SHGetSpecialFolderLocation(NULL, csidl, &pidl);
	if (hr == S_OK) {
		b = SHGetPathFromIDList(pidl, sfp);
		if (b)
			CoTaskMemFree(pidl);
		else
			sfp[0] = 0;
	}
	return b;
}

void get_windows_directory_root(TCHAR * windowsdir)
{
	if (GetWindowsDirectory(windowsdir, sizeof(windowsdir))) {
		PathStripToRoot(windowsdir);
		return;
	}
	strlcpy(windowsdir, "C:\\", MAX_PATH);
	return;
}

/*
 * end bit of code
 */
#endif

PUBLIC int get_home_dir(char *s)
{
	int len, i;

#ifdef WIN32
/*
 * Following bit of code from (inspired by):

 * GLIB - Library of useful routines for C programming
 * Copyright (C) 1995-1998  Peter Mattis, Spencer Kimball and Josh MacDonald
 */
	char *tmp;
	char homestr[MAX_PATH + 1] = "";

	tmp = getenv("HOME");

	if (tmp && isalpha(tmp[0]) && tmp[1] == ':') {
		strlcpy(homestr, tmp, MAX_PATH);
	} else {
		if ((tmp = getenv("USERPROFILE")) != NULL) {
			strlcpy(homestr, tmp, MAX_PATH);
		} else {
			if (get_special_folder(CSIDL_PROFILE, homestr) ==
			    0)
				get_windows_directory_root(homestr);
		}
	}

	tmp = homestr;

/*
 * end bit of code
 */
#else
	char *tmp;
	if ((tmp = getenv("HOME")) == NULL) {
		nio_log_print("get_home_dir(): HOME not found.\n");
		/* FIX (2026): was strlen(NULL). Use the password
		 * file entry, or else an empty string. */
		struct passwd *pw = getpwuid(getuid());
		tmp = (pw != NULL && pw->pw_dir != NULL) ? pw->pw_dir : "";
	}
#endif

	len = strlen(tmp);

	i = strlcpy(s, tmp, PATH_SIZE);

	return (len);
}

PRIVATE int dir_exists(const char *s)
{
	struct stat buf;

#ifdef UNIX
	if (lstat(s, &buf) < 0)
#else
	if (stat(s, &buf) < 0)
#endif
	{
		return (FALSE);
	}

	if (S_ISDIR(buf.st_mode))
		return (TRUE);
	else
		return (FALSE);
}

PUBLIC int file_exists(const char *s)
{
	struct stat buf;

#ifdef UNIX
	if (lstat(s, &buf) < 0)
#else
	if (stat(s, &buf) < 0)
#endif
	{
	//	nio_log_print("file_exists(): stat returns false\n");
		return (FALSE);
	}

	if (S_ISREG(buf.st_mode))
		return (TRUE);
	else
		return (FALSE);
}

PUBLIC void check_dir(const char *s)
{
	if (!dir_exists(s)) {
#ifdef UNIX
		if (mkdir(s, 0755) != 0)
#else
		if (mkdir(s) != 0)
#endif
		{
			if (errno != EEXIST)
				nio_log_print(
					"check_dir(): mkdir failed for %s\n",
					s);
		}
	}
}

PUBLIC char *niobasename(char *s)
{
	char *s2 = s;

	while (*s) {
#ifdef UNIX
		if (*s++ == '/')
			s2 = s;
#else
		if (*s == '\\' || *s == '/') {
			s2 = s + 1;
		}
		s++;
#endif
	}

	return (s2);
}

PUBLIC long file_size(const char *s)
{
	struct stat buf;

#ifdef UNIX
	if (lstat(s, &buf) < 0)
	{
		nio_log_print("file_size(): stat returns false\n");
		return (FALSE);
	}

	if (S_ISREG(buf.st_mode))
		return buf.st_size;
	else
		return 0;
#else
	char strbuf[_MAX_PATH];
	strcpy(strbuf,"c:/cygwin");
	strcat(strbuf,s);
	if (stat(strbuf, &buf) < 0)
	{
		nio_log_print("file_size(): stat returns false\n");
		return (FALSE);
	}

	if (S_ISREG(buf.st_mode))
		return buf.st_size;
	else
		return 0;
#endif
}


