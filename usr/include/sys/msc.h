/*	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1986. ALL
	RIGHTS RESERVED. PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef SCCSID
static char msc_h[] = "@(#)msc.h	1.25 (TI) 92/03/03";
#endif SCCSID

#ifdef __STDC__
#define VOLATILE volatile
#else
#define VOLATILE
#endif

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
#define REQSENSE        0x03    /* scsi read sense info command */
#define ECO             0x80    /* soft error count overflow */
#define SLMT3201        0       /* adnl status ret by mt3201 tape formatter */
#define SLEMULEX1       1       /* adnl status ret by emulex tape formatter */
#define SLEMULEX        3       /* adnl status ret by emulex tape formatter */
#define SLSCSI          6       /* adnl status ret by scsi tape formatter */
#define SLEXABYTE       18      /* adnl status ret by exabyte tape formatter */
#define DM_WAIT		120	/* number of delays for status to make */
#define RM_WAIT		140	/* number of delays for restore to make */
#define SM_WAIT		500	/* number of delays for setup to make */
/*#define MAXQTR		8*/	/* Max # 1/4" tapes per controller */
/*#define MAXMT		8*/	/* Max # 1/2" tapes per controller */
#define MSC0		3	/* Major number for MSC disk driver */
#define MQT0		4	/* Major number for MSC 1/4" tape driver */
#define MT0		5	/* Major number for MSC 1/2" tape driver */
#define MSCSPL		spl3	/* Mask interrupts to needed level 	 */
#define DSTAT	('D'<<8)|'S'	/* Ioctl to get disk stats. */
#define CSTAT	('C'<<8)|'S'	/* Ioctl to clear disk stats. */
#define CDROMB		0x20000 /* bit in minor number for CD-ROM device */

/* Additional commands not found on a NUPI */

#define ABQUEUE		0x17
#define PEJECT		0x19
#define AEJECT		0x1A

/* Command block options */

#define DONFLG 		0x01	/* place done value at done address */

/* Special event status information bits */

#define ILL_INT		0x80	/* Illegal interrupt */
#define INV_SPEC	0x100 	/* Invalid special event address */
#define MSC_ERR		0x200	/* MSC hardware or software error */
#define INV_SCSI	0x400 	/* Invalid SCSI operation */

struct one_msc {			/* one per controller structure */
	VOLATILE long		*msccar;
	VOLATILE char		*mscflg;
	VOLATILE char		*msccnf;
	VOLATILE int		mscflag;
	VOLATILE int		punum[MAXPOSS];
	VOLATILE int		lastdunit;
};

struct msc_per_unit {			/* msc devices one per unit structure*/
	struct mscds1blk_t	*ds1;
	struct mscds2blk_t	*ds2;
	struct ext_dev_stat	*ds4;	/* struct for SE_LOGGING */
	struct mscblk_t		*nb;
	struct mscscat_t	*ng;
	VOLATILE int		flag;
	VOLATILE int		wtics;
	VOLATILE long 		*skipparm;
	VOLATILE int 		indxperf;
	VOLATILE int		scatcnt;
        struct lckpg            lckpg[7]; /* locked user vm chunks */
	VOLATILE int 		refcnt;   /* exclusive use ref count */
	VOLATILE int 		pgrp;     /* exclusive use process group */
        VOLATILE int            numrds;   /* read  count statistic  */
        VOLATILE int            rderrs;   /* soft error read  count statistic */
        VOLATILE int            numwrts;  /* write count statistic  */
        VOLATILE int            wrterrs;  /* soft error write count statistic */
        VOLATILE int            delta_base; /* baseline tape soft error count */
	VOLATILE int		optflag;  /* flag for opTIma hook additions   */
};

struct mscblk_t {		/* MSC command block */
	VOLATILE char	command;	/* command name */
	VOLATILE char	opt2;		/* option bits */
	VOLATILE char	opt1;		/* option bits */
	VOLATILE unsigned char unit;	/* unit # */
	VOLATILE long	status;		/* return status */
	VOLATILE long 	nuaddr;	/* NuBus address of data or command extension */
	VOLATILE long	bcount;		/* byte count of request */
	VOLATILE long	block;		/* starting block number of request */
	VOLATILE long	evaddr;		/* event address */
	VOLATILE long	mscuse;		/* Reserved for MSC use only */
	VOLATILE long	res0;
	VOLATILE long	doneaddr;/* NuBus address to place done value in */
	VOLATILE long	doneval;/* Information that the controller will return*/
	VOLATILE long	exstatcnt;/* Extra status byte count */
	VOLATILE long	extaddr;/* Extra status address */
	VOLATILE long	res1;
	VOLATILE long	res2;
	VOLATILE long	res3;
	VOLATILE long	res4;
};

struct mscnsblk_t {	/* Controller status return values */
	VOLATILE long 	headers[2];
	VOLATILE long 	sevflags;
	VOLATILE long	eventinf;
};

struct mscds1blk_t {		/* device status descrip. 1 return value */
	VOLATILE long	headers[2];	/* header info */
	VOLATILE unsigned char unitsel;
	VOLATILE char	devstat[4];	/* ASCII string defining device type */
	VOLATILE char	nodata[3];	/* padded space to make long words */
};

struct mscds2blk_t {		/* dev. status descriptor 2 return struct */
	VOLATILE long	headers[2];
	VOLATILE long	devstat;
};

struct mscds3blk_t {		/* dev. status descriptor B return struct */
	VOLATILE long	headers[2];
	VOLATILE long	numblks;
	VOLATILE long	nouse[5];
};

struct mscsblk_t {    /* byte-swapped */
	VOLATILE long	evaddr;	/* nubus addr. of special event routine */
	VOLATILE long	params;	/* number of retries, etc. */
};

struct Mscsblk_t {
	VOLATILE long	evaddr;	/* nubus addr. of special event routine */
	VOLATILE long	params;	/* number of retries, etc. */
};

struct mscscat_t {		/* MSC scatter table */
	VOLATILE unsigned int nuaddr;
	VOLATILE int	scount;
};

struct mqttblk_t {
	VOLATILE long words[4];
};

struct Mqttblk_t {
	VOLATILE long words[4];
};

struct vttblk_t {
	VOLATILE long words[5];
};

struct Vttblk_t {
	VOLATILE long words[5];
};

struct mscstat_t {
	VOLATILE long headers[2];
	struct entry {
		VOLATILE unsigned char unitsel;
		VOLATILE char ds[4];
		VOLATILE char nodata[3];
	}entries[16];
};

struct mscdstat_t {
	VOLATILE long headers[2];
	VOLATILE int  dvc_stat[16];
};
#define OFFLINE	0x10	/* Offline status bit */
#define INDET   0x8000	/* Indeterminate status bit */
#define DVCNRDY 0x2000	/* Device not ready bit */

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

/*
 * Passed to the PERON IOCTL
 */
struct softype
{
        unsigned int type;                      /* log soft err or keep stats */
};

/*
 *  SOFTYPE Flags
 */
#define SOFTSTATS       0                       /* keep only soft error stats */
#define SOFTLOG         1                       /* get blk# of soft err & log */

/*
 * Structure filled with a PERRET IOCTL call
 */
struct perstat
{
        unsigned int numrds;                    /* Total # of blocks read     */
        unsigned int rderrs;                    /* Total # of soft read errs  */
        unsigned int numwrts;                   /* Total # of blocks written  */
        unsigned int wrterrs;                   /* Total # of soft write errs */
};

struct ext_dev_stat
{
	VOLATILE long words[4];
};

struct fsense_hdr
{
                                        /*       H  E  A  D  E  R     */
        unsigned char rsvd0;            /* Reserved Field             */
        unsigned char medium;           /* Medium Type                */
        unsigned char rsvd1;            /* Reserved Field             */
        unsigned char blk_ds_lngth;     /* Block Descriptor Length    */
        unsigned int  blk_ds_1;         /* Block Descriptor 1         */
        unsigned int  blk_ds_2;         /* Block Descriptor 2         */
};

struct pg_code_1
{
                                        /*  P  A  G  E    I  N  F  O  */
        unsigned char ps:1,             /* Param Saveable Bit         */
                       rsvd2:1,         /* Reserved Bit               */
                       pgcode:6;        /* Page Code (=1)             */
        unsigned char pglen:8;          /* Page Length                */
        unsigned char awre:1,           /* Auto Write Realloc Enable  */
                      arre:1,  		/* Auto Read  Realloc Enable  */
                       tb:1,            /* Transfer Block Bit         */
                       rc:1,            /* Read Continuous Bit        */
                       eer:1,           /* Enable Early Recovery Bit  */
                       per:1,           /* Post Error Bit             */
                       dte:1,           /* Disable Transfer on Error  */
                       dcr:1;           /* Disable Correction Bit     */
        unsigned char rd_rcnt:8;        /* Read Retry Count           */
	unsigned char crt_span:8;       /* Correction Span            */
        unsigned char hd_offcnt:8;      /* Head Offset Count          */
        unsigned char ds_offcnt:8;      /* Data Strobe Offset Count   */
        unsigned char recov_timlim:8;   /* Recover Time Limit (milli) */
};


struct fsense_cmd
{
        struct fsense_hdr header;
        struct pg_code_1  pg_info;
};

struct scsi_setup
{
        unsigned char mode_cnt:8;
        unsigned char cntrl_byte:8;
        unsigned char save_parms:1,
                       rsvd0:7;
        unsigned char rsvd1:5,
                       urt:1,
                       lrt:1,
                       lbc:1;
};

struct mode_sel_hdr
{
        unsigned char sense_data_lngth:8;
        unsigned char medium_type:8;
        unsigned char dev_spec_parms:8;
        unsigned char blk_des_lngth:8;
};

struct fsetup_cmd
{
        struct scsi_setup   swrd;
        struct mode_sel_hdr mhdr;
        unsigned int  blk_ds_1:32;      /* Block Descriptor 1         */
        unsigned int  blk_ds_2:32;      /* Block Descriptor 2         */
        struct pg_code_1 pg_info;
};

struct lock_pg
{
        caddr_t lckbot;
        caddr_t lcktop;
        int     rw;
        short   pid;
        short   refcnt;
};

struct rdvals
{
	char	*buf;
	unsigned cnt;
};
