/*
 	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1989.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/
/* @(#)strnet.h	1.14 91/04/10 */



#define  TRUE      1
#define  FALSE     0
#define  PDEBUG   if (gSTRNdebug) printf

/*************************************************************
*         STREAMS/CCB interface driver operations            *
*************************************************************/

#define  STRNOPEN   	0
#define  STRNOUTBOUND   1       
#define  STRNINBOUND    2
#define  STRNADDINQ     3
#define  STRNCLOSE      4
#define  STRNPANIC      5
#define  STRNPARERR	6

/*
*  stat code in the strn_head stat field
*/
#define  STRN_END_LIST  1
#define  STRN_FREE      2

struct  strn_OPEN  {
  struct  strnet_head   sh;
  struct  strn_head     dh;     
  long    hold;                /* max. # of inbound msg hold on CCB */
  unsigned long   outqfp;      /* Nu addr of the outqfirst in link  */
  unsigned long   exc_elem;    /* Nu addr of the exceptional strnet element */
};

struct  strn_INOUT  {
  struct  strnet_head   sh;
  struct  strn_head     dh;     
  struct  strnet_head   *intrn_next;
  long    strnmp;     	 	/* pointer to msg block. type mblk_t */
  long    total_len;
  long    msg_type;             /* message type */
  long    strn_qtype;           /* strn inbound queue type */
};

struct  strn_ADDINQ  {
  struct  strnet_head   sh;
  struct  strn_head     dh;     
  unsigned long    inqfirst;    /* pointer to the inbound queue */
  unsigned long    inqfp;       /* Nu addr of the medq/hiqfirst in the link */
  unsigned long    inqtype;     /* queue type */
};

struct  strn_EXC  {             /* exceptional element header */
  struct  strnet_head   sh;
  struct  strn_head     dh;     
};

#define  STRN_CCB_CHN   0            /* channel id on CCB */
#define  STRN_CCB_HOLD  20           /* # of packets that CCB would hold */
#define  STRN_SMQMSG_SIZE  128       /* msg size for the small inq buffers */
#define  STRN_LGQMSG_SIZE  2048      /* msg size for the large inq buffers */

/*
*  host inbound queue types
*/
#define  SMINQTYPE     1
#define  LGINQTYPE     2

/*
*   flags
*/
#define   STRN_SMINQ_INITED  0x00000001
#define   STRN_LGINQ_INITED  0x00000002
#define   STRN_TOUT_STARTED  0x00000004
#define   STRN_CCB_OPENED    0x00000008
#define   STRN_M_ERROR       0x00000010
#define   STRN_CLOSED        0x00000020
#define   STRN_PANICED       0x00000040
#define   STRN_REINIT        0x00000080
#define   STRN_WQ            0x00000100
#define   STRN_INUSE	     0x00000200
#define   STRN_CTLOUT	     0x00000400
#define   STRN_POLLING	     0x00000800
#define   STRN_CLEAN	     0x00001000


struct  strn_link  {
  int   dev_num;	  /* actual dev number to board */
  int   handle;           /* handle for CCB */
  long  qptr;		  /* pointer to read queue (queue_t)  */
  unsigned long   flags;        
  int   error;            /* saved errno in case of any fatal error */
  int   sminqmax;	  /* number of msg defined for the small inq */
  int   sminqlow;         /* the lowest no. of msg in the small inq ever */
  int   sminq_nmsg;       /* current number of msg on the small inbound queue */
  struct strnet_head *sminqfirst;
  struct strnet_head *sminqlast;
  int   lginqmax;	  /* number of msg defined for the large inq */
  int   lginqlow;         /* the lowest no. of msg in the large inq ever */
  int   lginq_nmsg;       /* currnet number of msg on the large inbound queue */
  struct strnet_head *lginqfirst;
  struct strnet_head *lginqlast;
  struct strnet_head *outqfirst; /* pointer to flow control outbound queue */
  struct strn_stat *statp;       /* pointer to the stat table  */
  struct strnet_head *opcl_el;   /* saved element for open/close purpose */
  struct strn_EXC exc_elem;      /* special exceptional strnet element */
};

struct  strn_stat  {
  int   link_count;        /* no. of links that shares this stat entry */
  int   dev_num;           /* actual dev number to board */
  char  ifname[STRN_IFNAME_LEN];        /* interface name  */
  int   outcnt;            /* outbound byte count  */
  int   outmsg;            /* outbound message count */
  int   incnt;             /* inbound byte count */
  int   inmsg;             /* inbound message count */
  long  stime;             /* start time stamp */
};

#define  STRN_INOUT_SIZE   (sizeof(struct  strn_INOUT))

/************************************************************************
*               Streams message type map 				*
*									*
*  Because the driver on the CCB don't include any streams header 	*
*  files, we provide a one-to-one map here for all the streams		*
*  message types for the CCB driver to specify. There is an array       *
*  defined in strnet.c for the message types that should match the      *
*  order defined here.							*
************************************************************************/
/*
 * Data and protocol messages (regular priority)
 */
#define	STRN_DATA		0    		/* regular data */
#define STRN_PROTO		1		/* protocol control */

/*
 * Control messages (regular priority)
 */
#define	STRN_BREAK		2		/* line break */
#define STRN_PASSFP	 	3		/* pass file pointer */
#define	STRN_SIG		4		/* generate process signal */
#define	STRN_DELAY		5		/* real-time xmit delay 
						   (1 param) */
#define STRN_CTL		6		/* device-specific control 
						   message */
#define	STRN_IOCTL		7		/* ioctl; set/get params */
#define STRN_SETOPTS		8		/* set various stream head 
						   options */
#define STRN_RSE		9		/* reserved for RSE use only */


/*
 * Control messages (high priority; go to head of queue)
 */
#define	STRN_IOCACK		10		/* acknowledge ioctl */
#define	STRN_IOCNAK		11		/* negative ioctl acknowledge */
#define STRN_PCPROTO		12		/* priority proto message */
#define	STRN_PCSIG		13		/* generate process signal */
#define	STRN_READ		14		/* generate read notification */
#define	STRN_FLUSH		15		/* flush your queues */
#define	STRN_STOP		16		/* stop transmission 
					   	   immediately */
#define	STRN_START		17		/* restart transmission after 
					   	   stop */
#define	STRN_HANGUP		18		/* line disconnect */
#define STRN_ERROR		19		/* fatal error used to set 
						   u.u_error */
#define STRN_COPYIN		20		/* request to copin data */
#define STRN_COPYOUT		21		/* request to copyout data */
#define STRN_IOCDATA		22		/* response to M_COPYIN and 
						   M_COPYOUT */
#define STRN_PCRSE		23		/* reserved for RSE use only */

