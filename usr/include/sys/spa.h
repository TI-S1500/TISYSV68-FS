/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/
/*
 *	@(#)spa.h	1.10 (Texas Instruments) 90/11/20
 */

/* software protection adapter (SPA) */

#ifdef __STDC__
#define VOLATILE volatile
#else
#define VOLATILE
#endif

#define 	MAXKEYLEN	80	/* Maximum key length		*/
#define		SPATSTPAT	0x00FFAA55	/* test pattern		*/

#define		PASS		1
#define		FAIL		0
#define 	TRUE		1
#define 	FALSE		0


#define MODULUS    128   /* base for using decimal digits           */

#define max(a,b) (a < b ? b : a)
#define min(a,b) (a > b ? b : a)
#define abs(x)   x >= 0 ? x : -(x))

#define		SPA		's'
#define		SP_ID		((SPA<<8)|0)
#define		SP_KEY		((SPA<<8)|1)
#define		SP_SAF		((SPA<<8)|2)
#define		SP_INC		((SPA<<8)|3)
#define		SP_DEC		((SPA<<8)|4)
#define		SP_SFR		((SPA<<8)|5)
#define		SP_UC		((SPA<<8)|6)
#define		SP_KUC		((SPA<<8)|7)
#define		DEVSPA		"/dev/spa"
#define		SOFTPWF		"/etc/softpwd"
/*
 * If any changes are made to the SPA structure these hardcoded offsets
 * MAY need to be changed
 */
#define TPOSET		112	/* Test pattern offset	*/
#define KEYOSET		5	/* SPA KEY offset	*/
#define KEYLOSET	4	/* SPA KEY LENGTH offset*/

struct spa_def
{
	 VOLATILE long	 id;	 /* SPA ID number		*/
	 VOLATILE unchar keylen; /* Length of public key 	*/
	 VOLATILE unchar key[MAXKEYLEN]; /* Public key		*/
	 VOLATILE unchar x1;	/* Alignment character		*/
	 VOLATILE char idstring[26];/* Identifier string common to	*/
				/* all SPAs			*/
				/* (C) Texas Instruments 1986	*/
	 VOLATILE long	tp;	/* Test patterns 00FFAAff	*/
	 VOLATILE char	date[24]; /* Date SPA manufactured	*/
	 VOLATILE unchar ranum[114]; /* Random numbers		*/
	 VOLATILE ushort crc;	/* CRC 16 area			*/
};

struct softwd {
	char	*sp_softid;		/* software identifier		*/
	char	*sp_ctpw;		/* ciphertext password		*/
	char	*sp_comment;		/* comment field		*/
};

union spapw {
	struct {
		long	*id;		/* pointer to stuff SPA ID	*/
	} id;

	struct {
		char	*key;		/* pointer to stuff SPA KEY	*/
		short	key_l;		/* length of SPA KEY		*/
	} key;

	struct {
		char	*ctpw;		/* pointer to ciphertext passwd	*/
		char	*ptpw;		/* pointer to plaintext passwd	*/
		short	ctpw_l;		/* length of ciphertext passwd	*/
		short	ptpw_l;		/* lingth of plaintext passwd	*/
	} safe;

	struct {
		char	*ctpw;		/* pointer to ciphertext passwd	*/
		char	*ptpw;		/* pointer to plaintext passwd	*/
		short	ctpw_l;		/* length of ciphertext passwd	*/
		short	ptpw_l;		/* length of plaintext passwd	*/
		char	*encr;		/* pointer to ciphertext code	*/
		char	*pwdid;		/* pointer to passwdid string	*/
		long	sd;		/* seed value 			*/
		short	encr_l;		/* length of ciphertext code	*/
		short	pwdid_l;	/* length of passwdid string	*/
	} safer;
};
