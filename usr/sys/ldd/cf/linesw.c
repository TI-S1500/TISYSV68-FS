/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

static char sccsid[] = "@(#)linesw.c	1.1 (TI) 88/03/17";

#include "sys/types.h"
#include "sys/conf.h"

/*
 * Line Discipline Switch Table
 */

extern nulldev();
extern ttopen(), ttclose(), ttread(), ttwrite(), ttioctl(), ttin(), ttout();

/* order:	open close read write ioctl rxint txint modemint */

struct linesw linesw[] = {
/*0*/	ttopen,		ttclose,	ttread,		ttwrite,
		ttioctl,	ttin,		ttout,		nulldev
};

/* number on entries in linesw */
int	linecnt = sizeof(linesw)/sizeof(struct linesw);

/*
 * Virtual Terminal Switch Table
 */

struct termsw termsw[] =
{
/*0*/	nulldev,	nulldev,	nulldev,	/* tty */
};

/* number of entries in termsw */
int termcnt = sizeof(termsw)/sizeof(struct termsw);
