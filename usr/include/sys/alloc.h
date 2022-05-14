/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char alloc_h[] = "@(#)alloc.h	1.3 (TI) 86/02/04";
#endif	SCCSID

/* @(#)alloc.h  2.15    UNIX System V/68 */
/* 
 variables needed for bit map allocation and deallocation routines
*/

#define BM_ALLOC  0x01		/* flag to allocate space in the bit map */
#define BM_FREE   0x00		/* flag to deallocate space */
#define MAXSIZPBM 8192		/* number of bits in a full bit map */
#define WRDSIZ    32		/* the number of bits in a word */
#define MAXSHFT   31		/* the most bits to shift in a word */
#define LEFTBIT   0x80000000	/* the leftmost bit of a word */
#define MAPBITS   8191		/* the max size of the bit map - 1 */
#define NUMBLOCKS 8192		/* the number of blocks represented by 1 bm */

#define ERR1      95		/* error - tried to change bits when they were
				   not all the same - 1's for deallocation */
#define ERR2      96		/* same as ERR1 for allocation */
#define ERR3      97		/* number of bits to change don't fit in bm */
#define TOOLARGE  98		/* requested allocation/deallocation goes
				   beyond the end of the file system */

#define SHIFTNUM  13		/* number to shift the block number to extract
				   the bit map number */
#define NUMMASK   0x1fff	/* the number to AND the block number with to
				   obtain the offset in the bit map that
				   represents the block number */
