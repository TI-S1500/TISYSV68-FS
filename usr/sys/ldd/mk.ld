#@(#)umk.ld	1.1 (TI) 88/03/10
.SUFFIXES: .o .O
SHELL	=	/bin/sh
LDDINC	=	.
INCSYS	=	/usr/include
CFLAGS	=	-I$(LDDINC) -I$(INCSYS) 
GFLAGS	=	-s
TCLDFLG	=	-N -u _start -e _start
CCBLDFLG=	-a -r -N -u ttyinit -e ttyinit
CCBLIB	=	$(LDDINC)/lib/libccb.a /usr/lib/libcsvs.a
TCLIB	=	$(LDDINC)/lib/libtc.a /usr/lib/libcsvs.a
CCBIFILE=	ccbifile
TCIFILE	=	tcifile
CC	=	cc10
AS	=	as
CCBTARGET=	ccbld
TCTARGET=	tcld
TCOBJ	=	tcld.o
TCLDLIB	=	tcld.lib
CCBLDLIB=	ccbld.lib
IOSLIB	=	ios.lib
SYMOBJ	=	tcld.sym
USROBJ	=	
CONFO	=	cf/conf.$(OBJ) cf/linesw.$(OBJ)
 
ccb: $(CCBTARGET)
$(CCBTARGET): $(CCBLDLIB) $(CONFO) $(USROBJ)
	$(LD) $(CCBLDFLG) -o $(CCBTARGET) $(CCBIFILE) $(CONFO) $(CCBLDLIB) \
	$(USROBJ) $(CCBLIB)
	cp $(CCBTARGET) /etc/$(CCBTARGET)


tc: $(TCTARGET)
$(TCTARGET): $(TCOBJ)
	tcdlcvt $(TCOBJ) $(TCTARGET) $(SYMOBJ)
	cp $(TCTARGET) /etc/$(TCTARGET)

$(TCOBJ): $(IOSLIB) $(CONFO) $(TCLDLIB) $(USROBJ)
	$(LD) $(TCLDFLG) -o $(TCOBJ) $(TCIFILE) $(IOSLIB) $(CONFO) \
	$(USROBJ) $(TCLDLIB) $(TCLIB)
$(CONFO): $(CONFC)
	(cd $(@D); $(MAKE) $(@F))

.c.o .c.O .s.o .s.O:
	$(CC)   $(CFLAGS) -DTERMCON -c $<               && mv $*.o $*.O
	$(CC)	$(CFLAGS) -c $< 
	
#.c~.o .c~.O .c.o .c.O:
#	$(GET)	$(GFLAGS) -p $< > $*.c
#	$(CC)   $(CFLAGS) -DTERMCON -c $*.c &&  mv $*.o $*.O
#	$(CC)	$(CFLAGS) -c $*.c
#	-rm -f  $*.c
#.s~.o .s~.O .s.o .s.O:
#	$(GET)	$(GFLAGS) -p $< > $*.s
#	$(AS)	$*.s
#	cp $*.o $*.O
#	-rm -f $*.s
