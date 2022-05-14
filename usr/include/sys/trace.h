/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char trace_h[] = "@(#)trace.h	1.3 (TI) 86/02/04";
#endif	SCCSID

/*	trace.h 1.1 of 7/21/81
	@(#)trace.h	1.1	UNIX System V/68
 */

/*
 * Per trace structure
 */
struct trace {
	struct 	clist tr_outq;
	short	tr_state;
	short	tr_chbits;
	short	tr_rcnt;
	unsigned char	tr_chno;
	char	tr_ct;
};
