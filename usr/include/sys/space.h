/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char space_h[] = "@(#)space.h	1.45 (TI) 91/09/16";
#endif	SCCSID

/*
** NOTE:
**
** Configurable data items are now allocated by STBM at boot time.
** Thus, their definitions can no longer occur in space.h.
*/

/* @(#)space.h	1.13 UNIX System V/68 */
#ifndef KERNEL
#define	KERNEL
#endif
#include "sys/acct.h"
struct	acct	acctbuf;
struct	inode	*acctp;


#ifdef NU
#include "sys/smap.h"
struct smap zsmap;		/* a zero filled smap */
#endif

#ifdef m68k
#include "sys/mmu.h"
/* struct	mmu_table	mmu_table[NPROC]; */	/* internal table */
#endif

#include "sys/tty.h"

#include "sys/buf.h"
struct	buf	bfreelist;	/* head of the free list of buffers */
lock_t		b_freelock;
sema_t		b_freecnt;
sema_t		b_freeslp;
struct	pfree	pfreelist;	/* Head of physio header pool */
sema_t		p_freelock;
sema_t		p_freecnt;
/* struct	buf	pbuf[NPBUF]; */	/* Physical io header pool */
/* struct	hbuf	hbuf[NHBUF]; */	/* buffer hash table */

struct	buf	bswlist;	/* head of swap buf pool */
int		swbuf_cnt;	/* current # of avail. swap bufr hdrs */

#include "sys/file.h"
/* struct	file	file[NFILE]; */	/* file table */

#include "sys/inode.h"
/* struct	inode	inode[NINODE];*/ /* inode table */

#include "sys/proc.h"
/* struct	proc	proc[NPROC];*/	/* process table */

#include "sys/map.h"
/* struct map swapmap[SMAPSIZ] = {mapdata(SMAPSIZ)}; */
/* struct map kvmap[KMAPSIZ] = {mapdata(KMAPSIZ)}; */

#include "sys/callo.h"
/* struct callo callout[NCALL];*/ /* Callout table */

#include "sys/mount.h"
/* struct mount mount[NMOUNT]; */ /* Mount table */
struct srmnt srmount[1];	/* Server mount table */

#include "sys/elog.h"
#include "sys/err.h"
struct	err	err = {		/* Error slots */
	NESLOT,
};

#include "sys/sysinfo.h"
struct sysinfo sysinfo;
struct cfginfo cfginfo;
struct syswait syswait;
struct syserr syserr;

#include "sys/utsname.h"
#include "sys/erec.h"
int corerrindx = 0;			/* index into incore error log */
struct corerr corerrlog[CORLOGSIZ];	/* incore (kernel origin) error log */

/* SVVS */
int lo_lo[8];
int locnt = 4;
int tmx_tmx[8];
int tmx_low[9];
int ti_tivc[0xE4];
int tivc_cnt = 12;
int tmxcnt = 4;
int tmxlcnt = 3;
/* SVVS */
#include "sys/stream.h"
#include "sys/strstat.h"
#include "sys/stropts.h"
#include "sys/log.h"
#define NLOG  3
#define LBSIZE 20
int strstksz = STRSTKSZ;
int log_cnt = NLOG;
struct log log_log[NLOG];
int log_bsz = LBSIZE;
/*********
#define NTRW  200
struct tim_tim {
	long 	 tim_flags;
	queue_t	*tim_rdq;
	mblk_t  *tim_iocsave;
} tim_tim[NTRW];
int tim_cnt = NTRW;
struct trw_trw {
	long 	 trw_flags;
	queue_t	*trw_rdq;
	mblk_t  *trw_mp;
};
struct trw_trw trw_trw[NTRW];
int trw_cnt = NTRW;
*********/

#define MAX_SP 200
struct sp {
	queue_t *sp_rdq;		/* this stream's read queue */
	queue_t *sp_ordq;		/* other stream's read queue */
	} sp_sp[MAX_SP];
int spcnt = MAX_SP;
int nstrpush ; 
int nmuxlink ;
int nstrevent ;
int maxsepgcnt ;
int strmsgsz ;
int strctlsz ;
char strlofrac ;
char strmedfrac ;
int nmblock ;
char MAJOR[128];
char MINOR[128];

#include "sys/var.h"
struct var v = {
	0,					/* NBUF */
	0,					/* NCALL */
	0,					/* NINODE */
	(char *)0,				/* (&inode[NINODE]) */
	0,					/* NFILE */
	(char *)0,				/* (&file[NFILE]) */
	0,					/* NMOUNT */
	(char *)0,				/* (&mount[NMOUNT]) */
	0,					/* NPROC */
	(char *)0,				/* (&proc[1]) */
	0,					/* NISEG */
	(char *)0,				/* (&iseg[NISEG]) */
	0,					/* NISEG */
	(char *)0,				/* (&segdesc[NSEGDESC]) */
	0,					/* NSEGDSM */
	(char *)0,				/* (&segdsm[NSEGDSM]) */
	0,                                 	/* CLIST */
	0,					/* NSWBUF */
	0,                                      /* MIRBUFS */
	0,                                      /* MIRBUFCNT */
	0,					/* MAXUP */
	0,					/* SMAPSIZ */
	0,					/* NHBUF */
	0,					/* NHBUF-1 */
	0,					/* NPBUF */
	0,					/* FSLIMIT */
	0,					/* LTICKS */
	0,					/* MAXSEGS */
	0,					/* rdsize */
	0,  					/* nqueue */
	0,  					/* nstream */
	0,  					/* nblk4096 */
	0,  		 			/* nblk2048 */
	0,		   			/* nblk1024 */
	0,  					/* nblk512 */
	0,  					/* nblk256 */
	0,		  			/* nblk128 */
	0,  					/* nblk64 */
	0,  					/* nblk16 */
	0,  					/* nblk4 */
	0,                                      /* ns5inodes */
	0                                       /* nrbufs */
};

#include "sys/init.h"

#ifndef	PRF_0
prfintr() {}
int	prfstat;
#endif

#ifdef	TRACE_0
#include "sys/trace.h"
struct trace trace[TRACE_0];
#endif

#include	"sys/ipc.h"
#include	"sys/msg.h"

/*
struct map	msgmap[MSGMAP];
struct msqid_ds	msgque[MSGMNI];
struct msg	msgh[MSGTQL];
struct	msgsem	msgsem[MSGMNI];
*/
struct msginfo	msginfo;

#include	"sys/sem.h"
/*
struct semid_ds	sema[SEMMNI];
struct sem	sem[SEMMNS];
struct map	semmap[SEMMAP];
*/
/* struct	sem_undo	*sem_undo[NPROC]; */
/*
#define	SEMUSZ	(sizeof(struct sem_undo)+sizeof(struct undo)*SEMUME)
int	semu[((SEMUSZ*SEMMNU)+NBPW-1)/NBPW];
union {
	short		semvals[SEMMSL];
	struct semid_ds	ds;
	struct sembuf	semops[SEMOPM];
}	semtmp;
*/
struct	seminfo seminfo;
/*
sema_t	semsem[SEMMNI];
*/

/*
*  STBM will allocate the shmem structure at boot time  
*/
/*  The following structures went away with the new shared memory story */
/* struct shmid_ds	*shm_shmem[NPROC*SHMSEG]; */
/* struct shmid_ds	shmem[SHMMNI]; */
/* struct	shmpt_ds	shm_pte[NPROC*SHMSEG]; */
#include	"sys/shm.h" 
struct	shminfo	shminfo;
/* sema_t	shmsem[SHMMNI];	*/	/* parallel sema_t for * semids */

#ifdef NU
#include "sys/cmap.h"
struct cmap *cmap;
struct cmap zcmap;		/* a zero filled cmap entry */

#include "sys/vmparams.h"
/* 
 * The tunable virtual memory parameters.
 */
struct vmparam i_vmparam =
{
	0,			/* maxpgio */
	VM_MINFREE,		/* minfree */
	VM_DESFREE,		/* desfree */
	VM_LOTSFREE,		/* lotsfree */
	0,			/* slowscan */
	0,			/* fastscan */
	-2,			/* multprog */
	MAXSLP,
	SAFERSS,
	CLIN,
	CLTXT,
	CLOUT
};

#include "sys/nubus.h"
int nbsegcount = NBSEGCOUNT;
struct nubus_seg nubus_seg[NBSEGCOUNT];

#endif	NU

		/* file and record locking */
#include "sys/flock.h"
struct flckinfo flckinfo;

/* struct filock flox[FLCKREC];	  */	/* lock structures */
/* struct flino flinotab[FLCKFIL];*/	/* inode to lock assoc. structures */

#ifdef	NU
#include "sys/devmap.h"
struct devmap devmap =
{
0
};
#include "sys/boot.h"
struct boot bparam;
struct boot *initstkdata;
#endif	NU

#include	"sys/sdma.h"
/*
struct sdma_ds sdma_ds[SDMAMNI];
struct	sdma_ds	*sdma_sdmamem[SDMASEG*MAXPROC];
*/
struct sdmainfo sdmainfo;

/*struct element	pool[BN_MAXQUE]; */	/* pool of queue elements 	*/
/*int		maxque = BN_MAXQUE;	 */     /* # of queue elements		*/
/*long		vw[BN_LWINDOW][2];	 */     /* local Virtual window 	*/
/*int		lwindow = BN_LWINDOW;	 */     /* # of virtual window ptes	*/
/*int 		maxlele = BN_MAXLELE;	 */     /* max # of local elements	*/


/* pstreams-based pseudoe-tty driver pstuff */
#define PTTY_CNT 256
#include "sys/ptms.h"
struct pt_ttys ptms_tty[PTTY_CNT];
int pt_cnt = PTTY_CNT;

int ldterm_cnt = PTTY_CNT;
/* NOTE: struct also defined in ldterm.h.  Change one, you must change'm all */
struct ldterm
{
	short ld_iflags;	/* input mode: ioctl message can set */
	short ld_oflags;	/* output mode: ioctl can set */
	short ld_lflags;	/* line discipline mode: ioctl can set */
	short ld_state;		/* internal state of tty ld */
	char  ld_col;		/* output column of tty */
	char  ld_erase;		/* erase char */
	char  ld_kill;		/* line kill char */
	char  ld_intrc;		/* interrupt char */
	char  ld_quitc;		/* quit char */
	char  ld_startc;	/* start char */
	char  ld_stopc;		/* stop char */
	char  ld_eofc;		/* end-of-file char */
	char  ld_eol;		/* input delim char (like NL) */
	char  ld_eol2;		/* 2nd input delim char */
	char  ld_swtchc;	/* switch char for shl */
	char  canonb[CANBSIZ];	/* input buffer for line formation */
	char  *op;		/* pointer for input buffer */
	mblk_t *echobuf;	/* pointer to temporary storage for echo */
	short lmode_flg;	/* save raw/cannon mode request */
	int   rawlength;	/* Number of characters in the raw buffer */
	mblk_t *raw_message;	/* pointer to raw message being built */
	int  timerid;		/* id returned by timeout() */
};

#define CANBSIZ 256
struct ldterm ldterm_tty[PTTY_CNT];

#include "sys/ptem.h"
struct ptem ptem[PTTY_CNT];
int ptem_cnt = PTTY_CNT;

#include "sys/seg.h"

struct free_segd_anch segd_anch;	/* Anchor for segdesc free list */
struct free_iseg_anch iseg_anch;	/* Anchor for iseg free list    */
struct free_segdsm_anch segdsm_anch;	/* Anchor for segdsm free list  */
lock_t segdlock;			/* global segdesc lock          */
lock_t iseglock;			/* Global iseg lock             */
lock_t segdsmlock;			/* Global segdsm lock           */
struct used_iseg_anch iseg_used; 	/* Anchor for all isegs in use  */

