/*	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1986. ALL
	RIGHTS RESERVED. PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef SCCSID
static char msc_h[] = "@(#)msc.h	1.15 (TI) 89/10/26";
#endif SCCSID


#define MAXPOSS		32
#define SMDSHFT		12	/* shift to get SMD bi in LSB */
#define SMDMASK		0x10	/* Bit in formun # set for SMD devices */
#define MSCSEN		16	/* Number of sense words */
#define MSCDEV		21
#define DEVPMSC		16
#define BYTEPCMD	64	/* bytes per command block */
#define WORDPCMD	16	/* words per command block */
#define CMDSPBLK	16	/* number of command blocks that fit in 1K */
#define MSCSTAT		0x83	/* command value for MSC status command */
#define MSCDSTAT	0x03	/* command value for MSC device status */
#define DM_WAIT		120	/* number of delays for status to make */
#define RM_WAIT		140	/* number of delays for restore to make */
#define SM_WAIT		500	/* number of delays for setup to make */
/*#define MAXQTR		8*/	/* Max # 1/4" tapes per controller */
/*#define MAXMT		8*/	/* Max # 1/2" tapes per controller */
#define MSC0		3	/* Major number for MSC disk driver */
#define MQT0		4	/* Major number for MSC 1/4" tape driver */
#define MT0		5	/* Major number for MSC 1/2" tape driver */
#define MSCSPL		spl4	/* Mask interrupts to level 4 */
#define DSTAT	('D'<<8)|'S'	/* Ioctl to get disk stats. */
#define CSTAT	('C'<<8)|'S'	/* Ioctl to clear disk stats. */

/* Additional commands not found on a NUPI */

#define ABQUEUE		0x17

/* Command block options */

#define DONFLG 		0x01	/* place done value at done address */

/* Special event status information bits */

#define ILL_INT		0x80	/* Illegal interrupt */
#define INV_SPEC	0x100 	/* Invalid special event address */
#define MSC_ERR		0x200	/* MSC hardware or software error */
#define INV_SCSI	0x400 	/* Invalid SCSI operation */

struct one_msc {			/* one per controller structure */
	long			*msccar;
	char			*mscflg;
	char			*msccnf;
	int			mscflag;
	int			punum[MAXPOSS];
	int			lastdunit;
};

struct msc_per_unit {			/* msc devices one per unit structure*/
	struct mscds1blk_t	*ds1;
	struct mscds2blk_t	*ds2;
	struct mscblk_t		*nb;
	struct mscscat_t	*ng;
	int			flag;
	int			wtics;
	long 			*skipparm;
	int 			indxperf;
	int			scatcnt;
};

struct mscblk_t {		/* MSC command block */
	char	command;	/* command name */
	char	opt2;		/* option bits */
	char	opt1;		/* option bits */
	unsigned char unit;	/* unit # */
	long	status;		/* return status */
	long 	nuaddr;		/* NuBus address of data or command extension */
	long	bcount;		/* byte count of request */
	long	block;		/* starting block number of request */
	long	evaddr;		/* event address */
	long	mscuse;		/* Reserved for MSC use only */
	long	res0;
	long	doneaddr;	/* NuBus address to place done value in */
	long	doneval;	/* Information that the controller will return*/
	long	exstatcnt;	/* Extra status byte count */
	long	extaddr;	/* Extra status address */
	long	res1;
	long	res2;
	long	res3;
	long	res4;
};

struct mscnsblk_t {	/* Controller status return values */
	long 	headers[2];
	long 	sevflags;
	long	eventinf;
};

struct mscds1blk_t {		/* device status descrip. 1 return value */
	long	headers[2];	/* header info */
	unsigned char unitsel;
	char	devstat[4];	/* ASCII string defining device type */
	char	nodata[3];	/* padded space to make long words */
};

struct mscds2blk_t {		/* dev. status descriptor 2 return struct */
	long	headers[2];
	long	devstat;
};

struct mscsblk_t {    /* byte-swapped */
	long	evaddr;		/* nubus addr. of special event routine */
	long	params;		/* number of retries, etc. */
};

struct Mscsblk_t {
	long	evaddr;		/* nubus addr. of special event routine */
	long	params;		/* number of retries, etc. */
};

struct mscscat_t {		/* MSC scatter table */
	unsigned int nuaddr;
	int	scount;
};

struct mqttblk_t {
	long words[4];
};

struct Mqttblk_t {
	long words[4];
};

struct vttblk_t {
	long words[5];
};

struct Vttblk_t {
	long words[5];
};

struct mscstat_t {
	long headers[2];
	struct entry {
		unsigned char unitsel;
		char ds[4];
		char nodata[3];
	}entries[16];
};

/*struct mscproc {
	long mscdone[MAXMSC];
};*/

struct msc {
	struct	one_msc		opmsc;
	struct	ctrl_time	msc_time;
	lock_t			mopc_lock;
	lock_t			msc_lock[DEVPMSC];
	lock_t			msc_lock1[DEVPMSC];
	lock_t			mqtqlock[DEVPMSC];
	lock_t			mtqlock[DEVPMSC];
	short			mqtopenf[DEVPMSC];
	short			mtopenf[DEVPMSC];
	daddr_t			mqtblkno[DEVPMSC];
	daddr_t			mqtnxrec[DEVPMSC];
	daddr_t			mtblkno[DEVPMSC];
	daddr_t			mtnxrec[DEVPMSC];
	int			mqtqtype[DEVPMSC];
	int			mtqtype[DEVPMSC];
#ifdef HISTA
	char			histset[DEVPMSC];
	long			hpblk[DEVPMSC];
	unsigned	long	deltab[DEVPMSC];
	unsigned	long	hendb[DEVPMSC];
	struct	stat_d		d_stat[DEVPMSC];
#endif HISTA
	sema_t			mqtsema[DEVPMSC];
	sema_t			mtsema[DEVPMSC];
	struct	iotime		mscstat[DEVPMSC];
	struct	iotime		mqtstat[DEVPMSC];
	struct	iotime		mtstat[DEVPMSC];
	struct	iobuf		msc_tab[DEVPMSC];
	struct	iobuf		mqttab[DEVPMSC];
	struct	iobuf		mttab[DEVPMSC];
	struct	msc_per_unit	mscopu[DEVPMSC];
	struct	msc_per_unit	mqtopu[DEVPMSC];
	struct	msc_per_unit	mtopu[DEVPMSC];
	struct	endbuf		mscend[DEVPMSC];
	struct	wrdmv		mscwrd[DEVPMSC];
	struct	buf		mqtbuf[DEVPMSC];
	struct	buf		*mqtalloc[DEVPMSC*2];
	struct	buf		mtbuf[DEVPMSC];
	struct	buf		*mtalloc[DEVPMSC*2];
};
