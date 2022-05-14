/*######################################################################*/
/*___	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1983.  ALL	*/
/*___	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.	*/
/*___	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT	*/
/*___	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND */
/*___	ASSOCIATED DOCUMENTATION.					*/
/*######################################################################*/

static char sccsid[] = "@(#)ttyioctl.c	1.3 (TI) 92/12/22";

/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
/*___									*/
/*___	Communications Carrier	board common ioctl.			*/
/*___									*/
/*___									*/
/*___									*/
/*___	Revision	System V					*/
/*___	Date:		March 23, 1988					*/
/*___									*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/

#include "sys/param.h"
#include "sys/types.h"
#include "sys/ttold.h"
#include "sys/termio.h"
#include "sys/dsr.h" 

/************************************************************************/
/*___ ttyioctl ___							*/
/************************************************************************/
/*___ Returns the size and direction of the structure passed in the	*/
/*___ queue element. Done this way because the Unix groups have 	*/
/*___ suggested that in the future the type and length of 'arg' will    */
/*___ be defined in the sys call, modification will then only require	*/
/*___ removal of this module.						*/
/*___									*/
/************************************************************************/
/* Description of variables						*/
/*									*/
/*  cmd     ............ cmd from ioctl command 			*/
/*  dir     ............ address of direction variable			*/
/************************************************************************/

ttyiocd(cmd,dir)
int cmd,*dir;
{
/*----------------------------------------------------------------------*/
/* 'DIR' is the direction of the ioctl. 0 indicates this is going from  */
/* the user space to the CCB. 1 indicates that the struct is going from */
/* the CCB to the user space.						*/
/*----------------------------------------------------------------------*/

	switch(cmd){

	case TCSETA:
	case TCSETAF:
	case TCSETAW:
		*dir=0;
		return(sizeof(struct termio));
		break;
	case TIOCSETP:
		*dir=0;
		return(sizeof(struct sgttyb));
		break;
	case LDSETT:
		*dir=0;
		return(sizeof(struct termcb));
		break;
	case TIOCMSET:
	case TIOCMBIS:
	case TIOCMBIC:
	case TI_HDSET: /* half-duplex special */
		*dir=0;
		return(sizeof(int));
		break;
/*----------------------------------------------------------------------*/
/* Change direction  (dir)						*/
/*----------------------------------------------------------------------*/
	case TCGETA:
		*dir=1;
		return(sizeof(struct termio));
		break;
	case TIOCGETP:
		*dir=1;
		return(sizeof(struct sgttyb));
		break;
	case LDGETT:
		*dir=1;
		return(sizeof(struct termcb));
		break;
	case TIOCMGET:
	case TI_HDGET: /* half-duplex special */
		*dir=1;
		return(sizeof(int));
		break;
	default:
		return(0);
	}
}

