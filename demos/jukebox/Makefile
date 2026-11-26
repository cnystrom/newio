#
#   Makefile for jukebox
#

CC =  gcc

BIN = jukebox.nio

#LIB = -lnsl -lsocket # Solaris
LIB = -lutil -lpthread $(shell sdl-config --libs)	-lSDL_ttf
#LIB = -lpthread

INCLUDES = \
	-I../../nio_lib \
	-I../../common \
	$(NULL)

CFLAGS = $(INCLUDES) -O -Wall -g -DDEBUG -DUNIX

OBJS =	\
	../../nio_lib/nio_lib.a \
	../../common/nio_log/nio_log.a \
	../../common/str_lib/str_lib.a \
	../../common/file_io_lib/file_io_lib.a \
	../../common/msg_lib/msg_lib.a \
	../../nio_lib/nio_lib.a \
	../../common/str_lib/str_lib.a \
	$(NULL)

all: $(BIN)

jukebox.nio:	jukebox.o $(OBJS)
		$(CC) -o $@ jukebox.o $(OBJS) $(LIB)

install:
	./install.sh

indent:
	indent -kr -i4 *.c

clean:
	rm -f *.o *.nio core *~
	cd songs; rm -f *.ogg

new: all install

