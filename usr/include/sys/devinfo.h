/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1986. ALL
	RIGHTS RESERVED. PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/


#define PURCMD 0	/* command sent to ioctl */
#define NUPITYPE 1	/* NUPI disk device */
#define MSCTYPE 2	/* MSC disk device */
#define NULLTYPE 0	/* if type field is 0, index is unused */

/* The following structure is returned to a utility that measures disk
** performance. An ioctl call to the NUPI or MSC drivers will return
** this structure.
*/

struct devinfo {
	short 	controller;
	short	formatter;
	short	unit;
	short 	index;
	short	type;
};
