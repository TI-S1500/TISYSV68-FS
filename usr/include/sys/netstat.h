/*
 	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/
/* @(#)netstat.h	1.7 (TI) 91/07/01 */ 

/******************************************************************
*                                                                 
*  The network interface statistics buffer definition 
*                                                                 
******************************************************************/
struct   sLCstatbuf  {             /*  Statistics buffer              */        
	   union {
	     unsigned char adr[6];
	     unsigned short wadr[3];
	   } LChadr;  		   /*  48-bit host address	      */
           struct    { 
             unsigned char    byte1;
             unsigned char    byte2;
           }         LCcksum;      /*  host address checksum          */
           unsigned char   LCdescr[64]; /* text description of interface,
                                           string should be NULL terminated */
           unsigned long   LCopttype;  /*  option card type           */
           unsigned long   LCadpttype; /*  adapter card type          */
           unsigned long   LCprotocol; /*  data link layer protocol   */
           unsigned long   LCspeed;    /*  if speed in bits/second    */
           unsigned long   LCmtu;      /*  max transmission unit in bytes */
           unsigned long   LCenablemc; /*  number of multicast enabled */
           unsigned long   LCmacenable;/*  enabled MAC sublayer status*/
           unsigned long   LCtdr;      /*  value of Time-domain Reflect test */
           unsigned long   LCseconds;  /*  elapsed time in seconds    */        
           unsigned long   LCcrcerr;   /*  CRC errors                 */ 
           unsigned long   LCalnerr;   /*  Alignment errors           */ 
           unsigned long   LCrscerr;   /*  Resource errors            */
           unsigned long   LCovrnerr;  /*  Overrun errors             */
           unsigned long   LCtnocar;   /*  xmit - no carrier          */
           unsigned long   LCtlcts;    /*  xmit - loss cts            */
           unsigned long   LCtunder;   /*  xmit - DMA underrun        */
           unsigned long   LCtdefer;   /*  xmit - deferrals           */
           unsigned long   LCtsqe;     /*  xmit - heart beat          */
           unsigned long   LCtcolerr;  /*  xmit - too many collisions */
           unsigned long   LCtcoll[16];  /*  xmit w/collisions 
                                               for different retries  */        
           unsigned long   LCrsf;      /*  rcv - frame too small      */
           unsigned long   LCrnoeof;   /*  rcv - no EOF flag
                                                  for Bitstuffing     */ 
           unsigned long   LCrpkt;     /*  packets received           */      
           unsigned long   LCrbyte;    /*  bytes received             */
           unsigned long   LCtpkt;     /*  packets transmitted        */
           unsigned long   LCtbyte;    /*  bytes transmitted          */   
           unsigned short  LCfdmax;    /*  maximum FD's in the 
                                                     receive area     */        
           unsigned short  LCfdlow;    /*  the lowest number of FD's left */
           unsigned short  LCbdmax;    /*  maximum BD's in the
                                                     receive area     */ 
           unsigned short  LCbdlow;    /*  the lowest number of BD's left */
           unsigned long   LCtfsize[25]; /*  xmit frame sizes - 
                                                 from 0 to 1535 bytes */        
           unsigned long   LCrfsize[25]; /*  rec. frame sizes - 
                                                 from 0 to 1535 bytes */  
           unsigned long   LCunktype;  /*  received frame with unknown type */
           unsigned long   LCbdcast;   /*  # of broadcast packets received */
           unsigned long   LCmulticast;  /*  # of multicast packets received */
           unsigned short  LCcurstart; /*  xmiter restart             */
           unsigned short  LCrurstart; /*  receiver restart           */
	   char  version[8];		/* zero-terminated version string */
	   unsigned long   LCtlatcoll;  /* xmit - late collision (82596) */
	   unsigned long   LCrcvcdt;	/* rcv - reception collision (82596) */
	   unsigned long   LCrcvlenerr; /* rcv - length field error (82596) */
           unsigned long   LCinrngerr;  /* rcv - in range len errors (82596) */
           unsigned long   LCoutrngerr; /* rcv - out range len errors (82596) */
	   unsigned short  LCfdhi;      /*  the highest # of FD's ever get */
	   unsigned short  LCbdhi;      /*  the highest # of BD's ever get */
	   unsigned short  LCtqlen;     /*  currnet # of packets on xmt queue */
	   unsigned long   LCtbdcast;	/*  # of broadcast packets sent */
	   unsigned long   LCtmulticast;/*  # of multicast packets sent */
	   unsigned long   LCtflow; 	/* # of outbound pkts discarded for 
					flow control */
	   unsigned long   LCrflow;	/* # of inbound pkts discarded for 
					flow control */
	   unsigned long   LCunkucast;  /* # of unknown-type uni-cast rcvd */
	   unsigned long   reserve1;    /* reserved for future use     */
	   unsigned long   reserve2;    /* reserved for future use     */
	   unsigned long   reserve3;    /* reserved for future use     */
	   unsigned long   reserve4;    /* reserved for future use     */
         };                                                                     


/************************************************************************/
/* Possible values for the data layer protocol.  These values are from  */
/* the RFC's for SNMP.  Any additions should match the new RFC's        */
/************************************************************************/
#define other			1	/*  none of the following          */
#define regular1822		2	/*                                 */
#define hdh1822			3	/*                                 */
#define ddn_x25			4	/*                                 */
#define rfc877_x25		5	/*                                 */
#define ethernet_csmacd		6	/*                                 */
#define iso88023_csmacd		7	/*                                 */
#define iso88024_tokenBus	8	/*                                 */
#define iso88025_tokenRing	9	/*                                 */
#define iso88026_man		10	/*                                 */
#define starLan			11	/*                                 */
#define proteon_10MBit		12	/*                                 */
#define proteon_80MBit		13	/*                                 */
#define hyperchannel		14	/*                                 */
#define fddi			15	/*                                 */
#define lapb			16	/*                                 */
#define sdlc			17	/*                                 */
#define t1_carrier		18	/*                                 */
#define cept			19	/*  european equivalent of T-1     */
#define basicIsdn		20	/*                                 */
#define primaryIsdn		21	/*                                 */
#define propPointToPointSerial	22	/*  proprietary serial             */
#define ppp			23	/*                                 */
#define softwareLoopback	24	/*                                 */
#define eon			25	/*                                 */
#define ethernet_3Mbit		26	/*                                 */
#define nsip			27	/*                                 */
#define slip			28	/*                                 */
