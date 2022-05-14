/*	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1987. ALL
	RIGHTS RESERVED. PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/
/***************************************/

#ifdef	SCCSID
static char anchor_h[] = "@(#)anchor.h	1.3 (TI) 87/06/29";
#endif	SCCSID

struct anchorh {	/* structure of the header of an anchor partition */
	char			name[4]; /* NCHR - used to identify it */
	int			revnum;  /* revision number of partition */
	int			entrysize; /* size of each entry in the anchor*/
	unsigned char		functype;  /* function type of all entries */
	unsigned char		user[2];  /* user type of all entries */
	char			res1; /* reserved */
	int 			numentries; /* number of entries in anchor */
	char			flags[2];  /* flags for striping and mirr. */
	short 			stripefact; /* striping factor */
	char			p_comment[40]; /* comment field */
};

struct anchore {	/* structure of entry in anchor partition */
	char			partname[4];	/* partition name of entry */
	unsigned int		slunit;  /* slot and logical unit # of entry */
	char			volname[16];	/* volume name of entry */
	char			reserved[8];	/* for proper alignment */
};
