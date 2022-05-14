/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char shm_h[] = "@(#)shm.h	1.7 (TI) 88/01/20";
#endif	SCCSID

/*
**	IPC Shared Memory Facility.
*/

/*
**	Implementation Constants.
*/

#define	SHMLBA	ctob(1)	/* segment low boundary address multiple */
			/* (SHMLBA must be a power of 2) */

/*
**	Permission Definitions.
*/

#define	SHM_R	0400	/* read permission */
#define	SHM_W	0200	/* write permission */

/*
**	ipc_perm Mode Definitions.
*/

#define	SHM_CLEAR	01000	/* clear segment on next attach */
#define	SHM_DEST	02000	/* destroy segment when # attached = 0 */
/*
**	Message Operation Flags.  Note: Following two flags MUST correspond
**				  with flags in mmu_status (see mmu.h).
*/
#define	SHM_RDONLY	010000	/* attach read-only (else read-write) */
#define	SHM_RND		020000	/* round attach address to SHMLBA */

#define SHM_ALL_FLAGS	030000  /* Above flags logically or'd together */

/*
**	Structure Definitions.
*/

/*
**	There is a shared mem id data structure for each segment in the system.

**	Warning: This structure can be returned to a user program on a 
**	system call, so its length must not change from the user's 
**	perspective.  The next structure (shmid_ds_user_len) defines the
**	amount actually returned to the user.
*/

struct shmid_ds {
	struct ipc_perm	shm_perm;	/* operation permission struct */
	int		shm_segsz;	/* segment size */
#ifndef m68k
	struct pt_entry	*shm_ptbl;	/* ptr to associated page table */
#else

# ifdef	NU
	int		shm_kvwaddr;	/* kernel virtual window for ptes */
	daddr_t		shm_ptdaddr;	/* pointer to swap area for ptes */
# else
	int		shm_paddr;	/* physical address of segment */
# endif

#endif
	ushort		shm_lpid;	/* pid of last shmop */
	ushort		shm_cpid;	/* pid of creator */
	ushort		shm_nattch;	/* current # attached */
	ushort		shm_cnattch;	/* in memory # attached */
	short		shm_cpuid;	/* cpu ID of allocating cpu	*/
	short		shm_padding;
	time_t		shm_atime;	/* last shmat time */
	time_t		shm_dtime;	/* last shmdt time */
	time_t		shm_ctime;	/* last change time */
	sema_t		shm_sema;	/* semaphore on this structure */
};
/*
** Structure used only by the system to decide how much of the above
** shmid_ds structure to return to the user on certain system calls.
*/
struct shmid_ds_user_len {
	struct ipc_perm	shm_perm;	/* operation permission struct */
	int		shm_segsz;	/* segment size */
#ifndef m68k
	struct pt_entry	*shm_ptbl;	/* ptr to associated page table */
#else

# ifdef	NU
	int		shm_kvwaddr;	/* kernel virtual window for ptes */
	daddr_t		shm_ptdaddr;	/* pointer to swap area for ptes */
# else
	int		shm_paddr;	/* physical address of segment */
# endif

#endif
	ushort		shm_lpid;	/* pid of last shmop */
	ushort		shm_cpid;	/* pid of creator */
	ushort		shm_nattch;	/* current # attached */
	ushort		shm_cnattch;	/* in memory # attached */
	short		shm_cpuid;	/* cpu ID of allocating cpu	*/
	short		shm_padding;
	time_t		shm_atime;	/* last shmat time */
	time_t		shm_dtime;	/* last shmdt time */
	time_t		shm_ctime;	/* last change time */
/* /*	sema_t		shm_sema;	/* semaphore on this structure */
};

struct	shminfo {
	int	shmmax,	/* max shared memory segment size */
		shmmin,	/* min shared memory segment size */
		shmmni,	/* # of shared memory identifiers */
		shmseg,	/* max attached shm (&nubus) segments per process */
		shmbrk,	/* gap (in clicks) used between data and shared memory*/
		shmmxat, /*max total attached segments system wide	   */
		shmall;	/* max total shared memory system wide (in clicks) */
};

extern struct shmid_ds	shmem[];	/* shared memory headers */
extern struct shminfo	shminfo;	/* shared memory info structure */
