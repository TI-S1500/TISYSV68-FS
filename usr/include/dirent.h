/*
    COPYRIGHT (c) 1988 TEXAS INSTRUMENTS, INCORPORATED.  ALL RIGHTS RESERVED.
*/
/*
static char *sccs_id = "@(#)dirent.h	1.1 88/03/01";
*/

#define MAXNAMLEN	512		/* maximum filename length */
#define DIRBUF		1048		/* buffer size for fs-indep. dirs */


typedef struct
	{
	int	dd_fd;			/* file descriptor */
	int	dd_loc;			/* offset in block */
	int	dd_size;		/* amount of valid data */
	char	*dd_buf;		/* directory block */
	}	DIR;			/* stream data from opendir() */

extern DIR		*opendir();
extern struct dirent	*readdir();
extern long		telldir();
extern void		seekdir();
extern int		closedir();

#define rewinddir( dirp )	seekdir( dirp, 0L )
#include <sys/dirent.h>
