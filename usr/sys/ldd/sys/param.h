/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

/* @(#)param.h	1.2 89/12/01 */

/*
 * fundamental variables
 * don't change too often
 */

#define	CANBSIZ	256		/* max size of typewriter line	*/
#define	HZ	20		/* Ticks/second of the clock */
#define TIMEZONE (6*60)		/* Minutes westward from Greenwich */
#define	NCARGS	5120		/* # characters in exec arglist */
/*
 * priorities
 * should not be altered too much
 */

#define	PMASK	0177
#define	PCATCH	0400
#define	ICATCH	0800
#define	PSWP	0
#define	PINOD	10
#define	PRIBIO	20
#define	PZERO	25
#define	NZERO	20
#define	PPIPE	26
#define	PWAIT	30
#define	PSLEP	39
#define	PUSER	60
#define	PIDLE	127

#define	NULL	0
#define	CMASK	0		/* default mask for file creation */

#define	lobyte(X)	(((unsigned char *)&X)[1])
#define	hibyte(X)	(((unsigned char *)&X)[0])
#define	loword(X)	(((ushort *)&X)[1])
#define	hiword(X)	(((ushort *)&X)[0])

/*
 * Handy function return values.
 */
#define	OK	(0)
#define ERR	(-1)

