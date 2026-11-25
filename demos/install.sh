#/bin/sh

echo
echo Warning: You may need to be root to run this script properly
echo

PROG_NAMES="bounce clickomania demo1 demo_apps edit epicycle example3 grav jukebox kaleidescope neko paint pong vazpac"

for progname in ${PROG_NAMES}
do
  echo
  echo "Installing ${progname}..."
  cd ${progname}
  make install
  cd ..
done

