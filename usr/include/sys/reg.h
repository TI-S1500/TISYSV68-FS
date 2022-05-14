/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char reg_h[] = "@(#)reg.h	1.4 (TI) 86/02/04";
#endif	SCCSID

/* @(#)reg.h	2.5	UNIX System V/68 */
/*
 * Location of the users' stored registers relative to R0.
 * Usage is u.u_ar0[XX].
 */
#define	R0	0
#define	R1	1
#define	R2	2
#define	R3	3
#define	R4	4
#define	R5	5
#define	R6	6
#define	R7	7
#define	R8	8
#define R9	9
#define	R10	10
#define	R11	11
#define	R12	12
#define	R13	13
#define	R14	14
#define	R15	(-1)
#define	USP	(R15)	
#define	FP	(R14)

/* User's view of 68020 exception stack frame */

#ifndef KERNEL
#define PS	15
#define PC	16
#define SP	(R15)
#endif
