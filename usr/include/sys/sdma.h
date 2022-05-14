/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1984.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char sdma_h[] = "@(#)sdma.h	1.4 (TI) 90/11/05";
#endif	SCCSID

struct sdmainfo
{
	int	sdmamax,	/* max lisp segment size		*/
		sdmamin,	/* min lisp segment size		*/
		sdmamni,	/* # of allowable lisp segments system wide */
		sdmaseg,	/* max attached lisp segments per process*/
		sdmaall;	/* max total allowable lisp memory system wide*/
};
			
struct	sdma_ds
{
	unsigned long	vaddr;
	unsigned long	segsz;
	unsigned long	flags;
	short	id;
	short	status;
} ;

struct	sdma
{
	unsigned long	vaddr;
	unsigned long	segsz;
	unsigned long	flags;
	long	*frame;
} ;

#define sdma_exit(x)	sdma_exec(x)

#define btopgs(vaddr, bytes)	(((bytes) + ((long)(vaddr)&0x3ff) + 1023)/1024)
#define BTOPGS(bytes)		(((bytes) + 2046)/1024)

#define bto4kpgs(vaddr, bytes) \
                   (((bytes) + ((long)(vaddr) & (NBPC-1)) + (NBPC-1))/NBPC)

#define	SIOCSET	('S'<<8 | 0)	/* Lock (set) pages in memory */
#define	SIOCREL	('S'<<8 | 1)	/* Release pages */
#define	SIOCGET	('S'<<8 | 2)	/* Get # of pages available */

/* Flags bits: */
/* Setting the NOCACHE bit causes the cache to be turned off for the
 * entire segment. This should be done only where it is necessary,
 * as it DESTROYS performance for any accesses to that segment.
 * Remember, cache gets flushed every context switch time
 * anyway.
 */
#define NOCACHE	1

