/******************************************************************************
 *
 *    nio_log.h
 *
 *    Copyright (C) 2005-2007  Chris Nystrom
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
 *    E-Mail: cnystrom@newio.org
 *
 *    Soli Deo Gloria
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "../nio_types.h"

	PUBLIC void nio_log_use_stdout(int b);
	PUBLIC int nio_log_open(const char *pathname);
	PUBLIC void nio_log_close(void);
	PUBLIC void nio_log_print(const char *format, ...);
	PUBLIC void nio_log_error(const char *func_name,
				  const char *format, ...);
	PUBLIC void nio_log_dump(char *s);

#ifdef __cplusplus
}
#endif
