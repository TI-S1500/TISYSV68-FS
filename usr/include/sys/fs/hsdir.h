
/*	Copyright (C) The Santa Cruz Operation, 1989, 1990.	*/

/*	This Module contains Proprietary Information of		*/
/*	The Santa Cruz Operation and should be treated		*/
/*	as Confidential.					*/

#ifdef SCCSID
static char hsdir_h[] = "@(#)hsdir.h	1.1 91/03/12"
#endif SCCSID

						/* BEGIN SCO_FS */
#ifndef	_SYS_FS_HSDIR_H
#define	_SYS_FS_HSDIR_H

/*
 * ISO-9660 filesystem directory entry
 */

struct isdir
{
	unchar	d_len_dr[1];	/* length of directory record	*/
	unchar	d_xalen[1];	/* length of extended attributes*/
	unchar	d_start[8];	/* start of extent		*/
	unchar	d_size[8];	/* size of extent		*/
	unchar	d_rtime[6];	/* recording date & time	*/
	unchar	d_tz[1];	/* timezone			*/
	unchar	d_flags[1];	/* file flags			*/
	unchar	d_unitsz[1];	/* file unit size		*/
	unchar	d_igap[1];	/* interleave gap		*/
	unchar	d_volseq[4];	/* volume sequence #		*/
	unchar	d_len_fi[1];	/* file identifier length	*/
	unchar	d_file_id[1];	/* file identifier		*/
};

typedef struct isdir	isdir_t;

/*
 * High Sierra filesystem directory entry
 */

struct hsdir
{
	unchar	d_len_dr[1];	/* length of directory record	*/
	unchar	d_xalen[1];	/* length of extended attributes*/
	unchar	d_start[8];	/* start of extent		*/
	unchar	d_size[8];	/* size of extent		*/
	unchar	d_rtime[6];	/* recording date & time	*/
	unchar	d_flags[1];	/* file flags			*/
	unchar	d_xxx[1];	/* ???				*/
	unchar	d_unitsz[1];	/* file unit size		*/
	unchar	d_igap[1];	/* interleave gap		*/
	unchar	d_volseq[4];	/* volume sequence #		*/
	unchar	d_len_fi[1];	/* file identifier length	*/
	unchar	d_file_id[1];	/* file identifier		*/
};

typedef struct hsdir	hsdir_t;

/*
 * file flags
 */
#define	HS_HIDDEN	0x01
#define	HS_DIR		0x02
#define	HS_ASSOC	0x04
#define	HS_RECORD	0x08
#define	HS_PROTECTION	0x10
#define	HS_MULTI_EXTENT	0x80

/*
 * special values of file-id
 */
#define	HS_DOT		0
#define	HS_DOTDOT	1

/*
 * separator characters in file-id
 */
#define	HS_SEP1		'.'		/* file extension separator	*/
#define	HS_SEP2		';'		/* version number separator	*/

/*
 * ISO-9660 extended attribute record
 */

struct isxarec
{
	unchar	xa_uid[4];	/* owner identification		*/
	unchar	xa_gid[4];	/* group identification		*/
	unchar	xa_perms[2];	/* permissions			*/
	unchar	xa_ctime[7];	/* creation date and time	*/
	unchar	xa_mtime[7];	/* modification date and time	*/
	unchar	xa_extime[7];	/* expiration date and time	*/
	unchar	xa_eftime[7];	/* effective date and time	*/
	unchar	xa_rec_fmt[1];	/* record format		*/
	unchar	xa_rec_attr[1];	/* record attributes		*/
	unchar	xa_rec_len[4];	/* record length		*/
	unchar	xa_systemid[32];/* system identifier		*/
	unchar	xa_sys_use[64];	/* system use area		*/
	unchar	xa_version[1];	/* extended attribute version	*/
	unchar	xa_len_esc[1];	/* length of escape sequences	*/
	unchar	xa_reserved[64];/* reserved			*/
	unchar	xa_len_au[4];	/* length of application use area */
	unchar	xa_au[1];	/* application use area		*/
};

typedef struct isxarec	isxarec_t;

#define	XA_ESC(p)	(&(p)->xa_au[getword((p)->xa_len_au)])


#define	HS_IRSYS	0x0001	/* read by system class user	*/
#define	HS_IXSYS	0x0004	/* execute by system class user	*/
#define	HS_IRUSR	0x0010	/* read by owner		*/
#define	HS_IXUSR	0x0040	/* execute by owner		*/
#define	HS_IRGRP	0x0100	/* read by group		*/
#define	HS_IXGRP	0x0400	/* execute by group		*/
#define	HS_IROTH	0x1000	/* read by any user		*/
#define	HS_IXOTH	0x4000	/* execute by any user		*/

#endif	/* _SYS_FS_HSDIR_H */
						/* END SCO_FS */
