/******************************************************************************
 *
 *    text.c
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

PUBLIC void text_size(glyphFont * gf, const char *s, SDL_Rect * r)
{
	int w = 0, h = 0;

	if (gf != NULL && gf->font != NULL && s != NULL) {
		TTF_SizeText(gf->font, s, &w, &h);
	}
	r->x = 0;
	r->y = 0;
	r->w = w;
	r->h = h;
}

/* Draw s at x, y in the font's colors. The caller updates the screen. */
PUBLIC void draw_text(glyphFont * gf, const char *s, int x, int y)
{
	SDL_Surface *text;
	SDL_Rect r;

	if (gf == NULL || gf->font == NULL || s == NULL || s[0] == '\0') {
		return;
	}

	text = TTF_RenderText_Shaded(gf->font, s, gf->fg, gf->bg);
	if (text == NULL) {
		fprintf(stderr, "draw_text(): %s\n", TTF_GetError());
		return;
	}

	r.x = x;
	r.y = y;
	r.w = text->w;
	r.h = text->h;
	blit_screen(text, &r);
	SDL_FreeSurface(text);
}

/*
 * Show a one-line status message ("file...42%") across the top of the
 * window while a resource is sent. It uses its own font, outside the
 * numbered fonts, so the numbering programs see doesn't change.
 */
PUBLIC void draw_resource_text(const char *s)
{
	static TTF_Font *status_font = NULL;
	static int tried = FALSE;
	SDL_Color white = { 255, 255, 255, 0 };
	SDL_Color black = { 0, 0, 0, 0 };
	SDL_Surface *text;
	SDL_Rect r;
	int w;

	if (status_font == NULL && !tried) {
		tried = TRUE;
		status_font = open_sys_ttf(NIO_DEFAULT_FONT, NIO_DEFAULT_PTSIZE);
	}

	if (status_font == NULL || s == NULL) {
		return;
	}

	w = get_screen_width();
	if (w <= 0) {
		return;
	}

	r.x = 0;
	r.y = 0;
	r.w = w;
	r.h = TTF_FontLineSkip(status_font);
	fill_rect(&r, 0);

	text = TTF_RenderText_Shaded(status_font, s, white, black);
	if (text != NULL) {
		r.w = text->w;
		r.h = text->h;
		blit_screen(text, &r);
		SDL_FreeSurface(text);
	}
	update_rectangle(0, 0, w, TTF_FontLineSkip(status_font));
}
