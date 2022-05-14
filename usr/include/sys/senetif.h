/*
 	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1991.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/
/* @(#)senetif.h	1.3 91/06/11 */
/******************************************************************
*                                                                 
*  Streams Ethernet driver (senet) ioctl interface call blocks	
*
******************************************************************/

#define SENET_ATCH	0x00000002	/* attach unit */
#define SENET_STAT	0x00000003	/* get network statistics */
#define SENET_GADR	0x00000004	/* get host address */
#define SENET_SADR	0x00000005	/* set host address */
#define SENET_RMCAST	0x00000006	/* register multicast address */
#define SENET_DMCAST	0x00000007	/* de-register multicast address */


struct atchioctl {		/* net stats command block */
	int	dev_num;	/* encoded device number, 0s000000, s = slot */
};

struct sSTAThead {
	int  clearflag;
};

struct statioctl {		/* net stats command block */
	struct sSTAThead stathead;
	struct sLCstatbuf statbuf;
};

struct adrioctl {		/* get host address command block */
	unsigned char enetadr[6];	/* 48-bit address */
};

struct sadrioctl {		/* set host address command block */
	int	dev_num;	/* encoded device number, 0s000000, s = slot */
	unsigned char enetadr[6];	/* 48-bit address */
};

struct mcastioctl {		/* reg/dereg multicast address command block */
	unsigned char mcastadr[6];	/* one multicast address */
};

