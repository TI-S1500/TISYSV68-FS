/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ifdef	SCCSID
static char tty_h[] = " @(#)tty.h	1.14 (TI) 92/09/28";
#endif	SCCSID

/*
 * Enable the GNU extensions if this is the GNU C compiler
 */

#ifdef __GNUC__
#pragma EXTENSIONS
#endif

/*
 * A clist structure is the head of a linked list queue of characters.
 * The routines getc* and putc* manipulate these structures.
 */

#define spltty() spl6()
struct clist {
	int	c_cc;		/* character count */
	struct cblock *c_cf;	/* pointer to first */
	struct cblock *c_cl;	/* pointer to last */
	lock_t	sema;		/* Clist semaphore */
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

/* sema_t defines */
#define	NTTY_SEMA	5	/* Number of semaphores	*/
#define	OPEN_SEMA	0	
#define	CLOSE_SEMA	1	
#define	READ_SEMA	2	
#define	WRITE_SEMA	3	
#define	IOCTL_SEMA	4	

/* drvrctl defines */
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
	sema_t	tty_sema[NTTY_SEMA];	/* TTY semaphores	*/
	lock_t	tty_lock;	/* for locking the TTY struct	*/
	int	x;		/* SPL value			*/
	uint	t_state;	/* internal state 		*/
	ushort	t_iflag;	/* input modes 			*/
	ushort	t_oflag;	/* output modes 		*/
	ushort	t_cflag;	/* control modes 		*/
	ushort	t_lflag;	/* line discipline modes 	*/
	short	t_pgrp;		/* process group name 		*/
	char	t_line;		/* line discipline 		*/
	char	t_delct;	/* delimiter count 		*/
	char	t_term;		/* terminal type 		*/	
	char	t_tmflag;	/* terminal flags 		*/
	char	t_col;		/* current column 		*/
	char	t_row;		/* current row 			*/
	char	t_vrow;		/* variable row 		*/
	char	t_lrow;		/* last physical row 		*/
	char    t_hqcnt;        /* no. high queue packets on t_outq */
	char	t_dstat;	/* used by terminal handlers
						and line disciplines */
	unsigned char	t_cc[NCC];	/* settable control chars */
	unsigned long 	padding[6];	/* Extra space for future use */
	short		t_dvrctl;
	struct feheader *fe_header;	/* pointer to fe header */
	int		fe_opcode;	/* fe opcode */
	union{
		struct ccbread 	 *rb;	/* pointer to user fe/tx read */
		struct editblock *eb;
	}fe_read_ptr;
	int		fe_mode;	/* mode (ie. NO_DELAY) */
	int		fe_timeout_id;	/* timeout id	*/
	char		*fe_readbuff;	/* pointer to user read buffer */
	uint		fe_state;	/* fe_state variable	*/
	uint		fe_position;	/* position within the buffer */
	uint		fe_lastpos;	/* last positon that contins data*/
	uint		fe_task_event;	/* deferred task_event */
	ushort		fe_flag;	/* general flags */
	ushort		fe_readcnt;	/* number of bytes to read */
	char 		fe_maxcol;	/* max column		*/
	char		fe_sticky;	/* sticky margin flag	*/
	unsigned char	fe_decode_state;/* escape sequence decode state */
	char		cpad;
	int	fe_table;
	struct  clist t_inputq;
	lock_t	tpsema;		/* for locking the tty struct */
	sema_t	sleeper;	/* for sleeping on the tty struct */
};

/* Macros		*/
#define	spin_lock_tty(tp)	(spsema(&((tp)->tty_lock)))
#define	unlock_tty_spin(tp)	(svsema(&((tp)->tty_lock)))

static inline void lock_tty_struct(struct tty *tp)	{
volatile int s;
		s = spl6();		
		spin_lock_tty(tp);	
		tp->x = s;
}
	
static inline void unlock_tty_struct(struct tty *tp)	{	
volatile int s = tp->x;
		unlock_tty_spin(tp);	
		(void)splx(s);		
}


/* Set to ensure single thread 	*/
#define	SET_TTY_SINGLE_THREAD(tp,index) ( 	\
	 psema(&(tp)->tty_sema[index],PWAIT | PCATCH ) )

#define	CLEAR_TTY_SINGLE_THREAD(tp,index) ( 	\
	 vsema(&(tp)->tty_sema[index] ))

/*
 * The structure of a clist block
 */
#define	CLSIZE	64
struct cblock {
	struct cblock *c_next;
	unsigned char	c_first;
	unsigned char	c_last;
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

#ifdef u3b15
/* following defs allow for job control in both vpm and stand-alone
   tty environments */
#define VPMTTY	1
#define SATTY	2
#endif

/* limits */
extern int ttlowat[], tthiwat[];
#define	TTYHOG	256
#define	TTXOLO	132
#define	TTXOHI	180
#define TTECHI  80

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
#define	WCLOSE  0200000		/* Waiting for a close to complete */

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
#define T_DISCONNECT	10
#define	T_PARM		11
#define	T_SWTCH		12
#define	T_WAIT		13

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
/*
 *	device reports
 */
#define	L_BUF		0
#define	L_BREAK		3
