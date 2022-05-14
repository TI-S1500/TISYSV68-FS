/*
   COPYRIGHT (c) 1986 TEXAS INSTRUMENTS, INCORPORATED.  ALL RIGHTS RESERVED.
*/
/*
static char *sccs_id = @(#)core.h	1.1 86/05/15";
*/
/*	@(#)core.h	1.2.1.1	*/
/* machine dependent stuff for core files */

#if vax
#define TXTRNDSIZ 512L
#define stacktop(siz) (0x80000000L)
#define stackbas(siz) (0x80000000L-siz)
#endif

#if pdp11
#define TXTRNDSIZ 8192L
#define stacktop(siz) (0x10000L)
#define stackbas(siz) (0x10000L-siz)
#endif


#if u3b
#define TXTRNDSIZ 0x20000
#define stacktop(siz) 0xF00000
#define stackbas(siz) (0xF00000 + siz)
#endif

#if u3b5
#define TXTRNDSIZ 2048L
#define stacktop(siz) (0xF00000 + siz)
#define stackbas(siz) 0xF00000
#endif

#if m68k
#define TXTRNDSIZ 512L
#if M68020	/* 32-bit addresses */
#define stacktop(siz) (0xffffffffL)	/* can't represent 2^32 */
#define stackbas(siz) (-siz)		/* 2^32 - siz */
#else		/* 24-bit addresses */
#define stacktop(siz) (0x1000000L)
#define stackbas(siz) (0x1000000L-siz)
#endif
#endif
