/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char nubus_h[] = "@(#)nubus.h	1.4 (TI) 86/09/19";
#endif	SCCSID

/*
 * Kernel struct for each NuBus segment.  Initialized by 'nubusinit'.
 * Attach and detach calls use 'nb_dev' as the lookup "key", and the
 * 'mmu_ndx' value in a SEG_NUBUS mmu_entry is also a 'nb_dev' value.
 */
struct nubus_seg
{
	dev_t	nb_dev;		/* major/minor "key", 0 => not defined */
	long	nb_addr;	/* 32-bit NuBus base address */
	long	nb_size;	/* bytes */
	caddr_t	nb_kvwaddr;	/* kernel virtual address for NuBus seg */
	daddr_t	nb_ptdaddr;	/* swap area for pte's */
	ushort	nb_status;	/* flags */
	ushort	nb_count;	/* number procs attached */
	ushort	nb_ccount;	/* number attached in memory */
	short	nb_padding;
};


#ifdef KERNEL

extern int nbsegcount;
extern struct nubus_seg nubus_seg[];

extern struct nubus_seg *nb_lookup();
extern caddr_t nubusinit();

#endif
