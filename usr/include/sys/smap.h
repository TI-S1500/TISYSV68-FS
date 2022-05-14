/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char smap_h[] = "@(#)smap.h	1.5 (TI) 90/12/11";
#endif	SCCSID

/* 
 * Swap space map - one per segment
 *
 * Maps virtual swap space for this segment
 * to physical swap space.  Space is allocated
 * in contiguous chunks of sizes starting at
 * SMMIN blocks and doubling to SMMAX blocks.
 */

#define	NSMAP	18	/* size of swap map */
#define	SMMIN	16	/* min chunk size in blocks */
#define	SMMAX	16384	/* max chunk size in blocks */

struct smap
{
	long	sm_size;	/* current size used by proc */
	long	sm_alloc;	/* current actual size */
	daddr_t	sm_map[NSMAP];	/* 1st disk block number in each chunk */
};

#ifdef KERNEL
extern struct smap zsmap;	/* a zero filled smap */
#endif

/*
 * The following structure is that ``returned''
 * from a call to vstodb().
 */
struct	dblock
{
	daddr_t	db_base;	/* base of physical contig block */
	daddr_t	db_size;	/* size of block */
};
