#!/bin/sh

. ../../build.sh

BIN_DIR=/usr/local/nio/${NEWIO_VERSION}/bin

LIB_DIR=/usr/local/nio/lib/demo1

mkdir -p ${BIN_DIR}
cp *.nio ${BIN_DIR}

mkdir -p ${LIB_DIR}
cp *.ogg ${LIB_DIR}

