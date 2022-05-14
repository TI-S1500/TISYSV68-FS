/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1986.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char device_h[] = "@(#)device.h	1.2 (TI) 86/02/04";
#endif	/* SCCSID */
 
#ifndef SCCSID

/********
*
*   This structure identifies contains a device part number and is
*   used to identify device characteristics.
*
********/
/*
*  part number structure 
*/
struct pnum
{
	char pnum[16];
};

/* 
* The following structure contains the device type codes and corresponding
* configuration function for all supported devices.  
*
*  	The device type code corresponds to the eight character device
*  	type field found in the configuration ROM.
*
*	The configuration function is a routine that will be called
*	by STBM to perform whatever configuration functions are
*	necessary for the driver associated with that device.
*	
*	The configuration function will be called with the following args.
*	int conf(confptr, devmap, slot)
*	struct confhdr *confptr;	
*			
*	struct devmap  *devmap;		
*	int	slot;
*/
struct device
{
	char type[3];		/* three character type code from ROM */
	struct pnum *pnum;	/* ptr to array of part number arrays */
	int (*conf)();		/* pointer to config for this device  */
	int (*mkdev)();		/* pointer to function that builds device
				   dependent major and minor device numbers
				   for rootdev, pipedev, etc */
};
/******
*
*  The following structure is used to identify the device crash index.  This
*  value is used by the kernel to determine which driver to use for the dump
*  
*******/
struct dmpdev
{
	char type[3];		/* three character type code from ROM */
	struct pnum *pnum;	/* ptr to array of part number arrays */
	int index;		/* crash index */
};
#endif	/* SCCSID */
