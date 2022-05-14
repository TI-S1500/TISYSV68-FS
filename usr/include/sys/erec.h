/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1984.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char erec_h[] = "@(#)erec.h	1.10 (TI) 92/01/16";
#endif	SCCSID


/* @(#)erec.h	1.4   */
/*
 * Every error record has a header as follows.
 */

struct errhdr {
	short	e_type;		/* record type */
	short	e_len;		/* bytes in record (with header) */
	time_t	e_time;		/* time of day */
	short	e_cpu;		/* cpu id 			*/
};

/*
 * Error record types
 */

#define E_GOTS		010		/* Start for UNIX/TS */
#define E_GORT		011		/* Start for UNIX/RT */
#define E_STOP		012		/* Stop */
#define E_TCHG		013		/* Time change */
#define E_CCHG		014		/* Configuration change */
#define E_BLK		020		/* Block device error */
#define E_STRAY		030		/* Stray interrupt */
#define E_PRTY		031		/* Memory parity */
#define E_LOST		032		/* Lost interrupt */
#define E_MSG		040             /* Console Message */
#define E_SFTERR 	050             /* Soft Error Disk Message */
#define E_TPSTAT 	060             /* Soft Error Tape Message */

#define MSGSIZE  	81		/* Max length of error msg */

/*
 * Error logging startup record. One of these is
 * sent to the logging daemon when logging is
 * first activated.
 */


struct estart {
	short	e_cpu;		/* cpu type */
	struct utsname e_name;	/* system names */
	short	e_mmr3;		/* contents of mem mgmt reg 3 (11/70 and 11/45) */
	long	e_syssize;	/* system memory size (11/70 only) */
	short	e_bconf;	/* block device configuration */
};

/*
 * Error logging soft disk error record
 *
 */
struct esoft {
	int  blockno;       /* block number on device    */
	int  devno;         /* device number             */
	int  read_or_write; /* read or write error       */
	int  error_type;    /* type of soft error	 */
	int  rsvd1;	    /* reserved field for tapes  */
	int  rsvd2;	    /* reserved field for tapes  */
};

/*
 * Error logging termination record that is sent to the daemon
 * when it stops error logging.
 */

#define eend errhdr

/*
 * Buffer used to read in the error text and format from the
 * error file.
 */

struct emfmt 
{
	char msg[MSGSIZE];
};
/*
 * A time change record is sent to the daemon whenever
 * the system's time of day is changed.
 */

struct etimchg {
	time_t	e_ntime;	/* new time */
};

/*
 * A configuration change message is sent to
 * the error logging daemon whenever a block device driver
 * is attached or detached (MERT only).
 */

struct econfchg {
	char	e_trudev;	/* "true" major device number */
	char	e_cflag;	/* driver attached or detached */
};

#define E_ATCH	1
#define E_DTCH	0


/*
 * Template for the error record that is logged by block devices.
 */

struct eblock {
	dev_t	e_dev;		/* "true" major + minor dev number */
	physadr	e_regloc;	/* controller address */
	short	e_bacty;	/* other block I/O activity */
	struct iostat e_stats;	/* unit I/O statistics */
	short	e_bflags;	/* read/write, error, etc */
	short	e_cyloff;	/* logical dev start cyl */
	daddr_t	e_bnum;		/* logical block number */
	ushort e_bytes;		/* number of bytes to transfer */
	paddr_t	e_memadd;	/* buffer memory address */
	ushort e_rtry;		/* number of retries */
	short	e_nreg;		/* number of device registers */
#ifdef vax
	struct	mba_regs e_mba;	/* mass bus adaptor registers */
#endif
};

/*
 * Flags (selected subset of flags in buffer header)
 */

#define E_WRITE	0
#define E_READ	1
#define E_NOIO	02
#define E_PHYS	04
#ifdef m68k
#define E_FORMAT 010
#else
#define E_MAP	010
#endif
#define E_ERROR	020

/*
 * Template for the stray interrupt record that is logged
 * every time an unexpected interrupt occurs.
 */

struct estray {
	physadr	e_saddr;	/* stray loc or device addr */
	short	e_sbacty;	/* active block devices */
};

/*
 * Memory parity error record that is logged whenever one
 * of those things occurs (11/70s only).
 */

struct eparity {
	short	e_parreg[4];	/* memory subsystem registers */
};
struct ememory {
	int	e_sbier;
	int	e_memcad;
};

/*
 * Error messages are now placed into the error log instead of being
 * written to the console. The error type E_MSG  has been added and 
 * uses the struct esys. The information to be passed will consist
 * of a message number and message parameters.
 */

struct esys
{
	int emsgnum;
	int enumparm;
	int eprm[8];
}; 

#define CORLOGSIZ   10 			/* size of incore error log */
struct corerr {
	short e_type;			/* currently E_MSG (logemsgs) only */
	short e_reps;			/* number of consecutive repetions */
	union {
		struct esys esys;	/* logemsg format */
		struct eblock eblock;	/* logberr format */
		char e_data[44];
	} u;
	time_t e_time;		/* time of occurrence/most recent repetion */
};

extern corerrindx;			/* offset in corerrlog */
extern struct corerr corerrlog[];	/* the core error log itself */
