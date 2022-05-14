# we got some C shell script here.
set path = ( /usr/lib/acct /bin /usr/local /usr/bin /usr/ti/prompts /etc)
set cdpath = ( . /usr/adm)
set me = ""
set pointer = "< >"
set prompt = "$CWD ! $pointer "
set ignoreeof
set history = 40
alias cd 'cd \!*; set prompt = "$CWD ! $pointer "'
alias h history
alias q logout
umask 2
