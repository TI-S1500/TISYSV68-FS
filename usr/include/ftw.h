/*
   COPYRIGHT (c) 1986 TEXAS INSTRUMENTS, INCORPORATED.  ALL RIGHTS RESERVED.
*/
/*
static char *sccs_id = @(#)ftw.h	1.1 86/05/15";
*/
/*	@(#)ftw.h	1.1	*/
/*
 *	Codes for the third argument to the user-supplied function
 *	which is passed as the second argument to ftw
 */

#define	FTW_F	0	/* file */
#define	FTW_D	1	/* directory */
#define	FTW_DNR	2	/* directory without read permission */
#define	FTW_NS	3	/* unknown type, stat failed */
