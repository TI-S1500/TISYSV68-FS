/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char ino_h[] = "@(#)ino.h	1.5 (TI) 89/08/17";
#endif	SCCSID

/* @(#)ino.h	2.1	UNIX System V/68 */
	/* Inode structure as it appears on a disk block. */
struct dinode
{
	ushort di_mode;		/* mode and type of file */
	short	di_nlink;    	/* number of links to file */
	ushort	di_uid;      	/* owner's user id */
	ushort	di_gid;      	/* owner's group id */
	off_t	di_size;     	/* number of bytes in file */
	char  	di_addr[36];	/* disk block addresses */
	/* The last 3 chars of the disk block addresses and the extra byte
	** must be divided in the following structure so that SVS C will
	** correctly assign the proper bit fields for the extended mode
	** flags and the NFS file generation number. The address fields
	** are actually 39 characters long.
	*/
	struct {
		unsigned addrs:  24,	/* The remainder of di_addr */
			 gen:    5,	/* File generation number */
			 xflags: 3;	/* Extended mode flags for TI Sys V */
	} di_lword;
	time_t	di_atime;   	/* time last accessed */
	time_t	di_mtime;   	/* time last modified */
	time_t	di_ctime;   	/* time created */
};

#define	di_gen	di_lword.gen
