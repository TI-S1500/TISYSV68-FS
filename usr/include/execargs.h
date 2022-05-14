/*
   COPYRIGHT (c) 1986 TEXAS INSTRUMENTS, INCORPORATED.  ALL RIGHTS RESERVED.
*/
/*
static char *sccs_id = @(#)execargs.h	1.1 86/05/15";
*/
/*	@(#)execargs.h	1.2	*/
#if vax
char **execargs = (char**)(0x7ffffffc);
#endif

#if pdp11
char **execargs = (char**)(-2);
#endif

#if u3b || u3b5
/* empty till we can figure out what to do for the shell */
#endif

#if m68k
#if M68020	/* 32-bit addresses */
char **execargs = (char**)(0xfffffffc);
#else		/* 24-bit addresses */
char **execargs = (char**)(0xfffffc);
#endif
#endif
