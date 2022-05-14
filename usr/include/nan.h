/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/
/* --------------------------------------------------------------------------
   COPYRIGHT (c) 1990   TEXAS INSTRUMENTS INCORPORATED   ALL RIGHTS RESERVED
  --------------------------------------------------------------------------- */

#ident	"@(#)nan.h	1.5 91/03/19"
/* Handling of Not_a_Number's (only in IEEE floating-point standard) */
#if _IEEE

#ifndef MAXFLOAT
#include <values.h>
#endif

typedef union 
{
	double	d;
	long	l[2];
} dnan; 

	/* IsNANorINF checks that exponent of double == 2047 *
	 * i.e. that number is a NaN or an infinity	     */
	
#define IsNANorINF(X)  ((((dnan *)&(X))->l[0] & 0x7FF00000) == 0x7FF00000)

	/* IsINF must be used after IsNANorINF		*
 	 * has checked the exponent 			*/

#define IsINF(X)  ((((dnan *)&(X))->l[0] & 0xFFFFF) == 0 &&  \
                    ((dnan *)&(X))->l[1] == 0)

	/* IsPosNAN and IsNegNAN can be used 		*
 	 * to check the sign of infinities too		*/

#define IsPosNAN(X)  ((((dnan *)&(X))->l[0] & 0x80000000) == 0)

#define IsNegNAN(X)  ((((dnan *)&(X))->l[0] & 0x80000000) != 0)

	/* GETNaNPC gets the leftmost 32 bits 		*	
	 * of the fraction part				*/

#define GETNaNPC(dval)   ((((dnan *)&(dval))->l[0] & 0xFFFFF) << 12 | \
			   ((dnan *)&(dval))->l[1] >> 20) 

#define KILLFPE()       (void) kill(getpid(), 8)
#define NaN(X)   	(IsNANorINF(X) && !IsINF(X))
#define KILLNaN(X)      if (NaN(X)) KILLFPE()
#define ChkNaNINF(X)	if (IsNANorINF(X)) \
			    if (IsINF(X)) \
				X = IsPosNAN(X) ? MAXFLOAT : -MAXFLOAT; \
			    else \
				KILLFPE()

#else

typedef double dnan;
#define IsINF(X)   0
#define IsPINF(X)  0
#define IsNegNAN(X)  0
#define IsPosNAN(X)  0
#define IsNAN(X)   0
#define GETNaNPC(X)   0L

#define NaN(X)  0
#define KILLNaN(X)
#endif
