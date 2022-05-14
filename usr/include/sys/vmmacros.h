/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char vmmacros_h[] = "@(#)vmmacros.h	1.10 (TI) 90/12/04";
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
#define vtotp(segdp,v)   (v - btoct(segdp->virt_beg))
#define vtodp(segdp,v)   (v - btoct(segdp->virt_beg))
#define vtoshmp(segdp,v) (v - btoct(segdp->virt_beg))
#define vtonubp(segdp,v) (v - btoct(segdp->virt_beg))
#define	vtosp(segdp, v)	 ((int)(btoct(USRSTACK) - 1 - (v)))

#define	tptov( segdp, i) ((unsigned)((btoct(segdp->virt_beg) + (i))))
#define	dptov( segdp, i) ((unsigned)((btoct(segdp->virt_beg) + (i))))
#define	sptov( segdp, i) ((unsigned)(btoct(USRSTACK) - 1 - (i)))

/*
 *  Tell whether virtual page numbers are in text|data|stack segment
 */
#define	isatsv(p, v)	istext(p,ctob(v))
#define	isadsv(p, v)	isdata(p,ctob(v))
#define	isassv(p, v)	(((v) >= btoct(USRSTACK) - (p)->p_ssize)\
			 && ((v) < btoct(USRSTACK)))

/*
 *  Tell whether pte's are text|data|stack
 */
#define	isatpte(p,pte) (((struct segdesc *)ptetosegd(p,pte))->type == SEG_TEXT)
#define	isadpte(p,pte) (((struct segdesc *)ptetosegd(p,pte))->type == SEG_DATA)
#define	isaspte(p,pte) (((struct segdesc *)ptetosegd(p,pte))->type == SEG_STACK)
#define	isashmpte(p,pte) (((struct segdesc *)ptetosegd(p,pte))->type == SEG_SHM)

/*
 *  Text|data|stack pte's to segment page numbers and back
 *  The corresponding shm calls are functions in vmsubr.c
 */
#define	ptetotp(p, pte) ((pte) - \
	ptetosegd(p,pte)->proc_L3_ptr)
#define	ptetodp(p, pte) ((pte) - \
	ptetosegd(p,pte)->proc_L3_ptr)
#define	ptetosp(p, pte) \
	((ptetosegd(p,pte)->proc_L3_ptr+(p)->p_ssize-1)-(pte))

#define	tptopte(segdp, i)  (segdp->proc_L3_ptr + (i))
#define	dptopte(segdp, i)  (segdp->proc_L3_ptr + (i))
#define	shmtopte(segdp, i) (segdp->proc_L3_ptr + (i))
#define	nubtopte(segdp, i) (segdp->proc_L3_ptr + (i))
#define sptopte(segdp, i)\
	((struct pte *)(ptom(segdp->gen_ptr.procptr)->mmu_pmvaddr)\
	 + ptom(segdp->gen_ptr.procptr)->mmu_pmsize/sizeof(struct pte) \
		- 1 - (i))

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
