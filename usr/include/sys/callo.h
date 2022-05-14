/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char callo_h[] = "@(#)callo.h	1.4 (TI) 89/06/14";
#endif	SCCSID

/*	@(#)callo.h	1.1	UNIX System V/68 */
/*
 * The callout structure is for a routine arranging
 * to be called by the clock interrupt
 * (clock.c) with a specified argument,
 * in a specified amount of time.
 * Used, for example, to time tab delays on typewriters.
 */

struct	callo
{
	int	c_time;		/* incremental time */
	caddr_t	c_arg;		/* argument to routine */
	int	(*c_func)();	/* routine */
	int 	c_id;
	csema_t	*c_sema;	/* semaphore to lock before entry */
};
extern struct callo callout[];
