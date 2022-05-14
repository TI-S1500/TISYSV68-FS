#ifndef FUWORD_H
#define FUWORD_H

#ifdef KERNEL

#ifdef __GNUC__     

#pragma EXTENSIONS

/* These macros only work with gnu compiler */
/* This macro replaces the fuword() function found in ml/umove.s */
/* Reference Using and Porting GNU CC section 6.16 */
/*
   FUBYTE, and all the SUXXXX routines must be hard coded to use
	"d0" because there is a possibility of a bad source address
	or a bad destination address for the "moves" operations.  If the source
	address or destination addresses for the "moves" operations is bad
	then the kernel fault handler will cause "d0" to 
	have a -1 in "d0" and the routine that calls FUBYTE can detect the error.

	A return value of -1 for FUWORD would be undetectable as an error
   because FUWORD returns an int from user address space.
*/

/* #define FUWORD(x) */

static inline int FUWORD(where_to_get) 
void *where_to_get; 
{ int output; \
      asm volatile ("\
	movesl %1@,%0"  \
	: "=d" (output) \
	: "a" (where_to_get) \
	       ); 
	return(output);
}  

static int inline FUHALF(where_to_get) 
void *where_to_get; 
{ 
	register int output asm ("d0");
   asm volatile ("\
	clrl d0	\n\
	movesw %0@,d0"  \
	: /* "=d" (output) */ \
	: "a" (where_to_get) \
	: "d0" ); 
	return(output);
}  

/* #define FUBYTE(x)   */
/*
	This FUBYTE macro must be coded to use "d0" because there is a
   possibility of a bad source address(where_to_get).  If the source
	address is bad then the kernel fault handler will cause "d0" to 
	have a -1 in "d0" and the routine that calls FUBYTE can detect the error.
*/
static int inline FUBYTE(where_to_get) 
void *where_to_get; 
{ 
	register int output asm ("d0");
   asm volatile ("\
	clrl d0	\n\
	movesb %0@,d0"  \
	: /* "=d" (output) */ \
	: "a" (where_to_get) \
	: "d0" ); 
	return(output);
}  

/* #define SUBYTE(addrx,valuex)    */
static inline SUBYTE(addrx,valuex) 
void *addrx; 
unsigned char valuex; 
{  register int output asm ("d0");
	asm volatile ("clrl d0\n	movesb %2,%1@"  \
	: "=&d" (output) \
	: "a" (addrx) , "d" (valuex) \
	: "d0" );  
	return(output);
} 

/* #define SUHALF(addrx,valuex)    */
static inline SUHALF(addrx,valuex) 
void *addrx; 
unsigned short valuex; 
{  register int output asm ("d0");
	asm volatile ("clrl d0\n	movesw %2,%1@"  \
	: "=&d" (output) \
	: "a" (addrx) , "d" (valuex) \
	: "d0" );  
	return(output);
} 

/* #define SUWORD(addrx,valuex)    */
static inline SUWORD(addrx,valuex) 
void *addrx; 
unsigned long valuex; 
{  register int output asm ("d0");
	asm volatile ("clrl d0\n	movesl %2,%1@"  \
	: "=&d" (output) \
	: "a" (addrx) , "d" (valuex) \
	: "d0" );  
	return(output);
} 

#else

#define FUWORD(x) fuword(x)
#define FUHALF(x) fuhalf(x)
#define FUBYTE(x) fubyte(x)
#define SUWORD(x,y) suword(x,y)
#define SUHALF(x,y) suhalf(x,y)
#define SUBYTE(x,y) subyte(x,y)

#endif /* __GNUC__ */

#endif /* KERNEL */
#endif /* ifndef FUWORD_H */
