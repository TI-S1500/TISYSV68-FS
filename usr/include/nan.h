/*
   COPYRIGHT (c) 1986 TEXAS INSTRUMENTS, INCORPORATED.  ALL RIGHTS RESERVED.
*/
/*
static char *sccs_id = @(#)nan.h	1.3 88/04/06";
*/
/*	@(#)nan.h	1.3	*/
/* Handling of Not_a_Number's (only in IEEE floating-point standard) */

			/*   disable the KILLFPE function for  SVS  - 1.16  */
#define KILLFPE()	(void) kill(getpid(), 8)
#if u3b || u3b5 || m68k
#define NaN(X)	(((union { double d; struct { unsigned :1, e:11; } s; } \
			*)&X)->s.e == 0x7ff)
#define KILLNaN(X)	if (NaN(X)) KILLFPE()
#else
#define Nan(X)	0
#define KILLNaN(X)
#endif
