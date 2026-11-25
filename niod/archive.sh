#!/bin/sh

. ../build.sh

TAR_FILE=niod.${VERSION}_src_${BUILD}_${DATE}.tar

make clean

cd ..

tar cvf ${TAR_FILE} niod

gzip ${TAR_FILE}

scp ${TAR_FILE}.gz cnystrom@olenska.newio.org:/export/home/cnystrom/ftp/niod

