#/bin/sh

echo
echo Warning: You may need to be root to run this script properly
echo

PROG_NAMES="demo1 demo_apps edit example3 jukebox neko paint"

for progname in ${PROG_NAMES}
do
  echo
  echo "Installing ${progname}..."
  cd ${progname}
  make install
  cd ..
done

