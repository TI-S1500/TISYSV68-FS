char what_post[]="@(#)post.c	1.5 87/06/03";

/* 
   POST.C 
   
    This program posts a resource, "rsrc1", using the inet driver call,
    postrsrc.  

    Compile this program with the command:
     cc post.c -o post /usr/lib/libnet.a
                                                                  */ 

#include <stdio.h>
#include <errno.h>
#include <sys/signal.h>
#include "/usr/include/xns.h"

#define  SLOT      3
#define  MAXSIZE   10

extern int      errno;
int             f, status, fd;
unsigned long   port0net, portinet;


struct {
  struct s_rmioctl rmioctl;
  char info[256];
} infoblk;
       
main ()
  {


  fd = inetopen(SLOT);
  if (fd == -1)
    printf("  DS1 error in inetopen, errno = %x \n", errno);
  else
    printf("  DS1 opened w/o error \n");


  for (f = 0; f < MAXSIZE; f++)       
    infoblk.info[f] = 'a';

  status = postrsrc(fd, "rsrc1", &infoblk, MAXSIZE);
  if (status == NS_OK)                      
    printf(" postrsc ok.\n"); 
  else 
    printf(" postrsc failure , status = %d\n", status); 


  status = inetclose(fd);
  if (status == NS_OK)
    printf(" Inetclose sucessful \n");
  else
    printf(" Inetclose error, status = %d \n", status);
 
} 
