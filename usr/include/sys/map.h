/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char map_h[] = "@(#)map.h	1.5 (TI) 89/07/21";
#endif	SCCSID

/* @(#)map.h	1.3   */
/*
 *	Map Structure - used to manage contiguous space.
 */

typedef struct	map	{
	long		m_size;
	unsigned long	m_addr;
} map_t;

#define	mapstart(X)	&X[2]
#define	mapsize(X)	X[0].m_size
#define	mapdata(X)	{(X)-3, 0} , {0, 0}
#define mapinit(X, Y, A, B)	X[0].m_size = (Y)-3;\
				X[1].m_size = (uint) A;\
				X[1].m_addr = (uint) B
#define mapsema(X)	((sema_t *) X[1].m_size)
#define mapout(X)	((sema_t *) X[1].m_addr)

extern	struct	map	swapmap[];
