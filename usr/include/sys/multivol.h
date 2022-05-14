/*	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1987. ALL
	RIGHTS RESERVED. PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/
/***************************************/

#ifdef	SCCSID
static char multivol_h[] = "@(#)multivol.h	1.3 (TI) 87/06/29";
#endif	SCCSID

#define ENTPERBLK	64	/* number of entries in 1k of internal table */
#define NUMBLKTBL	4	/* number of 1k blocks in the internal table */
#define SL_LU_SLICE	1	/* command to driver to return dev #, given
				   slot, unit, and slice number */
#define GET_ROPEN	2	/* command to driver to return a pointer to
				   the driver's raw open routine. */
#define GET_BOPEN	3	/* command to driver to return a pointer to 
				   the driver's block open routine */
#define GET_BMAJOR	4	/* command to return the block major number */
#define GET_RMAJOR	5	/* command to return the raw major number */
#define GET_LENGTH	6	/* command to return the length of a partition,
				   given the device number of the partition */
#define SL_LU_PNAME	7	/* command to have the driver return a device
				   number given the slot,unit,and part. name */
#define STRIPEBIT	0x01	/* flag in anchor that is set if the anchor
				   shows a striped file system */

struct int_table {	/* structure of entry in the internal table */
	dev_t			dev;	/* Block or raw device number */
	int			offset; /* offset in file system */
	int			size;	/* size of partition */
	int 			reserved;
};

struct log_table {	/* structure of permanently allocated table entry */
	struct int_table	*mptr[NUMBLKTBL];
	struct buf		*bufptr[NUMBLKTBL];
	dev_t			dev;
	int			refcnt;
	int			stripefact;
	int			numents;
};
