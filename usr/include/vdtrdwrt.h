/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1991.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.

*/

/*
********************************************************************************
*		Copyright (c) 1984 AT&T Technologies, Inc.		       *
*			    All Rights Reserved 			       *
*									       *
*									       *
*	      THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF		       *
*			  AT&T TECHNOLOGIES, INC.			       *
*	 The copyright notice above does not evidence any actual	       *
*	 or intended publication of such source code.			       *
********************************************************************************
*/
#ident "@(#)vdtrdwrt.h	1.14 91/01/04"
/* contains structures used in application interface to field edit 	*/

/* opcodes	 */
/* these opcodes are used by the application, vdtread/write routines, and */
/* field edit routines in the driver.  Nubus transport uses the ioctl opcodes */
/* defined in busnet.h.  Crb opcodes used by driver lower levels are defined */
/* in c304.h.								   */
#define FEWRITE		0x01		/* field edit write  */
#define STSWRITE	0x02		/* status line write */
#define STSRSTOR	0x03		/* status line restore */
#define FEREAD		0x04		/* field edit read     */
#define UPDATE		0x05		/* read with initial value */
#define UPDATE1		0x06		/* update w/o display */

/* validation table describes which characters are valid or invalid */
struct vpair {
	unsigned char low ;	/* low character in range  */
	unsigned char hi ;	/* high character in range */
} ;
struct validtable {
	short length ;	/* total length of table   */
	short flags ;	/* are following ranges valid or invalid? */
	struct vpair range[128] ;	/* up to 128 ranges    */
} ;

/* readblock describes how a read is to be done  */
struct readblock {
	char  opcode ; 		/* either read or update, so far */
	long fldflags;		/* which field edit keys to honor  */
	short  miscflag;	/* misc options */
	unsigned char sgr_on, sgr_off;		/* sgr flags */
	unsigned char fg_color, bg_color;	/* color specification */
	unsigned char  *buffaddr ;	/* read buffer pointer          */
	short bufflen ; 	/* number of characters to read  */
	unsigned char  fieldrow ; 	/* field start row address */
	unsigned char  fieldcol ; 	/* field start column address */
	unsigned char  cursorrow ;	/* starting cursor row position */
	unsigned char  cursorcol ; 	/* starting cursor column position */
	short rtimeout ; 	/* request timeout    */
	char  prompt ;		/* prompt character  */
	char  fill ; 		/* fill character  */
	long   eventflags1 ; 	/* which of 32 function keys to honor */
	long   eventflags2 ;	/* which events to honor    */
	long	eventflags3; 	/* function keys 33-64 */
	long	eventflags4; 	/* function keys 65-96 */
	long	eventflags5;	/* function keys 97-128 */
	struct ccbread *rtrn ;  /* pointer to returned data */
	struct validtable *valid_table_addr ; /* validation table offset */
} ;
/* on return to application from read request, readblock pointer points to */
/* a ccbread structure, which contains read data and last cursor position  */
struct ccbread {
	long   eventflag1 ; 	/* event/function keys, unchanged */
	long   eventflag2 ;
	long	eventflag3;
	long	eventflag4;
	long	eventflag5;
	int   fldflg ;		/* field edit keys to honor		*/
	unsigned char *buffaddr;/* pointer to returned read data        */
	short bufflen ;		/* number of characters actually read   */
	short vtabladdr ;	/* offset to start of validation table  */
	short miscflag ;	/* misc options, unchanged		*/
	char  opcode ;		/* read or update, unchanged		*/
	char  prompt ;		/* prompt character, unchanged		*/
	char  fill ;		/* fill character, unchanged		*/
	unsigned char  frow ;	/* field start row position, unchanged  */
	unsigned char  fcol ;	/* field start col position, unchanged  */
	unsigned char  crow ;	/* final cursor row position 		*/
	unsigned char  ccol ;	/* final cursor col position		*/
	unsigned char  numevents ;/* number of events of same type	*/
	short pad ;		/* unused, reserved for future          */
} ;
/* writeblock describes how each field in a request is to be written */
struct writeblock {
	char  opcode ; 	/* write, write status line, restore status line */
	char  error ; 	/* mostly syntax errors in block */
	short  miscflag;	/* misc options */
	unsigned char sgr_on, sgr_off;		/* sgr flags */
	unsigned char fg_color, bg_color;	/* color specification */
	unsigned char *buffaddr ;/* data buffer pointer  */
	short bufflen ;	/* length of data to write, this field  */
	unsigned char  row ; 	/* row address to start writing */
	unsigned char col ; 	/* column address to start writing */
	struct writeblock *nextblockaddr ; /* link to next field descriptor */
} ;

struct	sFE_get_parms {
	unsigned char max_row,max_col;
};

struct attributes {
	unsigned char disp ;
	unsigned char fg_color ;
	unsigned char bg_color ;
	unsigned char res ;
} ;

struct FE_screen {
	unsigned char maxrow ;
	unsigned char maxcol ;
	short	      flags ;
	unsigned char *data ;
	struct attributes *attr ;
} ;

/* eventflags1 flag definitions - which function keys to honor (1-32) */
#define FED_F1KEY ((long)1<<0)
#define FED_F2KEY ((long)1<<1)
#define FED_F3KEY ((long)1<<2)
#define FED_F4KEY ((long)1<<3)
#define FED_F5KEY ((long)1<<4)
#define FED_F6KEY ((long)1<<5)
#define FED_F7KEY ((long)1<<6)
#define FED_F8KEY ((long)1<<7)
#define FED_F9KEY ((long)1<<8)
#define FED_F10KEY ((long)1<<9)
#define FED_F11KEY ((long)1<<10)
#define FED_F12KEY ((long)1<<11)
#define FED_F13KEY ((long)1<<12)
#define FED_F14KEY ((long)1<<13)
#define FED_F15KEY ((long)1<<14)
#define FED_F16KEY ((long)1<<15)
#define FED_F17KEY ((long)1<<16)
#define FED_F18KEY ((long)1<<17)
#define FED_F19KEY ((long)1<<18)
#define FED_F20KEY ((long)1<<19)
#define FED_F21KEY ((long)1<<20)
#define FED_F22KEY ((long)1<<21)
#define FED_F23KEY ((long)1<<22)
#define FED_F24KEY ((long)1<<23)
#define FED_F25KEY ((long)1<<24)
#define FED_F26KEY ((long)1<<25)
#define FED_F27KEY ((long)1<<26)
#define FED_F28KEY ((long)1<<27)
#define FED_F29KEY ((long)1<<28)
#define FED_F30KEY ((long)1<<29)
#define FED_F31KEY ((long)1<<30)
#define FED_F32KEY ((long)1<<31)
/* eventflags3 flag definitions - which function keys to honor (33-64) */
#define FED_F33KEY ((long)1<<0)
#define FED_F34KEY ((long)1<<1)
#define FED_F35KEY ((long)1<<2)
#define FED_F36KEY ((long)1<<3)
#define FED_F37KEY ((long)1<<4)
#define FED_F38KEY ((long)1<<5)
#define FED_F39KEY ((long)1<<6)
#define FED_F40KEY ((long)1<<7)
#define FED_F41KEY ((long)1<<8)
#define FED_F42KEY ((long)1<<9)
#define FED_F43KEY ((long)1<<10)
#define FED_F44KEY ((long)1<<11)
#define FED_F45KEY ((long)1<<12)
#define FED_F46KEY ((long)1<<13)
#define FED_F47KEY ((long)1<<14)
#define FED_F48KEY ((long)1<<15)
#define FED_F49KEY ((long)1<<16)
#define FED_F50KEY ((long)1<<17)
#define FED_F51KEY ((long)1<<18)
#define FED_F52KEY ((long)1<<19)
#define FED_F53KEY ((long)1<<20)
#define FED_F54KEY ((long)1<<21)
#define FED_F55KEY ((long)1<<22)
#define FED_F56KEY ((long)1<<23)
#define FED_F57KEY ((long)1<<24)
#define FED_F58KEY ((long)1<<25)
#define FED_F59KEY ((long)1<<26)
#define FED_F60KEY ((long)1<<27)
#define FED_F61KEY ((long)1<<28)
#define FED_F62KEY ((long)1<<29)
#define FED_F63KEY ((long)1<<30)
#define FED_F64KEY ((long)1<<31)
/* eventflags4 flag definitions - which function keys to honor (65-96) */
#define FED_F65KEY ((long)1<<0)
#define FED_F66KEY ((long)1<<1)
#define FED_F67KEY ((long)1<<2)
#define FED_F68KEY ((long)1<<3)
#define FED_F69KEY ((long)1<<4)
#define FED_F70KEY ((long)1<<5)
#define FED_F71KEY ((long)1<<6)
#define FED_F72KEY ((long)1<<7)
#define FED_F73KEY ((long)1<<8)
#define FED_F74KEY ((long)1<<9)
#define FED_F75KEY ((long)1<<10)
#define FED_F76KEY ((long)1<<11)
#define FED_F77KEY ((long)1<<12)
#define FED_F78KEY ((long)1<<13)
#define FED_F79KEY ((long)1<<14)
#define FED_F80KEY ((long)1<<15)
#define FED_F81KEY ((long)1<<16)
#define FED_F82KEY ((long)1<<17)
#define FED_F83KEY ((long)1<<18)
#define FED_F84KEY ((long)1<<19)
#define FED_F85KEY ((long)1<<20)
#define FED_F86KEY ((long)1<<21)
#define FED_F87KEY ((long)1<<22)
#define FED_F88KEY ((long)1<<23)
#define FED_F89KEY ((long)1<<24)
#define FED_F90KEY ((long)1<<25)
#define FED_F91KEY ((long)1<<26)
#define FED_F92KEY ((long)1<<27)
#define FED_F93KEY ((long)1<<28)
#define FED_F94KEY ((long)1<<29)
#define FED_F95KEY ((long)1<<30)
#define FED_F96KEY ((long)1<<31)
/* eventflags5 flag definitions - which function keys to honor (97-128) */
#define FED_F97KEY ((long)1<<0)
#define FED_F98KEY ((long)1<<1)
#define FED_F99KEY ((long)1<<2)
#define FED_F100KEY ((long)1<<3)
#define FED_F101KEY ((long)1<<4)
#define FED_F102KEY ((long)1<<5)
#define FED_F103KEY ((long)1<<6)
#define FED_F104KEY ((long)1<<7)
#define FED_F105KEY ((long)1<<8)
#define FED_F106KEY ((long)1<<9)
#define FED_F107KEY ((long)1<<10)
#define FED_F108KEY ((long)1<<11)
#define FED_F109KEY ((long)1<<12)
#define FED_F110KEY ((long)1<<13)
#define FED_F111KEY ((long)1<<14)
#define FED_F112KEY ((long)1<<15)
#define FED_F113KEY ((long)1<<16)
#define FED_F114KEY ((long)1<<17)
#define FED_F115KEY ((long)1<<18)
#define FED_F116KEY ((long)1<<19)
#define FED_F117KEY ((long)1<<20)
#define FED_F118KEY ((long)1<<21)
#define FED_F119KEY ((long)1<<22)
#define FED_F120KEY ((long)1<<23)
#define FED_F121KEY ((long)1<<24)
#define FED_F122KEY ((long)1<<25)
#define FED_F123KEY ((long)1<<26)
#define FED_F124KEY ((long)1<<27)
#define FED_F125KEY ((long)1<<28)
#define FED_F126KEY ((long)1<<29)
#define FED_F127KEY ((long)1<<30)
#define FED_F128KEY ((long)1<<31)
/* eventflags2 bit definitions - which event keys to honor */
#define FED_PRINT_SCREEN 0x00000001
#define FED_REDRAW_SCREEN 0x00000002
#define FED_BAKSPAC	0x00000040
#define FED_UPARROW	0x00000080
#define FED_DNARROW	0x00000100
#define FED_LFARROW	0x00000200
#define FED_RTARROW	0x00000400
#define FED_INSCHAR	0x00000800
#define FED_DELCHAR	0x00001000
#define FED_ERASFLD	0x00002000
#define FED_SKIPKEY	0x00004000
#define FED_HOMEKEY	0x00010000
#define FED_ESCKEY	0x00020000
#define FED_PRINTKEY	0x00040000
#define FED_ERASINPUT	0x00080000
#define FED_ENTER	0x00100000
#define FED_BLNKGREY	0x02000000
#define FED_CMDKEY	0x04000000
#define FED_LFTFLD	0x08000000
#define FED_RITFLD	0x10000000
#define FED_BAKTAB	0x20000000
#define FED_TABKEY	0x40000000
#define FED_RTRNKEY	0x80000000

/* field flags bit definitions: if set, specified key is honored */
#define FED_EVENTREQ	0x00000001 /* only event key terminates read */
#define FED_MDT 	0x00000002 /* modified data tag 	     */
#define FED_NOECHO	0x00000004 /* do not echo read data	     */
#define FED_MULTIVENT	0x00000008 /* accept multiple events	     */
#define FED_OVERTYPE	0x00000010 /* allow overtype on field full   */
#define FED_BS_DESTRUCT 0x00000020 /* backspace is destructive	     */
#define FED_SKIPF	0x00000040 /* honor skip function	     */
#define FED_ERASFLDF	0x00000080 /* honor erase field function     */
#define FED_DELCHARF	0x00000100 /* honor delete char function     */
#define FED_INSCHARF	0x00000200 /* honor insert char function     */
#define FED_BSCHARF	0x00000400 /* honor backspace function	     */
#define FED_CURHOMEF	0x00000800 /* honor home cursor function     */
#define FED_DWNAROWF	0x00001000 /* down arrow function	     */
#define FED_UPAROWF	0x00002000 /* up arrow function 	     */
#define FED_RIGHTAROWF	0x00004000 /* right arrow key		     */
#define FED_LEFTAROWF	0x00008000 /* left arrow key		     */
#define FED_RTMARGIN	0x00010000 /* limit INS/DEL to right margin  */
#define FED_INSRTMOD	0x00020000 /* don't even ask!!		     */
#define FED_SKIPLAST    0x00040000 /* skip does not delete last char */
				   /* in a full field.               */

/* miscellaneous flags definitions:  describes misc options read/write */
#define FED_ERASEOS	0x0200 	/* erase to end of screen  */
#define FED_ERASEOL	0x0400	/* erase to end of line  */
#define FED_BEEP	0x0800	/* honk the horn      */
#define FED_SOLIDC	0x4000  /* make cursor solid  */
#define FED_BLINKC	0x8000	/* blink the cursor */
#define FED_ESMASK	0x0600	/* erase screen mask */
#define FED_SCROLL	0x0001	/* Scroll display */ 

/* SGR flags definitions:  describes SGR options read/write */
#define FED_SGR_ENABLE	0x80	/* SGR change requested */
#define FED_SGR_MASK	0xf	/* mask to extract sgr bits */
#define FED_BLINKF	8	/* blink the field  */
#define FED_UNDRLINE	4	/* underline the data displayed */
#define FED_REVERSE	2	/* display in reverse video */
#define FED_HIGHINT	1	/* display in high intensity */
/*
	The following macro's can be used to set the sgr bits to the 
	proper values in order to set the sgr to only those bits that
	are specified.
*/
#define set_rd_sgr(a,b) (((struct readblock *)a)->sgr_on = FED_SGR_ENABLE+b),\
	(((struct readblock *)a)->sgr_off = FED_SGR_ENABLE + (FED_SGR_MASK & ~b))
#define set_wrt_sgr(a,b) (((struct writeblock *)a)->sgr_on = FED_SGR_ENABLE+b),\
	(((struct writeblock *)a)->sgr_off = FED_SGR_ENABLE + (FED_SGR_MASK & ~b))

/* Color flag definitions: Used to specify color (if supported) */
#define FED_COLOR_ENABLE 0x80	/* color change requested */
typedef	enum {BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE} color_enum;

/* validation table flag:  if set, table specifies invalid characters */
#define VALID		0x00	/* only chars in range are valid */
#define NVALID		0x01 	/* chars in ranges are invalid */
#define ALTABLE		0x02	/* use alternate bitmap table */
#define EVENT_CHAR_BIAS	0x1000  /* bias used to report char events */

struct alttable {
	short length ;
	short flags ;
	unsigned long bitmap[16] ;
} ;
#define VBITS_IGNORE 0
#define VBITS_EVENT 1
#define VBITS_DATA 2

/* FE_open parameter flag definitions */
typedef enum {no_sgr_opt,
		no_cursor_opt, 
		no_buf_wrts, 
		no_raw_wrts,
		sticky_margin,
		nodisplay_cursor,
		noscroll_image,
		scrnimage,
		last_flag} flag_pos;

/* mapped event key return value:  if an event key is pressed, and the */
/* flags specify that it is to be honored in this request, the read    */
/* terminates and the corresponding value is returned		       */
#define FED_PRINTSCR_EVENT 0x01 /* returned only if screen image is not */
#define FED_REDRAWSCR_EVENT 0x02 /* being kept by field edit library	*/
#define	FED_F1EVENT	0x81
#define FED_F2EVENT	0x82
#define FED_F3EVENT	0x83
#define FED_F4EVENT	0x84
#define FED_F5EVENT	0x85
#define FED_F6EVENT	0x86
#define FED_F7EVENT	0x96
#define FED_F8EVENT	0x97
#define FED_F9EVENT	0x80
#define FED_F10EVENT	0x9a
#define FED_F11EVENT	0x9c
#define FED_F12EVENT	0x9d
#define FED_F13EVENT	0x9e
#define FED_F14EVENT	0x9f
#define FED_F15EVENT	0xe0
#define FED_F16EVENT	0xe1
#define FED_F17EVENT	0xe2
#define FED_F18EVENT	0xe3
#define FED_F19EVENT	0xe4
#define FED_F20EVENT	0xe5
#define FED_F21EVENT	0xe6
#define FED_F22EVENT	0xe7
#define FED_F23EVENT	0xe8
#define FED_F24EVENT	0xe9
#define FED_ENTREVENT	0x93	/* event from enter key  */
#define FED_CMDEVENT	0x98	/* event from command key */
#define FED_PRTEVENT	0x99	/* event from print key  */
#define FED_RTRNEVENT	0x8d	/* event from return key */
#define FED_ARUPEVENT	0x95	/* event from up arrow */
#define FED_ARDNEVENT	0x8a	/* event from down arrow */
#define FED_ARLFEVENT	0x88	/* event from left arrow */
#define FED_ARRTEVENT	0x92	/* event from right arrow */
#define FED_RTFLDEVENT	0x87	/* event from right field key */
#define FED_LTFLDEVENT	0x94	/* event from left field key */
#define FED_TABEVENT	0x89	/* event from tab key */
#define FED_BKTABEVENT	0xef	/* event from back tab key */
#define FED_BGREYEVENT	0x8f	/* event from blank grey key */
#define FED_ERNPTEVENT	0x8e	/* event from erase input key */
#define FED_SKIPEVENT	0x8b	/* event from skip key */
#define FED_ESCEVENT	0x9b	/* event from shifted escape key */
#define FED_HOMEVENT	0x8c	/* event from home key */
#define FED_ERSFLDEVENT	0x7f	/* event from erase field key */
#define FED_DELCHREVENT	0x90	/* event from delete char key */
#define FED_INSCHREVENT	0x91	/* event from insert char key */
#define FED_BAKSPEVENT  0xdf	/* event from backaspace key  */

#define FED_F25EVENT (0xf0 + 0)
#define FED_F26EVENT (0xf0 + 1)
#define FED_F27EVENT (0xf0 + 2)
#define FED_F28EVENT (0xf0 + 3)
#define FED_F29EVENT (0xf0 + 4)
#define FED_F30EVENT (0xf0 + 5)
#define FED_F31EVENT (0xf0 + 6)
#define FED_F32EVENT (0xf0 + 7)
#define FED_F33EVENT (0xf0 + 8)
#define FED_F34EVENT (0xf0 + 9)
#define FED_F35EVENT (0xf0 + 10)
#define FED_F36EVENT (0xf0 + 11)
#define FED_F37EVENT (0xf0 + 12)
#define FED_F38EVENT (0xf0 + 13)
#define FED_F39EVENT (0xf0 + 14)
#define FED_F40EVENT (0xf0 + 15)
#define FED_F41EVENT (0xf0 + 16)
#define FED_F42EVENT (0xf0 + 17)
#define FED_F43EVENT (0xf0 + 18)
#define FED_F44EVENT (0xf0 + 19)
#define FED_F45EVENT (0xf0 + 20)
#define FED_F46EVENT (0xf0 + 21)
#define FED_F47EVENT (0xf0 + 22)
#define FED_F48EVENT (0xf0 + 23)
#define FED_F49EVENT (0xf0 + 24)
#define FED_F50EVENT (0xf0 + 25)
#define FED_F51EVENT (0xf0 + 26)
#define FED_F52EVENT (0xf0 + 27)
#define FED_F53EVENT (0xf0 + 28)
#define FED_F54EVENT (0xf0 + 29)
#define FED_F55EVENT (0xf0 + 30)
#define FED_F56EVENT (0xf0 + 31)
#define FED_F57EVENT (0xf0 + 32)
#define FED_F58EVENT (0xf0 + 33)
#define FED_F59EVENT (0xf0 + 34)
#define FED_F60EVENT (0xf0 + 35)
#define FED_F61EVENT (0xf0 + 36)
#define FED_F62EVENT (0xf0 + 37)
#define FED_F63EVENT (0xf0 + 38)
#define FED_F64EVENT (0xf0 + 39)
#define FED_F65EVENT (0xf0 + 40)
#define FED_F66EVENT (0xf0 + 41)
#define FED_F67EVENT (0xf0 + 42)
#define FED_F68EVENT (0xf0 + 43)
#define FED_F69EVENT (0xf0 + 44)
#define FED_F70EVENT (0xf0 + 45)
#define FED_F71EVENT (0xf0 + 46)
#define FED_F72EVENT (0xf0 + 47)
#define FED_F73EVENT (0xf0 + 48)
#define FED_F74EVENT (0xf0 + 49)
#define FED_F75EVENT (0xf0 + 50)
#define FED_F76EVENT (0xf0 + 51)
#define FED_F77EVENT (0xf0 + 52)
#define FED_F78EVENT (0xf0 + 53)
#define FED_F79EVENT (0xf0 + 54)
#define FED_F80EVENT (0xf0 + 55)
#define FED_F81EVENT (0xf0 + 56)
#define FED_F82EVENT (0xf0 + 57)
#define FED_F83EVENT (0xf0 + 58)
#define FED_F84EVENT (0xf0 + 59)
#define FED_F85EVENT (0xf0 + 60)
#define FED_F86EVENT (0xf0 + 61)
#define FED_F87EVENT (0xf0 + 62)
#define FED_F88EVENT (0xf0 + 63)
#define FED_F89EVENT (0xf0 + 64)
#define FED_F90EVENT (0xf0 + 65)
#define FED_F91EVENT (0xf0 + 66)
#define FED_F92EVENT (0xf0 + 67)
#define FED_F93EVENT (0xf0 + 68)
#define FED_F94EVENT (0xf0 + 69)
#define FED_F95EVENT (0xf0 + 70)
#define FED_F96EVENT (0xf0 + 71)
#define FED_F97EVENT (0xf0 + 72)
#define FED_F98EVENT (0xf0 + 73)
#define FED_F99EVENT (0xf0 + 74)
#define FED_F100EVENT (0xf0 + 75)
#define FED_F101EVENT (0xf0 + 76)
#define FED_F102EVENT (0xf0 + 77)
#define FED_F103EVENT (0xf0 + 78)
#define FED_F104EVENT (0xf0 + 79)
#define FED_F105EVENT (0xf0 + 80)
#define FED_F106EVENT (0xf0 + 81)
#define FED_F107EVENT (0xf0 + 82)
#define FED_F108EVENT (0xf0 + 83)
#define FED_F109EVENT (0xf0 + 84)
#define FED_F110EVENT (0xf0 + 85)
#define FED_F111EVENT (0xf0 + 86)
#define FED_F112EVENT (0xf0 + 87)
#define FED_F113EVENT (0xf0 + 88)
#define FED_F114EVENT (0xf0 + 89)
#define FED_F115EVENT (0xf0 + 90)
#define FED_F116EVENT (0xf0 + 91)
#define FED_F117EVENT (0xf0 + 92)
#define FED_F118EVENT (0xf0 + 93)
#define FED_F119EVENT (0xf0 + 94)
#define FED_F120EVENT (0xf0 + 95)
#define FED_F121EVENT (0xf0 + 96)
#define FED_F122EVENT (0xf0 + 97)
#define FED_F123EVENT (0xf0 + 98)
#define FED_F124EVENT (0xf0 + 99)
#define FED_F125EVENT (0xf0 + 100)
#define FED_F126EVENT (0xf0 + 101)
#define FED_F127EVENT (0xf0 + 102)
#define FED_F128EVENT (0xf0 + 103)

/* FE_abort flags definitions */
#define ABORT_READ	1
#define ABORT_WRITE	2
#define ABORT_OPEN	4
#define ABORT_CLOSE	8

/*                                                                        */
/**************************************************************************/
/*                 CCB and Field edit errors                              */
/*      ********************  WARNING  *****************************      */
/*      These error symbols and numbers may be removed in a future        */
/*      release of field edit. The error symbols following these will be  */
/*      the replacement symbols and error numbers. It is recommended that */
/*      those symbols be used.                                            */
/**************************************************************************/
/*                                                                        */
/* These symbols are commented out and here for reference to the original */
/* names.  You should be using names of the following set of symbols.	  */
/*
#define      EBADFD		50
#define      ENOFETBL    	51
#define      EBADBLOCK  	52
#define      EBADOP		53
#define      EBADBUFF   	54
#define      EBADLEN		55
#define      EBADCURS   	56
#define      EFLGERR		57
#define      EVTABLE		58
#define      EBADCNT		59
#define      ERDTMO		60
#define      EFELIB_DATED	61
#define      ECCB_DATED 	62
#define      ENOIMAGE    	63
*** END of commented out symbol names   */
/*                                                                        */
/**************************************************************************/
/*                                                                        */
/* New ccb and field edit errors                                          */
/*                                                                        */
/**************************************************************************/
/*                                                                        */
#define EFE_BADFD	50	/* invalid FD specified */
#define EFE_NOFETBL	51	/* no Field edit table avail. */
#define	EFE_BADBLOCK	52	/* invalid field edit read block	*/
#define	EFE_BADOP	53	/* invalid field edit opcode 		*/
#define	EFE_BADBUFF	54	/* field edit buffer address error 	*/
#define	EFE_BADLEN	55	/* field edit buffer length error	*/
#define	EFE_BADCURS	56	/* cursor positioning error		*/
#define	EFE_FLGERR	57	/* field edit event flag error		*/
#define	EFE_VTABLE	58	/* validation table error		*/
#define EFE_BADCNT	59	/* wrtblk count not consistant with linkage */
#define EFE_RDTMO	60	/* read timeout period elapsed */
#define EFE_FELIB_DATED	61	/* felib code older version than ccb code */
#define EFE_CCB_DATED	62	/* ccb code older version than felib code */
#define EFE_NOIMAGE	63	/* screen image not being kept	*/
