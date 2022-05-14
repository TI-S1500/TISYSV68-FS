/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char errno_h[] = "@(#)errno.h	1.13 (TI) 91/04/08";
#endif	SCCSID

/* @(#)errno.h	2.1	UNIX System V/68 */
/*
 * Error codes
 */

#define	EPERM	1	/* Not super-user			*/
#define	ENOENT	2	/* No such file or directory		*/
#define	ESRCH	3	/* No such process			*/
#define	EINTR	4	/* interrupted system call		*/
#define	EIO	5	/* I/O error				*/
#define	ENXIO	6	/* No such device or address		*/
#define	E2BIG	7	/* Arg list too long			*/
#define	ENOEXEC	8	/* Exec format error			*/
#define	EBADF	9	/* Bad file number			*/
#define	ECHILD	10	/* No children				*/
#define	EAGAIN	11	/* No more processes			*/
#define	ENOMEM	12	/* Not enough core			*/
#define	EACCES	13	/* Permission denied			*/
#define	EFAULT	14	/* Bad address				*/
#define	ENOTBLK	15	/* Block device required		*/
#define	EBUSY	16	/* Mount device busy			*/
#define	EEXIST	17	/* File exists				*/
#define	EXDEV	18	/* Cross-device link			*/
#define	ENODEV	19	/* No such device			*/
#define	ENOTDIR	20	/* Not a directory			*/
#define	EISDIR	21	/* Is a directory			*/
#define	EINVAL	22	/* Invalid argument			*/
#define	ENFILE	23	/* File table overflow			*/
#define	EMFILE	24	/* Too many open files			*/
#define	ENOTTY	25	/* Not a typewriter			*/
#define	ETXTBSY	26	/* Text file busy			*/
#define	EFBIG	27	/* File too large			*/
#define	ENOSPC	28	/* No space left on device		*/
#define	ESPIPE	29	/* Illegal seek				*/
#define	EROFS	30	/* Read only file system		*/
#define	EMLINK	31	/* Too many links			*/
#define	EPIPE	32	/* Broken pipe				*/
#define	EDOM	33	/* Math arg out of domain of func	*/
#define	ERANGE	34	/* Math result not representable	*/
#define	ENOMSG	35	/* No message of desired type		*/
#define	EIDRM	36	/* Identifier removed			*/
#define	ECHRNG	37	/* Channel number out of range		*/
#define	EL2NSYNC 38	/* Level 2 not synchronized		*/
#define	EL3HLT	39	/* Level 3 halted			*/
#define	EL3RST	40	/* Level 3 reset			*/
#define	ELNRNG	41	/* Link number out of range		*/
#define	EUNATCH 42	/* Protocol driver not attached		*/
#define	ENOCSI	43	/* No CSI structure available		*/
#define	EL2HLT	44	/* Level 2 halted			*/
#define	ELOOP	47	/* Too many symbolic links		*/

/* Reserved error numbers 
#define	RESERVD	45	
#define	RESERVD	46
#define	RESERVD	48
#define	RESERVD	49	
*/
#define EDEADLK 50      /* record locking deadlock detection */
#define ENOLCK	51	/* no more record locks available */
#define ENOSAT	52	/* reserved */

/* device driver errors */
#define EOFFLN	53	/* Device offline */
#define ENOTRDY	54	/* Device not ready */
#define ERODEV	55	/* Read only device (or write protected) */
#define ERQEOD  56	/* I/O Request beyond end of device */
#define ETIMES  57	/* Driver timeout error */

/* Convergent Error Returns */
#define EBADE	60	/* invalid exchange			*/
#define EBADR	61	/* invalid request descriptor		*/
#define EXFULL	62	/* exchange full			*/
#define ENOANO	63	/* no anode				*/
#define EBADRQC	64	/* invalid request code			*/
#define EBADSLT	65	/* invalid slot				*/
#define EDEADLOCK 66	/* file locking deadlock error		*/

#define EBFONT	67	/* bad font file fmt			*/

/* stream problems */
#define ENOSTR	70	/* Device not a stream			*/
#define ENODATA	71	/* no data (for no delay io)		*/
#define ETIME	72	/* timer expired			*/
#define ENOSR	73	/* out of streams resources		*/

#define ENONET	74	/* Machine is not on the network	*/
#define ENOPKG	75	/* Package not installed                */
#define EREMOTE	76	/* The object is remote			*/
#define ENOLINK	77	/* the link has been severed */
#define EADV	78	/* advertise error */
#define ESRMNT	79	/* srmount error */

#define	ECOMM	80	/* Communication error on send		*/
#define EPROTO	81	/* Protocol error			*/
#define	EMULTIHOP 84	/* multihop attempted */
#define	ELBIN	85	/* Inode is remote (not really error)*/
#define	EDOTDOT 86	/* Cross mount point (not really error)*/
#define EBADMSG 87	/* trying to read unreadable message	*/

#define ENOTUNIQ 90	/* given log. name not unique */
#define EBADFD	 91	/* f.d. invalid for this operation */
#define EREMCHG	 92	/* Remote address changed */

/* shared library problems */
#define ELIBACC 93	/* Can't access a needed shared lib.	*/
#define ELIBBAD	94	/* Accessing a corrupted shared lib.	*/
#define ELIBSCN	95	/* .lib section in a.out corrupted.	*/
#define ELIBMAX	96	/* Attempting to link in too many libs.	*/

#define ETO020  97	/* More 020's than licensed for */
#define ETO030  98	/* More 030's than licensed for */
#define ETO0X0  99	/* More 020's and 030's than licensed for */
#define ELIBEXEC 100	/* Attempting to exec a shared library.	*/

/*web 4-28-89 */
/*
 *	System V STREAMS TCP
 */
/* Errors from 4.2 BSD picked up to support sockets */
/* Note that the numbers are different from 4.2 numbering */

#define TCPERR		101
/* non-blocking and interrupt i/o */
#define EWOULDBLOCK     (TCPERR+0)       /* Operation would block */
#define EINPROGRESS     (TCPERR+1)       /* Operation now in progress */
#define EALREADY        (TCPERR+2)       /* Operation already in progress */
/* ipc/network software */

/* argument errors */
#define ENOTSOCK        (TCPERR+3)       /* Socket operation on non-socket */
#define EDESTADDRREQ    (TCPERR+4)       /* Destination address required */
#define EMSGSIZE        (TCPERR+5)       /* Message too long */
#define EPROTOTYPE      (TCPERR+6)       /* Protocol wrong type for socket */
#define EPROTONOSUPPORT (TCPERR+7)       /* Protocol not supported */
#define ESOCKTNOSUPPORT (TCPERR+8)       /* Socket type not supported */
#define EOPNOTSUPP      (TCPERR+9)       /* Operation not supported on socket */
#define EPFNOSUPPORT    (TCPERR+10)      /* Protocol family not supported */
#define EAFNOSUPPORT    (TCPERR+11)      /* Address family not supported by protocol family */
#define EADDRINUSE      (TCPERR+12)      /* Address already in use */
#define EADDRNOTAVAIL   (TCPERR+13)      /* Can't assign requested address */

/* operational errors */
#define ENETDOWN        (TCPERR+14)      /* Network is down */
#define ENETUNREACH     (TCPERR+15)      /* Network is unreachable */
#define ENETRESET       (TCPERR+16)      /* Network dropped connection on reset */
#define ECONNABORTED    (TCPERR+17)      /* Software caused connection abort */
#define ECONNRESET      (TCPERR+18)      /* Connection reset by peer */
#define ENOBUFS         ENOSR            /* No buffer space available */
#define EISCONN         (TCPERR+20)      /* Socket is already connected */
#define ENOTCONN        (TCPERR+21)      /* Socket is not connected */
#define ESHUTDOWN       (TCPERR+22)      /* Can't send after socket shutdown */
#define ETOOMANYREFS    (TCPERR+23)      /* Too many references: can't splice */
#define ETIMEDOUT       (TCPERR+24)      /* Connection timed out */
#define ECONNREFUSED    (TCPERR+25)      /* Connection refused */


/* should be rearranged */
#define EHOSTDOWN       (TCPERR+26)      /* Host is down */
#define EHOSTUNREACH    (TCPERR+27)      /* No route to host */
#define ENOPROTOOPT     (TCPERR+28)      /* Protocol not available */
/* avoid 255 (it's a -1 for a char ) */
