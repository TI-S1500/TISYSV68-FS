/************************************************************************/
/* 	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1984.  ALL	*/
/*	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.	*/
/*	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT	*/
/*	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND	*/
/*	ASSOCIATED DOCUMENTATION.					*/
/************************************************************************/

#ifndef _SYS_BUSNET_H
#define	_SYS_BUSNET_H

#ifdef	SCCSID
static char busnet_h[] = "@(#)busnet.h	1.36 (TI) 90/09/13";
#endif	SCCSID

#ifdef __STDC__
#define VOLATILE volatile
#else
#define VOLATILE
#endif

/************************************************************************/
/*									*/
/*	Revision	System V		Programer: Don Capps	*/
/*	Date:		06/12/1989					*/
/*									*/
/************************************************************************/

/*----------------------------------------------------------------------*/
/* BusNet Opcodes							*/
/*----------------------------------------------------------------------*/

#define WR_TE   	0		/* Write opcode 		*/
#define RE_AD   	1		/* Read Opcode 			*/
#define IO_CTLL 	2		/* Ioctl Opcode			*/
#define OP_EN   	3		/* Open Opcode			*/
#define CL_OSE  	4		/* Close Opcode			*/
#define AB_ORT  	5	 	/* Abort Opcode	specific dev	*/
#define AD_VAN  	6 		/* Advanced io Opcode		*/
#define FREE_ONLY  	7 		/* Open Opcode			*/
#define PACKFAIL	8		/* Bus_net Packet Failure	*/
#define DIS_CON		9		/* Bus_net Disconnect 		*/

/*----------------------------------------------------------------------*/
/* Done flag encodings							*/
/*----------------------------------------------------------------------*/
#define KNETIO	0x40		/* indicates Kernel mode I/O  operation */
#define BNHUP	0x80		/* Indicates Busnet should send SIGHUP	*/
#define BNDON	0x1		/* Indicates I/O is completed		*/
#define PAR_ERR 0x10		/* Indicates parity error */

/*----------------------------------------------------------------------*/
/* Error message numbers for internal Bus_Net errors .			*/
/*----------------------------------------------------------------------*/
#define MSG1		1
#define MSG2		2
#define MSG3		3
#define MSG4		4

/*----------------------------------------------------------------------*/
/* Definitions of items in the BusNet 					*/
/*----------------------------------------------------------------------*/

extern int maxque, maxlele, lwindow;

#define NSPACE  	84		/* Space in element 		*/
#define MAXQUE  	maxque		/* Number of global elements 	*/
#define MAXLELE  	maxlele 	/* Number of Local elements 	*/
#define MAXTBL  	4 		/* Number of pages to send 	*/
#define LWINSIZE	30		/* size of local virtual window */
#define LWINDOW  	lwindow		/* Number of kernel virtual pte's */
#define TBLSIZE		256   		/* Request table size 		*/
#define NUSLOT		16   		/* Slots in the Nubus 		*/
#define RETRY  		50		/* Number of RETRYS on tas 	*/
#define UNLK		0x00FFFFFF	/* unlock a queue header 	*/
#define HIGHWATER	1		/* Number of Pkts/write imm  	*/
#define MAXDEV  	256		/* Max devices count		*/
#define MAXTTY  	128		/* Max terminal count		*/
#define TTYPOS  	1		/* Offset into totdev		*/
#define NBPQ 		0x400		/* Bytes per quark 		*/

/*----------------------------------------------------------------------*/
#define BNTYPE0 0			/* Type field in busnet gram */
#define BNTYPE1 1
/*----------------------------------------------------------------------*/

/*----------------------------------------------------------------------*/
/* Special commands for the field edit mode 				*/
/*----------------------------------------------------------------------*/
#define FEDITSETA	(('g'<<8)| 1) 
#define FEDITGETA	(('g'<<8)| 2)
#define EXT_READ	FEDITGETA	/* Extended read command */
#define EXT_WRITE	FEDITSETA	/* Extended write command */


/*----------------------------------------------------------------------*/
/* Definition of the ioctl structure used by BusNet			*/
/*----------------------------------------------------------------------*/
struct ciocsw{
	int	(*d_ioctl)();
	int	d_wrtlim;
};

/*----------------------------------------------------------------------*/
/* Definitions of the queue headers in the BusNet			*/
/*----------------------------------------------------------------------*/
struct lword{		/* definition of the lock word */
	VOLATILE unsigned char	lockb;
	VOLATILE unsigned char	collc;
	VOLATILE unsigned short	qlen;
	};

union locki{		/* This forces long word alignment in   */
			/* queheads 				*/
	VOLATILE long	lock1;
	struct lword lock2;
	};

struct quehead {	/* This is the structure of a queue header. 	*/
	union locki lock;
	VOLATILE long  head;	/* Pointer to head of queue 		*/
	VOLATILE long  tail;	/* Pointer to tail of queue 		*/
	VOLATILE long  event;	/* Comm board event address for this queue */
	};

/*----------------------------------------------------------------------*/
/* Definition of the request queue header  map 				*/
/*----------------------------------------------------------------------*/

struct krquehead{
	struct quehead header[TBLSIZE+NUSLOT+1];
	};

/*----------------------------------------------------------------------*/
/* Definition of the 'address','length' pairs				*/
/*----------------------------------------------------------------------*/

struct pair{			/* pair for user data buffer 		*/
	long	nu_add;		/* Nu-bus address of data 		*/
	long 	nu_len;		/* Length of request 			*/
	};

/*----------------------------------------------------------------------*/
/* Definition of the User table	in the element				*/
/*----------------------------------------------------------------------*/

struct U_table{			/* Table of user areas and lengths */
	struct pair nu_set[MAXTBL];
	};
/*----------------------------------------------------------------------*/
/* Definition of bsema_t type.  MUST MATCH sema_t TYPE IN SYS/TYPES.H   */
/*----------------------------------------------------------------------*/

typedef struct {
	VOLATILE short	lck;	/* used to lock semaphore code for this */
				/* second half of lck contains cpuid */
	VOLATILE short	val;	/* value of sema, > 0 avail, < 1 locked */
	VOLATILE struct	proc  *head;
	VOLATILE struct	proc  *tail;
	VOLATILE short	pid;	/* pid of last person to get semaphore */
	VOLATILE short	pvl;		
}	bsema_t;

/*----------------------------------------------------------------------*/
/* Definition of the BusNet element 					*/
/*----------------------------------------------------------------------*/

struct element {  /* This is the structure of a queue element 		*/
	long 	fwdpt;		/* nu-bus forward pointer		*/
	long	owner;		/* owner of this element		*/
	long 	type;		/* Type number 				*/
	struct 	U_table nu_table;  /* user data table 			*/
	long 	wake;		/* wakeup address 			*/
	long	io_arg;	    	/* addr field in io_ctl			*/
	long	io_flags;       /* flags field in io_ctl		*/
	long	totlen;		/* total length in this request 	*/
	long	spins;		/* spin  sema in this request 		*/
	long	spare;		/* spare  long in this request 		*/
	unsigned long	dev;	/* Device number pair 			*/
	long	ptblptr;	/* pointer to process table entry	*/
	long	socknum;	/* Socket number for Sockets		*/
	int	rval1;		/* reserved for later use       	*/
	int	rval2;		/* reserved for later use       	*/
	short	contflg;	/* Continuation flag 			*/
	short	splen;		/* length of space to copy		*/
	short 	opcode;		/* opcode to indicate action 		*/
	short 	length;		/* length of request 			*/
	short 	processor;	/* processor number			*/
	short 	uid;		/* User ID 				*/
	short 	gid;		/* Group ID 				*/
	short 	pid;		/* Process ID 				*/
	short  	io_com;		/* Sub op for Ioctl 			*/
	short  	eflag; 		/* Errors returned in queueing  	*/
	short	rawch;		/* system accounting information 	*/
	short	outch;		/* system accounting information 	*/
	short	canch;		/* system accounting information 	*/
	short	rcvint;		/* system accounting information 	*/
	short	xmtint;		/* system accounting information 	*/
	short	done;		/* done used to indicate complete 	*/
       	char	space[NSPACE];	/* interchangable area   	 	*/
	bsema_t	psema;
	long	sparel;
};

/*----------------------------------------------------------------------*/
/* Definition of the unanticipated I/O element space area 		*/
/*----------------------------------------------------------------------*/

struct advel{
	long	errno;			/* Error number			*/
	long	narg;			/* Error Number of args to log	*/
	long	arg[8];			/* args to log			*/
	char	rqsig;			/* requested signal to process  */
	char	gopsig;			/* group or individual process  */
	};	

/*----------------------------------------------------------------------*/
/* System information on the unanticipated I/O 				*/
/*----------------------------------------------------------------------*/


#ifdef KERNEL
long syscomd;
long sysclen;
#endif KERNEL

#endif _SYS_BUSNET_H
