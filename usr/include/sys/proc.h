/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char proc_h[] = "@(#)proc.h	1.51 (TI) 93/03/01";
#endif	SCCSID

/* @(#)proc.h	2.3	UNIX System V/68 */
/*
 * One structure allocated per active process. It contains all data needed
 * about the process while the process may be swapped out.
 * Other per process data (user.h) is swapped with the process.
 */

#ifdef __STDC__
#define VOLATILE volatile
#else
#define VOLATILE
#endif

typedef struct	proc {
	char	p_stat;
#ifdef NU
	char	p_prtn;		/* return value from psema/vsema on signal */
	char	p_fpurev;	/* FPU revision required by process	   */
	char	p_usrpri;	/* user-priority based on p_cpu and p_nice */
	int	p_flag;
#else
	char	p_flag;
#endif
	char	p_pri;		/* priority, negative is high */
	char	p_time;		/* resident time for scheduling */
	char	p_cpu;		/* cpu usage for scheduling */
	char	p_nice;		/* nice for cpu usage */
	ushort	p_uid;		/* real user id */
	ushort	p_suid;		/* set (effective) user id */
	ushort	p_sgid;		/* set (effective) group id */
	short	p_pgrp;		/* name of process group leader */
	short	p_pid;		/* unique process id */
	short	p_ppid;		/* process id of parent */
	char	p_cpub;		/* cpu-boundedness factor for load balancing */
	char	p_lbflag;	/* load balancing flags */
	unsigned char p_newcpu;	/* New cpu to move process to */
	char	p_cpu2;		/* 2nd cpu usage factor for scheduling */
#ifndef m68k
	short	p_addr;
	short	p_nspt;
	int *	p_spt;
#else
	long	p_addr;		/* mem|disk base click of u. seg */
	long	p_pmphyadr;	/* phys addr of page maps	*/
	caddr_t	p_mmuent;	/* mmu table entry pointer */
#endif
#ifdef NU
	int 	p_slptime;
	int	p_poip;		/* page out in progress */
	int	p_swrss;	/* resident set size before last swap */
#else
	int	p_size;		/* size of swappable image (clicks) */
	short	p_swaddr;	/* disk address when swapped */
#endif
	long	p_sig;		/* signals pending to this process */
	lock_t	p_siglck;	/* lock on p_sig - for p & v to use */
	short	p_swstat;	/* swap/p_stat (SXxxx) while swapped out */
	int	p_tsize;	/* size of text (used by exec/swapin) */
#ifdef NU
	int	p_dsize;
#endif
	int	p_ssize;	/* size of stack (used by exec/swapin) */
	unsigned p_dstart;	/* start addr of data segment */
	union {
		caddr_t	p_cad;
		int	p_int;
	} p_unw;
#define	p_wchan	p_unw.p_cad
#define	p_arg	p_unw.p_int
	caddr_t	p_w2chan;	/* sleep addr given on sleep call since	*/
				/* wchan has addr of sema used by sleep	*/
				/* routine.				*/
	sema_t	p_lock;		/* sema lock on this proc entry		*/
	sema_t	p_waitlck;	/* sema lock for wait coordination	*/
	sema_t	p_trlock;	/* sema lock for tracing		*/

	struct iseg *p_isegptr;	/* pointer to text structure */
#ifdef __STDC__
	VOLATILE struct proc *p_link;	/* linked list of running processes */
#else
	struct proc *p_link;	/* linked list of running processes */
#endif __STDC__
	int	p_clktim;	/* time to alarm clock signal */
	int	p_smbeg;	/* beginning pte entry for shared memory */
	int	p_smend;	/* ending pte entry for shared memory */
#ifdef NU
	unsigned char p_loadcpu; /* cpu that process is loaded on	*/
	unsigned char p_wantcpu; /* cpu that process needs to run on	*/
	short	p_cpticks;	/* ticks of cpu time */
	short	p_ctime;	/* clk ticks of cpu time during BAL_TIM */
	short	p_pctcpu;	/* %cpu for this process during BAL_TIM */
	short	p_epid;		/* effective pid; usually the same as pid;
				   for servers, the system that sent the msg */
	sysid_t	p_sysid;	/* normally same as sysid; for servers,
				   the system that sent the msg */
	struct proc *p_clones;	/* list of clones sharing data/ustack */
	struct proc *p_oldclone;/* ptr to clone with good swap map */
	struct segdesc *p_segdptr;/* Pointer to 1st seg descriptor */
	int	p_rssize;	/* clicks in current resident set */
	sema_t	*p_waitsema;	/* addr of semaphore process is waiting for */
	long	p_bncount;	/* count for outstanding busnet packets */
	long	p_wahead;	/* write ahead in proc struct for busnet.*/
	long	p_smsb;		/* Active starting block in swap space	*/
	long	p_holdsig;	/* Mask for currently blocked signals	*/
	int	p_flagp;	/* Used for polling flag. protected with   */
				/* cookie.  */
	short	p_shm_att_cnt;
	short	p_riseg_cnt;	/* Reserve count for Isegs 	*/
	short	p_rsegd_cnt;	/* Reserve count for segd 	*/
	short	p_rsegdsm_cnt;	/* Reserve count for segdsm 	*/
	short	p_iseg_cnt;	/* Inuse count for Isegs 	*/
	short	p_segd_cnt;	/* Inuse count for segd 	*/
	short	p_segdsm_cnt;	/* Inuse count for segdsm 	*/
	short   p_saved_pgrp;   /* saved p_pgrp for waitpid             */
	struct proc *p_next;	/* Next proc on alloc/free list 	*/
	struct proc *p_back;	/* Previous proc on alloc/free list	*/
	unsigned short   attached_pid;	/* pid of the parent before attach     */
	unsigned short   p_spare_w_air1;	/* spare space in proc struct           */
	long	p_spare_w_air2;	/* spare space in proc struct		*/
#endif
}proc_t;

extern struct proc proc[];	/* the proc table itself */

/* stat codes */
#define	SSLEEP	1		/* awaiting an event */
#define	SWAIT	2		/* (abandoned state) */
#define	SRUN	3		/* runnable */
#define	SIDL	4		/* intermediate state in process creation */
#define	SZOMB	5		/* intermediate state in process termination */
#define	SSTOP	6		/* process being traced */
#define	SXBRK	7		/* process being xswapped */
#define	SXSTK	8		/* process being xswapped */
				/* SXTXT 9 not used */
#define SXPTE	10		/* process being xswapped */
#define SXSWP	11		/* ditto */
#define SONPROC 12		/* process running on a processor */ 

/* flag codes */
#define	SLOAD	0x01		/* in core */
#define	SSYS	0x02		/* scheduling process */
#define	SLOCK	0x04		/* process cannot be swapped */
#define	SSWAP	0x08		/* process is being swapped out */
#define	STRC	0x10		/* process is being traced */
#define	SWTED	0x20		/* another tracing flag */
#define	STEXT	0x40		/* text pointer valid */
#define	SWNOTXT 0x80		/* do not swap text seg */
#ifdef NU
#define SCLONE	    0x0100	/* sharing data/ustack due to fork */
#define SPHYSIO     0x0200	/* doing raw i/o to locked pages */
#define SNOSWP	    0x0400	/* Please don't swap me! (Can still pageout) */
#define SWEXIT	    0x0800	/* proc is doing an exit */
#define SEXP	    0x1000	/* proc is trying to expand */
#define SNOMIGR	    0x2000	/* proc cannot be migrated right now	*/
#define SWAPSLF	    0x4000	/* proc should arrange to have itself swapped */
#define SWAPME	    0x8000	/* swapper should swap out this process	      */
#define SNOPAGE    0x10000	/* prevent pageout from stealing pages	*/
#define SNEVERM    0x20000	/* proc cannot be migrated at all */
#define SDLYMIGR   0x40000	/* delayed process migration		*/
#define SASC 	   0x80000	/* Amazing shrinking clone 		*/
#define SHALTED   0x100000	/* Process is halted (See opctl)	*/
#define SHALTME   0x200000	/* Process is to be halted asap		*/
#define SFLUSHS   0x400000	/* Flush system half of cache before resume*/
#define SFLUSHU   0x800000	/* Flush user   half of cache before resume*/
#define	SPOLL	 0x1000000	/* process in stream poll */
#define SPROCRUN 0x2000000	/* Process was run since last cleared. */
#define SPAGEDUP 0x4000000      /* Process is doing a pagedup */
#define SCINHDAT 0x8000000      /* Process needs cache inhibited data seg */
#define	SPANIC  0x80000000	/* this is the process that called panic   */

/* Load balancing flag codes */
#define FRCSWPD   0x01		/* Process was force swapped */
#define POTCPUB   0x02		/* Process is potentially cpu bound */
#define PLOCKED	  0x04		/* Process is "locked" in its cpu. */
#define MOVEME    0x08		/* Process is to be moved to a new cpu */
#define MOVELOCK  0x10		/* Process is to be moved and locked */
#define PROPLOCK  0x20		/* Propogate lock to children of this process */
#endif

#ifdef NU
/*
 * Value for p_oldclone which indicates that
 * our oldclone has gone away via exec or exit.
 */
#define NOCLONE	((struct proc *)(-1))
#endif

/*
 * parallel proc structure
 * to replace part with times
 * to be passed to parent process
 * in ZOMBIE state.
 */
#ifndef NPROC
struct	xproc {
	char	xp_stat;
#ifdef NU
	char	xp_prtn;	/* returned value frpm psema/vsema on signal */
	char	xp_fpurev;	/* fpu revision number */
	char	xp_usrpri;	/* user-priority based on xp_cpu and xp_nice */
	int	xp_flag;	/* flags field */
#else
	char	xp_flag;
#endif
	char	xp_pri;		/* priority, negative is high */
	char	xp_time;	/* resident time for scheduling */
	char	xp_cpu;		/* cpu usage for scheduling */
	char	xp_nice;	/* nice for cpu usage */
	ushort	xp_uid;		/* real user id */
	ushort	xp_suid;	/* set (effective) user id */
	ushort	xp_sgid;	/* set (effective) group id */
	short	xp_pgrp;	/* name of process group leader */
	short	xp_pid;		/* unique process id */
	short	xp_ppid;	/* process id of parent */
	char	xp_cpub;	/* cpu-boundedness factor for load balancing */
	char	xp_lbflag;	/* load balancing flags */
	unsigned char xp_newcpu;
	char	xp_unused2;
#ifndef m68k
	short	xp_addr;
	short	xp_nspt;
	int *	xp_spt;
#else
	long	xp_addr;	/* mem|disk base click of u. seg */
	long	xp_pmphyadr;	/* phys addr of page maps	*/
	caddr_t	xp_mmuent;	/* mmu table entry pointer */
#endif
	short	xp_xstat;	/* Exit status for wait */
	time_t	xp_utime;	/* user time, this proc */
	time_t	xp_stime;	/* system time, this proc */
};
struct plists {
        struct proc *head;
        int count;
};
#endif
