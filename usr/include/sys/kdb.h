/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char kdb_h[] = "@(#)kdb.h	1.9 (TI) 91/07/09";
#endif	SCCSID

/* include all the required include files so source only includes this one */

#define	KDB_VM

#include "sys/param.h"
#include "sys/types.h"
#include "sys/systm.h"
#include "sys/sysmacros.h"
#include "sys/fs/s5dir.h"
#include "sys/signal.h"
#include "sys/user.h"
#include "sys/errno.h"
#include "sys/conf.h"
#include "sys/trap.h"
#include "sys/inode.h"
#include "sys/file.h"
#include "sys/psl.h"
#include "sys/pte.h"
#include "sys/devmap.h"
#include "sys/cpu.h"
#include "sys/proc.h"
#include "sys/mmu.h"
#include "sys/vm.h"
#include "sys/cmap.h"
#include "sys/stack.h"
#include "sys/seg.h"

#define	_OK		0
#define	_ERR		-1

#define	_CONTINUE	0
#define	_RETURN		1

#define	SLASH		'/'
#define	BACKSLASH	'\134'
#define	QMARK		'?'

/* command bytes */

#define	ILL	'\001'
#define	NOP	'\002'
#define	DUMP	'\003'
#define	BP	'b'
#define	CONTIN	'c'
#define	DBP	'd'
#define SEGD    'e'
#define	GO	'g'
#define ISEG    'i'
#define	KDUMP	'k'
#define	MTABLE	'm'
#define	PROC	'p'
#define	REG	'r'
#define	SINGLE	's'
#define	TRACE	't'
#define	UDOT	'u'
#define VTRACE	'v'
#define	RITE	'w'
#define	ZORRO	'z'
#define CMAP    'C'
#define PARITYERR  'E'
#define HELP	'H'
#define	KDBINIT	'I'
#define PROX	'P'
#define VMTOTAL 'T'
#define VMMETER 'V'

#define	END_O_TAB	'\377'

struct regis
{
	unsigned long	usp;
	unsigned long	d[8];
	unsigned long	a[7];
	unsigned short	sr;
	unsigned long	pc;
	unsigned short	vor;
	unsigned long	iaddr;	/* or special status word */
	unsigned long	pipe;
	unsigned long	faddr;	/* data cycle fault address */
	unsigned short	ir0[2];
	unsigned long	s_dob;	/* data output buffer for short frame */
	unsigned short	ir1[2];
	unsigned long	sbaddr;	/* here and below, long frame only! */
	unsigned short	ir2[2];
	unsigned long	l_dob;
	unsigned long	l_dib;
	unsigned short	ir3[20];
	unsigned long	prestack;
};

struct cmd
{
	char	cmd;
	char	mode;
	char	aux;
	int	count;	
	long	addr;
};

struct cmd_tab
{
	char	cmd;
	int 	(*fun)();
	char 	*help;
};

char *lto8b();

extern end, etext;

extern char *kdbvw;

#ifdef	MULTI
extern cpuid;
#endif	MULTI
