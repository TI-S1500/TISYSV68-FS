/*
   COPYRIGHT (c) 1986 TEXAS INSTRUMENTS, INCORPORATED.  ALL RIGHTS RESERVED.
*/
/*
static char *sccs_id = @(#)assert.h	1.1 86/05/15";
*/
/*	@(#)assert.h	1.4	*/
#ifdef NDEBUG
#define assert(EX)
#else
extern void _assert();
#define assert(EX) if (EX) ; else _assert("EX", __FILE__, __LINE__)
#endif
