/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char init_h[] = "@(#)init.h	1.12 (TI) 92/01/14";
#endif	SCCSID

/*	@(#)init.h	1.1	UNIX System V/68 */
extern int clkstart(),cinit(),binit(),errinit(),iinit(),fsinit(),inoinit();
extern int finit(),flckinit(), kdbinit(), strinit();
#ifdef X25_0
extern x25init();
#endif
#ifdef ST_0
extern	stinit();
#endif
#ifdef	VPM_0
extern	vpminit();
#endif
extern	rtcinit();	/* real time clock */
extern  lckdinit();
extern  initqueue();

/*	Array containing the addresses of the various initializing	*/
/*	routines executed by "main" at boot time.			*/

int (*init_tbl[])() = {
	inoinit,
	clkstart,
	cinit,
	binit,
	errinit,
	finit,
	fsinit,
	iinit,
	flckinit,
	kdbinit,
	strinit,
#ifdef	VPM_0
	vpminit,
#endif
#ifdef X25_0
	x25init,
#endif
#ifdef ST_0
	stinit,
#endif
	rtcinit,
	lckdinit,
	initqueue,
	0
};
