/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char s5filsys_h[] = "@(#)s5filsys.h	1.4 (TI) 90/12/17";
#endif	SCCSID

/*
 * structure of contiguous system allocation table 
 */
struct bm_tab {       /* free space table entry - ADDED */
	long blk;            /* ADDED */
	long lng;	     /* ADDED */
};
/*
 * Structure of the super-block
 */
struct	filsys
{
	ushort	s_isize;	/* size in blocks of i-list */
	daddr_t	s_fsize;	/* size in blocks of entire volume */
	short	s_nfree;	/* number of addresses in s_free */
	daddr_t	s_free[NICFREE];	/* free block list */
	short	s_ninode;	/* number of i-nodes in s_inode */
	ino_t	s_inode[NICINOD];	/* free i-node list */
	char	s_flock;	/* lock during free list manipulation */
	char	s_ilock;	/* lock during i-list manipulation */
	char  	s_fmod; 	/* super block modified flag */
	char	s_ronly;	/* mounted read-only flag */
	time_t	s_time; 	/* last super block update */
	short	s_dinfo[4];	/* device information */
	daddr_t	s_tfree;	/* total free blocks*/
	ino_t	s_tinode;	/* total free inodes */
	char	s_fname[7];	/* file system name */
	char	s_fpack[7];	/* file system pack name */
	char	s_hardfs;	/* set by mkfs to indicate hardened fs */
	char	s_alter;	/* alternate sprblk updates (used in dfree) */
#ifdef m68k
#  if FsTYPE==2
/*	long	s_fill[136];*/	/* ADJUST to make sizeof filsys be 1024 */
	struct bm_tab s_freetab[NUMENTS+1]; /* free table for extent fs */
	int 	s_numbm;	/* number of bitmap blocks */
	daddr_t	s_bitblk;	/* block addr of first bitmap */
	long	s_state;	/* file system state */
/* LOGGING */
	long	s_fill[110];	/* ADJUST to make sizeof filsys be 1024 */
	long    s_l_mount_stamp;/* Log mount time stamp */
/* LOGGING */
/*	long	s_fill[111];*/	/* ADJUST to make sizeof filsys be 1024 */
#  else
	long	s_fill[7];	/* ADJUST to make sizeof filsys be 512 */
#  endif
#else
	long	s_fill[5];	/* ADJUST to make sizeof filsys be 512 */
#endif

	sema_t	s_semflock;	
	sema_t  s_semilock;

	long	s_magic;	/* magic number to indicate new file system */
	long	s_type;		/* type of new file system */
};

#define	FsMAGIC	0xfd187e20	/* s_magic number */
#define FsXMAGIC (FsMAGIC+1)	/* contiguous file system s_magic number */

#define	Fs1b	1	/* 512 byte block */
#define	Fs2b	2	/* 1024 byte block */

#define	FsOKAY	0x7c269d38	/* s_state: clean */
#define	FsACTIVE	0x5e72d81a	/* s_state: active */
#define	FsBAD	0xcb096f43	/* s_state: bad root */
#define FsBADBLK	0xbadbc14b	/* s_state: bad block corrupted it */

#define getfs(mp)	(struct filsys *)((struct buf *)mp->m_bufp)->b_un.b_addr
