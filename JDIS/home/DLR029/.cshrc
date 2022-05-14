#
# Initial users .cshrc script
# All of these commands are read each time a user starts up a new C Shell
# (csh) or Business Shell (bsh).
#
# Set up the search path
cd `pwd`
set path = ( . ~/bin /JDIS/PROG/CMN /usr/bin /bin /etc /util )
set history=40		# save last 40 commands
set uidname = `id | awk 'BEGIN {FS="("; RS=")"} NR==1 {print $2}'`
set prompt = "$CWD ($uidname) [\!] "
alias cd 'cd \!*;set prompt = "$CWD ($uidname) [\\!] "'
alias h		history
