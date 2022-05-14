#
# Initial users .login script
# All of these commands are read once, and only once, whenever a user
# logs in and the shell is C Shell (csh) or Business Shell (bsh).

# set preferred control characters
stty erase '^H' intr '^C' kill '^U' quit '^\' eof '^D'

# Verify terminal type.
echo "TERM = ($TERM) \c"
set terminal = `head -1`
if ($terminal != "") setenv TERM $terminal
unset terminal

# Start print screen process.
if (($TERM == t1 || $TERM == x1) && `tty` != /dev/console) then
#   setenv PSCRN lp02
    pdmon &
endif

# Set up defaults for dfm
setenv PRNT /usr/bin/dfmlp
setenv SHOW /bin/show
setenv EDIT /usr/bin/tx
