/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char enc_h[] = "@(#)enc.h	1.3 (TI) 86/02/04";
#endif	SCCSID

typedef short offset;
/* 
 * Enet defines 
 */
#define EADDR		6
#define EHDRSZ 		sizeof(struct Ehead)
#define EMAXPKT		1514		/* Max size of Ethernet pkts */
#define EMINPKT		64		/* Min size of Ethernet pkts */
#define EMAXDATA	EMAXPKT - EHDRSZ
#define EMINDATA	EMINPKT - EHDRSZ
/* 
 * A couple of UNET error codes 
 * This should agree with the UNET include file unetio.h
 */
#define	EBASE		64
#define EDATA2BIG	12 + EBASE
#define ENETDOWN	17 + EBASE
/* 
 * Defines for waits 
 */
#define ENCRSTWT	5		/* time to wait for reset if alloc */
#define ENCPRI		PZERO + 1
/* 
 * Various Protocol defines
 */
#define MAXPROTO	6		/* Maximum number of protocols */
#define PROTO0		0		/* Protocol 0 is UNET */
#define PROTO1		1		/* Protocol 1 is EtherSeries */
#define PROTO2		2		/* Spare protocol 1 */
#define PROTO3		3		/* Spare protocol 2 */
#define PROTO4		4		/* Spare protocol 3 */
#define PROTO5		5		/* Spare protocol 4 */
#define IPPROTO		0x0800		/* Unet protocol */
#define VALIDP		1		/* Flag to mark valid proto */
#define RAWUSER		0		/* Rawuser without ES raw devices */
#define NUMDEVS		1		/* Number of raw devices per bd */
#define NUMSYSPROTO	1
/* 
 * Values for encflag 
 * bits 0-3		debug flags
 * bits 4-7		board state flags
 * bits 8-11		interrupt warning flags
 */
#define TRACE		0x1
#define INFORM		0x2
#define TRANS		0x4
#define RECEIVE		0x8
#define RESET		0x10		/* Board is reset */
#define ALLOCATE	0x20		/* Allocated map area */
#define CMDBSY		0x40		/* Command Unit busy */
#define NOSLEEP		0x200		/* No sleep in interrupt code */
#define RAWOPEN		0x10000		/* A user on the raw device */
#define IPOPEN		0x20000		/* A user of IP present */
#define ENCDEBUG	0x0000000f	/* Get noise from encflag */
/* 
 * Flags for cflg for cmdproc 
 */
#define IP		0x100		/* Designate IP user on transmit */
#define CONFIG		0x200		/* Set default cfg attributes or not */
/* 
 * IOCTL commands 
 */
#define EIOCADD		(('E' << 8) | 0x01)	/* returns host's enet addr  */
#define EIOCSTZ		(('E' << 8) | 0x03)	/* report system stats       */
#define EIOCRESET	(('E' << 8) | 0x05)	/* reset board	             */
#define EIOCSTATE	(('E' << 8) | 0x07)	/* returns host's state      */
#define EIOCNOISE	(('E' << 8) | 0x08)	/* reports debug decibels    */
#define EIOCNSET	(('E' << 8) | 0x09)	/* sets debug decibels       */
#define EIOCNEWP	(('E' << 8) | 0x0c)	/* install new user proto    */
#define EIOCREMP	(('E' << 8) | 0x0d)	/* remove user protocol      */
#define EIOCNADD	(('E' << 8) | 0x0e)	/* change ethernet addr      */
#define EIOCOADD	(('E' << 8) | 0x0f)	/* reset orig ethernet addr  */
#define EIOCCFG		(('E' << 8) | 0x20)	/* modify board configuration*/
#define EIOCMADD	(('E' << 8) | 0x21)	/* multicast address addition*/
#define EIOCMREM	(('E' << 8) | 0x22)	/* multicast address removal */
#define EIOCDMP		(('E' << 8) | 0x23)	/* dmp board                 */
#define EIOCTDR		(('E' << 8) | 0x24)	/* TDR test on board         */
#define EIOCDIAG	(('E' << 8) | 0x25)	/* Run on board diagnostics  */
/* 
 * Miscellaneous Values 
 */
#define BOARDSZ		32		/* # of memory clicks on board */
#define NRFDS		15		/* # of buffer descriptors */
#define NBUFS32		19		/* # of data buffers for 32k bd */
#define BUFSIZE		1514		/* Size of data buffers */
#define CFGSIZ		12		/* # of bytes in the cfg cmd */
#define DMPSIZ		170		/* Buf size of dmp command */
#define BUFNULL		-1		/* CPU EOL flag */
#define MAXMULTI	4		/* Max # of multicast addr */
#define UNITS		2		/* Max # of boards in system */
#define MAXWAITING	5		/* Max pkts waiting on a device list */
#define CUSTAT		0x000f		/* Get status of CU from scb status */
#define RUSTAT		0xf000		/* Get status of RU from scb status */
#define NUMTBD		2		/* Number of tbd's */
#define NORMAL		0		/* Normal transmit header */
#define AUX		1		/* Aux transmit header for isend */

/* 
 * Control registers 
 */
#define ENCCAADDR	0x8000		/* Offset of channel attn */
#define ENCEADDR	0xA000		/* Offset of event addr reg */
#define ENCCFREG	0xC000		/* Offset of the config reg */
#define ENCFLREG	0xC002		/* Offset of the flag reg */
#define ENCCFROM	0xE000		/* Offset of the config rom */
#define ENCID		0xFFFEE0	/* Offset of unique enet id */
/* 
 * Values from here will be byte swapped. BIG and LITTLE ENDIAN WARS 
 */
/* 
 * Configuration register flags 
 */
#define LOOPBACK	0x0001		/* 501 loopback mode */
#define FAULTLED	0x0400		/* Fault LED */
#define ENCENBM		0x0200		/* Enable bus master */
#define ENCRESET 	0x0100		/* Reset the board */
#define MEM32		0x0008		/* Is board 32k */
/* 
 * System Configuration Pointer 
 */
struct scp
{
	short	sysbus;
	long	scpfiller;
	long	iscpaddr;
};
/* 
 * Intermediate System Configuration Pointer 
 */
/* Flags */
#define BUSY		0x0100		/* Initialization busy */
#define EIGHT		0x0100		/* 8 bit wide system bus */
#define SIXTEEN		0x0		/* 16 bit wide system bus */

struct iscp
{
	short busy;
	offset scboff;
	long scbbase;
};

/* 
 * System Control Block 
 */
/* Receive Unit Status */
#define RIDLE		0x0		/* Idle */
#define RSUSPEND	0x1000		/* Suspended */
#define RNORES		0x2000		/* No Resources */
#define RREADY		0x4000		/* Ready */
#define RUSTAT		0xf000		/* Get status of RU from scb status */

/* Command Unit Status */
#define CIDLE		0x0		/* Idle */
#define CSUSPEND	0x0001		/* Suspended */
#define	CACTIVE		0x0002		/* Ready */
#define CUSTAT		0x000f		/* Get status of CU from scb status */

/* Status bits */
#define RNR		0x0010		/* Receive unit became not ready */
#define CNR		0x0020		/* Command unit became not ready */
#define FR		0x0040		/* Frame has been received */
#define CX		0x0080		/* Executed command with 'I' set */
#define INTMASK		0x00f0		/* Get type of interrupt */

/* Receive Unit Commands */
#define RNOP		0x0		/* Doesn't alter unit's current state */
#define RSTART		0x1000		/* Start frame reception */
#define RRESUME		0x2000		/* Resume frame reception */
#define RSUSP		0x3000		/* Suspend frame receiving */
#define RABORT		0x4000		/* Abort receiver operation now */
#define RST		0x8000		/* Reset the board */

/* Command Unit Commands */
#define CNOP		0x0		/* Doesn't alter unit's current state */
#define CSTART		0x0001		/* Start executing first CBL command */
#define CRESUME		0x0002		/* Resume operation of command unit */
#define CSUS		0x0003		/* Suspend exection of CBL commands */
#define CABORT		0x0004		/* Abort current command now */

struct scb
{
	short status;
	short command;
	offset cbloff;
	offset rfaoff;
	short crcerr;
	short alnerr;
	short rscerr;
	short ovrnerr;
};

/* 
 * Command Blocks 
 *
 * Flags common to command block headers
 */

/* Status */
#define COMPLETE	0x0080		/* Command has been executed */
#define BSY		0x0040		/* Command currently being executed */
#define NOERR		0x0020		/* Command completed without error */
#define ABORT		0x0010		/* Terminated due to CU Abort command */

/* Command */
#define ENDLIST		0x0080		/* Indicates last CB for CBL */
#define SUSPEND		0x0040		/* Suspend the Command Unit */
#define INTR		0x0020		/* Interrupt after command completion */

/* 
 * Command block header 
 */
struct cbh
{
	short stat;
	short cmd;
	offset link;
};

/* 
 * Nop command 
 */
#define CNOP		0x0		/* No action taken cmd */

/* 
 * Individual Address setup command 
 */
#define CINDADR		0x0100		/* Individual addr setup cmd */

struct indaddr
{
	char indaddr[EADDR];		/* Individual address set up */
};

/* 
 * Configuration Command 
 */
#define CCFG		0x0200		/* Configure cmd */

/* For flag1[0] */
#define SRDY	0x40		/* SRDY/ARDY operates as SRDY */
#define SAVBF	0x80		/* Bad frames saved in memory */

/* For flag1[1] */
#define ACLOC	0x08		/* Addr and type part of buffers */
#define PMBL2	0x00		/* 2-byte preamble */
#define PMBL4	0x10		/* 4-byte preamble */
#define PMBL8	0x20		/* 8-byte preamble */
#define PMBL16	0x30		/* 16-byte preamble */
#define ILOOP	0x40		/* Internal loopback */
#define ELOOP	0x80		/* External loopback */
#define ILOP2	0xC0		/* bit 6 & 7 on:  internal loopback */

/* For flags1[2] */
#define BCKOF	0x80		/* Exponential Backoff Method */

/* For flags2[0] */
#define PROM	0x01		/* Promiscuous Mode */
#define BCDIS	0x02		/* Broadcast frames rejected */
#define MANCH	0x04		/* Manchester encoding/decoding */
#define TONOCS	0x08		/* Continue transmit on no 
					   carrier sense */
#define NCRC	0x10		/* Turn off CRC */
#define CRC	0x20		/* 16 bit CCITT CRC polynomial */
#define BTSTF	0x40		/* HDLC like Bitstuffing mode */
#define PAD	0x80		/* Perform padding */

/* For flags2[1] */
#define CSSRC	0x08		/* Carrier sense signal internally 
					   generated */
#define CDSRC	0x80		/* Collision detect signal internally
					   generated */

struct cfg
{
	char bytecnt;			/* # of bytes holding config params */
	char fifolmt;			/* FIFO LIMIT value */
	char flags1[3];			/* holds flags1 bytes 3, 4, 5 */
	char interfrsp;			/* interframe spacing */
	char slots[2];			/* slot time and # of retries */
	char flags2[2];			/* holds flags2 bytes 9 and 10 */
	char minfrlen;			/* minimum frame length */
	char filler;
};

/* 
 * Multicast Address setup command 
 */
#define CMULADR		0x0300		/* Multicast addr setup cmd */

struct multi
{
	short muadrcnt;			/* # of multicast addresses */
	char muaddrs[MAXMULTI][EADDR];	/* multicast address */
};

/*
 * Transmit command 
 */
#define CTRANS		0x0400		/* Transmit cmd */
/*
 * Relavent statuses to transmit found in cbh.stat 
 */
#define TMC		0x2000		/* Too many collisions */		
#define HB		0x4000		/* Heart-Beat during interframe 
					   spacing (monitor collision detect) */
#define TRNDFRD		0x8000		/* Transmission deferred */
#define DMAUNDER	0x0001		/* DMA underrun */
#define NOCTS		0x0002		/* Trans halted due to loss of 
					   Clear To Send */
#define NCS		0x0004		/* No Carrier Sense during trans */
#define TDBEOF		0x0080		/* Mark for last buffer to trans */

struct trans
{
	offset tdbptr;			/* offset of transmit buf descriptor */
	char destaddr[EADDR];		/* destination address */
	short proto;			/* type field */
};

/* 
 * Time Domain Reflectometer test command 
 */
#define CTDR		0x0500		/* TDR cmd */

/* flags for tdr */
#define SRTETH		0x1000		/* Short on the Ethernet link
					   identified */
#define OPNETH		0x2000		/* Open on the Ethernet link 
					   identified */
#define TRLNKPRB	0x4000		/* Transceiver Link Problem */
#define LNKOK		0x8000		/* No link Problems */
#define NOECHO		0xff07		/* No echo observed */

struct tdr
{
	short tdr;
};

/*
 * Dump Status command 
 */
#define CDMPSTAT	0x0600		/* Dump Status cmd */

struct dmp
{
	offset dmpptr;
};

/*
 * Diagnose command 
 */
#define CDIAG		0x0700		/* Diagnose cmd */
#define FAIL		0x0008		/* Relevant status field from cbh */
/*
 * Receive Frame Descriptor 
 */
/* RFD status flags and masks */
#define FD_COMPLETE	0x0080		/* Receive complete */
#define FD_BUSY		0x0040		/* FD consumed by RU */
#define FD_OK		0x0020		/* OK all others reset if on */
#define FD_CRCERR	0x0008		/* CRC error */
#define FD_ALIGN	0x0004		/* Alignment error */
#define FD_NRESOURCE	0x0002		/* Ran out of resources*/
#define FD_OVERRUN	0x0001		/* DMA overrun */
#define FD_RUNTPKT	0x8000		/* runt packet */
#define FD_NOEOF	0x4000		/* No EOF detected */

/* RFD flags */
#define FD_ELIST	0x0080		/* last rfd */
#define FD_SUSPEND	0x0040		/* suspend unit */

struct rfd
{
	short status;
	short flags;
	offset rfdptr;			/* offset of next Rec Frame Desc */
	offset rbpptr;			/* offset of Rec Buffer Desc */
	char dest[EADDR];
	char src[EADDR];
	short proto;
};
/*
 * Receive Buffer Descriptor 
 */
/* RBD flags and masks */
#define RBD_EOF		0x0080			/* last rbd of reception */
#define RBD_VALID	0x0040			/* valid count field */
#define RBD_ELIST	0x0080			/* last rbd */
#define RBD_CNT		0xff3f			/* data buf size */

struct rbd
{
	short actcnt;
	offset rdpptr;			/* offset of next Rec Buf Desc */
	long buf;
	short size;
};
/*
 * Transmit buffer descriptor 
 */
struct tbd
{
	short actcnt;
	offset tdbptr;			/* offset of next Trans Buf Desc */
	long buf;
};
/* 
 * Struct for isend cases of IP
 */
struct aux
{
	short stat;
	short cmd;
	offset link;
	offset tdbptr;			/* offset of transmit buf descriptor */
	char destaddr[EADDR];		/* destination address */
	short proto;			/* type field */
};
/* 
 * memory map of the onboard ram 
 */
struct buffer
{
	struct iscp iscp;
	struct scb scb;
	struct cbh cbh;			/* Command Block header */
	union				/* parameters to the command blks */
	{
		struct indaddr indaddr;
		struct cfg cfg;
		struct multi multi;
		struct trans trans;
		struct tdr tdr;
		struct dmp dmp;
	}cb;
	struct  aux auxtrans;
	struct	rfd rfd[NRFDS];
	struct	tbd tbd[NUMTBD];
	char 	tbdbuf[NUMTBD][EMAXPKT];
	char	dbuf[DMPSIZ];
	struct  rbd rbd[NBUFS32];
	char	bufs[NBUFS32][BUFSIZE];
};
/* 
 * Struct for device pointers 
 */
struct bfmgr
{
	struct rfd *ptr;
	int count;
};
/*
 * Struct to hold various ptrs 
 */
struct encptrs
{
	int *encCA;		/* ptr to Channel Attention register */
	long *encEV;		/* ptr to Event Address register */
	int *encFL;		/* ptr to Flag register */
	short *encCF;		/* ptr to Configuration register */
	char *encID;		/* ptr to Unique Enet Id */
	struct rfd *RDL_begin;	/* ptr to head of free frame list */
	struct rfd *RDL_end;	/* ptr to end of free frame list */
	struct rbd *FBL_begin;	/* ptr to head of free buffer list */
	struct rbd *FBL_end;	/* ptr to end of free buffer list */
	struct buffer *encbf;	/* ptr to on board ram */
};
/* 
 * Macro Mania 
 */
#define SPL()		spl4()
#define BOARD(x)	((minor(x) >> 4) & 0x0ff)
#define DEVICE(x)	(minor(x) & 0x0f)
#define off_ptr(encp, x) ((char *) (encp)->encbf + (int) (sswap(x) & 0xffff))
#define ptr_off(encp, x) sswap((int) (x) - (int) (encp)->encbf)
#define ADDR_EQ(a1, a2)	(*a1 == *a2 && (*(a1+1) == *(a2+1)) && \
			(*(a1+2) == *(a2+2)) && (*(a1+3) == *(a2+3)) && \
			(*(a1+4) == *(a2+4)) && (*(a1+5) == *(a2+5)))
/* 
 * Ethernet header 
 */
struct Ehead
{
	char dest[EADDR];
	char src[EADDR];
	short proto;
};
/*
 * Struct to hold IP specific stuff
 */
struct ip
{
	int (*rcv)();
	int (*win)();
	dev_t dev;
	char *buf;
};
/*
 * Struct to hold protocol list information on user defined protocols
 */
struct valproto
{
	short proto;
	short val;
	struct proc *u_procp;
	struct rfd *rfdptr;
	int count;
};
/*
 * the first 14 fields in statz are dictated by eseries
 * on board counters follow
 */
struct	statz			/* keep stats (mainly for ES)		*/
{
	long	reset;		/* Is board reset?			*/
	long	rcnt;		/* receive packet count			*/
	long	rboth;		/* IGNORED				*/
	long	xcnt;		/* count buffers transmitted		*/
	long	jams;		/* IGNORED 				*/
	short	crcerr;		/* # of aligned pkt w/ crc errors	*/
	short	alnerr;		/* # of misaligned pkt w/ crc errors	*/
	short	rscerr;		/* # of lost pkts to RU not ready	*/
	short	ovrnerr;	/* # of overrun errors			*/
	short   junk[4];	/* Take up some space here              */
};
/*
 *  Decls for Global pointers 
 */
extern struct Ehead Ehead[UNITS];
extern struct bfmgr bfmgr[UNITS][NUMDEVS];/* ptrs to device buffer lists */
extern struct valproto vp[UNITS][MAXPROTO];/* ptrs to proto buffer lists */
extern struct encptrs ep[UNITS];
extern int encflag[UNITS];
extern struct statz statz[UNITS];
