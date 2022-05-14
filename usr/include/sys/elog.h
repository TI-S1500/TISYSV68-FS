/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char elog_h[] = "@(#)elog.h	1.5 (TI) 87/05/04";
#endif	SCCSID

/* @(#)elog.h	1.3	UNIX System V/68 */
/*
 * "True" major device numbers. These correspond
 * to standard positions in the configuration
 * table, but are used for error logging
 * purposes only.
 */

#ifdef m68k
#define	TM0	0
#define	SMD0	1
#define QTR0	2
#else
#define RK0	0
#define RP0	1
#define RF0	2
#define TM0	3
#define TC0	4
#define HP0	5
#define HT0	6
#define HS0	7
#define RL0	8
#define	HP1	9
#define	HP2	10
#define	HP3	11
#endif

/*
 * IO statistics are kept for each physical unit of each
 * block device (within the driver). Primary purpose is
 * to establish a guesstimate of error rates during
 * error logging.
 */

struct iostat {
	long	io_reads;	/* number of read */
	long	io_writes;	/* number of writes */
	long	io_misc;	/* number of "other" operations */
	long	io_unlog;	/* number of unlogged errors */
};

/*
 * structure for system accounting
 */
struct iotime {
	struct iostat ios;
	long	mdev;		/* minor device number(for I.D.) */
	long	io_rd_bcnt;	/* total blocks read */
	long	io_wt_bcnt;	/* total blocks written */
	time_t	io_act;		/* total controller active time */
	time_t	io_resp;	/* total block response time */
};

#define MAXDPC		16	/* max disk per ctrl (nupi & msc) */
struct sar_ret {
	time_t	lbolt;
	int	ctrl;
	struct	iotime stat[MAXDPC];
};
