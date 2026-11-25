#!/bin/sh

FILE_NAME=songs.tar

wget ftp://ftp.newio.org/pub/nio_apps/jukebox/${FILE_NAME}.gz

gunzip ${FILE_NAME}.gz

cd ..

tar xvf songs/${FILE_NAME}

rm songs/${FILE_NAME}

