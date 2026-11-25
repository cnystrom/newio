#!/bin/sh

VERSION=0.09
BUILD=011
DATE=101106

PROGNAME=jukebox

TAR_FILE=${PROGNAME}.${VERSION}_src_${BUILD}_${DATE}.tar

make clean

cd ..

tar cvf ${TAR_FILE} ${PROGNAME}

gzip ${TAR_FILE}

scp ${TAR_FILE}.gz cnystrom@olenska.newio.org:/export/home/cnystrom

