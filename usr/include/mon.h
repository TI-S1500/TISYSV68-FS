/*
   COPYRIGHT (c) 1986 TEXAS INSTRUMENTS, INCORPORATED.  ALL RIGHTS RESERVED.
*/
/*
static char *sccs_id = @(#)mon.h	1.1 86/05/15";
*/
/*	@(#)mon.h	1.6	*/
struct hdr {
	char	*lpc;
	char	*hpc;
	int	nfns;
};

struct cnt {
	char	*fnpc;
	long	mcnt;
};

typedef unsigned short WORD;

#define MON_OUT	"mon.out"
#ifdef m68k
#define MPROGS0	(300 * sizeof(WORD))	/* We want 600!!! */
#else
#define MPROGS0	(150 * sizeof(WORD))	/* 300 for pdp11, 600 for 32-bits */
#endif
#define MSCALE0	4
#define NULL	0
