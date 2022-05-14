/*
   COPYRIGHT (c) 1986 TEXAS INSTRUMENTS, INCORPORATED.  ALL RIGHTS RESERVED.
*/
/*
static char *sccs_id = @(#)symbol.h	1.1 86/05/15";
*/
/*	@(#)symbol.h	1.1	*/
/*	3.0 SID #	1.1	*/
/*
 * Structure of a symbol table entry
 */

struct	symbol {
	char	sy_name[8];
	char	sy_type;
	int	sy_value;
};
