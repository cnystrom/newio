/******************************************************************************
 *
 *    paint.c
 *
 *    Copyright (C) 2005-2007  Chris Nystrom
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
 *    E-Mail: cnystrom@newio.org
 *
 *    Soli Deo Gloria
 *
 */

#ifdef UNIX
#include <unistd.h>
#endif
#include "nio_lib.h"

void clear_screen(void);
void draw_pen_area();
void command_area(void);

color black;
color blue;
color brown;
color green;
color yellow;
color orange;
color red;
color violet;
color white;

int pen_size;

color current_color;

int mousex = -1, mousey = -1;
int mousedx = 0, mousedy = 0;

#define ABS(a)		(((a)<0) ? -(a) : (a))
#define SGN(a)		(((a)<0) ? -1 : 1)
void digline(int x1, int y1, int x2, int y2);

int main(int argc, char *argv[])
{
    int cls_flag = 1;
    int b1 = 0, b2 = 0, b3 = 0;
    int omousex = 0, omousey = 0;
    int key = 0;
    int b1old = 0;

    nio_app_init("paint_demo", "0.1");

    black = nio_get_color("black");
    blue = nio_get_color("blue");
    brown = nio_get_color("brown");
    green = nio_get_color("green");
    yellow = nio_get_color("yellow");
    orange = nio_get_color("orange");
    red = nio_get_color("red");
    violet = nio_get_color("violet");
    white = nio_get_color("white");

    nio_set_screen(640, 480, white);

    current_color = black;

    pen_size = 4;

    clear_screen();

    while (1) {
	SDL_Event event;

	if (nio_poll_event(&event)) {
	    switch (event.type) {
	    case SDL_MOUSEBUTTONDOWN:
		if (SDL_BUTTON_LEFT == event.button.button)
		    b1 = 1;
		if (SDL_BUTTON_MIDDLE == event.button.button)
		    b2 = 1;
		if (SDL_BUTTON_RIGHT == event.button.button)
		    b3 = 1;
		mousex = event.button.x;
		mousey = event.button.y;
		break;
	    case SDL_MOUSEBUTTONUP:
		if (SDL_BUTTON_LEFT == event.button.button)
		    b1 = 0;
		if (SDL_BUTTON_MIDDLE == event.button.button)
		    b2 = 0;
		if (SDL_BUTTON_RIGHT == event.button.button)
		    b3 = 0;
		mousex = event.button.x;
		mousey = event.button.y;
		break;
	    case SDL_MOUSEMOTION:
		b1 = (SDL_BUTTON(SDL_BUTTON_LEFT) &
		      event.motion.state) == SDL_BUTTON(SDL_BUTTON_LEFT);
		b2 = (SDL_BUTTON(SDL_BUTTON_MIDDLE) &
		      event.motion.state) == SDL_BUTTON(SDL_BUTTON_MIDDLE);
		b3 = (SDL_BUTTON(SDL_BUTTON_RIGHT) &
		      event.motion.state) == SDL_BUTTON(SDL_BUTTON_RIGHT);
		mousex = event.motion.x;
		mousey = event.motion.y;
		mousedx = event.motion.xrel;
		mousedy = event.motion.yrel;
		break;
	    case SDL_KEYDOWN:
		key = event.key.keysym.sym;
		break;
	    case SDL_KEYUP:
		key = 0;
		break;
	    case SDL_QUIT:
		key = ESC;
		break;
	    default:
		break;
	    }
	    if (b1 == 1) {
		if (mousex > 630)
		    mousex = 630;

		if (mousey > 470)
		    mousey = 470;

		if (mousex < 20) {
		    command_area();
		} else {
		    if (b1old == 0) {
			omousex = mousex;
			omousey = mousey;
			nio_draw_rectangle_rgb
			    (mousex, mousey,
			     pen_size, pen_size,
			     current_color, NO_ALPHA, FILL);
		    } else {
			if (ABS(mousedx) > 1 || ABS(mousedy) > 1) {
			    digline(omousex, omousey, mousex, mousey);
			} else {
			    nio_draw_rectangle_rgb
				(mousex,
				 mousey,
				 pen_size,
				 pen_size, current_color, NO_ALPHA, FILL);
			}
		    }
		    nio_paint();

		    omousex = mousex;
		    omousey = mousey;
		    // Draw first before clearing screen again.
		    cls_flag = 1;
		}
	    }
	    b1old = b1;

	    if (b2 == 1 || key == ' ') {
		if (cls_flag) {
		    clear_screen();
		}

		cls_flag = 0;
	    }

	    if (b3 == 1 || key == ESC) {
		nio_exit();
		exit(0);
	    }
	} else
	    nio_delay(1);

    }
}

void clear_screen(void)
{
    // draw color selector
    nio_clear_screen(white);
    nio_draw_rectangle_rgb(0, 0, 20, 20, black, NO_ALPHA, FILL);
    nio_draw_rectangle_rgb(0, 19, 20, 20, blue, NO_ALPHA, FILL);
    nio_draw_rectangle_rgb(0, 39, 20, 20, brown, NO_ALPHA, FILL);
    nio_draw_rectangle_rgb(0, 59, 20, 20, green, NO_ALPHA, FILL);
    nio_draw_rectangle_rgb(0, 79, 20, 20, yellow, NO_ALPHA, FILL);
    nio_draw_rectangle_rgb(0, 99, 20, 20, orange, NO_ALPHA, FILL);
    nio_draw_rectangle_rgb(0, 119, 20, 20, red, NO_ALPHA, FILL);
    nio_draw_rectangle_rgb(0, 139, 20, 20, violet, NO_ALPHA, FILL);

    // outline white box
    nio_draw_line_rgb(0, 159, 19, 159, black, NO_ALPHA);
    nio_draw_line_rgb(0, 179, 19, 179, black, NO_ALPHA);
    nio_draw_line_rgb(0, 159, 0, 179, black, NO_ALPHA);
    nio_draw_line_rgb(19, 159, 19, 179, black, NO_ALPHA);

    draw_pen_area();
}

void draw_pen_area(void)
{
    nio_draw_rectangle_rgb(0, 200, 21, 81, white, NO_ALPHA, FILL);

    if (nio_color_equal(current_color, white)) {
	nio_draw_rectangle_rgb((0 + 8), (220 - 12), 4, 4, black,
			       NO_ALPHA, FILL);
	nio_draw_rectangle_rgb((0 + 7), (240 - 13), 6, 6, black,
			       NO_ALPHA, FILL);
	nio_draw_rectangle_rgb((0 + 5), (260 - 15), 10, 10, black,
			       NO_ALPHA, FILL);
	nio_draw_rectangle_rgb((0 + 1), (280 - 19), 18, 18, black,
			       NO_ALPHA, FILL);
    }

    nio_draw_rectangle_rgb((0 + 9), (220 - 11), 2, 2, current_color,
			   NO_ALPHA, FILL);
    nio_draw_rectangle_rgb((0 + 8), (240 - 12), 4, 4, current_color,
			   NO_ALPHA, FILL);
    nio_draw_rectangle_rgb((0 + 6), (260 - 14), 8, 8, current_color,
			   NO_ALPHA, FILL);
    nio_draw_rectangle_rgb((0 + 2), (280 - 18), 16, 16, current_color,
			   NO_ALPHA, FILL);

    if (pen_size == 2) {
	nio_draw_line_rgb(0, 200, 19, 200, black, NO_ALPHA);
	nio_draw_line_rgb(0, 219, 19, 219, black, NO_ALPHA);
	nio_draw_line_rgb(0, 200, 0, 219, black, NO_ALPHA);
	nio_draw_line_rgb(19, 200, 19, 219, black, NO_ALPHA);
    } else if (pen_size == 4) {
	nio_draw_line_rgb(0, 220, 19, 220, black, NO_ALPHA);
	nio_draw_line_rgb(0, 239, 19, 239, black, NO_ALPHA);
	nio_draw_line_rgb(0, 220, 0, 239, black, NO_ALPHA);
	nio_draw_line_rgb(19, 220, 19, 239, black, NO_ALPHA);
    } else if (pen_size == 8) {
	nio_draw_line_rgb(0, 240, 19, 240, black, NO_ALPHA);
	nio_draw_line_rgb(0, 259, 19, 259, black, NO_ALPHA);
	nio_draw_line_rgb(0, 240, 0, 259, black, NO_ALPHA);
	nio_draw_line_rgb(19, 240, 19, 259, black, NO_ALPHA);
    } else {
	nio_draw_line_rgb(0, 260, 19, 260, black, NO_ALPHA);
	nio_draw_line_rgb(0, 279, 19, 279, black, NO_ALPHA);
	nio_draw_line_rgb(0, 260, 0, 279, black, NO_ALPHA);
	nio_draw_line_rgb(19, 260, 19, 279, black, NO_ALPHA);
    }

    nio_paint();
}

void command_area(void)
{
    if (mousey < 19) {
	current_color = black;
	draw_pen_area();
    } else if (mousey < 39) {
	current_color = blue;
	draw_pen_area();
    } else if (mousey < 59) {
	current_color = brown;
	draw_pen_area();
    } else if (mousey < 79) {
	current_color = green;
	draw_pen_area();
    } else if (mousey < 99) {
	current_color = yellow;
	draw_pen_area();
    } else if (mousey < 119) {
	current_color = orange;
	draw_pen_area();
    } else if (mousey < 139) {
	current_color = red;
	draw_pen_area();
    } else if (mousey < 159) {
	current_color = violet;
	draw_pen_area();
    } else if (mousey < 179) {
	current_color = white;
	draw_pen_area();
    } else if (mousey < 219 && mousey >= 200) {
	pen_size = 2;
	draw_pen_area();
    } else if (mousey < 239) {
	pen_size = 4;
	draw_pen_area();
    } else if (mousey < 259) {
	pen_size = 8;
	draw_pen_area();
    } else if (mousey < 279) {
	pen_size = 16;
	draw_pen_area();
    }
}

void digline(int x1, int y1, int x2, int y2)
{
    int d, x, y, ax, ay, sx, sy, dx, dy;
    dx = x2 - x1;
    ax = ABS(dx) << 1;
    sx = SGN(dx);
    dy = y2 - y1;
    ay = ABS(dy) << 1;
    sy = SGN(dy);
    x = x1;
    y = y1;
    if (ax > ay) {		/* x dominant */
	d = ay - (ax >> 1);
	for (;;) {
	    nio_draw_rectangle_rgb(x, y,
				   pen_size, pen_size,
				   current_color, NO_ALPHA, FILL);
	    if (x == x2)
		return;
	    if (d >= 0) {
		y += sy;
		d -= ax;
	    }
	    x += sx;
	    d += ay;
	}
    } else {			/* y dominant */
	d = ax - (ay >> 1);
	for (;;) {
	    nio_draw_rectangle_rgb(x, y,
				   pen_size, pen_size,
				   current_color, NO_ALPHA, FILL);
	    if (y == y2)
		return;
	    if (d >= 0) {
		x += sx;
		d -= ay;
	    }
	    y += sy;
	    d += ax;
	}
    }
}
