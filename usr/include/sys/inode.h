/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char inode_h[] = "@(#)inode.h	1.16 (TI) 91/04/08";
#endif	SCCSID

#define FSPTR 1
/*
 *	The I node is the focus of all file activity in unix.
 *	There is a unique inode allocated for each active file,
 *	each current directory, each mounted-on file, text file,
 *	and the root. An inode is 'named' by its dev/inumber
 *	pair. (iget/iget.c) Data, from mode on, is read in from
 *	permanent inode on volume.
 *
 */

typedef	struct	inode
{
	struct	inode	*i_forw;	/* inode hash chain */
	struct	inode	*i_back;	/* '' */
	struct	inode	*av_forw;	/* freelist chain */
	struct	inode	*av_back;	/* '' */
	sema_t	i_lock;		/* Lock semaphore */
	int	*i_fsptr;	/* "typeless" pointer to fs dependent */
	long	i_number;	/* i number, 1-to-1 with dev address */
	ushort	i_ftype;	/* file type = IFDIR, IFREG, etc. */
	short	i_fstyp;	/* File system type */
	off_t	i_size;		/* size of file */
	ushort	i_uid;		/* owner */
	ushort	i_gid;		/* group of owner */
	ushort	i_flag;
	ushort	i_fill;
	cnt_t	i_count;	/* reference count */
	short	i_nlink;	/* directory entries */
	dev_t	i_rdev;		/* Raw device number */
	dev_t	i_dev;		/* device where inode resides */

	struct	mount	*i_mntdev;	/* ptr to mount dev inode resides on */
	union i_u {

		struct	mount	*i_mton;	/* pntr to mount table entry */
						/* that this inode is "mounted on" */
		struct stdata	*i_sp;  /* Associated stream.		*/
	} i_un;
#ifdef FSPTR
	struct fstypsw *i_fstypp;	/* pointer to file system */
					/* switch structure */
#endif
	long	*i_filocks;	/* pointer to filock (structure) list */
	sema_t	i_rlck;		/* exclusive/shared read access semaphore */
	struct	rcvd	*i_rcvd;	/* receive descriptor */
	unsigned long	i_vcode;	/* inode version code (RFS caching) */
	ushort	i_wcnt;			/* open for write count (RFS caching) */
	lock_t  i_flcksem;
	long    i_iseg_cnt;		/* Refcnt for Isegs on this inode */
} inode_t;

extern struct inode inode[];	/* The inode table itself */

struct	ifreelist
{	int	pad[2];		/* must match struct inode !*/
	struct inode	*av_forw;
	struct inode	*av_back;
	sema_t ih_lock;
} ;

extern struct ifreelist ifreelist;

#define	i_sptr	i_un.i_sp
#define	i_mnton	i_un.i_mton

/* flags */

#define	ILOCK	0x01		/* inode is locked */
#define	IUPD	0x02		/* file has been modified */
#define	IACC	0x04		/* inode access time to be updated */
#define	IMOUNT	0x08		/* inode is mounted on */
#define	ICLOSIP	0x10		/* last close is in progress */
#define	ITEXT	0x20		/* inode is pure text prototype */
#define	ICHG	0x40		/* inode has been changed */
#define ISYN	0x80		/* do synchronous write for iupdate */
#define	IADV	0x100		/* advertised */
#define	IDOTDOT	0x200		/* object of remote mount */
#define	IRMOUNT	0x800		/* remotely mounted	*/
#define	IISROOT	0x1000		/* This is a root inode of an fs */
#define IWROTE	0x2000		/* write has happened since open */
#define IBLKFRC 0x4000		/* logging, char foreced to block. */

/* file types */
/* WARNING: The following defines should NOT change!If more */
/* file types need to be added they should be added in the low */
/* bits */

#define	IFMT	0xf000		/* type of file */
#define		IFDIR	0x4000	/* directory */
#define		IFCHR	0x2000	/* character special */
#define		IFBLK	0x6000	/* block special */
#define		IFREG	0x8000	/* regular */
#define		IFMPC	0x3000	/* multiplexed char special */
#define		IFMPB	0x7000	/* multiplexed block special */
#define		IFIFO	0x1000	/* fifo special */
#define		IFLNK	0xa000	/* symlink */

/* file modes */
/* the System V Rel 2 chmod system call only knows about */
/* ISUID, ISGID, ISVTX */
/* Therefore, the bit positions of ISUID, ISGID, and ISVTX */
/* should not change */
#define	ISUID	0x800		/* set user id on execution */
#define	ISGID	0x400		/* set group id on execution */
#define ISVTX	0x200		/* save swapped text even after use */

/* access requests */
/* the System V Rel 2 chmod system call only knows about */
/* IREAD, IWRITE, IEXEC */
/* Therefore, the bit positions of IREAD, IWRITE, and IEXEC */
/* should not change */
#define	IREAD		0x100	/* read permission */
#define	IWRITE		0x080	/* write permission */
#define	IEXEC		0x040	/* execute permission */
#define	ICDEXEC		0x020	/* cd permission */
#define	IOBJEXEC	0x010	/* execute as an object file */
				/* i.e., 410, 411, 413 */
#define IMNDLCK		0x001	/* mandatory locking set */

#define	MODEMSK		0xfff	/* Nine permission bits - read/write/ */
				/* execute for user/group/others and */
				/* ISUID, ISGID, and ISVTX */	
				/* This is another way of saying: */
				/* (ISUID|ISGID|ISVTX| */
				/* (IREAD|IWRITE|IEXEC)| */
				/* ((IREAD|IWRITE|IEXEC)>>3)| */
				/* ((IREAD|IWRITE|IEXEC)>>6)) */
#define	PERMMSK		0x1ff	/* Nine permission bits: */
				/* ((IREAD|IWRITE|IEXEC)| */
				/* ((IREAD|IWRITE|IEXEC)>>3)| */
				/* ((IREAD|IWRITE|IEXEC)>>6)) */

#define i_wlck	i_lock		/* write access sema */
#define i_ewlck	i_lock		/* exclusive write access sema */
#define i_erlck	i_rlck		/* exclusive read access sema */
#define i_srlck	i_rlck		/* shared read access sema */

/* define exclusive write and read access to an inode
*  explock
*	wait for current    writers to finish
*	wait for concurrent readers to finish
*	give up read access(readers blocked at i_ewlk)
*  exprele
*	give up write access
*/

#define explock(IP)	psema( &(IP)->i_ewlk, PINOD );\
			psema( &(IP)->i_erlk, PINOD );\
			vsema( &(IP)->i_erlk        )

#define exprele(IP)	vsema( &(IP)->i_ewlk )

/* define shared read access to an inode that blocks writers
*  shplock
*	wait for writers to finish 
*	get shared read access
*	unblock a reader/writer process
*		a writer will be blocked by the ppsema
*		a reader will run concurrently 
*  shprele
*	give up shared read access
*		a writer unblocks after all concurrent readers finish
*/

#define shplock(IP)	psema ( &(IP)->i_ewlk, PINOD );\
			ppsema( &(IP)->i_srlk        );\
			vsema ( &(IP)->i_ewlk        )

#define shprele(IP)	vsema( &(IP)->i_srlk )

/* define exclusive write access to an inode
*  ewplock
*	wait for current writers to finish 
*	ignore concurrent readers
*		readers currently in the file are allowed to continue
*  ewprele
*	give up write access
*/

#define ewplock(IP)	psema( &(IP)->i_ewlck, PINOD )
#define ewprele(IP)	vsema( &(IP)->i_ewlck )

/* define conditional exclusive write access to an inode
*  ewplock
*	do not wait for current writers to finish 
*		if wait required, return fail
*	ignore concurrent readers
*		readers currently in the file are allowed to continue
*/

#define cewplock(IP)	cpsema( &(IP)->i_ewlck, PINOD )

/* define shared read access to an inode without blocking
*  srplock
*	ignore current writers
*		writer currently in the file is allowed to continue
*	get shared read access
*		readers currently in the file are allowed to continue
*  srprele
*	give up shared read access
*/

#define srplock(IP)	ppsema( &(IP)->i_srlck )
#define srprele(IP)	vsema ( &(IP)->i_srlck )

/* define exclusive read access to an inode
*  erplock
*	ignore current writers
*		writer currently in the file is allowed to continue
*	get exclusive read access
*		wait on readers in file
*  erprele
*	give up shared read access
*/

#define erplock(IP)	psema( &(IP)->i_erlck,PINOD )
#define erprele(IP)	vsema( &(IP)->i_erlck )

/* define standard
*  cplock(cewplock)
*	conditional exclusive write access
*  plock(ewplock)
*	exclusive write access
*  prele(ewprele)
*	give up exclusive write access
*/

#define cplock(IP)	cpsema( &(IP)->i_ewlck, PINOD )
#define plock(IP)	psema ( &(IP)->i_ewlck, PINOD )
#define prele(IP)	vsema ( &(IP)->i_ewlck )
