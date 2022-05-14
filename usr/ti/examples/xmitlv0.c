char what_xmitlv0[]="@(#)xmitlv0.c	1.5 87/06/03";

/*  XMITLV0.C   Transmit levl 0

    This is an example program designed to demonstrate simple 
 sending and recieving on the level 0 driver.  To execute the
 level 0 calls this program should be linked with "/usr/lib/libnet.a". 
 Compile with the unix statement:
 cc xmitlv0.c -xmitlv0 /usr/lib/libnet.a

    The protocol for a send-receive program such as this is as
follows:
     Action                          Level 0 function
----------------------------------------------------------
  Open the device                      netopen
  Get host address                     lanaddr 
  Insure packet type free              dregtype
  Register packet type                 regtype
loop
  Send packet                          ethsend
  Recieve packet                       ethrcv
end loop
  Close device                         netclose 
 
  This particular program has a few options.

-d <48 bit destination address>
    This option allows the user to specify where the packets are
    to be sent.  The input address should be 12 hexideximal char-
    acters. Example: xmitlv0 -d 08002800abcd. 
    The default destination address is the same as the source address.

-n <count>
    This option allows the user to change the number of packets
    that are sent out.  The default is 5.
 

                                                             */ 
     

#include <stdio.h>
#include <errno.h>
#include "/usr/include/lan.h"

#define  TYPE      0xfaba
#define  MAXTIME   12
#define  SIGNAL    0
#define  SLOT      3
#define  PORT      0                        
#define  LENGTH    60
#define  RCVLNGTH  1200
#define  TMO       5
#define  DATA_SIZE 5
#define  MAXLEN    3100
#define  LPCOUNT   5;

extern int   errno;
unsigned int   fd, actlen, handle;
int   status;
char buf[60], *bp;
unsigned short src_adr[3] = { 0x0800,0x2800,0x0744 };
unsigned short dst_adr[3] = { 0x0800,0x2800,0x0573 };

 
struct {
       dstx : 1;
       } flags; 

struct blck {                                 /* Packet block */
       struct s_netioctl  netioctl;
       struct s_ethhdr    l0hdr;
       char               netdata[MAXLEN];
       }  pktblk, *pb;

main (argc, argv)
int argc;
char **argv;
{
   
   char *ch, chbuf[80];
   int c, f, count;
   extern int optind;
   extern char *optarg;

   int  i, j;
   int  rcv_cnt = 0;

   optind = 1;
   count = LPCOUNT;

   while ((c = getopt(argc, argv, "d:n:")) != EOF)
    {
       switch (c) 
       { 

       case 'd':
                flags.dstx = 1;
                sscanf(optarg, "%s", chbuf);
                gethex(chbuf, dst_adr); 
                break; 
                break;

       case 'n': 
                sscanf(optarg, "%d", &count);
                break;

     
       case '?':
       default : 
                printf("Usage: xmitlv0 [-d 48 bit address] [-n count]\n");
                return;
       
   }    /* switch */
}    /* while */

  fd = netopen(SLOT, PORT);                      /* open device */
  if (fd == -1)
    printf(" Error in open, errno = %x \n", errno);
  else
    printf(" Source opened w/o error \n");


  status = lanaddr(fd, src_adr);                /* get host address */
  if  (status == NET_OK)
    printf(" Lanaddr successful \n");
  else
    printf(" Error in lanaddr, status = %d \n", status);


  if (!flags.dstx)
    for (f = 0; f < 3; f++)
      dst_adr[f] = src_adr[f];         /* DEFAULT = send to itself */

  pktblk.l0hdr.type = TYPE;

  status = dregtype(fd, TYPE);              /* Free type */
  if  (status == NET_NOTREG)
    printf(" Dregtype successful \n");
  else
    printf(" Warning in dregtype: possible removal of active packet type, status = %d \n", status);

  status = regtype(fd, TYPE, MAXTIME, SIGNAL, &handle);    /* register packet */
  if  (status == NET_OK)
    printf(" Regtype successful \n");
  else
    printf(" Error in regtype, status = %d \n", status);

  printf(" final SRC addr: ");  
  for (f = 0; f < 3; f++) 
    printf("%4.4x",  src_adr[f]);
  printf("\n");

  printf(" final DEST addr:");  
  for (f = 0; f < 3; f++) 
    printf("%4.4x", dst_adr[f]);
  printf("\n\n");

  bp = buf; 
  for (f = 0; f < LENGTH; f++) 
    *bp++ = pktblk.netdata[f] = f + 32;
   

/* Send and Recieve loop */

  for (i = 0; i < count; i++)
    { 

      for (j = 0; j < 3; j++)
        pktblk.l0hdr.srcadr.sadr[j] =  src_adr[j]; 
 
      for (j = 0; j < 3; j++)
        pktblk.l0hdr.dstadr.sadr[j] =  dst_adr[j]; 

      status = ethsend(fd, &pktblk, LENGTH);       /* Send Packet */
      if (status == NET_OK)
        printf("\n Ethsend sucessful \n");
      else
        printf("\n Error in ethsend, status = %d \n", status); 

      status = ethrcv(fd, &pktblk, handle, RCVLNGTH, TMO, &actlen);
      if (status == NET_OK)
          rcv_cnt++;
      else
        printf(" Error in ethrcv, status = %d\n", status);
   

    }         
  

  status = netclose(fd);                       /* Close device */
  if (status == NET_OK)
    printf(" Netclose sucessful \n");
  else
    printf(" Netclose error, status = %d \n", status);

  printf("\n # of packets recieved back  successfully = %d\n", rcv_cnt);
}
 



gethex(buf, cadr)
char *buf;
char cadr[];
{
  int  f, temp;

  for (f = 0; f < 6; f++, buf += 2)
   {
    sscanf(buf, "%2x", &temp);
    cadr[f] = temp;
   }
    
  return;
}
