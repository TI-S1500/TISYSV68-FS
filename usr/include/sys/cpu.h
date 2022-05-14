/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char cpu_h[] = "@(#)cpu.h	1.31 (TI) 90/09/13";
#endif	SCCSID

/****************************************************************************
 * 68K chip features
 ****************************************************************************/
#define	CACR_IBE	0x0010		/* Instruction Burst Enable	    */
#define	CACR_DBE	0x1000		/* Data        Burst Enable	    */

/****************************************************************************
 * BS32 Cpu Board Features
 ****************************************************************************/
#ifdef __STDC__
#define VOLATILE volatile
#else
#define VOLATILE
#endif

struct msb
{
	VOLATILE unsigned char	r;
	VOLATILE unsigned char	r1;		
	VOLATILE unsigned char	r2;	
	VOLATILE unsigned char	r3;	
};

/*****************************
 * Interrupt Controller Chip *
 ****************************/

#define	PIC 		0x00FFF400L	/* board offset of interrupt cntrlr */ 
#define INTBASE		0x00FFF7FCL	/* useful value for calculating
					   interrupt ram addresses */
#define INTAUN		0x000003FCL	/* another useful number for similar */
					/* calculations			     */
#define OVRNPRI		0x5F4		/* offset of overrun priority reg */
#define OVRNADDR	0x5F0		/* offset of overrun address reg */
#define IRQLVL		0x5EC		/* offset of first IRQ priority reg 
					   6 priority registers: 0x75 - 0x7A */
#define	PITCNTL		0x5D0		/* Programmable interrupt timer cntl */
#define PITNTRVL	0x5CC		/* PIT interval register */
#define PITCNTR		0x5C8		/* PIT counter register */
#define CLRINT		0x5C0		/* clear interrupt register */
#define ICRESET		0x10		/* CLRINT value for reset of pic */

#define	LEVELS		7		/* number of interrupt levels */
#define	VPL		16		/* number of vectors per level */
#define	N_IRQ		6		/* number of irq priority registers */

/*
** interesting bits and masks for the pit control register
*/
#define	PITMASK		0x07
#define	PITPRI		0x06	/* interrupt priority level 6 */

#define	PITENABLE	0x08
#define	PITDISABLE	0x00

#define	PITSCALE	0x30
#define	PIT_10us	0x00
#define	PIT_100us	0x10
#define	PIT_1ms		0x20
#define	PIT_10ms	0x30

#define	PITINT		0x00
#define	PITEXT		0x40

#define	PITLOAD		0x80

/* offsets into irqlvl */

#define	IRQ_ACCT	5
#define	IRQ_BATT	4
#define	IRQ_MFPPIT	4
#define	IRQ_HOT		3
#define	IRQ_UART	2
#define	IRQ_POWER	1
#define	IRQ_NMI		0

/* irq control/status register */

#define	IRQ_CLR		0x10	/* clear input latch */
#define	IRQ_LATCH	0x08	/* input latch enable */
#define	IRQ_PRI		0x07

/* interrupt overrun address register */

/* interrupt overrun priority register */

#define	ORUN_IE		0x08

/* interrupt error register */

#define	NMI_PEND	0x80
#define	PIT_ORUN	0x40
#define	PIT_PEND	0x20
#define	INT_ORUN	0x10
#define	IVERR_STAT	0x08
#define	IVERR_LVL	0x07

struct	mfp_pit
{
	VOLATILE unsigned char	interval;
	VOLATILE unsigned char	_nter[3];
	VOLATILE unsigned char	counter;
	VOLATILE unsigned char	_oun[3];
	VOLATILE unsigned char	control;
	VOLATILE unsigned char	_ont[3];
} ;

struct icc
{
	/*
	 * The interrupt ram itself
	 */
	VOLATILE long		iram[LEVELS*VPL];

	/*
	 * The clear interrupts register
	 */
	struct	msb	clri;

	struct	msb	nmi_vector;	/* used only in 32000 mode */

	/*
	 * Programmable interval timer control registers
	 */
	struct	pit
	{
		VOLATILE unsigned char	counter;
		VOLATILE unsigned char	_oun[3];
		VOLATILE unsigned char	interval;
		VOLATILE unsigned char	_nter[3];
		VOLATILE unsigned char	control;
		VOLATILE unsigned char	_ont[3];
	} pit;

	/*
	 * Programmable Interrupt Priority Level
	 */
	struct	msb	irqlvl[N_IRQ];

	/*
	 * IRQ status register
	 */
	struct	msb	irqstat;

	/*
	 * Interrupt Overrun Address Register
	 */
	struct	msb	ovrnaddr;

	/*
	 * Interrupt Overrun Priority Register
	 */
	struct	msb	ovrnpri;

	struct	msb	ns_only;	/* 32000 mode only */

	/*
	 * Interrupt error status register
	 */
	struct	msb	interr;
};

/*******************
 * Real Time Clock *
 *******************/

struct rtclock
{
	struct	msb	onesec;		/* single seconds;	0 - 9 */
	struct	msb	tensec;		/* tens of seconds;	0 - 5 */
	struct	msb	onemin;		/* single minutes;	0 - 9 */
	struct	msb	tenmin;		/* tens of minutes;	0 - 5 */
	struct	msb	onehr;		/* single hours;	0 - 9 */
	struct	msb	tenhr;		/* tens of hours;	0 - 5 */
	struct	msb	oneday;		/* single days;		0 - 9 */
	struct	msb	tenday;		/* tens of days;	0 - 3 */
	struct	msb	onemo;		/* single months;	0 - 9 */
	struct	msb	tenmo;		/* tens of months;	0 - 1 */
	struct	msb	oneyr;		/* single years;	0 - 9 */
	struct	msb	tenyr;		/* tens of years;	0 - 5 */
	struct	msb	wkday;		/* day of the week;	0 - 6 */
	struct	msb	ctlrg_d;	/* control reg. d */
	struct	msb	ctlrg_e;	/* control reg. e */
	struct	msb	ctlrg_f;	/* control reg. f */
};

/* control register d */

#define	RTC_HOLD	0x01
#define	RTC_BUSY	0x02
#define	RTC_IRQ		0x04

/* control register f */

#define RTC_RESET	0x01
#define RTC_24H		0x04

/**************************
 * Real Time Clock B68030 *
 **************************/

struct rctl {
	VOLATILE unsigned int 	w:1,	/* Write bit 		*/
			r:1,		/* Read bit 		*/
			s:1,		/* Sign Bit 		*/
			c4:1,		/* Calibration Bit 4 	*/
			c3:1,		/* Calibration Bit 3 	*/
			c2:1,		/* Calibration Bit 2 	*/
			c1:1,		/* Calibration Bit 1 	*/
			c0:1,		/* Calibration Bit 0 	*/
			not_used:24;	/* Not implemented   	*/
};

struct rt30clock
{
	struct	rctl	control;	/* control regs. 		*/
	struct	msb	sec;		/* single seconds   0-59	*/
	struct	msb	min;		/* single minutes   0-59 	*/
	struct	msb	hour;		/* single hours	    0-23 	*/
	struct	msb	day;		/* day of the week  1-7 	*/
	struct	msb	daymo;		/* day of month     1-31 	*/
	struct	msb	month;		/* month	    1-12 	*/
	struct	msb	year;		/* year		    0-99 	*/
};

#define RTC30IDX 0xffdfe0	/* Index from devmap.cpuaddr to RTC */

/********************
 * Accounting Timer *
 ********************/

struct acctimer
{
	VOLATILE ulong	data;
	VOLATILE ulong	dead[7];		/* repeats of data */
};

/*****************
 * Test Register *
 *****************/

struct testreg
{
	VOLATILE ulong	data;
	VOLATILE ulong	dead[15];		/* repeats of data */
};

#define SPAOFFSET  0xF0FF8000		/* offset to the spa */

/*********************************
 * Diagnostic Port Data Register *
 *********************************/

/************************************
 * Diagnostic Port Control Register *
 ************************************/

/********************************
 * DRAM Control/Status Register *
 ********************************/

#define CERRE		0x80000000	/* Correctable error, even memory */
#define UNCERRE		0x00800000	/* Uncorrectable error, even memory */
#define CERRO		0x00008000	/* Correctable error, odd memory  */
#define UNCERRO		0x00000080	/* Uncorrectable error, odd memory  */
#define MEMERR_RESET    0x20000000	/* Memory error reset */
#define CA_PARITY_ERR	0x00000200	/* 030 On-board cache parity bits */

/***********************************
 * Local Bus Error Status Register *
 ***********************************/

/* GACBL - Go Away, Come Back Later */

#define	GACBL_W		0x40	/* GACBL on write of RMC */
#define	GACBL_R		0x20	/* GACBL on second read during RMC */
#define	PB_LOCK		0x10	/* Physical bus lockup by cas2 */
#define	GACBL_OFLO	0x08	/* exceeded GACBL retry limit */
#define	MASTER		0x04	/* bus master disable error */
#define	NU_BERR		0x02	/* Nubus bus error */
#define	RAM_ERR		0x01	/* uncorrectable ram error */
#define	RAM_FLG		0x80	/* Accumulative ram error 1505 */

#define	SIZ_ERR		0x08	/* size error type of bus err - S1505 */

/***********************************
 * Local Timeout Status Register   *
 ***********************************/

#define	NU_TMO		0x04	/* Nubus timeout */
#define	PB_TMO		0x02	/* physical bus timeout */
#define	LB_TMO		0x01	/* logical bus timeout */

/*****************
 * Flag Register *
 *****************/

/*************************************************************
 * External Cache Control/Status & Memory Expansion Register *
 *************************************************************/

#define CMEMSR		0x00FFF7F4	/* offset of cache ctl reg */
/*
 * These bits are defined when written:
 */
#define CPU_EXEC 	0x80000000	/* enable cache */ 
#define CPU_EXFU 	0x40000000	/* flush user cache */
#define	CPU_EXFS 	0x20000000	/* flush supervisor cache */
#define CPU_DIS_CA	0x70000000	/* flush; disable cache & parity ck */
#define CPU_DIS_P	0x10000000	/* disable cache parity - 030 */
#define CPU_DSS		0x08000000	/* Unused bit-used only w/data scope */


/*
 * These bits are defined when read:
 */
#define	CPU_EXPM	0x01000000	/* 1 => expansion memory is present */
#define	CPU_EXPS	0x02000000	/* 0 => 2MB, 1 => 8MB exp. memory */

/*
 * Expansion RAM bits and mask for dramctls for 68030
 */
#define EXP_MSK	0x00700000l
#define EXP_SHF 20

/****************************
 * Configuration Register 0 *
 ****************************/

/****************************
 * Configuration Register 1 *
 ****************************/

/*********************
 * Configuration ROM *
 *********************/

#define	CPU_CROM	0xfffc00	/* offset in cpu address space */

struct crom
{
	VOLATILE char	dead[3];		/* not implemented */
	VOLATILE char	data;
};


/****************************************************************************
 * BS32 Cpu Board Layout
 ****************************************************************************/

/*
 * These registers and features exist in
 * the page beginning at 0xFFF400 of the
 * cpu's address space.
 */
struct cpu
{
	struct	icc		icc;		/* interrupt controller chip */
	VOLATILE char		dead[0x100];	/* unimplemented memory */
	struct	rtclock		rtclock;	/* real time clock */
	struct	rtclock		repeat;		/* repeated real time clock */
	struct	testreg		testreg;	/* test register */
	struct	acctimer	acctimer;	/* accounting timer */
	VOLATILE ulong		dgdata;		/* diag. port data register */
	VOLATILE ulong		dgctl;		/* diag. port control reg */
	VOLATILE ulong		dramctls;	/* DRAM control/status reg */
	struct msb		berrsr;		/* local bus error status reg */
	struct msb		toutsr;		/* local time out status reg */
	VOLATILE ulong		eccsr;		/* external cache ctl/sts reg */
	VOLATILE ulong		flagreg;	/* flag register */
	VOLATILE ulong		conf0;		/* configuration reg 0 */
};
struct cpu030
{
	struct	icc		icc;		/* interrupt controller chip */
	VOLATILE ulong		allzeros[2];
	VOLATILE ulong		acctmfp[5];
	VOLATILE ulong		spaidreg;	/* spa id register 	*/
	VOLATILE ulong		flagreg;	/* flag register	*/
	VOLATILE ulong		conf0;		/* configuration reg 0	*/
	VOLATILE ulong		scratch;	/* scratch pad		*/
	VOLATILE ulong		globalbase;	/* Nubus Global Base Reg*/
	struct	mfp_pit		mfp_pit;	/* MFP interval timer	*/
	VOLATILE ulong		reser[9];	/* Reserved space */
	VOLATILE ulong		dgdata;		/* diag. port data register */
	VOLATILE ulong		dgctl;		/* diag. port control reg */
	VOLATILE ulong		dgstat;		/* diag. port status  reg */
	VOLATILE ulong		slotid[4];	/* Nubus slot id	*/
	VOLATILE ulong		allones;
	VOLATILE ulong		unuseds[32];
	VOLATILE ulong		testreg;
	VOLATILE ulong		unuseds2[7];
	VOLATILE ulong		dramctls;	/* DRAM control/status reg */
	VOLATILE ulong		unuseds3[7];
	struct msb		berrsr;		/* local bus error status reg */
	VOLATILE ulong		unuseds4[7];
	struct msb		toutsr;		/* local time out status reg */
	VOLATILE ulong		unuseds5[7];
	VOLATILE ulong		ca_mem_ctl;	/* Cache/Memory ctl/status   */
	VOLATILE ulong		unuseds6[7];
	VOLATILE ulong		gpio;		/* general purpose I/O reg   */
};

#define	UPS_BIT_MASK	0x00200000		/* UPS active bit mask	*/

/*
 * The page beginning at 0xFFF800 is unimplemented.
 *
 * One page of configuration ROM exists beginning
 * at 0xFFFC00 in cpu address space; in this
 * region, only the LSB of each long word is
 * implemented.
 */


/*
 * /dev/ups ioctl() commands
 *
 */
#define	UPS_CPUTYPE	0	/* ioctl fails if NOT 1505	*/
#define	UPS_STATUS	1	/* report '0'/'1', batteries on?*/
#define	UPS_FW0		2	/* set forced write flag off	*/
#define	UPS_FW1		3	/* set FW on. wait for sync	*/
#define	UPS_FW2		4	/* set FW on. sync now.		*/
#define	UPS_OTSIG	5	/* cause otemp to start PF	*/
#define	UPS_NOTSIG	6	/* disable UPS_OTSIG		*/
#define	UPS_OTSTATUS	7	/* report status of overtemp	*/

/*************************************************************
 * General Puspose IO register                               *
 *************************************************************/
#define SIMM_SWITCH     0x00400000l     /* 0 = 4MB SIMMs installed
					   1 = 1MB SIMMs installed */
