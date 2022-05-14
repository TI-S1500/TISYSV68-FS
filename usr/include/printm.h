/*
   COPYRIGHT (c) 1986 TEXAS INSTRUMENTS, INCORPORATED.  ALL RIGHTS RESERVED.
*/
/*
static char *sccs_id = @(#)printm.h	1.1 86/05/15";
*/

#define MAXKEYS  31

typedef struct  {   /*  node to direct b-tree search   */  
	short  level ;
	short  max   ;
	long   myloc ; 
	long   keys[MAXKEYS]  ;
	long   locn[MAXKEYS]  ;
	}  NODE ;


#define NZ   sizeof(NODE)
