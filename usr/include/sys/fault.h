/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char fault_h[] = "@(#)fault.h	1.3 (TI) 86/02/04";
#endif	SCCSID

/*
 * Defines for MC68020 stack frame formats
 *
 * Format numbers are given in the most significant
 * byte of the vector offset word in the standard
 * Four Word Stack Frame.  See manual pages 6-19
 * through 6-23 for more detail. 
 */
#define	FORMAT0		0x0000		/* Four Word Stack Frame */
#define	FORMAT1		0x1000		/* Throwaway Four Word Stack Frame */
#define	FORMAT2		0x2000		/* Six Word Stack Frame */
#define	FORMAT9		0x9000		/* Coprocessor Mid-Inst Exception SF */
#define	FORMATA		0xa000		/* Short Bus Cycle Fault Stack Frame */
#define	FORMATB		0xb000		/* Long Bus Cycle Fault Stack Frame */
#define	FORMASK		0xf000		/* Bit mask */
