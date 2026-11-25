#!/bin/sh

DIRS="nio_log str_lib file_io_lib sock_lib ssh2_lib msg_lib"

for DIRECTORY in ${DIRS}
do
	echo "Compiling ${DIRECTORY}..."
	cd ${DIRECTORY}
	make
	cd ..
done

mkdir -p test

cd msg_lib/examples
make

cp server ../../test/tcp_server
cp server2 ../../test/stdio_server
cp client ../../test/tcp_client
cp client2 ../../test/ssh_client

cd ../../test
chmod +x tcp_server stdio_server tcp_client ssh_client
	
