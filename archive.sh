#!/bin/sh

. ./build.sh

PROGNAME=newio-${DATE}

echo "PROGNAME=${PROGNAME}"

TAR_FILE=${PROGNAME}.tar

echo "TAR_FILE=${TAR_FILE}"

./clean.sh 1>/dev/null

cd ..

echo "Current dir:"
pwd

echo "tar cvf ${TAR_FILE} ${PROGNAME}"
tar cvf ${TAR_FILE} ${PROGNAME}

gzip ${TAR_FILE}

#scp ${TAR_FILE}.gz cnystrom@apps.newio.org:~/ftp/newio

