#!/bin/sh

. ../build.sh

PROGNAME=d0

TAR_FILE=${PROGNAME}.${VERSION}_src_${BUILD}_${DATE}.tar

rm -f ${PROGNAME}

cd src
make indent
make clean

cd ../..

tar cvf ${TAR_FILE} ${PROGNAME}

gzip ${TAR_FILE}

scp ${TAR_FILE}.gz cnystrom@olenska.newio.org:/export/home/cnystrom/ftp/d0

