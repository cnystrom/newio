/******************************************************************************
 *
 *    done.c
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
 *
 *    Soli Deo Gloria
 *
 */

#include "nio_types.h"
#include "done.h"

PRIVATE int f_done = FALSE;

PUBLIC void set_done(int b)
{
//	nio_log_print("done(): f_done = %d\n", (int) b);

	f_done = b;
}

PUBLIC int done(void)
{
	return (f_done);
}
