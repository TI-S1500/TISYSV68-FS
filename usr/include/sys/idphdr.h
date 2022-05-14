/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1991.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
 */
/* @(#)idphdr.h	1.3 91/08/09 */

/* header file for idpmain.c, idpsubs.c, xnslev2.c, and libinet.c */

#define WKSMIN 1
#define WKSMAX 3000
#define MINEPHEM 3001
#define MAXEPHEM 65000
#define PEPSOCKBASE 65001

#define RIP_WKS 1
#define ECHO_WKS 2
#define ERROR_WKS 3

#define MAX_MINOR 128
#define HASHSIZE 256
#define ROUTETABLESIZE 255
#define MAXNETS 16

#define NOT_FOUND -1
#define HTFULL -2
#define ALREADY_PRESENT -3

#define NOLINK -1
#define NO_SLOT -1

#define REQUEST 1
#define RESPONSE 2

#define ISROUTER 1
#define NOROUTER -1
#define ME 0
#define ROUTE 1
#define BCAST 2
#define INFHOPS 16

#define IDP_SAP	0x600

#define IDP_MID ('J'<<24)||('M'<<16)||('O'<<8)||'C' /* unique module ID */

struct sockqp {
  queue_t *qptr;
  /* some structure to record which sockets are affiliated with this queue */
};

struct s_pepdata {
	long	pepid;		/* pep transaction id # pending */
	int	rexmits;	/* number of times to retransmit */
	int 	timo;		/* number of seconds between rexmits */
	mblk_t	*msg;		/* message containing request/response */
	queue_t	*queue;		/* queue request was recived on */
};

/* message command type */
#define XNS			('x'<<20)|('n'<<12)|('s'<<4)
#define XNS_SEND_MSG		XNS

struct xns_send_msg {
	long	prim_type;		/* usually XNS_SEND_MSG */
	long	temp[4];		/* space for DL_UNITDATA_REQ */
	short	dest[3];		/* space for LSAP dest address */
        long	slot;			/* slot to force out, or -1 */
};

/* ioctl command types for XNS driver */
#define XNS_INIT_REQ		XNS|1
#define XNS_LINKINFO		XNS|2
#define XNS_RIPREQ_REQ		XNS|3
#define XNS_ALLOC_SOCKET_REQ	XNS|4
#define XNS_BIND_SOCKET_REQ     XNS|5
#define XNS_UNBIND_SOCKET_REQ   XNS|6
#define XNS_GETAD_REQ		XNS|7
#define XNS_GETROUTAB_REQ	XNS|8
#define XNS_SETNETWORK_REQ	XNS|9
#define XNS_PEPSEND_REQ		XNS|10

struct xns_linkinfo {
	int		status;		/* unused */
	int		slot;		/* slot number of stream just linked */
};

struct xns_alloc_socket_req {
        int 		status;		/* return status */
	unsigned short	socket;		/* 0=ephermeral, 1-0xBB8 = WKS */
};

struct xns_bind_socket_req {
	int		status;		/* return status */
        unsigned short  socket;		/* allocated socket to bind to */
	int		handle;		/* file desc. of stream to bind to */
	int		maxtimer;	/* max time a msg can spend on a q */
        int		sig;		/* signal to send on incoming msg */
};

struct xns_unbind_socket_req {
	int		status;		/* return status */
	unsigned short  socket;		/* socket to unbind */
	int		handle;		/* ret. file desc. of stream bound to */
};

struct xns_getad_req {
        int		status;		/* return status */
        int		slot;		/* slot number to get info about */
	unsigned char	hostaddr[6];	/* Host address */
	unsigned long	network;	/* Host network */
};

struct xns_getroutab_req {
	int		status;		/* return status */
        long		curtics;	/* current tick count */
        int		numrtes;        /* num valid rtes that are returned */
        int		isrouter;	/* set if is a router */
	struct s_routent rtable[ROUTETABLESIZE]; /* Routing table */
};

struct xns_setnetwork_req {
	int		status;		/* return status */
	unsigned long	network;	/* network number */
	unsigned char	slot;		/* slot number */
        int		isrouter;	/* ISROUTER or NOROUTER */
                                        /* 0 for no change */
};

struct xns_pepsend_req {
	int		status;		/* return status */
        int		rexmits;	/* number of retransmits */
	int		timeout;	/* number of seconds between rexmits */
        char		block[1500];	/* block to send and receive */
};

union xns_primitives {
        int 				status;
        struct xns_linkinfo		linkinfo;
	struct xns_alloc_socket_req	alloc_socket_req;
	struct xns_bind_socket_req	bind_socket_req;
	struct xns_unbind_socket_req	unbind_socket_req;
	struct xns_getad_req		getad_req;	
	struct xns_getroutab_req	getroutab_req;	
	struct xns_setnetwork_req	setnetwork_req;
	struct xns_pepsend_req		pepsend_req;
};

/* error message types */
#define UNSPEC	1
#define CHKSUM	2
#define NOSKT	3
#define RESRC	4
#define DESTUNREACH	5
#define TOOMANYROUT	6

