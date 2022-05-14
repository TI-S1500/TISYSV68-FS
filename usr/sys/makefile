#
# /usr/sys makefile for TI System V
#
# @(#)umakefile	1.14 90/10/05
#
SHELL	=	/bin/sh
LD	=	ld
LDFLAGS =	-Z -a -r -e _start
NM	=	nm
NMFLAGS =	-xev
VOLNAME =	sys
DEFLB   =       unx1

CONF	=	cf/locore.o cf/conf.o cf/linesw.o cf/ttyioctl.o
REV	=	rev.o
LIBS	=	nfs.lib io.lib os.lib vm.lib kdb.lib ml.lib \
		fs.lib os.lib io.lib fpu.lib
PRIM	=	primitive.new
STBMLIB =	stbm.lib
UNIX	=	unix.new
LCF	=	lcf

all:	$(UNIX) $(PRIM)

$(UNIX):	$(LCF) $(LIBS) $(REV) $(CONF)
	$(LD) $(LDFLAGS) $(LCF) -o $(UNIX) $(CONF) $(REV) $(LIBS)

$(PRIM): $(STBMLIB)
	$(LD) $(LDFLAGS) -u busint -o $(PRIM) $(STBMLIB)

$(CONF):
	(cd $(@D); $(MAKE) $(@F))

# install new kernel into a boot band.

unx2 unx3 :	$(UNIX) $(PRIM)
	bband -p $(PRIM) -d /dev/dsk/$(VOLNAME):$@ $(UNIX)

# install new kernel into default boot band.
default :	$(UNIX) $(PRIM)
	bband -p $(PRIM) -d /dev/dsk/$(VOLNAME):$(DEFLB) $(UNIX)

names:		$(UNIX)
	$(NM) $(NMFLAGS) $(UNIX) | fgrep extern > names

