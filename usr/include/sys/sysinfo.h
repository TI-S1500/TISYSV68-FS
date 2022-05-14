/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/
#ifdef	SCCSID
static char sysinfo_h[] = "@(#)sysinfo.h	1.15 (TI) 91/05/16";
#endif	SCCSID

struct	busnet_stats {
	ulong	tot_ops;
	ulong	tot_wrt_ops;
	ulong	tot_wrt_sz;
	ulong	tot_read_ops;
	ulong	tot_read_sz;
	ulong	tot_zero_reads;
	ulong	tot_ioctls;
};

struct sysinfo {
	time_t	cpu[MAXCPU][4];
#define	CPU_IDLE	0
#define	CPU_USER	1
#define	CPU_KERN	2
#define	CPU_WAIT	3
	time_t	wait[MAXCPU];
	ulong	bread;
	ulong	bwrite;
	ulong	lread;
	ulong	lwrite;
	ulong	phread;
	ulong	phwrite;
	ulong	swapin[MAXCPU];
	ulong	swapout[MAXCPU];
	ulong	bswapin[MAXCPU];
	ulong	bswapout[MAXCPU];
	ulong	pagein[MAXCPU];
	ulong	pageout[MAXCPU];
	ulong	bpagein[MAXCPU];
	ulong	bpageout[MAXCPU];
	ulong	pswitch[MAXCPU];
	ulong	syscall;
	ulong	sysread;
	ulong	syswrite;
	ulong	sysfork;
	ulong	sysexec;
	ulong	runque;
	ulong	runocc;
	ulong	swpque;
	ulong	swpocc;
	ulong	iget;
	ulong	namei;
	ulong	dirblk;
	ulong	readch;
	ulong	writech;
	ulong	rcvint;
	ulong	xmtint;
	ulong	mdmint;
	ulong	rawch;
	ulong	canch;
	ulong	outch;
	ulong	msg;
	ulong	sema;
	ulong	swap_space_avail;
	ulong	swap_space_used;
	ulong	swap_space_max;
	ulong	tot_avail_mem[MAXCPU];
	ulong	tot_free_mem[MAXCPU];
	ulong	tot_processes[MAXCPU];
	ulong	num_clones[MAXCPU];
	ulong	num_migr;
	ulong	num_swpd_proc;
	struct	busnet_stats busnet_stats[16];
	ulong   b_number_of_pages[MAXCPU];
	int     fm_time_last_preempt[MAXCPU];
	int     fm_age_last_preempt[MAXCPU];
	int     vm_time_last_preempt[MAXCPU];
	int     vm_age_last_preempt[MAXCPU];
	int     vm_time_last_swapout[MAXCPU];
	int     vm_time_last_swap[MAXCPU];
	int     sys_time_tick;
	ulong   tot_phys_mem[MAXCPU];
	ulong   tot_used_shm_mem[MAXCPU];
	ulong   tot_used_process_mem[MAXCPU];
	int	knl_tsize;		/* Kernel text size in pages */
	int	knl_dsize;		/* Kernel data and bss size */
	ulong   least_free[MAXCPU];	/* Least amount of free memory */
        
};

struct shlbinfo {
	long	shlbs;		/* Max # of libs a process can link in	*/
				/*   at one time.			*/
	long	shlblnks;	/* # of times processes that have used	*/
				/*   static shared libraries.		*/
	long	shlbovf;	/* # of processes needed more shlibs	*/
				/*   than the system imposed limit.	*/
	long	shlbatts;	/* # of times processes have attached	*/
				/*   run time libraries.		*/
};

extern struct shlbinfo shlbinfo;

struct cfg_parms { /* As defined in boot.h */
	int	nproc;			/* Process table size */
	int	niseg;			/* Number of ISEGs */
	int	nfile;			/* Open file table size */
	int	ninode;			/* Inode table size */
	int	ncall;			/* Callout table size */
	int	nmount;			/* Mount table size */
	int	npbuf;			/* Raw I/O buffer header pool size */
	int	nswbuf;			/* Swap buffer pool size */
	int	nsmap;			/* Swap map size */
	int	nkmap;			/* Kernel virtual map size */
	int	nflrec;			/* Number of record locks */
	int	nflfil;			/* Number of file locks */
	int	npool;			/* Number of busnet packets */
	int	nsegd;			/* Number of segment descriptors */
	int	shmmni;			/* # of shared memory segments */
	int	shmall;			/* Number of shared mem pages */
	int	shmmax;		 	/* Max shared memory segment size */
	int	shmseg;			/* Max attached shm per process */
	int	msgmap;			/* Msg map size */
	int	msgall;			/* Size of message space */
	int	msgseg;			/* Number of msg segments */
	int	msgmni;			/* Number of message queues */
	int	msgmnb;			/* Maximum size of any queue */
	int	msgtql;			/* Number of messages */
	int	msgmax;			/* Maximum size of any message */
	int	semmap;			/* Semaphore map size */
	int	semmni;			/* Number of semaphore sets */
	int	semmsl;			/* Maximum number of sems in any set */
	int	semmns;			/* Number of semaphores */
	int 	semmnu;			/* Number of semaphore undos */
	int 	semume;			/* Maximum sem undos of any process */
	int 	semopm;			/* Maximum sem ops of any call */
	int	sdmamni;		/* Number of SDMA segments */
	int	sdmaall;		/* Number of SDMA pages */
	int	nsegdsm;		/* Number of segd swapmaps */
	int	mirbuf;			/* Number of mirror buffer headers */
};

struct cfginfo{
	struct cfg_parms current;
	struct cfg_parms max;
};

struct syswait {
	short	wait[MAXCPU];
};


struct syserr {
	long	inodeovf;
	long	fileovf;
	long	isegovf;
	long	procovf;
	long	sbi[5];
#define	SBI_SILOC	0
#define	SBI_CRDRDS	1
#define	SBI_ALERT	2
#define	SBI_FAULT	3
#define	SBI_TIMEO	4
};

#ifdef KERNEL
extern struct sysinfo sysinfo;
extern struct cfginfo cfginfo;
extern struct syswait syswait;
extern struct syserr syserr;
#endif
