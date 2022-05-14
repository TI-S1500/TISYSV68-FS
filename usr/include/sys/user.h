/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char user_h[] = "@(#)user.h	1.38 (TI) 91/07/24";
#endif	SCCSID

/* @(#)user.h	2.8	UNIX System V/68 */
#ifndef m68k
#include "sys/pcb.h"
#endif

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

#define MAXPSARGS	30
#define	PSCOMSIZ	DIRSIZ	/* For the time being set PSCOMSIZ */
				/* to DIRSIZ until we can get rid of */
				/* struct direct u_dent */

/*
 * The user structure.
 * One allocated per process.
 * Contains all per process data that doesn't need to be referenced
 * while the process is swapped.
 * The user block is USIZE*click bytes long; resides at virtual kernel
 * loc 0x7ffff800(vax), 0140000(11/70), floating(11/34), 0x1000000(m68k);
 * contains the system stack per user; is cross referenced
 * with the proc structure for the same process.
 */
 
typedef struct	user
{
#ifndef m68k
	struct pcb u_pcb;		/* pcb, save area when switching */
#endif

	label_t	u_rsav;			/* save info when exchanging stacks */
	label_t	u_qsav;			/* label variable for quits and interrupts */
	label_t	u_ssav;			/* label variable for swapping */
	char	u_segflg;		/* IO flag: 0:user D; 1:system; 2:user I */
	unsigned char	u_error;	/* return error code */
	ushort	u_uid;			/* effective user id */
	ushort	u_gid;			/* effective group id */
	ushort	u_ruid;			/* real user id */
	ushort	u_rgid;			/* real group id */
	short	u_fill;
	struct proc *u_procp;		/* pointer to proc structure */
	int	*u_ap;			/* pointer to arglist */
	union {				/* syscall return values */
		struct	{
			int	r_val1;
			int	r_val2;
		}r_reg;
		off_t	r_off;
		time_t	r_time;
	} u_r;
	caddr_t	u_base;			/* base address for IO */
	unsigned u_count;		/* bytes remaining for IO */
	off_t	u_offset;		/* offset in file for IO */
	short	u_fmode;		/* file mode for IO */
	short	u_errcnt;		/* syscall error count */
	long	u_elapusr;		/* acct timer - elapsed user time   */
	long	u_elapsys;		/* acct timer - elapsed system time */
	ushort	u_noblk;		/* read ahead block count */
	ushort	u_enflg;		/* enhancement flags */
	struct inode *u_cdir;		/* current directory of process */
	struct inode *u_rdir;		/* root directory of process */
	caddr_t	u_dirp;			/* pathname pointer */
	struct direct u_dent;		/* current directory entry */
	struct inode *u_pdir;		/* inode of parent directory of dirp */
	time_t	u_start;		/* start time - used by 'ps'	    */
	int	u_arg[10];		/* arguments to current system call */
	unsigned u_tsize;		/* text size (clicks) */
	unsigned u_dsize;		/* data size (clicks) */
#ifdef NU
	unsigned u_shsize;		/* shared mem size (clicks) */
#endif
	unsigned u_ssize;		/* stack size (clicks) */
	int	u_signal[NSIG];		/* disposition of signals */
	int	*u_ar0;			/* address of users saved R0 */
/* 				NEXT four lines must be contiguous */
	time_t	u_utime;		/* this process user time */
	time_t	u_stime;		/* this process system time */
	time_t	u_cutime;		/* sum of childs' utimes */
	time_t	u_cstime;		/* sum of childs' stimes */
/*									*/
	struct {			/* profile arguments */
		short	*pr_base;	/* buffer base */
		unsigned pr_size;	/* buffer size */
		unsigned pr_off;	/* pc offset */
		unsigned pr_scale;	/* pc scaling */
	} u_prof;
	char	u_intflg;		/* catch intr from sys */
	char	u_sep;			/* flag for I and D separation */
	short	u_rdtest;		/* flags for extra read logic */
	short	*u_ttyp;		/* pointer to pgrp in "tty" struct */
	dev_t	u_ttyd;			/* controlling tty dev */
	struct inode *u_ttyip;		/* inode of controlling tty (streams) */
	long 	u_execsz;		/* Exec size */
	struct exdata {			/* info about the executable file */
		struct inode *ip;	/* Inode pointer */
		unsigned ux_tsize;	/* program text size */
		unsigned ux_dsize;	/* program data size */
		unsigned ux_bsize;	/* program bss size */
		unsigned ux_lsize;	/* Lib size */
		unsigned ux_nshlibs;	/* Number of shared Libs */
		short	ux_mag;		/* magic number */
		unsigned ux_tstart;	/* byte offset of program text */
		unsigned ux_dstart;	/* byte offset of program data */
		unsigned ux_lstart;	/* byte offset of library section */
		unsigned ux_text;	/* virtual address of text (unused) */
		unsigned ux_data;	/* virtual address of data segment  */
		unsigned ux_entloc;	/* entry point */
	} u_exdata;
	unsigned long u_locked;
	char	u_comm[PSCOMSIZ];
	short	u_lock;			/* process/text locking flags */
	char	u_acflag;
	char	u_fpsav_val;		/* flag: 1=contents of u_fpsav valid*/
	short	u_cmask;		/* mask for file creation */
	daddr_t	u_limit;		/* maximum write address */
	struct file *u_ofile[NOFILE];	/* pointers to file structures of open files */
	char	u_pofile[NOFILE];	/* per-process flags of open files */
	int	u_slice_used;		/* cpu time used out of time slice */

	long	u_fpsav[FPUSIZE];	/*floating point coprocessor FRAME */
	long	u_fprsav[FREGS];	/*floating point coprocessor REGS  */
	csema_t	*u_drivsema;		/* currently locked driver   */
					/* semaphore.		     */
	time_t	u_ticks;
	long	u_mem;
	long	u_ior;
	long	u_iow;
	long	u_iosw;
	long	u_ioch;
	long	u_savsig;		/* save the signals */
	long	u_spare1;
	char	*u_comp;		/* pointer to current component */
	char	*u_nextcp;		/* pointer to beginning of next */
	long	u_bsize;		/* block size of device */
	int	u_mntindx;		/* mount index from sysid */
	ushort	u_pbsize;		/* bytes in block for IO */
	ushort	u_pboff;		/* offset in block for IO */
	dev_t	u_pbdev;		/* real device for IO */
#ifdef NU
	long	u_socknum;		/* socket# for socket mechanism     */
	dev_t 	u_ttyq;			/* pointer to saved translated ttyd */
	long	u_readone;		/* block number of a previous read  */
	long	u_readtwo;		/* block number of a previous read  */
#endif NU
	long	u_sigset;		/* Flags for how each signal handler */
					/* was established (signal/sigaction)*/
	char	u_psargs[MAXPSARGS];	/* Used by ps to get cmd line args */
	long	u_chksum;
struct 	tty	*u_pstp;		/* ptr to tty struct for print screen */
	long	u_tpspare;		/* print screen spare */
	int	u_stack[1];
					/* kernel stack per user
					 * extends from u + USIZE*NBPC
					 * backward not to reach here
					 */
}user_t;
extern struct user u;

#define	u_rval1	u_r.r_reg.r_val1
#define	u_rval2	u_r.r_reg.r_val2
#define	u_roff	u_r.r_off
#define	u_rtime	u_r.r_time

/* ioflag values: Read/Write, User/Kernel, Ins/Data */
#define	U_WUD	0
#define	U_RUD	1
#define	U_WKD	2
#define	U_RKD	3
#define	U_WUI	4
#define	U_RUI	5

#define	EXCLOSE	01

/* enhancement flags */
#define	U_RDWR		0x0000	/* initial value on rdwr() entry       */
				/* enhancements alterations apply only */
				/* to path thru rdwr()                 */
#define	U_NONE		0x0000	/* initial value.                      */
				/* enhancements alterations apply only */
				/* to path thru rdwr()                 */

/* enhancement flags : read ahead file system */
#define	U_SEQ		0x0001	/* access is sequential */

/* enhancement flags : concurrent file system */
#define	U_NORA		0x0002	/* process not allowed to reference */
				/* read ahead info in inode         */
#define	U_CC		0x0004	/* concurrent access allowed        */
#define	U_PP		0x0008	/* piggy back psema's allowed       */
#define	U_EW		0x0010	/* ewprele required on release      */
#define	U_PRELE		U_EW	/*   prele required on release      */
#define	U_SR		0x0020	/* srprele required on release      */
