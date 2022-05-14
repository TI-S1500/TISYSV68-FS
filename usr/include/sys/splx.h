/*
	This file contains inline assembly language macros for the "splx"
	routines used by the operating system.  They are meant to perform
   the same function as the called "splx() functions" that are in
	misc.s in the /src/uts/m68k/ml/misc.s.   The reason for changing 
	them to inline macros is to improve performance and be able to
	get a more accurate kernel trace with the kernel profile driver.

	Reference the header file asm.hs and the misc.s module for details
   about what code these macros emulate.

*/

#ifdef KERNEL
#ifdef __GNUC__     /* These macros only work with gnu compiler */
#ifndef splx
#define spl0()   \
( { int my_output; \
		   asm volatile ("movew sr,%0\n andw #0xf8ff,sr" \
			: "=d" (my_output)  \
			: /* no input */ );  \
			my_output ; } ) 

#define spl1()   \
( { int my_output; \
		   asm volatile ("movew sr,%0\n orw #0x2100,sr\n andw #0xf9ff,sr" \
			: "=d" (my_output)  \
			: /* no input */ );  \
			my_output ; } ) 

#define spl2()   \
( { int my_output; \
		   asm volatile ("movew sr,%0\n orw #0x2200,sr\n andw #0xfaff,sr" \
			: "=d" (my_output)  \
			: /* no input */ );  \
			my_output ; } ) 

#define spl3()   \
( { int my_output; \
		   asm volatile ("movew sr,%0\n orw #0x2300,sr\n andw #0xfbff,sr" \
			: "=d" (my_output)  \
			: /* no input */ );  \
			my_output ; } ) 

#define spl4()   \
( { int my_output; \
		   asm volatile ("movew sr,%0\n orw #0x2400,sr\n andw #0xfcff,sr" \
			: "=d" (my_output)  \
			: /* no input */ );  \
			my_output ; } ) 

#define spl5()   \
( { int my_output; \
		   asm volatile ("movew sr,%0\n orw #0x2500,sr\n andw #0xfdff,sr" \
			: "=d" (my_output)  \
			: /* no input */ );  \
			my_output ; } ) 

#define spl6()   \
( { int my_output; \
		   asm volatile ("movew sr,%0\n orw #0x2600,sr\n andw #0xfeff,sr" \
			: "=d" (my_output)  \
			: /* no input */ );  \
			my_output ; } ) 

#define spl7()   \
( { int my_output; \
		   asm volatile ("movew sr,%0\n orw #0x2700,sr" \
			: "=d" (my_output)  \
			: /* no input */ );  \
			my_output ; } ) 

#define splhi()   \
( { int my_output; \
		   asm volatile ("movew sr,%0\n orw #0x2700,sr" \
			: "=d" (my_output)  \
			: /* no input */ );  \
			my_output ; } ) 

#define splx(x)   \
( { int my_output; unsigned short my_x = (x);  asm volatile ("movew sr,%0\n movew %1,sr" \
			: "=&d" (my_output)  \
			: "d" (my_x) );  \
			my_output ; } ) 

#endif /* ifndef splx */
#endif /* __GNUC__ */

/*  UMIN and UMAX will work with SVS kernel also */

#ifndef UMIN
#define UMIN(a,b) ( (unsigned)a <= (unsigned)b ? a : b )
#endif
#ifndef UMAX
#define UMAX(a,b) ( (unsigned)a >= (unsigned)b ? a : b )
#endif

#endif /* KERNEL */
