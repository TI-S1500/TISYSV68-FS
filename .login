# .login  script for bsh and csh login

# Set preferred control characters
stty erase '^H' kill '^U' intr '^C' quit '^\' eof '^D' echoe echok tab3
# Set up pathname for user customized prompts
# setenv MLC /usr/ti/
# Set up defaults for dfm
setenv PRNT /usr/bin/lp
setenv SHOW /bin/show
setenv EDIT /usr/bin/tx
