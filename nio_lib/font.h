/******************************************************************************
 *
 *    font.h
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
 *    Blog:   http://conversazione.blogspot.com
 *    AIM:    nystromchris
 *
 *    Soli Deo Gloria
 *
 */

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef _FONT_H
#define _FONT_H

#define	MAX_FONTS 1024
#define	BUF_SIZE 1024

	typedef struct {
		int height;
		int ascent;
		int descent;
		int lineSkip;
		int width;
	} glyphMetrics;

	extern glyphMetrics system_font_metrics[MAX_FONTS];

	PUBLIC void load_system_glyph_metrics(int num, int ptSize,
					      int style, int font_num);
	PUBLIC void load_glyph_metrics(const char *fontName, int ptSize,
				       int style, int font_num);
	PUBLIC int get_font_height(int font_num);
	PUBLIC int get_font_width(int font_num);

#endif				/* _FONT_H */

#ifdef  __cplusplus
}
#endif
