/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1989.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char s5dir_h[] = "@(#)shadow.h	1.3 (TI) 89/12/07";
#endif	SCCSID

#define PASSWD 		"/etc/passwd"
#define LPASSWD		"/etc/passwd.local"
#define SHADOW		"/etc/shadow"
#define OPASSWD		"/etc/opasswd"
#define OSHADOW 	"/etc/oshadow"
#define PASSTEMP	"/etc/ptmp"
#define SHADTEMP	"/etc/stmp"

#define	DAY		(24L * 60 * 60) /* 1 day in seconds */
#define DAY_NOW		(long)time((long *)0) / DAY

/* The spwd structure is used in the retreval of information from
   /etc/shadow.  It is used by routines in the libsec library */

struct spwd {
	char *sp_namp ; /* user name */
	char *sp_pwdp ; /* user password */
	long sp_lstchg ; /* password lastchanged date */
	long sp_min ; /* minimum number of days between password changes */
	long sp_max ; /* number of days password is valid */
} ;

/* Declare all shadow password functions */

void 		setspent(), endspent() ;
struct spwd 	*getspent(), *fgetspent(), *getspnam() ;
int 		putspent(), lckpwdf(), ulckpwdf() ;
