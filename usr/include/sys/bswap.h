/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char bswap_h[] = "@(#)bswap.h	1.3 (TI) 86/02/04";
#endif	SCCSID

#ifndef SCCSID
 
/*	bswap.h	1.3	2/4/86	*/

#ifdef DEF_SCCS
static char vs_bswap[] = "@(#)bswap.h	1.3";
#else

struct nulong
{
	char a, b, c, d;
};

struct nushort
{
	char a, b;
};

struct m68long
{
	char d, c, b, a;
};

struct m68short
{
	char b, a;
};

/* byte swap long words */
#define lswap(x,y) {\
	((struct nulong *)(x))->a = ((struct m68long *)(y))->a; \
	((struct nulong *)(x))->b = ((struct m68long *)(y))->b; \
	((struct nulong *)(x))->c = ((struct m68long *)(y))->c; \
	((struct nulong *)(x))->d = ((struct m68long *)(y))->d; \
}

/* byte swap short words */
#define sswap(x,y) {\
	((struct nushort *)(x))->a = ((struct m68short *)(y))->a; \
	((struct nushort *)(x))->b = ((struct m68short *)(y))->b; \
}

#endif DEF_SCCS
 
#endif
