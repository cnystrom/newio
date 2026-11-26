/******************************************************************************
 *
 *    nio_log.c
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

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "nio_log.h"

PRIVATE FILE *pFile = NULL;

PRIVATE int use_stdout = FALSE;

PUBLIC void nio_log_use_stdout(int b)
{
	use_stdout = b;
}

PUBLIC int nio_log_open(const char *pathname)
{
	if (use_stdout) {
		return (TRUE);
	}

	if (pFile != NULL) {
		nio_log_close();
	}

	pFile = fopen(pathname, "w+");

	return (pFile != NULL);
}

PUBLIC void nio_log_close(void)
{
	if (pFile != NULL) {
		fclose(pFile);
		pFile = NULL;	/* FIX (2026): no use after close */
	}
}

#define DEBUG

PUBLIC void nio_log_print(const char *format, ...)
{
#ifdef DEBUG
	va_list ap;

	if (use_stdout) {
		va_start(ap, format);
		vprintf(format, ap);
		va_end(ap);

		fflush(stdout);

		return;
	}

	if (pFile != NULL) {

		va_start(ap, format);
		vfprintf(pFile, format, ap);
		va_end(ap);

		fflush(pFile);
	}
#endif
}

/*
PUBLIC void nio_log_dump(char *s)
{
	int i;
	int len;
	char c;

	len = strlen(s);

	printf("---\n");

	for (i = 0; i < len; i++) {

		c = *s++;

		printf("%d. %d %c\n", i, c, c);
	}

	printf("---\n");
}
*/

/*
PUBLIC void nio_log_nprint(char *s, int num)
{
	int i;

	for (i = 0; i < num; i++) {
		if (use_stdout) {
			putc((int) s++, stdout);
		}
		else {
			putc((int) s++, pFile);
		}
	}

	if (use_stdout) {
		putc(0, stdout);
	} else {
		putc(0, pFile);
	}
}
*/

PUBLIC void nio_log_error(const char *func_name, const char *format, ...)
{
	va_list ap;

	if (use_stdout) {

		printf(func_name);

		va_start(ap, format);
		vprintf(format, ap);
		va_end(ap);

		fflush(stdout);

		return;
	}

	if (pFile != NULL) {

		fprintf(pFile, func_name);

		va_start(ap, format);
		vfprintf(pFile, format, ap);
		va_end(ap);

		fflush(pFile);
	}
}
