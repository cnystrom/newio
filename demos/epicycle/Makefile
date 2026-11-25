#
#   Makefile for epicycle
#

CC =  gcc

BIN = epicycle.nio

#LIB = -lnsl -lsocket # Solaris
LIB = -lnsl -lutil -lpthread $(shell sdl-config --libs) -lSDL_ttf

INCLUDES = \
	-I../../nio_lib \
	-I../../common \
	$(NULL)

CPPFLAGS = $(INCLUDES) -O -Wall -g -DDEBUG -DUNIX

OBJS =	\
	../../nio_lib/nio_lib.a \
	../../common/msg_lib/msg_lib.a \
	../../common/file_io_lib/file_io_lib.a \
	../../common/str_lib/str_lib.a \
	../../common/nio_log/nio_log.a \
	../../nio_lib/nio_lib.a \
	../../common/str_lib/str_lib.a \
	$(NULL)

all: $(BIN)

epicycle.nio:	epicycle.o epicode.o $(OBJS)
		$(CC) -o $@ epicycle.o epicode.o $(OBJS) $(LIB)

install:
	./install.sh

indent:
	indent -kr -i4 *.c

clean:
	rm -f *.o *.nio core *~

new: all install

epicycle.c : epicode.h

