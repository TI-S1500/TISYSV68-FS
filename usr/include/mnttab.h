/*
   COPYRIGHT (c) 1986 TEXAS INSTRUMENTS, INCORPORATED.  ALL RIGHTS RESERVED.
*/
/*
static char *sccs_id = @(#)mnttab.h	1.2 87/12/10";
*/
/*	@(#)mnttab.h	1.2	*/
/*	3.0 SID #	1.1	*/
#define	NMOUNT	256

/* Format of the /etc/mnttab file which is set by the mount(1m)
 * command
 */
struct mnttab {
	char	mt_dev[32],
		mt_filsys[32];
		short	mt_ro_flg;
	time_t	mt_time;
};
