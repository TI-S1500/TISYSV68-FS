/*	(C)COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTS.
*/
/* 88/03/08 @(#)sysinfo.h	1.1 */
/************************************************************************/
/*	reduced sysinfo structure used on the ccb			*/
/************************************************************************/
struct sysinfo {
	long rcvint; 
	long xmtint;
	long rawch;
	long canch;
	long outch;
	};
extern struct sysinfo sysinfo; 
