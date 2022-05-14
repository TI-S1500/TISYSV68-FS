/*
 *	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1986.  ALL
 *	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
 *	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
 *	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
 *	ASSOCIATED DOCUMENTATION.
 */

#ifdef	SCCSID
static char sockvars_h[] = "@(#)sockvars.h	1.1 (TI) 87/11/02";
#endif	SCCSID

#define ERROR		-1
#define NUBUSDEV	"/dev/nubus"

struct sock
{
	int length;
	int domain;
	int type;
	int proto;
	int fd;
};

struct info
{
	int length;
	int flags;
	int addrlen;
	char addr[16];
};

struct selct
{
	int length;
	int nsock;
	int read;
	int write;
	int pend;
	int secs;
	int usec;
	int readbuf[32];
	int writebuf[32];
	int pendbuf[32];
};

struct options
{
	int length;
	int protocol;
	int optname;
	char optval[16];
	int optlen;
};

#define SIOCSOCK	'S'<<8 | 0
#define SIOCBIND	'S'<<8 | 1
#define SIOCCONN	'S'<<8 | 2
#define SIOCACPT	'S'<<8 | 3
#define SIOCLSTN	'S'<<8 | 4
#define SIOCRECV	'S'<<8 | 5
#define SIOCSEND	'S'<<8 | 6
#define SIOCPEER	'S'<<8 | 7
#define SIOCNAME	'S'<<8 | 8
#define SIOCGOPT	'S'<<8 | 9
#define SIOCSOPT	'S'<<8 | 10
#define SIOCSHUT	'S'<<8 | 11
#define SIOCSLCT	'S'<<8 | 12

