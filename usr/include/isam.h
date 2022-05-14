/*
 *  COPYRIGHT (c) 1986, 1987, 1988, 1989, 1990, 1991, 1992 TEXAS INSTRUMENTS,
 *  INCORPORATED.  ALL RIGHTS RESERVED.
 *
 *  COPYRIGHT (c) 1992, 1993 HEWLETT-PACKARD COMPANY.  ALL RIGHTS RESERVED.
 *
 *  @(#)isam.h (T-ISAM) version 2.8.8  (18 February 1993)
 */
#ifndef	ISINCLUDE
#define	ISINCLUDE	


/*==============================================================================
	KEY DESCRIPTOR - Used by isbuild(), isaddindex(), isstart() and
			 isindexinfo()
==============================================================================*/
#define	NPARTS		8

/*----- The Key Descriptor structure -----------------------------------------*/
struct	keypart
{
	short	kp_start;
	short	kp_leng;
	short	kp_type;
};

struct	keydesc
{
		short	k_flags;
		short	k_nparts;
	struct	keypart	k_part[NPARTS];
};

/*----- k_flags values -------------------------------------------------------*/
#define	ISNODUPS	0x0000		/* duplicates are not allowed */
#define	ISDUPS		0x0001		/* duplicates are allowed */
#define	DCOMPRESS	0x0002		/* key compression */
#define	LCOMPRESS	0x0004		/* key compression */
#define	TCOMPRESS	0x0008		/* key compression */
#define	COMPRESS	0x000e		/* key compression */

/*----- kp_type values and sizes ---------------------------------------------*/
#define	CHARTYPE	0x0000		/* field is CHARTYPE */
#define	INTTYPE		0x0001		/* field is INTTYPE */
#define	LONGTYPE	0x0002		/* field is LONGTYPE */
#define	DOUBLETYPE	0x0003		/* field is DOUBLETYPE */
#define	FLOATTYPE	0x0004		/* field is FLOATTYPE */
#define	DECIMALTYPE	CHARTYPE	/* field is DECIMALTYPE */
#define	ISDESC		0x0080		/* field is descending */

#define	CHARSIZE	0x0001		/* length of CHARTYPE item */
#define	INTSIZE		0x0002		/* length of INTTYPE item */
#define	LONGSIZE	0x0004		/* length of LONGTYPE item */
#define	FLOATSIZE	0x0004		/* length of FLOATTYPE item */
#define	DOUBLESIZE	0x0008		/* length of DOUBLETYPE item */

#define	MAXKEYSIZE	120		/* not used */


/*==============================================================================
	DICTIONARY DESCRIPTOR - Used by isindexinfo
==============================================================================*/

struct	dictinfo
{
	short	di_nkeys;	/* number of user keys */
	short	di_recsize;	/* (maximum) data record size */
	short	di_idxsize;	/* index record length */
	long	di_nrecords;	/* number of data records */
};


/*==============================================================================
	FILE USAGE CONSTANTS
==============================================================================*/
/*----- Used by isopen(), isbuild(), and islock() ----------------------------*/
#define	ISINPUT		0x0000		/* input only */
#define	ISOUTPUT	0x0001		/* output only */
#define	ISINOUT		0x0002		/* input or output */

#define	ISAUTOLOCK	0x0200		/* automatic locking/unlocking */
#define	ISMANULOCK	0x0400		/* manual locking */
#define	ISEXCLLOCK	0x0800		/* exclusive file access */

#define	ISMULTLOCK	0x8000		/* automatic locking, no unlock */
#define	ISWRITLOCK	0x4000		/* automatic locking on (re)write */
#define	ISCOMMIT	ISMULTLOCK
#define	ISWLOCK		ISWRITLOCK

/*----- Used by isread() and isstart() ---------------------------------------*/
#define	ISFIRST		0x0000		/* first key in current index */
#define	ISLAST		0x0001		/* last key in current index */
#define	ISNEXT		0x0002		/* next key in current index */
#define	ISPREV		0x0003		/* previous key in current index */
#define	ISCURR		0x0004		/* current key */
#define	ISEQUAL		0x0005		/* key equal to spec value */
#define	ISGREAT		0x0006		/* smallest key greater than spec val */
#define	ISGTEQ		0x0007		/* smallest key greater/equal spec val*/

#define	ISLOCK		0x0100		/* lock record */
#define	ISNOLOCK	0x0800		/* internal */


/*==============================================================================
	AUDIT TRAIL
==============================================================================*/

/*----- Commands for isaudit() -----------------------------------------------*/
#define	AUDSETNAME	0x0000		/* store pathname in data file */
#define	AUDGETNAME	0x0001		/* load pathname from data file */
#define	AUDSTART	0x0002		/* start audit trail */
#define	AUDSTOP		0x0003		/* stop audit trail */
#define	AUDINFO		0x0004		/* audit trail status */

/*----- Overhead struct that preceeds data record in audit trail -------------*/
struct audhead
{
	char	au_type[2];		/* operation type: dd, aa, rr, or ww */
	char	au_time[4];		/* time of operation */
	char	au_procid[2];		/* process id */
	char	au_userid[2];		/* user id */
	char	au_recnum[4];		/* record number */
};

#define	AUDHEADSIZE	14


/*==============================================================================
	iserrio VALUES
==============================================================================*/
#define	IO_OPEN		0x0010		/* error on open */
#define	IO_CREA		0x0020		/* error on create */
#define	IO_SEEK		0x0030		/* error on lseek */
#define	IO_READ		0x0040		/* error on read */
#define	IO_WRIT		0x0050		/* error on write */
#define	IO_LOCK		0x0060		/* error on fcntl */
#define	IO_IOCTL	0x0070		/* error on ioctl */

#define	IO_IDX		0x0001		/* system error on index file */
#define	IO_DAT		0x0002		/* system error on data file */
#define	IO_AUD		0x0003		/* system error on audit file */
#define	IO_LOK		0x0004		/* not used */
#define	IO_SEM		0x0005		/* not used */


/*==============================================================================
	iserrno VALUES
==============================================================================*/
#define	EDUPL		100		/* duplicate value not allowed */
#define	ENOTOPEN	101		/* file not open */
#define	EBADARG		102		/* bad argument */
#define	EBADKEY		103		/* bad key descriptor format */
#define	ETOOMANY	104		/* too many files open */
#define	EBADFILE	105		/* bad file format */
#define	ENOTEXCL	106		/* must be opened exclusive */
#define	ELOCKED		107		/* record locked */
#define	EKEXISTS	108		/* key descriptor exists */
#define	EPRIMKEY	109		/* can't delete primary key */
#define	EENDFILE	110		/* beginning or end of file */
#define	ENOREC		111		/* index or key (record) not found */
#define	ENOCURR		112		/* currency lost/undefined */
#define	EFLOCKED	113		/* file is locked */
#define	EFNAME		114		/* file name is too long */
#define	ENOLOK		115		/* not used */
#define	EBADMEM		116		/* not enough memory */
#define	EBADCOLL	117		/* not used */


/*==============================================================================
	DEFINE FUNCTIONS WHICH DO NOT RETURN int VALUES.
==============================================================================*/
	extern long		 ldlong();
	extern double		 ldfloat();
	extern double		 lddbl();

	extern unsigned char	*stint();
	extern unsigned char	*stlong();
	extern unsigned char	*stfloat();
	extern unsigned char	*stdbl();


/*==============================================================================
	GLOBAL VARIABLES AND DEFAULT/INITIAL VALUES.
==============================================================================*/

#ifdef	ISDEFSPACE
	unsigned int	 iserrno	= 0;	/* error code */
	unsigned int	 iserrio	= 0;	/* error info */
	unsigned char	 isstat1	= 0;	/* status byte 1 */
	unsigned char	 isstat2	= 0;	/* status byte 2 */

	         char	 isversnumber[]	= "tisam";
	         char	 iscopyright[]	= "tisam";
	         char	 isserial[]	= "tisam02.08.8";

	unsigned int	 issingleuser	= 0;	/* not used */
	unsigned int	 is_nerr	= 117;	/* not used */
	         char	*is_errlist[]	= {"", "", "", "", "", "",
					   "", "", "", "", "", "",
					   "", "", "", "", "", ""};
						/* not used */
	unsigned long	 isrecnum	= 0;	/* record offset */
#else
	extern	unsigned int	 iserrno;
	extern	unsigned int	 iserrio;
	extern	unsigned char	 isstat1;
	extern	unsigned char	 isstat2;

	extern	         char	*isversnumber;
	extern	         char	*iscopyright;
	extern	         char	*isserial;

	extern	unsigned int	 issingleuser;
	extern	unsigned int	 is_nerr;
	extern	         char	*is_errlist[];

	extern	unsigned long	 isrecnum;
#endif

#ifdef	ISDEFSPACE
	unsigned int	 isreclnu	= -1;	/* data bytes desired */
	unsigned int	 isreclnr	= 0;	/* data bytes returned */

	unsigned long	 iskdid		= 0;	/* unique key id */
	unsigned short	 isflage	= 0;	/* tisam k_flage */
	unsigned short	 isflagr	= 0;	/* tisam k_flage returned */
	unsigned long	 ismode		= 0;	/* tisam default mode */
	unsigned long	 isxxisam	= 0L;	/* internal */
#else
	extern	unsigned int	 isreclnu;
	extern	unsigned int	 isreclnr;

	extern	unsigned long	 iskdid;
	extern	unsigned short	 isflage;
	extern	unsigned short	 isflagr;
	extern	unsigned long	 ismode;
	extern	unsigned long	 isxxisam;
#endif

#define	ISMFISAM	0x00000001L		/* internal */

#endif
