/*
	This file contains inline assembly language macros for the 
	inc() and dec() routines used by the operating system.  
	They are meant to perform the same function as the called 
	functions that are in incdec.s in the /src/uts/m68k/ml/incdec.s.   
	The reason for changing them to inline macros is to improve 
	performance.

*/

#ifdef KERNEL
#ifdef __GNUC__     /* These macros only work with gnu compiler */
#pragma EXTENSIONS
#ifndef inc
#define inc(x)   \
( { short new_value; short old_value;\
	volatile short *my_x = (x); unsigned short saved_sr; \
	 asm volatile ("\n\
	movew sr,%2\n\
	orw #0x2700,sr\n\
0:\n\
	movew %3@,%1\n\
	movew %1,%0\n\
	addiw #1,%0\n\
	casw %1,%0,%3@\n\
	jne 0b\n\
	movew %2,sr\n\
	extl %1 "\
			: "=&d" (new_value), "=&d" (old_value) ,"=&d" (saved_sr) \
			:  "a" (my_x) );  \
			 old_value; } )

#endif /* ifndef inc */

#ifndef incl
#define incl(x)   \
( { int new_value; int old_value;\
	volatile int *my_x = (x); unsigned short saved_sr; \
	 asm volatile ("\n\
	movew sr,%2\n\
	orw #0x2700,sr\n\
0:\n\
	movel %3@,%1\n\
	movel %1,%0\n\
	addil #1,%0\n\
	casl %1,%0,%3@\n\
	jne 0b\n\
	movew %2,sr\n\
	"\
			: "=&d" (new_value), "=&d" (old_value) ,"=&d" (saved_sr) \
			:  "a" (my_x) );  \
			 old_value; } )
#endif /* ifndef incl */

#ifndef dec
#define dec(x)   \
( { short new_value; short old_value; \
	volatile short *my_x = (x); unsigned short saved_sr; \
	 asm volatile ("\n\
	movew sr,%2\n\
	orw #0x2700,sr\n\
0:\n\
	movew %3@,%1\n\
	movew %1,%0\n\
	subiw #1,%0\n\
	casw %1,%0,%3@\n\
	jne 0b\n\
	movew %2,sr\n\
	extl %0 "\
			: "=&d" (new_value), "=&d" (old_value) ,"=&d" (saved_sr) \
			: "a" (my_x) );  \
			 new_value; } ) 
#endif /* ifndef dec */

#ifndef decl
#define decl(x)   \
( { int new_value; int old_value; \
	volatile int *my_x = (x); unsigned short saved_sr; \
	 asm volatile ("\n\
	movew sr,%2\n\
	orw #0x2700,sr\n\
0:\n\
	movel %3@,%1\n\
	movel %1,%0\n\
	subil #1,%0\n\
	casl %1,%0,%3@\n\
	jne 0b\n\
	movew %2,sr\n\
	"\
			: "=&d" (new_value), "=&d" (old_value) ,"=&d" (saved_sr) \
			: "a" (my_x) );  \
			 new_value; } ) 
#endif /* ifndef decl */
#endif /* __GNUC__ */
#endif /* KERNEL */
