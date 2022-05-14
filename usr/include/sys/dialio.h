/*
*	(C) COPYRIGHT,	 TEXAS INSTRUMENTS INCORPORATED,   1986.   ALL
*	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS  INCORPORATED.
*	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
*	TO RESTRICTIONS SET FORTH IN TI'S  PROGRAM  LICENSE  AGREEMENT
*	AND ASSOCIATED DOCUMENTS.
*
*/

/* @(#)dialio.h	1.3 90/02/23 */

/* dial ioctl argument structure */
struct dialio {
	unsigned char speed;		/* speed */
					/* 0x00=300 */
					/* 0x01=1200 */
					/* 0x02=2400 */
					/* 0x03=4800 */
					/* 0x04=9600 */
	unsigned char leng;		/* data length */
					/* 0x00=5 bit */
					/* 0x08=6 bit */
					/* 0x10=7 bit */
					/* 0x18=8 bit */
	unsigned char stop;		/* stop bits */
					/* 0x00=1 stop bit */
					/* 0x20=1.5 stop bits */
					/* 0x40=2 stop bits */
	unsigned char par;		/* parity */
					/* 0x00=no parity */
					/* 0x80=even */
					/* 0xC0=odd */
	unsigned char time;		/* read/write timout in seconds */
	unsigned char insigs;		/* input signals */
					/* bit 0,1 = reserved */
					/*	 2 = DCD level */
					/*	 3 = DSR level */
					/*	 4 = CTS level */
					/*	 5 = DCD gone inactive */
					/*	 6 = DSR gone active   */
					/*	 7 = CTS gone inactive */
	};

/* dial ioctl commands: */
#define DIALGET 	(('D'<<8)|1)    /* get current dialio block */
#define DIALSET 	(('D'<<8)|2)    /* set new dialio parameters */
#define DIALTMO 	(('D'<<8)|3)    /* set new timeout */
#define DIALRST 	(('D'<<8)|4)    /* reset the modem */

/* default information: */
#define SPEED		2		/* 2400 */
#define CHARL		0x10		/* 7 bit character */
#define STOPB		0x00		/* 1 stop bit */
#define PARITY		0xC0		/* odd parity */

/* baud rates */
#define BAUD300		0x00		/* 300 baud	*/
#define BAUD1200	0x01		/* 1200 baud	*/
#define BAUD2400	0x02		/* 2400 baud	*/
#define BAUD4800	0x03		/* 4800 baud	*/
#define BAUD9600	0x04		/* 9600 baud	*/

/* number of data bits per character */
#define BIT5		0x00		/* 5 bit chars	*/
#define BIT6		0x08		/* 6 bit chars  */
#define BIT7		0x10		/* 7 bit chars	*/
#define BIT8		0x18		/* 8 bit chars	*/

/* number of stop bits per character */
#define STOP1		0x00		/* 1 stop bit	*/
#define STOP1_5		0x20		/* 1.5 stop bit */
#define STOP2		0x40		/* 2 stop bits	*/

/* type of parity */
#define NO_PARITY	0x00		/* no parity	*/
#define EVEN_PARITY	0x80		/* even parity	*/
#define ODD_PARITY	0xc0		/* odd parity	*/

/* line transition status */
#define CTST		0x80		/* CTS gone inactive */
#define DSRT		0x40		/* DSR gone active   */
#define DCDT		0x20		/* DCD gone inactive */

/* line levels */
#define CTSLVL		0x10		/* CTS high */
#define DSRLVL		0x08		/* DSR high */
#define DCDLVL		0x04		/* DCD high */
