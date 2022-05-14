/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1987.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/
#ifdef	SCCSID
static char mapout[] = "@(#)mapout.h	1.1 (TI) 87/10/16";
#endif	SCCSID
/* Contains structures used by the kernel to access the map out tables
 * at the tty driver level.
*/
/* Mapout ioctl's */
#define	MIOC  ('M'<< 8) 	/* others defined in termio.h 	*/
#define MGMAP (MIOC|00)		/* get mapping table		*/
#define MSMAP (MIOC|01)		/* set mapping table		*/
#define MCMAP (MIOC|02)		/* clear mapping table		*/
#define MINFO (MIOC|03)		/* get mapping info		*/

			/* map info structure  */
struct map_info{
	int 	msize;		/* size of map table	*/
	int	ntbls;		/* Number of mapout tables */
};

			/* User map data passed to the kernel */
			/* This structure needs to be same as last part */
			/* of mapout_tbl struct	found in maptbl.h */
struct map_data{
	dev_t	device;		/* Which disk file on	*/
	ino_t	inode;		/* Inode of file mapped */
	time_t	mtime;		/* Time file last modifed */
	char	pathname[80];	/* File pathname 	*/
	short 	odata_indx[256];/* Index into output data string */
	char 	odata[2];	/* Output data used in re-mapping  */
		/* Warning this paramater is defined at boot time	*/
};
