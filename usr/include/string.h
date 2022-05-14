/*
   COPYRIGHT (c) 1986 TEXAS INSTRUMENTS, INCORPORATED.  ALL RIGHTS RESERVED.
*/
/*
static char *sccs_id = @(#)string.h	1.2 91/08/12";
*/
/*	@(#)string.h	1.2	*/
#ifndef _STRING_FUNC
#define _STRING_FUNC
extern char
	*strcpy(),
	*strncpy(),
	*strcat(),
	*strncat(),
	*strchr(),
	*strrchr(),
	*strpbrk(),
	*strtok();
extern int
	strcmp(),
	strncmp(),
	strlen(),
	strspn(),
	strcspn();
#endif /* _STRING_FUNC */
