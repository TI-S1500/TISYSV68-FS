/* @(#)example.c	1.3 87/09/01 */
/************************************************************************/
/* The following example VPSC program uses the standard IMS		*/
/* "cctil" inquiry.  It reads a given file on the host and writes the	*/
/* information on a given System 1000 Series computer file		*/
/************************************************************************/

#include	<stdio.h>
#include	<ctype.h>
#include	<errno.h>
#include	<sys/types.h>
#include	"keycodes.h"
#include	"userv3279.h"

/* Constant definitions */

#define YES	 1
#define NO	 0

extern char *gets();

static FILE *fp;		       /* document file control structure */
long start_time, end_time;	       /* transfer start and end times */
int lines=0;			       /* line count */
int bytes=0;			       /* byte count */
int cnt;			       /* per line byte count */

main (argc, argv)
int   argc;			       /* arg count */
char  *argv[];			       /* array of arg pointers */
{
       int curr_st;		       /* v3279 status */
       int c = 0;		       /* get character	variable */
       int retry = YES;		       /* ask user for document again */
       char doc_name[80], *document;   /* document name and ptr to it */
       char TSO_name[80], *tsoptr;     /* cctil name and ptr to it */
       char uid[80], *uidp;	       /* security userid and ptr to it */
       char psw[80], *pswp;	       /* secrurity password and ptr to it */
       char block_strg[4];	       /* blockno as a string */
       char tok_strg[82];	       /* tss response string */
       char txt_strg[82];	       /* one line of data */
       char eline[100];		       /* tss security request string */
       int start_parm = 1;	       /* parameter count */
       int block_complete = 0;	       /* cctil block complete flag */
       int blockno = 1;		       /* block to request */
       int lineno;		       /* line counter */

/* disable video and keyboard */

       if (open_mcp(0x00000000,0))  {
	       printf("	Err on open_mcp	call, errno=%d",errno);
	       abort();
       }

/* get dataset names from caller if not provided on cmd line */

       while (retry)  {

	       if (argc	== start_parm)	{

/* no input file name, prompt for it */

		       printf(" Enter data set pathname: ");
		       tsoptr =	gets(TSO_name);
	       }
	       else  {

/* pathname passed */

		       strcpy (TSO_name, argv[start_parm]);
		       tsoptr =	TSO_name;
	       }
	       if (argc	< (start_parm +	2))  {

/* no output file name, prompt for it */

		       printf(" Enter the output file name: ");
		       document	= gets(doc_name);      /* get doc name */
	       }
	       else  {

/* document name passed */

		       strcpy (doc_name, argv[(start_parm + 1)]);
		       document	= doc_name;
	       }

/* open output file */

	       fp = fopen (document, "w") ;
	       if (fp == NULL)	{

/* fp is not valid, ask caller what to do */

		       printf("	 Can't open document file %s\n",document);
		       printf("  Do you want to Quit? (Y/N): ");
		       c = getchar();
		       if ( c == 'y' ||	c == 'Y')
			       exit (0);
	       }
	       else

/* fp is valid, go ahead */

		       retry = NO;

/* end while ( retry ) */

       }

/* prompt user for IMS security id/password */

       printf(" Enter TSS security id: ");
       uidp = gets(uid);
       printf(" Enter TSS password: ");
       pswp = gets(psw);

/* See if we are already logged on.  If not, a logon call must */
/* be made successfully before continuing. */

       vid_off();
       curr_st = get_status();
       if (!((curr_st &	BOUND) && (curr_st & DATATRAFFIC)))  {
	       if (logon("adaimb"))  {
		       printf("	 Err on	logon call, errno= %d",errno);
		       abort();
	       }

/* wait until "TERMINAL CONNECTED" msg hits. */

	       wait_str("DFS2002",0,2);
	       do_wait(WAIT_STRING);
       }
       vid_off();

 /* now build TSS security request. */

       send_key	(CLRKEY);
       do_wait(HOSTFREE);
       sprintf(eline,"tssim ");
       strcat(eline,uid);
       strcat(eline," ");
       strcat(eline,psw);
       strcat(eline," ");

/* send TSS security request */

       send_string(eline);
       send_key(EOSKEY);
       send_key(ENTER);
       while (1)  {
	       if (tss_resp())	{

/* get tss response */

		       get_scrn(tok_strg, 23, 0, 10);
		       if (strncmp(tok_strg, "TSS185I",7) == 0)

/* good security logon made */

			       break ;
		       else  {
			       vid_on();
			       sput_vdu("CCTIL REENTER",24,66,TURQOS,
				       REVERSE|BLINK);
		       }
	       }
	       else  {

 /* some screen we are not looking for has arrived, tell */
 /* operator they need to hit A2 key after viewing it */

		       vid_on();
		       sput_vdu("CCTIL A2 REQD", 24, 66, TURQOS, REVERSE|BLINK);
	       }
       }

/* initialize for cctil transfer */

       time(&start_time);
       send_key	(CLRKEY);
       do_wait(HOSTFREE);
       sput_vdu("CCTIL ACTIVE ", 24, 66, YELLOW, REVERSE);

/* send up error entry to get in sync */

       send_string("cctil ");
       send_key(ENTER);
       while (1)  {
	       if (cctil_resp())  {

 /* get cctil response */

		       get_scrn(tok_strg, 1, 1,	10);
		       if (strcmp(tok_strg, "CCTIL.110") == 0)

 /* error msg hit, we're in sync */

			       break ;
	       }

 /* some screen we are not looking for has arrived, tell */
 /* operator they need to hit A2 key after viewing it */

	       vid_on();
	       sput_vdu("CCTIL A2 REQD", 24, 66, TURQOS, REVERSE|BLINK);
       }

/* start the cctil transfer request itself. */

       while (1)  {
	       vid_off();
	       send_key(HOME);

/* build cctil request */

	       block_complete =	0;
	       sprintf(eline,"cctil ");
	       strcat(eline,tsoptr);
	       strcat(eline,",");
	       sprintf(block_strg,"%u",blockno);
	       strcat(eline,block_strg);
	       strcat(eline,",3");

/* request 3 blocks */

	       send_string(eline);
	       send_key	(ENTER);
	       while (!block_complete)	{
		       wait_answer();

/* we have data */

		       vid_off();
		       for (lineno = 2;	lineno < 24; lineno++) {
			       get_scrn(txt_strg, lineno, 1, 80);
			       if (strncmp(txt_strg, "CCTIL", 5) == 0)	{

/* found end of block */

				       block_complete =	1;
				       break ;
			       }
			       fprintf(fp,"%s\n",txt_strg);
			       bytes +=	79;
			       lines++;
		       }

/* end for all lines */

		       if (!block_complete)

/* request next page */

			       send_key(PA1);

/* end while block not complete */

	       }
	       blockno += 3;
       }
}

/************************************************************************/
/* wait_answer								*/
/*							 		*/
/* After an enter of some kind, we come here to wait on a response that	*/
/* we expect to receive.						*/
/************************************************************************/

wait_answer()
{
       char cctil_strg[10];	      /* cctil response string */

       sput_vdu("CCTIL WAITING", 24, 66, YELLOW, REVERSE);

/* wait for response from cctil */

       while (1)  {
	       if (cctil_resp())  {

/* got cctil response */

		       get_scrn(cctil_strg, 1, 1, 10);
		       if (strcmp(cctil_strg, "CCTIL.100") == 0)

/* cctil found EOF in source file */

			       leave();
		       if (strcmp(cctil_strg, "CCTIL.110") == 0)

/* cctil dataset name not found */

			       leave();
		       if (strcmp(cctil_strg, "----+----") == 0)  {

/* valid data response, return */

			       sput_vdu("CCTIL ACTIVE ", 24, 66, YELLOW,
				       REVERSE);
			       return (1);
		       }

/* end if cctil response */

	       }

/* some other response */

	       vid_on();
	       sput_vdu("CCTIL A2 REQD", 24, 66, TURQOS, REVERSE|BLINK);
       }
}

/************************************************************************/
/* cctil_resp								*/
/*									*/
/* This routine waits for data to be received.  If the received data	*/
/* is output from inquiry CCTIL, return 1 else return 0.		*/
/************************************************************************/

cctil_resp()
{
       char tst_strg[12] ;	      /* host response string */

/* wait for data to return */

       do_wait(RCVDATA);

/* get data returned */

       get_scrn(tst_strg, 0, 1,	6);

/* see if cctil data */

       if ((strcmp(tst_strg,"CCTIL"))==0)
	       return (1);
       else
	       return(0);
}

/************************************************************************/
/* tss_resp								*/
/*									*/
/* This routine waits for data to be received.  If the received data	*/
/* is output from inquiry TSSIM, return 1 else return 0.		*/
/************************************************************************/

tss_resp()
{
       char tst_strg[12] ;	      /* host response string */

/* wait for data to return */

       do_wait(RCVDATA);

/* get data returned */

       get_scrn(tst_strg, 23, 0, 11);

/* see if tss data */

       if ((strncmp(tst_strg,"TSS",3))==0)
	       return (1);
       else
	       return(0);
}

/************************************************************************/
/* do_wait								*/
/*									*/
/* Make a wait_mcp call for the EVENT passed as a parameter.		*/
/************************************************************************/

do_wait(event)
int event;			      /* event for which we must wait */
{
       int status;		      /* status returned by wait_mcp */

       while(1)	 {
	       status =	wait_mcp(10, event, 0, 0);

/* event happened? */

	       if (status == event)
		       return;

/* no, see what happened */

	       switch(status)  {

/* timeout occurred before event happened */

	       case 0:
		       break;	       /* just go wait again */

/* error */

	       case -1:
		       printf("	Err returned by	wait_mcp, err=%d",errno);
		       abort();

/* unknown error */

	       default:	
		       printf("	Unrecognized return from mcp_wait, code=%d",
			      status);
		       abort();
	       }
       }
}

/************************************************************************/
/* send_key								*/
/*									*/
/* Do a q_key() call for the passed keycode.				*/
/************************************************************************/

send_key(code)
int code;			      /* key code to be passed */
{
       int status;		      /* status returned by q_key */
       char line[10];		      /* display line */

       status=q_key(code);

/* verify q_key was ok */

       if ((status != 0) && (status != 2))  {
	       printf("	Error on q_key call, key=%x, err=%d",code,errno);
	       abort();
       }

/* display code sent */

       sprintf(line,"%2.2X",code);
       sput_vdu(line,24,60,YELLOW,NORMAL);
       return;
}

/************************************************************************/
/* send_string								*/
/*									*/
/* Do a q_string() call for the string pointed to by passed parameter.	*/
/************************************************************************/

send_string(s)
char *s;			       /* string to be passewd */
{
       int status;		       /* status returned by q_string */

       if (status = q_string(s))  {

/* error on q_string call */

	       printf("	Error on q_string call,	str=%s,	stroff=%d, err=%d",s,
		      status,errno);
	       abort();
       }
       return;
}

/************************************************************************/
/* vid_on								*/
/*									*/
/* Enable video to user							*/
/************************************************************************/

vid_on()
{

/* open mcp, enable video to v3279 */

       if (open_mcp(0x20000000,0))  {
	       printf("	Err on open_mcp	call, errno=%d",errno);
	       abort();
       }
}

/************************************************************************/
/* vid_off								*/
/*									*/
/* Disable video to user.						*/
/************************************************************************/

vid_off()
{

/* open mcp, disable video to v3279 */

       if (open_mcp(0x00000000,0))  {
	       printf("	Err on open_mcp	call, errno=%d",errno);
	       abort();
       }
}

/************************************************************************/
/* leave								*/
/*									*/
/* Print some stats for user to see momentarily and leave.		*/
/************************************************************************/

leave()
{
       int elaps;		       /* time for transfer */
       char line[40];		       /* build display */

       sput_vdu("                   ",24,60,TURQOS,NORMAL);
       vid_on();
       time(&end_time);
       elaps = end_time	- start_time;

/* display stats */

       sprintf(line,"Transfer complete,   elapsed seconds= %d",elaps);
       sput_vdu(line,3,10,TURQOS,NORMAL);
       sprintf(line,"                   bytes transferred= %d",bytes);
       sput_vdu(line,4,10,TURQOS,NORMAL);
       sprintf(line,"                   lines written    = %d",lines);
       sput_vdu(line,5,10,TURQOS,NORMAL);
       sprintf(line,"                   total bytes      = %d",bytes+lines);
       sput_vdu(line,6,10,TURQOS,NORMAL);
       sput_vdu("control will be transfered to v3279",7,10,TURQOS,NORMAL);
       fclose(fp);

/* let the caller read them */

       sleep(10);
       exit(0);
}

/************************************************************************/
/* abort								*/
/*									*/
/* Something bad happened.						*/
/************************************************************************/

abort()
{

/* close file and terminate v3279 */

       fclose(fp);
       sleep(10);
       push_key(QUIT);
       exit(1);
}
