/*
**	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1988.  ALL
**	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
**	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
**	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
**	ASSOCIATED DOCUMENTATION.
*/

#ifdef SCCSID
static char rd_h[] = "@(#)rd.h	1.1 (TI) 88/09/12";
#endif SCCSID

struct rdev {
	int lastblock;		/* last block of the ram disk */
	int size;		/* size of the ram disk, in blocks */
} rdev;

#define SACMD	0x83
