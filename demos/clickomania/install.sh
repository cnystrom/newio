#!/bin/sh

. ../../build.sh

BIN_DIR=/usr/local/nio/${NEWIO_VERSION}/bin

LIB_DIR=/usr/local/nio/lib/clickomania

mkdir -p ${BIN_DIR}

cp *.nio ${BIN_DIR}

mkdir -p ${LIB_DIR}

cp data/*.bmp ${LIB_DIR}
cp data/*.wav ${LIB_DIR}
cp data/*.png ${LIB_DIR}
cp data/*.ttf ${LIB_DIR}

