/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char systm_h[] = "@(#)systm.h	1.14 (TI) 90/09/28";
#endif	SCCSID

#ifdef __STDC__
#define VOLATILE volatile
#else
#define VOLATILE
#endif

/*	@(#)systm.h	1.2	UNIX System V/68 */
/*
 * Random set of variables used by more than one routine.
 */
extern struct inode *rootdir;	/* pointer to inode of root directory */
extern short cputype;		/* type of cpu = 680, 681, 682 */
extern time_t lbolt;		/* time in HZ since last boot */
extern time_t time;		/* time in sec from 1970 */
extern short dstflag;		/* 1=> daylight davings applies here */
extern short timezone;		/* minutes west of Greenwich */

extern VOLATILE short runrun[];		/* scheduling flag */
extern char curpri[];		/* current priority */

extern daddr_t swplo;		/* block number of swap space */
extern	nswap;			/* size of swap space */
extern dev_t rootdev;		/* device of the root */
extern dev_t swapdev;		/* swapping device */
extern dev_t pipedev;		/* pipe device */
extern dev_t dumpdev;		/* kernel dump device */
extern char *panicstr;		/* panic string pointer */
extern	blkacty;		/* active block devices */
extern	pwr_cnt, pwr_act;
extern int (*pwr_clr[])();

/*
 *  Declare system wide semaphores
 */
extern sema_t file_tlock;	/* system file table semaphore 	*/
extern sema_t mnt_lck;		/* mount table semaphore	*/
extern struct inode uinode;	/* lock for update(sync)	*/
extern sema_t np_open;		/* lock on nupi opens		*/
extern sema_t msc_open;		/* lock on msc opens		*/
extern sema_t mv_open;		/* lock on multivolume opens	*/
extern sema_t swapmpsem;	/* Semaphore on swapmap		*/ 
extern sema_t swapmpout;	/* Semaphore on swapmap mapout	*/ 
extern sema_t textsema;		/* Semaphore on text array	*/
extern lock_t textqlck;		/* Lock on x_caddr linked list  */
extern sema_t swapwait;		/* Semaphore on which to await swapout */
extern sema_t runin[];		/* Array (indexed by cpuid) of swapin semas */
extern sema_t runout[];		/* Array (indexed by cpuid) of swapout semas */
extern lock_t pmaplock;		/* Lock on pmaplist structure	*/
extern sema_t vscpysema;	/* Global lock on vscopy code	*/
extern sema_t vscpywait;	/* Sleep mechanism for vscopy	*/

dev_t getmdev();
daddr_t	bmap();
struct inode *ialloc();
struct inode *iget();
struct inode *owner();
struct inode *maknode();
struct inode *namei();
struct buf *s5alloc();
struct buf *getblk();
struct buf *geteblk();
struct buf *bread();
struct buf *breada();
struct filsys *getfs();
struct file *getf();
struct file *falloc();
int	upath();

/*
 * Structure of the system-entry table
 */
extern struct sysent {
	char	sy_narg;		/* total number of arguments */
	char	sy_nrarg;		/* number of args in registers */
	short	sy_fast;		/* flag: 1=no sleep possible	*/
	int	(*sy_call)();		/* handler */
} sysent[];

struct cntproc{				/* Count of processes on each cpu */
	lock_t	lock;			/* with a global lock on the struct */
	short	count[MAXCPU];
	};
