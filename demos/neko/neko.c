/******************************************************************************
 *
 *    neko.c
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
 *    E-Mail: cnystrom@gmail.com
 *
 *    Soli Deo Gloria
 *
 *    From:
 */

/*
JAVA NEKO V1.0,
   By Chris Parent, 1999

This source code is free to everyone. (Yahoo!!)

  This program loads in 32 images of neko, and tests them. (to show
you that they've been loaded)  Neko will chase you mouse cursor around the
applet.  Once she's over it and the mouse doesn't move she'll prepaire to take
a nap.  If the mouse go's outside the applet she will reach the border and try
to dig for it.  She'll eventually give up, and fall asleep.

                   --You must have 32 images, for this applet to work--

CURRENT FILE SETUP (Can be changed by programmer)

  /HTML file
  +-----/Neko (directory)
          +JavaNeko.class
          +-----/Images(directory)
                  +1 to 32.gif
OTHER PROGRAM NOTES:

     This applet searces for an applet parameter in you're HTML file called
   "COLOR".  You can put in the color of you're choice, in hexidecimal like
   "ffffff" which is the color white. This will be the background color of the
   applet.(The default is white)

     I used depreciated event handlers and methods, so this applet will run on
   the widest amount of web browsers.

     For effenciancy instead of decrementing and incrementing the variable no,
   like no++; or no--;, I instead specified next image like no=26; in the loop.
   Adding and subtracting takes to much time away from the thread.

THANKS
To the person or persons who created the images, Thank You!!!

*/

#include <math.h>
#ifdef UNIX
#include <unistd.h>
#endif
#include "nio_lib.h"

typedef int bool;

static int font;

void nio_loading(void)
{
    color black, white;

    black = nio_get_color("black");
    white = nio_get_color("white");

    font = nio_load_sys_font(NIO_MONO_BOLD,
			     NIO_DEFAULT_PTSIZE,
			     NIO_STYLE_NORMAL, black, white);

    nio_draw_text(font, 10, 10, "Loading resources...");

    nio_paint();
}

void nio_done_loading(void)
{
    nio_free_font(font);
}

#ifndef PI
#define PI (3.14)
#endif

#define OVER  (1)
#define UNDER (2)
#define LEFT  (3)
#define RIGHT (4)

// Cat position and image numbers
// Most images have 2 versions for animation
#define UP1          (0)
#define UP2          (1)
#define UP_RIGHT1    (2)
#define UP_RIGHT2    (3)
#define RIGHT1       (4)
#define RIGHT2       (5)
#define DOWN_RIGHT1  (6)
#define DOWN_RIGHT2  (7)
#define DOWN1        (8)
#define DOWN2        (9)
#define DOWN_LEFT1  (10)
#define DOWN_LEFT2  (11)
#define LEFT1       (12)
#define LEFT2       (13)
#define UP_LEFT1    (14)
#define UP_LEFT2    (15)
#define UP_EDGE1    (16)
#define UP_EDGE2    (17)
#define RIGHT_EDGE1 (18)
#define RIGHT_EDGE2 (19)
#define DOWN_EDGE1  (20)
#define DOWN_EDGE2  (21)
#define LEFT_EDGE1  (22)
#define LEFT_EDGE2  (23)
#define SIT         (24)
#define YAWN        (25)
#define SCRATCH1    (26)
#define SCRATCH2    (27)
#define SLEEP1      (28)
#define SLEEP2      (29)
#define LICK        (30)
#define WAKEUP      (31)
#define CURSOR      (32)

static int pos;			// Mouse's position in respect to the window
static int x, y;		// Mouse pos.
static int x2, y2;		// New Mouse pos.
static int ox, oy;		// Neko image pos.
static int dx, dy;		// Image-mouse distance
static int no;			// Image number.
static int ilc1;		// Image loop counter
static int ilc2;		// Second image loop counter
static bool move;		// Mouse move flag
static bool out;		// Mouse in window flag
static double theta;		// Image-mouse polar data
static double dist;		// Distance

static int height;		// Window height
static int width;		// Window width

static int font;
static color black;
static color white;
static int images[33];
static int sound0;

int main(int argc, char *argv[])
{
    nio_point p;

    nio_app_init("neko", "0.1");

    black = nio_get_color("black");
    white = nio_get_color("white");

    nio_set_screen(640, 480, white);

/*
	font = nio_load_sys_font(NIO_DEFAULT_FONT,
				 NIO_DEFAULT_PTSIZE,
				 NIO_STYLE_NORMAL, black, white);


	nio_term_init(font, white, 10, 10, 34, 80);

	nio_print_at(1, 1, "Downloading resources...");
*/

    nio_loading();

    nio_cursor(OFF);

    move = FALSE;
    out = FALSE;
    ilc1 = 0;
    ilc2 = 0;
    pos = 0;

    x = 320 - 8;
    y = 240 - 16;

    images[UP1] = nio_load_image("/usr/local/nio/lib/neko/1.GIF");
    images[UP2] = nio_load_image("/usr/local/nio/lib/neko/2.GIF");
    images[UP_RIGHT1] = nio_load_image("/usr/local/nio/lib/neko/3.GIF");
    images[UP_RIGHT2] = nio_load_image("/usr/local/nio/lib/neko/4.GIF");
    images[RIGHT1] = nio_load_image("/usr/local/nio/lib/neko/5.GIF");
    images[RIGHT2] = nio_load_image("/usr/local/nio/lib/neko/6.GIF");
    images[DOWN_RIGHT1] = nio_load_image("/usr/local/nio/lib/neko/7.GIF");
    images[DOWN_RIGHT2] = nio_load_image("/usr/local/nio/lib/neko/8.GIF");
    images[DOWN1] = nio_load_image("/usr/local/nio/lib/neko/9.GIF");
    images[DOWN2] = nio_load_image("/usr/local/nio/lib/neko/10.GIF");
    images[DOWN_LEFT1] = nio_load_image("/usr/local/nio/lib/neko/11.GIF");
    images[DOWN_LEFT2] = nio_load_image("/usr/local/nio/lib/neko/12.GIF");
    images[LEFT1] = nio_load_image("/usr/local/nio/lib/neko/13.GIF");
    images[LEFT2] = nio_load_image("/usr/local/nio/lib/neko/14.GIF");
    images[UP_LEFT1] = nio_load_image("/usr/local/nio/lib/neko/15.GIF");
    images[UP_LEFT2] = nio_load_image("/usr/local/nio/lib/neko/16.GIF");
    images[UP_EDGE1] = nio_load_image("/usr/local/nio/lib/neko/17.GIF");
    images[UP_EDGE2] = nio_load_image("/usr/local/nio/lib/neko/18.GIF");
    images[RIGHT_EDGE1] = nio_load_image("/usr/local/nio/lib/neko/19.GIF");
    images[RIGHT_EDGE2] = nio_load_image("/usr/local/nio/lib/neko/20.GIF");
    images[DOWN_EDGE1] = nio_load_image("/usr/local/nio/lib/neko/21.GIF");
    images[DOWN_EDGE2] = nio_load_image("/usr/local/nio/lib/neko/22.GIF");
    images[LEFT_EDGE1] = nio_load_image("/usr/local/nio/lib/neko/23.GIF");
    images[LEFT_EDGE2] = nio_load_image("/usr/local/nio/lib/neko/24.GIF");
    images[SIT] = nio_load_image("/usr/local/nio/lib/neko/25.GIF");
    images[YAWN] = nio_load_image("/usr/local/nio/lib/neko/26.GIF");
    images[SCRATCH1] = nio_load_image("/usr/local/nio/lib/neko/27.GIF");
    images[SCRATCH2] = nio_load_image("/usr/local/nio/lib/neko/28.GIF");
    images[SLEEP1] = nio_load_image("/usr/local/nio/lib/neko/29.GIF");
    images[SLEEP2] = nio_load_image("/usr/local/nio/lib/neko/30.GIF");
    images[LICK] = nio_load_image("/usr/local/nio/lib/neko/31.GIF");
    images[WAKEUP] = nio_load_image("/usr/local/nio/lib/neko/32.GIF");
    images[CURSOR] = nio_load_image("/usr/local/nio/lib/neko/cursor.jpg");

    sound0 = nio_load_sound("/usr/local/nio/lib/neko/catmeow.wav");

    nio_done_loading();

    nio_clear_screen(white);

    while (1) {

	int key;
	mouse_state ms;

	p = nio_get_screen_size();

	width = p.x;
	height = p.y;

	key = nio_get_key();
	ms = nio_mouse_state();

	if (ms.b1) {
	    nio_play_sound(sound0, 0);
	}

	if (ms.b3 || key == ESC) {
	    break;
	}

	x2 = ms.x;
	y2 = ms.y;


	move = FALSE;
	out = FALSE;

	// best I can do since SDL does not provide mouse events out
	// of window
	if (x2 == 0 || x2 == (width - 1) || y2 == 0 || y2 == (height - 1)) {
	    out = TRUE;
	}


	if (y2 < 32) {
	    y2 = 32;
	    pos = OVER;
	}

	if (y2 >= height - 2)
	    pos = UNDER;

	if (x2 < 16) {
	    x2 = 16;
	    pos = LEFT;
	}

	if (x2 >= width - 16) {
	    //              x2 = width - 16;
	    pos = RIGHT;
	}

	if ((x != x2) || (y != y2)) {
	    move = TRUE;
	    x = x2;
	    y = y2;
	}

	dx = x - ox;
	dy = oy - y;

	// Distance formula (from mouse to cat)
	dist = sqrt(dx * dx + dy * dy);

	// Angle from mouse to cat
	theta = atan2(dy, dx);


	// If moves cat 16 pixels...
	if (dist > 16) {

	    ox = (int) (ox + cos(theta) * 16);
	    oy = (int) (oy - sin(theta) * 16);
	    dist = dist - 16;

//   The following conditions determine what image should be shown.
//   There are two images for each action. For example if the cat's
//   going right, display the cat with open legs and then with close legs,
//   open, and so on.

	    // If right...
	    if (theta >= -PI / 8 && theta <= PI / 8)
		no = (no == RIGHT1) ? RIGHT2 : RIGHT1;

	    // If upper-right...
	    if (theta > PI / 8 && theta < 3 * PI / 8)
		no = (no == UP_RIGHT1) ? UP_RIGHT2 : UP_RIGHT1;

	    // If up...
	    if (theta >= 3 * PI / 8 && theta <= 5 * PI / 8)
		no = (no == UP1) ? UP2 : UP1;

	    // If upper-left...
	    if (theta > 5 * PI / 8 && theta < 7 * PI / 8)
		no = (no == UP_LEFT1) ? UP_LEFT2 : UP_LEFT1;

	    // If left...
	    if (theta >= 7 * PI / 8 || theta <= -7 * PI / 8)
		no = (no == LEFT1) ? LEFT2 : LEFT1;

	    // If bottom-left...
	    if (theta > -7 * PI / 8 && theta < -5 * PI / 8)
		no = (no == DOWN_LEFT1) ? DOWN_LEFT2 : DOWN_LEFT1;

	    // If down...
	    if (theta >= -5 * PI / 8 && theta <= -3 * PI / 8)
		no = (no == DOWN1) ? DOWN2 : DOWN1;

	    // If bottom-right...
	    if (theta > -3 * PI / 8 && theta < -PI / 8)
		no = (no == DOWN_RIGHT1) ? DOWN_RIGHT2 : DOWN_RIGHT1;

	    move = FALSE;

	} else {

	    // Mouse hasn't moved or the cat is over the mouse

	    switch (no) {
	    case SIT:		// <cat sit>
		// If the mouse is out side the applet
		if (out == TRUE) {
		    switch (pos) {
		    case OVER:
			no = UP_EDGE1;
			break;
		    case UNDER:
			no = DOWN_EDGE1;
			break;
		    case LEFT:
			no = LEFT_EDGE1;
			break;
		    case RIGHT:
			no = RIGHT_EDGE1;
			break;
		    default:
			no = LICK;
			break;
		    }
		    pos = 0;
		    break;
		}

		no = LICK;
		break;

		// The mouse is outside, above applet
	    case UP_EDGE1:
		// Show UP_EDGE images 6 times
		no = UP_EDGE2;
		ilc1++;
		if (ilc1 == 6) {
		    no = SCRATCH1;
		    ilc1 = 0;
		}
		break;

	    case UP_EDGE2:
		no = UP_EDGE1;
		break;

		// The mouse is outside, under applet
	    case DOWN_EDGE1:
		// Show DOWN_EDGE images 6 times
		no = DOWN_EDGE2;
		ilc1++;
		if (ilc1 == 6) {
		    no = SCRATCH1;
		    ilc1 = 0;
		}
		break;

	    case DOWN_EDGE2:
		no = DOWN_EDGE1;
		break;

		// The mouse is outside, left
	    case LEFT_EDGE1:
		// Show LEFT_EDGE images 6 times
		no = LEFT_EDGE2;
		ilc1++;
		if (ilc1 == 6) {
		    no = SCRATCH1;
		    ilc1 = 0;
		}
		break;

	    case LEFT_EDGE2:
		no = LEFT_EDGE1;
		break;

		// The mouse is outside, right
	    case RIGHT_EDGE1:
		// Show RIGHT_EDGE images 6 times
		no = RIGHT_EDGE2;
		ilc1++;
		if (ilc1 == 6) {
		    no = SCRATCH1;
		    ilc1 = 0;
		}
		break;

	    case RIGHT_EDGE2:
		no = RIGHT_EDGE1;
		break;

	    case LICK:		// Cat lick (6  times)
		no = SIT;
		ilc1++;
		if (ilc1 == 6) {
		    no = SCRATCH1;
		    ilc1 = 0;
		}
		break;

	    case SCRATCH1:
		no = SCRATCH2;
		break;		// Cat scratch images 4 times

	    case SCRATCH2:
		no = SCRATCH1;
		ilc2++;
		if (ilc2 == 4) {
		    no = YAWN;
		    ilc2 = 0;
		}
		break;

	    case YAWN:
		no = SLEEP1;
		break;

		// Cat sleeps forever unless mouse moves
	    case SLEEP1:
		no = SLEEP2;
		break;

	    case SLEEP2:
		no = SLEEP1;
		break;

	    default:
		no = SIT;
		break;
	    }

	    // Mouse moved. Wakup cat.
	    if (move == TRUE) {
		nio_play_sound(sound0, 0);
		no = WAKEUP;
		ilc1 = 0;
		ilc2 = 0;
		move = FALSE;
	    }
	}

	nio_clear_screen(white);
	nio_draw_image(images[no], ox - 16, oy - 32);
	nio_draw_image(images[CURSOR], ms.x, ms.y);
	nio_paint();

	usleep(200000);
    }

    nio_cursor(ON);
    nio_exit();
    exit(0);
}
