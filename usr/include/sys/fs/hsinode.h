
/*	Copyright (C) The Santa Cruz Operation, 1989, 1990.	*/

/*	This Module contains Proprietary Information of		*/
/*	The Santa Cruz Operation and should be treated		*/
/*	as Confidential.					*/

#ifdef SCCSID
static char hsinode_h[] = "@(#)hsinode.h	1.1 91/03/12"
#endif SCCSID

						/* BEGIN SCO_FS */
#ifndef	_SYS_FS_HSINODE_H
#define	_SYS_FS_HSINODE_H

/*
 * file system dependent inode structure for High Sierra filesystems
 */

struct hsinode
{
	struct	hsinode		*hi_next;	/* free list ptr	*/
	time_t			hi_ctime;	/* file creation time	*/
	time_t			hi_mtime;	/* file modification time */
	struct hsextent		*hi_extent;	/* file extents		*/
};

typedef struct hsinode	hsinode_t;

/*
 * structure describing a single extent of a file
 */

struct hsextent
{
	struct hsextent	*hx_next;	/* pointer to next extent	*/
	ulong		hx_start;	/* location of extent		*/
	off_t		hx_size;	/* size of extent		*/
	ushort		hx_volseq;	/* volume sequence #		*/
	unchar		hx_xalen;	/* extended attribute length	*/
	unchar		hx_flags;	/* file flags			*/
	unchar		hx_unitsz;	/* file unit size		*/
	unchar		hx_igap;	/* interleave gap		*/
};

typedef struct hsextent	hsextent_t;

extern struct hsinode	hsinode[];
extern int		hsninode;

extern struct hsextent	hsextent[];
extern int		hsnextent;

#endif	/* _SYS_FS_HSINODE_H */
						/* END SCO_FS */
