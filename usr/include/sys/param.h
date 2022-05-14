/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char param_h[] = "@(#)param.h	1.75 (TI) 93/02/24";
#endif	SCCSID

#define NBPBLK   1024    /* number of bytes per block */
#define NBLKPC   4       /* number of blocks per click */
      
#define L1MASK      0xfe000000l  /* mask on address to get L1 index */
#define L2MASK      0x01fc0000l  /* mask on address to get L2 index */
#define L3MASK      0x0003f000l  /* mask on address to get L3 index */

#define L1SHIFT     25           /* shift to get L1 index right justified */
#define L2SHIFT     18           /* shift to get L2 index right justified */
#define L3SHIFT     12           /* shift to get L3 index right justified */

#define MAXL2PTEPG  1024         /* # of L2 ptes per 4k Page (NPTESL2PT * NL2PTPC) */
#define MAXL3PTEPG  1024         /* # of L3 ptes per 4k Page (NPTESL3PT * NL3PTPC) */

/*
 * fundamental variables
 * don't change too often
 */

#define	NOFILE	100		/* max open files per process */
#define	MAXPID	30000		/* max process id */
#define	MAXUID	60000		/* max user id */
#define	MAXLINK	1000		/* max links */

#ifdef m68k
#define	MAXMEM	(128*1024*1024/NBPC)/* max 68000 core (128MB) in clicks */
#define B68020	0		/* possible board types values 	*/
#define B68030  0x30
#define B68040  0x04
#define B1505   0x15
#define B1507   0x14
#define B1506   0x06
#define B1508   0x08

#define _020_CHIP       0x2
#define _030_CHIP       0x3
#define _040_CHIP       0x4

#define MFF030  240 		/* Est. percent 030 is faster than 020 */
#define MFF040  880             /* Ext. percent 040 is faster than 020 */
#define RLSPEED0 110		/* Est. percent cpu 0 is faster than others*/
#define ULIMITSHFT 9		/* number of bytes to shift for ulimit */
#else
#define	MAXMEM	(16*128)	/* max core in 512-byte clicks */
#endif
#ifdef NU
#define MAXSEGSIZ (128*1024*1024/NBPC)/* max segment size, imposed by cmap.h */
#define MAX_SSIZE (256*1024/NBPC)	/* max user stack size (clicks) */
#endif

#define MAXSLOTS        16      /* max number of slots                  */
#define MAXCPU		16	/* max number of cpu's 			*/

#define	MAXBLK	125		/* max blocks possible for phys IO */
#define	SSIZE	1		/* initial stack size (clicks) */
#define	SINCR	1		/* increment of stack (clicks) */
#define	USIZE	1		/* size of user block (clicks) */
#define	ISIZE	1		/* size of system's interrupt stack (clicks)*/
#define DMAPPGS 4		/* number of configurable data L3s 4k pages*/
#define DMAPL3S 64		/* number of L3 tables for configurable data*/
#define	CPULOCSZ  1 		/* size of cpu local area (clicks) */
#define MAXLOCRAM	2	/* maximum contiguous hunks of local ram */
#define MAXRAM		4	/* max number of ram boards		*/
#define RAMID		9	/* ram device bdevsw major number */
#define	PROC1		3*ncpu	/* index into proc table for init process    */
#ifdef m68k
#  ifdef MC68020
#    define	USRSTACK (0)			/* Start of user stack */
#  else
#    ifdef NU
#	define	K1STACK (0x1000000) /* Top of kernel stack */
#	define  USTRUCT_LOW	(K1STACK-(USIZE*NBPC))
#	define  KISTACK		USTRUCT_LOW	/* Top of interrupt stack */
#	define  KISTACK_LOW	(KISTACK-(ISIZE*NBPC))
#      define	USRSTACK (0x8000000) /* Start of user stack */
#    else
#      define	USRSTACK (0x8000000)		/* Start of user stack */
#    endif
#  endif
#else
#    define	USRSTACK (0x80000000-ctob(USIZE))  /* Start of user stack */
#endif

#define	CANBSIZ	256		/* max size of typewriter line	*/
#define	HZ	20		/* Ticks/second of the clock */
#define	ACCT_TCKS (10000000/HZ)	/* acct timer increments per clock tick */
#define ACCT_ROLOVR 300000000	/* 30 seconds worth of acct timer ticks */
#define TIMEZONE (6*60)		/* Minutes westward from Greenwich */
#define DSTFLAG 1		/* Daylight Saving Time applies here */
#define	NCARGS	(16 * 1024)	/* # characters in exec arglist */
#define	NSYSENT	81 		/* # of system calls */

#define FREGS   27		/* Size of FPU floating point registers */
				/*  24 longs for FPU registers (8*3) 	*/
				/*   3 longs for FPU status & control regs */
#define FPUSIZE 55		/* worst case save size for 68882 FPU 	*/
				/* Total of 75 words as follows: 	*/
				/*  54 longs for FPU internal state 	*/
				/*   1 long for FPU fmt word pointer 	*/
#define FHEAD *(long *)(u.u_fpsav[FPUSIZE-1] ) /* Get format word 	*/
#define BIU_LOC (FPUSIZE - 2)   /* location of the BIU 			*/
#define BIU_EPB 0x08000000	/* BIU exception pending bit (not)	*/
#define FPU_MSK 0x00ff0000	/* Get frame size 			*/
#define FPU_882 0x00380000	/* Frame size for idle on 68882		*/
#define FPU_881 0x00180000	/* Frame size for idle on 68881		*/
#define FPU_040 0x00000000	/* Frame size for idle on 68040		*/

#define MG68881 0x7f0f0000   	/* Check this to shrink state frame for 882 */
#define Mg68881 0x5f0f0000   	/* Check this to shrink state frame for 882 */
#define MN68881 0x7c0e0000   	/* Load this to shrink state frame for 881 */
#define Mn68881 0x5c0e0000   	/* Load this to shrink state frame for 881 */

#define MG68882 0x7c0e0000	/* Check this to shrink state frame for 881 */
#define Mg68882 0x5c0e0000	/* Check this to shrink state frame for 881 */
#define MN68882 0x7c0e0000    	/* Load this to grow state frame for 882 */
#define Mn68882 0x5c0e0000    	/* Load this to grow state frame for 882 */

#define FPMASK   0xdfff0000	/* Bit mask for fpu model/revision compare */
#define WMASK   0x0000ffff	/* Bit mask for fpu model/revision compare */
				/* and BIU flags			   */
#define STRSTKSZ  8 * 1024	/* 8 k of stack for streamer */

#define	PATHSIZE	1024	/* max size of a pathname for nami */
/*
 * priorities
 * should not be altered too much
 */

#define	PMASK	0177
#define	PCATCH	0400	/* Return to caller on non-ignored signals */
#define	RICATCH	01000	/* Return to caller on signals user said to ignore!*/
#define	ICATCH	02000	/* Ignore signals until process is asleep  */
#define	PSWP	0
#define	PINOD	10
#define	PRIBIO	20
#define	PZERO	25
#define	NZERO	20
#define	PPIPE	26
#define	PWAIT	30
#define	PSLEP	39
#define	PUSER	60
#define	PIDLE	127
#define PX	47	/* PIDLE - 1 - (PUSER-NZERO) -39 <max p_nice value> */

/*
 * fundamental constants of the implementation--
 * cannot be changed easily
 */

#define	NBPW	sizeof(int)	/* number of bytes in an integer */

#define	NCPS	1		/* Number of clicks per segment */
#define	NBPC	4096		/* Number of bytes per click */
#define	NCPD	4		/* Number of clicks per disk block */
#define	BPCSHIFT	12	/* LOG2(NBPC) if exact */
#define	BPL2SHIFT	18	/* LOG2(amt of space mappable by an L2 entry) */
#define	BPL1SHIFT	25	/* LOG2(amt of space mappable by an L1 entry) */

#define NBPL1  512		/* number of bytes per L1 page table */
#define NBPL2  512		/* number of bytes per L2 page table */
#define NBPL3  256		/* number of bytes per L3 page table*/

#define NPTESL1PT   128   	/* 128 ptes per L1 page table */
#define NPTESL2PT   128   	/* 128 ptes per L2 page table */
#define NPTESL3PT   64    	/* 64  ptes per L3 page table */

#define NL1PTPC     8     	/* 8  l1 page tables can fit in 1 click */
#define NL2PTPC     8     	/* 8  l2 page tables can fit in 1 click */
#define NL3PTPC     16    	/* 16 l3 page tables can fit in 1 click */

#define	MOD128		0x7F	/* (number & MOD128) == (number % 128) */
#define	MOD256		0xFF	/* (number & MOD256) == (number % 256) */
#define	MOD512		0x1FF	/* (number & MOD512) == (number % 512) */
#define	MOD1024		0x3FF	/* (number & MOD1024) == (number % 1024) */
#define PGOFSET (NBPC - 1)
#define	NULL	0
#define	CMASK	0		/* default mask for file creation */
#define	CDLIMIT	(N512BLK * (1L<<11))	/* default max write address */
#define	NODEV	(dev_t)(-1)
#define NUMENTS	9		/* index of last entry in allocation table  */
				/* for contiguous file systems 		    */
#define	CLKTICK	50000		/* microseconds in a clock tick */

#define	UMODE	PS_CUR		/* usermode bits */
#ifdef m68k
#define	USERMODE(ps)	((ps & UMODE) == 0)
#else
#define	USERMODE(ps)	((ps & UMODE) == UMODE)
#endif

#define	BASEPRI(ps)	((ps & PS_M) == 0)

#ifdef m68k
#define SEG_SYS		0	/* System space */
#define SEG_TEXT	1	/* Text segment. Shared by default */
#define SEG_DATA	2	/* Data+Bss. Includes Text if not shared */
#define SEG_STACK	3	/* Stack segment */

#define	SEG_FIXED	3	/* Number of segs with fixed mmu_entry's */

#define SEG_SHM		4	/* Shared memory segment. */
#  ifdef NU
#define	SEG_NUBUS	5
#define	SEG_TYPES	5	/* Highest segment type	*/

#define NUBUSSEGS	8
/*
 * The system buffer pool type.  No proc will ever have a page of
 * this type.  Procs only have pages of types SEG_SYS thru SEG_TYPES.
 */
#  define SEG_BUF	6
#  endif
#endif

#if defined(vax) || defined(pdp11)
#define	lobyte(X)	(((unsigned char *)&X)[0])
#define	hibyte(X)	(((unsigned char *)&X)[1])
#define	loword(X)	(((ushort *)&X)[0])
#define	hiword(X)	(((ushort *)&X)[1])
#else
#define	lobyte(X)	(((unsigned char *)&X)[1])
#define	hibyte(X)	(((unsigned char *)&X)[0])
#define	loword(X)	(((ushort *)&X)[1])
#define	hiword(X)	(((ushort *)&X)[0])
#endif

#ifdef NU
/*
 * Handy function return values.
 */
#define	OK	(0)
#define ERR	(-1)
#endif

/*
 * Device manager major number identifiers
 */
#define NOID		0		/* no id */
#define NPID		1		/* nupi disk */
#define NTID		2		/* nupi 1/4" tape */
#define CTTYID		5		/* tty devices */
#define	CACUID		7		/* acu devices */
#define	CDNLDID		8		/* ccb downlaod */
#define CBSCID		9		/* bsc device */
#define	CBSCTID		10		/* bsc trace device */
#define	CLOGID		11		/* ccb log device */
#define INETID		15		/* lan inet */
#define	L0ID		18		/* lan L0 */
#define	IOPID		19		/* lan iop */
#define	SPPID		20		/* lan spp */
#define SNAID		24		/* sdlc device */
#define MSCDID		25		/* msc disk */
#define	MSCQID		26		/* msc 1/4" tape */
#define MSCMID		27		/* msc 1/2" tape */
#define	CLPID		30		/* parallel printer */
#define CDIALID		32		/* dial device */
#define NMID		33		/* nupi 1/2" tape */
#define MVID		35		/* multivolume driver */
#define XPTID		38		/* dnio/1500 xport */
#define VT990ID		39		/* dnio/1500 vtty */
#define X250ID		47		/* X.25 driver */
#define LAPDID		50		/* Lapd(mtc) driver */
#define MRID		71		/* mirror driver */
#define LINK_MAJOR      79              /* MTC link device driver */
#define TTY_MAJOR       80              /* MTC TTY driver */

/*
 Define NuBus address and size of NVRAM option.
 */

#define NV_NUADDR    0xf0d80000
#define NV_SIZE      0x20000

#ifndef BFUNCTION			/* Busnet switch */
#define BFUNCTION
struct bfunc {
	int (*name)();
	};
#endif

/* The number of bytes in the buffer of stbm messages passed from the
 * primitive to the kernel at the beginning of user memory
*/
#define MAX_STBM_MESSAGES_SIZE 4096
