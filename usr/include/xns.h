/*
 	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
 */
/* @(#)xns.h	1.2 87/08/20 */ 

union  addr48 {			/* definition of 48-bit address */
	char    adr[6];
	unsigned short sadr[3];
};

/* IDP header structure */
struct s_idphdr	{		/* XNS internet datagram protocol */
    short    idpcheck;		/* checksum */
    short    idplen;		/* total length of IDP packet */
    char     idpxport;		/* transport control */
    char     idptype;		/* type of XNS level 2 packet */
    long     idpdnet;		/* destination network id */
    short    idpdhost[3];	/* destination 48-bit host address */
    short    idpdskt;		/* destination socket number */
    long     idpsnet;		/* source network id */
    short    idpshost[3];	/* source 48-bit host address */
    short    idpsskt;		/* source socket number */
};

struct s_pephdr {
    long     pepxid;		/* transaction id */
    short    pepcltype;	 	/* client type */
};
#define PEPHDRLEN	(sizeof(struct s_pephdr))

#define RIP_TYPE	1
#define ECHO_TYPE	2
#define ERROR_TYPE	3
#define PEP_TYPE	4
#define SPP_TYPE	5

struct	sOP_read {
	int	handle;		/* suppiled handle */
	unsigned int	timout;	/* how long to wait (250msec units) */
};

#define NUM_MREAD  8
struct  sOP_mread {
	int	numhandles;
	int	handles[NUM_MREAD];	/* array of handles */
	unsigned int 	timout; /* how long to wait (250msec units) */
};

struct	sOP_write {		/* MUST be same size as sOP_read */
	int	filler[2];
};

struct  sOP_pep {
	int reqlength;
	int rspoff;		/* offset to response area */ 
	short retries;
	short timo;
};

struct  sOP_rm {
	unsigned long rmnet;
	unsigned short rmhost[3]; 
	char resname[8];
	unsigned short actlen;
};  

struct  sOP_rout {
	int numnets;
	int curtics;
	int gateflags;
};

struct  sOP_malloc {
	 int  numskts;
};

#define	NS_OK		0
#define NS_IOERR	1003920
#define	NS_NOSOCKAVAIL 	1003921
#define	NS_SOCKTBLFULL	1003922
#define	NS_INVSKT	1003923
#define NS_INUSE	1003924
#define NS_OPENTBLFULL	1003925
#define NS_NOTALLOC	1003926
#define NS_NOTOPEN	1003927
#define NS_UNKNET	1003928
#define	NS_BADHAND	1003929
#define	NS_READPEND	1003930
#define	NS_XFRFAIL	1003931
#define	NS_TRUNCATION 	1003932
#define	NS_TOOBIG	1003933
#define	NS_TIMOUT 	1003934
#define	NS_RESERR	1003935
#define	NS_BADOP	1003936
#define NS_ALRDYOPEN	1003937
#define NS_DUPRSRC	1003938
#define NS_UNDEFRSRC	1003939
#define NS_POSTTBLFULL	1003940
#define NS_BADIDPSIZE	1003941
#define	NS_SIZEERR 	1003942
#define NS_UNREGRSRC	1003943
#define NS_BADREQ 	1003944

struct	sioctl_head {		/* ioctl fixed header */
	int	size;			/* size of ioctl buf */
	int	op_code;		/* supplied op_code */
	int	status;			/* returned status */
	int	socket;			/* supplied/returned socket */
};

struct s_idpioctl {
	struct sioctl_head ioctl_head;
	union {
	    struct sOP_read opread;
	    struct sOP_write opwrite;
	} rwcmd;
};

struct s_pepioctl {
	struct sioctl_head ioctl_head;
	struct sOP_pep oppep;
};

struct s_routent {
	unsigned long netnum;		/* network number */
	unsigned short router[3];	/* 48-bit address of router */
	unsigned char hop;		/* hop count (0 means local) */
	unsigned char port;		/* LAN port used for routing */
	unsigned long uptime;		/* last update time */
};

struct s_rmioctl {
	struct sioctl_head ioctl_head;
	struct sOP_rm oprm;
};

struct s_routioctl {
	struct sioctl_head ioctl_head;
	struct sOP_rout oprout;
};

struct	sRMhdr {                        /* rm header */
    char 		RMhisname[8];   /* requested resource name */
    char		RMmyname[8];    /* requestor's name */
    unsigned short	RMopcode;       /* rm opcode */
    unsigned short	RMstat;         /* rm status */
    unsigned long	RMnet;          /* requested resource network */
    union  	addr48 	RMhost;         /* requested resource host */
    unsigned short	RMsock;         /* requested resource socket */
    unsigned short	RMtype;         /* requestor's data type */
    long		RMtrnid;        /* requestor's transaction id */
};
