/*	(C)COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985 .  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTS.
*/
static char user_h[]="@(#)user.h	1.1 (TI) 88/03/23";
/* @(#)user.h	1.1 */
/**********************************************************************/
/*	reduced user structure used by the ld device driver on the ccb*/
/**********************************************************************/

struct user {
	long u_base;		/* base address for i/o */
	unsigned u_count;	/* bytes remaining for i/o */ 
	long u_fmode;		/* file mode for i/o */
	struct proc *u_procp;	/* pointer to proc structure */
	short *u_ttyp;		/* spare */
	int u_rval1;		/* return value 1 */
	int u_rval2;		/* return value 2 */
	short u_error;		/* return error code */
	short u_ttyd;
	int u_arg0;
	};
extern struct user u;
