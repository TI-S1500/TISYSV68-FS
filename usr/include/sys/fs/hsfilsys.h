
/*	Copyright (C) The Santa Cruz Operation, 1989, 1990.	*/

/*	This Module contains Proprietary Information of		*/
/*	The Santa Cruz Operation and should be treated		*/
/*	as Confidential.					*/

#ifdef SCCSID
static char hsfilsys_h[] = "@(#)hsfilsys.h	1.1 91/03/12"
#endif SCCSID

						/* BEGIN SCO_FS */
#ifndef	_SYS_FS_HSFILSYS_H
#define	_SYS_FS_HSFILSYS_H

/*
 * hsfilsys - in-core "superblock" for High Sierra / ISO9660 filesytem
 */

struct hsfilsys
{
	int		s_flags;	/* superblock flags		*/
	int		s_type;		/* filesystem type		*/
	unchar		s_systemid[32];	/* system identifier		*/
	unchar		s_volumeid[32];	/* volume identifier		*/
	ushort		s_lbsize;	/* logical block size		*/
	off_t		s_rootino;	/* root inode number		*/
	ulong		s_volspacesz;	/* volume space size		*/
	ushort		s_volsetsz;	/* volume set size		*/
	ushort		s_volseqno;	/* volume sequence number	*/
	time_t		s_ctime;	/* volume creation time		*/
	time_t		s_mtime;	/* volume modification time	*/
	time_t		s_extime;	/* volume expiry time		*/
	time_t		s_ettime;	/* volume effective time	*/
};

typedef struct hsfilsys	hsfilsys_t;

/*
 * values for s_flags
 */
#define	HS_SFREE	0x00
#define	HS_SINUSE	0x01

/*
 * values for s_type
 */
#define	HIGH_SIERRA	0x01
#define	ISO9660		0x02

#define getfs(mp)	((struct hsfilsys *)(mp->m_bufp))

#define	TYPE(mp)	(getfs(mp)->s_type)	/* filesystem type	*/
#define	ROOTINO(mp)	(getfs(mp)->s_rootino)	/* root inode #		*/
#define	LBSIZE(mp)	(getfs(mp)->s_lbsize)	/* logical block size	*/

#endif	/* _SYS_FS_HSFILSYS_H */
						/* END SCO_FS */
