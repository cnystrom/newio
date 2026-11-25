#!/bin/sh

. ../build.sh

PROGNAME=d0

DISTRIB=${PROGNAME}.${VERSION}_bin_${BUILD}

cd src

make clean
make

cd ..

mkdir -p ../${DISTRIB}
cp ${PROGNAME} ../${DISTRIB}
cp *.wav ../${DISTRIB}
cp install*.sh ../${DISTRIB}

mkdir -p ../${DISTRIB}/fonts
cd fonts
cp * ../../${DISTRIB}/fonts

cd ../..

tar cvf ${DISTRIB}.tar ${DISTRIB}

gzip ${DISTRIB}.tar

scp ${DISTRIB}.tar.gz olenska.newio.org:/export/home/cnystrom/ftp/d0

