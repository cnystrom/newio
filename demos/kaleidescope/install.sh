#!/bin/sh

. ../../build.sh

BIN_DIR=/usr/local/nio/${NEWIO_VERSION}/bin

mkdir -p ${BIN_DIR}
cp *.nio ${BIN_DIR}

