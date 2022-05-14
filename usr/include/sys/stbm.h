/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char sccsid[] = "@(#)stbm.h	1.34 (TI) 88/09/19 ";
#endif	SCCSID
 
#ifndef SCCSID

/* number of cpu local 4k pages */
#define CPU_LOCALP  1	

/* number of kbytes of stack for STBM primitive */
#define PSTCKSIZ   9

/* length in kbytes of TI System V config. module - used by cband */ 
/* and bband to establish start of stack for the STBM primitive */
#define CONFMODSIZ	4

/* Number of 4k pages of memory reserved for ROM during boot + 1 page for
 * disk based STBM use*/
#define ROMMEM 25
		
/* Number of 4k pages of memory reserved for ROM during system operation */
#define RMEM 2

/* Number of 4k pages of memory reserved for ROM during OS execution,  
 * these  pages are reserved to preserve the state of the ROM monitor 
 * so a crash dump can be achieved */
#define RESMEM 2

/* board offset of accounting timer */
#define ACCTTMR 0x00fff7c0
#define ACCTMR030 0x00fff7b0
/*  accounting timer value for one second */
#define	ONE_SEC 0x989680L

/* default bit in partition table property bits field */
#define PDEF 0x04

/* maximum size we think the partition table will be */
#define PTLEN 4096

/* secondary processor failure error codes */
#define SCONFERR 1

/* Self test failed mask for the config register */
#define STFAIL 0x04

/*
*  Constants for range checking and defaults for configurable data structures
*  Each data structure has a maximum size, minimum count, default count, and
*  an arbitrary starting virtual address. 
*	
*/
/* approximate amount of user memory needed to get the system up */
#define REQUSERMEM	100

/* Number of L3s for the total configurable data address space */
#define DATASTRT	0x00500000l

/* add-on package configurable parameters */
#define ADDONPADDR	0x00500000l	/* MUST BE PHYSICALLY CONTIGUOUS MEM*/
#define MAXADDONP	0x00002000l	/* 8KB (256 add-on parameters)	    */

/* busnet packets: struct element pool[BN_MAXQUE] */
#define BPOOLADDR	0x00502000l	/* MUST BE PHYSICALLY CONTIGUOUS MEM*/
#define MAXELE		0x00070000l	/* poolsiz */
#define MINELE		32
#define DEFELE		200

/* size of streams net heap  char strn_heap[strnhs], struct map strn_map[] */
#define STRNHSADDR	0x00572000l	/* MUST BE PHYSICALLY CONTIGUOUS MEM*/
#define MAXSTRNHS	0x0000a000l	/* strnhs (40kb)	*/
#define MINSTRNHS	5		/* (1k bytes) 5k minimum, if not zero */
#define DEFSTRNHS	0		/* 0 == no streams net		*/

/* streams net links : struct gSTRN_link[strnlnk]*/
#define STRLNKADDR	0x0057c000l	/* MUST BE PHYSICALLY CONTIGUOUS MEM*/
#define MAXSTRLNK	0x00002000l	/* strnlnk */
#define MINSTRLNK	4		/* minimum, if not zero */
#define DEFSTRLNK	16

/* process table: struct proc proc[NPROC] */
#define PROCADDR	0x0057e000l
#define MAXPROC		0x00103000l	/* procsiz */
#define MINNPROC	50
#define DEFNPROC	100

/* mmu table: struct mmu_table mmu_table[NPROC] */ 
#define MMUADDR		0x00681000l	
#define MAXMMUT		0x0013e000l	/* mmusiz */

/* sem_undo: struct sem_undo *sem_undo[NPROC] */ 

#define SEMADD		0x007bf000l
#define MAXSEM		0x00005000l	/* semsiz */

/* text table: struct text text[NTEXT] */
#define TEXTADDR	0x007c4000l
#define MAXTEXT		0x00070000l	/* textsiz */
#define MINNTEXT	20
#define DEFNTEXT	50

/* open file table: struct file file[NFILE] */
#define FILEADDR	0x00834000l
#define MAXFILE		0x0004a000l	/* filesiz */
#define MINNFILE	100
#define DEFNFILE	250

/* in memory inode table: struct inode inode[NINODE] */
#define INODEADDR	0x0087e000l
#define MAXINODE	0x00112000l	/* inosiz */
#define MINNINODE	100
#define DEFNINODE	200

/* in memory inode table: struct s5inode s5inode[NINODE] */
#define S5INODEADDR	0x00990000l
#define MAXS5INODE	0x00156000l	/* s5inosiz */

/* callout table: struct callo callout[NCALL] */

#define CALLADDR	0x00ae6000l
#define MAXCALL		0x00003000l	/* calsiz */
#define MINNCALL	10
#define DEFNCALL	50

/* mount table: struct mount mount[NMOUNT] */
#define MOUNTADDR	0x00ae9000l
#define MAXMOUNT	0x00003000l	/* mountsiz */
#define MINNMOUNT	8
#define DEFNMOUNT	10

/* I/O memory distribution */
#define MINDIST		0
#define MAXDIST		100
#define DEFDIST		50

/* buffer pool */
#define MINNBUF		100
#define DEFNBUF		400
/* no maximum -- physical memory is the maximum */

/* file management read ahead */
#define MINFMRA 	0
#define DEFFMRA		3

/* swap buffer pool */
#define MAXNSWBUF	100
#define MINNSWBUF	4
#define DEFNSWBUF	20

/* phys buffer header pool: struct buf pbuf[NPBUF] */
#define PBUFADDR	0x00aec000l
#define MAXPBUF		0x00002000l	/* pbufsiz */
#define MINNPBUF	2
#define DEFNPBUF	8

/* hash table: struct hbuf hbuf[NHBUF] */
#define HBUFADDR	0x00aee000l
#define MAXHBUF		0x00064000l	/* hbufsiz */
#define MINNHBUF	2
#define DEFNHBUF	64

/* swap map: struct map swapmap[SMAPSIZ] */
#define SMAPADDR	0x00b52000l
#define MAXSMAP		0x00008000l	/* smapsiz */
#define MINSMAP		128
#define DEFSMAP		256

/* kvw map: struct map kvmap[KMAPSIZ] */
#define KMAPADDR	0x00b5a000l   
#define MAXKMAP		0x00008000l	/* kmapsiz */
#define MINKMAP		128
#define DEFKMAP		256

/* record locks: struct filock flox[FLCKREC] */
#define FLRECADDR	0x00b62000l
#define MAXFLREC	0x00143000l	/* flrecsiz */
#define MINFLREC	23
#define DEFFLREC	400

/* shared memory attach limit per process: struct pmapinfo pmaplist[SHMSEG]*/ 
#define SHMSEGADDR	0x00ca5000l
#define MAXSHMSEG	0x00001000l	/* shmseg */
#define MINSHMSEG	2
#define DEFSHMSEG	8

/* shared memory attach system limit: struct mmu_attach mmu_attach[SHMMAX] */
#define SHMXADDR	0x00ca6000l
#define MAXSHMX		0x00038000l	/* shmxat */
#define MINSHMX		8
#define DEFSHMX		16

/* shared memory segment count system limit: struct shmid_ds shmem[SHMMNI] */
#define SHMMNIADDR	0x00cde000l
#define SHMMNIMAX	0x00011000l 	/* shmmni */
#define SHMMNIMIN	8
#define SHMMNIDEF	8

/* message map: struct map msgmap[MSGMAP] */
#define MSGMAPADDR	0x00cef000l 
#define MAXMSGMAP	0x00008000l	/* msgmapsiz */

/* message queues: struct msqid_ds msgque[MSGMNI] */
#define MSGMNIADDR	0x00cf7000l 
#define MAXMSGMNI	0x00034000l	/* msgqsiz */
#define MINMSGMNI	0
#define DEFMSGMNI	50

/* miscellaneous defaults */
#define DEFMSGSSZ	8		/* segment size */
#define DEFMSGSEG	1024		/* segment count */
#define DEFMSGMNB	16384		/* queue size limit */
#define DEFMSGMAX	8192		/* message size limit */

/* message queue semaphores: struct msgsem msgsem[MSGMNI] */
#define MSGSEMADDR	0x00d2b000l 
#define MAXMSGSEM	0x00030000l	/* msgsem */

/* message headers: struct msg msgh[MSGTQL] */
#define MSGTQLADDR	0x00d5b000l 
#define MAXMSGTQL	0x00018000l	/* msghsiz */
#define MINMSGTQL	0
#define DEFMSGTQL	40

/* semaphore map: struct map semmap[SEMMAP] */
#define SEMMAPADDR	0x00d73000l  
#define MAXSEMMAP	0x00004000l	/* semmapsiz */

/* semaphore sets: struct semid_ds sema[SEMMNI] */
#define SEMMNIADDR	0x00d77000l  
#define MAXSEMMNI	0x00004000l	/* semqsiz */
#define MINSEMMNI	0
#define DEFSEMMNI	5
#define MINSEMMSL	0
#define DEFSEMMSL	10		/* semmsl */
#define DEFSEMOPM	10		/* semopm */
#define MINSEMOPM	0		/* semopm */

/* semaphore semaphores: struct sema_t semsem[SEMMNI] */
#define SEMSEMADDR	0x00d7b000l  
#define MAXSEMSEM	0x00002000l	/* semsem */

/* semaphores: struct sem sem[SEMMNS] */
#define SEMMNSADDR	0x00d7d000l
#define MAXSEMMNS	0x00028000l	/* semasiz */
#define MINSEMMNS	0
#define DEFSEMMNS	60

/* semaphore temporary data area:
*	union{
*		short		semvals[SEMMSL];
*		struct semid_ds ds;
*		struct sembuf 	semops[SEMOPM];
*		}semtmp;
*/
#define SEMTMPADDR	0x00da5000l   
#define MAXSEMTMP	0x00001000l	/* semtmp */

/* sem undo: int semu[(((sizeof(sem_undo)+sizeof(undo) * SEMUME)) * SEMMNU)] */
#define SEMUADDR	0x00da6000l  
#define MAXSEMU		0x00084000l	/* semusiz */
#define MINSEMU		0
#define DEFSEMMNU	30	
#define MINSEMMNU	1
#define MINSEMUME	1
#define DEFSEMUME	10

/* maximum number of sdma segments: struct sdma_ds sdma_ds[SDMAMNI] */
#define SDMAMNIADDR	0x00e2a000l  
#define MAXSDMAMNI	0x00008000l	/* sdmamni */
#define MINSDMAMNI	0
#define DEFSDMAMNI	0

/* maximum sdma attaches:struct sdma_ds *sdma_sdmamem[SDMASEG*NPROC] */
#define SDMASEGADDR	0x00e32000l  
#define MAXSDMASEG	0x00020000l	/* sdmaseg */
#define MINSDMASEG	0
#define DEFSDMASEG	0

/* maximum number of streams queues: struct stdata streams[NSTREAM] */
#define STREAMADDR	0x00e52000l  
#define MAXSTREAM	0x0001b000l	/* nstream */
#define MINSTREAM	0
#define DEFSTREAM	0
/* maximum number of streams: struct queue_t queue[NQUEUE] */
#define STRQUEADDR	0x00e6d000l  
#define MAXSTRQUE	0x00024000l	/* nstrq */
#define MINSTRQUE	0
#define DEFSTRQUE	0
/* maximum number of linked streams: struct linkblk linkblk[NMUXLINK] */
#define MUXLADDR	0x00e91000l  
#define MAXMUXL		0x00006000l	/* nmxul */
#define MINMUXL		0
#define DEFMUXL		0
/* maximum number of streams events: struct strevent strevent[NSTREVENT] */
#define STREVNTADDR	0x00e97000l  
#define MAXSTREVNT	0x00002000l	/* nstrevent */
#define MINSTREVNT	0
#define DEFSTREVNT	0
/* number of dblocks: struct dblk_t dblock[DBLOCK] */
#define DBLOCKADDR      0x00e99000l  	
#define MAXDBLOCKSZ	0x00028000l	/* ndblock */
/* number of mblocks: struct mblk_t mblock[MBLOCK] */
#define MBLOCKADDR	0x00ec1000l  
#define MAXMBLOCKSZ	0x0004b000l	/* nmblock */
/* number of strn_map: struct map strn_map[STRNHSZ/64] */
#define STRNMAPADDR	0x00f0c000l  		
#define MAXSTRNMAP	0x00002000l	/* strnmap (40kb/64 *sizeof(map))*/
#define MINSTRNMAP	80		/* 5k/64 		*/
/* number of strn_stat:  struct strn_stat gSTRN_stat[STRN_LINKS] */
#define STRNSTATADDR	0x00f0e000l  
#define MAXSTRNSTAT	0x00002000		

/* miscellaneous streams related items */
#define DEFMAXSEP	0		/* nmaxsepgcnt */
#define MAXMAXSEP	512
#define MINMAXSEP	0
#define DEFSTRPUSH	0		/* nstrpush	*/
#define MAXSTRPUSH	512
#define MINSTRPUSH	0
#define DEFSTRMSGSZ	0		/* strmsgsz	*/
#define MAXSTRMSGSZ	40960
#define MINSTRMSGSZ	0
#define DEFSTRCSZ	0		/* strctlsz	*/
#define MAXSTRCSZ	40960
#define MINSTRCSZ	0
#define DEFSTRLO	0		/* strlofrac	*/
#define MAXSTRLO	100
#define MINSTRLO	0
#define DEFSTRMED	0		/* strmedfrac	*/
#define MAXSTRMED	100
#define MINSTRMED	0
#define DEF4096V	0
#define MAX4096V	512
#define MIN4096V	0
#define DEF2048V	0
#define MAX2048V	1024
#define MIN2048V	0
#define DEF1024V	0
#define MAX1024V	2048
#define MIN1024V	0
#define DEF512V		0
#define MAX512V		4096
#define MIN512V		0
#define DEF256V		0
#define MAX256V		8192
#define MIN256V		0
#define DEF128V		0
#define MAX128V		16384
#define MIN128V		0
#define DEF64V		0
#define MAX64V		32767
#define MIN64V		0
#define DEF16V		0
#define MAX16V		32767
#define MIN16V		0
#define DEF4V		0
#define MAX4V		32767
#define MIN4V		0

/* 
* msc disk/tape controller structure 
*/
#define MSCADDR		0x00f10000l  
#define MSCMAX		0x00019000l

/* 
*  nupi disk/tape controller structure 
*/
#define NPIADDR		0x00f29000l  
#define NPIMAX		0x0000d000l

/*
*  mapout table
*/
#define MAPTBLADDR	0x00f36000l  
#define MAXMAPTBLSZ	0x0000a000l
#define DEFMAPTBLSZ	0x00000400l
#define MINMAPTBLSZ	0x00000100l

/*
*  number of map tables
*/
#define MINNMAPTBLS	0x00000001
#define MAXNMAPTBLS	0x0000000f	
#define DEFNMAPTBLS	0x00000001

/*
*  number of mapout devices struct map_cntl mapcntl[NMAPDEV]
*/
#define MAPDEVADDR	0x00f40000l  
#define MAXNMAPDEV	0x00004000l
#define DEFNMAPDEV	1
#define MINNMAPDEV	1

/* Fudge factor for kernel virtual window size(in clicks): Max process 
*  address space + shared memory space + buffers and buffer headers + 
*  (ncpu * KVW_FIXED)
*/
#define KVW_FIXED 256

/* 
*  Size of kernel virtual window is configured transparently based on the
*  user selected file buffers, swap buffer headers, shared memory, and
*  number of processes.
*  Kernel Virtual Window  has an entire L2 of its own.
*/
#define KVWADDR		0x00f44000l  
#define KVWMAX		0x00020000l
/*
*  NOTE:  It is VITALLY IMPORTANT that the KVW does NOT overlap in
*  its logical addresses with the following hard-coded logical addresses.
*  These hard-coded logical addresses must agree with end.s 
*  definitions. 
*/
#define CPU_REGISTERP 1         /* number of cpu register pages */
#define HOLE1		(KISTACK_LOW-(ISIZE * NBPC ))
#define CPU_LOCAL_ADR	(HOLE1-(CPU_LOCALP * NBPC ))
#define	CPUBADDR	(CPU_LOCAL_ADR-(CPU_REGISTERP * NBPC ))

/*
*  address of first 32MB chunk of buffer cache/RAM disk
*/
#define BCADDR		0x6000000l

/* shared memory break value (1K bytes) */
#define SHMBRKMAX	8192
#define SHMBRKMIN	1
#define SHMBRKDEF	1024

/* shared memory 1k unit count system limit   MAX is the 1/2 of all user memory */ 
#define SHMALLMIN	32
#define SHMALLDEF	140

/* file size limit in 512 byte blocks */
#define MAXFSLMT	0x400000
#define MINFSLMT	0x400		
#define DEFFSLMT	16384		

/* maximum processes per user */
#define MINUPL		4
#define DEFUPL		25

/* maximum processes size (1k bytes) */
#define MINPSIZ		1000
#define MAXPSIZ		131072
#define DEFPSIZ		16384

/* maximum stack size (1k bytes) */
#define MINSSIZ		1000
#define MAXSSIZ		131072
#define DEFSSIZ		16384

/* time slice value (lticks) */
#define MINLTICK	1
#define DEFLTICK	20

/* load balancing minimum time */
#define MINBTIM		2
#define DEFBTIM		5

/* load balancing minimum memory */
#define MINBMEM		20
#define DEFBMEM		200

/* default enable core dump */
#define DEFENCORE	1


/******** 
*
* table for distribution of ram disk and buffer cache 
*
**********/
struct disttab {
	int	meg[MAXCPU];
	int	rdsiz[MAXCPU];
	int	nbuf[MAXCPU];
	long	nrbuf[MAXCPU];			/* Ram board buffers */
	};

/********
*
*   This structure contains the data provided by STBM ROM code to
*   the STBM primitive.  This structure is found on the STBM stack
*   when the primitive is entered
*
*
********/
struct rom
{
	unsigned long  slot;		/*  slot ID we are running in */
	unsigned long  mslot;		/*  slot ID of STBM master */	
	struct stbmcb *cp;  /*  pointer to STBM command buffer */
};

struct stbmcb
{
	long statflg;
	long rambase;			/* nubus address to load  	*/
	long monitor;
	long keybd;
	long lodsrc;
	char lodname[4];		/* name of load partition 	*/
	long cfgbnd;
	char cfgname[4];		/* name of configuration band	*/
	long *sync;			/* pointer to sync flag */
};
/*
*  Structure which follows stbmcb structure in memory.  This structure
*  can be expanded in the future to pass more information from pass 1
*  of the primitive to pass 2.
*/
struct stbmsave
{
	long entcnt;			/* Num of config entries	*/
};
/********
* 
*       The following structure describes the information provided by
*       ROM based STBM code at boot time.  This information includes the
*	STBM command buffer which is only used for the STBM master.  This
*	information also includes special information for accessing the
*       ROM based diagnostic engine interpreter.
*
********/
struct romdata
{
	long *stack;			/* ROM based STBM saved stack pointer */
	long *data;			/* ROM based STBM data pointer */
	int  (*init_mon)(); 		/* initialize monitor */
	int  (*draw_char)(); 		/* draw character */
	int  (*init_key)(); 		/* initialize keyboard */
	int  (*get_key)(); 		/* read a character */
	int  (*init_if)(); 		/* initialize interface */
	int  (*init_unit)(); 		/* initialize unit */
	int  (*dev_stat)(); 		/* load source status */
	int  (*load_pgm)(); 		/* load program */
	int  (*init_de)();		/* init for generic de code */
	int  (*run_de)();		/* run generic de code */
	struct stbmcb stbmcb;		/* master's command buffer from ROM */
};

/********
*
*  This structure is the overhead information provided to STBM ROM
*  by the boot band installation utility.  This information serves as
*  a guide for ROM to massage and enter the boot band
*
********/
struct	stbmovhd
{
	long	intvec;		/* offset to primitive's interrupt vectors */
	long	veccnt;		/* count of vectors */
	long	pc;		/* pc to enter primary */
	long	stack;		/* stack pointer value to enter unix */
	struct	stbmcb *stbmcb;  /* pointer to STBM command buffer */
};

/********
*
*  masks for statflag
*
********/
#define STBMBUSY	0x00000080L
#define STBMSTATUS	0xffffff7fL


/********
*
* miscellaneous values
*
********/

#define BAITADDR	0x000010000l

/********
*
*  The following macros are used to simplify position independence.
*  They add the slot and the beginning of the STBM primitive to
*  determine the physical address for position independent disk based
*  STBM code.
*
********/

#define Adjust(x)  (char *)x + rom.slot + lodinfo.stbmbgn
#define Fadj(x)  (int(*)())((char *)x + rom.slot + lodinfo.stbmbgn)
#define ADJUST(x)  (char *)x + rp->slot + lp->stbmbgn
#define FADJ(x)  (int(*)())((char *)x + rp->slot + lp->stbmbgn)
#define CADJ(x)  (int(*)())((char *)x + rp->slot + lp->stbmbgn)
#define Dbug(x,y) if(lp->flags&V_FLAG){extern int dbgmsg();int(*df)();df=FADJ(dbgmsg);(*df)(rp,lp,vp,x,y);}
#define DBUG(x,y) if(lodinfo.flags&V_FLAG){extern int dbgmsg(); int(*df)();df=Fadj(dbgmsg);(*df)(&rom,&lodinfo,&stbmdata,x,y);}
/********
*
*  The following structure is built by the boot band installation utility
*  to guide the STBM primitive in booting unix.  It is found on the STBM
*  primitive stack within the load band
*
********/

struct lodinfo
{
	long	tpages;		/* pages of kernel text */
	long	dbpages;	/* pages of kernel data and bss */
	long	stbmbgn;	/* offset of primitive within load band */
	long	entry;		/* virtual address of unix entry */
	struct  romdata	*romdata; /* pointer to data passed by ROM */
	long	flags;		/* flag for STBM primitive verbose option */
};
/* flag for lodinfo.flags for STBM primitive verbose option */
#define V_FLAG 1			

/********
*
* This structure contains the definitions for global STBM variables.
* Isolating these definitions in a structure facilitates postition independence
* as follows:   The structure is declared on the stack in the main program
* a pointer to this structure is passed to all functions.  All accesses to
* these variables by functions other than main are through pointers hence
* postion independent.  
*
********/
struct stbmdata
{
	int 	plen;		/* length of partition in kbytes */
	char	console[14];	/* console name */
	unsigned long cputype;	/* our cpu type */
	int	dumpslot;	/* dump tape slot */
	int	dindex;		/* dump index */
	char	dlunit[4];	/* logical dump unit in ascii */
	int	dumpunit;	/* dump tape unit */
	char 	*nvaddr;	/* pointer to nvram */
	int	v;		/* value for return from getval */
	int	nproc;		/* number of process table entries */
	int	procsiz;	/* size of process table */
	int	mmusiz;		/* size of mmu table */
	int	semsiz;		/* size of *sem_undo[NPROC] */
	int	nfile;		/* number of open file table entries */
	int	filesiz;	/* size of open file table */
	int 	ntext;		/* number of text structures*/
	int	textsiz;	/* size of text structures */
	int	ninode;		/* number of in core inodes */
	int	inosiz;		/* size of inode structures */
	int	s5inosiz;	/* size of s5inode structures */
	int	ncall;		/* number of callout table entries */
	int	calsiz;		/* size of callout table */
	int	nmount;		/* number of mount table entries */
	int	mountsiz;	/* size of mount structure */
	int	nbuf;		/* number of file buffers specified by user*/
	int	totbuf;		/* total number of file buffers */
	int	bufsiz;		/* size of file buffers and buffer headrs */
	int	nswbuf;		/* number of swap buffers */
	int	npbuf;		/* number of phys buffer headers */
	int	pbufsiz;	/* size of phys buf header pool */
	int	nhbuf;		/* number of hash buffers */
	int	hbufsiz;	/* size of hash buffer list */
	int	nsmap;		/* number of swap map entries */
	int	smapsiz;	/* size of smap structure */
	int	nkmap;		/* number of kvw map entries */
	int	kmapsiz;	/* size of kvw map strucure */
	int	nmsgmap;	/* number of message map entries */
	int	msgmapsiz;	/* size of message map structure */
	int	msgssz;		/* size of message segment */
	int	msgseg;		/* number of message segments */
	int	msgsiz;		/* size of memory for messages */
	int	msgmni;		/* number of message queues */
	int	msgqsiz;	/* memory for msg queues */
	int	msgsem;		/* memory for msg semaphores */
	int	msgmnb;		/* message queue size limit */
	int	msgtql;		/* maximum number of messages */
	int	msghsiz;	/* size of headers for max messages */
	int	msgmax;		/* maximum message size */
	int	nsemmap;	/* number of semaphore map entries */
	int	semmapsiz;	/* size of semaphore map structure */
	int	semmni;		/* number of semaphore sets */
	int	semqsiz;	/* size of semaphore identifier struct */
	int	semsem;		/* size of semaphore semaphore structure */ 
	int	semmsl;		/* maximum semaphores per set */
	int	semmns;		/* maximum semaphores per system */
	int	semasiz;	/* size of system wide semaphore array */
	int	semopm;		/* maximum number of semaphores per call */
	int	semtmp;		/* size of semtmp structure */
	int	semmnu;		/* maximum undo structures per system*/
	int	semume;		/* maximum undo structures per process*/
	int	semusz;		/* size of undo structure */
	int	semusiz;	/* size of sem-undo array */
	int	nsdmamni;	/* number of sdma identifiers */
	int	sdmamni;	/* size of sdma identifiers structure */
	int	nsdmaseg;	/* max sdma seg attatches per process */
	int	sdmaseg;	/* size of sdma attach structures */
	int	sdmaall;	/* total amount of sdma allowed */
	int	sdmamax;	/* maximum size of any 1 sdma structure */
	int	cmapsiz;	/* estimated size of core map array */
	int	nflrec;		/* number of record locks */
	int	flrecsiz;	/* size of record lock structures */
	int	npool;		/* number of busnet packets */
	int	poolsiz;	/* size of busnet packet pool */
	int	shmmax;		/* shared memory maximum segment size */ 
	int	nshmmni;	/* # of shared memory identifiers */
	int	shmmni;		/* size of shmid_ds structure */
	int	nshmseg;	/* number of attaches per process */
	int	shmseg;		/* size of pmapinfo array */
	int	shmbrk;		/* shared memory break value in 4k pages*/
	int	nshmxat;	/* number of system wide attaches */
	int	shmxat;		/* size of mmu_attach structure */
	int	shmall;		/* total shared 4k memory pages in system */
	int	fslimit;	/* file size limit */
	int	ltick;		/* time slice length in ticks */
	int	maxup;		/* maximum processes per user */
	int	baltim;		/* load balancing time */
	int 	balmem;		/* load balancing memory */	
	int	kwclicks;	/* kernel virtual window size */
	int	umemsiz[MAXCPU]; /* estimated amount of user memory in clicks */
	int 	nctrl;		/* number of disk and tape controllers */
	int	nnupi;
	int	npsiz;		/* amount of memory for nupi structs */
	int	maptblsz;	/* size of map table requested by user */
	int	maptsiz;	/* size of memory for map table */
	int	nmaptbls;	/* number of map tables */
	int	nmapdev;	/* number of mapout devices */
	int	mapcntlsiz;	/* size of mapcntl structure */
	int	ncpu;
	int	nccb;
	int	nmsc;
	int	nram;
	int	mscsiz;		/* amount of memory for msc structus */
	int	cpuid;		/* our own cpuid */
	int	ec;		/* error code */
	int	deicod;		/* diagnostic engine error code */
	long	load_slot;	/* slot number of load source */
	long 	load_unit;	/* unit number of load source */ 
	long	conf_slot;	/* slot number of config band source */
	long	conf_unit;	/* unit number of config band source */
	long	defslot;	/* slot we were loaded from */
	long	defunit;	/* logical unit we were loaded from */
	char	*cbandptr;	/* pointer to config band if loaded */
	char	*cendptr;	/* pointer to first byte after config band */
	long	cmodlen;	/* length in bytes of config module */
	long	cmodoff;	/* offset in bytes of config module */
	struct cmodp *cmdptr;	/* index to config module overhead */
	unsigned long	uslot;	/* slot number of unix cpu zero */
	unsigned short slots;	/* 1 bit for each slot for unix to use */
	unsigned long rootslot;  /* slot for root device */
	unsigned long rootunit;	/* unit for root device */
	unsigned long rootslice; /* slice number for root device */
	unsigned long swapslot;  /* slot for swap device */
	unsigned long swapunit;	/* unit for swap device */
	unsigned long swapslice;/* slice number for swap device */
	unsigned long pipeslot;  /* slot for pipe device */
	unsigned long pipeunit;	/* unit for pipe device */
	unsigned long pipeslice;/* slice number for pipe device */
	long	noscndry;	/* 1 = do not boot secondaries */
	unsigned long confmem; 	/* size of mem for configurable data */
	unsigned long confsiz;  /* size of configurable data */
	unsigned long lodsrc[16]; /* converted load source units */
	unsigned long movdelta;	/* relocation distance */
	unsigned long rdsiz;	/* user specified size of ram disk in 1k bytes */
	unsigned long fmra;	/* file management read ahead size */
	unsigned long rdbcmem;	/* memory for ram disk and buffer cache */
	unsigned long rdbcL3s;	/* L3s for ram disk, buffer cache, and L3s */
	int	dist;		/* distribution for RAM disk and buffer cache */
	int	psiz;		/* process size limit in 4k pages */
	int	ssiz;		/* stack size limit in 4k pages */
	int	encore;		/* 1=enable core */
	struct	stbmdata2 *stbm2;/* Pointer to extension of stbmdata! */
	int	startvidx;	/* index into conftab of startv slot */
	int	shmallvidx;	/* index into conftab of shmallv slot */
};

/**********
*
*  The following structure exists because the previous structure(stbmdata)
*  became too big!. !*#@ pcc... 
*
***********/
struct stbmudata
{
	unsigned long highfree; /* max click number of physical mem */
	unsigned long lowfree;	/* first free virtual click number */
	unsigned long physmem;	/* number of clicks of local physical memory */
	char	*Uaddr;		/* physical address of user pages */
	int 	L1addr;		/* physical address of L1 table */
	long	pmmuflg;	/* pmmu flag 1=pmmu is present */
	unsigned long swapsize;	/* swap device size (in kbytes) */
	int	map4kpages;	/* number of kernel 4k map pages */
	long cmappages;		/* number of cmappages */
	long cmap4kmaps;	/* number of 4k pages to map cmap */
	long contdatapgs;       /* number of contiguous configurable data pages */
};
/**********
*
*  The following structure exists because the previous structure(stbmdata)
*  became too big again!  Don't want to use stbmudata because it is global
*  rather than on main's stack.
*
***********/
struct stbmdata2
{
	int	strnhsz;	/* streams net heap size */
	int	nstrnmap;	/* number of entries in strn_map array */
	int	strnmapsz;	/* streams net heap map size */
	int	nstrnlnk;	/* number of streams net links */
	int	strnlnsz;	/* streams net link count size */
	int	strnstsz;	/* streams net stat size 		*/
	int	nstrq;		/* number of streams queues 		*/
	int	strqsz;		/* size   of streams queues data structures */
	int	nstream;	/* number of streams 			*/
	int	streamsz;	/* size   of streams structures		*/
	int	nmuxlink;	/* number of mux links 			*/
	int	muxlsz;		/* size   of mux links structures	*/
	int	nstrevent;	/* number of streams events 		*/
	int	strevntsz;	/* size   of streams events structures	*/
	int	nmaxsepgnt;	/* number of extra event segments 	*/
	int	nstrpush;	/* number of pushed streams modules 	*/
	int	strmsgsz;	/* max message data size 		*/
	int	strctlsz;	/* max streams control size 		*/
	int	strlofrac;	/* low priority threshold 		*/
	int	strmedfrac;	/* med priority threshold		*/
	int	nblk4096;	/* number of 4096 byte blocks 		*/
	int	nblk2048;	/* number of 2048 byte blocks 		*/
	int	nblk1024;	/* number of 1024 byte blocks 		*/
	int	nblk512;	/* number of 512 byte blocks 		*/
	int	nblk256;	/* number of 256 byte blocks 		*/
	int	nblk128;	/* number of 128 byte blocks 		*/
	int	nblk64;		/* number of 64 byte blocks 		*/
	int	nblk16;		/* number of 16 byte blocks 		*/
	int	nblk4;		/* number of 4 byte blocks 		*/
	int	dblocksz;	/* size of all the mblk_t structs	*/
	int	mblocksz;	/* dblocksz + 25%			*/
	int	addonsiz;	/* size of add-on packages config. parms*/
	int	naddonp;	/* number of add-on parameters		*/
	int     addonphys;	/* physical address of addon parms pages*/
	int     nmblock;	/* number of entries in mblock[]	*/
	int     ndblock;	/* number of entries in dblock[]	*/
	struct	ramhunk ram[MAXLOCRAM + 1];
				/* physical memory map for 1507         */

};
/********
*
*  This structure contains info concerning ddr for monitor and key board
*
********/
struct ddrinfo
{
	int	mon_init;	/* 1 = monitor is initialized */
	int	mon_found;	/* 0 = no monitor */
	long	mon_slot;	/* slot number of monitor if it exists */
	long	mon_unit;	/* unit number of monitor if it exists */
	long	key_found;	/* 0 = no keyboard */
	long	key_slot;	/* slot number of keyboard if it exists */
	long    key_unit;	/* unit number of keyboard if it exists */
	long	key_init;	/* 1 = keyboard initialized */
	long    keytmo;		/* 1=keyboard has timed out (nobody home) */
};
/**********
*
*  The following structures define the configuration band overhead
*  information.  It is found in the beginning of a configuration band
*  and is used for verification.
*
*******/
/**
* the following structure provides information for finding and verifying
* specific configuration modules within the config band.
***/
#define CMODCNT 16
struct cmodp
{
	short offset;		/* offset in blocks from beginning of config
				   band for config module */
	short length;  		/* length in blocks of config module */
	long timeout;		/* log2 of boot time out in seconds; 0 means 
				   no time out */
	long count;		/* count of configuration entries */
	unsigned short crc;	/* crc of config module */
	unsigned short type;	/* board type of config module */
	unsigned short slots;	/* slots for which module is valid */
	unsigned short flags;	/* slots for slave device or processor */
	char reserved[12];	/* reserved for expansion */
};
#define FLG_SCNDRY 0x0001
#define FLG_SLV 0x0002
#define FLG_SHR 0x0008
#define MSK_NDX 0x00F0
#define SHF_NDX 4
struct cfgovhd
{
	char verify[4];		/* constand value for verification */ 
	unsigned short crcsum;	/* crc checksum */
	char gen[2];		/* generation in four bytes. currently 0 */
	char rev[2];		/* revision in four bytes. currently 1 */
				/* revisions within a generation MUST be
				   upwardly compatable */
	char comment[64];	/* user supplied comments */
	char reserved[438];	/* reserved for future use */
	struct cmodp cmodp[16]; /* 16 configuration module pointers */
};
/* number of bytes to crc in configuration band overhead */
#define OVHDCRC 1018 

/* This constant must reflect the exact number of configuration module entries*/
#define ENTCNT 83

/* This constant must reflect the number of blocks in a unix config module */
#define CONFSIZ 1

/* configuration module entry structure */
struct cfent
{
	char ent[32];
};
/*
*  the following structure describes verification functions and configuration
*  functions for each configuration modle entry.
*/
struct conftab
{
	int (*vfyfunc)();		/* config module entry verification */
	int (*conffunc)();		/* config module entry configuration */
};

/*
*
*  These are the error codes for the stbm command buffer from secondaries
*
*/
#define SCERR		1	/* initial message that says we are booting */
#define SBERR		2	/* initial message that says we are booting */
/******
*
*  This is where error codes for the STBM primitive live , error text that
*  corresponds to these codes are found in error.c
*
*******/
#define BOOTMSG		0	/* initial message that says we are booting */
#define DONEMSG		1	/* message that says we are done booting */
#define NOBOOT 		2	/* boot failed */
#define CONFERR		3	/* configuration error recovery begins */
#define NOCONF		4	/* Missing/invalid configuration information*/
#define BOOT2		5	/* message that says are booting secondaries */
#define DED_SCNDRY	6	/* message that says secondary not responding*/
#define NO_SCNDRY	7	/* no secondaries booted */
#define NOPTAB		8	/* unable to load partition table */
#define NOCBAND		9	/* unable to load configuration band */
#define DEI_1		10	/* device not ready */
#define DEI_2		11	/* device off line */
#define DEI_3		12	/* device error */
#define DEI_4		13	/* partition not found */
#define DEI_X		14	/* other device error */
#define INVCBAND	15	/* invalid configuration band */
#define OLDCBAND	16	/* out of date config band */
#define CORRUPTCB	17	/* config band contents are corrupted */
#define BADSLOT		18	/* slot specified is not valid */
#define NOTDSK		19	/* specified device is not a disk */
#define NOSLOTS		20	/* list available Nubus slots or type all */
#define MYSLOT		21	/* currently executing cpu slot not allowed */
#define ROOTPART	22	/* unable to verify root file system partition*/
#define SWAPPART	23	/* unable to verify swap partition */
#define PIPEPART	24	/* unable to verify pipe file system partition*/
#define BADPTAB		25	/* device has invalid partition table */
#define UNSPTDEVR	26	/* root file system device selection
				   unsupported*/
#define UNSPTDEVS	27	/* swap device selection unsupported */ 
#define UNSPTDEVP	28	/* pipe file system device selection
				   unsupported*/
#define INITROOT	29	/* cannot initialize root file system device */
#define INITSWAP	30	/* cannot initialize swap device */
#define INITPIPE	31	/* cannot initialize pipe file system device */
#define NODSK		32	/* no disk in configuration */
#define NO_CMOD		33	/* No configuration module for slot x */
#define INITLOAD	34	/* Unable to initialize load source interface.*/
#define INITUNIT	35	/* Unable to initialize load source unit */
#define NOLODS		36	/* Specified slot does is not a load source */
#define LODWHA		37	/* Loading xxxx from slot x unit x */
#define LODDEF		38	/* loading default from slot x unit x */
#define NOLPART		39	/* Unable to verify load partition */
#define LOADC		40	/* Loading config partition from slotx unit...*/
#define NOCPART		41	/* Unable to verify config partition */
#define INVPTAB		42	/* Invalid partition table */
#define NOPRIM		43	/* Primary reboot failed */
#define SECERR		44	/* Secondary processor boot failed */
#define NVINIT		45	/* initializing nvram in slot x */
#define NVUPDAT		46	/* update NVRAM? */
#define NVINVALID	47	/* invalid NVRAM in slot x */
#define NVDIFF		48	/* resources different from default */
#define NOTTAP		49	/* Specified slot does not contain tape */
#define INITDUMP	50	/* Unable to initialize dump device */
#define BADVALUE	51	/* Value specified not within allowable range*/
#define NO_SLAVES	52	/* Slave devices will not be booted */
#define SLVERR		53	/* Slave device error */
#define SLV2ERR		54	/* Slave device error, code = */
#define SLAVEBT		55	/* Slave device download start msg */
#define LODSERR		56	/* Error initializing load source */
#define SLVINIT		57	/* Slave device initialization error */
#define NOMEM		58	/* Out of physical memory */
#define SBUF		59	/* Not enough secondary memory for buffers */
#define SPBERR		60	/* Single processor boot only */
#define BADMEM		61	/* Too many parity errors */
#define SLV2BIG		62	/* partition too big */
#define SYSPAR		63	/* Parity error in system memory */
#define TOOMANY		64	/* Too many configurable parameters */
#define NOTECM		65      /* Not enough physically contiguous memory to boot*/
#define RELOCERR        66      /* Unix/Primitive too big. Can't relocate */

/*****
*
*  The following are indexes used for debug messages 
*
*******/
#define STBM_RELOC	0
#define STBM_SETVBR	1
#define STBM_SCAN    	2
#define STBM_NVRAMCK 	3
#define STBM_PREPCL  	4
#define STBM_PREPBS  	5
#define STBM_PREPSB  	6
#define STBM_PREPBM  	7
#define STBM_PREPAC  	8
#define STBM_PREPVM  	9
#define STBM_PREPVS  	10
#define STBM_PREPSTK 	11
#define STBM_PREPEU  	12
#define STBM_STBMBGN 	13
#define STBM_MOVADDR 	14
#define STBM_SWSTK   	15
#define STBM_ZERODEV 	16
#define STBM_TOUCHE  	17
#define STBM_TOUCH   	18
#define STBM_EMPTY   	19
#define STBM_CRCK	20
#define STBM_CROK	21
#define STBM_STF	22
#define STBM_CRFRMT  	23
#define STBM_NVRES   	24
#define STBM_VALIDNV 	25
#define STBM_NVPICK  	26
#define STBM_CBANDA  	27
#define STBM_PTLOAD  	28
#define STBM_NTRDY   	29
#define STBM_CBV	30
#define STBM_CENDP	31
#define STBM_NOTSLM	32
#define STBM_ISSLM	33
#define STBM_CKSIN	34
#define STBM_NOTSLS  	35
#define STBM_NOTSLH  	36
#define STBM_FNDSLM  	37
#define STBM_SLVLDA  	38
#define STBM_INITDEI 	39
#define STBM_RUNDEI  	40
#define STBM_SETSYNC 	41
#define STBM_BTPTA   	42
#define STBM_SECFND  	43
#define STBM_SECTYP  	44
#define STBM_POKESEC  	45
#define STBM_POKESEC2 	46
#define STBM_SECDON2  	47
#define STBM_BLDBUF   	48
#define STBM_SMSRCH   	49
#define STBM_SMSLT	50
#define STBM_SMENT	51
#define STBM_CMNONE	52
#define STBM_WEDIE	53
#define STBM_BTV	54
#define STBM_INITIF	55
#define STBM_DSTAT	56
#define STBM_INITU	57
#define STBM_RELNOW	58
#define STBM_INIREL	59
#define STBM_REENT	60
#define STBM_CMSRCH  	61
#define STBM_CMSLOT  	62
#define STBM_CMENT   	63
#define STBM_CMVF	64
#define STBM_BDCFENT	65
#define STBM_RSV	66
#define STBM_SWV	67
#define STBM_GETS	68
#define STBM_USES	69
#define STBM_CPID	70
#define STBM_CPU0	71
#define STBM_DCF	72
#define STBM_VFRU	73
#define STBM_VFSU	74
#define STBM_VRPN	75	
#define STBM_VSPN	76	
#define STBM_CPUFND	77	
#define STBM_CCBFND	78	
#define STBM_030FND     79
#define STBM_NPIFND	80	
#define STBM_MSCFND	81	
#define STBM_MEMFND	82	
#define STBM_RTDEV	83	
#define STBM_SWPDEV	84	
#define STBM_SWPSZ	85	
#define STBM_DMPSV	86	
#define STBM_DMPUV	87
#define STBM_CONS	88
#define STBM_PROCV	89
#define STBM_TXTV	90
#define STBM_FILEV	91
#define STBM_INODV	92
#define STBM_CALLO	93
#define STBM_MNTV	94
#define STBM_BUFV	95
#define STBM_SWPB	96
#define STBM_PBFV	97
#define STBM_HBUFV	98
#define STBM_SMAP	99
#define STBM_KMAP	100
#define STBM_FLREC	101
#define STBM_FLFIL	102
#define STBM_BNETV	103
#define STBM_SHSEG	104
#define STBM_SHMX	105
#define STBM_SHMNIV	106
#define STBM_SHMALL	107
#define STBM_SHBRK	108
#define STBM_MSGSZ	109
#define STBM_MSGMP	110
#define STBM_MSMNI	111
#define STBM_MSGMN	112
#define STBM_MSGTQL	113
#define STBM_MSGMX	114
#define STBM_SEMMNI	115
#define STBM_SEMMSL	116
#define STBM_SEMMNS	117
#define STBM_SEMOPM	118
#define STBM_SEMMNU	119
#define STBM_SEMUME	120
#define STBM_SDMAMNI	121
#define STBM_SDMASEG	122
#define STBM_FSLMT	123
#define STBM_PUPLV	124
#define STBM_LTKV	125
#define STBM_LTIMV	126
#define STBM_LMEMV	127
#define STBM_SMEM	128
#define STBM_KVWSZ	129
#define STBM_MAPTV	130
#define STBM_NMAPTV	131
#define STBM_NMAPDV	132
#define STBM_CDATP	133
#define STBM_MPGS	134
#define STBM_L1ADR	135
#define STBM_DL3ADR	136
#define STBM_UL3ADR	137
#define STBM_UADDR	138
#define STBM_MAPC	139
#define STBM_STKC	140
#define STBM_TL1ADDR	141
#define STBM_TKENT	142
#define STBM_KSTK	143
#define STBM_RAMD	144
#define STBM_FMRA	145
#define STBM_TRACE	146
#define STBM_AVMEM	147
#define STBM_CFMEM	148
#define STBM_KWCLK	149
#define STBM_PMEM	150
#define STBM_LFREE	151
#define STBM_HFREE	152
#define STBM_CMAPA	153
#define STBM_KL3	154
#define STBM_CDL3	155
#define STBM_USIZL3	156
#define STBM_CPULOCL3	157
#define STBM_RDBCMEM	158
#define STBM_CPUMEM	159
#define STBM_DIST	160
#define STBM_SSIZ	161
#define STBM_PSIZ	162
#define STBM_ENCORE	163
#define STBM_RDTOT	164
#define STBM_RBTOT	165
#define STBM_BCTOT	166
#define STBM_CPUN	167
#define STBM_RDLOC	168
#define STBM_RBLOC	169
#define STBM_BCLOC	170
#define STBM_NP2FND	171
#define STBM_NVBLOCK	172
#define STBM_NVTYP	173
#define STBM_NVLEN	174
#define STBM_STRNHSV	175
#define STBM_STRNLNKV	176
#define STBM_STRQUEV	177
#define STBM_STREAMV	178
#define STBM_MUXLV	179
#define STBM_STREVNTV	180
#define STBM_MAXSEPV	181
#define STBM_STRPUSHV	182
#define STBM_STRMSGSZV	183
#define STBM_STRCSZV	184
#define STBM_STRLOV	185
#define STBM_STRMED	186
#define STBM_4096V	187
#define STBM_2048V	188
#define STBM_1024V	189
#define STBM_512V	190
#define STBM_256V	191
#define STBM_128V	192
#define STBM_64V	193
#define STBM_16V	194
#define STBM_4V		195
#define STBM_PIPV	196
#define STBM_VFPU	197
#define STBM_VPPN	198
#define STBM_PIPEDEV	199	
#define STBM_1507FND	200	
#endif SCCSID    

/* Page tables count for STBM */

#define KERNEL_L2s   1    /* Number of L2 page tables for kernel*/
#define PHYS_L2s     1    /* Number of L2 page tables for phys addr kernel*/
#define KVWS_L2s     1    /* Number of L2 page tables for kvw*/
#define RDBC_L2s     4    /* Number of L2 page tables for buffer cache and 
			   * ram disk */ 
#define UPAGES_L3s   1    /* Number of L3 page tables for upages, CPU local 
			   * page etc */

/* address in Unix band to word that points to devmap address */
#define UNIX_DEVMAP_PTR 0x410


#define NCLICK_PER_L1_ENTRY 8192 /* 8192 4k clicks are mapped by 1 L1 entry */

#define CTOMEGSHIFT 8            /* clicks to meg shift */

/* returns the # of 4k pages needed for all the l3 page tables
 * for number of pages given.  1 4k page can contain 16 l3 page tables
*/
#define ctol3pages(clicks) (((clicks) + MAXL3PTEPG - 1)/MAXL3PTEPG)

/* returns the # of l3 page tables needed to map in the number of 
 * clicks given
*/
#define ctol3pt(clicks) (((clicks) - 1)/NPTESL3PT + 1)

/* changes a number of clicks and returns the number of l3 page tables 
 * that will fit in it. 
*/
#define l3pagestol3pt(l3pages) ((l3pages) * NL3PTPC)

/* changes the number of l3 page tables into minimun number of clicks 
 * it would take to contain them.
*/ 
#define l3pttol3pages(l3pts)  (((l3pts) + NL3PTPC - 1) / NL3PTPC)


