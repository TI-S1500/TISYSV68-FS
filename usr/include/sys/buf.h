/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char sccsid[] = "@(#)buf.h	1.19 (TI) 89/11/01";
#endif	SCCSID

/*	@(#)buf.h	1.2	UNIX System V/68 */
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
	short	b_unusd1;		/* unused for now */
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
#endif
	sema_t b_iodone;		/* buffer indicating io done */

	short    b_pri;			/* buffer priority */
	short    b_ppri;		/* buffer priority */
};

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
};
#endif

#ifdef KERNEL
extern sema_t b_freeslp;		/* sema for bio freelist sleep */
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
#define	B_OPEN		0x0400	/* open routine called */
#define	B_STALE 	0x0800
#ifdef NU
#define B_UTABLE	0x1000	/* swapping SEG_SYS */
#define B_PTE		0x2000	/* swapping page tables */
#define B_PAGEIO	0x4000	/* doing paging i/o */
#define B_MAPPED	0x8000	/* b_addr is mapped into kernel */
#define B_VALID		0x10000 /* page frame allocated, only hdrs in */
				/* the bfreelist will have ~B_VALID   */
#endif
#define B_NORELSE	0x00020000  /* bwrite will not release this block */
#define B_NODEV		0x00040000  /* bscn   will never find on cache    */
#define B_INTERN	0x00080000  /* internal command flag for driver */
#define B_LLIST		0x00100000 /* linked list of bufs */
#define B_MVFS		0x00200000 /* multivolume flag */
#define B_VSCOPY	0x00400000 /* special flag between bio and vscopy */

/*
 * Fast access to buffers in cache by hashing.
 */

#define	bhash(d,b)	(&hbuf[((int)d+(int)b)&v.v_hmask])

struct hbuf
{
	        lock_t	 lock;
		ushort	 algn;		/* alignment short */
	struct	buf	*bp[MAXCPU];
	struct	buf	*bpfree[MAXCPU];
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
