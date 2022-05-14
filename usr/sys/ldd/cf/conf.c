/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1984.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

static char sccsid[] = "@(#)conf.c	1.2 (TI) 88/03/23";

#include 	"sys/types.h"
#include	"sys/systm.h"
#include	"sys/conf.h"
#include	"sys/tty.h"

/*
 *  CCB Configurable Parameters
 */

#define	NCLIST	400

extern nulldev();
extern drtopen(), drtclose(), drtread(), drtwrite(), drtioctl();

struct cdevsw cdevsw[] =
{
/* mjr	open,		close,		read,		write,		ioctl,     	tty structure	 */

/* 0*/	nulldev,		nulldev,	nulldev,		nulldev,	nulldev,	0,
/* 1*/	drtopen,		drtclose,	drtread,		drtwrite,	drtioctl,   	0,
};

int	cdevcnt = sizeof(cdevsw)/sizeof(struct cdevsw);

/* add any line discipline initialization entries here */
int (*dev_init[])() = {
	0
};

/*
   enb_printf is the variable that enables printfs on a CCB or TC. The following
   is a breakout of assigned values verses meaning.
			enb_printf = 0  printfs are disabled(NOP).
			enb_printf = 1  printfs are enabled
			enb_printf = 2  printfs are logged.
*/
int enb_printf = 0;
/* DO NOT MODIFY BELOW THIS LINE */
#ifndef TERMCON
	int tc=0;		/* CCB environment  */
	JMPVECT execvect;	/* EXEC entry vectors */
#else
	int tc=1;		/* TC environment */
	extern JMPVECT execvect;/* TCEXEC entry vectors */
#endif
int cblkcnt = NCLIST;
struct cblock cfree[NCLIST];
