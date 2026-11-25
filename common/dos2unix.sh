#!/bin/sh

echo
echo Conerting shell scripts...
echo
find . -name "*.sh" -exec dos2unix {} \;
find . -name "*.sh" -exec chmod +x {} \;

echo
echo Converting header files...
echo
find . -name *.h -exec dos2unix {} \;

echo
echo Converting c files...
echo
find . -name *.c -exec dos2unix {} \;

echo
echo Converting Makefiles...
echo
find . -name Makefile -exec dos2unix {} \;

