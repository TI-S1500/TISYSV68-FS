/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1989.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char sccsid[] = "@(#)nvram.h	1.11 (TI) 92/09/22 ";
#endif	SCCSID
 
/* size of NVRAM crc */
#define NVCRCSIZ 14

/* offset in NVRAM to typed blocks */
#define NVTYPOFF 0x100

/* offset in NVRAM to memory parity list for S1505 */
#define NV_MPE_LST	0x1000

/* type field of "end" block */
#define NVT_END  0xfffe

/* misc crash records definitions */
#define CRASH_RECORD_PROCESSOR_TYPE        2
#define CRASH_RECORD_REV                   1
#define CRASH_RECORD_SIZE              0x200
#define CRASH_RECORD_FIRST_REC         0x800
#define CRASH_RECORD_LAST_REC          0xe00

/*
* the following strucure describes the system NVRAM layout.  Note that
* this structure is only useful for "in memory" copies because NVRAM 
* is implemented in every fourth byte.
*/
struct nvram
{
	long 	monitor;		/* default monitor */
	long 	keyboard;		/* default keyboard */
	long 	lodsrc;			/* default load source */
	unsigned char 	format;		/* NuGeneration format = 01 */
	unsigned char 	rev;		/* revision */
	unsigned short 	rescrc;		/* resource crc */
	unsigned short 	confcrc;	/* config crc */
	unsigned short 	reserve;	/* reserved, for board test */
	unsigned char  	asvalid;	/* abnormal shutdown valid=>56*/
	unsigned char  	shtdwn[11];	/* abnormal shutdown info */
	unsigned short 	crtype;		/* crash record processor type */
	unsigned char   crrev;          /* crash record revision */ 
	unsigned char   crreserved;     /* crash record reserved */
	unsigned short 	cractive;	/* crash record current active*/
	unsigned short 	crsize;		/* crash record size */
	unsigned short 	crlastrec;	/* crash record last record */
	unsigned short 	crfirstrec;     /* crash record first record */
	unsigned char  	crresdata[12];	/* crash record reserved */
	dev_t    future_nv_logdev;      /* future home for active log device */
	dev_t	 nv_logdev;		/* active logging device (this should
					 * be where NVRAM allocation management
					 * data is stored) */
};

/* maximum number of hard parity errors allowed */
#define MAXMERR 32
/* maximum number of parity errors entries in nvram list (plus 1 for 
   				overhead entry				*/
#define MAX_NVPERR 65

#define PERREXIST 1	/* return code if hard parity error exists in NVRAM */
/*
* the following structure describe the list of hard memory parity errors
*/
struct merrlst
{
	int count;
	unsigned long perrs[MAXMERR]; 
};

/*
*  the following structure describes the list of memory parity errors
*  as it appears in NVRAM 
*/
struct nverr_entry
{
	unsigned	orig_id	   : 8,	/* ID of code finding the error */
			orig_task  : 8, /* 'task' ID of code finding error */
			hard_soft  : 1,	/* Flag:  1=error known to be hard */
			unusedbit  : 1,
			testcount  : 6, /* pass test count; 0=unused entry */
			unusedbits : 4,
			byte_in_err: 4; /* from memory error log register */
	unsigned	mem_addr;	/* Board relative addr of longword */
};
struct nverrlst
{
	unsigned char	nverrcrc[2];	/* crc on memory parity list	*/
	unsigned char	maxcount;	/* maximum number of entries	*/
	unsigned char	curcount;	/* number of nverr_entry's in use */
	unsigned char	nvunused[4];
	struct	nverr_entry entry[MAX_NVPERR-1];
};
/* Values for orig_id field */
#define	ID_FIRM	0x46	/* Firmware found the parity error */
#define	ID_UNIX	0x55	/* UNIX found the parity error */

/* Values for orig_task field */
#define TASK_PRIM	0x50  /* STBM Primitive found the error */
#define TASK_KERN	0x4B  /* Kernel found the parity error */
#define TASK_USER	0x55  /* User   found the parity error */
#define TASK_CCB	0x42  /* CCB	found the parity error */
#define TASK_CTRL	0x43  /* A controller found the parity error */

#ifdef KERNEL
extern struct merrlst merrlst;
#endif KERNEL

/* crash record definition */
struct crash_record
{
    unsigned char  cr_flags;            /* crash rec flags (see defs below) */
    unsigned char  cr_pad;              /* unused                           */
    unsigned short cr_text_index;       /* index into crash rec text        */
    time_t         cr_boot_time;        /* boot time (seconds since epoch)  */
    time_t         cr_stop_time;        /* stop time (seconds since epoch)  */
    signed   char  cr_text[(CRASH_RECORD_SIZE/4) - 12];  /* crash rec text   */
};  


/* crash record flag definitions */
#define CR_UNSEEN_FLAG  0x0001    /* crash record has not been seen */
#define CR_PANIC_FLAG   0x0002    /* abnormal shutdown flag         */
#define CR_BOOTDVR_FLAG 0x0004    /* bootdvr flag                   */   
#define CR_PF_FLAG      0x0008    /* powerfail flag                 */
