/*	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1987. ALL
	RIGHTS RESERVED. PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/
/***************************************/

#ifdef	SCCSID
static char mirror_h[] = "@(#)mirror.h	1.3 (TI) 92/09/01";
#endif	SCCSID

#define MIRR_RAWB     0x100000  /* Bit in minor number that indicates raw
				 * mirror device */

struct mirrorh {	/* structure of the header of a mirror band */
	char			name[4]; /* MIRR - used to identify it */
	int			revnum;  /* revision number of partition */
	int			entrysize; /* size of each entry in the table*/
	unsigned char		functype;  /* function type of all entries */
	unsigned char		user[2];  /* user type of all entries */
	char			res1; /* reserved */
	int 			numentries; /* number of entries in table */
	int			flags; /* flags for mirror validity */
	char			p_comment[40]; /* comment field */
};

struct mirrore {	/* structure of entry in mirror band */
	char			partname[4];	/* partition name of entry */
	unsigned int		slunit;  /* slot and logical unit # of entry */
	char			volname[16];	/* volume name of entry */
	int			flags;  /* validity flags */
	unsigned int		devnum;	/* device number if entry is the
					   alternate anchor */
};

/*  flag values  */
#define M_INIT		1
#define M_BAD		2
#define M_ACTIVE	4
#define M_GOOD		8
#define M_FULL		0x10

struct mirentry {
	dev_t dev;
	int slot;
	int flags;
	int bufoffset;
	int size;
	int mvflg;
};

struct openmir {
	dev_t dev;
	dev_t altdev;
	int mirflg;
	int altflg;
	int miroffset;
	struct mirentry openent[2];
	struct buf *mirbufp;
	struct buf *altbufp;
	int refcnt;
	int numwrites;
	int closing;
	int writeanch;
	lock_t ent_lock;
	lock_t buflock;
	lock_t fld_lock;
	lock_t spare;
};

/* ioctl commands */

#define UPMIRR	23
#define CHKMIRR 24
#define CHKMNT  25
