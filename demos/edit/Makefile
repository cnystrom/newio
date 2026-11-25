#
#   Makefile for demo1
#

INSTALL_DIR=/usr/local/nio/bin

CC =  gcc

BIN = edit.nio

#LIB = -lnsl -lsocket # Solaris
LIB = -lnsl -lutil -lpthread $(shell sdl-config --libs) -lSDL_ttf # Linux

INCLUDES = \
	-I../../nio_lib \
	-I../../common \
	$(NULL)

CFLAGS = $(INCLUDES) -O3 -Wall -g -DDEBUG -DUNIX

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

edit.nio:	edit.o $(OBJS)
		$(CC) -o $@ edit.o $(OBJS) $(LIB)

install:
	./install.sh

indent:
	indent -kr -i4 *.c

clean:
	rm -f *.o *.nio core *~

new: all install

