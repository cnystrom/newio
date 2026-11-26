/******************************************************************************
 *
 *    nio_font.h
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

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef _NIO_FONT_H
#define _NIO_FONT_H

#define NIO_MONO_BOLD_OBLIQUE 0
#define NIO_MONO_BOLD         1
#define NIO_MONO_OBLIQUE      2
#define NIO_MONO              3
#define NIO_SANS_BOLD_OBLIQUE 4
#define NIO_SANS_BOLD         5
#define NIO_SANS_OBLIQUE      6
#define NIO_SANS              7
#define NIO_SERIF_BOLD_ITALIC 8
#define NIO_SERIF_BOLD        9
#define NIO_SERIF_ITALIC      10
#define NIO_SERIF             11

#define MAX_FONT_NUM		11

#define NIO_DEFAULT_FONT	3
#define NIO_DEFAULT_PTSIZE	12

#define NIO_STYLE_NORMAL        (0x00)
#define NIO_STYLE_BOLD          (0x01)
#define NIO_STYLE_ITALIC        (0x02)
#define NIO_STYLE_UNDERLINE     (0x04)

#endif				/* _NIO_FONT_H */

#ifdef  __cplusplus
}
#endif
