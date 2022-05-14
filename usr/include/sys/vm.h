/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char vm_h[] = "@(#)vm.h	1.3 (TI) 86/02/04";
#endif	SCCSID

/* 
 * Include file which gets you all of the virtual memory headers.
 */

#ifdef KERNEL
#include "sys/vmparams.h"
#include "sys/vmmacros.h"
#include "sys/vmmeter.h"
#else
#include <sys/vmparams.h>
#include <sys/vmmacros.h>
#include <sys/vmmeter.h>
#endif

