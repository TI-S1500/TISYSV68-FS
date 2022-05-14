/*
   COPYRIGHT (c) 1986 TEXAS INSTRUMENTS, INCORPORATED.  ALL RIGHTS RESERVED.
*/
/*
static char *sccs_id = @(#)grp.h	1.1 86/05/15";
*/
/*	@(#)grp.h	1.1	*/
/*	3.0 SID #	1.1	*/
struct	group {	/* see getgrent(3) */
	char	*gr_name;
	char	*gr_passwd;
	int	gr_gid;
	char	**gr_mem;
};
