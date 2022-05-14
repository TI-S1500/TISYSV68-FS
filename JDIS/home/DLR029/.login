#
# Initial users .login script
# All of these commands are read once, and only once, whenever a user
# logs in and the shell is C Shell (csh) or Business Shell (bsh).
#
# set preferred control characters
stty erase '^H' intr '^C' kill '^U' quit '^\' eof '^D'
#
# Verify terminal type.
if ($TERM == unknown) then
    echo "TERM = ($TERM) \c"
    set terminal = `head -1`
    if ($terminal != "") setenv TERM $terminal
    unset terminal
endif
#
# Set up defaults for dfm
setenv PRNT /usr/bin/dfmlp
setenv SHOW /bin/show
setenv EDIT /usr/bin/tx
#
# Exec aspen.
cd /JDIS/PROG/CMN; exec aspen
