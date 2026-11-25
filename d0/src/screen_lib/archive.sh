#!/bin/sh

. ../build.sh

FILENAME=screen_lib

TAR_FILE=${FILENAME}.${VERSION}_${BUILD}_${DATE}.tar

make clean

cd ..

tar cvf ${TAR_FILE} ${FILENAME}

gzip ${TAR_FILE}

scp ${TAR_FILE}.gz olenska.newio.org:/export/home/cnystrom

