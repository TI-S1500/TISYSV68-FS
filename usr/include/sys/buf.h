/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char sccsid[] = "@(#)buf.h	1.33 (TI) 91/08/22";
#endif	SCCSID

/*
 * LOGGING if #defined causes the conditional inclusion of code to log file
 *         system data.
*/
/*
 * Each buffer in the pool is usually doubly linked into 2 lists:
 * the device with which it is currently associated (always)
 * and also on a list of blocks available for allocation
 * for other use (usually).
 * A buffer is on the available list, and is liable
 * to be reassigned to another disk block, if and only
 * if it is not marked BUSY.  When a buffer is busy, the
 * available-list pointers can be used for other purposes.
 * Most drivers use the forward ptr as a link in their I/O active queue.
 * A buffer header contains all the information required to perform I/O.
 * Most of the routines which manipulate these things are in bio.c.
 */
struct buf
{
	sema_t b_lock;			/* buffer semaphore */
	int	b_flags;		/* see defines below */
	struct	buf *b_forw;		/* headed by d_tab of conf.c */
	struct	buf *b_back;		/*  "  */
	struct	buf *av_forw;		/* position on free list, */
	struct	buf *av_back;		/*     if not BUSY*/
	dev_t	b_dev;			/* major+minor device name */
	unsigned b_bcount;		/* transfer count */
	union {
	    caddr_t b_addr;		/* low order core address */
	    int	*b_words;		/* words for clearing */
	    struct filsys *b_filsys;	/* superblocks */
	    struct dinode *b_dino;	/* ilist */
	    daddr_t *b_daddr;		/* indirect block */
	    struct sat *b_sat;		/* secondary allocation table */
	} b_un;

#define	paddr(X)	(paddr_t)(X->b_un.b_addr)

	daddr_t	b_blkno;		/* block # on device */
	char	b_error;		/* returned after I/O */
	char	b_cpuid;		/* cpuid-needed for pageout operations*/
	char	b_bcpu;			/* cpu which owns this file buffer. */
	char	b_unusd1;		/* unused for now */
	unsigned int b_resid;		/* words not transferred after error */
	time_t	b_start;		/* request start time */
	struct  proc  *b_proc;		/* process doing physical or swap I/O */
#ifdef NU
	caddr_t b_xaddr;
	daddr_t b_xblkno;
	int b_xcount;
        unsigned int b_xresid;
	int	b_pfcent;
	struct buf *b_scatbuf;		/* pointer to scatter table for MSC */
	struct buf *b_cmdaddr;		/* address of command block for MSC */
	dev_t b_odev;
	daddr_t b_oblkno;
	dev_t b_mirdev;
	struct buf *b_otherbp;
#endif
	sema_t b_iodone;		/* buffer indicating io done */
	struct   buf	*b_next;	/* Links for */
      	struct	 buf	*b_prev;	/* LRU stack. */
	struct   hbuf	*b_hash;	/* Pointer to hash list buffer is on. */
/* DFBC */
	long		b_cmap;		/* Index to cmap struct for page
					 this buffer is on. */
	long		b_time_stamp;	/* LRU time stamp used by VM. */
/* DFBC */
/* LOGGING */
        struct l_anchor *b_lloc;        /* log location is record number in log */
                                        /* partition.  Record zero is the first */
                                        /* record.  It is also used as an index */
                                        /* into the lanchor vector.             */

        struct buf     *b_mbnext;       /* Links for modified buffers for use   */
        struct buf     *b_mbprev;       /* by the logging system.               */
/* LOGGING */
};

/* DFBC */
struct aux_cmap
{
	struct	aux_cmap   *ac_forw;	/* Links used to maintian page oriented */
	struct  aux_cmap   *ac_back;    /* LRU ring for pages owned by fcb. */
	long		   ac_time_stamp; /* Time stamp for pages owned by fcb. */
};
/* DFBC */

#ifdef NU
/*
 * Struct to describe the clustered i/o done by
 * swap for the paging system.
 */ 
struct swinfo 
{
	int	sw_size;
	caddr_t	sw_addr;
	int	sw_pfcent;
	int	sw_curcnt;
	caddr_t	sw_oaddr;
	int	sw_oblkno;
};
#endif

#ifdef KERNEL
extern sema_t b_freeslp;		/* sema for bio freelist sleep */
extern sema_t b_lrustack[];		/* sema for LRU stack. */
extern struct buf *b_most_inactive[]; /* pointer to most inactive buffer.*/
extern struct buf pbuf[];		/* Physio header pool */
struct pfree {
	int	b_flags;
	struct	buf *av_forw;
};
extern struct pfree pfreelist;		/* head of physio pool */
extern sema_t p_freelock;		/* sema for physio free pool */
extern sema_t p_freecnt;		/* count for physio free elements */
# ifdef NU
/* 
 * The swap bufs are allocated dynamically.
 */
extern struct buf bswlist;		/* head of swap buffer list */
extern int	  swbuf_cnt;		/* current # of avail swap bufs */
extern struct buf *swbuf;		/* the swap bufs */
extern struct swinfo *swinfo;		/* the swap info headers */
# endif
#endif

/*
 * These flags are kept in b_flags.
 */
#define	B_WRITE		0x0000	/* non-read pseudo-flag */
#define	B_READ		0x0001	/* read when I/O occurs */
#define	B_DONE		0x0002	/* transaction finished */
#define	B_ERROR		0x0004	/* transaction aborted */
#define	B_BUSY		0x0008	/* not on av_forw/back list */
#define	B_PHYS		0x0010	/* Physical IO potentially using UNIBUS map */
#ifdef m68k
#define	B_FORMAT	0x0020	/* format track when I/O occurs */
#else
#define	B_MAP		0x0020	/* This block has the UNIBUS map allocated */
#endif
#define	B_WANTED	0x0040	/* issue wakeup when BUSY goes off */
#define	B_AGE		0x0080	/* delayed write for correct aging */
#define	B_ASYNC		0x0100	/* don't wait for I/O completion */
#define	B_DELWRI	0x0200	/* don't write till block leaves available list */
#define B_RETAIN	0x0400	/* Buffer has retain status. */
#define	B_STALE 	0x0800
#ifdef NU
#define B_UTABLE	0x1000	/* swapping SEG_SYS */
#define B_PTE		0x2000	/* swapping page tables */
#define B_PAGEIO	0x4000	/* doing paging i/o */
#define B_MAPPED	0x8000	/* b_addr is mapped into kernel */
#define B_2NDCYCLE	0x10000	/* Buffer is in second lru cycle. */
#endif
#define B_NORELSE	0x00020000  /* bwrite will not release this block */
#define B_NODEV		0x00040000  /* bscn   will never find on cache    */
#define B_INTERN	0x00080000  /* internal command flag for driver */
#define B_LLIST		0x00100000 /* linked list of bufs */
#define B_MVFS		0x00200000 /* multivolume flag */
#define B_VSCOPY	0x00400000 /* special flag between bio and vscopy */

/* LOGGING */
#define B_DWY0          0x00800000 /* Don't write yet flag for logging. */
#define B_WIRED         0x01000000 /* Buffer is wired. i. e. don't preempt.    */
#define B_LLOC_VALID    0x02000000 /* The buffer is on a modified list. This
				    means that b_lloc has a valid pointer to
				    an l_anchor structure. */
#define B_IFIFO         0x04000000 /* Buffer is being used for fifo data. */
/* LOGGING */
#define B_COPY		0x08000000 /* special flag for mirroring */
#define B_SECOND	0x10000000 /* special flag for mirroring */
#define B_MIRR		0x20000000 /* special flag for mirroring */
#define B_MIRDON	0x40000000 /* special flag for mirroring */
#define B_DWY1          0x80000000 /* Don't write yet flag for logging. */

/*
 * Fast access to buffers in cache by hashing.
 */

#define	bhash(d,b)	(&hbuf[((int)d+(int)b)&v.v_hmask])

struct hbuf
{
	        lock_t	 lock;
		ushort	 algn;		/* alignment short */
	struct  buf	*bp;
};

extern struct hbuf hbuf[];

#define	BS_NEED		0x0001
#define	BS_WANT 	0x0002
#define	BS_GRAVY	0x0004
#define	BS_READA	(BS_WANT|BS_GRAVY)
#define	BS_INCORE	0x0008
#define	BS_NOLOCK	0x0020

#define	B_PRIHI		0x0010
#define	B_PRIMD		0x0004
#define	B_PRILO		0x0001
#define	B_PRIFREE	0x0000

#define	BF_FALL		0x0000
#define	BF_FFREE	0x0001
/* LOGGING */
#define BF_PHYSICAL     0x0002
/* LOGGING */


#define LRUTOP		0x00000000
#define LRUBOTTOM 	0x00000001
#define NFREEFLUSH	64

#define GOT_BUF		0x0
#define BUF_LOCKED	0x1
#define BUF_DIRTY	0x2


/* DFBC */
#define B_MIN_PAGES	0x20
#define B_FM_TO_VM_TIME_DELTA 1
#define B_VM_TO_FM_TIME_DELTA 1
#define B_SWAPOUT_THRESHOLD 90
#define B_SWAPIN_THRESHOLD 120
#define B_SWAP_RATE_THRESHOLD 5
#define B_MIN_SWAPIN_RATE 15 
#define B_MAX_XFER 64
#define B_LONG_XFER 32
/* DFBC */

/* LOGGING */
/*
 * Log anchor for a doubly linked list of modified buffers which must be
 * flushed before a particular log partition location is overwritten.  These
 * anchors are kept in a vector, lanchors which holds NLLOC of these structures.
 */

struct l_anchor          
{   lock_t	la_lock;  
    ushort	la_count;
    struct buf *la_first;
};                       
                        
/*
 * The following structure is only used in the Log Header which is defined
 * below.  Actually the Log Header consists of a single l_header followed by a
 * vector of l_devtab_ent.  The code is written to allow the number of elements
 * in l_devtab_ent to vary from one partition to the next.  This is just for
 * flexibility in the initial tuning.  In the shipped system the size of the
 * l_devtab_ent vector will be pinned down to a constant.  Or maybe not.  In
 * any case, the idea is to keep these two structures in a single contiguous
 * chunk of RAM and write them as one logical record whenever the Log Header is
 * to be updated.
 */

struct l_devtab_ent
{
	dev_t lh_dev;         /* device number */
	uint  lh_seqnum;      /* log record number current when mounted */
	uint  lh_mount_stamp; /* nanosecond timer when mounted */
	uint  lh_count;	      /* Open/Mount count. */
	uint  lh_post_ok;     /* Device is ok for post. */
};

struct l_header
{
	uint                 lh_header_size;  /* (in bytes) This includes this structure
                                               * and the device table which follows it on
                                               * on disk.  This also gives after rounding
					       * up the character position of the first
					       * slot in the partition.
					       */
	uint                 lh_slot_size;    /* (in blocks)  The log record size.  This is
                                               * redundant here but it is included to
					       * allow us to vary the slot size in the
					       * future.
					       */
	struct l_devtab_ent *lh_devtab;
	uint                 lh_nslots;       /* Number of slots in the log partition */
	uint                 lh_ndte;         /* Number of device table entries */
	uint		     lh_nvram_used;   /* Indicates NVRAM was*/
					      /*used on the previous*/
					      /*cycle */	
        uint		     lh_magic_number; /* Magic number for log
					       header. */
	int		     lh_spare1;
	int		     lh_spare2;
};

#define LOG_MAGIC_NUMBER 	0xb39e5a8c

/*
 * A log partition contains a header, defined above, and a number of slots.  Each
 * slot can contain a variable number of log records which are defined below.
 *
 * A log record consists of a l_lr_head, a variable number of block entries, and
 * a l_lr_tail.
 *
 * A block entry consists of a lr_be_head and a variable length of data.
 */

/*
 * The following structure defines the leading information for a log
 * record.
 */

struct l_lr_head
{
	uint lr_seqnum;   /* The unique sequence number kept in logger */
	uint lr_size;     /* The size of the data which follows in bytes */
	uint lr_checksum; /* Logical record checksum. */	
};

/*
 * The following structure defines the trailing information for a logical record.
 */
struct l_lr_tail
{
	uint lr_seqnum;   /* This should match that in the corresponding l_lr_head */
};

/*
 * The following structure define the leading information for a block entry in
 * a logical record.
 */
struct lr_be_head
{
	dev_t   be_dev;
	daddr_t be_bno;
	ushort  be_offset;
	short   be_size;
};

/*
 * The following structure is defined to collect all of the global variables for the kernel
 * logging system.  There is only one instance of this structure and it is initialized in
 * main.
 */
struct logger
{
	struct l_header *l_header;      /* Log header pointer */
	struct buf      *l_header_bh;   /* buf header allocated for writing l_header */
	int              l_buffer_left; /* Log buffer remaining space in bytes*/
	uint             l_rec_start;   /* Offset in buffer of start of current log record */
	uint             l_buf_pos;     /* Log buffer position char offset in bytes */
	uint             l_slot_no;     /* Current slot number in log partition.  The first
					 * slot is number 1.
					 */
	char            *l_buffer[2];   /* Log buffer pointers */
	struct buf      *l_buffer_bh;   /* buf header allocated for writing l_buffer */
	struct l_anchor *l_anchors;     /* Log modified buffer list anchor vector pointer */
	uint             l_seqnum;      /* Next sequence number.  This is the number
                                         * used to label the individual lsync additions
					 * to the log records.
					 */
	char             l_enabled;     /* 0 if logging disabled
					 * 1 if logging is active and forced writes are forced
					 * 2 if logging is active and forced writes are logged
					 */
	char             l_loggable;    /* Logical record is loggable.  This field is used
					 * to communicate between logger functions.  It is
					 * set in l_prep.
					 */
	char             filler[2];
};


/*
 Structure to define the mapping between bdevsw[] indexes
 and cdevsw[] indexes for loggable devices.
 */
struct log_c_b_map {
	short	c_index;
	short	b_index;
};


/* LOGGING */
extern struct log_c_b_map log_c_b_map[];
extern struct logger sys_logger;
extern int log_buffer_usage_table[];
/* LOGGING */






