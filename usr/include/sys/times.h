/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifndef _TIMES_H
#define _TIMES_H

#ifdef	SCCSID
static char times_h[] = "@(#)times.h	1.4 (TI) 92/09/16";
#endif	SCCSID

/* @(#)times.h	1.1	UNIX System V/68 */
/*
 * Structure returned by times()
 */
struct tms {
	time_t	tms_utime;		/* user time */
	time_t	tms_stime;		/* system time */
	time_t	tms_cutime;		/* user time, children */
	time_t	tms_cstime;		/* system time, children */
};

#endif
