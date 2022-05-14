/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char mmu_h[] = "@(#)mmu.h	1.7 (TI) 90/08/09";
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
 *  Structure describing a single segment within a process.
 */
struct mmu_entry
{
	ushort		mmu_status;	/* Flags for this segment */
	ushort		mmu_spare;	/* spare word for long alignment */
	caddr_t 	mmu_vaddr;	/* Virtual start address of segment */
	long		mmu_size;	/* Segment size in bytes */
	struct pte *	mmu_pte;	/* Base pte in page maps */
	dev_t		mmu_ndx;	/* General value per segment -- */
					/* 'dev' value for SEG_NUBUS    */
};

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
	struct smap 	mmu_dmap;	/* SEG_DATA  swap map */
	struct smap 	mmu_smap;	/* SEG_STACK swap map */
	long 		mmu_syspte[USIZE]; /*L2 ptes for SEG_SYS (u. & kstack)*/
	struct mmu_entry mmu_entry[SEG_FIXED];
	short		 mmu_att_cnt;
	short		 mmu_table_spare;
	struct mmu_attach * mmu_attachp; /* ptr to attach structures (if any)*/
};
struct	mmu_attach	/* For use with 'attached' segments	*/
{
	struct mmu_entry att_mmu_entry;
	struct mmu_attach * att_next; /* ptr to next attach structure */
	union {
		struct shmid_ds	  * att_shmemp;
		struct nubus_seg  * att_nubus_segp;
	} m_att;

};

extern struct mmu_table mmu_table[];	/* The internal table itself */
extern struct mmu_attach mmu_attach[];	/* The attach struct array	*/
struct mmu_attach *mmu_att_alloc();

/*
 *  The following define the status bits in mmu_status.
 */
#define SEG_VALID	0001	/* Segment allocated in mem */
#define SEG_SWAPPED	0002	/* Segment currently swapped out */
#define SEG_PROTECT	0004	/* user read-only, kernal read-write */
#define	SEG_ALLOC	0010	/* mmu_attach structure is in use	*/
#define SEG_SHMEM	0020    /* shared memory segment		*/
#define SEG_NUB		0040	/* nubus segment			*/
/*
 *  NOTE: Remaining bits MUST correspond with SHM Message Operation Flags
 *	  (see shm.h).
 */
#define	SEG_RDONLY	010000
#define	SEG_RND		020000
/*
 *  The following convert from a proc pointer (or proc/seg)
 *  to a mmu_table (or mmu_entry) pointer.
 *  NOTE:  The ptomep() macro is useful ONLY for Text, Data, & Stack entries !
 */
#define	ptom(p)		((struct mmu_table *)((struct proc *)p)->p_mmuent)
#define ptomep(p,seg)	(&ptom(p)->mmu_entry[(seg)-1])
