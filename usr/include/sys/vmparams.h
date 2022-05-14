/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char vmparams_h[] = "@(#)vmparams.h	1.9 (TI) 91/07/08 3/14/93";
#endif	SCCSID

/*
 * The size of the clock loop.
 */
#define	LOOPSIZ	(highfree - lowfree)

/*
 * The time for a process to be blocked before being very swappable.
 * This is a number of seconds which the system takes as being a non-trivial
 * amount of real time.  You probably shouldn't change this;
 * it is used in subtle ways (fractions and multiples of it are, that is, like
 * half of a ``long time'', almost a long time, etc.)
 * It is related to human patience and other factors which don't really
 * change over time.
 */
#define	MAXSLP 		10

/*
 * A swapped in process is given a small amount of core without being bothered
 * by the page replacement algorithm.  Basically this says that if you are
 * swapped in you deserve some resources.  We protect the last SAFERSS
 * pages against paging and will just swap you out rather than paging you.
 * Note that each process has at least USIZE+2 pages which are not
 * paged anyway.  This is currently 1+2=3 pages, so this number
 * just means a swapped in process is given around 36k bytes.
 */
#define	SAFERSS		6

/*
 * DISKRPM is used to estimate the number of paging i/o operations
 * which one can expect from a single disk controller.
 */
#define	DISKRPM		50

/*
 * Max number of pages per cluster.  Clustering is
 * the gathering of pages together for pagein/pageout.
 * Note that CLMAX must be <= SMMIN in smap.h.
 */
#define	CLMAX	4		/* 4096*4 = 16k maximum cluster size 	*/

/* CLIN	can be no more than 1/2 of the SMMIN value.			*/
#define CLIN	1		/* 4096*1 = 4k clusters on pagein of data */

/* CLOUT can be no more than 1/2 of the SMMIN value.			*/
#define	CLOUT	2		/* 4096*2 = 8k on pageout 		*/

/* CLTXT can be no more than 1/2 of the SMMIN value.			*/
#define CLTXT	2		/* 4096*2 = 8k text clusters 		*/

/*
 * Paging thresholds (see vminit.c)
 * Strategy of 5/8/84:
 *	lotsfree is 1/4 of memory free.
 *	desfree is 200k bytes, but at most 1/8 of memory
 *	minfree is 64k bytes, but at most 1/2 of desfree
 */
#define	LOTSFREEFRACT	8
#define	DESFREE		(100*1024)/NBPC + MUST_KEEP + CLMAX
#define	DESFREEFRACT	16
#define	MINFREE		(32*1024)/NBPC + MUST_KEEP + CLMAX
#define	MINFREEFRACT	2
#define SWAP_THRESHOLD 90

/*
 * Minimum number of pages that MUST be kept free in order to guarantee
 * that a fork() operation of a large process will not run out of memory
 * before completing.  Since a process cannot be swapped while doing a
 * fork(), it would totally hang a cpu if the fork() couldn't complete.
 */
#define MUST_KEEP	35
/*
 * Gather all of the tunable virtual memory parameters
 * into one structure.  If they are patched non-zero
 * in a unix object, they are left alone and may thus
 * be changed per system using sdb.  Otherwise, they are
 * calculated very early on using the above constants.
 */
struct vmparam
{
	int	maxpgio;
	int	minfree;
	int	desfree;
	int	lotsfree;
	int	slowscan;
	int	fastscan;
	int	multprog;
	int	maxslp;
	int	saferss;
	int	clin;
	int	cltxt;
	int	clout;
};

/* extern double avenrun; */
