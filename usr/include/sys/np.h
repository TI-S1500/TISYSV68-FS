/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1984.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
#ident "@(#)np.h	1.47  (TI) 92/05/05"
#endif	SCCSID

#ifdef __STDC__
#define VOLATILE volatile
#else
#define VOLATILE
#endif

/*
** nupiblk_t	- basic command block.
** nupisblk_t	- extension for the setup command.
** nupinsblk_t	- extension for the nupi status command.
** nupifsblk_t	- extension for the formatter status command.
** nupidsblk_t	- extension for the device status command.
** nupiscat_t	- extension for scatter/gather commands.
** nupitblk_t	- extension for tape formatter setup.
** NPDEV	- number of long words of formater and device status.
** NPSEN	- number of words of SCSI sense status and other.
** NTWORDS	- number of long words for formatter setup extension.
*/

#define	NPDEV	21
#define	NPSEN	16
#define	NTWORDS	4

struct nupiblk_t
{
	VOLATILE char	command;
	VOLATILE char	option;
	VOLATILE char	uu0;
	VOLATILE char	unit;
	VOLATILE long	status;
	VOLATILE long	nuaddr;
	VOLATILE long	bcount;
	VOLATILE long	block;
	VOLATILE long	evaddr;
	VOLATILE long	uu1;
	VOLATILE long	uu2;
};

struct nupisblk_t
{
	VOLATILE long	evaddr;	/* nubus address of special event int. vector */
	VOLATILE long	params;	/* number of retries to do, etc. */
};

struct nupinsblk_t
{
	VOLATILE long	sevflags;
	VOLATILE short	selftest;
	VOLATILE short	subtest;
	VOLATILE long	devstat[NPDEV];
	VOLATILE short	senses[NPSEN];
};

struct nupifsblk_t
{
	VOLATILE long	fmtstat;
	VOLATILE long	devstat[2];
	VOLATILE short	senses[NPSEN];
};

struct nupidsblk_t
{
	VOLATILE long	devstat;
	VOLATILE short	senses[NPSEN];
};

struct nupiscat_t
{
	VOLATILE long	nuaddr;
	VOLATILE long	scount;
};

struct nupitblk_t
{
	VOLATILE long	words[NTWORDS];
};

struct nupvtblk_t
{
	VOLATILE long	words[5];
};

struct nupi_dev_stat
{
	VOLATILE int words[9];
};

/*
** The little-endian (byte-swapped) versions of the command block
** and its extensions, which NUPI expects to see in memory.
*/

struct Nupiblk_t
{
	VOLATILE char	unit;
	VOLATILE char	uu0;
	VOLATILE char	option;
	VOLATILE char	command;
	VOLATILE long	status;
	VOLATILE long	nuaddr;
	VOLATILE long	bcount;
	VOLATILE long	block;
	VOLATILE long	evaddr;
	VOLATILE long	uu1;
	VOLATILE long	uu2;
};
struct Nupisblk_t
{
	VOLATILE long	words[sizeof(struct nupisblk_t)/sizeof(long)];
};
struct Nupinsblk_t
{
	VOLATILE long	words[sizeof(struct nupinsblk_t)/sizeof(long)];
};
struct Nupifsblk_t
{
	VOLATILE long	words[sizeof(struct nupifsblk_t)/sizeof(long)];
};
struct Nupidsblk_t
{
	VOLATILE long	words[sizeof(struct nupidsblk_t)/sizeof(long)];
};
struct Nupitblk_t
{
	VOLATILE long	words[sizeof(struct nupitblk_t)/sizeof(long)];
};
struct Nupiscat_t
{
	VOLATILE long	words[sizeof(struct nupiscat_t)/sizeof(long)];
};
struct Nupvtblk_t
{
	VOLATILE long	words[sizeof(struct nupvtblk_t)/sizeof(long)];
};

/* Utility and status commands */

#define	SETUP		0x81
#define FSETUP		0x41		/* Formatter Setup Command */
#define MSCSENSE	0x45		/* Formatter Sense Command */
#define NSTATUS		0x82
#define SARCMD		0x83
#define CTRLTIME	0x84
#define N2STATUS	0x85
#define PERON		0x86		/* Post soft ERror ON	   */
#define PEROFF		0x87		/* Post soft ERror OFF     */
#define PERRET		0x88		/* Post soft ERror RETurn stats */
#define CTRLPASS	0x89		/* Cntrl/SCSI Pass-Through cmds */
#define BYPSRD		0x90		/* BY PaSs ReaD		   */
#define FSTATUS		0x42
#define DSTATUS		0x02
#define PASSTHRD	0x71		/* pass through scsi read  */
#define PASSTHWRT	0x72		/* pass through scsi write */

/* General Device and Disk commands */

#define RESTORE		0x10
#define SEEK		0x11
#define READ		0x12
#define WRITE		0x13
#define FORMAT		0x14
#define	RNUPIBUF	0x15
#define	BUFTRANS	0x16
#define SWAPWRITE	0x17

/* Tape Specific commands */

#define	REWIND		0x20
#define UNLOAD		0x21
#define ERASE		0x22
#define SKIPFOR		0x23
#define SKIPREV		0x24
#define WRTFM		0x25
#define SKIPFILE	0x26
#define SKPFFM		0x27
#define SKPRFM		0x28

/* Selftest and Diagnostic commands */

#define	NSELF		0xB0
#define	FSELF		0x70
#define	DSELF		0x30
#define SCSIPTR		0x71
#define SCSIPTW		0x72
#define PHYSDC		0x33

/* Command options */

#define EVENT		0x80
#define	SCATTER		0x40
#define	PHYSICAL	0x20
#define	SWAPPCE		0x10
#define	VARBLK		0x04

/* Completion status */

#define BUSY		0x80
#define COMPLETE	0x40
#define N_ERROR		0x20
#define NRETRY		0x10
#define COMP_RET	COMPLETE | NRETRY
#define	COMP_ERR	COMPLETE | N_ERROR
#define ERR_RET		N_ERROR | NRETRY
#define AUXS		0x08
#define FORMBUSY	0x008F0000

/* Errors */

#define CLASS		0xE0
#define CODE		0x1F
#define	EC(x)		((x)<<5)
#define SSDA		0x08
#define FILEMARK	0x04
#define EOM		0x02
#define ILI		0x01
#define E_SCSI		0x8E
#define E_MEDIA		0xCA
#define E_DELTA		0x45
#define E_NUBUS		0x62	/* NUBUS error on 1505 = PARITY error */
#define	DT		0xE0000000
#define	QTAPE		0x20000000
#define	FDISK		0x40000000
#define	RDISK		0x60000000
#define	TOL		0x10000000	/* Formatter or Device is OFFLINE */
#define	WPROT		0x01000000	/* Device Write Protected         */
#define	NTREADY		0x00200000	/* Device Not Ready               */
#define IND_STA		0x00800000	/* Indeterminate Device Status    */

/* interesting bits in the configuration register */

#define	BD_RESET	0x01
#define ENABLE_BUSM	0x02
#define FAULT_LED	0x04
#define SBTEST		0x08

/* diagnostic status from NUPI flag register */

#define ST_INC		0x1		/* 1 ==> self-test is incomplete */
#define ST_FAIL		0x2		/* 1 ==> self-test failed */
#define SCSI_STS	0x4		/* 1 ==> SCSI failed self-test */

/* soft error logging disk read/write flags */
#define READ_ERR	1
#define WRITE_ERR	0

/*
** Multiplexing minor device numbers.
**
** Nupi disk:
** bits 0-3:	logical driver number.
** bit    4:	unit select.
** bits 5-7:	formatter select.
**
** Nupi tape:
** bits   0-3:	unused.
** bit      4:	rewind on close.
** bit      5:	QIC11 format.     --------\
** bit      6:	6250 format.      =========>  Bits are exclusive.
** bit      7:	CT2000 format.    --------/
** bit      8:	unit select.
** bits  9-11:	formatter select.
** bits 12-15:	slot number.
** bits 16-20:  tape format type bits
**
** PHYSTAPE	Generate formatter/unit given minor device number.
** NTREWIND	True if minor selects the rewinding device.
** QIC11	True if minor selects QIC11 format.
** TPDENSITY	Shifts and masks off the NEW tape density definition bits.
**
** NUBUS	top nibble of nubus addresses
** MAXSCAT	max # of scatter table entries
** TCOUNT	minimum transfer count
** S_WAIT	max # of delay(2) to wait for completion of SETUP & STATUS
** R_WAIT	max # of delay(2) to wait for completion of RESTORE
** NUPIWLIM	max # of ticks before assuming interrupt is lost
** KSCAT	kernel scatter  table flag bit
** DENSITY_BIT	# of bits to shift to move density bits over to low bit position
** DENSITY_BITS	mask of tape density bits
*/

#define PHYSTAPE(x)	((((x) & 0x0E) << 2) | ((x) & 0x01))
#define	NOREWIND(x)	((x) & 0x10)
#define	QIC11(x)	((x) & 0x20)
#define	MT6250(x)	((x) & 0x40)
#define	VTTAPE(x)	((x) & 0x80)
#define	NOTPOPEN(x)	((x) & 0x00200000)  /* allow opens w/no tape inserted */
#define	TPDENSITY(x)	( ((x) >> DENSITY_BIT) & DENSITY_BITS )
#define DENSITY_BIT	16
#define DENSITY_BITS	0x1f
#define	K_FIT		0xc
#define	VSETUP		0xd
#define	STREAM		0x8100000
#define	WRD4		0x20000
#define VTEXT		0x8e
#define	TIMEOFF		0x10000000
#define	Q11		4
#define	NP0		1
#define	NT0		2
#define	NUBUS		0xf0000000
/*#define	MAXP		8*/
#define MAXSCAT		128
#define	TCOUNT		1024
#define S_WAIT		100
#define D_WAIT		20
#define R_WAIT		40
#define RD_WAIT		10
#define NUPIWLIM	40
#define	byte		unsigned char
#define	NTU		24      /* Max # controllers * devices per cntrl. */
#define	NUPISPL		spl3
#define ONEK		1024
#define ONEW		4
#define	b_command	b_resid
#define	b_repcnt	b_blkno
#define	INF		1000000
#define	T_WRITTEN	1
#define	SIO		2
#define	SCOM		4
#define	SSEEK		8

/* Controller status return FLAG bit values  mscnsblk_t,nupinsblk_t */
#define	NB_ERROR	0x01
#define	OVERT		0x02
#define	ILL_WR		0x04
#define	TOO_MANY	0x08
#define	ILL_CMD		0x10
#define	POWER_F		0x20
#define	ERROR_OUT	0x40

/* one per unit flags	*/
#define	ISOPEN		1
#define B_SERV		2
#define	TIMEOUT		4
#define KSCAT		0x08
#define EOM_NXT		0x10
#define CDROMDEV	0x20
#define XOPENLOCK	0x40
#define XNOLABEL	0x80
#define EOM_NXT_NXT	0x100

/* one per unit opTIma flags */
#define SE_LOGGING      0x01            /* Enable/Disable Soft Error Logging */
#define CATCH_CMD       0x02            /* Special flg for mscintr & MSCDSTAT*/
#define XUSE            0x04            /* Flag to limit pass-thru commands  */
#define SE_COLLECTION   0x08            /* Enable/Disable Soft Err Collection */
#define WRITE_MODE      0x10            /* Previous tape command was a write */
#define PASS_TMO        0x20            /* Linked List Ctrl-Pass Timout Flag */

#define LASTBIT		0xfe
#define CTRLSHFT	12
#define FORMSHFT	8
#define CTRLMASK	0x0f
#define FORMMASK	255
#define HALFMASK	0x0000ffff
/*#define MAXCTRL		3*/
/*#define MAXCTL		3*/
/*#define MAXUNITS	24*/
#define DEVCNTRL	8
#define DEVENTS		256
#define BLKSIZ		1024
#define MAXPOS		16
#define INTERN		0x20000
#define PSELFMSK	0xf000
#define PSELFERR	0x2000
#define CSELFMSK	0xf00000
#define CSELFERR	0x200000
#define CERRMSK		0xff0000
#define CERRSHFT	16
#define DERRMSK		0xff00
#define DERRSHFT	8
#define INTERR		0xffff00
#define MAXSTAT		12
#define CLOSEBIT	0x10
#define WRITBIT		0x20
#define PARITYERR_MSG	1		/* driver parity err msg dsply flg */

/* Struct holding locked segments of usr vm pages.
*  It is used to keep from trying to lock/unlock the same vm pages.
*  The values it stores are the bottom and top addresses of a page
*  segment.  These values are on page boundaries and can span more
*  than one consecutive vm page.  Examples are (using 1k pages):
*  bottom=0x0000,top=0x3ff   or   bottom=0x10800,top=0x10bff.       */
struct lckpg {
	caddr_t lckbot;		/* vm addr of bottom of page segment */
	caddr_t lcktop;		/* vm addr of top of page segment */
	int	rw;		/* the direction of the xfer 0=wrt,1=rd */
	};

struct one_per_unit
{
	struct Nupidsblk_t	*ds;
	struct nupi_dev_stat	*ds2;
	struct Nupiblk_t	*nb;
	struct Nupiscat_t	*ng;
	VOLATILE int		flag;
	VOLATILE int		wticks;
	VOLATILE int		scatcnt;
	daddr_t			prblk;
	VOLATILE long 		*skipparm;
	VOLATILE long 		indxperf;
        struct lckpg            lckpg[7]; /* locked user vm chunks */
    	VOLATILE int		refcnt;   /* exclusive use ref count */
    	VOLATILE int		pgrp;     /* exclusive use process group */
        VOLATILE int            numrds;   /* read  count statistic  */
        VOLATILE int            rderrs;   /* soft error read  count statistic */
        VOLATILE int            numwrts;  /* write count statistic  */
        VOLATILE int            wrterrs;  /* soft error write count statistic */
        VOLATILE int            delta_base; /* baseline tape soft err count */
	VOLATILE int		optflag;  /* flag for opTIma hook additions   */
};

struct one_ctl
{
	VOLATILE long			*nupicar;
	VOLATILE char			*nupiflg;
	VOLATILE char			*nupicnf;
	VOLATILE int			npiflg;
	VOLATILE long			punum[MAXPOS];
	VOLATILE long			lastdunit;
};

struct nup_dsk
{
	VOLATILE short	formun;	/* combination formatter and unit number */
	VOLATILE short	perfindx; /* index into performance information */
	VOLATILE long	size;	/* size, in blocks, of the partition */
	VOLATILE long	offset;	/* ofset from start of disk, in blocks */
	VOLATILE long	pu;	/* index into all structures that have one
				   entry per disk */
	VOLATILE long	devnum; /* the minor device number */
	VOLATILE short	refcnt;	/* the reference count of the device */
	VOLATILE short 	type;
};

struct perfindx {
	VOLATILE short used[12]; /* tells whether index is used */
};

struct endbuf {
	caddr_t addr;
	VOLATILE int count;
	VOLATILE int flag;
};

struct wrdmv {
	VOLATILE char addr[8];
};

struct ctrl_time {
	VOLATILE int num_req;
	time_t req_start;
	time_t tot_time;
};

struct time_ret {
	time_t lbolt;
	struct ctrl_time ctrl_time[MAXCTRLS];
};

#ifdef HISTA
struct stat_d {
	int histqc[33];		/* histogram queue count */
	int histts[33];		/* histogram transfer size */
	int histdb[33];		/* histogram delta block  */
	int histdl[33];		/* histogram distribution block  */
	int histll[33];		/* histogram linked list count */
};
#endif HISTA

/* The following structure defines all the space necessary for each
   NUPI controller. STBM allocates the space for this structure at
   boot time. He allocates enough for the number of controllers in
   the chassis.                                                   */

struct nupi {
	struct 	one_ctl 	opc;
	struct 	ctrl_time 	nupi_time;
	lock_t			nupictrl;
	lock_t			nopc_lock;
	lock_t			np_lock[DEVCNTRL];
	lock_t			np_lock1[DEVCNTRL];
	lock_t			nqlock[DEVCNTRL];
	lock_t			nmqlock[DEVCNTRL];
	short			ntopenf[DEVCNTRL];
	short			nmtopenf[DEVCNTRL];
	daddr_t			ntblkno[DEVCNTRL];
	daddr_t			ntnxrec[DEVCNTRL];
	daddr_t			nmtblkno[DEVCNTRL];
	daddr_t			nmtnxrec[DEVCNTRL];
	int			qtype[DEVCNTRL];
	int			qmtype[DEVCNTRL];
#ifdef HISTA
	char			nhistset[DEVCNTRL];
	char			nhpblk[DEVCNTRL];
	unsigned	long	ndeltab[DEVCNTRL];
	unsigned	long	nhendb[DEVCNTRL];
	struct	stat_d		nd_stat[DEVCNTRL];
#endif HISTA
	sema_t			ntsema[DEVCNTRL];
	sema_t			nmtsema[DEVCNTRL];
	struct	iotime		nupistat[DEVCNTRL];
	struct	iotime		ntstat[DEVCNTRL];
	struct	iotime		nmtstat[DEVCNTRL];
	struct 	iobuf		nup_tab[DEVCNTRL];
	struct 	iobuf		nttab[DEVCNTRL];
	struct 	iobuf		nmttab[DEVCNTRL];
	struct	one_per_unit	opu[DEVCNTRL];
	struct	one_per_unit	opu_t[DEVCNTRL];
	struct	one_per_unit	mopu_t[DEVCNTRL];
	struct 	endbuf		endbuf[DEVCNTRL];
	struct 	wrdmv		wrdmv[DEVCNTRL];
	struct 	buf		cntbuf[DEVCNTRL];
	struct 	buf		*balloc[DEVCNTRL*2];
	struct 	buf		cntmbuf[DEVCNTRL];
	struct 	buf		*bmalloc[DEVCNTRL*2];
};
