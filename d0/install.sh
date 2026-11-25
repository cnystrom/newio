#!/bin/sh
#
#    dnought install script
#
#    install.sh
#

PROGNAME=d0
DNOUGHT_DIR=${HOME}/.${PROGNAME}

echo
echo This script installs ${PROGNAME} in your home directory...
echo

echo
echo Checking Directories...

if [ ! -d ${HOME}/bin ]
then
  echo "mkdir -p ${HOME}/bin"
  mkdir -p ${HOME}/bin
fi

if [ ! -d ${DNOUGHT_DIR} ]
then
  echo "mkdir -p ${DNOUGHT_DIR}"
  mkdir -p ${DNOUGHT_DIR}
fi

if [ ! -d ${DNOUGHT_DIR}/fonts ]
then
  echo "mkdir -p ${DNOUGHT_DIR}/fonts"
  mkdir mkdir -p ${DNOUGHT_DIR}/fonts
fi

echo
echo Installing client and fonts...

echo "cp ${PROGNAME} ${HOME}/bin"
cp ${PROGNAME} ${HOME}/bin

echo "cp newio.wav ${DNOUGHT_DIR}"
cp newio.wav ${DNOUGHT_DIR}

echo "cd fonts"
cd fonts

echo "cp * ${DNOUGHT_DIR}/fonts"
cp * ${DNOUGHT_DIR}/fonts

echo
echo You may want to put:
echo
echo "    ${HOME}/bin"
echo
echo in your path, if it is not already.
echo
echo Done!
echo
