#@(#)update.os	1.25 92/10/16
#
# 	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1991.  ALL	
#	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.	
#	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT	
#	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND	
#	ASSOCIATED DOCUMENTATION.					

for=tcp 	# pathname for /usr/ti and /usr/ti/patch
FOR=TCP 	# name for display purposes
version=3.0	# version of $for to be patched by this script

echo "Updating $FOR$version ..."

# CALLED BY: The Os update scripts. Called after OS update is complete
#	     and yet while special file system is still mounted.
#	     Caller MUST pass in the cfg partitions that need to be
#	     updated for cband parms. Examples :
#	      setenv CBANDS "/dev/dsk/sys:cfg1"
#	      setenv CBANDS "/dev/dsk/sys:cfg1 /dev/dsk/sys:cfg2"
# PURPOSE  : To install any patches to $FOR that may be shipped in the
#	     /usr/ti/$for directory.
# REQUIRED : May be called as "sh -e $0" so any error will terminate
#	     the script. This must be turned off with "set +e" and 
#	     "set -e" around grep, expr or other cmds known to return 
#	     non-zero values. Another method to "hide" a non-zero return
#	     value is to imbed the cmd inside an if conditional.
# EXIT VALUES :
#	0 - OK
#	1 - not enough space to install
#	2 - all other fatal errors
ENOSP=1
FATAL=2

set +e
instversion=${1:-`grep Release /etc/$for | cut -f7 -d' '`}
instversion=${instversion:-?.?}
set -e

# Call exitall instead of exit do do cleanup in "$exitline"
exitline=
exitall() {
	eval "$exitline"
	exit $1
}

cleaniolib() {
	for x in `ar t io_lib | tr "\012"  " " `
	do 
	rm -f $x
	done
}

echo "$FOR$instversion is currently installed."
if [ $version != $instversion ]; then
	echo "\nError: $0 is intended to update $FOR$version ONLY!\n"
	exitall $FATAL
fi

# 1	PATCH REASON:
# replace wait3.o in libsocket.a so inetd will not print
# erroneous error messages in syslog about inetd and tftp.
# the real fix is that wait3.o was compiled with a newer
# version of wait.h that has the fill and endian swap for
# the wait union.

# 2	PATCH REASON:
# replace lmail.o which was broken by tcp patch 30009. It causes
# mail forwarded with "mail -F young@dsg" to send mail but the 
# body is ALWAYS just the char "F".

# 3	PATCH REASON:
# replace named.o which swalloed up calls to syslog. Fix in storage.c
# keeps fake openlog function from getting compiled in. Now, every time
# named is started, you should see a "restarted" syslog message.

# 4	PATCH REASON:
# replace removetcp so that when tcp is removed AND a new kernel
# is made WITHOUT tcp, the ipmux.o module in /usr/sys/io.lib
# will not be left since ld will see multiply-defined symbols
# due to the Joe Senner ipmux hooks were also places in inetd.o
# as part of the OS.

# 5	PATCH REASON:
# Provide documentation for /dev/senet in /etc/strcf.
# Since the man page does not mention it, at least doc it in the file!

# 6	PATCH REASON:
# Fix timing problem with slattach on multi-cpu systems
# Prevents SIOCGIFFLAG error during slattach
# Also: fix both slattach and setslip to understand /usr/etc is
# where commands are installed.

# 7	PATCH REASON:
# Fix slattach/detach to force user to be root and prevent 
# re-attaching to existing tty.

# 8	PATCH REASON:
# Fix term setting in installname to allow new term types for
# QUME terminal

# 9	PATCH REASON:
# Correct slip.o to make slip interfaces count by 2 in the
# output of tcpstat -S. This now aggrees with the interface
# name passed to sldetach. Changes sl0,sl1,sl2 into sl0,sl2,sl4 ...
# and so the code is not consistent.

# 10	PATCH REASON:
# strerr daemon used to get started (and killed) by /etc/tcp but
# now it is required earlier in boot by xnsd and is started by /etc/download
# Remove it from /etc/tcp (except if it is not already running)
# Also correct bug with CBANDS parm in this script.
# Also correct bug which assumes only 1 slink will be running - slattach
# can ALSO generate slink processes.

# 11	PATCH REASON:
# Remove comments from /etc/hosts.equiv - they are not supported

# 12 	PATCH REASON:
# misc fixes: a. correctly escape "$?" in change to /etc/tcp
# b. add line to remove /etc/arp_data
# c. modified tcp version from 3.0.0 to 3.0.1, ident from 3.23 to 3.25
# d. add vty.o from late-breaking scrform chaneg by Bill
# e. add ipmux changes in ipmux.o even though code is probably going to 
#    be obsoleted by route techniques.
# f. comment modifed in .cshrc and .profile when tcp modifies PATH

# 13 	PATCH REASON:
# more changes to make install and ez-update closer to identical
# added ip.o to get socket.h verison 1.12
# added several .o files that get signal.h 1.12 or wait3.o version
# These were not added before since the change in wait3.o was only needed
# by inetd since it was the only utility that used BOTH the return
# value and the update-arg value methods of returning values that the
# call to wait3 provides.
# Also added mod changes from install.scr for the /dev devices
# from 644 to 666 that paul put in.

wd=/usr/ti/$for/$version
cd $wd
archives="wait3.o"
archives2=`ar t io_lib | tr "\012" " " `
if [ -f io_lib ]; then
	# Bill's change did not update 3.0 dir - but I usually did
	# also add ip.o since there are some header file changes in 3.3.1 OS
	exitline=cleaniolib
	ar x io_lib 
fi

objects="inetd.o lmail.o named.o setslip.o netlogin.o telnet.o rlogind.o 
	rwho.o ftp.o rwhod.o ruptime.o telnetd.o logger.o routed.o 
	sendmail.o"
tools="commands io_lib"
scripts="removetcp settings strcf slattach sldetach installname"
filesneeded="$archives $archives2 $objects $tools $scripts"

missing=
for file in $filesneeded; do
	if [ ! -f $file ]; then
		missing="$missing $file"
	fi
done
if [ -n "$missing" ]; then
	echo "Missing files in `pwd` :"
	echo "$missing"
	exitall $FATAL
fi

if [ ! -d /usr/ti/patch ]; then 
	echo Creating /usr/ti/patch directory
	mkdir /usr/ti/patch
fi
patchlog() {
	# just echo a blank line if NO args
	if [ $# = 0 ]; then
		echo >> /usr/ti/patch/$for # BLANK line
	else
		echo "OS UPDATE:	$FOR$version	$@" >> /usr/ti/patch/$for
	fi
}
patchlog
patchlog "Starting update on `date`"

# Update scripts:
cp removetcp /usr/ti/$for
patchlog "updated /usr/ti/$for/removetcp"

# Merge new settings file with 'TCP/IP virtual terminals' line of
# existing settings file which the TCP install changed ZZVTYS to 20 or
# whatever the user specified.
vterms="`grep 'virtual terminals' /usr/ti/$for/settings`"
grep -v 'virtual terminals' settings > /usr/ti/$for/settings
echo "$vterms" >> /usr/ti/$for/settings
patchlog "updated /usr/ti/$for/settings"

if [ -f /.cshrc ]; then
	echo
	echo Adding /usr/etc to PATH for the super user...
	# See if already installed, either tcp3.1 OR tcp3.0 versions
	egrep -v 'added by TCP/IP|set path=.?\( /usr/etc \$path|set path=.?\( \$path /usr/etc' \
		/.cshrc > pathtemp$$ ; cp pathtemp$$ /.cshrc
	echo 'set path=( $path /usr/etc ) # added by TCP/IP' >> /.cshrc
fi

if [ -f /.profile ]; then
	echo
	echo Adding /usr/etc to PATH for the root user...
	# See if already installed, either tcp3.1 OR tcp3.0 versions
	egrep -v 'added by TCP/IP|PATH=/usr/etc:\$PATH|PATH=\$PATH:/usr/etc' \
		/.profile > pathtemp$$ ; cp pathtemp$$  /.profile
	echo 'PATH=$PATH:/usr/etc # added by TCP/IP' >> /.profile
fi
rm -f  pathtemp$$
patchlog "updated comments in /.cshrc and /.profile"

# We can't replace the strcf file - it has already been configured
# Actually re-install using any old tienet entries:
# First save old file in case there is a problem:
if [ ! -f /usr/ti/$for/strcf.old ]; then
	cp /etc/strcf /usr/ti/$for/strcf.old
fi
grep "^	tienet" /etc/strcf > tmp$$ # look for tienet lines beginning with tab
echo '}' | cat strcf tmp$$ - > /etc/strcf
rm -f tmp$$
sync
patchlog "updated comments in /etc/strcf"

cp slattach /usr/etc/slattach
patchlog "updated /usr/etc/slattach"

cp sldetach /usr/etc/sldetach
patchlog "updated /usr/etc/sldetach"

cp installname /usr/ti/tcp
patchlog "updated /usr/ti/tcp/installname"

# CBANDS is set by main script or some other caller for me
if [ -z "$CBANDS" ]; then
	echo "environment var CBANDS has not been set!"
	exitall $FATAL
else
	for cfg in $CBANDS; do
		cat /usr/ti/$for/settings | sh /usr/ti/$for/setcband $cfg
		patchlog "updated cband parms in : $cfg"
	done
fi

# We can't replace the /etc/tcp - it has already been configured
# so we edit the change in.
# First save old file in case there is a problem:
if [ ! -f /usr/ti/$for/tcp.old ]; then
	cp /etc/tcp /usr/ti/$for/tcp.old
fi
set +e # ignore edit errors which can occur if re-executing script
echo '/^PROCS=/s/ strerr//
/slnks/
.,+1c
	slnks=`ps -el | grep -c slink`
	if [ $slnks -ge 1 ]; then
.
/^	rm -f \/etc\/arp_data/d
/-x \/usr\/bin\/arp/i
	rm -f /etc/arp_data # cache file created by "arp -a"
.
/^#ident @(#)tcp.sh/c
#ident @(#)tcp.sh	3.25 92/03/06
.
/^#version = "@(#)tcp:/c
#version = "@(#)tcp:		TI-Sys-V-3.2 TCP/IP version 3.0.1	DATE: 03/06/92";
.
w
q' | ed - /etc/tcp > /dev/null # remove strerr from PROCS list 
set -e

# Replace strerr lines after "	# Daemon" with the following: 
cat << EOF > tcpfix
	# Daemons & other things -- edit as appropriate
	#
	ps -e | fgrep strerr > /dev/null 2>&1
	if [ \$? = 0 ]; then # already running - this should be true on OS 3.3.1
		: ##echo "(strerr already running) \c"
	else
		strerr > /dev/console 2>&1 &
		echo "strerr \c"
	fi


	#
EOF

csplit -s -f tcptmp /etc/tcp '/^	# Daemons /' \
			     '/^	# run these /'
cat tcptmp00 tcpfix tcptmp02 > /etc/tcp
rm -f tcpfix tcptmp00 tcptmp01 tcptmp02 

sync
patchlog "updated strerr handling in /etc/tcp"

# The old hosts.equiv file possibly saved from old release may have
# comments in it - they are NOT supported and can cause
# strange bugs in sendmail addr parsing. Remove comments.
if [ -s /etc/hosts.equiv ]; then
        echo 'Removing comments from /etc/hosts.equiv - they are not supported'
        echo 'g/^#/d
w
q' | ed - /etc/hosts.equiv > /dev/null
        sync
fi
patchlog "removed comments from /etc/hosts.equiv"

# The high performance Ethernet interface
# (LAN) should be shipped with OS - but make sure it is there
# It requires cband parms to support it. primitive.new and cband
# have been modified to force some minimum parms to get rid of
# the "out of streams" error message when /dev/senet exists and
# the system boots up and the new ethernet driver tries to open it.
#
if [ ! -c /dev/senet ]; then
	rm -f /dev/senet
	mknod /dev/senet c 54 74
	patchlog "created /dev/senet"
fi

# First archive directory changes :
libdir=/usr/lib
lib=libsocket.a
echo "Replacing $archives in archive $libdir/$lib"
for archive in $archives; do
	ar r $libdir/$lib $archive
done
patchlog "patched $archives in archive $libdir/$lib"


# Second archive directory changes :
libdir2=/usr/sys
lib2=io.lib
echo "Replacing $archives2 in archive $libdir2/$lib2"
for archive in $archives2; do
	ar r $libdir2/$lib2 $archive
done
patchlog "patched $archives2 in archive $libdir2/$lib2"


echo "\nInstalling new commands from objects :"
echo "$objects\n"

for obj in $objects; do
	cmd=`echo $obj | sed 's/\.o//'`
	echo "====== make $cmd ======"
	# KLUDGE: make of inetd.o also clobbers inetc.conf, services, etc.
	# so do make of inetd1 instead, this is NOT needed for tcp3.1
	if [ $cmd = inetd ]; then
		cmd=inetd1
	fi
	make -f commands SOCKET=socket_s CURSES=curses NSL=nsl_s CLIB=c_s \
			 mytty=/dev/null \
			 CRT0=/lib/crt1.o CRTN=/lib/crtn.o $cmd
	# log an entry into the patch log for $FOR.
	patchlog "patched $cmd"
done
# sendmail.o needs to be propagated to mailq & newaliases
rm -f /usr/bin/newaliases  /usr/bin/mailq
cp /usr/lib/sendmail  /usr/bin/mailq
cp /usr/lib/sendmail  /usr/bin/newaliases
chmod 666 /dev/llcloop /dev/slip
chmod 666 /dev/inet/arp /dev/inet/icmp /dev/inet/ip /dev/inet/rip

echo "======================="

eval "$exitline"
patchlog "OS update completed on `date`"

echo "\n$FOR update complete.\n"
