#!/bin/sh

. ../../build.sh

BIN_DIR=/usr/local/nio/${NEWIO_VERSION}/bin

LIB_DIR=/usr/local/nio/lib

mkdir -p ${BIN_DIR}
cp *.nio ${BIN_DIR}

mkdir -p ${LIB_DIR}

mkdir -p ${LIB_DIR}/movie
cp *.mpg ${LIB_DIR}/movie

mkdir -p ${LIB_DIR}/bltsrc
cp repeat.jpg ${LIB_DIR}/bltsrc

mkdir -p ${LIB_DIR}/list
cp midas*.jpg ${LIB_DIR}/list

mkdir -p ${LIB_DIR}/startrek
cp *.jpg ${LIB_DIR}/startrek
cp *.wav ${LIB_DIR}/startrek

