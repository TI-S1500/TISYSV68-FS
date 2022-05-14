/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char cmap_h[] = "@(#)cmap.h	1.15 (TI) 90/12/13";
#endif	SCCSID

/* 
 * core map - one entry per available page frame
 * 
 * Cmap keeps the state of each potentially available page
 * frame in the system.  Space for the cmap array is reserved
 * by startup() and the structure is initialized in vminit().
 *
 * With the current field sizes, the following limits are imposed:
 *	256K free physical page frames (c_forw, c_back)
 *	256M virtual space per logical segment (c_page)
 *	2048 proc, text, and shared memory structures (c_ndx, c_refcnt)
 */
struct cmap
{
	unsigned int	c_forw:	18,	/* index of next free list entry */
			c_refcnt: 13,	/* number ptes referencing page */
			:1;
	unsigned int	c_back: 18,	/* index of previous free list entry */
			c_ndx: 13,	/* index of owning proc/text/shm */
			:1;

	unsigned int	c_page:	18,	/* virtual page number in segment */
			c_want:	13,	/* someone wants to lock this entry */
			:1;
	unsigned int	c_blkno: 24,	/* blk where text first came from */
			c_type:	3,	/* type of page (see param.h) */
			c_sdma: 1,	/* page locked due to sdma */
			c_badpg: 1,	/* page experienced parity error */
			c_free:	1,	/* page on free list	*/
			c_lock:	1,	/* state being modified, hands off */
	  		:1;
/* DFBC */
	long	        c_time_stamp;	/* lru time stamp for DFBC */
	struct buf      *c_buf;		/* Pointer to buf for fbc */
/* DFBC */		
	struct segdesc	*c_segdptr;	/* Pointer to segdesc */
};

/*
 * Clock page replacement stuff.
 */
struct pfclk
{
	int	nscan;
	int	desscan;
	int	hand;
};

#define MAXSEGSIZ (128*1024*1024/NBPC)/* max segment size, imposed by cmap.h */

/* 
 * Head/tail of free list.
 */
#define	CMFREE	0		/* cmap[CMFREE] heads free list */
#define	CMNULL	(-1)		/* end of list index */

/* 
 * Misc goodies.
 */
#ifdef KERNEL
extern	struct	cmap *cmap;	/* the core map itself */
extern	struct	cmap zcmap;	/* a cmap full of zeros	*/
#endif
