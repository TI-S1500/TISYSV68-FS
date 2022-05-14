/*
 * The DECIMALTYPE is a machine-independent method for the representation
 * of numbers of up to thirty-two significant digits, with or without a
 * decimal point, and exponents in the range -64 to +63. DECIMALTYPE 
 * numbers consist of an exponent and a mantissa (or fractional part) in 
 * base 100.  In normalized form, the first digit of the mantissa must be 
 * greater than zero.
 *
 * When used within a program, DECIMALTYPE numbers are stored in a C structure
 * of the type shown below.  This file should be included in all C source
 * files that use any of the decimal routines.
 */

#define DECSIZE 16

struct decimal
{
	short dec_exp;			  /* -64 to +63 */
	short dec_pos;			  /* 1: pos, 0: neg */
	short dec_ndgts;		  /* # of dec_dgts in use (0 offset) */
	unsigned char dec_dgts[DECSIZE];
};

typedef struct decimal dec_t;

/*
 * Packed format (format in records in file)
 *	First byte = 
 *		top 1 bit = sign  (0=neg, 1=pos)
 *		low 7 bits = exponent in excess 64 format
 *	rest of bytes = base 100 digits in 100 complement format.
 *	  
 *	zero is represented as 80000...  (hex)
 */
