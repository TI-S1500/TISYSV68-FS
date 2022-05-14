
/*	Copyright (C) The Santa Cruz Operation, 1989, 1990.	*/

/*	This Module contains Proprietary Information of		*/
/*	The Santa Cruz Operation and should be treated		*/
/*	as Confidential.					*/

#ifdef SCCSID
static char hsfcntl_h[] = "@(#)hsfcntl.h	1.1 91/03/12"
#endif SCCSID

						/* BEGIN SCO_FS */

#ifndef	_SYS_FS_HSFCNTL_H
#define	_SYS_FS_HSFCNTL_H

/*
 * fcntl(2) requests
 */

#define F_HS_GET_VOLID			0x6010	/* get volume id	*/
#define F_HS_GET_VOLSETID		0x6011	/* get volume set id	*/
#define F_HS_GET_COPYRIGHT_FILEID	0x6012	/* get copyright file-id*/
#define F_HS_GET_ABSTRACT_FILEID	0x6013	/* get abstract file-id	*/
#define F_HS_GET_BIBLIOGRAPHIC_FILEID	0x6014	/* get bibliographic file-id */
#define	F_HS_GET_VOL_ESCAPE_SEQ		0x6015	/* get volume esacape sequences*/

#define	F_HS_GET_RECORD_FORMAT		0x6020

/*
 * fcntl arguments for various functions
 */
/*
 * F_HS_GET_RECORD_FORMAT
 */
struct hs_record_format
{
	unchar	record_format;
	unchar	record_attributes;
	ushort	record_length;
};
#define	HS_RF_NONE		0
#define	HS_RF_FIXED		1
#define	HS_RF_VARIABLE_L	2
#define	HS_RF_VARIABLE_R	3

#endif	/* _SYS_FS_HSFCNTL_H */
						/* END SCO_FS */
