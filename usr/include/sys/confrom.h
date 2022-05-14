/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1986.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char confrom_h[] = "@(#)confrom.h	1.4 (TI) 86/09/19";
#endif	SCCSID

/* Contents of configuration ROM header */
/* note that only every fourth address refers to an actual physical byte */

struct confhdr
{
	char	nu_test[3];
	char	sub_base[8];
	char	restart[3];
	char	event[3];
	char    evnt2[3];
	char	nvsiz[1];
	char	nvoff[3];	
	char	resource;	/* resources for boot procedure */
	char	id_byte;	/* known value 0xC3 */
	char	testtime;	/* log2 of self-test time */
	char	format;		/* ID ROM format : currently 03 */
	char	flags;		/* flags */
	char	flgoffs[3];	/* board offset of device flag register */
	char	diagoffs[3];	/* board offset of diagnostic if any */
	char	drvoffs[3];	/* ROM offset of device driver if any */
	char	cfoffs[3];	/* board offset of config register */
	char	part[16];	/* assembly part number */
	char	boardtype[8];	/* generic name of the board and info */
	char	vendor[4];	/* vendor id */
	char	romsize;	/* log2 of ROM size in bytes */
#define NONCRC	18		/* number of bytes not used in CRC check */
	unsigned short crcsum;	/* checksum of bytes in ROM */
	char	rev[7];		/* assembly revision level */
	char	serial[9];	/* serial number */
};
#define CONFADDR 0x01000000l

/***
*  Masks for resource byte
***/
/* bit 0 indicates resource with system memory */
#define RES_RAM 	0x01
/* bit 1 indicates resource is a boot source */
#define RES_LOAD	0x02
/* bit 2 indicates resource is a local area network resource */
#define RES_LAN		0x04
/* bit 3 indicates resource is an STBM monitor resource */
#define RES_MON		0x08
/* bit 4 indicates resource is a bootable processor */
#define RES_CPU		0x10
/* bit 5 indicates resource is an STBM keyboard resource */
#define RES_KEY		0x20
/* bit 6 indicates resource has Non Volatile RAM */
#define RES_NVR		0x40
/* bit 7 indicates resource has sub boards */
#define RES_SUB		0x80 

/***
* Mask for ROM FLAGS
***/
/* bit 0 indicates capable of selftest */
#define FLG_ST 		0x01
/* bit 1 indicates nubus test candidate */
#define FLG_NT		0x02
/* bit 2 indicates STBM candidate (potential master) */
#define FLG_STBM	0x04
/* bit 3 indicates device supports block moves */
#define FLG_BM		0x08
/* bit 4 indicates resource contains system memory */
#define FLG_MEM		0x10
/* bit 5 indicates needs power-fail event */
#define FLG_PFE		0x20
/* bit 6 indicates NuBus test pointer field valid */
#define FLG_NBP		0x40
/* bit 7 indicates slave device */
#define FLG_SLAVE	0x80 

/* remarks on the configuration ROM fields */


/* BOARD TYPE - MEM..., CPU..., DSK..., SIB... */

/* VENDOR ID - TIIR for Irvine, TIAU for Austin, (blank)LMI for LMI */

/* SERIAL NUMBER - date + place of manufacture, not included in CRC */
/* byte 7   WEEK, two BCD digits specifying week of manufacture (01-52) */
/* byte 6   YEAR, alphanumeric: 1983=3, 1992=2, 1993=A, 2118=Z */
/* byte 5-3 SITE, three char alphanumeric indicating co. + site of manu. */
/* byte 2-0 SEQUENCE NUMBER, 5 digit hex, right adjusted, that uniquely
		identifies all assemblies built on a weekly level. */
