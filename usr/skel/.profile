#
# Initial users .profile script
# .profile is read each time a Bourne Shell (sh) is started up, this
# includes both logging in and shell escapes.
#
# set preferred control characters
stty erase '^H' intr '^C' kill '^U' quit '^\' eof '^D' echoe echok tab3
# set up search path
PATH=/bin:/usr/bin:$HOME/bin:.
export PATH
# Set up pathname for user customized prompts
# MLC=/usr/ti/
# export MLC
# Set up defaults for dfm
PRNT=/usr/bin/dfmlp 
export PRNT
SHOW=/bin/show 
export SHOW
EDIT=/usr/bin/tx
export EDIT
