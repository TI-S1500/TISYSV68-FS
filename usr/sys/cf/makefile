#
#  /usr/sys/cf makefile for TI System V
# @(#)umakefile	1.5 88/03/24
#
# Note:
# If you happen to have portable C, then be sure to use XFLAGS.
# XFLAGS should be left undefined for svs C.
#
#XFLAGS	=	-DPCC -O

SHELL	=	/bin/sh
CFLAGS	=	-Dm68k -DKERNEL -DM68020 -DNU $(XFLAGS)
GFLAGS	=	-s
AS	=	mc68as

OBJECTS =	locore.o conf.o linesw.o ttyioctl.o

all:		$(OBJECTS)

