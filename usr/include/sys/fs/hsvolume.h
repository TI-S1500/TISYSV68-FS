
/*	Copyright (C) The Santa Cruz Operation, 1989, 1990.	*/

/*	This Module contains Proprietary Information of		*/
/*	The Santa Cruz Operation and should be treated		*/
/*	as Confidential.					*/

#ifdef SCCSID
static char hsvolume_h[] = "@(#)hsvolume.h	1.1 91/03/12"
#endif SCCSID

						/* BEGIN SCO_FS */
#ifndef	_SYS_FS_HSVOLUME_H
#define	_SYS_FS_HSVOLUME_H

/*
 * isfilsys - ISO9660 volume descriptor
 */
struct isvol
{
	unchar	v_type[1];		/* Volume Descriptor Type	*/
	unchar	v_standard[5];		/* Standard Identifier		*/
	unchar	v_version[1];		/* Volume Descriptor Version	*/
	unchar	v_flags[1];		/* Volume Flags			*/
	unchar	v_systemid[32];		/* System Identifier		*/
	unchar	v_volumeid[32];		/* Volume Identifier		*/
	unchar	v_unused[8];
	unchar	v_volspacesz[8];	/* Volume Space Size		*/
	unchar	v_escapes[32];		/* Escape Sequences		*/
	unchar	v_volsetsz[4];		/* Volume Set Size		*/
	unchar	v_volseqno[4];		/* Volume Sequence Number	*/
	unchar	v_lbsize[4];		/* Logical Block Size		*/
	unchar	v_pathtablesz[8];	/* Path Table Size		*/
	unchar	v_lpathtable0[4];	/* Location of L Path Table	*/
	unchar	v_lpathtable1[4];	/* Location of L Path Table	*/
	unchar	v_rpathtable0[4];	/* Location of R Path Table	*/
	unchar	v_rpathtable1[4];	/* Location of R Path Table	*/
	isdir_t	v_rootdir;		/* Root Directory Descriptor	*/
	unchar	v_volsetid[128];	/* Volume Set Identifier	*/
	unchar	v_publisher[128];	/* Publisher Identifier		*/
	unchar	v_preparer[128];	/* Data Preparer Identifier	*/
	unchar	v_application[128];	/* Application Identifier	*/
	unchar	v_copyright[37];	/* Copyright File Identifier	*/
	unchar	v_abstract[37];		/* Abstract File Identifier	*/
	unchar	v_bibliography[37];	/* Bibliographic File Identifier*/
	unchar	v_ctime[17];		/* Volume Creation Time		*/
	unchar	v_mtime[17];		/* Volume Modification Time	*/
	unchar	v_extime[17];		/* Volume Expiration Time	*/
	unchar	v_etime[17];		/* Volume Effective Time	*/
	unchar	v_fsver[1];		/* File Structure Version	*/
	unchar	v_rsvd[1];
	unchar	v_app[512];		/* Application Use		*/
	unchar	v_rsvd_1[654];
};

typedef struct isvol	isvol_t;

/*
 * hsfilsys - High Sierra volume descriptor
 */
struct hsvol
{
	unchar	v_XXX[8];		/* ????				*/
	unchar	v_type[1];		/* Volume Descriptor Type	*/
	unchar	v_standard[5];		/* Standard Identifier		*/
	unchar	v_version[1];		/* Volume Descriptor Version	*/
	unchar	v_flags[1];		/* Volume Flags			*/
	unchar	v_systemid[32];		/* System Identifier		*/
	unchar	v_volumeid[32];		/* Volume Identifier		*/
	unchar	v_unused[8];
	unchar	v_volspacesz[8];	/* Volume Space Size		*/
	unchar	v_escapes[32];		/* Escape Sequences		*/
	unchar	v_volsetsz[4];		/* Volume Set Size		*/
	unchar	v_volseqno[4];		/* Volume Sequence Number	*/
	unchar	v_lbsize[4];		/* Logical Block Size		*/
	unchar	v_pathtablesz[8];	/* Path Table Size		*/
	unchar	v_lpathtable0[4];	/* Location of L Path Table	*/
	unchar	v_lpathtable1[4];	/* Location of L Path Table	*/
	unchar	v_lpathtable2[4];	/* Location of L Path Table	*/
	unchar	v_lpathtable3[4];	/* Location of L Path Table	*/
	unchar	v_rpathtable0[4];	/* Location of R Path Table	*/
	unchar	v_rpathtable1[4];	/* Location of R Path Table	*/
	unchar	v_rpathtable2[4];	/* Location of R Path Table	*/
	unchar	v_rpathtable3[4];	/* Location of R Path Table	*/
	hsdir_t	v_rootdir;		/* Root Directory Descriptor	*/
	unchar	v_volsetid[128];	/* Volume Set Identifier	*/
	unchar	v_publisher[128];	/* Publisher Identifier		*/
	unchar	v_preparer[128];	/* Data Preparer Identifier	*/
	unchar	v_application[128];	/* Application Identifier	*/
	unchar	v_copyright[32];	/* Copyright File Identifier	*/
	unchar	v_abstract[32];		/* Abstract File Identifier	*/
	unchar	v_ctime[16];		/* Volume Creation Time		*/
	unchar	v_mtime[16];		/* Volume Modification Time	*/
	unchar	v_extime[16];		/* Volume Expiration Time	*/
	unchar	v_etime[16];		/* Volume Effective Time	*/
	unchar	v_fsver[1];		/* File Structure Version	*/
	unchar	v_rsvd[1];
	unchar	v_app[512];		/* Application Use		*/
	unchar	v_rsvd_1[681];
};

typedef struct hsvol	hsvol_t;

/*
 * values for v_type
 */
#define	HS_BOOT		0		/* Boot Record			*/
#define	HS_PRIMARY	1		/* Primary Descriptor		*/
#define	HS_SUPP		2		/* Supplementary Descriptor	*/
#define	HS_VOLPART	3		/* Partition Descriptor		*/
#define	HS_TERM		255		/* Volume Descriptor Terminator	*/

#endif	/* _SYS_FS_HSVOLUME_H */
						/* END SCO_FS */
