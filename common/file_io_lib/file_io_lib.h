/******************************************************************************
 *
 *    file_io_lib.h
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

#ifndef _FILE_IO_LIB_H
#define _FILE_IO_LIB_H

#ifdef WIN32
#include <stddef.h>
#endif				/*  */

#ifndef _SYS_TYPES_H
#include <sys/types.h>
#endif				/*  */

#ifndef _TYPES_H
#include "nio_types.h"
#endif				/*  */

#ifndef PRIVATE
#define PRIVATE static
#endif				/*  */

#ifndef PUBLIC
#define PUBLIC
#endif				/*  */
PUBLIC int get_home_dir(char *s);
PUBLIC int file_exists(const char *s);
PUBLIC void check_dir(const char *s);
PUBLIC char *niobasename(char *s);
PUBLIC long file_size(const char *s);

// path
#define PATH_SIZE  (256)
typedef char path[PATH_SIZE];

#ifdef WIN32
#define S_ISDIR(m) (((m) & _S_IFMT) == _S_IFDIR)
#define S_ISFIFO(m) (((m) & _S_IFMT) == _S_IFIFO)
#define S_ISCHR(m) (((m) & _S_IFMT) == _S_IFCHR)
#define S_ISBLK(m) (((m) & _S_IFMT) == _S_IFBLK)
#define S_ISREG(m) (((m) & _S_IFMT) == _S_IFREG)
#endif				/*  */
PUBLIC size_t pathcpy(path dst, const char_ptr src);
PUBLIC size_t pathcat(path dst, const char_ptr src);

#endif				// _FILE_IO_LIB_H
