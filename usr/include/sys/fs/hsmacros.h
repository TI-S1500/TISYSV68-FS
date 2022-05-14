
/*	Copyright (C) The Santa Cruz Operation, 1989, 1990.	*/

/*	This Module contains Proprietary Information of		*/
/*	The Santa Cruz Operation and should be treated		*/
/*	as Confidential.					*/

#ifdef SCCSID
static char hsmacros_h[] = "@(#)hsmacros.h	1.2 91/06/28"
#endif SCCSID

						/* BEGIN SCO_FS */
#ifndef	_SYS_FS_HSMACROS_H
#define	_SYS_FS_HSMACROS_H

#define	TRUE	1
#define	FALSE	0

#define FsBSIZE(bsize)		(1024)
#define FsBSHIFT(bsize)		(10)
#define FsBMASK(bsize)		(01777)
/* inode numbers for regular files = byte displacement to the directory
    entry for that file. For directory files, we start with the byte
    displacement to the start of the file itself, shift right 10 and
    then set bit 0 as a flag. This is done to decrease the amount of
    information lost when hsstatf and hsgetdents truncate the inode
    number to 16 bits. This decreases the chances for having duplicate
    inode numbers, which can confuse the pwd command */
#define FsITOD(bsize, x)	((x & 1) == 1)  ? \
				  (daddr_t)(((unsigned long)(x)) & 0xfffffffe) : \
				  (daddr_t)(((unsigned long)(x)) >> FsBSHIFT(bsize))
#define FsITOO(bsize, x)	((x & 1) == 1) ? \
				  (ushort)(0) : \
				  (ushort)(((unsigned long)(x)) & FsBMASK(bsize))
#define FsDINO(ino)             ((ino & 03777) == 0) ? \
				  ((ino >> 10) | 1) : \
				  ino
#define	FsINO(bsize, bno, off)  (ulong)((((unsigned long)(bno)) << FsBSHIFT(bsize)) + off)

#define	STRUCTOFF(structure, field)	(int) &(((struct structure *) 0)->field)

/*
 * macros for accessing binary data in the High Sierra filesystem
 */
#if	i386 || i286
#define	getbyte(p)	(*(unchar *)(p))
#define	getword(p)	(*(ushort *)(p))
#define	getdword(p)	(*(ulong *)(p))
#else
#define	getbyte(p)	(*(unchar *)(p))
#define	getword(p)	(*(ushort *)(p+sizeof(ushort)))
#define	getdword(p)	(*(ulong *)(p+sizeof(ulong)))
#endif

#endif	/* _SYS_FS_HSMACROS_H */
						/* END SCO_FS */
