/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1984.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.

static char id_sccs[] = "@(#)sky.h	1.1 (TI) 87/08/31";

*/

/* SKY Fast Floating-point Processor */

/* programmed I/O registers (offsets from base) */

#define SKYIO	0x400		/* I/O register base address */

#define	COMREG	(SKYIO + 0)	/* command register */
#define	STCREG	(SKYIO + 2)	/* status and control register */
#define	DT1REG	(SKYIO + 4)	/* data register 1 */
#define	DT2REG	(SKYIO + 6)	/* data register 2 */
#define	MC1REG	(SKYIO + 8)	/* microcode register 1 */
#define	MC2REG	(SKYIO + 10)	/* microcode register 2 */

/* command  register */

#define CMDINIT	0x1000		/* initialize */
#define CMDADD	0x1001		/* read add */
#define CMDSAVE	0x1040		/* save context */
#define CMDREST	0x1041		/* save context */
#define CMDLOGE	0x102d		/* log base e */
#define CMDNOP	0x1063		/* nop */

/* status and control register */

#define STCSTATE 0xe000		/* state mask (ready|idle|direction) */
#define STCRDY	 0x8000		/* I/O ready */
#define STCIDLE  0x4000		/* idle */
#define STCDIR	 0x2000		/* I/O direction */
#define STCRST	 0x0080		/* reset */
#define STCMODE	 0x0060		/* mode mask */
#define STCINT	 0x0010		/* interrupt enable */
#define STCIST	 0x0003		/* interrupt status mask */

/* modes */

#define MODHALT	0x0000		/* halt - restart */
#define MODRESU	0x0020		/* halt - resume */
#define MODNORM 0x0040		/* run - normal */
#define MODSS	0x0060		/* run - single step */

/* microcode ram */

#define MICROSIZ 4096		/* size of microcode ram */
#define MICROADDR 0x1000	/* base address of microcode */

struct sky				/* SKY I/O register structure */
{
	short comreg;			/* command register */
	short stcreg;			/* status and control register */
	union 				/* data register . .  */
	{
		long reg;		/* as a long */
		struct
		{
			short reg1;	/* as 2 shorts */
			short reg2;	
		} s;
	} dt;
	long mcreg;			/* microcode register */
};

struct skysave				/* context save structure */
{
	short pc;			/* last pc (command) */
	long reg[8];			/* internal registers */
};
