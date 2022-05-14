/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1989.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char s5macros_h[] = "@(#)s5macros.h	1.2 (TI) 89/08/17";
#endif	SCCSID

#ifndef FsTYPE
#define FsTYPE	2
#endif

#if FsTYPE==1

#define FsBSIZE(bsize)	BSIZE
#define FsBSHIFT(bsize)	BSHIFT
#define FsNINDIR(bsize)	NINDIR
#define FsBMASK(bsize)	BMASK
#define FsINOPB(bsize)	INOPB
#define FsLTOP(bsize, b)	(b)
#define FsPTOL(bsize, b)	(b)
#define FsNMASK(bsize)	NMASK
#define FsNSHIFT(bsize)	NSHIFT
#define FsITOD(bsize, x)   (daddr_t)(((unsigned)(x)+(2*INOPB-1)) >> INOSHIFT)
#define FsITOO(bsize, x)   (daddr_t)(((unsigned)(x)+(2*INOPB-1)) & (INOPB-1))
#define FsINOS(bsize, x)   (((x)&~07)+1)
#endif

#if FsTYPE==2
#define FsBSIZE(bsize)	BSIZE
#define FsBSHIFT(bsize)	BSHIFT
#define FsNINDIR(bsize)	NINDIR
#define FsBMASK(bsize)	BMASK
#define FsINOPB(bsize)	INOPB
#define FsLTOP(bsize, b)   (b)
#define FsPTOL(bsize, b)   (b)
#define FsNMASK(bsize)	NMASK
#define FsNSHIFT(bsize)	NSHIFT
#define FsITOD(bsize, x)   (daddr_t)(((unsigned)(x)+(2*INOPB-1)) >> INOSHIFT)
#define FsITOO(bsize, x)   (daddr_t)(((unsigned)(x)+(2*INOPB-1)) & (INOPB-1))
#define FsINOS(bsize, x)   (((x)&~017)+1)
#define FsBNO(bsize, x)    ((x) >> 10)
#define FsBOFF(bsize, x)   ((x)&01777)
#endif
 
#if FsTYPE==3

#define FsLRG(bsize)	((bsize)==1024)
/*
#define FsBSIZE(bsize)	(FsLRG(bsize) ? 1024 : 512)
*/
#define FsBSIZE(bsize)	(bsize)
#define FsBSHIFT(bsize)	(FsLRG(bsize) ? 10 : 9)
#define FsNINDIR(bsize)	(FsLRG(bsize) ? 256 : 128)
#define FsBMASK(bsize)	(FsLRG(bsize) ? 01777 : 0777)
#define FsINOPB(bsize)	(FsLRG(bsize) ? 16 : 8)
#define FsLTOP(bsize, b)	(FsLRG(bsize) ? ((b)<<1) : (b))
#define FsPTOL(bsize, b)	(FsLRG(bsize) ? ((b)>>1) : (b))
#define FsNMASK(bsize)	(FsLRG(bsize) ? 0377 : 0177)
#define FsNSHIFT(bsize)	(FsLRG(bsize) ? 8 : 7)
#define FsITOD(bsize, x)	(daddr_t)(FsLRG(bsize) ? \
	((unsigned)(x)+31)>>4 : ((unsigned)(x)+15)>>3)
#define FsITOO(bsize, x)	(daddr_t)(FsLRG(bsize) ? \
	((unsigned)(x)+31)&017 : ((unsigned)(x)+15)&07)
#define FsINOS(bsize, x)	(FsLRG(bsize) ? \
	(((x)&~017)+1) : (((x)&~07)+1))
#endif

/* 2k fs macros */

#if FsTYPE==4
#define FsBSIZE(bsize)	BSIZE
#define FsBSHIFT(bsize)	BSHIFT
#define FsNINDIR(bsize)	NINDIR
#define FsBMASK(bsize)	BMASK
#define FsINOPB(bsize)	INOPB
#define FsLTOP(bsize, b)	((b)<<2)
#define FsPTOL(bsize, b)	((b)>>2)
#define FsNMASK(bsize)	NMASK
#define FsNSHIFT(bsize)	NSHIFT
#define FsITOD(bsize, x)   (daddr_t)(((unsigned)(x)+(2*INOPB-1)) >> INOSHIFT)
#define FsITOO(bsize, x)   (daddr_t)(((unsigned)(x)+(2*INOPB-1)) & (INOPB-1))
#define FsINOS(bsize, x)   (((x)&~037)+1)
#endif