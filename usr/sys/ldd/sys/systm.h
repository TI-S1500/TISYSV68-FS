
/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1984.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

static char sccsid[] = "88/03/08 (TI) @(#)systm.h	1.1";

/* 88/03/08 */

union u_jmpvect {
	int	(*(*vi)[])();		
	char	*(*(*vp)[])();
	int	*(*vv)[];
};
typedef union u_jmpvect JMPVECT;
/************************************************************************/
/* function call codes (used in macros below)				*/
/************************************************************************/

#define V_INSTALL0	0
#define V_INSTALLSPI	1
#define V_INSTALLHW	2
#define V_REMOVE0	3
#define V_REMOVESPI	4
#define V_REMOVEHW	5
#define V_UNLOAD 	6
#define V_YIELD		7
#define V_DESCHED	8
#define V_SCHED		9
#define V_SLEEP		10
#define V_WAKEUP 	11
#define V_WAIT		12
#define V_POST		13
#define V_TIMEOUT	14
#define V_DELAY		15
#define V_QUEUE		16
#define V_QUEUEHEAD	17
#define V_DEQUEUE	18
#define V_BLDQUEUE	19
#define V_BUFWRITE	20
#define V_BUFREAD	21
#define V_BUFCLOSE	22
#define V_BUFOPEN	23
#define V_WREAD		24
#define V_WWRITE 	25
#define V_ALOMEM 	26
#define V_DALMEM  	27
#define V_INITHEAP	28
#define V_NEW		29
#define V_DISPOSE	30
#define V_GETWIND	31
#define V_RELWIND	32
#define V_ADDNAME	33
#define V_DELNAME	34
#define V_FINDNAME	35
#define V_REGDD		36
#define V_DREGDD	37
#define V_SIGNAL	38		
#define V_BCOPY 	39
#define V_GETSLOT	40
#define V_GETTICS	41
#define V_LOGMSG	42
#define V_CONSOLE	43
#define V_OPENLOG	44
#define V_SIGPRC0	45
#define V_SIGCMP0	46
#define V_SIGGET0	47
#define V_KILL_TIMO	48
#define V_QUEUEGROUP	49
#define V_OPENLOG2	50
#define V_LOGMSG2	51
#define V_PSIGNAL	52
#define V_PANIC		53
#define V_QTIMEOUT	54
#define V_INCELEM	55

/************************************************************************/
/* function declarations and macros (functions that return integers	*/
/* have macros but no explicit declarations)				*/
/************************************************************************/

#ifdef TERMCON
int installhw(),remove0(),removespi(),removehw(),unload(),yield(),desched(),
	sched(),sleep(),wakeup(),post(),timeout(),delay(),queue(),
	queuehead(),bldqueue(),bufwrite(),bufread(),bufclose(),bufopen(),
	wread(),wwrite(),dalmem(),initheap(),dispose(),getwind(),relwind(),
	addname(),delname(),dregdd(),signal(),bcopy(),logmsg(),console(),
	openlog(),sigprc0(),sigcmp0(),sigget0(),kill_timeout(),queuegroup(),
	openlog2(),logmsg2(),psignal(),panic(),qtimeout(),incelem();

#else

#define install0(i,e,p) ((addr) ((*(*execvect.vi)[V_INSTALL0])(i,e,p)))
#define installspi(l,p,e,i) ((addr) ((*(*execvect.vi)[V_INSTALLSPI])(l,p,e,i)))
#define installhw(v,l,e,p) ((int) ((*(*execvect.vi)[V_INSTALLHW])(v,l,e,p)))
#define remove0(p) ((int) ((*(*execvect.vi)[V_REMOVE0])(p)))
#define removespi(p) ((int) ((*(*execvect.vi)[V_REMOVESPI])(p)))
#define removehw(v) ((int) ((*(*execvect.vi)[V_REMOVEHW])(v)))
#define unload(p) ((*(*execvect.vi)[V_UNLOAD])(p))
#define yield() ((int) ((*(*execvect.vi)[V_YIELD])()))
#define desched() ((int) ((*(*execvect.vi)[V_DESCHED])()))
#define sched(p) ((int) ((*(*execvect.vi)[V_SCHED])(p)))
#define sleep(c,p) ((int) ((*(*execvect.vi)[V_SLEEP])(c,p)))
#define wakeup(c) ((*(*execvect.vi)[V_WAKEUP])(c))
#define wait(m,h) ((unsigned long) ((*(*execvect.vi)[V_WAIT])(m,h)))
#define post(p,e) ((int) ((*(*execvect.vi)[V_POST])(p,e)))
#define timeout(f,a,t) ((int) ((*(*execvect.vi)[V_TIMEOUT])(f,a,t)))
#define delay(t) ((int) ((*(*execvect.vi)[V_DELAY])(t)))
#define queue(a,i) ((int) ((*(*execvect.vi)[V_QUEUE])(a,i)))
#define queuehead(a,i) ((int) ((*(*execvect.vi)[V_QUEUEHEAD])(a,i)))
#define dequeue(a) ((struct ccbelem *) ((*(*execvect.vp)[V_DEQUEUE])(a)))
#define bldqueue (*(*execvect.vi)[V_BLDQUEUE])
#define bufwrite(b,f,t,n,p) ((int) ((*(*execvect.vi)[V_BUFWRITE])(b,f,t,n,p)))
#define bufread(b,f,t,n,p) ((int) ((*(*execvect.vi)[V_BUFREAD])(b,f,t,n,p)))
#define bufclose(b,p) ((*(*execvect.vi)[V_BUFCLOSE])(b,p))
#define bufopen(b,p) ((*(*execvect.vi)[V_BUFOPEN])(b,p))
#define wread(s,d,n) ((*(*execvect.vi)[V_WREAD])(s,d,n))
#define wwrite(s,d,n) ((*(*execvect.vi)[V_WWRITE])(s,d,n))
#define alomem(p,s,r) ((char *) ((*(*execvect.vp)[V_ALOMEM])(p,s,r)))
#define dalmem(i,p) ((int) ((*(*execvect.vi)[V_DALMEM])(i,p)))
#define initheap(p,s,l) ((int) ((*(*execvect.vi)[V_INITHEAP])(p,s,l)))
#define new(p,s) ((char *) ((*(*execvect.vp)[V_NEW])(p,s)))
#define dispose(i,p) ((int) ((*(*execvect.vi)[V_DISPOSE])(i,p)))
#define getwind(p,w,c,n) ((int) ((*(*execvect.vi)[V_GETWIND])(p,w,c,n)))
#define relwind(p,w) ((int) ((*(*execvect.vi)[V_RELWIND])(p,w)))
#define addname(n,v,p) ((int) ((*(*execvect.vi)[V_ADDNAME])(n,v,p)))
#define delname(n) ((int) ((*(*execvect.vi)[V_DELNAME])(n)))
#define findname(n) ((int *) ((*(*execvect.vp)[V_FINDNAME])(n)))
#define regdd(m,a,q,p) ((struct q_anchor *) \
     ((*(*execvect.vp)[V_REGDD])(m,a,q,p)))
#define dregdd(m,a,p) ((int) ((*(*execvect.vi)[V_DREGDD])(m,a,p)))
#define signal(p,s) ((int) ((*(*execvect.vi)[V_SIGNAL])(p,s)))
#define bcopy(s,d,n) ((*(*execvect.vi)[V_BCOPY])(s,d,n))
#define getslot() (*((short *)((*execvect.vv)[V_GETSLOT])))
#define gettics() (*((unsigned long *)((*execvect.vv)[V_GETTICS])))
#define logmsg (*(*execvect.vi)[V_LOGMSG])
#define console (*(*execvect.vi)[V_CONSOLE])
#define openlog (*(*execvect.vi)[V_OPENLOG])
#define sigprc0(p,c,s) ((int) ((*(*execvect.vi)[V_SIGPRC0])(p,c,s)))
#define sigcmp0(s) ((int) ((*(*execvect.vi)[V_SIGCMP0])(s)))
#define sigget0() ((int) ((*(*execvect.vi)[V_SIGGET0])()))
#define kill_timeout(t) ((int) ((*(*execvect.vi)[V_KILL_TIMO])(t)))
#define queuegroup(a,i) ((int) ((*(*execvect.vi)[V_QUEUEGROUP])(a,i)))
#define openlog2 (*(*execvect.vi)[V_OPENLOG2])
#define logmsg2 (*(*execvect.vi)[V_LOGMSG2])
#define psignal(i,g,p,s) ((int) ((*(*execvect.vi)[V_PSIGNAL])(i,g,p,s)))
#define panic(e) ((int) ((*(*execvect.vi)[V_PANIC])(e)))
#define qtimeout(f,a,t) ((int) ((*(*execvect.vi)[V_QTIMEOUT])(f,a,t)))
#define incelem(a) ((int) ((*(*execvect.vi)[V_INCELEM])(a)))
#endif
extern JMPVECT execvect;
extern int prog_id;
#define timeout(x,y,z) (qtimeout(x,y,z))
