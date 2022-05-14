/*
 *  COPYRIGHT (c) 1986, 1987, 1988, 1989, 1990 TEXAS INSTRUMENTS,
 *  INCORPORATED.  ALL  RIGHTS RESERVED.
 *
 *  @(#)tisam.h	(T-ISAM) version 2.7.2  (20 July 1990)
 */
#ifndef	TIINCLUDE
#define	TIINCLUDE

/*==============================================================================
	MAXIMUM VALUES AND LENGTHS
==============================================================================*/
#define	TIMAXFILENAME	64		/* maximum file name length */
#define	TIMAXREC	0xfa00		/* maximum record length */
#define	TIMAXKEY	120		/* maximum key length */
#define	TIVNLEN		8		/* maximum version name length */
#define	TINFIELD	8		/* number of key fields */


/*==============================================================================
	KEY DESCRIPTOR - Used by tibuild(), tiaddindex(), tistart(), and
			tiindexinfo()
==============================================================================*/

/*----- The Key Descriptor structure -----------------------------------------*/
struct	tikeypart
{
	short	kp_start;		/* offset to part array(field) */
	short	kp_leng;		/* length of part array(field) */
	short	kp_type;		/* type of part array(field) */
};

struct	tikeydesc
{
		short		k_flags;		/* cisam flags */
		short		k_nparts;		/* number of parts */
	struct	tikeypart	k_part[TINFIELD];	/* key part array */
		short		k_flage;		/* extended flags */
		short		k_type;			/* INTERNAL USE */
		long		k_kdid;			/* key ID */
};

/*----- k_flags values -------------------------------------------------------*/
#define	TINODUP		0x0000		/* duplicates are not allowed */
#define	TIKEYDUP	0x0001		/* duplicates are allowed */
#define	TIKEYCMP	0x000e		/* compress key */

/*----- k_flage values -------------------------------------------------------*/
#define	TIKEYSTR	0x0001		/* (auto store) */
#define	TIKEYID		0x0002		/* (id only) */
#define	TIKEYNOA	0x0004		/* no ANSI currency */
#define	TIKEYVAL	0x0008		/* validate key */
#define	TIKEYEVN	0x0010		/* round to even length */
#define	TIKEYFAS	0x0020		/* faster processing of duplicate */
					/*   keys.  no ANSI currency kept.*/

/*----- kp_type values and associated lengths --------------------------------*/
#define	TIFCHR		0x0000		/* field is CHARTYPE */
#define	TIFINT		0x0001		/* field is INTTYPE */
#define	TIFLNG		0x0002		/* field is LONGTYPE */
#define	TIFDBL		0x0003		/* field is DOUBLETYPE */
#define	TIFFLT		0x0004		/* field is FLOATTYPE */
#define	TIFDESC		0x0080		/* field is descending */

#define	TILCHR		0x0001		/* length of CHARTYPE item */
#define	TILINT		0x0002		/* length of INTTYPE item */
#define	TILLNG		0x0004		/* length of LONGTYPE item */
#define	TILFLT		0x0004		/* length of FLOATTYPE item */
#define	TILDBL		0x0008		/* length of DOUBLETYPE item */


/*==============================================================================
	DICTIONARY DESCRIPTOR - Used by tiindexinfo()
==============================================================================*/

struct	tidictinfo
{
	short	di_nkeys;		/* number of user keys */
	short	di_recsize;		/* maximum data record length */
	short	di_idxsize;		/* index(device) record length */
	long	di_nrecords;		/* number of data records */
	char	di_vernum[TIVNLEN];
	char	di_idxname[TIMAXFILENAME];
};


/*==============================================================================
	FILE USAGE CONSTANTS
==============================================================================*/
/*----- Internal constants ---------------------------------------------------*/
#define	TILOG		0x40000000L	/* internal */
#define	TISWDAT		0x20000000L	/* internal */
#define	TISWKEY		0x10000000L	/* internal */
#define	TIAUDIT		0x04000000L	/* internal */
#define	TIREWLOG	0x02000000L	/* internal */
#define	TINOLOCK	0x00000800L	/* internal */
#define	TIUNLOCK	0x00000100L	/* internal */
#define	TILESS		0x00000020L	/* internal */

/*----- Used by tibuild() and tiopen() ---------------------------------------*/
#define	TIINPUT		0x00000001L	/* input only */
#define	TIOUTPUT	0x00000002L	/* output only */
#define	TIINOUT		0x00000003L	/* input and output */

#define	TIEXCLLOCK	0x00000004L	/* exclusive file access */
#define	TIAUTOLOCK	0x00000008L	/* automatic locking/unlocking */ 
#define	TIMANULOCK	0x00000010L	/* manual locking */
#define	TIMULTLOCK	0x00008000L	/* automatic locking/no unlock */
#define	TIWRITLOCK	0x00004000L	/* automatic lock for write/rewrite */
#define	TIZEROL		0x00000000L

/*----- Used by tilock() -----------------------------------------------------*/
#define TIREADLK	TIINPUT		/* apply "read lock" to file. */
#define TIWRITLK	TIOUTPUT	/* apply "write lock" to file. */

/*----- Used by tioption() ---------------------------------------------------*/
#define	TIADVLOCK	0x00002000L	/* advance currency on locked record */
#define	TICOMPRESS	0x08000000L	/* compress data records */
#define	TINOFREE	0x80000000L	/* don't record free space */
#define	TINOEXCLLOCK	0x00001000L	/* disable exclusive opens */
#define	TISLEPLOCK	0x00000200L	/* read with sleep-on-lock */

#define	TIPROSAFE	TILOG			/* integrity across aborts */
#define	TIDATSAFE	(TILOG|TISWDAT)		/* data file integrity */
#define	TIKEYSAFE	(TILOG|TISWDAT|TISWKEY)	/* key+data file integrity */
#define	TISYSSAFE	(TILOG|TISWDAT|TISWKEY)	/* key+data file integrity */
#define	TIREWSAFE	(TILOG|TIREWLOG)	/* slow, safe rewrites */

#define	TIOPTSET	0x0001		/* Set options */
#define	TIOPTGET	0x0002		/* Get options */
#define	TIOPTGLOBAL	0x8000		/* Global set/get options */

/*----- Used by tiread() and tistart() ---------------------------------------*/
#define	TIFIRST		0x00000001L	/* First key in current index */
#define	TILAST		0x00000002L	/* Last key in current index */
#define	TICURR		0x00000008L	/* Current key */
#define	TIEQUAL		0x00000040L	/* Key eaual to spec value */
#define	TIGREAT		0x00000080L	/* Smallest key greater than spec val */
#define	TIGTEQ	  (TIEQUAL|TIGREAT)	/* Smallest key greater than or equal
						to spec value */

/*----- Used by tiread() only -----------------------------------------------*/
#define	TIPREV		0x00000004L	/* Previous key */
#define	TINEXT		0x00000010L	/* Next key */

#define	TILOCK		0x00000100L	/* Lock record */
#define	TISLOCK		0x00000200L	/* Sleep lock */


/*----- Used by tifree() only -----------------------------------------------*/
#define TIKEY		0x00000001L	/* Key File */
#define TIDAT		0x00000002L	/* Data File */

/*==============================================================================
	AUDIT TRAIL
==============================================================================*/

/*----- Commands for tiaudit() -----------------------------------------------*/
#define	TIAUDSETNAME	0x0000		/* store pathname in data file  */
#define	TIAUDGETNAME	0x0001		/* load pathname from data file */
#define	TIAUDSTART	0x0002		/* start audit trail            */
#define	TIAUDSTOP	0x0003		/* stop audit trail             */
#define	TIAUDINFO	0x0004		/* audit trail status           */

/*----- Overhead struct that preceeds data record in audit trail -------------*/
struct tiaudhead
{
	char	au_type[2];		/* operation type: dd, aa, rr, or ww */
	char	au_time[4];		/* time of operation                 */
	char	au_procid[2];		/* process id                        */
	char	au_userid[2];		/* user id                           */
	char	au_recnum[4];		/* record offset in data file        */
};

#define	TIAUDHEADSIZE	14		/* size of struct tiaudhead          */


/*==============================================================================
	tierrio VALUES
==============================================================================*/
#define	TIOE_OPEN	0x0010		/* error on open */
#define	TIOE_CREA	0x0020		/* error on create */
#define	TIOE_SEEK	0x0030		/* error on lseek */
#define	TIOE_READ	0x0040		/* error on read */
#define	TIOE_WRIT	0x0050		/* error on write */
#define	TIOE_LOCK	0x0060		/* error on fcntl */
#define	TIOE_IOCTL	0x0070		/* error on ioctl */
#define	TIOE_FSTAT	0x0080		/* error on fstat */
#define	TIOE_LINK	0x0090		/* error on link */
#define	TIOE_CLOSE	0x00a0		/* error on close */

#define	TIOE_IDX	0x0001		/* system error on index file */
#define	TIOE_DAT	0x0002		/* system error on data file */
#define	TIOE_AUD	0x0003		/* system error on audit file */


/*==============================================================================
	tierrno VALUES
==============================================================================*/
#define TIE_DUPL	100		/* duplicate key values not allowed */
#define	TIE_NOTOPEN	101		/* file not open */
#define	TIE_BADARG	102		/* bad argument */
#define	TIE_BADKEY	103		/* bad key descriptor format */
#define	TIE_TOOMANY	104		/* too many files open */
#define	TIE_BADFILE	105		/* bad file format */
#define	TIE_NOTEXCL	106		/* file must be opened exclusive */
#define	TIE_LOCKED	107		/* record locked */
#define	TIE_KEXISTS	108		/* key descriptor exists */
#define	TIE_PRIMKEY	109		/* can't delete primary key */
#define	TIE_ENDFILE	110		/* beginning or end of file */
#define	TIE_NOREC	111		/* index or key (record) not found */
#define	TIE_NOCURR	112		/* currency lost/undefined */
#define	TIE_FLOCKED	113		/* file is locked */
#define	TIE_FNAME	114		/* file name is too long */
#define	TIE_NOLOK	115		/* not used */
#define	TIE_BADMEM	116		/* not enough memory */

#define	TIE_ALTERTREE	120		/* not used */
#define	TIE_OVERRUN	121		/* internal */
#define	TIE_REBUILD	123		/* it is necessary to rebuild the file*/
#define TIE_BADIDX	124		/* index file does not match data file*/
#define TIE_FEATURES	125		/* feature mismatch */
#define TIE_FORK	126		/* detected "fork()" with open file */
#define TIE_RECLEN	127		/* invalid record length */
#define TIE_REDEF	128		/* file redefined by other user */


/*==============================================================================
	DEFINE TISAM FUNCTIONS WHICH DO NOT RETURN int VALUES.
==============================================================================*/
	long		ldlong();
	double		ldfloat();
	double		lddbl();

	unsigned char	*stint();
	unsigned char	*stlong();
	unsigned char	*stfloat();
	unsigned char	*stdbl();

	long		tioption();


/*==============================================================================
	GLOBAL T-ISAM VARIABLES AND DEFAULT/INITIAL VALUES.
==============================================================================*/
#ifdef	TIDEFSPACE
	unsigned long	tiopt		= 0L;	/* default options at build */
	unsigned short	tiflgs		= 0;	/* OR'ed to k_flags */
	unsigned short	tiflge		= 0;	/* OR'ed to k_flage */
	unsigned short	tiflgds		= 0;	/* OR'ed to k_flags if dups */
	unsigned short	tiflgde		= 0;	/* OR'ed to k_flage if dups */
	unsigned int	tinbmx		= 24;	/* desired cache size */

	unsigned int	tireclnr	= 0;	/* data bytes returned */
	unsigned long	tirecid		= 0L;	/* data record offset */
	unsigned long	tinxtid		= 0L;	/* nest data record offset */

	unsigned int	tierrno		= 0;	/* error code */
	unsigned int	tierrio		= 0;	/* I/O error information */
	unsigned char	tistat1		= '0';	/* status byte 1 */
	unsigned char	tistat2		= '0';	/* status byte 2 */

	         char	tivernum[]	= "02.07.2";	/* internal */
	unsigned char	tivchr		= ' ';		/* internal */
	unsigned long	tiodid		= 1024L;	/* internal */
	unsigned long	tixxisam	= 0L;		/* internal */
	int		(*tiaddx)()	= (int(*)())0;  /* internal */

#else
	extern	unsigned long	tiopt;
	extern	unsigned short	tiflgs;
	extern	unsigned short	tiflge;
	extern	unsigned short	tiflgds;
	extern	unsigned short	tiflgde;
	extern	unsigned int	tinbmx;

	extern	unsigned int	tireclnr;
	extern	unsigned long	tirecid;
	extern	unsigned long	tinxtid;
	extern	unsigned char	tivchr;

	extern	unsigned int	tierrno;
	extern	unsigned int	tierrio;
	extern	unsigned char	tistat1;
	extern	unsigned char	tistat2;

	extern	         char	tivernum[];
	extern	unsigned char	tivchr;
	extern	unsigned long	tiodid;
	extern	unsigned long	tixxisam;
	extern  int		(*tiaddx)();

#endif

#define	TIMFISAM	0x00000001L	/* internal */
#define TIREISAM	0x00000002L	/* internal */

#endif
