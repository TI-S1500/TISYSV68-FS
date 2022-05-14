char what_inetxmit[]="@(#)inetxmit.c	1.6 87/06/03";

/*    inetxmit.c

     This is an example program designed to demonstrate simple 
  sending and recieving of packets on the level 1, inetnet driver.
  To exectute the inet calls, this program should be linked with
  "/usr/lib/libnet.a".
     
     The protocol for a send-receive program with the level 1 driver,
  is as follows:

        Action                             Level 0 function
--------------------------------------------------------------------
  Open the device                            inetopen
  Allocate a socket                          idpalloc 
  Open the socket                            idpopen
  Get host address                           idpgetad  
loop
  Send packet                                idpsend
  Recieve packet                             isprcv
end loop
  Close socket                               idpclose
  Close device                               inetclose
      
  The program assumes that both the source and the destination
  are on the same network.  If not, 'idpblk.idphdr.idpshost' should
  be filled with the source network, and 'idpblk.idphdr.idpdhost'
  with the destination network.  Like the socket fields 'idpsskt',
  and 'idpdskt', the network addresses only have to be initialized
  in the header block, 'idpblk.idphdr', and do not have to be 
  restated in the packet exchange loop.    

 
  This particular program has a few options.

-d <48 bit destination address>
   This option allows the user to specify where the packets are
   to be sent.  The input address must be 12 hexideximal characters.
   Example: inetxmit -d 080028abcd
   The default destination address is the same as the source address.

-k <socket>
   This option allows the user to specify which socket to open for
   recieving.  The default socket is 0, which allows the system to
   assign and return an ephemeral socket on a "idpalloc".  If the
   user specifies a socket, the socket number must be in the range 
   of valid well-known sockets (1 through 0xBB8).
   Example: inetxmit -k 302

                                                                  */ 

#include <stdio.h>
#include <errno.h>
#include <sys/signal.h>
#include "/usr/include/xns.h"

#define  TYPE      0xfaba
#define  MAXTIME   5
#define  SIGNAL    0
#define  SLOT      3
#define  PORT      0
#define  MAXLEN    1500
#define  TMO       5 
#define  DATA_SIZE 5
#define  MAXLOOP   5
#define  ADRLEN    3
#define  LENGTH    60
#define  SOCKET    0x0

extern int   errno;
int    fd, actlen, handle, port;
int    status, rcv_count;
unsigned int    socket;
unsigned long   port0net, portinet;
unsigned short  src_adr[] =   { 0x0800,0x2800,0x0573 };
unsigned short  dst_adr[] =   { 0x0800,0x0280,0x0744 };


struct {
       dstx : 1;
       } flags; 

struct blck {
       struct s_idpioctl idpioctl;
       struct s_idphdr   idphdr;
       char              idpdata[MAXLEN];
            } idpblk;
       
main (argc, argv)
int argc;
char **argv;
  {
  int  f, j, z, option;
  char  *bp, buf[LENGTH];
  unsigned short temp[3];

  extern int  optind;
  extern char *optarg;


  port = PORT; 
  socket = SOCKET;
  flags.dstx = 0;
  optind = 1;
  while (( option = getopt(argc, argv, "k:d:")) != EOF) {
  switch(option){
      case 'k':     sscanf(optarg, "%x", &socket);
                    printf(" -k socket %x\n", socket);
                    break;
 
      
      case 'd':     flags.dstx = 1;
                    gethex(optarg, dst_adr);
                    break;
  


      case '?':    
      default :     printf(" ILLEGAL OPTION\n");
                    return;
   }
  }
  fd = inetopen(SLOT);
  if (fd == -1)
    printf(" Error in inetopen, errno = %x \n", errno);
  else
    printf(" opened w/o error \n");
 
  status = idpalloc(fd, &socket);
  if (status == NS_OK)
    printf(" Idpalloc OK socket %x\n", socket);
  else
    printf(" Error in idpalloc # %d, socket %x \n", status, socket);

  
  status = idpopen(fd, socket, &handle, MAXTIME, SIGNAL);
  if  (status == NS_OK)
    printf(" idopen successful \n");
  else
    printf(" Error in idopen, errorno = %d \n", status);

  status = idpgetad(fd, src_adr, &port0net, &portinet);
  if (status == NS_OK)
    printf(" idpgetad OK \n");
  else
    printf(" Error in idpgetad # %d \n", status);

  if (!flags.dstx)
    for (f = 0; f < 3; f++)
      dst_adr[f] = src_adr[f];

  printf(" Final source address:");
  for (j = 0; j < ADRLEN; j++)
    printf(" %x", src_adr[j]);
  printf("\n");   

  printf(" Final destination address:");
  for (j = 0; j < ADRLEN; j++)
    printf(" %x", dst_adr[j]);
  printf("\n");   

  bp = buf;
  for (j = 0; j < LENGTH; j++)
    idpblk.idpdata[j] = j + 32;

  for (j = 0; j < ADRLEN; j++)
    idpblk.idphdr.idpshost[j] = src_adr[j];  

  for (j = 0; j < ADRLEN; j++)
    idpblk.idphdr.idpdhost[j] = dst_adr[j];  

  idpblk.idphdr.idpsskt = socket;            /* fill source and destination */
  idpblk.idphdr.idpdskt = socket;            /*        header sockets       */


  for (z = 0; z < MAXLOOP; z++)
    {

      status = idpsend(fd, &idpblk, LENGTH);
      if (status == NS_OK)
        printf("\n Idpsend successful \n");
      else
        printf(" Error in idpsend, status = %d \n", status); 

      status = idprcv(fd, &idpblk, handle, MAXLEN, TMO, &actlen);
      if (status == NS_OK)
          rcv_count++;
      else
        printf(" Error in idpercv, status = %d \n", status); 


    }  /* for */       
  


  status = idpclose(fd, socket);
  if (status == NS_OK)
    printf(" Idpclose sucessful \n");
  else
    printf(" Idpclose error, status = %d \n", status);

  status = inetclose(fd);
  if (status == NS_OK)
    printf(" Inetclose sucessful \n");
  else
    printf(" Inetclose error, status = %d \n", status);
  
  printf("\n # of packets recieved back successfully = %d\n", rcv_count);
} 

gethex(ch, cadr)
   char *ch;
   char cadr[];
   {
      int  f, temp;

      for (f = 0; f < 6; f++, ch += 2) 
       {
        sscanf(ch, "%2x", &temp);
        cadr[f] = temp; 
       }
   }
