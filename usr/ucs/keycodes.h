/*
*	(C) COPYRIGHT,	 TEXAS INSTRUMENTS INCORPORATED,   1987.   ALL
*	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS  INCORPORATED.
*	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
*	TO RESTRICTIONS SET FORTH IN TI'S  PROGRAM  LICENSE  AGREEMENT
*	AND ASSOCIATED DOCUMENTS.
*/
/* @(#)keycodes.h	1.13 91/12/03 */

/* KEYCODES */
#define DSPK	0x01
#define	QUIT    0x03
/*#define DEVCNCL 0x10*/
#define	TERM    0x15
#define	EXECUTE 0x17
#define CHGHAT	0x19
#define SYSREQ	0x80
#define PF1	0x81
#define PF2	0x82
#define PF3	0x83
#define PF4	0x84
#define PF5	0x85
#define PF6	0x86
#define PF7	0x87
#define PF8	0x88
#define PF9	0x89
#define PF10	0x8a
#define PF11	0x8b
#define PF12	0x8c
/*#define PGM1	  0x8d*/
/*#define PGM2	  0x8e*/
/*#define PGM3	  0x8f*/
#define PA1	0x90
#define PA2	0x91
#define PA3	0x92
#define CLRKEY	0x93
#define ENTER	0x94
#define INS	0x95
#define SKIP	0x96
/*#define MODE2   0x97*/
/*#define MODE1   0x98*/
/*#define MODE3   0x99*/
#define ERASEIN	0x9a
#define FLEFT	0x9b
#define DELETE	0x9c
#define DUP	0x9d
#define ERASEOF	0x9e
#define EOSKEY	0x9f
#define CRGRET	0xa0
#define FRIGHT	0xa1
#define RIGHT	0xa2
#define LEFT	0xa3
#define UPKEY	0xa4
#define DOWN	0xa5
#define WTKEY	0xa6
#define HOME	0xa7
#define PRINT	0xa8
/*#define DSCKBD  0xa9*/
#define WAIT	0xaa
#define ATTN	0xab
#define FDMK	0xac
/*#define CLRCH0  0xad*/
/*#define ULINE   0xae*/
/*#define BLINKEY 0xaf*/
/*#define RVIDEO  0xb0*/
/*#define RCOLOR  0xb1*/
/*#define CBLUE   0xb2*/
/*#define CRED	  0xb3*/
/*#define CMAGNTA 0xb4*/
/*#define CGREEN  0xb5*/
/*#define CCYAN   0xb6*/
/*#define CYELLOW 0xb7*/
/*#define CWHITE  0xb8*/
#define ALPHA	0xb9
/*#define CPSCRN  0xba*/
#define TAB	0xbb
#define BACKTAB	0xbc
/*#define DSPATR  0xbd*/
/*#define CTAB	  0xbe*/
/*#define STAB	  0xbf*/
/*#define CPWORD  0xc0*/
#define PF13	0xc1
#define PF14	0xc2
#define PF15	0xc3
#define PF16	0xc4
#define PF17	0xc5
#define PF18	0xc6
#define PF19	0xc7
#define PF20	0xc8
#define PF21	0xc9
#define PF22	0xca
#define PF23	0xcb
#define PF24	0xcc
/*#define WDLEFT  0xcd*/
/*#define WDRIGHT 0xce*/
/*#define WDDEL   0xcf*/
#define SKPSOD	0xd0
#define SKPEOD	0xd1
/*#define TSTMODE 0xd2*/
/*#define CPFLD   0xd3*/
/*#define SLCURS  0xd6*/
/*#define BELL	  0xd7*/
#define FERASE	0xd8
/*#define PGM4	  0xd9*/
/*#define PGM5	  0xda*/
/*#define PGM6	  0xdb*/
/*#define PGM7	  0xdc*/
/*#define PGM8	  0xdd*/
/*#define PGM9	  0xde*/
/*#define PGM10   0xdf*/
/*#define PGM11   0xe0*/
/*#define PGM12   0xe1*/
#define LPRINT	0xe2
/*#define PF25	  0xe3*/
/*#define PF26	  0xe4*/
/*#define PF27	  0xe5*/
/*#define PF28	  0xe6*/
/*#define PF29	  0xe7*/
/*#define PF30	  0xe8*/
/*#define PF31	  0xe9*/
/*#define PF32	  0xea*/
/*#define PF33	  0xeb*/
/*#define PF34	  0xec*/
/*#define PF35	  0xed*/
/*#define PF36	  0xee*/
/*#define TASK1   0xef*/
/*#define TASK2   0xf0*/
/*#define TASK3   0xf1*/
/*#define TASK4   0xf2*/
/*#define TASK5   0xf3*/
/*#define TASK6   0xf4*/
/*#define TASK7   0xf5*/
/*#define TASK8   0xf6*/
/*#define TASK9   0xf7*/
/*#define TASK10  0xf8*/
/*#define TASK11  0xf9*/
/*#define TASK12  0xfa*/
#define TOPPAGE 0xfb
#define ENDPAGE 0xfc
#define STARTLINE 0xfd
#define ENDLINE 0xfe
#define RESETKY	0xff

#define PREKEYS 46			/* number of pre-defined keys */
#define PREFCTNS 41			/* number of pre-defined functions */
#define USRKEYS 33			/* number of user-defined keys */
#define USRFCTNS 14 			/* number of user-defined functions */
#define MAPSIZE PREKEYS+USRKEYS		/* number of keys */
#define NUMFCTNS PREFCTNS+USRFCTNS 	/* number of functions */

#ifdef FE
typedef struct mapentry {
	unsigned int	fevent;
	unsigned char	key3279;
	} MAPENTRY ; 

typedef struct keytable {
	char	*fctn;
	char 	keyseq[13];
	} KEYTABLE;

typedef struct keydef {
	int	code;
	char	*text;
	} KEYDEF ; 
#endif
