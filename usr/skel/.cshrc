#
# Initial users .cshrc script
# All of these commands are read each time a user starts up a new C Shell
# (csh) or Business Shell (bsh).
#
# Set up the search path
set path = ( . /bin /usr/bin ~/bin /usr/ti/prompts )
set history=40		# save last 40 commands
set prompt = $CWD' [\!] '
alias cd 'cd \!*;set prompt = "$CWD [\\!] "'
alias q		exit
alias h		history
