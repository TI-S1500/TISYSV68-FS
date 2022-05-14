/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char pmapinfo_h[] = "@(#)pmapinfo.h	1.4 (TI) 90/08/09";
#endif	SCCSID

/*	The pmapinfo struct is used store information pertaining to a 
 *	process' segments.  This information is used to calculate the 
 *	number of page map pages needed by the process.  The information 
 *	is also used to build the page maps (ie. how to map L2s to L1s 
 *	and L3s to L2s.
 */

struct 	pmapinfo
{
	unsigned long	addr;	/* beginning virtual address of seg */
	unsigned long	size;	/* size of seg in bytes */
	unsigned int	nL2s;	/* no. of additional L2 pgs needed to map seg */
	unsigned int	nL3s;	/* no. of additional L3 pgs needed to map seg */
	unsigned int	begL2;	/* physical offset in clicks of seg's beginning
				   L2 page from start of process' page maps */
	unsigned int	begL3;	/* physical offset in clicks of seg's beginning
				   L3 page from start of process' page maps */

};

/*
 * define parameters needed by following macros and routine 'nptpages'.
 * note: other parameters referenced by macros are defined in
 *       "sys/param.h".
 */

#define	TOTAL		0


/* Macros needed by 'nptpages' in module 'vmsubr.c' to calculate number
 * of L2 and L3 page maps needed.  Macros also calculate beginning and
 * ending offsets for L2's and L3's in the page maps.
 */

#define	L2INDEX(addr)   ((addr) >> BPL1SHIFT)  	/* index of L2 in L1 pg for a
					           fully populated addr space */
#define	L3INDEX(addr)   ((addr) >> BPL2SHIFT) 	/* index of L3 in L2 pgs for a
						   fully populated addr space */
#define	PTEINDEX(addr) 	((addr) >> BPCSHIFT)	/* index of pte in L3 pgs for a
						   fully populated addr space */

/* Following macros calculate start and ending indices for L2's and L3's */
/* in a fully populated address space 			        	 */

#define STARTL2(segp) 	(L2INDEX((segp)->addr))
#define	STARTL3(segp) 	(L3INDEX((segp)->addr))

#define	ENDL2(segp)   	(L2INDEX((segp)->addr + (segp)->size - 1))
#define	ENDL3(segp)   	(L3INDEX((segp)->addr + (segp)->size - 1))


/* Following macros calculate number of L2's and L3's needed to map in */
/* segment's address space					       */

#define	NL2S(segp)    	(ENDL2(segp) - STARTL2(segp) + 1)
#define	NL3S(segp)    	(ENDL3(segp) - STARTL3(segp) + 1)


/* Following macros calculate index for L2's and L3's in the physical */
/* page maps for a process 					      */

#define	L2ENT(segp)   	(((segp)->begL2 * NPTESL2PT) + \
				(L3INDEX((segp)->addr) & (NPTESL2PT-1)))

#define	L3ENT(segp)   	(((segp)->begL3 * NPTESL3PT) + \
				(PTEINDEX((segp)->addr) & (NPTESL3PT-1)))
