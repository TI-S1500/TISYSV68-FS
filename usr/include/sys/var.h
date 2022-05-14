/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char var_h[] = "@(#)var.h	1.11 (TI) 89/08/18";
#endif	SCCSID

/*	@(#)var.h	1.1	UNIX System V/68 */
struct var {
	int	v_buf;
	int	v_call;
	int	v_inode;
	char *	ve_inode;
	int	v_file;
	char *	ve_file;
	int	v_mount;
	char *	ve_mount;
	int	v_proc;
	char *	ve_proc;
	int	v_text;
	char *	ve_text;
	int	v_clist;
	int	v_nswbuf;
	int	v_maxup;
	int	v_smap;
	int	v_hbuf;
	int	v_hmask;
	int	v_pbuf;
	int	v_fslimit;
	int	v_lticks;
	int	v_maxsegs;
	int     v_rdsiz;
	int	v_nqueue;	/* Nbr of streams queues.		*/
	int	v_nstream;	/* Number of stream head structures.	*/
	int	v_nblk4096;	/* Number of 4096 bytes stream buffers.	*/
	int	v_nblk2048;	/* Number of 2048 bytes stream buffers.	*/
	int	v_nblk1024;	/* Number of 1024 bytes stream buffers.	*/
	int	v_nblk512;	/* Number of 512 bytes stream buffers.	*/
	int	v_nblk256;	/* Number of 256 bytes stream buffers.	*/
	int	v_nblk128;	/* Number of 128 bytes stream buffers.	*/
	int	v_nblk64;	/* Number of 64 bytes stream buffers.	*/
	int	v_nblk16;	/* Number of 16 bytes stream buffers.	*/
	int	v_nblk4;	/* Number of 4 bytes stream buffers.	*/
	int	v_s5inode;	/* Number of s5inodes */
};
extern struct var v;
