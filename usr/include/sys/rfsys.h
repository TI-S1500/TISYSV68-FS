/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1989.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char rfsys_h[] = "@(#)rfsys.h	1.1 (TI) 89/08/17";
#endif	SCCSID

/*	@(#)rfsys.h	1.1	UNIX System V/68 */
/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/


#ifdef INKERNEL
extern	char	Domain[];
#endif

/*  opcodes for rfsys system call */

#define RF_FUMOUNT	1	/* forced unmount */
#define RF_SENDUMSG	2	/* send buffer to remote user-level */
#define RF_GETUMSG	3	/* wait for buffer from remote user-level */
#define RF_LASTUMSG	4	/* wakeup from GETUMSG */
#define RF_SETDNAME	5	/* set domain name */
#define RF_GETDNAME	6	/* get domain name */
#define RF_SETIDMAP	7
#define RF_FWFD		8
#define RF_VFLAG	9
#define RF_DISCONN	10	/* return value for link down */
#define RF_VERSION	11
#define RF_RUNSTATE	12	/* see if RFS is running */


/* defines for VFLAG option	*/
#define V_CLEAR 0
#define V_SET	1
#define V_GET	2

/* defines for the VERSION option	*/
#define VER_CHECK	1
#define VER_GET		2