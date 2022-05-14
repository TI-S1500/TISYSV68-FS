
/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1984.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef SCCSID
static char sccsid[] = "@(#)proc.h	1.1 (TI) 88/03/08";
#endif

/* @(#)proc.h	1.1 */

struct proc {      
	short p_pid;		/* process id */
	short p_pgrp;		/* process group leader */
	};

