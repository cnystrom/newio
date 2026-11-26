/******************************************************************************
 *
 *    fonts.c
 *
 *    New original replacement, added 2026 after the previous third-party
 *    font helper (font_lib) was omitted from the published NewIO tree. This file is not
 *    derived from that source. It provides the functions the d0 client
 *    calls, under the same names.
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published
 *    by the Free Software Foundation; either version 2.1 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but without any warranty whatsoever.
 *
 *****************************************************************************/

#include <stdio.h>
#include <string.h>

#include "font_lib.h"
#include "screen_lib.h"
#include "file_io_lib.h"
#include "../install_dir.h"

#define FONT_DIR "fonts/"
#define PATH_LEN (512)

PRIVATE const char *sys_font_file[MAX_SYS_FONT + 1] = {
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

PRIVATE glyphFont fonts[MAX_FONTS];

/*
 * Font numbers count up from 0, the same way nio_lib numbers them on the
 * server, so a number sent by a program names the same font here. When
 * every font has been freed (the login and URL boxes free theirs, and
 * call_nio() frees all at the end of a program) numbering starts over.
 */
PRIVATE int next_font = 0;

PRIVATE int font_ready = FALSE;

PRIVATE SDL_Color pixel_to_color(Uint32 pixel)
{
	SDL_Color c = { 0, 0, 0, 0 };
	SDL_PixelFormat *fmt = get_pixel_format();

	if (fmt != NULL) {
		SDL_GetRGB(pixel, fmt, &c.r, &c.g, &c.b);
	}
	return (c);
}

PUBLIC int font_init(void)
{
	if (!font_ready) {
		if (TTF_Init() < 0) {
			fprintf(stderr, "font_init(): %s\n", TTF_GetError());
			return (-1);
		}
		font_ready = TRUE;
	}
	memset(fonts, 0, sizeof(fonts));
	next_font = 0;
	return (0);
}

PUBLIC void font_quit(void)
{
	if (font_ready) {
		free_all_fonts();
		TTF_Quit();
		font_ready = FALSE;
	}
}

PUBLIC int load_font(const char *filename, int point_size, int style,
		     Uint32 fg, Uint32 bg)
{
	TTF_Font *f;
	int n;

	if (!font_ready && font_init() != 0) {
		return (-1);
	}

	if (next_font >= MAX_FONTS) {
		fprintf(stderr, "load_font(): too many fonts.\n");
		return (-1);
	}

	n = next_font++;

	f = TTF_OpenFont(filename, point_size);
	if (f == NULL) {
		fprintf(stderr, "load_font(): can't open %s: %s\n",
			filename, TTF_GetError());
		/* keep the number used, so later numbers still match */
		memset(&fonts[n], 0, sizeof(glyphFont));
		return (n);
	}

	TTF_SetFontStyle(f, style);

	fonts[n].font = f;
	fonts[n].height = TTF_FontHeight(f);
	fonts[n].ascent = TTF_FontAscent(f);
	fonts[n].descent = TTF_FontDescent(f);
	fonts[n].lineSkip = TTF_FontLineSkip(f);
	fonts[n].fg = pixel_to_color(fg);
	fonts[n].bg = pixel_to_color(bg);

	return (n);
}

PRIVATE void sys_font_path(int sys_font, char *path, size_t len)
{
	if (sys_font < 0 || sys_font > MAX_SYS_FONT) {
		fprintf(stderr, "sys_font_path(): bad font number %d.\n",
			sys_font);
		sys_font = NIO_DEFAULT_FONT;
	}

	snprintf(path, len, "%s%s%s", get_install_dir(), FONT_DIR,
		 sys_font_file[sys_font]);
}

PUBLIC int load_sys_font(int sys_font, int point_size, int style,
			 Uint32 fg, Uint32 bg)
{
	char path[PATH_LEN];

	sys_font_path(sys_font, path, sizeof(path));
	return (load_font(path, point_size, style, fg, bg));
}

/* Open a system font outside the numbered table (see draw_resource_text). */
PUBLIC TTF_Font *open_sys_ttf(int sys_font, int point_size)
{
	char path[PATH_LEN];

	if (!font_ready && font_init() != 0) {
		return (NULL);
	}
	sys_font_path(sys_font, path, sizeof(path));
	return (TTF_OpenFont(path, point_size));
}

PUBLIC void free_font(int font_num)
{
	int i;

	if (font_num < 0 || font_num >= MAX_FONTS) {
		return;
	}

	if (fonts[font_num].font != NULL) {
		TTF_CloseFont(fonts[font_num].font);
	}
	memset(&fonts[font_num], 0, sizeof(glyphFont));

	/* start numbering over once nothing is loaded */
	for (i = 0; i < next_font; i++) {
		if (fonts[i].font != NULL) {
			return;
		}
	}
	next_font = 0;
}

PUBLIC void free_all_fonts(void)
{
	int i;

	for (i = 0; i < next_font; i++) {
		if (fonts[i].font != NULL) {
			TTF_CloseFont(fonts[i].font);
		}
		memset(&fonts[i], 0, sizeof(glyphFont));
	}
	next_font = 0;
}

PUBLIC glyphFont get_font(int font_num)
{
	glyphFont none;

	if (font_num < 0 || font_num >= MAX_FONTS) {
		memset(&none, 0, sizeof(none));
		return (none);
	}
	return (fonts[font_num]);
}
