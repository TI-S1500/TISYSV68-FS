/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char termio_h[] = "@(#)termio.h	1.11 (TI) 91/04/12 3/14/93";
#endif	SCCSID

/* @(#)termio.h	1.1	UNIX System V/68 */
#define	NCC	8

/* control characters */
#define	VINTR	0
#define	VQUIT	1
#define	VERASE	2
#define	VKILL	3
#define	VEOF	4
#define	VEOL	5
#define	VEOL2	6
#define	VMIN	4
#define	VTIME	5
/* Added for TCP/IP virtual terminals */
#define	VSWTCH	7

#define	CNUL	0
#define	CDEL	0377
/* default control chars */
#define	CESC	'\\'
#define	CINTR	03	/* cntl c */
#define	CQUIT	034	/* cntl \ or cntl | */
#define	CERASE	010	/* BS, cntl h */
#define	CKILL	025	/* cntl u */
#define	CEOF	04	/* cntl d */
#define	CSTART	021	/* cntl q */
#define	CSTOP	023	/* cntl s */
#define	CSWTCH	032	/* cntl z */

/* Added for TCP/IP virtual terminals */
#define	CNSWTCH	0

/* input modes */
#define	IGNBRK	0000001
#define	BRKINT	0000002
#define	IGNPAR	0000004
#define	PARMRK	0000010
#define	INPCK	0000020
#define	ISTRIP	0000040
#define	INLCR	0000100
#define	IGNCR	0000200
#define	ICRNL	0000400
#define	IUCLC	0001000
#define	IXON	0002000
#define	IXANY	0004000
#define	IXOFF	0010000

/* output modes */
#define	OPOST	0000001
#define	OLCUC	0000002
#define	ONLCR	0000004
#define	OCRNL	0000010
#define	ONOCR	0000020
#define	ONLRET	0000040
#define	OFILL	0000100
#define	OFDEL	0000200
#define	NLDLY	0000400
#define	NL0	0
#define	NL1	0000400
#define	CRDLY	0003000
#define	CR0	0
#define	CR1	0001000
#define	CR2	0002000
#define	CR3	0003000
#define	TABDLY	0014000
#define	TAB0	0
#define	TAB1	0004000
#define	TAB2	0010000
#define	TAB3	0014000
#define	BSDLY	0020000
#define	BS0	0
#define	BS1	0020000
#define	VTDLY	0040000
#define	VT0	0
#define	VT1	0040000
#define	FFDLY	0100000
#define	FF0	0
#define	FF1	0100000

/* control modes */
#define	CBAUD	0000017
#define	B0	0
#define	B50	0000001
#define	B75	0000002
#define	B110	0000003
#define	B134	0000004
#define	B150	0000005
#define	B200	0000006
#define	B300	0000007
#define	B600	0000010
#define	B1200	0000011
#define	B1800	0000012
#define	B2400	0000013
#define	B4800	0000014
#define	B9600	0000015
#define	B19200	0000016
#define	B38400	0000017
#define	EXTA	B19200
#define	EXTB	B38400
#define	CSIZE	0000060
#define	CS5	0
#define	CS6	0000020
#define	CS7	0000040
#define	CS8	0000060
#define	CSTOPB	0000100
#define	CREAD	0000200
#define	PARENB	0000400
#define	PARODD	0001000
#define	HUPCL	0002000
#define	CLOCAL	0004000
#define	KEYTRANS 010000		/* added for rsd stuff */

/* line discipline 0 modes */
#define	ISIG	0000001
#define	ICANON	0000002
#define	XCASE	0000004
#define	ECHO	0000010
#define	ECHOE	0000020
#define	ECHOK	0000040
#define	ECHONL	0000100
#define	NOFLSH	0000200

#define	SSPEED	7	/* default speed: 300 baud */

/*
 * Ioctl control packet
 */
struct termio {
	unsigned short	c_iflag;	/* input modes */
	unsigned short	c_oflag;	/* output modes */
	unsigned short	c_cflag;	/* control modes */
	unsigned short	c_lflag;	/* line discipline modes */
	char	c_line;		/* line discipline */
	unsigned char	c_cc[NCC];	/* control chars */
};
#define	IOCTYPE	0xff00

#define	TIOC	('T'<<8)
#define	TCGETA	(TIOC|1)
#define	TCSETA	(TIOC|2)
#define	TCSETAW	(TIOC|3)
#define	TCSETAF	(TIOC|4)
#define	TCSBRK	(TIOC|5)
#define	TCXONC	(TIOC|6)
#define	TCFLSH	(TIOC|7)
#define	TCDSET	(TIOC|32)
#define	TIOCGWINSZ	(TIOC|104)
#define	TIOCSWINSZ	(TIOC|103)

#define	LDIOC	('D'<<8)
#define	LDOPEN	(LDIOC|0)
#define	LDCLOSE	(LDIOC|1)
#define	LDCHG	(LDIOC|2)
#define	LDGETT	(LDIOC|8)
#define	LDSETT	(LDIOC|9)

#define PRIOC	('P'<<8)		/* invokes print screen */
#define PRTSCRN (PRIOC|0)

/* window ioctls, see <wio.h>	*/
#define WIOCMAKE	(('w'<<8)|0)	/* make a window		*/
#define WIOCINIT	(('w'<<8)|1)	/* initialize window		*/
#define WIOCDRAW	(('w'<<8)|2)	/* draw window			*/
#define WIOCERAS	(('w'<<8)|3)	/* erase window			*/
#define WIOCGETD	(('w'<<8)|4)	/* get window data		*/
#define WIOCSETD	(('w'<<8)|5)	/* set window data		*/
#define WIOCLFNT	(('w'<<8)|6)	/* load window font		*/
#define WIOCSFNT	(('w'<<8)|7)	/* set window font		*/
#define WIOCCFNT	(('w'<<8)|8)	/* clear window font		*/
#define WIOCGFNT	(('w'<<8)|9)	/* get window font data		*/
#define WIOCRDMS	(('w'<<8)|10)	/* read window mouse		*/
#define WIOCGRSD	(('w'<<8)|11)	/* get raster-display data	*/
#define WIOCSTAT	(('w'<<8)|12)	/* get window status flags	*/
#define WIOCLABL	(('w'<<8)|13)	/* get window label		*/
#define WIOCRACD	(('w'<<8)|14)	/* get window row/column data	*/
#define WIOCSKBD	(('w'<<8)|15)	/* set keyboard window		*/
#define WIOCSRSD	(('w'<<8)|16)	/* set raster-display uflags	*/
#define WIOCARSD	(('w'<<8)|17)	/* NuBus attach to rsd (vcmem)	*/

/* vc driver ioctls */
#define VIOCSTLINE	(('v'<<8)|0)	/* change the line discipline	*/

/*
 * Terminal types
 */
#define	TERM_NONE	0	/* tty */
#define	TERM_TEC	1	/* TEC Scope */
#define	TERM_V61	2	/* DEC VT61 */
#define	TERM_V10	3	/* DEC VT100 */
#define	TERM_TEX	4	/* Tektronix 4023 */
#define	TERM_D40	5	/* TTY Mod 40/1 */
#define	TERM_H45	6	/* Hewlitt-Packard 45 */
#define	TERM_D42	7	/* TTY Mod 40/2B */

/*
 * Terminal flags
 */
#define TM_NONE		0000	/* use default flags */
#define TM_SNL		0001	/* special newline flag */
#define TM_ANL		0002	/* auto newline on column 80 */
#define TM_LCF		0004	/* last col of last row special */
#define TM_CECHO	0010	/* echo terminal cursor control */
#define TM_CINVIS	0020	/* do not send esc seq to user */
#define TM_SET		0200	/* must be on to set/res flags */

/*
 * structure of ioctl arg for LDGETT and LDSETT
 */
struct	termcb	{
	char	st_flgs;	/* term flags */
	char	st_termt;	/* term type */
	char	st_crow;	/* gtty only - current row */
	char	st_ccol;	/* gtty only - current col */
	char	st_vrow;	/* variable row */
	char	st_lrow;	/* last row */
};

/*
*	modem control ioctl defines, per SVR4 termios.h
*/
#define tIOC		('t'<<8)
#define TIOCMSET	(tIOC|26) /* set new signal mask */
#define TIOCMBIS	(tIOC|27) /* set bitwise */
#define TIOCMBIC	(tIOC|28) /* clear bitwise */
#define TIOCMGET	(tIOC|29) /* get current settings */
#define TIOCM_LE	0001 /* "line enable" (?), unsupported */
#define TIOCM_DTR	0002 /* data terminal ready, output sig */
#define TIOCM_RTS	0004 /* four-channel only */
#define TIOCM_ST	0010 /* unsupported */
#define TIOCM_SR	0020 /* unsupported */
#define TIOCM_CTS	0040 /* four-channel only */
#define TIOCM_CAR	0100 /* four-channel only */
#define TIOCM_CD	TIOCM_CAR /* four-channel only */
#define TIOCM_RNG	0200 /* ring indicator, four-channel only */
#define TIOCM_RI	TIOCM_RNG /* ring indicator, four-channel only */
#define TIOCM_DSR	0400 /* data set ready, input sig */
/* NOTE: these last two are extensions beyond SVR4 SVID, and thus may */
/* have to change if AT&T defines these bits for something else */
/* They are only supported on the 4-channel anyway */
#define TIOCM_SRTS	01000 /* secondary RTS, four-channel only */
#define TIOCM_SI	02000 /* speed indicator */