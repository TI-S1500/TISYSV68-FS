/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char seg_h[] = "@(#)seg.h	1.5 (TI) 91/04/05";
#endif	SCCSID

/*	@(#)seg.h	2.2	UNIX System V/68 */
/*
 * Memory management addresses and bits
 */
#ifndef SEG_SUBR
#define SEG_SUBR 1

#define	RO	SEG_PROTECT	/* access abilities */
#define	RW	0

struct iseg {
	struct segdesc *segdptr; 	/* pointer to first segdesc */
	short flags;		 	/* Flags */
	lock_t lock;	 		/* lock */
	short refcnt;			/* Reference count */
	sema_t sema;	 		/* Semaphore */
	struct inode *iptr;	 	/* pointer to Inode */
	struct iseg *next_iseg;	 	/* Free list or Inuse list */
	long	i_rssize[MAXCPU]; 	/* Iseg resident set size */
};

/*	Flags within iseg.flags		*/
#define	PTRACED 	0x0001	

struct segdesc {
	short type;
	short flags;
	union {
		struct proc *procptr;
		struct segdesc *freeptr;
	}gen_ptr;
	caddr_t virt_beg;		/* Virt in users space */
	unsigned long size;		/* size in bytes of seg */
	unsigned long isize;		/* size in bytes of seg */
	struct pte *proc_L3_ptr;	/* Pointer to users L3 ptes */
	struct segdesc *next_proc_sd_using_lib;
	struct segdesc *next_sd_for_proc;
	union {
		struct iseg *isegptr;	 	/* Normal case */
		struct shmid_ds *att_shmemp;	/* shared memory */
		struct nubus_seg *att_nubus_segp; /* Nubus segs */
	}gsegptr;
	union {
		unsigned long physindx; 	/* Byte offset in file */
		unsigned long devt;		/* Nubus segs pseudo dev */
	} index;
	struct segdsm *smptr_old;			/* Old_clones swapmap */
	struct segdsm *smptr;			/* To my swap map */
};

struct segdsm { 			/* segment swapmap structure */
	unsigned long refcnt;		/* Reference count on this smap */
	struct smap smap;		/* Real smap structure */
	struct segdsm *next_segdsm;	/* Free list pointer */
	};

struct free_segd_anch { 		/* Anchor for segdesc free list */
	struct segdesc *segdfree;	/* pointer to free list */
	unsigned long freecount;	/* number of free segdesc */
	};			

struct free_iseg_anch { 		/* Anchor for iseg free list */
	struct iseg *isegfree;		/* pointer to free list */
	unsigned long freecount;	/* number of free segdesc */
	};

struct free_segdsm_anch { 		/* Anchor for swapmaps free list */
	struct segdsm *segdsmfree;	/* pointer to free list */
	unsigned long freecount;	/* number of free swapmaps */
	};

struct used_iseg_anch {			/* Anchor for inuse isegs */
	struct iseg *head;		/* Head of list */
	struct iseg *tail;		/* Tail of list */
};

extern struct inode *votinode();
extern struct iseg *get_iseg(), *vtoiseg();
extern struct segdesc *segd_alloc(), *segd_clone(), *vtosegd(), *ptetosegd();
extern struct segdesc *get_home_segd(),*get_next_seg();
extern struct segdsm *segdsm_alloc();

extern struct iseg iseg[];
extern struct segdesc segdesc[];
extern struct segdsm segdsm[];
extern struct free_iseg_anch iseg_anch;     /* iseg free list        */
extern struct free_segd_anch segd_anch;     /* segd free list        */
extern struct free_segdsm_anch segdsm_anch; /* segdsm free list      */
extern struct used_iseg_anch iseg_used;     /* iseg used list        */
extern lock_t segdlock;			    /* global segdesc lock   */
extern lock_t iseglock;			    /* Global iseg lock      */
extern lock_t segdsmlock;		    /* Global segdsm lock    */


#endif
