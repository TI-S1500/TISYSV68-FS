#ifdef __STDC__
/* This file is a macro to replace the below mentioned function
   Reference bio.c to see how this evolved.
 * Read in the block
 */
#ifdef KERNEL
#ifndef bread 
#define bread(dev,blkno) (struct buf *)breada(dev,blkno,1)
#endif
#endif
#endif
