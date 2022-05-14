/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char cpuloc_h[] = "@(#)cpuloc.h	1.31 (TI) 92/01/07";
#endif	SCCSID

#ifdef __STDC__
#define VOLATILE volatile
#else
#define VOLATILE
#endif

/* 
*	Define cpu local area virtual addresses.
*
*	NOTE: The first few of these are arranged carefully so that 
*	      frequently referenced items are in the same 16-byte 
*	      cache line on 1505s & 1507s!  ALSO, see NOTE below.
*/

struct cpuloc
{
	VOLATILE long _nmistack[48]; /* nonmaskable interrupt stack	*/
				/* used during process switching	*/
	long	_cpuid;		/* contains ID of this cpu		*/
	long	_bdtype;	/* cpu board type (020/030/1505/1507)	*/
	long	_chiptype;	/* contains chip type (020/030/040)	*/
	VOLATILE long _qrunflag;/* Streams hook				*/

struct	proc *  _curproc;	/* ptr to currently running process	*/
	long	_bdspeed;	/* board's speed factor			*/
	long *  _myrunrun;	/* ptr to this cpu's runrun flag	*/
	VOLATILE int _countsvcs;/* flag to count system calls		*/

	VOLATILE long _acctim;	/* previous value of accounting timer 	*/
	VOLATILE long _newacct;	/* latest value of accounting timer	*/
	VOLATILE long    _usrtim; /* accumulated user-mode cpu time 	*/
	VOLATILE long    _systim; /* accumulated system-mode cpu time 	*/

	ulong * _ccrp;		/* ptr to cache control    reg on board */
struct  msb  *  _toutsrp;	/* ptr to timeout   status reg on board */
#define _sbc_errp _toutsrp      /* ptr to SBC Error Status Register	*/
struct  msb  *  _berrsrp;	/* ptr to bus error status reg on board */
	ulong * _drmstap;	/* ptr to dram  status     reg on board */

struct	cpu  *	_cpubase;	/* mapped pointer to cpu registers	*/
	long	_mmust1;	/* status from MMU status register	*/
	long	_fub4pu;	/*					*/
	VOLATILE long _msptimer; /* most sig. part of time stamp 	*/

	VOLATILE short	_savest; /* saved sr reg - see semaphore routines*/
	VOLATILE short	_tasdct; /* tas delay count - see sema.s	*/
	VOLATILE long	_tasdelsp;	/* saved sp reg - see sema.s	*/
	sema_t *_lckdsema;
	long	_lckdos;

	ulong * _drmctlp;	/* ptr to dram  control    reg on board */
	long	_ks_inval;	/* Flag - need to invalidate stack page */
	VOLATILE long _haltsp;	/* DEBUG				*/
	VOLATILE long _mmbroot;	/* contains phys. addr of rptable	*/
				/* set up by stbm			*/
	long	_idleing;	/* idleing flag				*/
	short	_need40cp;	/* need sys stk pushed to memory on 040s*/
				/* dummy entries - for development -	*/
	short	_dummy1;	/* so recompilation of world not needed	*/
	long	_dummy2;	/* so often.				*/

/* #######################################################################
*  NOTE:  Any changes above this line MUST have corresponding changes
*	  made to the assembler language definition of the cpu local
*	  area (end.s).  No symbols defined below this line can be
*	  referenced by assembler language routines !!!!
** ##################################################################### */
	int	_avefree;	/* moving average of remaining free blocks */
	int	_avefree30;	/* 30 sec (avefree is 5 sec) moving average */
	long	_bal_tim;	/* time counter for load balancing	*/
	char   *_csdcalled;	/* calcsd() called flag-see calcsd code*/
	int	_deficit;	/* estimate of needs of new swapped in procs */
	int	_freemem;	/* amount of currently available memory */
	char   *_gen_timein;	/* flag: timein() needs to be called	*/
	int	_highfree;	/* max available click			*/
	long	_L0phyadr;
	sema_t *_Lckdvsem;	/* See msg.c & sema.c			*/
	int	_lastnrun;   /* count (per second) of # of runnable processes */
	int	_lowfree;	/* min available click			*/
	int	_lowhand;	/* low value for hand used by pageout	*/
	int	_maxcmap;
	int	_maxmem;	/* current max user memory		*/
	int 	_mscdone[2];	/* one done value per cpu per MSC */
	int	_one_sec;	/* one second counter for clock		*/
	int	_physmem;	/* physical memory (in clicks) on board */
	int	_schedpgct;	
	int	_sm_ticks;	/* Reserved for Texas Instruments */
	long	_sptrap;	
	int	_tmo_cnt;
	long	_usrsptrap;
	long	_vmcall;

	struct	vmmeter		_cnt;
	struct	vmmeter		_rate;
	struct	vmmeter		_sum;

	struct	vmparam		_vmparam;

	struct	pfclk		_pfclk;

	int	_clicnt[CLMAX];	/* # cluster ins of particular size */
	int	_clocnt[CLMAX];	/* ditto for cluster outs */

	short	_lticks;
	short	_tmo_ok;
	short	_tmo_ok2;
	short	_tmo_type;
	short 	prflg;		/* local printf flag */
	short 	_refcnt;	/* reference count of device inode */
	short	_ramerrcnt;	/* parity error counter */
	short	_align1;	/* unused-longword alignment only */

	struct	vmtotal		_total;
struct	mif040 * _mif0ptr;	/* ptr to MIF0 on B68040 boards	      */
struct	mif040 * _mif1ptr;	/* ptr to MIF1 on B68040 boards       */
struct	snif040 * _snifptr;	/* ptr to SNIF on B68040 boards       */
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
