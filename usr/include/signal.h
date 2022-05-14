/*
   COPYRIGHT (c) 1986 TEXAS INSTRUMENTS, INCORPORATED.  ALL RIGHTS RESERVED.
*/
/*
static char *sccs_id = @(#)signal.h	1.5 88/03/17";
*/
/*	@(#)signal.h	1.1	*/
/*	3.0 SID #	1.3	*/
#include<sys/signal.h>

extern	void(*signal())();
extern  void(*sigset())();
