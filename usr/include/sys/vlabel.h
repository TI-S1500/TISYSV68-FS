/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char vlabel_h[] = "@(#)vlabel.h	1.3 (TI) 86/02/04";
#endif	SCCSID

/* volume label flag word */

struct vfword_def
{
	unsigned v_dtopt : 3;		/* disk and tape options	*/

		/*	TAPE OPTIONS      */

			/* 000 - stream only		*/
			/* 001 - start/stop		*/
			/* 010 - stream w/track select  */
			/* 011 - start/stop w/track sel */
			/* 100-111 - reserved		*/

		/*	DISK OPTIONS	  */

			/* reserved			*/
	
		/*	WORM OPTIONS	  */

			/* none			*/
	
	unsigned v_fixed : 1;		/* 0 - removable  1 - fixed	*/
	unsigned v_logical : 1;		/* 0 - phys addr, 1 - logical addr */
	unsigned v_typecode : 3;	/* 000 - disk			*/
					/* 001 - tape			*/
					/* 010 - Wrt-Once-Rd-Many WORM  */
					/* 011-111 - reserved		*/
	unsigned  : 24;			/* bits 8-31 reserved		*/
};
 
/* characteristics of device containing volume label */

struct diskchar_def
{
	/*	DISK CHARACTERISTICS	    */
	ushort	bytepsectr;		/* bytes per sector */
	ushort	res1;			/* reserved */
	char	sectrptrack;		/* sectors per track */
	char	headpcyl;		/* heads per cylinder */
	ushort	cylinders;		/* number of cylinders */
	ushort	ressectr;		/* # reserved sectory for defects */
	int	res2;			/* reserved */
};


struct tapechar_def
{
	/* 	TAPE CHARACTERISTICS	*/
	ushort	 bytepphysbk;		/* bytes per physical block */
	ushort	 res1;			/* reserved */
	ushort	 numtracks;		/* # of tracks (if supported) */
	int	 numblocks;		/* number of blocks (nominal) */
	int	 res2;			/* reserved */
};

/*	Map for volume label */

struct vlabel
{
	char	label[4];		/* volume lbl record indicator "LABL" */
	int	revnum;			/* revision number */
	int     res1[2];		/* reserved */
	struct  vfword_def vfword;	/* flag word */
	char	devname[12];		/* device name text */
	ushort	bytepblk;		/* bytes per block */
	union 		 		/* device characteristics */
	{
		struct diskchar_def diskchar;
		struct tapechar_def tapechar;
	} vdevchar;
	char	volname[16];		/* volume name */
	int	res3[4];		/* reserved */
	char	partlabel[4];		/* partition table name PTBL */
	int	partsblk;		/* starting block of partition table */
	int	partlth;		/* partition table length in blocks */
	char	res7[20];		/* reserved for future partition info */
	char	savelabel[4];		/* secondary save partition name SAVE */
	int	savesblk;		/* starting blk of save partition */
	int	savelth;		/* save partition length in blocks */
	char	res8[20];		/* reserved for future SAVE info */
	char	res9[112];		/* reserved for future label info */
	char	vcomment[768];		/* volume comments */
};
