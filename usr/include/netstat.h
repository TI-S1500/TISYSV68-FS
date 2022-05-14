/*
 	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
 */
/* @(#)netstat.h	1.1 86/09/19 */ 

/******************************************************************
*                                                                 *
*  MODULE NAME : stat.h
*                                                                 *
*  ABSTRACT : Define the statistics buffer
*                                                                 *
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
           unsigned long   LCseconds;  /*  elapsed time in seconds    */        
           unsigned short  LCcrcerr;   /*  CRC errors                 */ 
           unsigned short  LCalnerr;   /*  Alignment errors           */ 
           unsigned short  LCrscerr;   /*  Resource errors            */
           unsigned short  LCovrnerr;  /*  Overrun errors             */
           unsigned short  LCtnocar;   /*  xmit - no carrier          */
           unsigned short  LCtlcts;    /*  xmit - loss cts            */
           unsigned short  LCtunder;   /*  xmit - DMA underrun        */
           unsigned short  LCtdefer;   /*  xmit - deferrals           */
           unsigned long  LCtsqe;      /*  xmit - heart beat          */
           unsigned short  LCtcolerr;  /*  xmit - too many collisions */
           long  LCtcoll[16];          /*  xmit w/collisions 
                                               for different retries  */        
           unsigned short  LCrsf;      /*  rcv - frame too small      */
           unsigned short  LCrnoeof;   /*  rcv - no EOF flag
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
           unsigned short  LCtfsize[25]; /*  xmit frame sizes - 
                                                 from 0 to 1535 bytes */        
           unsigned short  LCrfsize[25]; /*  rec. frame sizes - 
                                                 from 0 to 1535 bytes */  
           unsigned short  LCunktype;  /*  received frame with unknown type */
           long  LCbdcast;        /*  # of broadcast packets received */
           long  LCmulticast;     /*  # of multicast packets received */
           unsigned short  LCcurstart; /*  xmiter restart             */
           unsigned short  LCrurstart; /*  receiver restart           */
	   char  version[8];		/* zero-terminated version string */
         };                                                                     

