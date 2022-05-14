/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char tty_h[] = "@(#)tty.h	1.8 (TI) 90/02/08";
#endif	SCCSID

/*	@(#)tty.h	1.1	UNIX System V/68 */
/*
 * A clist structure is the head of a linked list queue of characters.
 * The routines getc* and putc* manipulate these structures.
 */

struct clist {
	int	c_cc;		/* character count */
	struct cblock *c_cf;	/* pointer to first */
	struct cblock *c_cl;	/* pointer to last */
};

/* Macro to find clist structure given pointer into it	*/
/*
 *  This macro has been changed to allow two discontiguous arrays of
 *  cblocks to be used.  This is required to support TCP/IP virtual
 *  terminals which allocate the addcfree array of cblocks when TCP/IP
 *  is started.
 *						web
 *
#define CMATCH(pointer)		(char *)(cfree + (pointer - cfree))
*/
#define CMATCH(pointer) \
	(addcfree && (pointer >= addcfree) && (pointer < addcfend)) ? \
	(char *)(addcfree + (pointer - addcfree)) : \
	(char *)(cfree + (pointer - cfree))

/* Character control block for interrupt level control	*/

struct ccblock {
	caddr_t	c_ptr;		/* buffer address	*/
	ushort	c_count;	/* character count	*/
	ushort	c_size;		/* buffer size		*/
};

/*
 * A tty structure is needed for each UNIX character device that
 * is used for normal terminal IO.
 */
#define	NCC	8
struct tty {
	struct	clist t_rawq;	/* raw input queue */
	struct	clist t_canq;	/* canonical queue */
	struct	clist t_outq;	/* output queue */
	struct	ccblock	t_tbuf;	/* tx control block */
	struct	ccblock t_rbuf;	/* rx control block */
	int	(* t_proc)();	/* routine for device functions */
	ushort	t_iflag;	/* input modes */
	ushort	t_oflag;	/* output modes */
	ushort	t_cflag;	/* control modes */
	ushort	t_lflag;	/* line discipline modes */
	short	t_state;	/* internal state */
	short	t_pgrp;		/* process group name */
	char	t_line;		/* line discipline */
	char	t_delct;	/* delimiter count */
	char	t_term;		/* terminal type */	
	char	t_tmflag;	/* terminal flags */
	char	t_col;		/* current column */
	char	t_row;		/* current row */
	char	t_vrow;		/* variable row */
	char	t_lrow;		/* last physical row */
	char	t_hqcnt;	/* no. high queue packets on t_outq */	
	char	t_dstat;	/* used by terminal handlers
						and line disciplines */
	unsigned char	t_cc[NCC];	/* settable control chars */
	struct	windef *t_wp;	/* pointer to window structure */
	struct	keybd *t_kp;	/* pointer to keyboard structure */
	short	t_ms_x;		/* needed for mouse */
	short	t_ms_y;		/* " " " " " " " "  */
	lock_t	tpsema;		/* for locking the tty struct */
	sema_t	sleeper;	/* for sleeping on the tty struct */
};

/*
 * Used by mouse line discipline.
 */
#define	t_ms_bs	t_vrow
#define	t_ms_sc	t_lrow
#define	t_ms_by	t_dstat

/*
 * The structure of a clist block
 */
#define	CLSIZE	64
struct cblock {
	struct cblock *c_next;
	char	c_first;
	char	c_last;
	short	c_padding;
	char	c_data[CLSIZE];
};

extern struct cblock cfree[];
extern struct cblock *addcfree, *addcfend;
extern struct cblock * getcb();
extern struct cblock * getcf();
extern struct clist ttnulq;

struct chead {
	struct cblock *c_next;
	int	c_size;
	int	c_flag;
};
extern struct chead cfreelist;

struct inter {
	int	cnt;
};

#define	QESC	0200	/* queue escape */
#define	HQEND	01	/* high queue end */

#define	TTIPRI	28
#define	TTOPRI	29

/* limits */
extern int ttlowat[], tthiwat[];
#define	TTYHOG	256
#define	TTXOLO	60
#define	TTXOHI	180
#define	TTECHI	80

/* Hardware bits */
#define	DONE	0200
#define	IENABLE	0100
#define	OVERRUN	040000
#define	FRERROR	020000
#define	PERROR	010000

/* Internal state */
#define	TIMEOUT	01		/* Delay timeout in progress */
#define	WOPEN	02		/* Waiting for open to complete */
#define	ISOPEN	04		/* Device is open */
#define	TBLOCK	010
#define	CARR_ON	020		/* Software copy of carrier-present */
#define	BUSY	040		/* Output in progress */
#define	OASLP	0100		/* Wakeup when output done */
#define	IASLP	0200		/* Wakeup when input done */
#define	TTSTOP	0400		/* Output stopped by ctl-s */
#define	EXTPROC	01000		/* External processing */
#define	TACT	02000
#define	CLESC	04000		/* Last char escape */
#define	RTO	010000		/* Raw Timeout */
#define	TTIOW	020000
#define	TTXON	040000
#define	TTXOFF	0100000

/* l_output status */
#define	CPRES	0100000

/* device commands */
#define	T_OUTPUT	0
#define	T_TIME		1
#define	T_SUSPEND	2
#define	T_RESUME	3
#define	T_BLOCK		4
#define	T_UNBLOCK	5
#define	T_RFLUSH	6
#define	T_WFLUSH	7
#define	T_BREAK		8
#define	T_INPUT		9
/* added for rsd stuff */
#define	T_F1		10
#define T_F2		11
#define	T_F3		12
#define	T_F4		13
#define	T_F5		15
#define T_F6		16
#define	T_F7		17
#define	T_F8		18

/*
 * Terminal flags (set in t_tmflgs).
 */

#define SNL	1		/* non-standard new-line needed */
#define ANL	2		/* automatic new-line */
#define LCF	4		/* Special treatment of last col, row */
#define TERM_CTLECHO	010	/* Echo terminal control characters */
#define TERM_INVIS	020	/* do not send escape sequences to user */
#define QLOCKB		040	/* high queue locked for base level */
#define QLOCKI		0100	/* high queue locked for interrupts */
#define	TERM_BIT 0200		/* Bit reserved for terminal drivers. */
				/* Usually used to indicate that an esc*/
				/* character has arrived and that the  */
				/* next character is special.          */
				/* This bit is the same as the TM_SET  */
				/* bit which may never be set by a user*/

/* The following two definitions were added to TCP/IP virtual terminals */
#define	L_BUF	0
#define	L_BREAK	3
