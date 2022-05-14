/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1989.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char s5inode_h[] = "@(#)s5inode.h	1.5 (TI) 91/01/28";
#endif	SCCSID

#define	NADDR	13
#define	NSADDR	(NADDR*sizeof(daddr_t)/sizeof(short))

struct s5inode {
	ushort	s5i_flags;	/* see below */	
	ushort	s5i_mode;	/* file mode and type */
	struct {
		union s5i_u1 {
			struct	s5inode	*s5i_nxt; /* free list pntr */
			daddr_t s5i_a[NADDR];	/* if normal file/directory */
			short	s5i_f[NSADDR];	/* counts for fifo's */
		} s5i_u1;
		sema_t s5i_fifo[4];	/* if fifo's */
	} s5i_blks;
	union s5i_u2 {
		int	*s5i_mp;	/* pointer to blk # map for paging */
		off_t	s5i_doff;	/* directory offset - */
					/* for directory caching */
	} s5i_u2;
	daddr_t	s5i_bnlb;
	daddr_t	s5i_bnle;
	daddr_t	s5i_bnpe;
	union {
		struct {
			unsigned di_time:24,
				 di_gens: 5,
				 xflags: 3;
		} s5gen_struct;
		unsigned long	 s5gen_long;
	} s5gen_union;
};

/* Extended mode flag bits */
#define s5i_xmode	s5gen_union.s5gen_struct.xflags
#define s5i_gen		s5gen_union.s5gen_struct.di_gens
#define s5i_ctime	s5gen_union.s5gen_struct.di_time

#define s5i_gen_num(ip)	( (((struct s5inode *)(ip->i_fsptr))->s5gen_union.s5gen_long) >> 3)

/* Flags */
#define	S5IFREE		0x0	/* Free cell */

#define	s5i_next	s5i_blks.s5i_u1.s5i_nxt
#define	s5i_addr	s5i_blks.s5i_u1.s5i_a
#define	s5i_rdev	s5i_blks.s5i_u1.s5i_a[0]

#define	s5i_map		s5i_u2.s5i_mp
#define	s5i_diroff	s5i_u2.s5i_doff

#define	s5i_faddr	s5i_blks.s5i_u1.s5i_a
#define	NFADDR	10
#define	PIPSIZ	NFADDR*BSIZE
#define	s5i_frptr	s5i_blks.s5i_u1.s5i_f[NSADDR-5]
#define	s5i_fwptr	s5i_blks.s5i_u1.s5i_f[NSADDR-4]
#define	s5i_frcnt	s5i_blks.s5i_fifo[0]
#define	s5i_fwcnt	s5i_blks.s5i_fifo[1]
#define	s5i_waite	s5i_blks.s5i_u1.s5i_f[NSADDR-3]
#define	s5i_waitf	s5i_blks.s5i_u1.s5i_f[NSADDR-2]
#define	s5i_fflag	s5i_blks.s5i_u1.s5i_f[NSADDR-1]
#define	s5i_empty	s5i_blks.s5i_fifo[2]
#define	s5i_full	s5i_blks.s5i_fifo[3]
#define	IFIR	01
#define	IFIW	02

/* extended modes */
#define IFORCED 1		/* file is forced write */
#define IEXTENT 2		/* file is on a contiguous filsys */
#define IHARDFS 4		/* file is on a hardened filesys */

extern struct s5inode s5inode[];
