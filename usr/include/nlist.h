/*
   COPYRIGHT (c) 1986 TEXAS INSTRUMENTS, INCORPORATED.  ALL RIGHTS RESERVED.
*/
/*
static char *sccs_id = @(#)nlist.h	1.1 86/05/15";
*/
/*
*	"@(#) nlist.h: 1.2 3/19/83"
*/

#if vax || u3b || u3b5 || m68k

/* symbol table entry structure */

struct nlist
{
	char		*n_name;	/* symbol name */
	long		n_value;	/* value of symbol */
	short		n_scnum;	/* section number */
	unsigned short	n_type;		/* type and derived type */
	char		n_sclass;	/* storage class */
	char		n_numaux;	/* number of aux. entries */
};

#else /* pdp11 || u370 */

struct nlist
{
	char		n_name[8];	/* symbol name */
#if pdp11
	int		n_type;		/* type of symbol in .o */
#else
	char		n_type;
	char		n_other;
	short		n_desc;
#endif
	unsigned	n_value;	/* value of symbol */
};

#endif
