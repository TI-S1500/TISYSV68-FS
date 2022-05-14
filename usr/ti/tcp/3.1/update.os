# @(#)update.os	1.2 93/02/09
#
# 	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1989.  ALL	
#	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.	
#	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT	
#	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND	
#	ASSOCIATED DOCUMENTATION.					

for=tcp
FOR=TCP
version=3.1
echo "Starting update of $FOR$version."

# CALLED BY: The Os update scripts. Called after OS update is complete
#	     and yet while special file system is still mounted.
# PURPOSE  : To install any patches to $FOR that may be shipped in the
#	     /usr/ti/$for/$version directory.
# REQUIRED : May be called as "sh -e $0" so any error will terminate
#	     the script. This must be turned off with "set +e" and 
#	     "set -e" around grep, expr or other cmds known to return 
#	     non-zero values.

set +e
instversion=${1:-`grep Release /etc/$for | cut -f7 -d' '`}
instversion=${instversion:-?.?}
set -e
echo "$FOR$instversion is currently installed."
if [ $version != $instversion ]; then
	echo "\nError: $0 is intended to update $FOR$version ONLY!\n"
	exit 1
fi

wd=/usr/ti/$for/$version
cd $wd

objects="inet.o arp.o ip.o ip_icmp.o llcloop.o rip.o slip.o socket.o \
	tcp.o udp.o vty.o ipmux.o"
filesneeded="$objects"

missing=
for file in $filesneeded; do
	if [ ! -f $file ]; then
		missing="$missing $file"
	fi
done
if [ -n "$missing" ]; then
	echo "missing files in `pwd` :"
	echo "$missing"
	exit 1
fi

# Delete "dummy" inet.o from io.lib.  No need to save it; osupdate
# already copied it from io.lib to /usr/sys/OLDinet.o.

set +e
if [ `ar -t /usr/sys/io.lib | grep -c inet.o` != 0 ]; then
	ar -d /usr/sys/io.lib inet.o
fi
set -e

# Create tcp.lib

ar -r /usr/sys/tcp.lib $objects

# Check if tcp.lib is included in /usr/sys/makefile LIBS macro

set +e
if [ `grep -c '^LIBS[	].*tcp.lib' /usr/sys/makefile` = 0 ]; then
	# add tcp.lib to list of included LIBS
	echo '/^LIBS/s/io.lib/tcp.lib io.lib/
w' | ed - /usr/sys/makefile > /dev/null
fi
set -e

echo "\n$FOR update complete.\n"
