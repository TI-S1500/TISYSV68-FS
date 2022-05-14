/*
   COPYRIGHT (c) 1986 TEXAS INSTRUMENTS, INCORPORATED.  ALL RIGHTS RESERVED.
*/
/*
static char *sccs_id = "@(#)time.h	1.4 89/11/14";
*/
/*	@(#)time.h	1.1	*/
/*	3.0 SID #	1.2	*/
struct	tm {	/* see ctime(3) */
	int	tm_sec;
	int	tm_min;
	int	tm_hour;
	int	tm_mday;
	int	tm_mon;
	int	tm_year;
	int	tm_wday;
	int	tm_yday;
	int	tm_isdst;
};
struct	iform {	/* see ctime(3) */
	int	if_sec;
	int	if_min;
	int	if_hour;
	int	if_mday;
	int	if_mon;
	int	if_year;
	int	if_wday;
	int	if_time;
};
extern struct tm *gmtime(), *localtime();
extern struct iform *iformat();
extern char *ctime(), *asctime(), *itime();
extern void tzset();
extern long timezone;
extern int daylight;
extern char *tzname[];
