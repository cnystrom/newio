#/bin/sh

echo
echo "Cleaning nio_lib..."
cd ../nio_lib
make clean

cd ../demos

PROG_NAMES="bounce clickomania demo1 demo_apps edit example3 grav jukebox kaleidescope neko paint pong vazpac"

for progname in ${PROG_NAMES}
do
  echo
  echo "Cleaning ${progname}..."
  cd ${progname}
  make indent
  make clean
  cd ..
done

