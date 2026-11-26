/******************************************************************************
 *
 *    rw_stdio.c
 *
 *    Copyright (C) 2007  Dreadnought Incorporated
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
 *    E-Mail: cnystrom@newio.com
 *
 *    Soli Deo Gloria
 *
 */

#include <stdlib.h>
#ifdef UNIX
#include <unistd.h>
#endif
#include "nio_types.h"
#include "nio_log.h"
#include "str_lib.h"

int read_data(int fd, char *p, int len, int block)
{
	int ret = 0;
	char *s;

	ret = read(fd, p, len);

	s = str_null_terminated(p, ret);

	nio_log_print("read_data(): |%s|\n", s);

	free(s);

	if (ret == -1) {
		nio_log_error("read_data():", " error on read\n");
		nio_log_close();
		exit(-1);
	}

	if (ret == 0) {
		nio_log_error("read_data():", " EOF\n");
	}

	return (ret);
}

int write_data(int fd, char *p, int len)
{
	int ret = 0;
	int total = 0;
	char *s;

	total = len;

	s = str_null_terminated(p, len);

	nio_log_print("write_data(): |%s|\n", s);

	free(s);

	while (total > 0) {
		ret = write(fd, p, len);

		total -= ret;

		if (total > 0) {
			nio_log_error("write_data():", " short write.\n");
			nio_log_close();
			exit(-1);
		}

	}

	return (ret);
}
