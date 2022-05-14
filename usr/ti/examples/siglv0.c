char what_siglv0[]="@(#)siglv0.c	1.5 87/06/03";

/*    SIGLV0.C

       This LEVEL 0 program  recieves packets by implementing signalling.
    For proper execution of the LEVEL 0 calls, compile this program with
    the statement:
    cc siglv0.c -o siglv0 /usr/lib/libnet.a

       Signalling is done by first calling the Unix function:
              signal(sig, func)
    with "sig" set to 16, and "func" set to s0hdlr.  16 and 17 are
    user defined signals and work well for this purpose.  This value
    of "sig" must be passed to regtype.
       Initially a global variable, sig0set, is set to 0.  As long as
    this variable is zero SIGLV0 will wait, i.e., SIGLV0 will not poll with a
    ethrcv.  When a packet arrives the signal proccess forces execution to
    go to s0hdlr, where the sig0set variable is set allowing processing
    to continue.  In addition, s0hdlr, recalls signal(sig,func).
  
       Since more than one packet can be on the recieving queue at a
    time, SIGLV0 polls with ethrcv until all the packets are read.  A 
    timeout error will occure when no packets are on the queue.  By   
    using signalling SIGLV0 is assured of at least one packet on the
    queue, thus the timeout value passed to regtype (TMO) can be 
    set to 0.

       An outer loop is used to count the number of signals recieved.
    When this outer loop terminates, SIGLV0 prints the number of packets
    successfully recieved.  This outer loop can be changed by using the
    -n option.  The default is 5.


   The protocol for the signal-recieve program such as this one
   is as follows:

       Action                                Level 0 Function
--------------------------------------------------------------------
    Open the device                           netopen
    Insure packet type free                   dregtype
    Register packet type                      regtype
loop
    loop on signal set variable
     
    loop
      Receive packet                          ethrcv  
    end loop on time out

end loop
  
    Close device                              netclose

                                                                  */ 




#include <stdio.h>
#include <errno.h>
#include <sys/signal.h>
#include "/usr/include/lan.h"

#define  TYPE    0xfaba
#define  MAXTIME   5
#define  SIGNAL    16
#define  SLOT      3
#define  PORT      0
#define  MAXLEN    1500
#define  TMO       0 
#define  MAXLOOPS  5

extern int   errno;
int  status, fd, actlen, handle;


struct blck {
       struct s_netioctl netioctl;
       struct s_ethhdr   l0hdr;
       char              netdata[MAXLEN];
            } pktblk;

int   s0hdlr();
int   (*signal(sig, s0hdlr))();
int   err, sig;
int   sig0set;
       
main (argc, argv)
int argc;
char **argv;
  {
  int  j, g, option, count;
  int  maxlp = MAXLOOPS;
  char c;

  extern int  optind;
  extern char *optarg;


  count = 0;
  optind = 1;
  if (argc > 1)
  {
  while (( option = getopt(argc, argv, "n:")) != EOF) {
  switch(option){
      case 'n':     sscanf(optarg, "%d", &maxlp);
                    break;
 

      case '?':    
      default :     printf("Usage: siglv0 [-n loops] \n");
                    return;
   }
  }
 }

  fd = netopen(SLOT, PORT);                        /* Open device */
  if (fd == -1)
   {
    printf(" Error in open, errno = %x \n", errno);
    return;
   }
  else
    printf(" Netopen successful \n");
 

 
  sig0set = 0;                                  /* Register signal 16 */ 
  sig = SIGNAL;
  err = signal (sig, s0hdlr);
  if (err == 1)        
   {
    printf(" Error in init. sig, errno: %d\n", errno);
    return;
   }
 

  pktblk.l0hdr.type = TYPE;

  status = dregtype(fd, TYPE);                 /* Free type */
  if (status == NET_NOTREG)
     printf(" Dregtype Successful \n");
  else 
     printf(" Warning in dregtype: possible removal of active packet type, status = %d\n", status);

  status = regtype(fd, TYPE, MAXTIME, SIGNAL, &handle);   /* Register type */
  if  (status == NET_OK)
    printf(" Regtype successful \n");
  else
   {
    printf(" Error in regtype, status = %d \n", status);
    return;
   }


/*  Recieving loop */

  for (g = 0; g < maxlp; g++)
    {

      while (!sig0set);            /* poll variable until signalled */

      sig0set = 0;

                                  /* read packets until queue emptied */
      status = NET_OK;
      while ((status = ethrcv(fd, &pktblk, handle, MAXLEN, TMO, &actlen))
             == NET_OK)
      if (status == NET_OK)
        count++;
   
      if (status != NET_TIMOUT)
       {
        printf("\n  Error in ethrcv, status = %d \n", status);
        return; 
       }



    }  /* for */       
  


  status = netclose(fd);               /* close device */
  if (status == NET_OK)
    printf(" Netclose sucessful \n");
  else
    printf(" Netclose error, status = %d \n", status);
  
  printf("\n Number of packets recieved successfully = %d \n", count);
} 



s0hdlr(sval)
int sval;

/*
 *  This routine set the signal set variable, sig0set, and 
 *  recalls signal(sig,func) to re-intialize the signalling process
 */

{
  if (sval == SIGNAL)
   {
    sig0set = 1;
    err = signal (sig, s0hdlr);
    if (err == 1)        
      {
      printf(" Error in init. sig, errno: %d\n", errno);
      return;
      }
   }
  else 
   {
    sig0set = -1;
    printf("  Incorrect signal returned to s0hdlr: %d\n", sval);
   }
  return(sig0set);
} 
