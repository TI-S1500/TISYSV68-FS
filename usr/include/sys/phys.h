/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char phys_h[] = "@(#)phys.h	1.3 (TI) 86/02/04";
#endif	SCCSID

#define PHYSMAJ	24		/* Physical memory major device number */ 

#define MAXPHYS 0x8		/* Max number of physical memory devices */
#define P_MAP	0x0		/* Flag to map */
#define P_UNMAP	0x1		/* Flag to unmap */

struct alist {
	unsigned paddr;
	int nbytes;
	unsigned vaddr;
};
