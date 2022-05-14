/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char kerrf_h[] = "@(#)kerrf.h	1.21 (TI) 90/10/11";
#endif	SCCSID

/* @(#)kerrf.h	1.1	UNIX System V/68 */
/*
 * Values of fields that make up a kernel error number
 */

#define	KERN 		0x40000000	/* Kernel error       	*/

/* Kernel Categories  */

#define OS		0x0000000	
#define IO		0x1000000
#define CF		0x2000000
#define ML		0x3000000
#define VM		0x4000000
#define KDB		0x5000000
#define COMM		0x6000000
#define NFS		0x7000000
#define TCP		0x8000000

/* OS sub categories */
#define	EXEC		0x100000
#define	FS		0x200000

/* IO sub categories */

#define CTRL		0x100000
#define SPEVENT		0x200000
#define DEVICE		0x300000
#define UNKNOWN		0x400000
#define INPUT		0x500000
#define MULVOL		0x600000
#define STREAMS		0x700000

/* CF sub categories */

/* ML sub categories */

/* VM sub categories */

/* KDB sub categories */

/* COMM sub categories */
#define CCB_HW		0x100000
#define CCB_SW		0x200000
#define CCB_UNK		0x300000
#define REMOTE_HW	0x900000
#define REMOTE_SW	0xa00000
#define REMOTE_UNK	0xb00000	

/* TCP and NFS sub categories */
#define WARN		0x100000
#define NOTE		0x200000
#define CONT		0x300000
#define TNPANIC		0x400000
#define TNSUBMASK	0xf00000

/* Error severity */

#define PANIC		0xf0000
#define FATAL		0xc0000
#define ERROR		0x90000
#define WARNING		0x60000
#define DBG		0x30000
#define INFO		0x00000

/* Specific Errors */

/* OS */

#define	E_MMUEXEC	(KERN|OS|EXEC|ERROR|1)
#define	E_BADALIGN	(KERN|OS|EXEC|ERROR|4)

#define	SHL		64

#define	E_NOSECT	(KERN|OS|EXEC|ERROR|SHL+1)
#define	E_BADSECT	(KERN|OS|EXEC|ERROR|SHL+2)
#define	E_LONGNAME	(KERN|OS|EXEC|ERROR|SHL+3)
#define	E_NOSHL		(KERN|OS|EXEC|ERROR|SHL+4)
#define	E_NOLINK	(KERN|OS|EXEC|ERROR|SHL+5)
#define	E_LINKERR	(KERN|OS|EXEC|ERROR|SHL+6)

#define	W_INOALCD	(KERN|OS|FS|WARNING|1)
#define	W_IADRESS	(KERN|OS|FS|WARNING|2)
#define	E_BADFREE	(KERN|OS|FS|ERROR|1)
#define	E_NOSPACE	(KERN|OS|FS|ERROR|2)
#define	E_BADBLK	(KERN|OS|FS|ERROR|3)
#define	E_NOINODS	(KERN|OS|FS|ERROR|4)
#define	E_FLOVFLW	(KERN|OS|FS|ERROR|5)
#define	E_INOVFLW	(KERN|OS|FS|ERROR|6)
#define	E_BITMAP	(KERN|OS|FS|ERROR|7)

#define SINGLE_PARITY	(KERN|OS|WARNING)
#define DOUBLE_PARITY	(KERN|OS|FATAL)
#define DBL_PARITY	(KERN|OS|FATAL|1)
#define BF_INSTR	(KERN|OS|FATAL|2)

/* IO */
#define	IRQ_HOT_MSG	(KERN|IO|SPEVENT|FATAL|2)
#define	IRQ_UPS_MSG	(KERN|IO|SPEVENT|WARNING|3)
/* CF */
/* ML */
/* VM */

#define	E_NODATSWP	(KERN|VM|FATAL|1)
#define	E_NOSTKSWP	(KERN|VM|FATAL|2)

/* KDB */
/* COMM */

