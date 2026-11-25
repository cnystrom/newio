#!/bin/sh

echo
echo Compiling common...
echo

cd common
./compile.sh

echo
echo Compiling niod...
echo

cd ../niod
make

echo
echo Compiling nio_lib
echo

cd ../nio_lib
make

echo
echo Compiling demos...
echo

cd ../demos
./compile.sh

