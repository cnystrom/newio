#
#   Makefile for niod
#

CC =  gcc

BIN = niod

#LIB = -lnsl -lsocket # Solaris
LIB = -lnsl -lutil

all: $(BIN)

INCLUDES =	-I../common \
		-I../common/nio_log \
		-I../common/file_io_lib \
		-I../common/str_lib \
		$(NULL)

LIB_PATHS =	-L../common/file_io_lib \
		-L../common/nio_log \
		-L../common/str_lib \
		$(NULL)

CFLAGS = -O -Wall -g -DDEBUG -DUNIX $(INCLUDES)

OBJS =	../common/file_io_lib/file_io_lib.a \
	../common/nio_log/nio_log.a \
	../common/str_lib/str_lib.a \
	$(NULL)

niod:		niod.o $(OBJS)
		$(CC) -o $@ niod.o $(INCLUDES) $(OBJS) $(LIB)

indent:
		dos2unix *.c
		indent -kr -i4 *.c

install:
		./install.sh

clean:
		rm -f *.o $(BIN) *.nio core *~

new: all install

