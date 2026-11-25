#!/bin/sh

VERSION=0.11
BUILD=060
DATE=111606

PROGNAME=demo_apps

TAR_FILE=${PROGNAME}.${VERSION}_${BUILD}_${DATE}.tar

make clean

cd ..

tar cvf ${TAR_FILE} ${PROGNAME}-${VERSION}

gzip ${TAR_FILE}

scp ${TAR_FILE}.gz cnystrom@olenska.newio.org:/export/home/cnystrom

