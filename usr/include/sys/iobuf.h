/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char iobuf_h[] = "@(#)iobuf.h	1.3 (TI) 86/02/04";
#endif	SCCSID

/*	@(#)iobuf.h	1.1	UNIX System V/68 */
/*
 * Each block device has a iobuf, which contains private state stuff
 * and 2 list heads: the b_forw/b_back list, which is doubly linked
 * and has all the buffers currently associated with that major
 * device; and the d_actf/d_actl list, which is private to the
 * device but in fact is always used for the head and tail
 * of the I/O queue for the device.
 * Various routines in bio.c look at b_forw/b_back
 * (notice they are the same as in the buf structure)
 * but the rest is private to each device driver.
 */
struct iobuf
{
	int	b_flags;		/* see buf.h */
	struct	buf *b_forw;		/* first buffer for this dev */
	struct	buf *b_back;		/* last buffer for this dev */
	struct	buf *b_actf;		/* head of I/O queue */
	struct 	buf *b_actl;		/* tail of I/O queue */
	dev_t	b_dev;			/* major+minor device name */
	char	b_active;		/* busy flag */
	char	b_errcnt;		/* error count (for recovery) */
	struct eblock	*io_erec;	/* error record */
	int	io_nreg;		/* number of registers to log on errors */
	physadr	io_addr;		/* register address */
	struct	iostat	*io_stp;	/* unit I/O statistics */
	time_t	io_start;
	int	pos;			/* Last known position of head */
	int	rev;			/* Reverse build act Q flag */
	int	io_s1;			/* space for drivers to leave things */
	int	io_s2;			/* space for drivers to leave things */
	struct  buf *b_bldf;            /* head pointer for disk build queue */
	struct  buf *b_bldl;            /* tail pointer for disk build queue */
};

#define tabinit(dv,stat)	{0,0,0,0,0,makedev(dv,0),0,0,0,0,0,stat,0,0}
#define NDEVREG(X)		(sizeof(struct X)/sizeof(int))

#define	B_ONCE	01	/* flag for once only driver operations */
#define	B_TIME	04	/* for timeout use */
