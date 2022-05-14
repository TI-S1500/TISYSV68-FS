/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char sccsid[] = "@(#)sema.h	1.8 (TI) 89/09/19";
#endif	SCCSID

#define	TASBIT	0x8000
#define	UNLOCK	0x007f
#define	LOCKED	TASBIT
#define BLOCKOK 	1
#define NOBLOCK 	2
#define MUSTHAVE 	3
#define INTLEV 		4
#define PROCLEV		5

#ifdef SINGLECPU

#define	appdrivsema(W, X, Y, Z)	/* only needed so ALL compiles work */
#define	apvdrivsema(W, X)	/* only needed so ALL compiles work */
#define	spdrivlck(W, X)		/* only needed so ALL compiles work */
#define	svdrivlck(W)		/* only needed so ALL compiles work */
#define	appsema(X, Y)		/* only needed so ALL compiles work */
#define	apvsema(X)		/* only needed so ALL compiles work */
#define	apcpsema(X)	1	/* SUCCESS */
#define	apcvsema(X)	0	/* NO PROCESS waiting */
#define	spsema(X)		/* only needed so ALL compiles work */
#define	svsema(X)		/* only needed so ALL compiles work */

#else  /* multiple cpus */

#define	appdrivsema(W, X, Y, Z)	 pdrivsema(W, X, Y, Z)
#define	apvdrivsema(W, X)	 vdrivsema(W, X)
#define	appsema(X,Y)	psema(X,Y)
#define	apvsema(X)	vsema(X)
#define	apcpsema(X)	cpsema(X)
#define	apcvsema(X)	cvsema(X)
#define svsema(X)	*(short *) (X) = 0x7f

#define valusema(X) 	(((sema_t *)X)->val)
#define pvlsema(X) 	(((sema_t *)X)->pvl)

#endif
