#ident	"@(#)nlp:model/alert.proto	1.1"

export ASPEN_HOME; ASPEN_HOME='/JDIS/PROG/CMN/'
export AUTHNO; AUTHNO='25991'
export BF; BF='N'
export COBOL; COBOL='/JDIS/PROG/CMN/runcobol'
export COBOL_SUFFIX; COBOL_SUFFIX='.COB'
export COMM_ONLY; COMM_ONLY='N'
export CWD; CWD='/JDIS/PROG/CMN'
export D1; D1='/JDIS/DATA/'
export D2; D2='/JDIS/DATA/'
export D3; D3='/JDIS/DATA/'
export DATE; DATE='MM/DD/YY hh:mm:ss'
export DELAY_3270; DELAY_3270='10'
export DEOP; DEOP='NO'
export DLR_POLL; DLR_POLL='/dev/tty00 2400 o=1.2,3.2,17.3,18.1,19.3,14.1,20.3,30.1'
export EDIT; EDIT='/usr/bin/tx'
export EXEC; EXEC='/usr/bin/line_config'
export FP_POLL; FP_POLL='/dev/tty00 1200 o=1.2,2.3,3.1,17.3,18.1,19.3,14.1,20.3,30.1'
export FRSTD; FRSTD='/JDIS/PROG/'
export GOBEGBAK; GOBEGBAK='2000'
export HOME; HOME='/JDIS/home/DLR001'
export IPADDR; IPADDR=''
export LANG; LANG='USA'
export LINKTIME; LINKTIME='Wed Apr 26 05:43:10 1995'
export LOGNAME; LOGNAME='DLR001'
export MAIL; MAIL='/usr/mail/DLR001'
export MAINMENU; MAINMENU='MAINMENU'
export MENUHEAD; MENUHEAD='Meyer Implement Inc'
export MIPLIMIT; MIPLIMIT='20000'
export MODE; MODE='""'
export MSCOM1; MSCOM1='/JDIS/PROG/'
export OS; OS='TI_UNIX'
export PATH; PATH=':~/bin:/JDIS/PROG/CMN:/usr/bin:/bin:/etc:/util'
export POLLFUNC; POLLFUNC='DPOLL'
export POLL_DIR; POLL_DIR='/JDIS/PROG/COMM'
export POST_POLL; POST_POLL='/dev/tty00 2400 o=30.1'
export PRCBK1; PRCBK1='/JDIS/PROG/'
export PRE_POLL; PRE_POLL='/dev/tty00 1200 o=1.2,2.3,3.1,14.1,17.5,18.1,19.2,20.2,30.2,31.2'
export PRNT; PRNT='/usr/bin/dfmlp'
export PROMPT_VAL; PROMPT_VAL='ST08 Enter Selection:'
export PRT1; PRT1='LP$01'
export PRT2; PRT2='LP01'
export PS1; PS1='# '
export PSCRN; PSCRN='lp01'
export RUNPATH; RUNPATH='/JDIS/PROG/CMN'
export RUN_PROG; RUN_PROG='/JDIS/PROG/'
export SESSION_DIR; SESSION_DIR='P00182'
export SESSION_NO; SESSION_NO='01'
export SHELL; SHELL='/bin/csh'
export SHOW; SHOW='/bin/show'
export SPOOL; SPOOL='/JDIS/SPOOL/'
export START; START='WARM'
export STATION; STATION='/JDIS/station/'
export ST_DIR; ST_DIR='/JDIS/station/st08/P00182/'
export SYSRC; SYSRC='0'
export TERM; TERM='x1'
export TERMNO; TERMNO='08'
export TMPDIR; TMPDIR='/JDIS/tmp'
export TPDV; TPDV='1'
export TRNFIL; TRNFIL='/JDIS/DATA/MF/TRNOUT'
export TZ; TZ='CST6CDT'
export USERID; USERID='DLR001'
export USERTERM; USERTERM='tty06'
export USERTTY; USERTTY='tty06'
export US_RETAIL; US_RETAIL='Y'
export Z1; Z1='/JDIS/ZRUNTIME'


cd /JDIS/PROG/CMN
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
