/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1986.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char rtc_h[] = "@(#)rtc.h	1.1 (TI) 86/04/13";
#endif	SCCSID

#define	RTC_OP	(('R'<<24)|('T'<<16)|('C'<<8))

#define	RTC_GET		(RTC_OP|1)
#define	RTC_SET		(RTC_OP|2)
#define	RTC_ENABLE	(RTC_OP|3)
#define	RTC_DISABLE	(RTC_OP|4)