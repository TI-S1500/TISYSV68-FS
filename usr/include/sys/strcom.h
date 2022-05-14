/*
 	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1989.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/
/* @(#)strcom.h	1.8 90/01/12 */

/*************************************************************
*              strnet element common header                  *
*                                                            *
*   The first three fields are the same as the first three   *
*   fields in the busnet element.                            *
*************************************************************/
struct  strnet_head   {
  struct  strnet_head  *next;     /* pointer to next element   */
  long     slot;                  /* slot number of the sender */
  long     type;                  /* type number               */
  long     eladdr;                /* original address of the element */
  long     stat;                  /* status of the element     */
  long     size;                  /* size of the whole element */
};

struct  strn_head  {
  long        op;     		/* strnet opcode */
  long        stat;   		/* status     */
  long        dev_num;          /* device number passed to board */
  long        handle; 		/* handle from the CCB driver  */
  long        oplink;           /* pointer to the internal structure */
};

#define  STRNET_HEAD_SIZE  (sizeof(struct  strnet_head))
#define  STRN_HEAD_SIZE    (sizeof(struct  strn_head))
#define  MAX_STREL_SIZE		1028          /* max. str element size */

/*
* flags for function get_msgel and str_pair
*/
#define  PCOUNT    0x00000001
#define  PBUFLMT   0x00000002

/*
*  type reserved for the strnet
*/
#define  STRN_TYPE    2

#define  STRNM_ID   101              /* net/if.h strnet module id */
#define  STRN_ID_MASK    0xf0000000  /* id number mask  */
#define  STRN_SLOT_MASK  0x0f000000  /* slot number mask */
#define  STRN_PORT_MASK  0x000000ff  /* port number mask */

#define  LLIEN_ID        1           /* device id on the CCB */
#define  STRN_IFNAME_LEN   6         /* max. length of interface name */

/*
*  strcom statistics buffer
*/
struct  strcom_stat {
	int  aloc_cnt;
	int  aloc_max;
	int  fail_cnt;
 	int  curr_bcnt;
	int  max_bcnt;
};

/*
*   ioctl op code for strnet
*/
#define  STRNET_CFG    0x00000001    /* send CCB dev config and open it */
#define  STRN_CLRSTAT  0x00000002    /* clear statistics of one interface */

/* 
*  STRNET_CFG ioctl data buffer definition
*/
struct   strnet_cfgio {
    unsigned long    dev_num;
    char     ifname[STRN_IFNAME_LEN];
    int      smbufs;       /* number of small buffers needed in the rcv pool */
    int      lgbufs;       /* number of large buffers needed int he rcv pool */
};

/* 
*  STRN_CLRSTAT ioctl                          
*/
struct   strn_clrstatio {
    char     ifname[STRN_IFNAME_LEN];
};

