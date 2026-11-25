#!/bin/sh

echo
echo Cleaning common...
echo

cd common
./clean.sh

echo
echo Cleaning niod...
echo

cd ../niod
make clean

echo
echo Cleaning nio_lib
echo

cd ../nio_lib
make clean

echo
echo Cleaning demos
echo

cd ../demos
./clean.sh

echo
echo Cleaning d0...
echo

cd ..
rm d0/d0

cd d0/src
make clean


