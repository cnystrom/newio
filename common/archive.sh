#!/bin/sh

DATE=070729

FILENAME=msg_lib-${DATE}

TAR_FILE=${FILENAME}.tar

./clean.sh

cd ..

tar cvf ${TAR_FILE} common

gzip ${TAR_FILE}

scp ${TAR_FILE}.gz apps.newio.org:~/ftp/d0-libs

