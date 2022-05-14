/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char ttold_h[] = "@(#)ttold.h	1.3 (TI) 86/02/04";
#endif	SCCSID

/* @(#)ttold.h	1.1	UNIX System V/68 */
struct	sgttyb {
	char	sg_ispeed;
	char	sg_ospeed;
	char	sg_erase;
	char	sg_kill;
	int	sg_flags;
};

/* modes */
#define	O_HUPCL	01
#define	O_XTABS	02
#define	O_LCASE	04
#define	O_ECHO	010
#define	O_CRMOD	020
#define	O_RAW	040
#define	O_ODDP	0100
#define	O_EVENP	0200
#define	O_NLDELAY	001400
#define	O_NL1	000400
#define	O_NL2	001000
#define	O_TBDELAY	002000
#define	O_NOAL	004000
#define	O_CRDELAY	030000
#define	O_CR1	010000
#define	O_CR2	020000
#define	O_VTDELAY	040000
#define	O_BSDELAY	0100000

#define	tIOC	('t'<<8)
#define	TIOCGETP	(tIOC|8)
#define	TIOCSETP	(tIOC|9)
