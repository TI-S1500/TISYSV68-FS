/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char stack_h[] = "@(#)stack.h	1.6 (TI) 90/12/05";
#endif	SCCSID

/**************************************************
 * Definitions for MC68020 stack frames.	  *
 * See pp. 6-19 through 6-23 in the 68020 manual. *
 **************************************************/

/*
 * Exception types and their vector numbers
 */
#define BUSERR		2	/* Bus Error/Segment Violation (SIGBUS) */
#define ADDRERR		3	/* Address Error (SIGSEGV) */
#define INSTERR		4	/* Illegal Instruction Trap (SIGILL) */
#define ZDVDERR		5	/* Zero Divide Trap (SIGFPE) */
#define CHKTRAP		6	/* CHK Trap (SIGSEGV) */
#define TRAPVFT		7	/* TRAPV instruction fault (SIGILL) */
#define PRIVFLT		8	/* privileged instruction fault (SIGILL) */
#define TRCTRAP		9	/* Trace Trap (SIGTRAP) */
#define L1010FT		10	/* Line 1010 Emulator Trap (SIGILL) */
#define L1111FT		11	/* Line 1111 Emulator Trap (SIGILL) */
#define STRAYFT		24	/* Spurious Interrupt */

/*
 * Stack Frame Format Code:  sp + 0x06
 */
#define	FMAT		0xf000		/* Bit mask */
#define	  FMAT_B	0xb000		/* Long Bus Cycle Fault Stack Frame */
#define	  FMAT_A	0xa000		/* Short Bus Cycle Fault Stack Frame */
#define	  FMAT_9	0x9000		/* Coprocessor Mid-Inst Exception SF */
#define	  FMAT_2	0x2000		/* Six Word Stack Frame */
#define	  FMAT_1	0x1000		/* Throwaway Four Word Stack Frame */
#define	  FMAT_0	0x0000		/* Four Word Stack Frame */

/*
 * Special Status Word:  sp + 0x10
 */
#define	SSW_FC		0x8000		/* Fault on Inst Pipe, stage C */
#define	SSW_FB		0x4000		/* Fault on Inst Pipe, stage B */
#define	SSW_RC		0x2000		/* Rerun Flag, stage C */
#define	SSW_RB		0x1000		/* Rerun Flag, stage B */
#define	SSW_DF		0x0100		/* 1 => Rerun Data Bus Cycle */
#define SSW_RM		0x0080		/* Read-Modify-Write on Data Cycle */
#define	SSW_RW		0x0040		/* 1 => Read Data Cycle, 0 => Write */
#define	SSW_SIZ		0x0030		/* Bit mask for Data Cycle Size */
#define SSW_FCODE	0x0007		/* Mask for Data Cycle Address Space */
#define	  SSW_UDATA	0x0001		/* User Data Space */
#define	  SSW_UPROG	0x0002		/* User Program Space */
#define	  SSW_FC2	0x0004		/* Kernel Space  */ 
#define	  SSW_KDATA	0x0005		/* Kernel Data Space */
#define	  SSW_KPROG	0x0006		/* Kernel Program Space */

/*
 * Registers pushed by trap assembly code
 * in locore.s.
 */
struct lostack
{
	ulong	usp;		/* user stack pointer */
	ulong	r[15];		/* d0-d7,a0-a6 */
};

/*
 * Normal Four Word Stack Frame		(format $0)
 *
 *	Produced on master stack by interrupts, format errors,
 *	TRAP instructions, illegal instructions, A-line and
 *	F-line emulator traps, privilege violations, and
 *	coprocessor pre-instruction exceptions.
 *
 * Throwaway Four Word Stack Frame	(format $1)
 *
 *	Produced on interrupt stack when making transition from
 *	master to interrupt state.
 */
struct fstack
{
	ushort	sr;		/* status register */
	ulong	pc;		/* format $0:	next or exception
						instruction
				   format $1: 	copy of format $0 pc */
	ushort	vor;		/* vector offset register */
};
	
/*
 *  Normal Six Word Stack Frame		(format $2)
 *
 *	Produced by instruction-related exceptions, including
 *	coprocessor post-instruction exceptions, CHK, CHK2,
 *	cpTRAPcc, TRAPV trace, and zero divide.
 */
struct sstack
{
	ushort	sr;		/* status register */
	long	pc;		/* next instruction */
	ushort	vor;		/* vector offset register */
	long	iaddr;		/* address of the instruction which
				   caused the exception */
};

/*
 * Coprocessor Mid-Instruction Exception Stack Frame	(format $9)
 *
 *	Produced by coprocessor interface exceptions.
 */
struct cstack
{
	ushort	sr;		/* status register */
	long	pc;		/* address of next word to fetch from
				   instruction stream */
	ushort	vor;		/* vector offset register */
	long	iaddr;		/* address of first word of instruction
				   executing when exception occurred */
	short	words[4];	/* junk */
};

	

/*
 * Short Bus Cycle Fault Stack Frame	(format $a)
 *
 *	Produced by bus cycle faults when the processor recognizes
 *	that the pc is at an instruction boundary.
 *
 * Long Bus Cycle Fault Stack Frame	(format $b)
 *
 *	Produced by bus cycle fault when not at an instruction boundary.
 */
struct bstack
{
	ushort	sr;		/* status register */
	long	pc;		/* format $a:	next instruction
				   format $b: 	current instruction */
	ushort	vor;		/* vector offset register */
	short	words0;		/* junk */
	ushort	ssw;		/* special status word */
	short	ipsc;		/* instruction pipe stage C */
	short	ipsb;		/* instruction pipe stage B */
	long	faddr;		/* fault address */
	long	pdca;		/* pending data cycle address */
	long	dob;		/* data output buffer */
	union
	{
		/* format $a */
		struct 
		{
			short	words2[2];	/* junk */
		} fa;
		/* format $b */
		struct
		{
			short	words2[4];	/* junk */
			long	sbaddr;		/* stage b address */
			short	words3[2];	/* junk */
			long	dib;		/* data input buffer */
			short	words4[22];	/* junk */
		} fb;
	} t;
};
struct bstack040
{
	ushort	sr;		/* status register */
	ulong	pc;		/* format $7:	current instruction */
	ushort	vor;		/* vector offset register */
	ulong	ea;		/* effective address */
	ushort	ssw;		/* special status word */
	char	zero3;		/* byte of zero		*/
	char	wb3s;		/* writeback 3 status	*/
	char	zero2;		/* byte of zero		*/
	char	wb2s;		/* writeback 3 status	*/
	char	zero1;		/* byte of zero		*/
	char	wb1s;		/* writeback 3 status	*/
	ulong	faddr;		/* fault address */
	ulong	wb3a;		/* writeback 3 address	*/
	ulong	wb3d;		/* writeback 3 data	*/
	ulong	wb2a;		/* writeback 2 address	*/
	ulong	wb2d;		/* writeback 2 data	*/
	ulong	wb1a;		/* writeback 1 address	*/
	ulong	wb1d;		/* writeback 1 data	*/
	ulong	pd1;		/* push data - longword 1 */
	ulong	pd2;		/* push data - longword 2 */
	ulong	pd3;		/* push data - longword 3 */
};
#define	pd0	wb1d		/* push data - longword 0 */
/*
 * Bit definitions for bits within writeback status bytes
*/
#define	WB_V	0x80		/* Valid		*/
#define WB_SZ	0x60		/* Size field		*/
#define	WB_TT	0x18		/* Transfer Type	*/
#define WB_TM	0x07		/* Transfer Mode	*/
/*
 * 68040 Special Status Word:  sp + 0x0C
 */
#define	SSW_CP		0x8000	/* Continuation - FPU Post Exc pending 	      */
#define	SSW_CU		0x4000	/* Continuation - Unimpl. FP Inst Exc pending */
#define	SSW_CT		0x2000	/* Continuation - Trace Exc pending 	      */
#define	SSW_CM		0x1000	/* Continuation - MOVEM Inst. Exc pending     */
#define	SSW_MA		0x0800	/* Misaligned access			      */
#define SSW_ATC		0x0400	/* ATC Fault				      */
#define	SSW_LK		0x0200	/* Locked Transfer			      */
#define	SSW_RW040	0x0100	/* Read/Write				      */
#define SSW_X		0x0080	/* Undefined				      */
#define	SSW_SIZ040	0x0060	/* Transfer size field			      */
#define	SSW_TT		0x0018	/* Transfer type field			      */
#define	SSW_TM		0x0007	/* Transfer mode field			      */
/*  The following are defined above for 68020/30, but also apply for 040.     */
/* #define	  SSW_UDATA	0x0001	  */	/* User Data Space */
/* #define	  SSW_UPROG	0x0002	  */	/* User Program Space */
/* #define	  SSW_FC2	0x0004	  */	/* Kernel Space  */ 
/* #define	  SSW_KDATA	0x0005	  */	/* Kernel Data Space */
/* #define	  SSW_KPROG	0x0006	  */	/* Kernel Program Space */
