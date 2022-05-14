/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/
/*	Original 5.0 release: sa.h 1.6 of 6/28/82	*/
/*	sa.h contains struct sa and defines variable used
		in sadc.c and sar.c.
	The nlist setup table in sadc.c is arranged as follows:
	For VAX and PDP11 machines,
		- device status symbol names for controllers with 8 drives ,
			headed by _hpstat.
			(not include the _gdstat)
		- device status symbol names for controllers with 4 drives,
			headed by _rlstat.
		- device status symbol names for controllers with 1 drive,
			headed by _tsstat.
		- general disk driver status system name.
		- symbol name for _sysinfo.
		- symbol names for system tables: inode, file,
			text and process.
		- symbol name for _var.
		- symbol name for _rl_cnt.
		- symbol name for _gd_cnt.
		- symbol name for system error table:

	For 3b20S system,
		- symbol name of dskinfo table
		- symbol name of UN52 tape drive.
		- symbol name for _sysinfo.
		- symbol names for system tables: inode, file,
			text and process.
		- symbol name for _var.
		- symbol name for dsk_cnt.
		- symbol name for un52_cnt.
		- symbol name for system error table:
	For IBM 370 system,
		- symbol name for sysinfo.
		- symbol names for system tables: inode, file,
				text and process.
		- symbol name for var.
		- symbol name for system error table:
	For M68K system,
		- symbol name for sysinfo.
		- symbol names for system tables: inode, file,
				iseg and process.
		- symbol name for var.
		- symbol name for udstat.
		- symbol name for system error table:
			Note that this is always the last entry in setup
			table, since the number of entries of setup table
			is used in sadc.c.
*/



#include <a.out.h>

#define npidev(x)	(dev_t)(0x01000a00 | ((x)<<12))
#define mscdev(x)	(dev_t)(0x19000a00 | ((x)<<12))

/*	The following variables define the positions of symbol
	table names in setup table:
*/

#define	DVMP	0
#define	SINFO	1
#define	INO	2
#define	FLE	3
#define	ISEG	4
#define	PRO	5
#define	V	6
#define	SERR	7

char *Setup[] = {	/* to initialize setup[] */
	"devmap",
	"sysinfo",
	"inode",
	"file",
	"iseg",
	"proc",
	"v",
	"syserr",
	(char*)0
};
struct syment setup[sizeof(Setup)/sizeof(char*)];

#define	NDEVS	12	/* max # of disks we will keep stats on */
char devnm[SINFO][6] = {
	"disk-",
};


/* structure dskcontrol is used to keep track of nodes and their associated 
   file descripters for disk controllers in the system 
*/
struct dskcontrol{
	char *path;
	int fd;
};


/*	structure sa defines the data structure of system activity data file
*/

struct sa {
	int	num_cpu;	/* number of cpu's in chassis */
	struct	sysinfo si;	/* defined in /usr/include/sys/sysinfo.h  */
	int	szinode;	/* current size of inode table  */
	int	szfile;		/* current size of file table  */
	int	sziseg;		/* current size of iseg table  */
	int	szproc;		/* current size of proc table  */
	int	mszinode;	/* maximum size of inode table  */
	int	mszfile;	/* maximum size of file table  */
	int	msziseg;	/* maximum size of iseg table  */
	int	mszproc;	/* maximum size of proc table  */
	long	inodeovf;	/* cumulative overflows of inode table
					since boot  */
	long	fileovf;	/* cumulative overflows of file table
					since boot  */
	long	isegovf;	/* cumulative overflows of iseg table
					since boot  */
	long	procovf;	/* cumulative overflows of proc table
					since boot  */
	time_t	ts;		/* time stamp  */
	long	ramio;		/* I/O requests to/from ram disk
					since boot  */
	long	ramcnt;		/* number of block transferred from/to ram
					since boot  */

	long	devio[NDEVS][4]; /* device unit information  */

#define	IO_OPS	0  /* number of I /O requests since boot  */
#define	IO_BCNT	1  /* number of blocks transferred since boot */
#define	IO_ACT	2  /* cumulative time in ticks when drive is active  */
#define	IO_RESP	3  /* cumulative I/O response time in ticks since boot  */
};
extern struct sa sa;
