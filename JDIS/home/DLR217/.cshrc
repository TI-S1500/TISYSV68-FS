#
# Initial users .cshrc script
# All of these commands are read each time a user starts up a new C Shell
# (csh) or Business Shell (bsh).

# Make sure that CWD is correct
cd `pwd`

# Set up the search path
set path = ( . ~/bin /JDIS/PROG/CMN /usr/bin /bin /etc /util )

# Enable history
set history=40
alias h		history

# Set prompt
set uidname = `id | awk 'BEGIN {FS="("; RS=")"} NR==1 {print $2}'`
set prompt = "$CWD ($uidname) [\!] "
alias cd 'cd \!*;set prompt = "$CWD ($uidname) [\\!] "'
