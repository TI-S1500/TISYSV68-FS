# Netware 3.11 on OS 3.3.2 update script.  If OSupdate is use to
# update the system then this script will install a new /usr/sys/pwn.lib.
#
if [ -x pnw0001/install -a -r pnw0001/readme -a -r pnw0001/pnw.lib.332 ]
then
	mydir=`pwd`
	cd pnw0001; 
	(sh -xv install)
	myerror=$?
   	cd $mydir	
	exit $myerror
fi
