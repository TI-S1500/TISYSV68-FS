/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char devmap_h[] = "@(#)devmap.h	1.19 (TI) 90/09/18";
#endif	SCCSID

 
#ifndef SCCSID
 
/*	Device map structure passed to Unix on startup at top of stack */

#define MAXCCB		15	/* max number of CCBs */
#define MAXSLOTS        16      /* max number of slots */
#define MAXCTRLS	8	/* max disk/tape controllers */
#define MSCTYP		1	/* ctrltype in interrupt switch for msc */
#define NPITYPE		2	/* ctrltype in interrupt switch for nupi */
#define NP2TYPE MSCTYP		/* ctrltype in interrupt switch for np2 */
#define TYPNPI		0	/* controller type nupi cntrltype array */	
#define TYPMSC		1	/* controller type msc cntrltype array */	
#define TYPNP2		2	/* controller type np2 cntrltype array */	
#endif

/* Ram is assumed to be allocated to Unix in contiguous hunks of pages */

struct ramhunk
{
	long ramaddr;	/* NuBus address of ram */
	long ramsize;	/* size of ram in pages */
};

struct devmap
{
	/***
	*  Nubus configuration structure:  1 entry per slot
	***/
	struct nu_confd
	{
		char  serial[9];		/* board serial number */
		char  revision[7];		/* board revision level */
		char  vendor_id[4];		/* vendor ID		*/
		char  type[8];			/* board type 		*/
		char  pnum[16];			/* part number 		*/
	}nu_conf[MAXSLOTS];

	char bd_type[MAXSLOTS];	/* Array of board types--indexed by slot!  */

	long flgrega[MAXSLOTS]; /* Nubus addresses of dev flag reg	*/
	long cnfrega[MAXSLOTS]; /* Nubus addresses of dev conf reg	*/
	long carrega[MAXSLOTS]; /* Nubus addresses of dev cmd addr reg	*/

	/***
	*  RAM board structure
	***/
	struct rambd
	{
		unsigned long slot;
		struct ramhunk ram;
		unsigned long *drmctl;	/* alignment */ 
	} rambd[MAXRAM];
	int nram;	/* number of ram boards */

	/***
	*  ram disk structure
	***/
	struct ramdisk
	{
		long base;	/* first vaddr for sysaddr */
		long limit;	/* last vaddr  for sysaddr */
		long l3addr;	/* vaddr of L3s for sysaddr */
		long addr;	/* virtual addr of start of chunk of ram disk */
		long size;	/* size of this chunk in blocks (kbytes) */
		long bcaddr;	/* vaddr of start of chunk buffer cache */
		long bcsize;	/* size of this chunk in blocks (kbytes) */
		long nbuf;	/* number of buffers */
	}ramdisk[MAXRAM+MAXCPU];

	/***
	*  cpu structure: 1 entry per cpu
	***/
	struct cpu_struct
	{
		long cpuaddr;			/* cpu slot address     */
		struct	ramhunk ram[MAXLOCRAM]; /* contiguous local ram */
	} cpu[MAXCPU];

	long bdtype[MAXCPU];	/* Array of cpu board types 020/030/1505 */

	/***
	*  CCB structure: 1 entry per Comm Carrier Board
	***/
	struct ccbd
	{
		long slot;			/* ccb slot address     */
		long ramadd;			/* ram addr of CCB	*/
		long ramsiz;			/* size of ram in bytes */
	}ccb[MAXCCB];
 
	/***
	*  nupi structure: 1 entry per slot
	***/
	long nupi[MAXSLOTS];		/* logical device number or -1; */
	int  numnupis;			/* number of nupis in chassis */

	/***
	*  msc structure: 1 entry per slot
	***/
	long msc[MAXSLOTS];		/* logical device number or -1; */
	int  nummscs;			/* number of mscs and np2s in chassis */

	/*
	*  Interrupt switch for determining which kind of controller
	*  is present
	*/
	struct intsw
	{
		int	ctrltype;	/* msc or nupi */
		int	logctrl;	/* logical controller number */
	}intsw[MAXCTRLS]; 

	unsigned short cntrltype[MAXCTRLS];	/* type of controllers*/

	/***
	*  unix resources  
	***/

	unsigned long	swapsize; 	/* Blocks in swapdev 	*/
	unsigned short	slots;	/* 1 bit for every slot we will use */
	unsigned short	fille;	/* lets keep it on word boundaries */
	unsigned long rootdev;	/* root source device */
 	unsigned long pipedev;	/* pipe source device */
	unsigned long swapdev;	/* swap source device */

	char console[8];	/* name of unix console device */
	char dummy[48];		/* reserved for expansion */
};

/* 
 * Logical board type numbers.  See bd_type array.
*/
/*			 0	Empty slot 				  */
#define NUPI_TYP	 1
#define MSC_TYP		 2
#define NP2_TYP		 3
/*				Leave hole for more disk ctrl type boards. */
#define B68020_TYP	0x20
#define B68030_TYP	0x21
#define B1505_TYP	0x22
#define B1507_TYP	0x23
/*				Leave hole for more cpu type boards. */
#define CCB_TYP		0x30
#define CPO_TYP		0x31
#define CP2_TYP		0x32
/*				Leave hole for more ccb type boards. */
#define MEM_TYP		0x40
/*				Leave hole for more mem type boards. */

/* 
* defines for RAM board 
/* RAM failure register */
#define RAMFR    0x00FFC018
#define RAMCERR	 0x00080000l
#define RAMUCERR 0x00100000l

#ifdef KERNEL
extern struct devmap devmap;
#endif
 
