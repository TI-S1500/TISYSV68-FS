/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1987.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char sccsid[] = "@(#)opc.h	1.5 (TI) 89/10/25";
#endif	SCCSID

struct op_cmdblk
{
  short process_id;	/* pid the caller wants to manipulate  */
  short cpunumber;	/* The cpuid the caller wants */
  long parm;		/* Parameter */
};

/*
  Ioctl's
*/
#define OIOCLOCK	('O'<<8 | 0)	/* Lock a process in a cpu */
#define OIOCUNLK	('O'<<8 | 1)	/* Unlock a process */
#define OIOCMOVE	('O'<<8 | 2)	/* Move a process to another cpu */
#define OIOCMOVEL	('O'<<8 | 3)	/* Move a process and lock it */
#define OIOCNONEW	('O'<<8 | 4)	/* Disallow new processes on a cpu */
#define OIOCNEW		('O'<<8 | 5)	/* Allow new processes on a cpu */
#define OIOCNCPUB	('O'<<8 | 6)	/* Disallow cpu bound procs on a cpu */
#define OIOCCPUB	('O'<<8 | 7)	/* Allow cpu bound procs on a cpu */
#define OIOCLOCKNEW	('O'<<8 | 8)	/* Lock all new processes on a cpu */
#define OIOCNOLKNEW	('O'<<8 | 9)	/* Don't lock new procs on this cpu */
#define OIOCLOCKALL	('O'<<8 | 10)	/* Lock all processes on a cpu */
#define OIOCUNLKALL	('O'<<8 | 11)	/* Unlock all processes on a cpu */
#define OIOCNOMIGR	('O'<<8 | 12)	/* Disable all process migration */
#define OIOCMIGR	('O'<<8 | 13)	/* Enable process migration */
#define OIOCNORR	('O'<<8 | 14)	/* Disable new process round robin */
#define OIOCRR		('O'<<8 | 15)	/* Enable new process round robin */
#define OIOCMOVEALL	('O'<<8 | 16)	/* Move all processes off this cpu */
#define OIOCCHLOCK	('O'<<8 | 17)   /* Lock proc & descendants on cpu */
#define OIOCCHUNLK	('O'<<8 | 18)   /* Don't lock proc & descendants */
#define OIOCBALTIM	('O'<<8 | 19)   /* Change load balancing interval */
#define OIOCMINBMEM	('O'<<8 | 20)   /* Change minimum balance memory */
#define OIOCLMAXPCT	('O'<<8 | 21)   /* Change max cpu load percent */
#define OIOCIDLEDPCT	('O'<<8 | 22)   /* Change idle diff percent */
#define OIOCSEL0PCT	('O'<<8 | 23)   /* Change select 0 percent */
#define OIOCSNAPDEC	('O'<<8 | 24)   /* Change snapidle decrement */
#define OIOCRLSPEED	('O'<<8 | 25)   /* Change relative speed of cpu */
#define OIOCHALTP	('O'<<8 | 26)   /* Halt Process			*/
#define OIOCRESUMEP	('O'<<8 | 27)   /* Resume Process		*/
#define OIOCZIPPINESS	('O'<<8 | 28)   /* Change on-chip cache bursting */

/*
  Cpu control flag values
*/
#define NONEW	0x01	/* Do not allow new processes */
#define NOCPUB	0x02	/* Do not allow cpu-bound processes */
#define LOCKNEW 0x04	/* Lock all new processes to the cpu */

#ifdef KERNEL
extern short cpu_flags[MAXCPU];
#endif KERNEL
