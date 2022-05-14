/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char vmmacros_h[] = "@(#)vmmacros.h	1.9 (TI) 90/08/09";
#endif	SCCSID

/* 
 *  Virtual memory macros.
 *
 *  Throughout these macros, "page 0" is the low addressed page
 *  for text, data, and shared memory.  For stack, "page 0"
 *  is the high addressed page (e.g. the base of the stack)
 */

/* 
 *  Does a pte have a page frame allocated, either valid or reclaimable?
 */
#define	PFALLOC(pte)	((*(unsigned long *)(pte) & \
				(PG_ALLOC | PG_FOD)) == PG_ALLOC)

/* 
 *  Does the pte reference a valid page?
 */
#define	INVALID(pte)	((unsigned long)((pte)->pg_dt) == 0)

/*
 *  Core clicks to number of pages of page tables needed to map that much.
 */
#define	ctopt(x)	(((x)+MAXL3PTEPG-1)/MAXL3PTEPG)

/*
 *  Virtual page numbers to text|data|stack segment page numbers and back
 */
#define	vtotp(p, v)	((int)(v))
#define	vtodp(p, v)	((int)((v) - (p)->p_dstart))
#define	vtosp(p, v)	((int)(btoct(USRSTACK) - 1 - (v)))

#define	tptov(p, i)	((unsigned)(i))
#define	dptov(p, i)	((unsigned)((p)->p_dstart + (i)))
#define	sptov(p, i)	((unsigned)(btoct(USRSTACK) - 1 - (i)))

/*
 *  Tell whether virtual page numbers are in text|data|stack segment
 */
#define	isatsv(p, v)	((v) < (p)->p_tsize)
#define	isadsv(p, v)\
		((v) >= (p)->p_dstart && (v) < (p)->p_dstart + (p)->p_dsize)
#define	isassv(p, v)	(((v) >= btoct(USRSTACK) - (p)->p_ssize)\
			 && ((v) < btoct(USRSTACK)))

/*
 *  Tell whether pte's are text|data|stack
 */
#define	isatpte(p, pte)\
	((pte) >= tptopte(p, 0) && (pte) < tptopte(p, (p)->p_tsize))
#define	isadpte(p, pte)\
	((pte) >= dptopte(p, 0) && (pte) < dptopte(p, (p)->p_dsize))
#define	isaspte(p, pte)		((pte) > sptopte(p, (p)->p_ssize))
#define	isashmpte(p, pte)  (  ( (pte) >= dptopte(p, (p)->p_dsize) )  && \
			      ( (pte) <= sptopte(p, (p)->p_ssize) )  )

/*
 *  Text|data|stack pte's to segment page numbers and back
 *  The corresponding shm calls are functions in vmsubr.c
 */
#define	ptetotp(p, pte)\
	((pte) - ptom(p)->mmu_entry[SEG_TEXT-1].mmu_pte)
#define	ptetodp(p, pte)\
	((pte) - ptom(p)->mmu_entry[SEG_DATA-1].mmu_pte)
#define	ptetosp(p, pte)\
	((ptom(p)->mmu_entry[SEG_STACK-1].mmu_pte \
		+ (p)->p_ssize - 1) - (pte))

#define	tptopte(p, i)\
	(ptom(p)->mmu_entry[SEG_TEXT-1].mmu_pte + (i))
#define	dptopte(p, i)\
	(ptom(p)->mmu_entry[SEG_DATA-1].mmu_pte + (i))
#define sptopte(p, i)\
	((struct pte *)(ptom(p)->mmu_pmvaddr)\
	 + ptom(p)->mmu_pmsize/sizeof(struct pte) - 1 - (i))

/* Average new into old with aging factor time */
#define	ave(smooth, cnt, time) \
	smooth = ((time - 1) * (smooth) + (cnt)) / (time)

/*
 * Function declarations to keep the compiler happy.
 */
struct pte *kvwtopte(), *shptopte(), *vtopte(), *cvtopte(), *cmaptopte();
caddr_t kremap();
caddr_t knalloc();
struct buf *vbmap();
