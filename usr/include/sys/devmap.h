/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char devmap_h[] = "@(#)devmap.h	1.33 (TI) 92/10/07";
#endif	SCCSID

 
#ifndef SCCSID
 
/* Device map structure -- built by the stbm primitive */

#define MAXCCB		15	/* max number of CCBs */
#define MAXCTRLS	16	/* max disk/tape controllers */
#define MAXETHERS	16	/* max ethernet boards			*/

#define TYPNPI          0       /* controller type nupi cntrltype array */
#define TYPMSC          1       /* controller type msc cntrltype array */
#define TYPNP2          2       /* controller type np2 cntrltype array */

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

	char  resource[MAXSLOTS];/* Resource type values from config ROMs */

	char bd_type[MAXSLOTS];	/* Array of board types--indexed by slot! */
				/* See defines below for possible values */

	/***
	*  cpu structure: 1 entry per cpu
	***/
	struct cpu_struct
	{
		long cpuaddr;			/* cpu slot address     */
		struct	ramhunk ram[MAXLOCRAM]; /* contiguous local ram */
	} cpu[MAXCPU];

	long bdtype[MAXCPU]; /*cpu board types--indexed by logical cpu num*/
			     /*param.h has all possible values		  */

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
	*  mirror disk info
	***/
	long mhaddr;	/* vaddr of start of chunk of mirror headers */
	long mhsize;	/* size of this chunk in blocks (kbytes) */
	long mhcnt;	/* number of mirror buffer headers */

	int  numnupis;		/* number of nupis in chassis */
	int  nummscs;		/* number of mscs and np2s in chassis */
	int  numethers;		/* number of ethernet boards in chassis */

	struct etherd		/* ethernet board structure: 1 entry/bd */
	{
		char	slot;
		char	subslot;
		short	unused;
		long	baseaddr;/* base physical address of board	*/
		long	memsize; /* size of memory (in bytes) on board	*/
		long	sramaddr;/* physical address of sram		*/
		long	sramsize;/* size of sram in clicks		*/
	} etherd[MAXETHERS];

	struct	ctrld		/* disk/tape controller structure	*/
	{			/* One entry per controller		*/
		char	slot;
		char	subslot;
		char	ctrltype;
		char	logctrl;
		long	carrega;
		long	cnfrega;
		long	flgrega;
		long	baseaddr;
	} ctrld[MAXCTRLS];

	/***
	*  unix resources  
	***/

	unsigned long	swapsize; 	/* Blocks in swapdev 	*/
	unsigned short	slots;	/* 1 bit for every slot we will use */
	unsigned short	fille;	/* lets keep it on word boundaries */
	unsigned long rootdev;	/* root source device */
 	unsigned long pipedev;	/* pipe source device */
	unsigned long swapdev;	/* swap source device */
/* LOGGING */
	unsigned long logdev;	/* log device */
/* LOGGING */
	char console[8];	/* name of unix console device */
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
#define B1506_TYP       0x24
#define B1508_TYP       0x25
#define B68040_TYP      0x26
/*				Leave hole for more cpu type boards. */
#define CCB_TYP		0x30
#define CPO_TYP		0x31
#define CP2_TYP		0x32
/*				Leave hole for more ccb type boards. */
#define MEM_TYP		0x40
/*				Leave hole for more mem type boards. */
#define CC8_TYP		0x50
#define LAN_TYP		0x51

/* 
* defines for RAM board 
*/
/* RAM failure register */
#define RAMFR    0x00FFC018
#define RAMCERR	 0x00080000l
#define RAMUCERR 0x00100000l

/* CCB option port Values for associated board type */
#define TKN_RING        0x1             /* extended byte designator */
#define MHA_BOARD       0x2             /* extended byte designator */
#define LAN_BOARD       0x3
#define SYNC_BOARD      0x4
#define ASYNC_4CHAN     0x5
#define ASYNC_8CHAN     0x6
#define NO_OPTION       0x7             /* no option installed      */
#define TKN_BOARD       0x8             /* token ring board         */
#define MHA_CPOBD       0xa
#define UNK_BOARD       0xff            /* unknown board type       */
#define CPO_NO_OPT	0xf		/* no option on a CPO board */

#define OPT8_EXT_ODD	0x2

#ifdef KERNEL
extern struct devmap devmap;
#endif
 
