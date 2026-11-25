#
#   Makefile for nio_demo_apps
#

CC =  gcc

BIN = keys.nio list.nio screen.nio chars.nio boxes.nio dots.nio lines1.nio lines2.nio lines3.nio arcs.nio startrek.nio mouse.nio movie.nio resize.nio bltsrc.nio

#LIB = -lnsl -lsocket # Solaris
LIB = -lpthread $(shell sdl-config --libs) -lSDL_ttf

INCLUDES =	\
		-I../../nio_lib \
		-I../../common \
		-I../../common/str_lib \
		-I../../common/msg_lib \
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

start.nio:	start.o $(OBJS)
		$(CC) -o $@ start.o $(OBJS) $(LIB)

list.nio:	list.o $(OBJS)
		$(CC) -o $@ list.o $(OBJS) $(LIB)

chars.nio:	chars.o $(OBJS)
		$(CC) -o $@ chars.o $(OBJS) $(LIB)

boxes.nio:	boxes.o $(OBJS)
		$(CC) -o $@ boxes.o $(OBJS) $(LIB)

dots.nio:	dots.o $(OBJS)
		$(CC) -o $@ dots.o $(OBJS) $(LIB)

lines1.nio:	lines1.o $(OBJS)
		$(CC) -o $@ lines1.o $(OBJS) $(LIB)

lines2.nio:	lines2.o $(OBJS)
		$(CC) -o $@ lines2.o $(OBJS) $(LIB)

lines3.nio:	lines3.o $(OBJS)
		$(CC) -o $@ lines3.o $(OBJS) $(LIB)

arcs.nio:	arcs.o $(OBJS)
		$(CC) -o $@ arcs.o $(OBJS) $(LIB)

screen.nio:	screen.o $(OBJS)
		$(CC) -o $@ screen.o $(OBJS) $(LIB)

play.nio:	play.o $(OBJS)
		$(CC) -o $@ play.o $(OBJS) $(LIB)

keys.nio:	keys.o $(OBJS)
		$(CC) -o $@ keys.o $(OBJS) $(LIB)

mouse.nio:	mouse.o $(OBJS)
		$(CC) -o $@ mouse.o $(OBJS) $(LIB)

startrek.nio:	startrek.o $(OBJS)
		$(CC) -o $@ startrek.o $(OBJS) $(LIB)

movie.nio:	movie.o $(OBJS)
		$(CC) -o $@ movie.o $(OBJS) $(LIB)

resize.nio:	resize.o $(OBJS)
		$(CC) -o $@ resize.o $(OBJS) $(LIB)

bltsrc.nio:	bltsrc.o $(OBJS)
		$(CC) -o $@ bltsrc.o $(OBJS) $(LIB)

indent:
		indent -kr -i4 *.c

install:
		./install.sh

clean:
		rm -f *.o *.nio core *~ .*.swp

new: all install

