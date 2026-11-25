#!/bin/sh
#
#    install-root.sh
#

PROGNAME=d0
LOCAL_DIR=/usr/local
SHARE_DIR=/usr/local/share/dnought

echo
echo This script install ${PROGNAME} in /usr/local
echo

echo
echo Checking Directories...

if [ ! -d ${LOCAL_DIR}/bin ]
then
  echo "mkdir -p ${LOCAL_DIR}/bin"
  mkdir mkdir -p ${LOCAL_DIR}/bin
fi

if [ ! -d ${SHARE_DIR} ]
then
  echo "mkdir -p ${SHARE_DIR}"
  mkdir -p ${SHARE_DIR}
fi

if [ ! -d ${SHARE_DIR}/fonts ]
then
  echo "mkdir -p ${SHARE_DIR}/fonts"
  mkdir mkdir -p ${SHARE_DIR}/fonts
fi

echo
echo Installing client and fonts...

echo "cp ${PROGNAME} ${LOCAL_DIR}/bin"
cp ${PROGNAME} ${LOCAL_DIR}/bin

echo "cp newio.wav ${SHARE_DIR}"
cp newio.wav ${SHARE_DIR}

echo "cd fonts"
cd fonts

echo "cp * ${SHARE_DIR}/fonts"
cp * ${SHARE_DIR}/fonts

echo
echo Done!
echo
