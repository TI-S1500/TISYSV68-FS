/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char cpuloc_h[] = "@(#)cpuloc.h	1.26 (TI) 90/10/04";
#endif	SCCSID

#ifdef __STDC__
#define VOLATILE volatile
#else
#define VOLATILE
#endif

/* 
*	 define cpu local area virtual addresses
*/

struct cpuloc
{
	VOLATILE long _nmistack[48]; /* nonmaskable interrupt stack	*/
				/* used during process switching	*/
struct	cpu  *	_cpubase;	/* mapped pointer to cpu registers	*/
	long	_cpuid;		/* contains ID of this cpu		*/

	long	_bdtype;	/* cpu board type (020/030)		*/
	ulong * _ccrp;		/* ptr to cache control    reg on board */
struct  msb  *  _berrsrp;	/* ptr to bus error status reg on board */
struct  msb  *  _toutsrp;	/* ptr to timeout   status reg on board */
	ulong * _drmctlp;	/* ptr to dram  control    reg on board */
	ulong * _drmstap;	/* ptr to dram  status     reg on board */

	sema_t *_lckdsema;
	VOLATILE long _mmbroot;	/* contains phys. addr of rptable	*/
				/* set up by stbm			*/
	VOLATILE long _haltsp;	/* DEBUG				*/

	VOLATILE long _acctim;	/* previous value of accounting timer 	*/
	VOLATILE long _msptimer; /* most sig. part of time stamp 	*/
	VOLATILE long _newacct;	/* latest value of accounting timer	*/
	VOLATILE long    _usrtim; /* accumulated user-mode cpu time 	*/
	VOLATILE long    _systim; /* accumulated system-mode cpu time 	*/
	VOLATILE short	_savest; /* saved sr reg - see semaphore routines*/
	VOLATILE short	_tasdct; /* tas delay count - see sema.s	*/
	VOLATILE long	_tasdelsp;	/* saved sp reg - see sema.s	*/
struct	proc *  _curproc;	/* ptr to currently running process	*/
	long	_lckdos;
	long	_fub4pu;	/*					*/
	long	_qrunflag;	/* Streams hook				*/
	long	_mmust1;	/* status from MMU status register	*/
	long	_ks_inval;	/* Flag - need to invalidate stack page */
				/* dummy entries - for development -	*/
	long	_dummy1;	/* so recompilation of world not needed	*/
/*****	long	_dummy2;	** so often.				*/

/* #######################################################################
*  NOTE:  Any changes above this line MUST have corresponding changes
*	  made to the assembler language definition of the cpu local
*	  area (end.s).  No symbols defined below this line can be
*	  referenced by assembler language routines !!!!
** ##################################################################### */
	int	_avefree;	/* moving average of remaining free blocks */
	int	_avefree30;	/* 30 sec (avefree is 5 sec) moving average */
	long	_bal_tim;	/* time counter for load balancing	*/
	int	_deficit;	/* estimate of needs of new swapped in procs */
	int	_freemem;	/* amount of currently available memory */
	int	_highfree;	/* max available click			*/
	long	_idleing;	/* idleing flag				*/
	long	_L0phyadr;
	int	_lastnrun;   /* count (per second) of # of runnable processes */
	int	_lowfree;	/* min available click			*/
	char	*_csdcalled;	/* calcsd() called flag-see calcsd code*/
	int	_maxcmap;
	int	_maxmem;	/* current max user memory		*/
	int 	_mscdone[2];	/* one done value per cpu per MSC */
	sema_t	*_Lckdvsem;	/* See msg.c & sema.c			*/
	int	_one_sec;	/* one second counter for clock		*/
	int	_physmem;	/* physical memory (in clicks) on board */
	int	_schedpgct;	
	int	_sm_ticks;	/* Reserved for Texas Instruments */
	long	_sptrap;	
	int	_tmo_cnt;
	long	_usrsptrap;
	long	_vmcall;
	int	_lowhand;	/* low value for hand used by pageout	*/

	struct	vmmeter		_cnt;
	struct	vmmeter		_rate;
	struct	vmmeter		_sum;

	struct	vmparam		_vmparam;

	struct	pfclk		_pfclk;

	int	_clicnt[CLMAX];	/* # cluster ins of particular size */
	int	_clocnt[CLMAX];	/* ditto for cluster outs */

	short	_lticks;
	short	_tmo_ok;
	short 	prflg;		/* local printf flag */
	short 	_refcnt;	/* reference count of device inode */
	short	_ramerrcnt;	/* parity error counter */
	short	_align1;	/* unused-longword alignment only */

	struct	vmtotal		_total;
};
/*
 *	Define various variables if KERNEL is defined.  An application
 *	wouldn't want this done, but the O.S. does.  
 *
 *	NOTE:  Add #defines to this file only when truely useful.  Most
 *	such definitions should be added to the file that really needs
 *	them so that all other files that include this one don't have
 *	to carefully avoid too many particular variable names.
*/
#ifdef	KERNEL

extern	struct	cpuloc	cpuloc;

#define cpuid		cpuloc._cpuid
#define curproc		cpuloc._curproc

#endif
