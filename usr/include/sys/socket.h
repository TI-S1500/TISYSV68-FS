
/*
 *	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1986.  ALL
 *	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
 *	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
 *	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
 *	ASSOCIATED DOCUMENTATION.
 */

#ifdef	SCCSID
static char socket_h[] = "@(#)socket.h	1.12 (TI) 91/11/11";
#endif	SCCSID
/*web 4-28-89 */
#ifndef socket_h
#define socket_h
/*
 * Definitions related to sockets: types, address families, options.
 */

/*
 * Types
 */
#define	SOCK_STREAM	1		/* stream socket */
#define	SOCK_DGRAM	2		/* datagram socket */
#define	SOCK_RAW	3		/* raw-protocol interface */
#define	SOCK_RDM	4		/* reliably-delivered message */
#define	SOCK_SEQPACKET	5		/* sequenced packet stream */

/*
 * Option flags per-socket.
 */
#define	SO_DEBUG	0x01		/* turn on debugging info recording */
#define	SO_ACCEPTCONN	0x02		/* socket has had listen() */
#define	SO_REUSEADDR	0x04		/* allow local address reuse */
#define	SO_KEEPALIVE	0x08		/* keep connections alive */
#define	SO_DONTROUTE	0x10		/* just use interface addresses */
/*web 4-28-89 */
#define	SO_BROADCAST	0x0020	/* permit sending of broadcast msgs */
				/* 0x20 was SO_NEWFDONCONN */
#define	SO_USELOOPBACK	0x40		/* bypass hardware when possible */
#define	SO_LINGER	0x80		/* linger on close if data present */
#define	SO_DONTLINGER	(~SO_LINGER)	/* ~SO_LINGER */
/*web 4-28-89 */
#define	SO_OOBINLINE	0x0100	/* leave received OOB data in line */
#define SO_ORDREL	0x0200	/* give use orderly release */
#define SO_IMASOCKET	0x0400	/* use socket semantics (affects bind) */

/*
 * Additional options, not kept in so_options.
 */
#define SO_SNDBUF	0x1001	/* send buffer size */
#define SO_RCVBUF	0x1002	/* receive buffer size */
#define SO_SNDLOWAT	0x1003	/* send low-water mark */
#define SO_RCVLOWAT	0x1004	/* receive low-water mark */
#define SO_SNDTIMEO	0x1005	/* send timeout */
#define SO_RCVTIMEO	0x1006	/* receive timeout */
#define	SO_ERROR	0x1007	/* get error status and clear */
#define	SO_TYPE		0x1008	/* get socket type */
#define SO_PROTOTYPE	0x1009	/* get/set protocol type */

/*
 * Structure used for manipulating linger option.
 */
struct linger {
	int             l_onoff;/* option on/off */
	int             l_linger;	/* linger time */
};

/*
 * An option specification consists of an opthdr, followed by the value of
 * the option.  An options buffer contains one or more options.  The len
 * field of opthdr specifies the length of the option value in bytes.  This
 * length must be a multiple of sizeof(long) (use OPTLEN macro).
 */

struct opthdr {
	long            level;	/* protocol level affected */
	long            name;	/* option to modify */
	long            len;	/* length of option value */
};

#define OPTLEN(x) ((((x) + sizeof(long) - 1) / sizeof(long)) * sizeof(long))
#define OPTVAL(opt) ((char *)(opt + 1))

/*
 * the optdefault structure is used for internal tables of option default
 * values.
 */
struct optdefault {
	int             optname;/* the option */
	char           *val;	/* ptr to default value */
	int             len;	/* length of value */
};

/*
 * the opproc structure is used to build tables of options processing
 * functions for dooptions().
 */
struct opproc {
	int             level;	/* options level this function handles */
	int             (*func) ();	/* the function */
};

/*
 * Address families.
 */
#define	AF_UNSPEC	0		/* unspecified */
#define	AF_UNIX		1		/* local to host (pipes, portals) */
#define	AF_INET		2		/* internetwork: UDP, TCP, etc. */
#define	AF_IMPLINK	3		/* arpanet imp addresses */
#define	AF_PUP		4		/* pup protocols: e.g. BSP */
#define	AF_CHAOS	5		/* mit CHAOS protocols */
#define	AF_NS		6		/* XEROX NS protocols */
#define	AF_NBS		7		/* nbs protocols */
#define	AF_ECMA		8		/* european computer manufacturers */
#define	AF_DATAKIT	9		/* datakit protocols */
#define	AF_CCITT	10		/* CCITT protocols, X.25 etc */
#define	AF_SNA		11		/* IBM SNA */
#define	AF_NUBUS	12		/* Texas Instruments Nubus IPC */
/*web 4-28-89 */
#define AF_DECnet	13	/* DECnet */
#define AF_DLI		14	/* Direct data link interface */
#define AF_LAT		15	/* LAT */
#define	AF_HYLINK	16	/* NSC Hyperchannel */
#define	AF_APPLETALK	17	/* Apple Talk */

#define	AF_MAX		18

/*
 * Structure used by kernel to store most
 * addresses.
 */
struct sockaddr {
	ushort	sa_family;	
	char	sa_data[14];	
};

/*
 * Structure used by kernel to pass protocol
 * information in raw sockets.
 */
struct sockproto {
	ushort	sp_family;		/* address family */
	ushort	sp_protocol;		/* protocol */
};

/*
 * Protocol families, same as address families for now.
 */
#define	PF_UNSPEC	AF_UNSPEC
#define	PF_UNIX		AF_UNIX
#define	PF_INET		AF_INET
#define	PF_IMPLINK	AF_IMPLINK
#define	PF_PUP		AF_PUP
#define	PF_CHAOS	AF_CHAOS
#define	PF_NS		AF_NS
#define	PF_NBS		AF_NBS
#define	PF_ECMA		AF_ECMA
#define	PF_DATAKIT	AF_DATAKIT
#define	PF_CCITT	AF_CCITT
#define	PF_SNA		AF_SNA
#define	PF_NUBUS	AF_NUBUS

#define	PF_MAX		13

/*
 * Level number for (get/set)sockopt() to apply to socket itself.
 */
#define	SOL_SOCKET	0xffff		/* options for socket level */

/*
 * Maximum queue length specifiable by listen.
 */
#define	SOMAXCONN	5
/*
 * Message header for recvmsg and sendmsg calls.
 */
struct msghdr {
	caddr_t         msg_name;	/* optional address */
	int             msg_namelen;	/* size of address */
	int             msg_base;	/* base address of data */
	int             msg_len;/* size of data */
	caddr_t         msg_accrights;	/* access rights sent/received */
	int             msg_accrightslen;
};

#define	MSG_OOB		0x1		/* process out-of-band data */
#define	MSG_PEEK	0x2		/* peek at incoming message */
#define	MSG_DONTROUTE	0x4		/* send without using routing tables */

#define	MSG_MAXIOVLEN	16

/*web 4-28-89 */
/*
 * This ioctl code uses BSD style ioctl's to avoid copyin/out problems.
 * Ioctl's have the command encoded in the lower word, and the size of any in
 * or out parameters in the upper word.  The high 2 bits of the upper word
 * are used to encode the in/out status of the parameter; for now we restrict
 * parameters to at most 128 bytes.
 */
#define	IOCPARM_MASK	0x7f	/* parameters must be < 128 bytes */
#define	IOC_VOID	0x20000000	/* no parameters */
#define	IOC_OUT		0x40000000	/* copy out parameters */
#define	IOC_IN		0x80000000	/* copy in parameters */
#define	IOC_INOUT	(IOC_IN|IOC_OUT)
/* the 0x20000000 is so we can distinguish new ioctl's from old */
#define	_IOS(x,y)	(IOC_VOID|('x'<<8)|y)
#define	_IOSR(x,y,t)	(IOC_OUT|((sizeof(t)&IOCPARM_MASK)<<16)|('x'<<8)|y)
#define	_IOSW(x,y,t)	(IOC_IN|((sizeof(t)&IOCPARM_MASK)<<16)|('x'<<8)|y)
/* this should be _IOSRW, but stdio got there first */
#define	_IOSWR(x,y,t)	(IOC_INOUT|((sizeof(t)&IOCPARM_MASK)<<16)|('x'<<8)|y)

/*
 * Socket ioctl commands
 * 
 */

#define SIOCSHIWAT	_IOSW(S, 1, int)	/* set high watermark */
#define SIOCGHIWAT	_IOSR(S, 2, int)	/* get high watermark */
#define SIOCSLOWAT	_IOSW(S, 3, int)	/* set low watermark */
#define SIOCGLOWAT	_IOSR(S, 4, int)	/* get low watermark */
#define SIOCATMARK	_IOSR(S, 5, int)	/* at oob mark? */
#define SIOCSPGRP	_IOSW(S, 6, int)	/* set process group */
#define SIOCGPGRP	_IOSR(S, 7, int)	/* get process group */
#define FIONREAD	_IOSR(S, 8, int)	/* BSD compatibilty */
#define FIONBIO		_IOSW(S, 9, int)	/* BSD compatibilty */
#define FIOASYNC	_IOSW(S, 10, int)	/* BSD compatibilty */
#define SIOCPROTO	_IOSW(S, 11, struct socknewproto)	/* link proto */
#define SIOCGETNAME	_IOSR(S, 12, struct sockaddr)	/* getsockname */
#define SIOCGETPEER	_IOSR(S, 13, struct sockaddr)	/* getpeername */
#define IF_UNITSEL	_IOSW(S, 14, int)	/* set unit number */
#define SIOCXPROTO	_IOS(S, 15)	/* empty proto table */

#define	SIOCADDRT	_IOSW(R, 9, struct rtentry)	/* add route */
#define	SIOCDELRT	_IOSW(R, 10, struct rtentry)	/* delete route */

#define	SIOCSIFADDR	_IOSW(I, 11, struct ifreq)	/* set ifnet address */
#define	SIOCGIFADDR	_IOSWR(I, 12, struct ifreq)	/* get ifnet address */
#define	SIOCSIFDSTADDR	_IOSW(I, 13, struct ifreq)	/* set p-p address */
#define	SIOCGIFDSTADDR	_IOSWR(I, 14, struct ifreq)	/* get p-p address */
#define	SIOCSIFFLAGS	_IOSW(I, 15, struct ifreq)	/* set ifnet flags */
#define	SIOCGIFFLAGS	_IOSWR(I, 16, struct ifreq)	/* get ifnet flags */
#define	SIOCGIFCONF	_IOSWR(I, 17, struct ifconf)	/* get ifnet list */
#define SIOCIFDETACH	_IOSW(I, 26, struct ifreq)	/* detach interface */
#define SIOCGENPSTATS	_IOSWR(I, 27, struct ifreq)	/* get ENP stats */

#define SIOCX25XMT	_IOSWR(I, 29, struct ifreq)	/* start a slp proc in
							 * x25if */
#define SIOCX25RCV	_IOSWR(I, 30, struct ifreq)	/* start a slp proc in
							 * x25if */
#define SIOCX25TBL	_IOSWR(I, 31, struct ifreq)	/* xfer lun table to
							 * kernel */

#define	SIOCGIFBRDADDR	_IOSWR(I, 32, struct ifreq)	/* get broadcast addr */
#define	SIOCSIFBRDADDR	_IOSW(I, 33, struct ifreq)	/* set broadcast addr */
#define	SIOCGIFNETMASK	_IOSWR(I, 34, struct ifreq)	/* get net addr mask */
#define	SIOCSIFNETMASK	_IOSW(I, 35, struct ifreq)	/* set net addr mask */
#define	SIOCGIFMETRIC	_IOSWR(I, 36, struct ifreq)	/* get IF metric */
#define	SIOCSIFMETRIC	_IOSW(I, 37, struct ifreq)	/* set IF metric */

#define	SIOCSARP	_IOSW(I, 38, struct ifreq)	/* set arp entry */
#define	SIOCGARP	_IOSWR(I, 39, struct ifreq)	/* get arp entry */
#define	SIOCDARP	_IOSW(I, 40, struct ifreq)	/* delete arp entry */

#define SIOCSLGETREQ	_IOSWR(I, 41, struct ifreq)	/* wait for switched
							 * SLIP request */
#define SIOCSLSTAT	_IOSW(I, 42, struct ifreq)	/* pass SLIP info to
							 * kernel */

#define SIOCSIFNAME	_IOSW(I, 43, struct ifreq)	/* set interface name */
#define	SIOCGIFONEP	_IOSWR(I, 44, struct ifreq)	/* get one-packet params */
#define	SIOCSIFONEP	_IOSW(I, 45, struct ifreq)	/* set one-packet params */

#define SIOCGENADDR	_IOSWR(I, 65, struct ifreq)	/* Get ethernet addr */

#define SIOCSOCKSYS	_IOSW(I, 66, struct socksysreq)	/* Pseudo socket syscall */
/*NVS*/
#define SIOCJNVS	_IOSW(I, 71, int)	/* join pty & socket */
#define SIOCJNVSWAIT	_IOSW(I, 72, int)	/* wait for SIOCJNVS completion */
#define JNVS_PKTMODE	0x10000			/* packet mode */
#define JNVS_TELNET	0x20000			/* telnet mode */
#define JNVS_TELBIN	0x40000			/* telnet binary mode */
/*NVS*/

/*
 * This structure is used to encode pseudo system calls
 */
struct socksysreq {
	int             args[7];
};

/*
 * This structure is used for adding new protocols to the list supported by
 * sockets.
 */

struct socknewproto {
	int             family;	/* address family (AF_INET, etc.) */
	int             type;	/* protocol type (SOCK_STREAM, etc.) */
	int             proto;	/* per family proto number */
	dev_t           dev;	/* major/minor to use (must be a clone) */
	int             flags;	/* protosw flags */
};

/*
 * utility definitions.
 */

#define MAXHOSTNAMELEN	64

#define	NBBY	8		/* number of bits in a byte */
/*
 * Select uses bit masks of file descriptors in longs. These macros
 * manipulate such bit fields (the filesystem macros use chars). FD_SETSIZE
 * may be defined by the user, but the default here should be >= NOFILE
 * (param.h).
 */
#ifndef	FD_SETSIZE
#define	FD_SETSIZE	256
#endif

typedef long    fd_mask;
#define NFDBITS	(sizeof(fd_mask) * NBBY)	/* bits per mask */
#ifndef howmany
#define	howmany(x, y)	(((x)+((y)-1))/(y))
#endif

typedef struct fd_set {
	fd_mask         fds_bits[howmany(FD_SETSIZE, NFDBITS)];
}               fd_set;

#define	FD_SET(n, p)	((p)->fds_bits[(n)/NFDBITS] |= (1 << ((n) % NFDBITS)))
#define	FD_CLR(n, p)	((p)->fds_bits[(n)/NFDBITS] &= ~(1 << ((n) % NFDBITS)))
#define	FD_ISSET(n, p)	((p)->fds_bits[(n)/NFDBITS] & (1 << ((n) % NFDBITS)))
#define FD_ZERO(p)	memset((char *)(p), '\0', sizeof(*(p)))

/* defines for user/kernel interface */

#define	MAX_MINOR	(makedev(1,0) - 1)	/* could be non-portable */

#if (INTEL == 32)
#define SOCKETSYS	128	/* MUST BE CHANGED DEPENDING ON OS/SYSENT.C!! */
#endif

#if (ATT == 32)
#define SOCKETSYS	88	/* MUST BE CHANGED DEPENDING ON OS/SYSENT.C!! */
#endif

#if (INTEL == 31) || (ATT == 31)
#define SOCKETSYS	88	/* MUST BE CHANGED DEPENDING ON OS/SYSENT.C!! */
#endif

#ifndef SOCKETSYS
#define SOCKETSYS	83	/* MUST BE CHANGED DEPENDING ON OS/SYSENT.C!! */
#endif


#define  SO_ACCEPT	1
#define  SO_BIND	2
#define  SO_CONNECT	3
#define  SO_GETPEERNAME	4
#define  SO_GETSOCKNAME	5
#define  SO_GETSOCKOPT	6
#define  SO_LISTEN	7
#define  SO_RECV	8
#define  SO_RECVFROM	9
#define  SO_SEND	10
#define  SO_SENDTO	11
#define  SO_SETSOCKOPT	12
#define  SO_SHUTDOWN	13
#define  SO_SOCKET	14
#define  SO_SELECT	15
#define  SO_GETIPDOMAIN	16
#define  SO_SETIPDOMAIN	17
#define  SO_ADJTIME	18
#define  SO_SETREUID	19
#define  SO_SETREGID	20
#define  SO_GETTIME	21
#ifndef KTTY
#define	 SO_SELECTRD	22
#endif

#endif				/* socket_h */
