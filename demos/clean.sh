#/bin/sh

echo
echo "Cleaning nio_lib..."
cd ../nio_lib
make clean

cd ../demos

PROG_NAMES="demo1 demo_apps edit example3 jukebox neko paint"

for progname in ${PROG_NAMES}
do
  echo
  echo "Cleaning ${progname}..."
  cd ${progname}
  make indent
  make clean
  cd ..
done

