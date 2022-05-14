/*
*	(C) COPYRIGHT,	 TEXAS INSTRUMENTS INCORPORATED,   1987.   ALL
*	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS  INCORPORATED.
*	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
*	TO RESTRICTIONS SET FORTH IN TI'S  PROGRAM  LICENSE  AGREEMENT
*	AND ASSOCIATED DOCUMENTS.
*/
/* @(#)userv3279.h	1.1 87/04/25 */

extern int	open_mcp();
extern int	get_cursor();
extern int	get_fld();
extern int	get_8bitscrn();
extern int	get_scrn();
extern int	get_rawscrn();
extern int	sget_vdu();
extern int	sput_vdu();
extern int	push_key();
extern int	q_8bitkey();
extern int	q_key();
extern int	q_string();
extern int	wait_str();
extern int	wait_key();
extern unsigned short	wait_mcp();
extern unsigned short	get_status();
extern char	*nmerrno();
extern char	*nmtypemsg();
extern char	*nmkey();
extern char	*nmevent();
extern char	*nmstatus();

#define shmaddr 0L

struct intfshm {
	unsigned short	v3279status;
	unsigned short	waitmask;
	long	sndkey;
	unsigned short	vduoffset;
	unsigned short	szterm;
	unsigned short	vdusz;
	unsigned short	offset;
	unsigned short	mtype;
	unsigned char	keyerr;
	unsigned char	attr;
	unsigned char	waitkey;
};
typedef struct intfshm *INTFP;

struct intfmsg {
	long	type;
	unsigned char	text[2];
};

/* userintf send message types */
#define OPENMCP 17L
#define PVDU	18L
#define PUSHKEY	19L
#define QKEY	20L
#define QSTRING	21L
#define RLSCRN	22L
#define CLOSEMCP 23L

/* 914c receive types */
#define KEYOK	24L
#define KEYERR	25L
#define WAITMCP	26L

/* status bits */
#define HOSTLOCK	0x0001
#define LOCKED	 	0x0001
#define HOSTFREE	0x0002
#define MESSAGE		0x0004
#define WAIT_STRING	0x0008
#define WAIT_KEY	0x0010
#define HITKEY		0x0010
#define BINDSES		0x0020
#define BOUND		0x0020
#define UNBINDSES	0x0040
#define STARTDATA	0x0080
#define DATATRAFFIC	0x0080
#define STOPDATA	0x0100
#define STARTSSC	0x0200
#define SSCSESSION	0x0200
#define STARTLULU	0x0400
#define LULUSESSION	0x0400
#define RCVDATA		0x0800
#define DATARCVD	0x0800
#define CLRDATA		0xf7ff
#define HOLDDATA	0x1000
#define VIDEO		0x2000
#define KEYBOARD	0x4000
#define STARTUNOWN	0x8000

/* function errno returns */
#define SETSLOCK 50
#define LOCKSET 51
#define LOSTSESSION 52
#define INVKEY 53
#define IIPLOCK 54
#define ATTNERR 55
#define AIDERR 56
#define ATRBPROTECT 57
#define FLDNUM 58
#define INVINS 59
#define NOENABLE 60
#define NOT_OPEN 61
#define TRUNCATED 62
#define NOMSGQ	63
#define INVPARM	64

/* highlighting codes */
#ifndef BLINK
#define	NORMAL	0
#define	BLINK	1
#define	REVERSE	2
#define	USCORE	4
#endif

/* extended colors */
#ifndef BLUE
#define	BLACK	0
#define	BLUE	1
#define	RED	2
#define	PINK	3
#define	GREEN	4
#define	TURQOS	5
#define	YELLOW	6
#define	WHITE	7
#define	MAGENTA	3
#define	CYAN	5
#define GREY 8
#define LT_BLUE 9
#define LT_GREEN 10
#define LT_CYAN 11
#define LT_RED 12
#define LT_MAGENTA 13
#define BROWN 14
#define HI_WHITE 15
#endif
