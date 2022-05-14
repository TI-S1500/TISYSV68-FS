#
# Initial users .login script
# All of these commands are read once, and only once, whenever a user
# logs in and the shell is C Shell (csh) or Business Shell (bsh).
#
# set preferred control characters
stty erase '^H' intr '^C' kill '^U' quit '^\' eof '^D' echoe echok tab3
# Set up pathname for user customized prompts
# setenv MLC /usr/ti/
# Set up defaults for dfm
setenv PRNT /usr/bin/lp
setenv SHOW /bin/show
setenv EDIT /usr/bin/tx
