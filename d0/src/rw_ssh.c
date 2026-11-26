/******************************************************************************
 *
 *    rw_ssh.c
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
#include "nio_types.h"
#include "nio_log.h"
#include "str_lib.h"
#include "ssh2_lib.h"

int read_data(int fd, char *p, int len, int block)
{
	int ret = 0;
//      char *s;

	ret = read_channel(p, len, block);

/*
	s = str_null_terminated(p, ret);

	nio_log_print("read_data(): |%s|\n", s);

	nio_log_dump(s);

	free(s);
*/

	if (ret == -1) {
		nio_log_error("read_data():", " error on read\n");
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
/*	char *s;

	s = str_null_terminated(p, len);

	nio_log_print("write_data(): |%s|\n", s);

	free(s);
*/
	total = len;

	while (total > 0) {

		ret = write_channel(p, len);

		total -= ret;

		if (total > 0) {
			nio_log_error("write_data():", " short write.\n");
		}

	}

	return (ret);
}
