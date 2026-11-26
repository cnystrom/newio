#/bin/sh

echo
echo "Compiling nio_lib..."
cd ../nio_lib
make

cd ../demos

PROG_NAMES="demo1 demo_apps edit example3 jukebox neko paint"

for progname in ${PROG_NAMES}
do
  echo
  echo "Compiling ${progname}..."
  cd ${progname}
  make
  cd ..
done

