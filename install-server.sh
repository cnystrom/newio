#!/bin/sh

echo
echo This should be run as root!
echo

. ./build.sh

cd niod
make install

cd ../demos
./install.sh

DIR_NAME=newio-${VERSION}_${BUILD}_${DATE}

cd /usr/local/nio

rm -f bin
echo "ln -s ${DIR_NAME}/bin bin"
ln -s ${DIR_NAME}/bin bin

