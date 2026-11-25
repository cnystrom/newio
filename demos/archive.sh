#!/bin/sh

. ../build.sh

PROGNAME=demos

TAR_FILE=${PROGNAME}.${VERSION}_src_${BUILD}_${DATE}.tar

rm -f ${PROGNAME}

./clean.sh

cd ..

tar cvf ${TAR_FILE} ${PROGNAME}-${VERSION}

gzip ${TAR_FILE}

scp ${TAR_FILE}.gz cnystrom@olenska.newio.org:/export/home/cnystrom/ftp/nio_apps

