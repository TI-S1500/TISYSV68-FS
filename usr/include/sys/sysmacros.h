/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char sysmacros_h[] = "@(#)sysmacros.h	1.9 (TI) 90/08/24";
#endif	SCCSID

/*
 * Some macros for units conversion
 */
/* Core clicks to segments and vice versa */
#define ctos(x) ((x+(NCPS-1))/NCPS)
#define	stoc(x) ((x)*NCPS)

/* Core clicks to disk blocks */
#define	ctod(x)		((x)*NCPD) 

/* inumber to disk address */
#ifdef INOSHIFT
#define	itod(x)	(daddr_t)(((unsigned)x+(2*INOPB-1))>>INOSHIFT)
#else
#define	itod(x)	(daddr_t)(((unsigned)x+(2*INOPB-1))/INOPB)
#endif

/* inumber to disk offset */
#ifdef INOSHIFT
#define	itoo(x)	(int)(((unsigned)x+(2*INOPB-1))&(INOPB-1))
#else
#define	itoo(x)	(int)(((unsigned)x+(2*INOPB-1))%INOPB)
#endif

/* clicks to bytes */
#ifdef BPCSHIFT
#define	ctob(x)	((unsigned)(x)<<BPCSHIFT)
#else
#define	ctob(x)	((x)*NBPC)
#endif

/* bytes to clicks */
#ifdef BPCSHIFT
#define	btoc(x)	(((unsigned)(x)+(NBPC-1))>>BPCSHIFT)
#define	btoct(x)	((unsigned)(x)>>BPCSHIFT)
#else
#define	btoc(x)	(((unsigned)(x)+(NBPC-1))/NBPC)
#define	btoct(x)	((unsigned)(x)/NBPC)
#endif

/* major part of a device */
#define	major(x)	(int)(((unsigned)x>>24)&0xff)
#define	bmajor(x)	(int)(((unsigned)x>>24)&037)

/* minor part of a device */
#define	minor(x)	(int)((unsigned)x&0xffffff)

/* make a device number */
#define	makedev(x,y)	(dev_t)(((x)<<24) | (y))

#ifdef NU

/* disk blocks to clicks */
#define dtoc(x) ((x+(NCPD-1))/NCPD)

/* disk blocks to bytes */
#define dtob(x)		(ctob(dtoc(x)))
#define btod(x)		(ctod(btoc(x)))

/* virtual addr to level 1, 2, and 3 map indices */
#define btol1(x)	((unsigned long)(x) >> BPL1SHIFT)
#define btol2(x)	((unsigned long)(x) >> BPL2SHIFT)
#define btol3(x)	((unsigned long)(x) >> BPCSHIFT)

#define	MIN(a,b)	((a < b) ? a : b)
#define MAX(a,b)	((a < b) ? b : a)

#define ASSERT(x)	if (!(x)) panic("ASSERT(x)");

#endif

/* tracing macro, useful for debugging */
#ifdef VMTRACE
#define	vm_trace(s,l1,l2,l3,l4,l5)	do_vmtrace(s,l1,l2,l3,l4,l5)
#else
#define	vm_trace(s,l1,l2,l3,l4,l5)
#endif
#define SNEXT(p)		(char *)((int)p + sizeof (short))
#define INEXT(p)		(char *)((int)p + sizeof (int))
#define LNEXT(p)		(char *)((int)p + sizeof (long))
#define	SALIGN(p)		(char *)(((int)p+1) & ~1)
#define	IALIGN(p)		(char *)(((int)p+3) & ~3)
#define	LALIGN(p)		(char *)(((int)p+3) & ~3)

/*
 *  Evaluate to true if the process is a server - Distributed UNIX
 */
#define	server()	(u.u_procp->p_sysid != 0)

/*
 * Defined for RFS client caching
 */

extern int rcacheinit;			/* RFS client caching flag */
extern unsigned long rfs_vcode;		/* version code for RFS caching */
/*int rcacheinit = 0;
unsigned long rfs_vcode = 0;*/

#define enable_cache(rcvd) \
{ \
}

#define disable_cache(ip) \
{ \
}

#define CLOSEI(ip, flag, count, offset) \
{ \
	if (rcacheinit && (ip)->i_ftype == IFREG && (count) == 1 \
		&& !server() && (flag) & FWRITE) { \
		(ip)->i_wcnt--; \
		if ((ip)->i_flag & IWROTE && (ip)->i_wcnt == 0) { \
			(ip)->i_flag &= ~IWROTE; \
			if ((ip)->i_rcvd) \
				enable_cache((ip)->i_rcvd); \
		} \
	} \
	FS_CLOSEI(ip, flag, count, offset); \
}

#define OPENI(ip, mode) \
{ \
	if (rcacheinit && (ip)->i_ftype == IFREG && !server() && (mode) & FWRITE) \
		(ip)->i_wcnt++; \
	FS_OPENI(ip, mode); \
}

#define WRITEI(ip) \
{ \
	if (rcacheinit && (ip)->i_ftype == IFREG) { \
		if (!server()) \
			(ip)->i_flag |= IWROTE; \
		(ip)->i_vcode = ++rfs_vcode; \
		if ((ip)->i_rcvd) \
			disable_cache(ip); \
	} \
	FS_WRITEI(ip); \
}

#define ITRUNC(ip) \
{ \
	if (rcacheinit && (ip)->i_ftype == IFREG) { \
		if (!server()) \
			(ip)->i_flag |= IWROTE; \
		(ip)->i_vcode = ++rfs_vcode; \
		if ((ip)->i_rcvd) \
			disable_cache(ip); \
	} \
	FS_ITRUNC(ip); \
}

#define IPUT(ip) \
{ \
	if (rcacheinit && (ip)->i_nlink <= 0 && (ip)->i_count == 1) { \
		(ip)->i_vcode = ++rfs_vcode; \
	} \
	FS_IPUT(ip); \
}

#define FREESP(ip, arg, flag, offset) \
{ \
	if (rcacheinit && (ip)->i_ftype == IFREG) { \
		if (!server()) \
			(ip)->i_flag |= IWROTE; \
		(ip)->i_vcode = ++rfs_vcode; \
		if ((ip)->i_rcvd) \
			disable_cache(ip); \
	} \
	FS_FCNTL(ip, F_FREESP, arg, flag, offset); \
}



/* Following macros and defines refer to disk blocks */
#define ctoblks(clicks) ((clicks) * NBLKPC)                /* clicks to blocks */
#define blkstoc(blks)   (((blks) + NBLKPC - 1) / NBLKPC)   /* blocks to clicks */
#define blkstob(blks)   ((blks) * NBPBLK)	           /* blocks to bytes  */
#define btoblks(bytes)  (((bytes) + NBPBLK - 1) / NBPBLK)  /* bytes to blocks  */
#define blkstoct(blks)  ((blks) / NBLKPC)                  /* blocks to click truncate */

/* Following macros are for translating to and from kBytes */
#define ctokbytes(clicks) (((clicks) * NBPC) / 1024)               /* clicks to kbytes */
#define kbytestoc(kbytes) ((((kbytes) * 1024) + NBPC - 1) / NBPC)  /* kbytes to clicks */
#define kbytestob(kbytes) ((kbytes) * 1024)	                   /* kbytes to bytes  */
#define btokbytes(bytes)  (((bytes) + 1023) / 1024)                /* bytes to kbytes  */

#include "sys/splx.h"
