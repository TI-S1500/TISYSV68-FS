/*
   COPYRIGHT (c) 1986 TEXAS INSTRUMENTS, INCORPORATED.  ALL RIGHTS RESERVED.
*/
/*
static char *sccs_id = "@(#)dial.h	1.3 91/10/18";
*/
#ifndef IUCLC
#include <sys/termio.h>
#endif

#define	TRUE	1
#define FALSE	0

		/* error mnemonics */

#define INTRPT	(-1)	/* unexpected failure */
#define D_HUNG	(-2)	/* dial failed *
#define NO_ANS	(-3)	/* caller script failed */
#define A_PROB	(-5)	/* device failed */
#define L_PROB	(-6)	/* can't access device */
#define NO_Ldv	(-7)	/* can't open Devices file */
#define DV_NT_A	(-8)	/* device locked */
#define NO_BD_A	(-10)	/* no devices available */
#define BAD_SYS (-13)	/* system not in Systems file */

typedef struct {
	struct termio *attr;	/* ptr to termio attribute struct */
	int	baud;		/* unused */
	int	speed;		/* line speed */
	char	*line;		/* device name for out-going line */
	char	*telno;		/* ptr to tel-no digits string or remote
					location name */
	int	modem;		/* unused */
	char	*device;	/* unused */
	int	dev_len;	/* unused */
} CALL;

extern int dial();
extern void undial();
