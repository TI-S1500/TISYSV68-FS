/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char partab_h[] = "@(#)partab.h	1.4 (TI) 87/04/30";
#endif	SCCSID

#define MAXPENTRY	255		/* max number of partition entries */
#define SIZEPENTRY      sizeof(struct ptabe)/4  /* size of each entry */
#define SIMPUSER	1		/* defines which P_USERTYPE to use */
#define PTEOVERHD	16		/* number of bytes of overhead in  */
					/* ptabe. i.e. not the comment field */
/*************************************************************************
**  NOTE:								**
**    A 68010 will not handle shorts across word boundries              **
**    which is exactly what happens to the "user type" in the           **
**    Partition Table Entry structure.  So, 2 versions of a macro       **
**    were written to handle it.                                        **
**									**
**    The first is more generic and can be use for any alignment	**
**    problem.  Just pass in the address of the first "char" and	**
**    the macro returns an "short"					**
**									**
**    The second is a little more complicated				**
**    in the fact it understands the structure and when called		**
**    with JUST the address of the target structure it returns		**
**    an unsigned short.						**
**									**
*************************************************************************/

#ifdef SIMPUSER
#define P_USERTYPE(x)	(unsigned short)((*(x+1)<<8) | *x)
#else
#define P_USERTYPE(x)	(unsigned short)(((struct ptabe *)x)->p_user[1])<<8 \
			| (((struct ptabe *)x)->p_user[0])
#endif

	/* Partition table entry */

struct ptabe 
{ 
	char	p_name[4];		/* partition name */
	int	p_strtblk; 		/* start block number of partition */
	int	p_length; 		/* length of partition in blocks */
	unsigned char p_functype; 	/* function type */
	unsigned char p_user[2];	/* user type */
	unsigned char p_property; 	/* property bits */
	char	p_comment[48]; 		/* partition comment */
};

/*	Map for partition table 	*/

struct ptab
{
	char	label[4];		/* partition table indicator "PRTN" */
	int	revnum;			/* revision number */
	int     numpart;		/* number of partitions in table */
	int	pentrylth;		/* size of each table entry */
	int	commoffset;		/* offset to comment in 32 bit words */
	int	res1[11];		 /* reserved for future info */
};
