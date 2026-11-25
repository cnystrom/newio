#/bin/sh

echo
echo "Compiling nio_lib..."
cd ../nio_lib
make

cd ../demos

PROG_NAMES="bounce clickomania demo1 demo_apps edit epicycle example3 grav jukebox kaleidescope neko paint pong vazpac"

for progname in ${PROG_NAMES}
do
  echo
  echo "Compiling ${progname}..."
  cd ${progname}
  make
  cd ..
done

