/******************************************************************************
 *
 *    font.c
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
#include <stdlib.h>
#ifdef UNIX
#include <unistd.h>
#endif
#include <string.h>

#include "SDL.h"
#include "SDL_ttf.h"

#include "nio_types.h"
#include "nio_log.h"
#include "nio_lib.h"
#include "font.h"

PRIVATE char *font_file[] = {
	"FreeMonoBoldOblique.ttf",
	"FreeMonoBold.ttf",
	"FreeMonoOblique.ttf",
	"FreeMono.ttf",
	"FreeSansBoldOblique.ttf",
	"FreeSansBold.ttf",
	"FreeSansOblique.ttf",
	"FreeSans.ttf",
	"FreeSerifBoldItalic.ttf",
	"FreeSerifBold.ttf",
	"FreeSerifItalic.ttf",
	"FreeSerif.ttf"
};

#ifdef WIN32
char system_font_path[] = "c:/cygwin/usr/local/nio/lib/system/";
#else
char system_font_path[] = "/usr/local/nio/lib/system/";
#endif

glyphMetrics system_font_metrics[MAX_FONTS] = {
	{13, 10, -2, 14, 16},
	{13, 10, -2, 14, 14},
	{13, 10, -2, 14, 15},
	{13, 10, -2, 14, 14},
	{13, 10, -2, 14, 24},
	{13, 10, -2, 14, 23},
	{13, 10, -2, 14, 24},
	{13, 10, -2, 14, 25},
	{13, 10, -2, 14, 28},
	{13, 10, -2, 14, 30},
	{13, 10, -2, 14, 27},
	{13, 10, -2, 14, 26},
};

#define LETTER_X 88

PUBLIC void
load_glyph_metrics(const char *fontName, int ptSize, int style,
		   int font_num)
{
//      int i;
	int advance = 0;
	int maxx = 0;
//      char letter[2] = { 0, 0 };
	TTF_Font *ttfFont = NULL;
	int minx;
	int miny, maxy;

	if (TTF_Init() < 0) {
		nio_log_print("Can't init SDL_ttf library.\n");
		return;
	}

	ttfFont = TTF_OpenFont(fontName, ptSize);

	if (NULL == ttfFont) {
		nio_log_print
		    ("load_glyph_font(): Can't open font file. (%s)\n",
		     fontName);
		return;
	}

	TTF_SetFontStyle(ttfFont, style);

	system_font_metrics[font_num].height = TTF_FontHeight(ttfFont);
	system_font_metrics[font_num].ascent = TTF_FontAscent(ttfFont);
	system_font_metrics[font_num].descent = TTF_FontDescent(ttfFont);
	system_font_metrics[font_num].lineSkip = TTF_FontLineSkip(ttfFont);

	TTF_GlyphMetrics(ttfFont,
			 (Uint16) LETTER_X, &minx,
			 &maxx, &miny, &maxy, &advance);

	nio_log_print("advance = %d\n", advance);
	nio_log_print("maxx = %d\n", maxx);
	nio_log_print("font->width = %d\n", advance + maxx);

	system_font_metrics[font_num].width = advance + maxx;

	TTF_Quit();
}

PUBLIC void
load_system_glyph_metrics(int num, int ptSize, int style, int font_num)
{
	char buf[BUF_SIZE];

	strncpy(buf, system_font_path, BUF_SIZE - 1);
	buf[BUF_SIZE - 1] = '\0';
	/* FIX (2026): the strncat bound was the whole buffer, not the room left */
	strncat(buf, font_file[num], BUF_SIZE - strlen(buf) - 1);

	load_glyph_metrics(buf, ptSize, style, font_num);
}

PUBLIC int get_font_height(int font_num)
{
	return system_font_metrics[font_num].height;
}

PUBLIC int get_font_width(int font_num)
{
	return system_font_metrics[font_num].width;
}

void font_init()
{
	if (TTF_Init() < 0) {
		nio_log_print("Can't init SDL_ttf library.\n");
		return;
	}
}

void font_quit()
{
	TTF_Quit();
}
