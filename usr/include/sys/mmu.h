/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char mmu_h[] = "@(#)mmu.h	1.9 (TI) 91/02/25";
#endif	SCCSID

/*
*	This is the header file for the UNIX V/68 generic
*	MMU interface.  It provides the information that
*	is used by the various routines that call MMU
*	functions in the files  os/mmuhi.c and os/mmulo.c.
*/

/*
 * Make sure that the virtual memory smap is defined
 */
#ifndef SMMIN
#ifdef KERNEL
#include "sys/smap.h"
#else
#include <sys/smap.h>
#endif
#endif

#ifndef SEG_TEXT
#ifdef KERNEL
#include "sys/param.h"
#else
#include <sys/param.h>
#endif
#endif

/*
 *  Structure describing a process's address space
 *  (see param.h for SEG_xxx defines).
 */
struct	mmu_table
{
	struct proc *	mmu_proc;	/* Pointer to related proc */
	int		mmu_pmpaddr;	/* Click start address of page maps */
	caddr_t 	mmu_pmvaddr;	/* Kernal virtual addr of page maps */
	long		mmu_pmsize;	/* Number of page maps (in bytes)   */
	short		mmu_cpmpages;	/* Current number of page maps pages */
	short		mmu_npmpages;	/* Needed  number of page maps pages */
	long 		mmu_syspte[USIZE];/*L3 ptes for SEG_SYS (u. & kstack)*/
	long		mmu_table_spare;
};

extern struct mmu_table mmu_table[];	/* The internal table itself */

/*
 *  The following define the status bits in segdesc.flags.
 */

#define SEG_VALID	0x0001	/* Segment allocated in mem */
#define SEG_SWAPPED	0x0002	/* Segment currently swapped out */
#define SEG_PROTECT	0x0004	/* user read-only, kernal read-write */
#define SEG_TEXT_PTES   0x0008  /* Text ptes are filled in, so they can
                                 * be copied, change ownership to and 
                                 * distributed to in all cases
                                */
/*
 *  NOTE: Remaining bits MUST correspond with SHM Message Operation Flags
 *	  (see shm.h).
 */
#define	SEG_RDONLY	010000
#define	SEG_RND		020000

/*
 *  The following convert from a proc pointer (or proc/seg)
 *  to a mmu_table.
 */
#define	ptom(p)		((struct mmu_table *)((struct proc *)p)->p_mmuent)

