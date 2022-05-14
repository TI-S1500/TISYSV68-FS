/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
#ident "@(#)ioctl.h	1.6 (TI) 91/03/14"
#endif	SCCSID

/* @(#)ioctl.h	1.1	UNIX System V/68 */
/*
*  mag tape io control commands
*/
#define MTIOCTOP	(('m'<<8)|1)	/* do a mag tape op (see <mtio.h>) */
#define MTIOCGET	(('m'<<8)|2)	/* get mag tape status (see <mtio.h>*/

/*
*  quarter-inch tape io control commands
*/
#define QTRIOCTOP	(('m'<<8)|1)	/* do a 1/4" tape op (see <qtrio.h>) */
#define QTRIOCGET	(('m'<<8)|2)	/* get 1/4" tape status (see <qtrio.h>*/

/*
*  ram disk driver ioctl commands
*/
#define GETSIZE	1	/* get the size of the ram disk in blocks */

/* Device status ioctl to NUPI or MSC return structure */
struct dstatus {
	short	devtype;
	int	formatter;
	int 	unit;
};

#define MAXDEVS 16  /* Max # devices per controller */

/* Single structure containing the correct number of status structures
   necessary for the ioctl call to the NUPI or MSC.
*/

struct onlndev {
	struct dstatus dstatus[MAXDEVS];
};
