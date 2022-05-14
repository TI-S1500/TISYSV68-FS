/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char runq_h[] = "@(#)runq.h	1.4 (TI) 90/09/13";
#endif	SCCSID

#ifdef __STDC__
#define VOLATILE volatile
#else
#define VOLATILE
#endif

/* <@(#)runq.h	1.4     90/09/13> */

/*
 * Structure for the run q.   NOTE:  Any changes to this file need
 * to have corresponding changes to the assembler labels defined in sema.s
 */
struct runq {
	lock_t	lock;
	VOLATILE struct proc *qp;
};
