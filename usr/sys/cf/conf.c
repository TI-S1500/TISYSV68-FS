/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1987.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

static char sccsid[] = "@(#)conf.c	1.104  (TI)  90/11/16";

#include	"sys/param.h"
/*********************************************************************
*
*    T I   S Y S T E M   V   C O N F I G U R A T I O N   N O T E S
*
*    TI System V configuration and system tuning is accomplished
*    using the cband(1T) utility.  Most parameters that were
*    found in this file in previous releases have been removed.
*    The following table shows the correspondence between the
*    old parameters found here and the prompts that have replaced them.
*    Each of the parameters are documented in Appendix C of the 
*    Administrator's Guide.
*
*
*          Parameter             	Old Name
*
*         Process table size:    	NPROC		
*         Text table size:       	NTEXT	
*         Open file table size:  	NFILE	
*         Inode table size:      	NINODE	
*         Callout table size:    	NCALL	
*         Mount table size:      	NMOUNT	
*         File buffer pool size: 	NBUF	
*         Swap buffer pool size: 	NSWBUF	
*         Raw IO header pool size:     	NPBUF	
*         Hash buffer pool size: 	NHBUF	
*	  Swap map size: 		SMAPSIZ                
*	  Kernel virtual map size: 	KMAPSIZ
*	  Record lock limit: 		FLCKREC        
*	  File lock limit: 		FKCKFIL             
*	  Comm packet pool size: 	BN_MAXQUE        
*	  Shm attach per process limit: SHMSEG
*	  Shm attach system limit: 	(none)
*	  Shm segment count limit:      SHMMNI        
*	  Shm page count limit: 	SHMALL         
*	  Shm break value: 		SHMBRK            
*	  Message segment size: 	MSGSSZ           
*	  Number of message segments:   MSGSEG 
*	  Number of message queues:     MSGMNI        
*	  Message queue size limit:     MSGMNB    
*	  Maximum number of messages:   MSGTQL    
*	  Maximum message size: 	MSGMAX       
*	  Number of semaphore sets:     SEMMNI      
*	  Maximum semaphores per set:   SEMMSL
*	  Number of semaphores: 	SEMMNS
*	  Max semaphore ops per call:   SEMOPM
*	  Max semaphore undos: 		SEMMNU
*	  Max undos per process: 	SEMUME
*	  Sdma segment count limit: 	SDMAMNI
*	  Sdma attach limit: 		SDMASEG
*	  File size limit: 		FSLIMIT
*	  Maximum processes per user:   MAXUP
*	  Time slice size: 		LTICKS
*	  Load balancing interval:      BAL_TIM
*	  Load balancing mem minimum:   MIN_BAL_MEM
*	  TTY mapout table size:        (none)
*	  Number of TTY mapout tables:  (none)
*	  Number of mapout devices: 	(none)
*
*
*    Previous releases of TI System V included the following configurable 
*    parameters.  These parameters are no longer included, instead their 
*    values are now automatically configured.  The purpose of the parameter 
*    is described as well as the automatic configuration strategy.
*    
*    BN_LWINDOW 
*    	This parameter determined the number of page tables for exclusive 
*    	use of the busnet software.  This parameter is always a 
*    	constant value of 30.
*    
*    BN_MAXLELE
*    	This parameter determined the number of comm packets available 
*    	for exclusive use by each processor in the system.  Its value
*    	is automatically configured to allow half of the comm packet pool to
*    	be divided equally among all CPUs in the system for their exclusive
*    	use.  The remaining comm packets are part of a global pool
*    	and are allocated on an "as needed" basis.
*    SDMA
*    	This parameter when set to 0 disabled SDMA software.  SDMA software
*    	is currently disabled by setting the value of either of the following
*    	prompts to zero.  A non-zero value for both prompts will enable the
*    	SDMA feature.
*    	  Sdma segment count limit:
*    	  Sdma attach limit: 
*    
*    MESG
*    	This parameter when set to 0 disabled IPC message software.  
*    	IPC message software is currently disabled by setting the value of 
*    	any of the following prompts to zero.  A non-zero value for all 
*    	of the following prompts will enable the IPC message software.
*    	  Message segment size: 	
*    	  Number of message segments:  
*    	  Number of message queues:   
*    	  Message queue size limit:  
*    	  Maximum number of messages:
*    	  Maximum message size: 
*    
*    MSGMAP
*    	This parameter determined the size of the map structure used to
*    	control allocation of message segments.  This parameter is automatically
*    	configured to an appropriate value relative to the value of the
*    	Number of message segments parameter.
*    
*    SEMA
*    	This parameter when set to 0 disabled IPC semaphore software.  
*    	IPC semaphore software is currently disabled by setting the value of 
*    	any of the following prompts to zero.  A non-zero value for all 
*    	of the following prompts will enable the IPC semaphore software.
*    	  Number of semaphore sets:     
*    	  Maximum semaphores per set:  
*    	  Number of semaphores: 	
*    	  Max semaphore ops per call:  
*    	  Max semaphore undos: 	
*    	  Max undos per process:
*    
*    SEMMAP
*    	This parameter determined the size of the map structure used to
*    	control allocation of semaphores.  This parameter is automatically
*    	configured to an appropriate value relative to the value of the
*    	Number of semaphores parameter.
*    
*    SEMVMX
*    	This parameter determined the maximum value of any semaphore.  It
*    	is automatically set to be 32767.
*    
*    SEMAEM
*    	This parameter determined the maximum value allowed for an "adjust
*    	on exit" operation.  It is automatically set to be 16384.
*    
*    SHMEM
*    	This parameter when set to 0 disabled IPC shared memory software.  
*    	It is no longer possible to disable IPC shared memory software
*    	because shared memory is required for certain standard software
*    	features included with TI System V.
*    
*    SHMMIN 
*    	This parameter determined the minimum size of any shared memory 
*    	segment.  This parameter is automatically set to 1.
*        
*    SHMMAX
*    	This parameter determined the maximum size of any shared memory
*    	segment.  This parameter is automatically set to the same as
*    	the amount of memory the user specifies for the total number of
*    	pages that can be used for shared memory, since there is no
*	reason to artificially restrict the size of a segment.
*    
*    SDMAMAX
*    	This parameter determined the maximum size of any sdma segment.
*    	This parameter is automatically set to 100K less than the 
*    	amount of available user memory local to the CPU with the 
*    	least amount of available user memory.
*    
*    SDMAMIN
*    	This parameter determined the minimum size of any sdma segment.
*    	This parameter is automatically set to 1.
*    
*    SDMAALL
*    	This parameter determined the maximum number of sdma pages
*    	allowed in the system.  This parameter is automatically
*    	set to be half of all available user memory in the system.
*    
*    
************************************************************************/

/* Virtual Memory Parameters */
#define VM_LOTSFREE	0	/* when Pageout should quit       */
#define VM_DESFREE	0	/* when Pageout should be started */
#define VM_MINFREE	0	/* when Swapper should be started */

/* NOTE:  The above three parameters will be changed by the system (if needed)*/
/*        according to the following formulas to ensure reasonable 	      */
/* 	  values:							      */
/*	MEMSIZ 	 = number of pages of user memory in the cpu		      */
/*	lotsfree = max( min( max( <your value>, MEMSIZ/16),MEMSIZ/4),200);    */
/*	desfree  = max( min( max( <your value>, lotsfree/4), lotsfree/2,136); */
/*	minfree  = max( min( max( <your value>, desfree/4), desfree/2),104);   */
#define	NCLIST	50
/*
*  The following parameters should not be changed
*/
#define	NBSEGCOUNT	8
#define	PRF_0	1
#define	TRACE_0	1

/* More load balancing parameters */

#define LOAD_MAX_PCT 88
#define IDLE_DIFF_PCT 20
#define SELECT0_PCT 75
#define SNAPIDLE_DEC 5
#define MIGR_ALLOWED 1
#define	NEWP_RR 0

/* Load Balancing cpu-boundedness parameters	*/
#define CPUB_TIME 2500000	/* (250 milleseconds) */
#define	CPUB_DIV 52104 		/* (CPUB_DIV+1000)/(PX+1) <where PX=47> */
/* Above number needn't be exact.  Just so CPUB_TIME/CPUB_DIV approx = PX */
#define	CPUB_LVL 33		/* approx 500,000 instructions */

#include	"sys/types.h"
#include	"sys/sysmacros.h"
#include	"sys/space.h"
#include	"sys/conf.h"
#include	"sys/sema.h"

#include	"sys/errno.h"

#define	NULLSEMA	((csema_t *) 0)

extern nodev(), nulldev();
extern struct inode *nodevi();
extern int *nodevf();
extern s5init(), s5iput(), s5iupdat(), s5readi(), s5writei(), s5allocmap();
extern s5itrunc(), s5statf(), s5namei(), s5mount(), s5umount(),*s5freemap();
extern s5openi(), s5closei(), s5update(), s5statfs(), s5access(), s5getdents();
extern s5setattr(), s5notify(), s5fcntl(), s5ioctl(), s5readmap();
extern nfsinit(), nfsiput(), nfsiupdat(), nfsreadi();
extern nfswritei(), nfsitrunc(), nfsstatf(), nfsnamei(), nfsmount(); 
extern nfsumount(), nfsopeni(), nfsclosei(), nfsupdate();
extern nfsstatfs(), nfsaccess(), nfsgetdents(), nfssetattr(), nfsnotify();
extern  nfsfcntl(), nfsioctl(), nfsreadmap(), nfsallocmap(), *nfsfreemap();

extern struct inode *s5getinode();
extern struct inode *nfs_iget();
extern struct inode *s5iread();
extern struct inode *nfsiread();
extern tirdwropen(), tirdwrclose();
extern clnopen();
extern logopen(), logclose();

extern ipopen(), ipclose(); 
extern icmpopen(),icmpclose(); 
extern ripopen(), ripclose(); 
extern lo_open(), lo_close();
extern tcpopen(), tcpclose();
extern arpopen(), arpclose();
extern udpopen(), udpclose();
extern sockopen(), sockclose(), sockioctl(), sockread(), sockwrite();
extern strnopen(), strnclose();

extern struct streamtab loginfo;
extern struct streamtab clninfo;
extern struct streamtab timinfo;
extern struct streamtab trwinfo;
extern struct streamtab appinfo;

extern struct streamtab ipinfo;		
extern struct streamtab icmpinfo;	
extern struct streamtab ripinfo;	
extern struct streamtab lo_info;
extern struct streamtab tcpinfo;
extern struct streamtab arpinfo;
extern struct streamtab udpinfo;
extern struct streamtab strninfo;
extern struct streamtab slinfo;

extern struct streamtab ptminfo;
extern struct streamtab pteminfo;
extern struct streamtab ptsinfo;
extern struct streamtab ldtrinfo;

extern ropen(),  rclose(),  rstrategy(),  rprint();
extern npopen(), npclose(), npstrategy(), npprint();
extern ntopen(), ntclose(), ntstrategy(), ntprint();
extern nmtopen(), nmtclose(), nmtstrategy(), nmtprint();
extern mscopen(), mmcclose(), mscstrategy(), mscprint();
extern mqtopen(), mqtclose(), mqtstrategy(), mqtprint();
extern mtopen(), mtclose(), mtstrategy(), mtprint();
extern mvbopen(), mvbclose(), mvstrategy();
extern ttrstrt(),tttimeo();
extern rdopen(), rdclose(), rdstrategy(), rdprint();
extern nfsdopen(), nfsdclose(), nfsdstrategy(), nfsdprint(), nfsdioctl();
extern lckdinit(), lckdopen(), lckdclose(), lckdioctl();
extern pwopen(), pwclose(), pwioctl(), pw_timeout();

extern x250open(),  x250close(),  x250read(),  x250write(),  x250ioctl();
extern x251open(),  x251close(),  x251read(),  x251write(),  x251ioctl();
extern klopen(),    klclose(),    klread(),    klwrite(),    klioctl();
extern npopen(),    npclose(),    npread(),    npwrite(),    npioctl();
extern ntopen(),    ntclose(),    ntread(),    ntwrite(),    ntioctl();
extern nmtopen(),   nmtclose(),   nmtread(),   nmtwrite(),   nmtioctl();
extern mscopen(),   mscclose(),   mscread(),   mscwrite(),   mscioctl();
extern mqtopen(),   mqtclose(),   mqtread(),   mqtwrite(),   mqtioctl();
extern mvropen(),   mvrclose(),   mvread(),    mvwrite(),    mvioctl();
extern mtopen(),    mtclose(),    mtread(),    mtwrite(),    mtioctl();
extern syopen(),                  syread(),    sywrite(),    syioctl();
extern                            mmread(),    mmwrite();    mmioctl();

extern cacuopen(),  cacuclose(),  cacuread(),  cacuwrite(),  cacuioctl();
extern snaopen(),   snaclose(),   snaread(),   snawrite(),   snaioctl();
extern cttyopen(),  cttyclose(),  cttyread(),  cttywrite(),  cttyioctl();
extern inetopen(),  inetclose(),  inetread(),  inetwrite(),  inetioctl();
extern lapdopen(),  lapdclose(),  lapddread(),  lapdwrite(),  lapdioctl();
extern L0open(),    L0close(),    L0read(),    L0write(),    L0ioctl();
extern iopopen(),   iopclose(),   iopread(),   iopwrite(),   iopioctl();
extern sppopen(),   sppclose(),   sppread(),   sppwrite(),   sppioctl();
extern xportopen(), xportclose(), xportread(), xportwrite(), xportioctl();
extern cdnldopen(), cdnldclose(), cdnldread(), cdnldwrite(), cdnldioctl();
extern cbscopen(),  cbscclose(),  cbscread(),  cbscwrite(),  cbscioctl();
extern cbsctopen(), cbsctclose(), cbsctread(), cbsctwrite(), cbsctioctl();
extern clogopen(),  clogclose(),  clogread(),  clogwrite(),  clogioctl();
extern clpopen(),   clpclose(),   clpread(),   clpwrite(),   clpioctl();
extern cspareopen(), cspareclose(), cspareread(), csparewrite(), cspareioctl();
extern spaopen(),  spaclose(), spaioctl();
extern prfread(),  prfwrite(), prfioctl();

extern dpopen(),    dpclose(),    dpread(),    dpwrite(),    dpioctl();
extern physopen(),  physclose(),  physioctl();
extern bootopen(),					     bootioctl();
extern erropen(),   errclose(),   errread(),   errwrite();
extern tmropen(),   tmrclose(),   tmrread();
extern	hotopen(),	hotclose(),		hotwrite(),	hotioctl();
extern rtcioctl();
extern sdmaopen(), sdmaioctl();
extern cdialopen(), cdialclose(), cdialread(), cdialwrite(), cdialioctl();
extern bnopen(), bnclose(), bnread(), bnwrite(), bnioctl();
extern trnsprtopen(),trnsprtclose(),trnsprtread(),trnsprtwrite(),
	trnsprtioctl();
extern dnopen(),dnclose(),dnread(),dnwrite(),dnioctl();
extern cbscmopen(), cbscmclose(), cbscmread(), cbscmwrite(), cbscmioctl();
extern rdopen(),    rdclose(),     rdioctl();

extern vtyopen(),vtyclose(),vtyread(),vtywrite(),vtyioctl();
extern upsopen(),upsclose(),upsread(),upswrite(),upsioctl();
extern ttypopen(),ttypclose(),ttypread(),ttypwrite(),ttypioctl();
extern vpbopen(),vpbclose(),vpbread(),vpbwrite(),vpbioctl();

extern slsopen(), slsclose();

extern ptmopen(), ptmclose(), ptsopen(), ptsclose();
extern ldraw_timeout();
extern seltimein();
extern unselect();

extern mscinfo(), npinfo(), np2info();

extern strtime(), str2time(), str3time();
/* OPCTL */
extern opcopen(), opcioctl();
extern opcopen(), opcioctl();
extern strn_timeout();
extern strn_polling();
extern strn_ctl();
extern   ip_slowtimo();
extern   lingertimer();
extern  polltime();
extern  skewer();
extern  tcp_calldeq();
extern  tcp_fasttimo();
extern  tcp_slowtimo();
extern  arptimer();
extern  sl_timeout();
extern kclt_rcvudata();
extern klm_wait();
extern  lckdopen();
extern  lckdioctl();

drivlck_t item_sema = { 0,1};	/* initially unlocked. Used for q_link    */
csema_t str_sema = { 0,1};	/* initially unlocked. Used for streams.  */
csema_t lockd_sema = {0,1};     /* nfs lockd semaphore.  Initially unlocked. */

struct tdevsw tdevsw[] =
{
/*0*/	strtime,  &str_sema,
/*1*/	str2time, &str_sema,
/*2*/	str3time, &str_sema,
/*3*/	qenable,  &str_sema,
/*4*/	ttrstrt,  &str_sema,
/*5*/	tttimeo,  &str_sema,
/*6*/   strn_timeout, &str_sema,
/*7*/   strn_polling, &str_sema,
/*8*/   strn_ctl, &str_sema,
/*9*/   ip_slowtimo, &str_sema,
/*10*/  tcp_slowtimo, &str_sema,
/*11*/  polltime, &str_sema,
/*12*/  skewer, &str_sema,
/*13*/  tcp_calldeq, &str_sema,
/*14*/  tcp_fasttimo, &str_sema,
/*15*/  arptimer, &str_sema,
/*16*/  sl_timeout, &str_sema,
/*17*/  kclt_rcvudata, &str_sema,
/*18*/  klm_wait, &lockd_sema,
/*19*/  lckdopen, &lockd_sema,
/*20*/  lckdioctl, &lockd_sema,
/*21*/  pw_timeout, &str_sema,
/*22*/  ldraw_timeout, &str_sema,
/*23*/  seltimein, &str_sema,
/*24*/  unselect, &str_sema,
};


struct fmodsw fmodsw[] =
{
  "LOG"  , &loginfo,
  "CLONE" ,&loginfo,
  "timod", &timinfo,
  "tirdwr",&trwinfo,
  "arpproc", &appinfo,
  "ptem", &pteminfo,
  "ldterm", &ldtrinfo,
};

/* IMPORTANT - Please reserve bdevsw major numbers 3,4,5 for msc disk,1/4"
	tapes, and 1/2"tapes as stbm already assumes this  */

struct bdevsw bdevsw[] =
{
/* mjr	open,     close,     strategy,     print */

/* 0*/	ropen,    rclose,    rstrategy,    rprint,    NULLSEMA, 0, NOID,
/* 1*/	npopen,   npclose,   npstrategy,   npprint,   NULLSEMA, 1, NPID,
/* 2*/	ntopen,   ntclose,   ntstrategy,   ntprint,   NULLSEMA, 0, NTID,
/* 3*/	mscopen,  mscclose,  mscstrategy,  mscprint,  NULLSEMA, 1, MSCDID,
/* 4*/	mqtopen,  mqtclose,  mqtstrategy,  mqtprint,  NULLSEMA, 0, MSCQID,
/* 5*/	mtopen,   mtclose,   mtstrategy,   mtprint,   NULLSEMA, 0, MSCMID,
/* 6*/	nmtopen,  nmtclose,  nmtstrategy,  nodev,     NULLSEMA, 0, NMID,
/* 7*/	mvbopen,  mvbclose,  mvstrategy,   nodev,     NULLSEMA, 1, MVID,
/* 8*/	nulldev,  nulldev,   nodev,   	   nodev,     NULLSEMA, 0, NOID,
/* 9*/	rdopen,   rdclose,   rdstrategy,   rdprint,   NULLSEMA, 0, NOID,
/* 10*/	nfsdopen, nfsdclose, nfsdstrategy, nfsdprint, NULLSEMA, 0, NOID,
/* 11*/	lckdopen, lckdclose, nodev, nodev, NULLSEMA, 0, NOID,
};

struct cdevsw cdevsw[] =
{
/* mjr	open,		close,		read,		write,		ioctl,     	tty structure	sema		socket		major_id */

/* 0*/	klopen,	klclose,klread,	klwrite,klioctl,0,NULLSEMA,0,NOID,0,
/* 1*/	npopen,	npclose,npread,	npwrite,npioctl,0,NULLSEMA,1,NPID,0,
/* 2*/	ntopen,	ntclose,ntread,	ntwrite,ntioctl,0,NULLSEMA,0,NTID,0,
/* 3*/	syopen,	nulldev,syread,	sywrite,syioctl,0,NULLSEMA,0,NOID,0,
/* 4*/	nulldev,nulldev,mmread,	mmwrite,mmioctl,0,NULLSEMA,0,NOID,0,
/* 5*/	cttyopen,cttyclose,cttyread,cttywrite,cttyioctl,0,NULLSEMA,0,CTTYID,0,
/* 6*/	nodev,	nodev,	nodev,	nodev,	nodev,0,NULLSEMA,0,NOID,0,
/* 7*/	cacuopen,cacuclose,cacuread,cacuwrite,cacuioctl,0,NULLSEMA,0,CACUID,0,
/* 8*/	cdnldopen,cdnldclose,cdnldread,cdnldwrite,cdnldioctl,
	0,NULLSEMA,0,CDNLDID,0,
/* 9*/	cbscopen,cbscclose,cbscread,cbscwrite,cbscioctl,0,NULLSEMA,0,CBSCID,0,
/*10*/	cbsctopen,cbsctclose,cbsctread,cbsctwrite,cbsctioctl,
	0,NULLSEMA,0,CBSCTID,0,
/*11*/	clogopen,clogclose,clogread,clogwrite,clogioctl,0,NULLSEMA,0,CLOGID,0,
/*12*/	dpopen,	dpclose,dpread,	dpwrite,dpioctl,0,&str_sema,0,NOID,0,
/*13*/	physopen,physclose,nodev,nodev,	physioctl,0,NULLSEMA,0,NOID,0,
/*14*/	bootopen,nodev,	nodev,nodev,bootioctl,0,NULLSEMA,0,NOID,0,
/*15*/	inetopen,inetclose,inetread,inetwrite,inetioctl,0,NULLSEMA,0,INETID,0,
/*16*/  erropen,errclose,errread,errwrite,nodev,0,NULLSEMA,0,NOID,0,
/*17*/	tmropen,tmrclose,tmrread,nodev,	nodev,0,NULLSEMA,0,NOID,0,
/*18*/	L0open,	L0close,L0read,	L0write,L0ioctl,0,NULLSEMA,0,L0ID,0,
/*19*/	iopopen,iopclose,iopread,iopwrite,iopioctl,0,NULLSEMA,0,IOPID,0,
/*20*/	sppopen,sppclose,sppread,sppwrite,sppioctl,0,NULLSEMA,0,SPPID,0,
/*21*/xportopen,xportclose,xportread,xportwrite,xportioctl,0,NULLSEMA,0,NOID,0,
/*22*/ hotopen,hotclose,nodev,hotwrite,hotioctl,0,NULLSEMA,0,NOID,0,
/*23*/	spaopen,spaclose,nodev,	nodev,	spaioctl, 0,NULLSEMA,0,NOID,0,
/*24*/	snaopen,snaclose,snaread,snawrite,snaioctl,0,NULLSEMA,0,SNAID,0,
/*25*/	mscopen,mscclose,mscread,mscwrite,mscioctl,0,NULLSEMA,1,MSCDID,0,
/*26*/	mqtopen,mqtclose,mqtread,mqtwrite,mqtioctl,0,NULLSEMA,0,MSCQID,0,
/*27*/	mtopen,	 mtclose,mtread,mtwrite,mtioctl,0,NULLSEMA,0,MSCMID,0,
/*28*/	nulldev,nulldev,nulldev,nulldev,rtcioctl,0,NULLSEMA,0,NOID,0,
/*29*/	sdmaopen,nulldev,nodev,	nodev,	sdmaioctl,0,NULLSEMA,0,NOID,0,
/*30*/	clpopen,clpclose,clpread,clpwrite,clpioctl,0,NULLSEMA,0,CLPID,0,
/*31*/  nulldev,nulldev,prfread,prfwrite,prfioctl, 0,NULLSEMA,0,NOID,0,
/*32*/ cdialopen,cdialclose,cdialread,cdialwrite,cdialioctl,0,
	NULLSEMA,0,CDIALID,0,
/*33*/ cspareopen,cspareclose,cspareread,csparewrite,cspareioctl,
	0,NULLSEMA,0,NOID,0,
/*34*/ nmtopen,	nmtclose,nmtread,nmtwrite,nmtioctl,0,NULLSEMA,0,NMID,0,
/*35*/cbscmopen,cbscmclose,cbscmread,cbscmwrite,cbscmioctl,0,NULLSEMA,0,NOID,0,
/*36*/ opcopen,	nulldev,nodev,	nodev,	opcioctl,0,NULLSEMA,0,NOID,0,
/*37*/ mvropen,	mvrclose,mvread,mvwrite,mvioctl,0,NULLSEMA,1,MVID,0,
/*38*/ nulldev,	nulldev,nodev,	nodev,	nulldev,0,NULLSEMA,0,NOID,0,
/*39*/ nulldev,	nulldev,nodev,	nodev,	nulldev,0,NULLSEMA,0,NOID,0,
/*40*/ nulldev,	nulldev,nodev,	nodev,	nulldev,0,NULLSEMA,0,NOID,0,
/*41*/ nulldev,	nulldev,nodev,	nodev,	nulldev,0,NULLSEMA,0,NOID,0,
/*42*/ nulldev,	nulldev,nodev,	nodev,	nulldev,0,NULLSEMA,0,NOID,0,
/*43*/ nulldev,	nulldev,nodev,	nodev,	nulldev,0,NULLSEMA,0,NOID,0,
/*44*/ bnopen,	bnclose,bnread,	bnwrite,bnioctl,0,NULLSEMA,1,NOID,0,
/*45*/ trnsprtopen,trnsprtclose,trnsprtread,trnsprtwrite,trnsprtioctl,
	0,NULLSEMA,1,XPTID,0,
/*46*/ dnopen,	dnclose,dnread,	dnwrite,dnioctl,0,NULLSEMA,0,VT990ID,0,
/*47*/ x250open,x250close,x250read,x250write,x250ioctl,0,NULLSEMA,1,X250ID,0,
/*48*/ x251open,x251close,x251read,x251write,x251ioctl, 0,NULLSEMA,1,NOID,0,
/*49*/ rdopen,	rdclose,nodev,	nodev,	rdioctl,0,NULLSEMA,0,NOID,0,
/*50*/ lapdopen,lapdclose,lapddread,lapdwrite,lapdioctl,0,NULLSEMA,0,LAPDID,0,
/*51*/ nulldev,nulldev,nodev,nodev,nulldev,0,NULLSEMA,0,NOID,0,
/*52*/ nulldev,nulldev,nodev,nodev,nulldev,0,NULLSEMA,0,NOID,0,
/*53*/ logopen,logclose,nodev,nodev,nodev,0,&str_sema,0,NOID,&loginfo,
/*54*/ clnopen,nodev,nodev,nodev,nodev,0,&str_sema,0,NOID,&clninfo,
/*55*/ ipopen,ipclose,nodev,nodev,nodev,0,&str_sema,0,NOID,&ipinfo,
/*56*/ icmpopen,icmpclose,nodev,nodev,nodev,0,&str_sema,0,NOID,&icmpinfo,
/*57*/ lo_open,lo_close,nodev,nodev,nodev,0,&str_sema,0,NOID,&lo_info,
/*58*/ ripopen,ripclose,nodev,nodev,nodev,0,&str_sema,0,NOID,&ripinfo,
/*59*/ tcpopen,tcpclose,nodev,nodev,nodev,0,&str_sema,0,NOID,&tcpinfo,
/*60*/ arpopen,arpclose,nodev,nodev,nodev,0,&str_sema,0,NOID,&arpinfo,
/*61*/ udpopen,udpclose,nodev,nodev,nodev,0,&str_sema,0,NOID,&udpinfo,
/* Do we need an ID for the socket device ? */
/*62*/ sockopen,sockclose,sockread,sockwrite,sockioctl,0,&str_sema,0,NOID,0,
/*63*/ ttypopen,ttypclose,ttypread,ttypwrite,ttypioctl,0,&str_sema,0,NOID,0,
/*64*/ vtyopen,vtyclose,vtyread,vtywrite,vtyioctl,0,&str_sema,0,NOID,0,
/*65*/ slsopen,slsclose,nodev,nodev,nodev,0,&str_sema,0,NOID,&slinfo,
/*66*/ strnopen,strnclose,nodev,nodev,nodev,0,&str_sema,0,NOID,&strninfo,
/*67*/ nfsdopen,nfsdclose,nodev,nodev,nfsdioctl,0,NULLSEMA,0,NOID,0,
/*68*/ lckdopen,lckdclose,nodev,nodev,lckdioctl,0,NULLSEMA,0,NOID,0,
/*69*/ upsopen,upsclose,upsread,upswrite,upsioctl,0,NULLSEMA,0,NOID,0,
/*70*/ vpbopen,vpbclose,vpbread,vpbwrite,vpbioctl,0,NULLSEMA,0,NOID,0,
/*71*/ pwopen,pwclose,nodev,nodev,pwioctl,0,&str_sema,0,NOID,0,
/*72*/ ptmopen,ptmclose,nodev,nodev,nodev,0,&str_sema,0,NOID,&ptminfo,
/*73*/ ptsopen,ptsclose,nodev,nodev,nodev,0,&str_sema,0,NOID,&ptsinfo,
};

struct fstypsw fstypsw[] =
{
	{   /* entry 0 always has null pointers */
	nodev, nodev, nodevi, nodev, nodev, nodev, nodev, nodev, nodev, nodev,
	nodev, nodev, nodevi, nodev, nodev, nodev, nodev, nodev, nodev, nodev, 
	nodevf, nodev, nodev, nodev, nodev, nodev, nodev, nodev, nodev, nodev, 
	nodev, nodev },
	{   /* this is the system 5 entry */
	s5init, s5iput, s5iread, nodev, s5iupdat, s5readi, s5writei, 
	s5itrunc, s5statf, s5namei, s5mount, s5umount, s5getinode, 
	s5openi, s5closei, s5update, s5statfs, s5access, s5getdents, 
	s5allocmap, s5freemap, s5readmap, s5setattr, s5notify, s5fcntl, 
	nodev, s5ioctl, nodev, nodev, nodev, nodev, nodev },
	{   /* this is the nfs entry */
	nfsinit, nfsiput, nfsiread, nodev, nfsiupdat, nfsreadi, nfswritei,
	nfsitrunc, nfsstatf, nfsnamei, nfsmount, nfsumount, nfs_iget,
	nfsopeni, nfsclosei, nfsupdate, nfsstatfs, nfsaccess, nfsgetdents,
	nfsallocmap, nfsfreemap, nfsreadmap, nfssetattr, nfsnotify, nfsfcntl, 
	nodev, nfsioctl, nodev, nodev, nodev, nodev, nodev }
};

/* NFS installed identifiers - initialized to 0, but if NFS is installed, the
   NFS initialization code will change them. These are for the sysm68k system
   call.
*/
caddr_t	nfsdef = 0;
caddr_t nfsst = 0;

char s51kfs[8] = "S51K";
char nfsfs[8] = "NFS";

int nfs_rnum = 0;
struct rnode *nfs_rnodes = NULL;

struct fsinfo fsinfo[] =
{
/*0*/ {0, 0, 0, 0},
/*1*/ {0, 0, &s51kfs[0], 0},
/*2*/ { 1,                 /* FS_NOICACHE  dont cache inodes */
	0, &nfsfs[0], 
	4,                 /* NO_SEEK  notify on seeks        */
      }
};

extern bnserv(), knserv(), strnintr();
struct bfunc bustype[] = { 
/*0*/ bnserv, 
/*1*/ knserv,
/*2*/ strnintr,
};

int	bdevcnt = sizeof(bdevsw)/sizeof(struct bdevsw);
int	cdevcnt = sizeof(cdevsw)/sizeof(struct cdevsw);
int	nfstyp = sizeof(fstypsw)/sizeof(struct fstypsw);
int	tdevcnt = sizeof(tdevsw)/sizeof(struct tdevsw);
int	fmodcnt = sizeof(fmodsw)/sizeof(struct fmodsw);
int	bfuncnt = sizeof(bustype)/sizeof(struct bfunc);

dev_t	rootdev, pipedev, swapdev, dumpdev;
daddr_t	swplo = 1;
int	nswap;

extern int dpputc(), dpgetc(), dpisac(), dpinit(), initmap(), trnsprtinit();
extern int vpbinit();
int	console, contype, defcon;

/*
 * Console device switch
 */

struct	klsw	klsw[] =
{
	"dp",		makedev(12,0),		dpputc, dpgetc, dpisac, 0,
	"lxcon",	makedev(5,0x600000),	dpputc, dpgetc, dpisac, 0,
	0
};

struct	ident_dev multidevs[] =
{
	npinfo,
	mscinfo,
	np2info,
};
/* Using the slot number, find an index into multidevs that points to
** the function in the correct device driver that finds all the miscellaneous
** information that the multivolume file system driver needs. 
*/
getfunc(slot)
int slot;
{
	int	tmp = devmap.bd_type[slot];
	switch(tmp) {
		case NUPI_TYP : return(0);
		case MSC_TYP  : return(1);
		case NP2_TYP  :	return(2);
		default:	return(-1); /* Unknown board -- rtn err	*/
	}
}

/*
 * dev_init is used by main.  It is a null terminated list of
 * procedures to be called.
 */

int (*dev_init[])() = {
	dpinit,
	initmap,
	trnsprtinit,
	vpbinit,
	0
};

/* int	ubal_tim = BAL_TIM; */
/* int	umin_bal_mem = MIN_BAL_MEM; */
char	loadmax_pct = LOAD_MAX_PCT;
char	idlediff_pct = IDLE_DIFF_PCT;
char	select0_pct = SELECT0_PCT;
char	migr_allowed = MIGR_ALLOWED;
char	newp_rr = NEWP_RR;
char	snapidle_dec = SNAPIDLE_DEC;
short	unused54 = 54;	/* keep longword alignment */

int	cpub_time = CPUB_TIME;
int	cpub_div  = CPUB_DIV;
int	cpub_lvl  = CPUB_LVL;
