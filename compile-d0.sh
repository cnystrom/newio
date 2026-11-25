#!/bin/sh

echo
echo Compiling common...
echo

cd common
./compile.sh

echo
echo Compiling d0...
echo

cd ../d0/src
make

