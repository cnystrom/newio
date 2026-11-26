/******************************************************************************
 *
 *    keysym.h
 *
 *    New original replacement, added 2026 after the previous third-party
 *    keysym.h was omitted from the published NewIO tree. This file is not
 *    derived from that source.
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

/*
 * NewIO key names. Programs that use nio_lib name keys NIOK_xxx; each one
 * is the SDL 1.2 key code of the same name (SDLK_xxx), which is what the
 * d0 client sends in a key event.
 */

#ifndef _NIO_keysym_h
#define _NIO_keysym_h

#include <SDL/SDL_keysym.h>

#define NIOK_UNKNOWN             SDLK_UNKNOWN
#define NIOK_FIRST               SDLK_FIRST
#define NIOK_BACKSPACE           SDLK_BACKSPACE
#define NIOK_TAB                 SDLK_TAB
#define NIOK_CLEAR               SDLK_CLEAR
#define NIOK_RETURN              SDLK_RETURN
#define NIOK_PAUSE               SDLK_PAUSE
#define NIOK_ESCAPE              SDLK_ESCAPE
#define NIOK_SPACE               SDLK_SPACE
#define NIOK_EXCLAIM             SDLK_EXCLAIM
#define NIOK_QUOTEDBL            SDLK_QUOTEDBL
#define NIOK_HASH                SDLK_HASH
#define NIOK_DOLLAR              SDLK_DOLLAR
#define NIOK_AMPERSAND           SDLK_AMPERSAND
#define NIOK_QUOTE               SDLK_QUOTE
#define NIOK_LEFTPAREN           SDLK_LEFTPAREN
#define NIOK_RIGHTPAREN          SDLK_RIGHTPAREN
#define NIOK_ASTERISK            SDLK_ASTERISK
#define NIOK_PLUS                SDLK_PLUS
#define NIOK_COMMA               SDLK_COMMA
#define NIOK_MINUS               SDLK_MINUS
#define NIOK_PERIOD              SDLK_PERIOD
#define NIOK_SLASH               SDLK_SLASH
#define NIOK_0                   SDLK_0
#define NIOK_1                   SDLK_1
#define NIOK_2                   SDLK_2
#define NIOK_3                   SDLK_3
#define NIOK_4                   SDLK_4
#define NIOK_5                   SDLK_5
#define NIOK_6                   SDLK_6
#define NIOK_7                   SDLK_7
#define NIOK_8                   SDLK_8
#define NIOK_9                   SDLK_9
#define NIOK_COLON               SDLK_COLON
#define NIOK_SEMICOLON           SDLK_SEMICOLON
#define NIOK_LESS                SDLK_LESS
#define NIOK_EQUALS              SDLK_EQUALS
#define NIOK_GREATER             SDLK_GREATER
#define NIOK_QUESTION            SDLK_QUESTION
#define NIOK_AT                  SDLK_AT
#define NIOK_LEFTBRACKET         SDLK_LEFTBRACKET
#define NIOK_BACKSLASH           SDLK_BACKSLASH
#define NIOK_RIGHTBRACKET        SDLK_RIGHTBRACKET
#define NIOK_CARET               SDLK_CARET
#define NIOK_UNDERSCORE          SDLK_UNDERSCORE
#define NIOK_BACKQUOTE           SDLK_BACKQUOTE
#define NIOK_a                   SDLK_a
#define NIOK_b                   SDLK_b
#define NIOK_c                   SDLK_c
#define NIOK_d                   SDLK_d
#define NIOK_e                   SDLK_e
#define NIOK_f                   SDLK_f
#define NIOK_g                   SDLK_g
#define NIOK_h                   SDLK_h
#define NIOK_i                   SDLK_i
#define NIOK_j                   SDLK_j
#define NIOK_k                   SDLK_k
#define NIOK_l                   SDLK_l
#define NIOK_m                   SDLK_m
#define NIOK_n                   SDLK_n
#define NIOK_o                   SDLK_o
#define NIOK_p                   SDLK_p
#define NIOK_q                   SDLK_q
#define NIOK_r                   SDLK_r
#define NIOK_s                   SDLK_s
#define NIOK_t                   SDLK_t
#define NIOK_u                   SDLK_u
#define NIOK_v                   SDLK_v
#define NIOK_w                   SDLK_w
#define NIOK_x                   SDLK_x
#define NIOK_y                   SDLK_y
#define NIOK_z                   SDLK_z
#define NIOK_DELETE              SDLK_DELETE
#define NIOK_WORLD_0             SDLK_WORLD_0
#define NIOK_WORLD_1             SDLK_WORLD_1
#define NIOK_WORLD_2             SDLK_WORLD_2
#define NIOK_WORLD_3             SDLK_WORLD_3
#define NIOK_WORLD_4             SDLK_WORLD_4
#define NIOK_WORLD_5             SDLK_WORLD_5
#define NIOK_WORLD_6             SDLK_WORLD_6
#define NIOK_WORLD_7             SDLK_WORLD_7
#define NIOK_WORLD_8             SDLK_WORLD_8
#define NIOK_WORLD_9             SDLK_WORLD_9
#define NIOK_WORLD_10            SDLK_WORLD_10
#define NIOK_WORLD_11            SDLK_WORLD_11
#define NIOK_WORLD_12            SDLK_WORLD_12
#define NIOK_WORLD_13            SDLK_WORLD_13
#define NIOK_WORLD_14            SDLK_WORLD_14
#define NIOK_WORLD_15            SDLK_WORLD_15
#define NIOK_WORLD_16            SDLK_WORLD_16
#define NIOK_WORLD_17            SDLK_WORLD_17
#define NIOK_WORLD_18            SDLK_WORLD_18
#define NIOK_WORLD_19            SDLK_WORLD_19
#define NIOK_WORLD_20            SDLK_WORLD_20
#define NIOK_WORLD_21            SDLK_WORLD_21
#define NIOK_WORLD_22            SDLK_WORLD_22
#define NIOK_WORLD_23            SDLK_WORLD_23
#define NIOK_WORLD_24            SDLK_WORLD_24
#define NIOK_WORLD_25            SDLK_WORLD_25
#define NIOK_WORLD_26            SDLK_WORLD_26
#define NIOK_WORLD_27            SDLK_WORLD_27
#define NIOK_WORLD_28            SDLK_WORLD_28
#define NIOK_WORLD_29            SDLK_WORLD_29
#define NIOK_WORLD_30            SDLK_WORLD_30
#define NIOK_WORLD_31            SDLK_WORLD_31
#define NIOK_WORLD_32            SDLK_WORLD_32
#define NIOK_WORLD_33            SDLK_WORLD_33
#define NIOK_WORLD_34            SDLK_WORLD_34
#define NIOK_WORLD_35            SDLK_WORLD_35
#define NIOK_WORLD_36            SDLK_WORLD_36
#define NIOK_WORLD_37            SDLK_WORLD_37
#define NIOK_WORLD_38            SDLK_WORLD_38
#define NIOK_WORLD_39            SDLK_WORLD_39
#define NIOK_WORLD_40            SDLK_WORLD_40
#define NIOK_WORLD_41            SDLK_WORLD_41
#define NIOK_WORLD_42            SDLK_WORLD_42
#define NIOK_WORLD_43            SDLK_WORLD_43
#define NIOK_WORLD_44            SDLK_WORLD_44
#define NIOK_WORLD_45            SDLK_WORLD_45
#define NIOK_WORLD_46            SDLK_WORLD_46
#define NIOK_WORLD_47            SDLK_WORLD_47
#define NIOK_WORLD_48            SDLK_WORLD_48
#define NIOK_WORLD_49            SDLK_WORLD_49
#define NIOK_WORLD_50            SDLK_WORLD_50
#define NIOK_WORLD_51            SDLK_WORLD_51
#define NIOK_WORLD_52            SDLK_WORLD_52
#define NIOK_WORLD_53            SDLK_WORLD_53
#define NIOK_WORLD_54            SDLK_WORLD_54
#define NIOK_WORLD_55            SDLK_WORLD_55
#define NIOK_WORLD_56            SDLK_WORLD_56
#define NIOK_WORLD_57            SDLK_WORLD_57
#define NIOK_WORLD_58            SDLK_WORLD_58
#define NIOK_WORLD_59            SDLK_WORLD_59
#define NIOK_WORLD_60            SDLK_WORLD_60
#define NIOK_WORLD_61            SDLK_WORLD_61
#define NIOK_WORLD_62            SDLK_WORLD_62
#define NIOK_WORLD_63            SDLK_WORLD_63
#define NIOK_WORLD_64            SDLK_WORLD_64
#define NIOK_WORLD_65            SDLK_WORLD_65
#define NIOK_WORLD_66            SDLK_WORLD_66
#define NIOK_WORLD_67            SDLK_WORLD_67
#define NIOK_WORLD_68            SDLK_WORLD_68
#define NIOK_WORLD_69            SDLK_WORLD_69
#define NIOK_WORLD_70            SDLK_WORLD_70
#define NIOK_WORLD_71            SDLK_WORLD_71
#define NIOK_WORLD_72            SDLK_WORLD_72
#define NIOK_WORLD_73            SDLK_WORLD_73
#define NIOK_WORLD_74            SDLK_WORLD_74
#define NIOK_WORLD_75            SDLK_WORLD_75
#define NIOK_WORLD_76            SDLK_WORLD_76
#define NIOK_WORLD_77            SDLK_WORLD_77
#define NIOK_WORLD_78            SDLK_WORLD_78
#define NIOK_WORLD_79            SDLK_WORLD_79
#define NIOK_WORLD_80            SDLK_WORLD_80
#define NIOK_WORLD_81            SDLK_WORLD_81
#define NIOK_WORLD_82            SDLK_WORLD_82
#define NIOK_WORLD_83            SDLK_WORLD_83
#define NIOK_WORLD_84            SDLK_WORLD_84
#define NIOK_WORLD_85            SDLK_WORLD_85
#define NIOK_WORLD_86            SDLK_WORLD_86
#define NIOK_WORLD_87            SDLK_WORLD_87
#define NIOK_WORLD_88            SDLK_WORLD_88
#define NIOK_WORLD_89            SDLK_WORLD_89
#define NIOK_WORLD_90            SDLK_WORLD_90
#define NIOK_WORLD_91            SDLK_WORLD_91
#define NIOK_WORLD_92            SDLK_WORLD_92
#define NIOK_WORLD_93            SDLK_WORLD_93
#define NIOK_WORLD_94            SDLK_WORLD_94
#define NIOK_WORLD_95            SDLK_WORLD_95
#define NIOK_KP0                 SDLK_KP0
#define NIOK_KP1                 SDLK_KP1
#define NIOK_KP2                 SDLK_KP2
#define NIOK_KP3                 SDLK_KP3
#define NIOK_KP4                 SDLK_KP4
#define NIOK_KP5                 SDLK_KP5
#define NIOK_KP6                 SDLK_KP6
#define NIOK_KP7                 SDLK_KP7
#define NIOK_KP8                 SDLK_KP8
#define NIOK_KP9                 SDLK_KP9
#define NIOK_KP_PERIOD           SDLK_KP_PERIOD
#define NIOK_KP_DIVIDE           SDLK_KP_DIVIDE
#define NIOK_KP_MULTIPLY         SDLK_KP_MULTIPLY
#define NIOK_KP_MINUS            SDLK_KP_MINUS
#define NIOK_KP_PLUS             SDLK_KP_PLUS
#define NIOK_KP_ENTER            SDLK_KP_ENTER
#define NIOK_KP_EQUALS           SDLK_KP_EQUALS
#define NIOK_UP                  SDLK_UP
#define NIOK_DOWN                SDLK_DOWN
#define NIOK_RIGHT               SDLK_RIGHT
#define NIOK_LEFT                SDLK_LEFT
#define NIOK_INSERT              SDLK_INSERT
#define NIOK_HOME                SDLK_HOME
#define NIOK_END                 SDLK_END
#define NIOK_PAGEUP              SDLK_PAGEUP
#define NIOK_PAGEDOWN            SDLK_PAGEDOWN
#define NIOK_F1                  SDLK_F1
#define NIOK_F2                  SDLK_F2
#define NIOK_F3                  SDLK_F3
#define NIOK_F4                  SDLK_F4
#define NIOK_F5                  SDLK_F5
#define NIOK_F6                  SDLK_F6
#define NIOK_F7                  SDLK_F7
#define NIOK_F8                  SDLK_F8
#define NIOK_F9                  SDLK_F9
#define NIOK_F10                 SDLK_F10
#define NIOK_F11                 SDLK_F11
#define NIOK_F12                 SDLK_F12
#define NIOK_F13                 SDLK_F13
#define NIOK_F14                 SDLK_F14
#define NIOK_F15                 SDLK_F15
#define NIOK_NUMLOCK             SDLK_NUMLOCK
#define NIOK_CAPSLOCK            SDLK_CAPSLOCK
#define NIOK_SCROLLOCK           SDLK_SCROLLOCK
#define NIOK_RSHIFT              SDLK_RSHIFT
#define NIOK_LSHIFT              SDLK_LSHIFT
#define NIOK_RCTRL               SDLK_RCTRL
#define NIOK_LCTRL               SDLK_LCTRL
#define NIOK_RALT                SDLK_RALT
#define NIOK_LALT                SDLK_LALT
#define NIOK_RMETA               SDLK_RMETA
#define NIOK_LMETA               SDLK_LMETA
#define NIOK_LSUPER              SDLK_LSUPER
#define NIOK_RSUPER              SDLK_RSUPER
#define NIOK_MODE                SDLK_MODE
#define NIOK_COMPOSE             SDLK_COMPOSE
#define NIOK_HELP                SDLK_HELP
#define NIOK_PRINT               SDLK_PRINT
#define NIOK_SYSREQ              SDLK_SYSREQ
#define NIOK_BREAK               SDLK_BREAK
#define NIOK_MENU                SDLK_MENU
#define NIOK_POWER               SDLK_POWER
#define NIOK_EURO                SDLK_EURO
#define NIOK_UNDO                SDLK_UNDO

#endif				/* _NIO_keysym_h */
