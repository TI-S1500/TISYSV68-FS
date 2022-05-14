/*
   COPYRIGHT (c) 1986 TEXAS INSTRUMENTS, INCORPORATED.  ALL RIGHTS RESERVED.
*/
/*
static char *sccs_id = @(#)prmode.h	1.2 88/02/29";
*/

/* print various r,w,x permissions */

/*		this file requires the  <sys/stat.h>  header  <------
				and the <sys/inode.h> header  <------     */
prmode(aflag,xflag)
short  aflag,xflag ;
{
/* these arrays are declared static to allow initializations */
static int
	m0[] = { 1,   S_IREAD     ,  'r', '-' },  /*  owner permissions  */
	m1[] = { 1,   S_IWRITE    ,  'w', '-' },
	m2[] = { 3,   S_ISUID
		     |S_IEXEC     ,  's',
		      S_IEXEC     ,  'x',
		      S_ISUID     ,  'S', '-' },
	m3[] = { 1,   S_IREAD >>3 ,  'r', '-' },  /*  group permissions  */
	m4[] = { 1,   S_IWRITE>>3 ,  'w', '-' },
	m5[] = { 3,   S_ISGID
		     |S_IEXEC >>3 ,  's',
		      S_IEXEC >>3 ,  'x',
		      S_ISGID     ,  'l', '-' },
	m6[] = { 1,   S_IREAD >>6 ,  'r', '-' },  /*  other's permissions  */
	m7[] = { 1,   S_IWRITE>>6 ,  'w', '-' },
	m8[] = { 3,   S_ISVTX
		     |S_IEXEC >>6 ,  't',
		      S_IEXEC >>6 ,  'x',
		      S_ISVTX     ,  'T', '-'},

	*m[] = { m0, m1, m2, m3, m4, m5, m6, m7, m8};

register int **mp;

for (mp = &m[0]; mp < &m[sizeof(m)/sizeof(m[0])];) select(*mp++,aflag);
if( xflag&IFORCED ) putchar ('f');
  else		    putchar (' ');
}

select(pairp,aflag)			/*  only call is from pmode   */
register int *pairp, aflag;
{
register int n;

	n = *pairp++;
	while (n-->0) {
		if((aflag & *pairp) == *pairp) { pairp++; break; }
		 else			       { pairp += 2; }
	}
	putchar(*pairp);
}
