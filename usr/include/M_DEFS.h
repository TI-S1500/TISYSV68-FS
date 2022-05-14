/*
   COPYRIGHT (c) 1985 TEXAS INSTRUMENTS, INCORPORATED.  ALL RIGHTS RESERVED.
*/
/*
static char *sccs_id = @(#)M_DEFS.h	1.2 91/04/08";
*/

/*  these are the symbolic definitions for the standard messages
 *  available through printm
 */

#define M_CANTOPEN	1000501L	/*  can't open file %s        	*/
#define M_CANTCLOSE	1000502L	/*  can't close file %s        	*/
#define M_CANTSTAT	1000503L	/*  can't stat file %s        	*/
#define M_CANTCREATE	1000504L	/*  can't create file %s	*/
#define M_CANTFIND 	1000505L	/*  can't find file %s		*/
#define M_CANTREAD 	1000506L	/*  can't read file %s		*/
#define M_CANTWRITE	1000507L	/*  can't write  file %s	*/
#define M_CANTEXEC 	1000508L	/*  can't exec program %s	*/
#define M_CANTCOPY 	1000509L	/*  can't copy file %s   	*/

#define M_NAME2LONG	1000510L	/*  file name too long; %s	*/
#define M_CANTCHDIR	1000511L	/*  can't chdir to %s		*/
#define M_CANTLINK	1000512L	/*  can't link to file %s	*/
#define M_CANTCMOD	1000513L	/*  can't chmod on file %s	*/
#define M_INVALDARG	1000514L	/*  invalid argument %s		*/
#define M_NOMEMORY 	1000515L	/*  no more memory      	*/
#define M_ILLOPT	1000516L	/*  option %c is illegal	*/
#define M_ILLSTR   	1000517L	/*  option %s is illegal 	*/

#define M_READERR	1000520L	/*  read error on file %s	*/	
#define M_WRITERR	1000521L	/*  write error on file %s	*/	
#define M_SEEKERR	1000522L	/*  seek error on file %s	*/	
#define M_CANTCOWN	1000523L	/*  can't chown on file %s	*/
#define M_CANTMKNOD	1000524L	/*  can't mknod for file %s	*/
#define M_CANTFORK	1000525L	/*  can't fork			*/
#define M_CANTSYMLINK 1000526L	/* can't create symlink %s */

#define M_PERROR	1000526L	/*  same as perror sys call	*/


#define M_INFO		0
#define M_WARN		1
#define M_ERRO		2
#define M_HALT		3
