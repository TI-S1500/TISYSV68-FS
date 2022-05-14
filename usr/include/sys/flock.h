/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char flock_h[] = "@(#)flock.h	1.11 (TI) 91/06/24";
#endif	SCCSID

/* file segment locking set data type - information passed to system by user */
/* it is also found in fcntl.h */
#ifndef	F_RDLCK
struct	flock	{
	short	l_type;
	short	l_whence;
	long	l_start;
	long	l_len;		/* len = 0 means until end of file */
	short	l_sysid;
	short	l_pid;
};
#endif

struct	_uslpinfo
	{
		struct	filock	*filp;
		struct	proc	*pp;
			long	 unused1;
			long	 unused2;
	};

#define	l_end	l_len

/* file segment locking types */
#ifndef F_RDLCK
#define	F_RDLCK	01	/* Read lock */
#endif
#define	F_WRLCK	02	/* Write lock */
#define	F_UNLCK	03	/* Remove lock(s) */

/* fcntl(2) requests */
#define	F_DUPFD	0	/* Duplicate fildes */
#define	F_GETFD	1	/* Get fildes flags */
#define	F_SETFD	2	/* Set fildes flags */
#define	F_GETFL	3	/* Get file flags */
#define	F_SETFL	4	/* Set file flags */
#define	F_GETLK	5	/* Get file lock */
#define	F_SETLK	6	/* Set file lock */
#define	F_SETLKW	7	/* Set file lock and wait */
#define	F_CHKFL	8	/* reserved */
#define	F_ALLOCSP	10	/* reserved */
#define	F_FREESP	11	/* reserved */

/* file locking structure (connected to file table entry) */
struct	filock	{
	struct	flock set;	/* contains type, start, and length */
	union
	{
		int	wakeflg;	/* for locks sleeping on this one */
		struct {
			short	sysid;
			short	pid;
		} blk;
	}	stat;
	union
	{
		       sema_t		ws;
		struct _uslpinfo	si;
	}	ws_si;

	struct	filock *prev;
	struct	filock *next;
};

/* table to associate files with chain of locks */
struct	flino {
	dev_t	fl_dev;
	ino_t	fl_number;
	short	fl_padding;
	int	fl_refcnt;	 /* # of procs currently referencing this flino */
	sema_t	fl_sem;		 /* chain lock */
	struct	filock *fl_flck; /* pointer to chain of locks for this file */
	struct	flino  *prev;
	struct	flino  *next;
};

/* file and record locking configuration structure */
/* record and file use totals may overflow */
struct flckinfo {
	long recs;	/* number of records configured on system */
	long reccnt;	/* number of records currently in use */
	long recovf;	/* number of times system ran out of record locks */
	long rectot;	/* number of records used since system boot */
};

#define INOFLCK 1	/* Inode is locked when reclock() is called */
#define SETFLCK 2	/* Set a file lock */
#define SLPFLCK 4	/* Wail if blocked */

#define	USE_PID 1	/* use epid when cleaning locks */
#define	IGN_PID 2	/* ignore epid when cleaning locks */

#define MAXEND  017777777777

extern struct flckinfo	flckinfo;
extern struct filock	flox[];
extern struct flino	flinotab[];
