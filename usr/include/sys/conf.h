/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char conf_h[] = "@(#)conf.h	1.13 (TI) 89/09/29";
#endif	SCCSID

/*	@(#)conf.h	1.1	UNIX System V/68 */
/*
 * Declaration of block device switch. Each entry (row) is
 * the only link between the main unix code and the driver.
 * The initialization of the device switches is in the file conf.c.
 */
struct bdevsw {
	int	(*d_open)();
	int	(*d_close)();
	int	(*d_strategy)();
	int	(*d_print)();
	csema_t  *d_sema;		/* driver sema */
	int	d_sock;
	int	major_id;
};
#ifdef KERNEL
extern struct bdevsw bdevsw[];
#endif KERNEL

/*
 * Timeout device access to drivers must gain the semaphore.
 */
struct tdevsw {
	int	(*d_fun)();
	csema_t	*d_sema;
};
#ifdef KERNEL
extern struct tdevsw tdevsw[];
#endif KERNEL
/*
 * Character device switch.
 */
struct cdevsw {
	int	(*d_open)();
	int	(*d_close)();
	int	(*d_read)();
	int	(*d_write)();
	int	(*d_ioctl)();
	struct tty *d_ttys;
	csema_t  *d_sema;		/* driver sema */
	int	 d_sock;
	int	major_id;
	struct streamtab *d_str;
};
#ifdef KERNEL
extern struct cdevsw cdevsw[];

#define	FMNAMESZ	8

struct fmodsw {
	char	f_name[FMNAMESZ+1];
	struct  streamtab *f_str;
};
extern struct fmodsw fmodsw[];
extern int	fmodcnt;
extern int	bdevcnt;
extern int	cdevcnt;
extern int	tdevcnt;
extern int	multicnt;
#endif KERNEL

/*
 * Line discipline switch.
 */
struct linesw {
	int	(*l_open)();
	int	(*l_close)();
	int	(*l_read)();
	int	(*l_write)();
	int	(*l_ioctl)();
	int	(*l_input)();
	int	(*l_output)();
	int	(*l_mdmint)();
};
#ifdef KERNEL
extern struct linesw linesw[];

extern int	linecnt;
#endif KERNEL
/*
 * Terminal switch
 */
struct termsw {
	int	(*t_input)();
	int	(*t_output)();
	int	(*t_ioctl)();
};
#ifdef KERNEL
extern struct termsw termsw[];

extern int	termcnt;
#endif KERNEL

/*
 * console switch
 */
#ifdef KERNEL
struct klsw
{
	char	name[14];	/* logical name passed in boot structure */
	dev_t	dev;		/* device number */
	int	(*putc)();	/* device dependent putchar procedure */
	int	(*getc)();
	int	(*isac)();
	char	line;		/* line discipline number */
};
extern struct klsw klsw[];
#endif KERNEL

/* Declaration of array structure for multivolume file systems.
 * This structure allows other boards to use the multivolume
 * capability. The function element in this structure is needed by the
 * multivolume driver to perform a variety of functions that are device
 * dependent. This function must be located in the device driver if the
 * controller is intended to support multivolume file systems.
 */
struct ident_dev {
	int	(*infofunc)();	/* driver entry point for multi-
				   purpose function */
};
#ifdef KERNEL
extern struct ident_dev multidevs[];
#endif KERNEL

/* file system switch structure */

struct fstypsw {
/* 0*/	int		(*fs_init)();
/* 1*/	int		(*fs_iput)();
/* 2*/	struct inode	*(*fs_iread)();
/* 3*/	int		(*fs_filler)();
/* 4*/	int		(*fs_iupdat)();
/* 5*/	int		(*fs_readi)();
/* 6*/	int		(*fs_writei)();
/* 7*/	int		(*fs_itrunc)();
/* 8*/	int		(*fs_statf)();
/* 9*/	int		(*fs_namei)();
/*10*/	int		(*fs_mount)();
/*11*/	int		(*fs_umount)();
/*12*/	struct inode	*(*fs_getinode)();
/*13*/	int		(*fs_openi)();		/* open inode */
/*14*/	int		(*fs_closei)();		/* close inode */
/*15*/	int		(*fs_update)();		/* update */
/*16*/	int		(*fs_statfs)();		/* statfs and ustat */
/*17*/	int		(*fs_access)();
/*18*/	int		(*fs_getdents)();
/*19*/	int		(*fs_allocmap)();	/* Let the fs decide if */
						/* if can build a map so */
						/* this fs can be used for */
						/* paging */
/*20*/	int		*(*fs_freemap)();	/* free block list */
/*21*/	int		(*fs_readmap)();	/* read a page from the fs */
						/* using the block list */
/*22*/	int		(*fs_setattr)();	/* set attributes */
/*23*/	int		(*fs_notify)();		/* notify fs of action */
/*24*/	int		(*fs_fcntl)();		/* fcntl */
/*25*/	int		(*fs_fsinfo)();		/* additional info */
/*26*/	int		(*fs_ioctl)();		/* ioctl */
/*27*/	int		(*fs_fill[5])();
};
#ifdef KERNEL
extern struct fstypsw fstypsw[];
extern int nfstyp;
#endif KERNEL

/* FS specific data */
struct fsinfo {
	long		fs_flags;	/* flags - see below */
	struct mount	*fs_pipe;	/* The mount point to be used */
					/* as the pipe device for */
					/* this fstyp */
	char		*fs_name; 	/* Pointer to fstyp name */
					/* See above */
	long		fs_notify;	/* Flags for fs_notify */
					/* e.g., NO_CHDIR, NO_CHROOT */
					/* see nami.h */
};
#ifdef KERNEL
extern struct fsinfo fsinfo[];
#endif KERNEL
