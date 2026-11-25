#!/bin/sh

. ../../build.sh

BIN_DIR=/usr/local/nio/${NEWIO_VERSION}/bin

LIB_DIR=/usr/local/nio/lib/bounce

mkdir -p ${BIN_DIR}

cp *.nio ${BIN_DIR}

mkdir -p ${LIB_DIR}

cp *.bmp ${LIB_DIR}
cp *.wav ${LIB_DIR}
cp *.ttf ${LIB_DIR}

