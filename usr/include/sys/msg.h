/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char msg_h[] = "@(#)msg.h	1.4 (TI) 86/09/19";
#endif	SCCSID

/* @(#)msg.h	1.4   */
/*
**	IPC Message Facility.
*/

/*
**	Implementation Constants.
*/

#define	PMSG	(PZERO + 2)	/* message facility sleep priority */

/*
**	Permission Definitions.
*/

#define	MSG_R	0400	/* read permission */
#define	MSG_W	0200	/* write permission */

/*
**	ipc_perm Mode Definitions.
*/

#define	MSG_RWAIT	01000	/* a reader is waiting for a message */
#define	MSG_WWAIT	02000	/* a writer is waiting to send */

/*
**	Message Operation Flags.
*/

#define	MSG_NOERROR	010000	/* no error if big message */

/*
	Macro for generating msqid_ds semaphore address
	assumes 'x' is of type (struct msqid_ds *)
*/

#define MSGADDR(x) &msgsem[x-msgque]

/*
**	Structure Definitions.
*/

/*
**	There is one msg queue id data structure for each q in the system.
*/

struct msqid_ds {
	struct ipc_perm	msg_perm;	/* operation permission struct */
	ushort		msg_rwcnt ;	/* nbr waiting on rwait */
	ushort		msg_wwcnt ;	/* nbr waiting on wwait */
	struct msg	*msg_first;	/* ptr to first message on q */
	struct msg	*msg_last;	/* ptr to last message on q */
	ushort		msg_cbytes;	/* current # bytes on q */
	ushort		msg_qnum;	/* # of messages on q */
	ushort		msg_qbytes;	/* max # of bytes on q */
	ushort		msg_lspid;	/* pid of last msgsnd */
	ushort		msg_lrpid;	/* pid of last msgrcv */
	short		msg_padding;
	time_t		msg_stime;	/* last msgsnd time */
	time_t		msg_rtime;	/* last msgrcv time */
	time_t		msg_ctime;	/* last change time */
};

/*
	Semaphore structures associated with msg q's (msqid_ds).
	This is necessary to make old user object files
	run without recompilation because of the addition
	of semaphore structures within the msqid_ds structures.
*/

struct msgsem
{
	sema_t	msg_lock;	/* lock for msqid_ds structure */
	sema_t	msg_rwait;	/* to wait to read a msg */
	sema_t	msg_wwait;	/* to wait to write a msg */
};

/*
**	There is one msg structure for each message that may be in
**	the system.
*/

struct msg {
	struct msg	*msg_next;	/* ptr to next message on q */
	long		msg_type;	/* message type */
	short		msg_ts;		/* message text size */
	short		msg_spot;	/* message text map address */
};

/*
**	User message buffer template for msgsnd and msgrecv system.
**	calls.
*/

struct msgbuf {
	long	mtype;		/* message type */
	char	mtext[1];	/* message text */
};

/*
**	Message information structure.
*/

struct msginfo {
	int	msgmap,	/* # of entries in msg map */
		msgmax,	/* max message size */
		msgmnb,	/* max # bytes on queue */
		msgmni,	/* # of message queue identifiers */
		msgssz,	/* msg segment size (should be word size multiple) */
		msgtql;	/* # of system message headers */
	ushort	msgseg;	/* # of msg segments (MUST BE < 32768) */
	short	msgpadding;
};
