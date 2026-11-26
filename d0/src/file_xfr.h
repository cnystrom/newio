/******************************************************************************
 *
 *    file_xfr.h
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

#ifndef _H_FILE_XFR
#define _H_FILE_XFR

#ifndef PRIVATE
#define PRIVATE static
#endif

#ifndef PUBLIC
#define PUBLIC
#endif

PUBLIC void init_file_loader(const char *app_name,
			     const char *app_ver, const char *cwd);

PUBLIC void init_file_xfer(const char *s);

PUBLIC char *load_file(const char *filename);

PUBLIC char *get_filepath(const char *filename);

PUBLIC int write_resource(char *buf, int count);

PUBLIC void close_resource();
#endif				/* _H_FILE_XFR */
