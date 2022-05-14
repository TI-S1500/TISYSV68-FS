/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char boot_h[] = "@(#)boot.h	1.14 (TI) 90/08/10";
#endif	SCCSID

/********
*
*  This miscellaneous boot information passed from STBM to unix on the stack.
*  It contains the information necessary to initialize the kernel virtual
*  window structure and information that cannot be obtained by the kernel
*  without making unnecessary assumptions about the physical arrangement of
*  the kernel virtual address space.
*
********/

struct boot 
{
        struct					/* kernel virtual window */
	{
		long	*l3ptr;			/* ptr to first l3 */
		long	vaddr;		        /* vaddr of bottom of window */
		int	vclick;			/* .... and its click number */
	}kvw;
	long	*usize_L3p;		/* usize base pte vaddr */
	long	*kernel_L3p;		/* kernel base pte vaddr */
	long	*cpuloc_L3p;		/* cpu local area base pte vaddr */
	long	*data_L3p;		/* config data base pte vaddr */
	long	*cmap;			/* core map vaddr */
	char    *nvaddr;		/* nvram address */
	int	nproc;			/* number of proc structures */
	int	nfile;			/* number of open file table entries */
	int	ninode;			/* number of in core inodes */
	int	ncall;			/* number of callout table entries */
	int	nmount;			/* number of mount table entries */
	int	ntext;			/* number of text structures */
	int	nbuf;			/* number of file buffers */
	int	nswbuf;			/* number of swap buffers */
	int	npbuf;			/* raw I/O buffer header pool size */
	int	nhbuf;			/* hash buffer pool size */
	int	nsmap;			/* number of swap maps */
	int	nkmap;			/* number of of kvw map */
	int	msgmap;			/* number of message maps */
	int	msgssz;			/* msg segment size */
	int	msgseg;			/* number of msg segments */
	int	msgmni;			/* number of message queues */
	int	msgmnb;			/* number of bytes on queues */
	int	msgtql;			/* maximum number of messages */
	int	msgmax;			/* maximum size of message */
	int	nflrec;			/* number of record locks */
	int	shmmax;		 	/* max shared memory segment size */
	int	shmmni;			/* # of shared memory identifiers */
	int	shmseg;			/* max attached shm per process */
	int	shmbrk;			/* gap (in clicks) */
	int	shmxat; 		/* max total attached segments system */
	int	shmall;			/* max shm system wide (in clicks) */
	int	semmap;			/* size of IPC semaphore map */
	int	semmni;			/* IPC semaphore max identifiers */
	int	semmsl;			/* IPC semaphore max per identifier */
	int	semmns;			/* IPC semaphore max in system */
	int 	semopm;			/* IPC semaphore max per call */
	int 	semmnu;			/* IPC semaphore max undo structures*/
	int 	semume;			/* semaphore max undos per process */
	int	semusz;			/* size of each undo structure */
	int	semusiz;		/* size of undo array */
	int	semtmp;			/* size of semaphore temp area */
	int	sdmamax;		/* maximum size of any sdma structure */
	int	sdmaseg;		/* maximum number of sdma attaches */
	int	sdmamni;		/* maximum number of sdma segments */
	int	sdmaall;		/* total amount of sdma allowed */
	int	npool;			/* number of busnet packets */
	int 	fslimit;		/* file size limit */
	int	ltick;			/* system time slice in ticks */
	int	maxup;			/* maximum processes per user */
	int	baltim;			/* load balancing time */
	int	balmem;			/* load balancing memory */
	int	kwclicks;		/* kernel virtual window size */
	int 	mscsiz;			/* total size of msc structures */
	int 	npsiz;			/* total size of nupi structures */
	int	maptblsz;		/* size of maptable data */
	int	nmaptbls;		/* number of map tables */
	int	nmapdev;		/* number of mapout devices */
	int	mapcntlsiz;		/* size of mapcntl struct */
	char	lodname[4];		/* boot band name */
	char	cfgname[4];		/* config band name */
	int	lodsrc;			/* load source slot */
	int	rdsiz;			/* ram disk size */
	int	fmra;			/* file management read ahead */
	int	dist;			/* buffer cache memory distrbution */
	int	psiz;			/* process size limit */
	int	ssiz;			/* stack size limit */
	int	encore;			/* 1=enable core dump */
	int	bufdist[MAXCPU];	/* number of ram board buffers */
	char	console[14];
	short	filler;
	int	strnhsz;	/* streams net heap size */
	int	nstrnmap;	/* number of entries in strn_map array */
	int	nstrnlnk;	/* number of streams net links */
	int	nstrq;		/* number of streams queues 		*/
	int	nstream;	/* number of streams 			*/
	int	nmuxlink;	/* number of mux links 			*/
	int	nstrevent;	/* number of streams events 		*/
	int	nmaxsepgnt;	/* number of extra event segments 	*/
	int	nstrpush;	/* number of pushed streams modules 	*/
	int	strmsgsz;	/* max message data size 		*/
	int	strctlsz;	/* max streams control size 		*/
	int	strlofrac;	/* low priority threshold 		*/
	int	strmedfrac;	/* med priority threshold		*/
	int	nblk4096;	/* number of 4096 byte blocks 		*/
	int	nblk2048;	/* number of 2048 byte blocks 		*/
	int	nblk1024;	/* number of 1024 byte blocks 		*/
	int	nblk512;	/* number of 512 byte blocks 		*/
	int	nblk256;	/* number of 256 byte blocks 		*/
	int	nblk128;	/* number of 128 byte blocks 		*/
	int	nblk64;		/* number of 64 byte blocks 		*/
	int	nblk16;		/* number of 16 byte blocks 		*/
	int	nblk4;		/* number of 4 byte blocks 		*/
	int	naddonp;	/* number of add-on configurable parms	*/
	int     nmblock;	/* number of entries in mblock[]	*/
	int     ndblock;	/* number of entries in dblock[]	*/
};

#ifdef KERNEL
extern struct boot bparam;
extern struct boot *initstkdata;
#endif
