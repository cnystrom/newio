#!/bin/sh

VERSION=0.009
BUILD=004
DATE=020106

PROGNAME=example3

TAR_FILE=${PROGNAME}.${VERSION}_${BUILD}_${DATE}.tar

make indent
make clean

cd ..

tar cvf ${TAR_FILE} ${PROGNAME}

gzip ${TAR_FILE}

scp ${TAR_FILE}.gz cnystrom@olenska.newio.org:/export/home/cnystrom

