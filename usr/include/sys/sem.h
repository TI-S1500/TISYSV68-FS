/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char sem_h[] = "@(#)sem.h	1.5 (TI) 87/07/30";
#endif	SCCSID

/* @(#)sem.h	1.4   */
/*
**	IPC Semaphore Facility.
*/

/*
**	Implementation Constants.
*/

#define	PSEMN	(PZERO + 3)	/* sleep priority waiting for greater value */
#define	PSEMZ	(PZERO + 2)	/* sleep priority waiting for zero */
#define	PSEML	(PZERO + 4)	/* sleep priority waiting for lock */

/*
**	Permission Definitions.
*/

#define	SEM_A	0200	/* alter permission */
#define	SEM_R	0400	/* read permission */

/*
**	Semaphore Operation Flags.
*/

#define	SEM_UNDO	010000	/* set up adjust on exit entry */

/*
**	Semctl Command Definitions.
*/

#define	GETNCNT	3	/* get semncnt */
#define	GETPID	4	/* get sempid */
#define	GETVAL	5	/* get semval */
#define	GETALL	6	/* get all semval's */
#define	GETZCNT	7	/* get semzcnt */
#define	SETVAL	8	/* set semval */
#define	SETALL	9	/* set all semval's */

/*
**	Miscellaneous Parameters
*/

#define SEMMSL 10	/*  lowest configurable maximum # of semaphores per id*/
#define SEMOPM 4	/*  lowest configurable maximum ops per semop call */
#define SEMVMX 32767	/* max semaphore value */
#define SEMAEM 16384	/* max adjust on exit value */

/*
	Macro to generate sem id lock ptr
*/

#define SEMADDR(x)	&semsem[x-sema]

/*
**	Structure Definitions.
*/

/*
**	There is one semaphore id data structure for each set of semaphores
**		in the system.
*/

struct semid_ds {
	struct ipc_perm	sem_perm;	/* operation permission struct */
	struct sem	*sem_base;	/* ptr to first semaphore in set */
	ushort		sem_nsems;	/* # of semaphores in set */
	short		sem_padding;
	time_t		sem_otime;	/* last semop time */
	time_t		sem_ctime;	/* last change time */
};

/*
**	There is one semaphore structure for each semaphore in the system.
*/

struct sem {
	ushort	semval;		/* semaphore text map address */
	short	sempid;		/* pid of last operation */
	short	semncnt;	/* # awaiting semval > cval */
	short	semzcnt;	/* # awaiting semval = 0 */
	sema_t	semnwait;	/* to wait for non-zero value */
	sema_t	semzwait;	/* to wait for zero value */
};

/*
**	There is one undo structure per process in the system.
*/

struct sem_undo {
	struct sem_undo	*un_np;	/* ptr to next active undo structure */
	short		un_cnt;	/* # of active entries */
	struct undo {
		short	un_aoe;	/* adjust on exit values */
		short	un_num;	/* semaphore # */
		int	un_id;	/* semid */
	}	un_ent[1];	/* undo entries (one minimum) */
};

/*
** semaphore information structure
*/
struct	seminfo	{
	int	semmap,		/* # of entries in semaphore map */
		semmni,		/* # of semaphore identifiers */
		semmns,		/* # of semaphores in system */
		semmnu,		/* # of undo structures in system */
		semmsl,		/* max # of semaphores per id */
		semopm,		/* max # of operations per semop call */
		semume,		/* max # of undo entries per process */
		semusz,		/* size in bytes of undo structure */
		semvmx,		/* semaphore maximum value */
		semaem;		/* adjust on exit max value */
};

/*
**	User semaphore template for semop system calls.
*/

struct sembuf {
	ushort	sem_num;	/* semaphore # */
	short	sem_op;		/* semaphore operation */
	short	sem_flg;	/* operation flags */
};

