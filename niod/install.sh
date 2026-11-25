#!/bin/sh

echo
echo "This should be run as root..."
echo

. ../build.sh

if test -f /usr/local/etc/sshd_config
then
        echo "Config file found at /usr/local/etc/"
	CONFIG_DIR=/usr/local/etc
elif test -f /etc/sshd_config
then
        echo "Config file found at /etc/"
	CONFIG_DIR=/etc
elif test -f /etc/ssh/sshd_config
then
        echo "Config file found at /etc/ssh"
	CONFIG_DIR=/etc/ssh
else
	echo "sshd config file not found: aborting. Please call tech support"
	exit -1
fi

BIN_NAME=niod-${VERSION}_${BUILD}_${DATE}

mkdir -p /usr/local/libexec
cp niod /usr/local/libexec/${BIN_NAME}

echo "Subsystem newio /usr/local/libexec/${BIN_NAME}" >> ${CONFIG_DIR}/sshd_config

if test -f /sbin/service
then
	echo "Running /bin/service sshd restart"
	/sbin/service sshd restart
else
	echo "Running /etc/init.d/ssh restart"
	/etc/init.d/ssh restart
fi

LIB_DIR=/usr/local/nio/lib/system

mkdir -p ${LIB_DIR}
cp ../d0/fonts/*.ttf ${LIB_DIR}


