/*
 	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
 */
/* @(#)lan.h	1.12 88/12/23 */ 

/*
 *		lan.h
 */

union  addr48 {			/* definition of 48-bit address */
	char    adr[6];
	unsigned short sadr[3];
};
				/* Level zero opcode structure definitions */

struct	sOP_reg {		/* register type */
	unsigned short	type;	/* packet type for receive */
	int	handle;		/* returned for receive calls */
	int	lsignal;	/* signal for packet received */
	int	maxtimer;	/* time packets are allowed on queue */
};

struct	sOP_dreg {		/* deregister type */
	unsigned short	type;	/* packet type for receive */
};

struct	sOP_rcv_snd {		/* receive and send packets */
	int	handle;		/* handle for receives */
	int	timout;		/* timeout value */
};


struct	sOP_stat {		/* ethernet statistics */
	int	clear;		/* read/reset flag */
	int	adp;		/* returned adaptor type */
};

struct	sOP_mc_reg_dreg {	/* register/deregister multicast address */
	union addr48 mcaddr;	/* multicast address */
};

struct	sOP_getadr {		/* register/deregister multicast address */
	union addr48 hostaddr;	/* multicast address */
};

struct	sOP_netutil {		/* measure network utilization */
	unsigned long intrvl;	/* interval length in units of 3.2 us */
	unsigned long samples;	/* number of samples */
	unsigned short lev;	/* interrupt level at which to sample */
	unsigned long ncs0;	/* number of samples carrier on for port 0 */
	unsigned long ncs1;	/* number of samples carrier on for port 1 */
};

struct 	sOP_nmgr {			/* name manager request packet */
	unsigned short ethadr[3];	/* ethernet address */
	unsigned long  netadr;		/* network address */
	unsigned short socket;		/* socket (optional) */
	char sname[8];			/* sitename */
	unsigned short nm_op;		/* nmgr internal op code */
};

struct	s_ethhdr {		/* level zero ethernet header */
	union addr48 dstadr;	/* destination address */
	union addr48 srcadr;	/* source address */
	unsigned short	type;	/* packet type */
};

#define L0HDRLEN (sizeof(struct sL0Head))
#define DUMP_AREA_LEN 170	/* 586 dump area length */

#define ZERO_REG     0		/* register type */
#define ZERO_DEREG   1		/* deregister type */
#define ZERO_SEND    2		/* send packet */
#define ZERO_RCV     3		/* receive packet */
#define ZERO_STAT    4		/* netstat */
#define ZERO_MC_REG  5		/* register multicast address */
#define ZERO_MC_DREG 6		/* deregister multicast address */
#define ZERO_NETUTIL 7		/* network utilization */
#define ZERO_GETADR  8		/* get 48-bit address */
#define ZERO_NM_REQ  9		/* name manager request */
#define ZERO_DUMP   10		/* 586 dump area */

#define MAX_OP       11		/* opcode limit */

				/* LEVEL ZERO status error codes */

#define NET_OK		0
#define NET_IOERR	1003901
#define	NET_BADHAND	1003902
#define	NET_BADTYP	1003903
#define	NET_TOOBIG	1003904
#define	NET_XFRFAIL	1003905
#define	NET_TIMOUT	1003906
#define	NET_RCVPEND	1003907
#define	NET_TRUNCATION	1003908
#define	NET_RESERR	1003909
#define	NET_NOROOM	1003910
#define	NET_NOTREG	1003911
#define NET_INUSE	1003912
#define NET_BADOP	1003913
#define NET_BADMCADR	1003914
#define NET_SPACERR	1003915
#define NET_DUPMC	1003916
#define NET_UNDEFMC	1003917
#define NET_TIMERR	1003918
#define NET_NMNOTACTV   1003964

union	uCMD{
	struct	sOP_reg		OP_reg;
	struct	sOP_dreg	OP_dreg;
	struct	sOP_rcv_snd	OP_rcv_snd;
	struct	sOP_stat	OP_stat;
	struct	sOP_mc_reg_dreg	OP_mc_reg_dreg;
	struct  sOP_netutil	OP_netutil;
	struct  sOP_getadr	OP_getadr;
	struct  sOP_nmgr	OP_nmgr;
};

struct	sioctl_head {		/* ioctl fixed header */
	int	size;			/* size of ioctl buf */
	int	xfer_size;		/* transfer size */
	int	op_code;		/* supplied op_code */
	int	status;			/* returned status */
};

struct	ioctl_buf {		/* ioctl buffer template */
	struct	sioctl_head ioctl_head;
	union	uCMD cmd;
};

struct	s_netioctl {		/* ioctl buffer template */
	struct	sioctl_head ioctl_head;
	struct  sOP_rcv_snd rcvsnd;
};

struct s_statioctl {		/* net stats command block */
	struct sioctl_head ioctl_head;
	struct sOP_stat	opstat;
};

#define IOCTL_HEADER_SIZE (sizeof (struct sioctl_head))
#define IOCTL_UNION_SIZE  (sizeof (struct ioctl_buf))
#define ZEROREG_SIZE   (IOCTL_HEADER_SIZE + sizeof(struct sOP_reg))
#define ZERODREG_SIZE  (IOCTL_HEADER_SIZE + sizeof(struct sOP_dreg))
#define ZEROXFER_SIZE  (IOCTL_HEADER_SIZE + sizeof(struct sOP_rcv_snd))
#define ZEROSTAT_SIZE  (IOCTL_HEADER_SIZE + sizeof(struct sOP_stat))
#define ZEROMCRD_SIZE  (IOCTL_HEADER_SIZE + sizeof(struct sOP_mc_reg_dreg))
#define ZERONUTL_SIZE  (IOCTL_HEADER_SIZE + sizeof(struct sOP_netutil))
#define ZEROGADR_SIZE  (IOCTL_HEADER_SIZE + sizeof(struct sOP_getadr))
#define ZERONMGR_SIZE  (IOCTL_HEADER_SIZE + sizeof(struct sOP_nmgr))
#define ZERODUMP_SIZE  IOCTL_HEADER_SIZE

#define ADP_IEEE_802	0x77
#define ADP_STARLAN	0x78
#define ADP_V35		0x79
#define ADP_NONE	0x7f
