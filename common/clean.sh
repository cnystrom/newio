#!/bin/sh

DIRS="nio_log str_lib file_io_lib sock_lib ssh2_lib msg_lib"

for DIRECTORY in ${DIRS}
do
	echo "Cleaning ${DIRECTORY}..."
	cd ${DIRECTORY}
	make clean
	cd ..
done

cd test
rm -f ssh_client
rm -f stdio_server
rm -f tcp_client
rm -f tcp_server
	
