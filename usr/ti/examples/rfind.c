char what_rfind[]="@(#)rfind.c	1.5 87/06/03";

/*    rfind.c

       This program is designed to find a packet, "rsrc", using
    the inet driver call findrsrc.

    
       This program has the following option:

-a < 48 bit post address>
   This option allows the user to specify at which address the 
   resource is posted at.  The input address must be 12 hexideximal
   characters.   Example: rfind -a 080028000abcd
   The default is what is initialized in find_adr, i.e, 080028000554. 

                                                                  */ 

#include <stdio.h>
#include <errno.h>
#include <sys/signal.h>
#include "/usr/include/xns.h"

#define  SLOT      3
#define  MAXLEN    256

extern int   errno;
int  status, fd, actlen;
unsigned long netadr = 0;
unsigned short find_adr[] = { 0x0800, 0x2800, 0x0554 };

struct {
  struct s_rmioctl rmioctl;
  char info[256];
} infoblk;
       
main (argc, argv)
int argc;
char **argv;
  {
  int  f, option;

  extern int  optind;
  extern char *optarg;


  while (( option = getopt(argc, argv, "a:")) != EOF) {
  switch(option){

      case 'd':     gethex(optarg, find_adr);
                    break;

      case '?':    
      default :     printf("  find.c ILLEGAL OPTION\n");
                    return;
   }
  }

  fd = inetopen(SLOT);
  if (fd == -1)
    printf(" error in inetopen, errno = %x \n", errno);
  else
    printf(" opened w/o error \n");

          

  status = findrsrc(fd, "rsrc1", netadr, find_adr, &infoblk, MAXLEN, &actlen);
  if (status == NS_OK)                      
    printf("  findrsc ok \n"); 
  else 
    printf("  findrsc failure, status = %d\n", status); 


  status = inetclose(fd);
  if (status == NS_OK)
    printf(" inetclose sucessful \n");
  else
    printf(" inetclose error, status = %d \n", status);
 
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
      
      return;
   }
