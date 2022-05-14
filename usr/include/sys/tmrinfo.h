/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1986.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char tmrinfo_h[] = "@(#)tmrinfo.h	1.2 (TI) 89/10/24";
#endif	SCCSID

/****************************************************************************
 * Structure returned by accounting timer pseudo driver.
 ****************************************************************************/

struct tmrinfo
{
	unsigned long	actim[2];	/* 56-bit time stamp		     */
		 long	wsec;		/* time in seconds since boot	     */
		time_t	wticks;		/* time in clock ticks since boot    */
		time_t	utime;		/* user   cpu time in clock ticks    */
		time_t	stime;		/* system cpu time in clock ticks    */
	unsigned long	umiltime;	/* user   cpu time in milliseconds   */
	unsigned long	smiltime;	/* system cpu time in milliseconds   */
	unsigned long	umictime;	/* user   cpu time in microseconds   */
	unsigned long	smictime;	/* system cpu time in microseconds   */
};
