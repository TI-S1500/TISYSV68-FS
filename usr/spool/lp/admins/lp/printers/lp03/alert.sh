#ident	"@(#)nlp:model/alert.proto	1.1"

export DATE; DATE='MM/DD/YY hh:mm:ss'
export LANG; LANG='USA'
export PATH; PATH='/bin:/etc:/usr/bin'
export TZ; TZ='CST6CDT'


cd /dev
ulimit 4000000
umask 002

AlErT () {
	2>&1 (
## YOUR COMMAND STARTS HERE -- DON'T TOUCH ABOVE!!
mail root
## YOUR COMMAND ENDS HERE -- DON'T TOUCH BELOW!!

	) <$1 1>${TmPsTdErR} || return 1
	return 0
}

TmPsTdErR=${TMPDIR:-/usr/tmp}/`/bin/uname`$$
trap 'rm -f ${TmPsTdErR}; exit 0' 0 1 2 15

while AlErT $1
do
	if [ 0 -le 0 ]
	then
		exit 0
	else
		TiCk=0
		while [ "${TiCk}" -lt 0 ]
		do
			TiCk=`expr "${TiCk}" + 1`
			sleep 60
		done
	fi
done

ec=$?
if [ "${ec}" -ne 0 ]
then
	{

		echo "
One of your print service alerts failed with exit code ${ec}.
The standard output and standard error were:
	"
		cat ${TmPsTdErR}
		echo '

The alert message is:
'
		cat $1

	} | mailx -s 'Failed print service alert' root
fi
