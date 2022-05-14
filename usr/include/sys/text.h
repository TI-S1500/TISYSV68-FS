/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char text_h[] = "@(#)text.h	1.8 (TI) 88/11/11";
#endif	SCCSID

#ifdef NU
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
#endif

/*	@(#)text.h	1.1	UNIX System V/68 */
/*
 * Text structure.
 * One allocated per pure procedure on swap device.
 * Manipulated by text.c
 */
struct text
{
#ifndef NU
	short	x_daddr;	/* disk address of segment (rel. to swplo) */
#endif	
	short	x_size;		/* size (clicks) */
#ifdef NU
	short	x_poip;
	long	x_rssize;
	long	x_swrss;
	struct smap x_smap;	/* smap structure for text */
	daddr_t x_ptdaddr;	/* swap address for ptes */
#endif
	struct proc *x_caddr;	/* ptr to linked proc, if loaded */
	struct inode *x_iptr;	/* inode of prototype */
	struct inode *x_siptr;	/* inode of shared library */
	sema_t	x_sema;		/* lock on text structure */
	sema_t	x_wait;		/* wait for load/swap to finish	*/
	short	x_count;	/* reference count */
	short	x_ccount;	/* number of loaded references */
	char	x_flag;		/* traced, written flags */
	char	x_spare;
	ushort	x_encr_l;
	caddr_t x_encr;
};

extern struct text text[];

#define	XTRC	01		/* Text may be written, exclusive use */
#define	XWRIT	02		/* Text written into, must swap out */
#define	XLOAD	04		/* Currently being read from file */
#define	XLOCK	010		/* Being swapped in or out */
#define	XWANT	020		/* Wanted for swapping */
#define XPAGED	040		/* Text was paged in (fill on demand) */
#define	XSHARED	0100		/* Linked with a shared library */
#define	XSPADEC	0200		/* SPA password decoded */
