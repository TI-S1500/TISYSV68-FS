/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char file_h[] = "@(#)file.h	1.1 (TI) 88/03/08";
#endif	SCCSID

/* @(#)file.h	1.1 */
/*
 * One file structure is allocated for each open/creat/pipe call.
 * Main use is to hold the read/write pointer associated with
 * each open file.
 */

/* flags */
#define	FOPEN	(-1)
#define	FREAD	00001
#define	FWRITE	00002
#define	FNDELAY	00004
#define	FAPPEND	00010
#define	FSYNC	00020
#define	FMASK	00377

/* open only modes */
#define	FCREAT	00400
#define	FTRUNC	01000
#define	FEXCL	02000

/* creat only modes */
#define FW 0200000  /* forced write */
