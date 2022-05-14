#
#  /usr/sys/ldd/cf makefile for TI System V
# @(#)umakefile	1.1 (TI) 88/03/10
#
#
.SUFFIXES: .o .O
SHELL	=	/bin/sh
INCLUDE =	-I..
CFLAGS	=	$(INCLUDE)
GFLAGS	=	-s
CC	=	cc10

FILES	=	conf.c linesw.c 
OBJECTS =	conf.$(OBJ) linesw.$(OBJ)

all:		$(OBJECTS)

.c.o .c.O:
	$(CC)   $(CFLAGS) -DTERMCON -c $<               && mv $*.o $*.O
	$(CC)	$(CFLAGS) -c $< 
