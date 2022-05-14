/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char vmmeter_h[] = "@(#)vmmeter.h	1.6 (TI) 91/12/10";
#endif	SCCSID

/*
 * Virtual memory related instrumentation
 */
struct vmmeter
{
#define	v_first	v_swtch
	unsigned v_swtch;	/* context switches */
	unsigned v_trap;	/* calls to trap */
	unsigned v_syscall;	/* calls to syscall() */
	unsigned v_pswpin;	/* pages swapped in */
	unsigned v_pswpout;	/* pages swapped out */
	unsigned v_pgin;	/* pageins (via swap space) */
	unsigned v_pgout;	/* pageouts */
	unsigned v_pgpgin;	/* pages paged in */
	unsigned v_pgpgout;	/* pages paged out */
	unsigned v_faults;	/* total page faults taken */
	unsigned v_pgdup;	/* pagedups due to copy-on-write forks */
	unsigned v_pgrec;	/* total page reclaims */
	unsigned v_pginops;	/* total page-in operations */
	unsigned v_bhit;	/* found in buffer cache */
	unsigned v_exfod;	/* pages filled on demand from executables */
	unsigned v_zfod;	/* pages zero filled on demand */
	unsigned v_intrans;	/* intransit blocking page faults */
	unsigned v_nexfod;	/* number of exfod's created */
	unsigned v_nzfod;	/* number of zfod's created */
	unsigned v_scan;	/* scans in page out daemon */
	unsigned v_rev;		/* revolutions of the hand */
	unsigned v_dfree;	/* pages freed by daemon */
#define	v_last v_dfree
	unsigned v_swpin;	/* swapins */
	unsigned v_swpout;	/* swapouts */
};

/* systemwide totals computed every five seconds */
struct vmtotal
{
	short	t_rq;		/* length of the run queue */
	short	t_dw;		/* jobs in ``disk wait'' (neg priority) */
	short	t_pw;		/* jobs in page wait */
	short	t_sl;		/* jobs sleeping in core */
	short	t_sw;		/* swapped out runnable/short block jobs */
	short	t_free;		/* free memory pages */
	int	t_vm;		/* total virtual memory */
	int	t_avm;		/* active virtual memory */
	short	t_rm;		/* total real memory in use */
	short	t_arm;		/* active real memory */
	int	t_vmtxt;	/* virtual memory used by text */
	int	t_avmtxt;	/* active virtual memory used by text */
	short	t_rmtxt;	/* real memory used by text */
	short	t_armtxt;	/* active real memory used by text */
};
