#!/bin/sh

. ../../build.sh

BIN_DIR=/usr/local/nio/${NEWIO_VERSION}/bin

LIB_DIR=/usr/local/nio/lib/edit

mkdir -p ${BIN_DIR}
cp *.nio ${BIN_DIR}

mkdir -p ${LIB_DIR}
cp *.png ${LIB_DIR}

