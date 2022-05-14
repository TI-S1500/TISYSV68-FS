/*
   COPYRIGHT (c) 1986 TEXAS INSTRUMENTS, INCORPORATED.  ALL RIGHTS RESERVED.
*/
/*
static char *sccs_id = @(#)memory.h	1.1 86/05/15";
*/
/*	@(#)memory.h	1.2	*/
extern char
	*memccpy();
#ifndef _MEM_FUNC
#define _MEM_FUNC
extern char
	*memchr(),
	*memcpy(),
	*memset();
extern int memcmp();
#endif
