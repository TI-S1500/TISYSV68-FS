
/*
   COPYRIGHT (c) 1986 TEXAS INSTRUMENTS, INCORPORATED.  ALL RIGHTS RESERVED.
*/
/*
static char *sccs_id = @(#)cpio.h	1.3 87/04/14";
*/

#define MAGIC	070707		/* cpio magic number */
#define CHARS	76		/* ASCII header size minus filename field */
#define BUFSIZE 1024
#define CPIOBSZ 4096		/* file read/write */
#define HDRSIZE	(Hdr.h_name-(char *)&Hdr) /* header size minus filename field */
	/* Cpio header format */
struct header {
	short		h_magic       ,
			h_dev         ;
	unsigned short	h_ino         ,
			h_mode        ,
			h_uid         ,
			h_gid         ;
	short		h_nlink       ,
			h_rdev        ,
			h_mtime[2]    ,
			h_namesize    ,
			h_filesize[2] ;
	char		h_name[256]   ;
} ; 


