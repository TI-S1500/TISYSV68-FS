/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
#ident "@(#)mtio.h	1.8 (TI) 93/03/05"
#endif	SCCSID

/*
 * Structures and definitions for mag tape io control commands
 */

#ifndef _IOCTL_
#include <sys/ioctl.h>
#endif

/* structure for MTIOCTOP - mag tape op command */

struct	mtop	{
	long	mt_op;		/* operations defined below */
	long	mt_count;	/* how many of them */
	char   *mt_param;       /* parameters, if any */
	int	mt_dir;		/* transfer direction */
};

/* operations: */
#define MTWEOF	0	/* write an end-of-file record */
#define MTFSF	1	/* forward space file */
#define MTBSF	2	/* backward space file */
#define MTFSR	3	/* forward space record */
#define MTBSR	4	/* backward space record */
#define MTREW	5	/* rewind */
#define MTOFFL	6	/* rewind and put the drive offline */
#define MTNOP   7       /* nop */
#define MTERASE 8       /* erase to end of tape */
#define MTPASSTHR 9     /* scsi pass through command */
#define MTMAXSIZE 10    /* return maximum transfer size */

/* transfer direction */
#define MTREAD	0	/* read transfer, drive to host */
#define MTWRITE	1	/* write transfer, host to drive */

/* The following status commands are NOT supported! */

/* structure for MTIOCGET - mag tape get status command */

/*struct	mtget	{*/
	/*short	mt_dsreg;*/	/* drive status register */
	/*short	mt_erreg;*/	/* error register */
	/*short	mt_resid;*/	/* residual count */
/* the following two are not yet implemented */
	/*short	mt_fileno;*/	/* file number of current position */
	/*short	mt_blkno;*/	/* block number of current position */
/*};*/

/* unfortunately the bits in these registers are grossly device dependent */
/* should be defined here but aren't */
