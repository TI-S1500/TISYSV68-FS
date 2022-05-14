/* --------------------------------------------------------------------------
   COPYRIGHT (c) 1990   TEXAS INSTRUMENTS INCORPORATED   ALL RIGHTS RESERVED
  --------------------------------------------------------------------------- */
/*
#ident "@(#)malloc.h	1.2 90/11/28"
*/
/*	@(#)malloc.h	1.2	*/

/*
	Constants defining mallopt operations
*/
#define M_MXFAST	1	/* set size of blocks to be fast */
#define M_NLBLKS	2	/* set number of block in a holding block */
#define M_GRAIN		3	/* set number of sizes mapped to one, for
				   small blocks */
#define M_KEEP		4	/* retain contents of block after a free until
				   another allocation */
/*
	structure filled by 
*/
struct mallinfo  {
	int arena;	/* total space in arena */
	int ordblks;	/* number of ordinary blocks */
	int smblks;	/* number of small blocks */
	int hblks;	/* number of holding blocks */
	int hblkhd;	/* space in holding block headers */
	int usmblks;	/* space in small blocks in use */
	int fsmblks;	/* space in free small blocks */
	int uordblks;	/* space in ordinary blocks in use */
	int fordblks;	/* space in free ordinary blocks */
	int keepcost;	/* cost of enabling keep option */
};	

#ifndef _MALLOC_FUNC
#define _MALLOC_FUNC
extern char *malloc();
extern void free();
extern char *realloc();
#endif
extern int mallopt();
extern struct mallinfo mallinfo();
