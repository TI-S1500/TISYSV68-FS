/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char pte_h[] = "@(#)pte.h	1.14 (TI) 90/09/25";
#endif	SCCSID

#ifdef	PCC
/* Note of historical interest: */

/*
 *  The following pte structures have somewhat bizarre declarations in 
 *  order to overcome a bug found in pcc.  We would like to
 *  have the ptes contain "unsigned int pg_pfnum:22" (pg_blkno is
 *  similar).  However, if we do this, pcc generates long moves
 *  to access all fields of the pte.  This is as expected, except that
 *  a long move offset two bytes into the pte is used to access the
 *  bit fields in the least significant byte.  In particular, the
 *  following code is generated to access the pg_fod field:
 *		mov.l	pte,%a2
 *		mov.l	2(%a2),%d0
 *		lsr.l	&22,%d0
 *		and.l	&1,%d0
 *  If the pte is the last long in a page, this causes the first two
 *  bytes of the next page to be referenced.  This is hardly appropriate
 *  for a memory mapped architecture.
 */

struct 	ptd {	/* pointer table descriptor */
	unsigned long	pg_addr    :28, /* Address of next level table	     */
		        pg_a       :1,  /* Accessed bit			     */
			pg_wp	   :1,  /* Write-protect bit                 */
			pg_dt	   :2;  /* Descriptor type (valid bit)       */	
};


struct	pgd	/* page table descriptor */
{
	unsigned long	:8,	    /* First 22 bits contain page frame */
			:8,	    /*   address of requested page      */
			:5,
		 	pg_gbl	:1, /* Page is global ATC entry - 040 only */
		 	pg_alloc:1, /* Page currently allocated		*/
			pg_fod  :1, /* Page fill-on-demand indicator */
			pg_g	:1, /* Gate indicator, not used by MMB */
			pg_ci	:1, /* Cache inhibit indicator */
			pg_lk	:1, /* Page lock bit, not used by MMB */
			pg_m	:1, /* Modified bit */
			pg_a	:1, /* Accessed bit */
			pg_wp	:1, /* Write-protect bit */
			pg_dt  :2;  /* Descriptor type (valid bit) */	
};

struct	fpgd	/* page table descriptor of a page not yet allocated */
{
	unsigned long	:8,	     /* First 22 bits contain filesystem */
			:8,	     /* block number	                 */
			:6,
		 	pg_ftext:1,  /* Page initialization indicator */
			pg_fod  :1,  /* Page fill-on-demand indicator */
			pg_g	:1,  /* Gate indicator, not used by MMB */
			pg_ci	:1,  /* Cache inhibit indicator */
			pg_lk	:1,  /* Page lock bit, not used by MMB */
			pg_m	:1,  /* Modified bit */
			pg_a	:1,  /* Accessed bit */
			pg_wp	:1,  /* Write-protect bit */
			pg_dt  :2;  /* Descriptor type (valid bit) */	
};
#else
/* This structure is bit swapped to accomidate the SVS C compiler */

struct 	ptd	/* pointer table descriptor */
{
	unsigned long	pg_dt	   :2,  /* Descriptor type (valid bit)       */	
			pg_wp	   :1,  /* Write-protect bit                 */
			pg_a       :1,  /* Accessed bit			     */
			pg_addr    :28; /* Address of next level table	     */
};

struct	pgd	/* page table descriptor */
{
	unsigned long	pg_dt	:2,	/* Descriptor type (valid bit) */
			pg_wp	:1,	/* Write-protect bit */
			pg_a	:1,	/* Accessed bit */
			pg_m	:1,	/* Modified bit */
			pg_lk	:1,	/* Page lock bit, not used by MMB */
			pg_ci	:1,	/* Cache inhibit indicator */
			pg_g	:1,	/* Gate indicator, not used by MMB */
			pg_fod  :1,	/* Page fill-on-demand indicator */
		 	pg_alloc:1,	/* Page currently allocated	*/
			pg_nuba	:21,	/* Page frame address */
			pg_pfa	:1;	/* Page frame allocated */
};

struct	fpgd	/* page table descriptor of a page not yet allocated */
{
	unsigned long	pg_dt	:2,	/* Descriptor type (valid bit) */
			pg_wp	:1,	/* Write-protect bit */
			pg_a	:1,	/* Accessed bit */
			pg_m	:1,	/* Modified bit */
			pg_lk	:1,	/* Page lock bit, not used by MMB */
			pg_ci	:1,	/* Cache inhibit indicator */
			pg_g	:1,	/* Gate indicator, not used by MMB */
			pg_fod  :1,	/* Page fill-on-demand indicator */
		 	pg_ftext:1,	/* Swap map invalid indicator */
			pg_blkno:21,	/* Page frame block number */
			pg_pfa	:1;	/* Page frame allocated */
};
#endif	PCC

/*
 * mnemonics for old codgers who grew
 * up with "page table entries"...
 */
#define L0pte	ptd
#define L1pte	ptd 
#define L2pte	ptd 
#define L3pte	pgd 
#define pte	pgd 
#define fpte	fpgd 

#define NBPP 		4096
#define NOSLEEP    	01

#define	PG_RW  		0x000L      /* Read/write (i.e., not write-prot.) */	
#define	PG_V		0x001L	    /* Page descriptor is valid */
#define	PG_DTSHORT 	0x002L      /* Ptr descriptor type (ptr to short) */
#define	PG_DTLONG 	0x003L      /* Ptr descriptor type (ptr to long) */
#define	PG_DTVAL 	0x003L      /* Valid ptr/page descriptor type mask */
#define	PG_WP		0x004L	    /* Page is write protected (read only) */
#define	PG_A		0x008L	    /* Page is accessed */
#define	PG_M		0x010L	    /* Page is modified */
#define	PG_LK		0x020L	    /* Page is locked in ATC */
#define	PG_CPYBK	0x020L	    /* Page is cacheable with copyback cache */
#define	pg_cpybk	pg_lk	    /* Overlap of bit definitions !	*/
#define	PG_CI		0x040L	    /* Page is cache-inhibited */
#define	PG_G		0x080L	    /* Gate flag (unused) */
#define	PG_FOD		0x100L	    /* Page is fill-on-demand */
#define	PG_ALLOC 	0x200L      /* Page currently allocated	*/
#define	PG_FTEXT 	0x200L      /* Page should be initialized */
#define	PG_WAL 	       0x1C00L      /* User/supervisor write access */
#define	PG_RAL 	       0xE000L      /* User/supervisor read access */
#define	PG_LU  	   0x80000000L      /* Lower limit */	

/*
 * These two macros are needed because of the pcc bug explained above.
 * These macros assume the following about a pte:
 *	1. A pfnum (pte) is 20 bits, left justified.  The pg_alloc bit
 *	   is set and the pg_fod == 0 whenever 
 *	   whenever a pte points to a NuBus address.
 *	2. A blkno (fpte,pte) is 21 bits and occupies bits
 *	   10-30, leaving bit 31 unset.
 *
 * This is also assumed by PFALLOC in vmmacros.h.
 */
#define gpteblk(fpte)		((*(unsigned *)(fpte)) >> 10)
#define	spteblk(fpte, blk)	(*(unsigned *)(fpte) = ((*(unsigned *)(fpte))\
				& 0x03ff) | (((unsigned)(blk)) << 10))
#define gptepfn(pte)	(((*(unsigned *)(pte)&(PG_ALLOC | PG_FOD))==PG_ALLOC)?\
				((*(unsigned *)(pte)) >> BPCSHIFT) : 0x0L)
#define	sptepfn(pte, pfn)	(*(unsigned *)(pte) = ((*(unsigned *)(pte))\
				& PGOFSET) | (((unsigned)(pfn)) << BPCSHIFT))
