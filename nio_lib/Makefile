#
# Makefile for nio_lib.o
#

CC =  gcc

INCLUDES =	-I../common \
		-I../common/str_lib \
		-I../common/file_io_lib \
		-I../common/nio_log \
		-I../common/msg_lib \
		$(NULL)

CFLAGS = -O -Wall -g -DDEBUG -DUNIX $(INCLUDES) $(shell sdl-config --cflags)

all:		nio_lib.a

nio_lib.a:	nio_lib.c event.o keyboard.o mouse.o colors.o joystick.o rw_stdio.o font.o term.o nio_lib.h nio_font.h ../common/msg_lib/msg_lib.a
		$(CC) $(CFLAGS) -c nio_lib.c 
		rm -f nio_lib.a
		ar rcs nio_lib.a nio_lib.o rw_stdio.o font.o term.o keyboard.o mouse.o colors.o event.o joystick.o
		ranlib nio_lib.a

keyboard.o:	keyboard.c keyboard.h
		$(CC) $(CFLAGS) -c keyboard.c

joystick.o:	joystick.c joystick.h
		$(CC) $(CFLAGS) -c joystick.c

event.o:	event.c event.h
		$(CC) $(CFLAGS) -c event.c

#reply.o:	reply.c reply.h
#		$(CC) $(CFLAGS) -c reply.c

mouse.o:	mouse.c mouse.h
		$(CC) $(CFLAGS) -c mouse.c

colors.o:	colors.c colors.h
		$(CC) $(CFLAGS) -c colors.c

rw_stdio.o:	rw_stdio.c
		$(CC) $(CFLAGS) -c rw_stdio.c

font.o:		font.c font.h
		$(CC) $(CFLAGS) -c font.c

term.o:		term.c term.h
		$(CC) $(CFLAGS) -c term.c

indent:
		indent -kr -i4 *.h *.c

install:
		cp *.a ..
		cp *.h ..

clean:
		rm -f *.o *.a core .*.swp *~

