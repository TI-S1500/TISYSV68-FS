/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H

#ifdef	SCCSID
static char types_h[] = "@(#)types.h	1.23 (TI) 90/09/13";
#endif	SCCSID

#ifdef __STDC__
#define VOLATILE volatile
#else
#define VOLATILE
#endif

/* @(#)types.h	2.2	UNIX System V/68 */

#define MAXSEMA 16 
typedef	struct { int r[1]; } *	physadr;
typedef	long		daddr_t;
typedef	char *		caddr_t;
typedef	unsigned int	uint;
typedef	unsigned short	ushort;
typedef	unsigned long	ulong;
typedef unsigned char	unchar; /* Note: 'uchar' already in use. */
typedef	ushort		ino_t;
typedef short		cnt_t;
typedef	long		time_t;
#ifdef m68k
typedef	int		label_t[13];
#else
typedef	int		label_t[10];
#endif
typedef	int		dev_t;
typedef	long		off_t;
typedef	long		paddr_t;
typedef	long		key_t;
typedef long		pte_t;
typedef	unsigned int	size_t;		/* len param for string funcs */

typedef short		lock_t;		/* lock word for busy wait	*/
typedef short		sysid_t;
typedef short		index_t;

typedef struct {
	VOLATILE short	lck;	/* used to lock semaphore code for this */
				/* second half of lck contains cpuid */
	VOLATILE short	val;	/* value of sema, > 0 avail, < 1 locked */
	VOLATILE struct	proc  *head;
	VOLATILE struct	proc  *tail;
	VOLATILE short	pid;	/* pid of last person to get semaphore */
	VOLATILE ushort	pvl;	/* number of piggy back psema's */
}	sema_t;			/* system wide semaphore	*/

typedef struct {
	VOLATILE short	lck;		
	VOLATILE short	val;		
	VOLATILE short   owner;		
	VOLATILE short   pad;		
	sema_t  rsema;
}	csema_t;		

typedef struct {
	VOLATILE short	lck;		
	VOLATILE short	val;		
	VOLATILE short   owner;		
	VOLATILE short   pad;		
}	drivlck_t;		

/* Temp kludge	*/
#define L0pte	ptd
#define L1pte	ptd 
#define L2pte	ptd 
#define L3pte	pgd 
/* svs C gets confused by this define when trying to find pte.h */
#ifdef	PCC
#define pte	pgd
#endif	PCC
#define fpte	fpgd 

/* These u_ types are used for BSD compatibility */

#define bool_t int
typedef unsigned char   u_char;
typedef unsigned short  u_short;
typedef unsigned int    u_int;
typedef unsigned long   u_long;

struct genmem{
	int		cpu;
	struct  pte * pteptr;
	unsigned long size;
	char	*	rmem;
};		
#endif /* _SYS_TYPES_H */
