
#
#	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
#	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
#	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
#	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
#	ASSOCIATED DOCUMENTATION.
#

#             @(#)locore.s	1.70 (TI) 92/02/28

# interesting offsets into the stack after the registers have been saved
# including the user's stack pointer!
set	SR,64
set	PC,66
set	VOROFF,70
set	SSW,74
set	SSW040,76
set	DCFA,80
set	FA040,84
# the supervisor bit in the status register (0x20 00)
set	SUPER,5
set	PS_SUP,0x2000
# the master bit in the status register
set	PS_MAS,0x1000
set	NPS_MAS,0xefff

#
	set	ACCTCTL, 0x01e8 # offset from PIC of acct timer ctl reg
	set	ACCTIMER, 0x03c0 # offset from PIC of acct timer data reg
	set	ACCTIMER30, 0x03b0 # acct timer data reg on 030 board
	set	B68020, 0	# Board type = 68020
	set	_020_CHIP, 0x2	# Chip type  = 68020
	set	_030_CHIP, 0x3	# Chip type  = 68030
	set	_040_CHIP, 0x4	# Chip type  = 68040
	set	NOT_NAN, 0xfeffffff #mask for turning off NAN in FPSR
#
# 68020 vector table
#

	text
	global	M68Kvec
M68Kvec:

# Vectors 0-63: Motorola defined vectors
	long	0		# 0	initial isp
	long	0		# 4	initial pc

busvec:	global	busvec
	long	busint		# 8	bus error

adrvec:	global	adrvec
	long	adrint		# c	address error

illvec:	global	illvec
	long	illint		# 10	illegal instruction

zdvec:	global	zdvec
	long	zdint		# 14	zero divide

chkvec:	global	chkvec
	long	chkint		# 18	chk, ck2

tvvec:	global	tvvec
	long	tvint		# 1c	trapcc, trapv

pvvec:	global	pvvec
	long	pvint		# 20	privledge violation

trcvec:	global	trcvec
	long	trcint		# 24	trace

Avec:	global	Avec
	long	Aint		# 28	A line exception

Fvec:	global	Fvec
	long	hfline		# 2c	F line exception

	long	ur_int		# 30	Unassigned, Reserved

cpvvec:	global	cpvvec
	long	cpvint		# 34	Coprocessor protocol violation

fmtvec:	global	fmtvec
	long	fmtint		# 38	Format error

uivec:	global	uivec
	long	uiint		# 3c	Unitialized interrupt

	long	ur_int		# 40	Unassigned, Reserved
	long	ur_int		# 44	Unassigned, Reserved
	long	ur_int		# 48	Unassigned, Reserved
	long	ur_int		# 4c	Unassigned, Reserved
	long	ur_int		# 50	Unassigned, Reserved
	long	ur_int		# 54	Unassigned, Reserved
	long	ur_int		# 58	Unassigned, Reserved
	long	ur_int		# 5c	Unassigned, Reserved

sivec:	global	sivec
	long	siint		# 60	Spurious interrupt

avvec:	global	avvec
	long	nullvect	# 64	Level 1 auto vector
	long	nullvect	# 68	Level 2 auto vector
	long	nullvect	# 6c	Level 3 auto vector
	long	nullvect	# 70	Level 4 auto vector
	long	nullvect	# 74	Level 5 auto vector
	long	nullvect	# 78	Level 6 auto vector
	long	nullvect	# 7c	Level 7 auto vector

tr0vec:	global	tr0vec
	long	trap0		# 80	trap 0, system call

tr1vec:	global	tr1vec
	long	trapn		# 84	trap 1
tr2vec:	global	tr2vec
	long	trapn		# 88	trap 2
tr3vec:	global	tr3vec
	long	trapn		# 8c	trap 3
tr4vec:	global	tr4vec
	long	trapn		# 90	trap 4
tr5vec:	global	tr5vec
	long	trap5		# 94	trap 5
tr6vec:	global	tr6vec
	long	trapn		# 98	trap 6
tr7vec:	global	tr7vec
	long	trapn		# 9c	trap 7
tr8vec:	global	tr8vec
	long	trapn		# a0	trap 8
tr9vec:	global	tr9vec
	long	trapn		# a4	trap 9
trAvec:	global	trAvec
	long	trapn		# a8	trap 10
trBvec:	global	trBvec
	long	trapn		# ac	trap 11
trCvec:	global	trCvec
	long	trapn		# b0	trap 12
trDvec:	global	trDvec
	long	trapn		# b4	trap 13
trEvec:	global	trEvec
	long	trapn		# b8	trap 14
trFvec:	global	trFvec
	long	trapn		# bc	trap 15

# Floating point coprocessor exceptions

fpuvec:	global	fpuvec
	long	hbsun		# c0	branch on set or unorder condition
	long	hinex		# c4	inexact result
	long	hdz		# c8	divide by zero
	long	hunfl		# cc	underflow
	long	hoperr		# d0	operand error
	long	hovfl		# d4	overflow
	long	hsnan		# d8	signaling NAN

	long	hunimp		# dc	Unassigned, Reserved

# Memory Management coprocessor exceptions

mmuvec:	global	mmuvec
	long	mmuint		# e0	configuration error
	long	mmuint		# e4	illegal operation
	long	mmuint		# e8	access level violation

	long	ur_int		# ec
	long	ur_int		# f0
	long	ur_int		# f4
	long	ur_int		# f8
	long	ur_int		# fc

# Vectors 64-255: User defined vectors (ie interrupts)

# Vectors 64-136: Unused

	long	nullvect	# 100
	long	nullvect	# 104
	long	nullvect	# 108
	long	nullvect	# 10c
	long	nullvect	# 110
	long	nullvect	# 114
	long	nullvect	# 118
	long	nullvect	# 11c
	long	nullvect	# 120
	long	nullvect	# 124
	long	nullvect	# 128
	long	nullvect	# 12c
	long	nullvect	# 130
	long	nullvect	# 134
	long	nullvect	# 138
	long	nullvect	# 13c
	long	nullvect	# 140
	long	nullvect	# 144
	long	nullvect	# 148
	long	nullvect	# 14c
	long	nullvect	# 150
	long	nullvect	# 154
	long	nullvect	# 158
	long	nullvect	# 15c
	long	nullvect	# 160
	long	nullvect	# 164
	long	nullvect	# 168
	long	nullvect	# 16c
	long	nullvect	# 170
	long	nullvect	# 174
	long	nullvect	# 178
	long	nullvect	# 17c
	long	nullvect	# 180
	long	nullvect	# 184
	long	nullvect	# 188
	long	nullvect	# 18c
	long	nullvect	# 190
	long	nullvect	# 194
	long	nullvect	# 198
	long	nullvect	# 19c
	long	nullvect	# 1a0
	long	nullvect	# 1a4
	long	nullvect	# 1a8
	long	nullvect	# 1ac
	long	nullvect	# 1b0
	long	nullvect	# 1b4
	long	nullvect	# 1b8
	long	nullvect	# 1bc
	long	nullvect	# 1c0
	long	nullvect	# 1c4
	long	nullvect	# 1c8
	long	nullvect	# 1cc
	long	nullvect	# 1d0
	long	nullvect	# 1d4
	long	nullvect	# 1d8
	long	nullvect	# 1dc
	long	nullvect	# 1e0
	long	nullvect	# 1e4
	long	nullvect	# 1e8
	long	nullvect	# 1ec
	long	nullvect	# 1f0
	long	nullvect	# 1f4
	long	nullvect	# 1f8
	long	nullvect	# 1fc
	long	nullvect	# 200
	long	nullvect	# 204
	long	nullvect	# 208
	long	nullvect	# 20c
	long	nullvect	# 210
	long	nullvect	# 214
	long	nullvect	# 218
	long	nullvect	# 21c
	long	nullvect	# 220

# Vectors 137-143, special ICC interrupts

irqvec:	global	irqvec
	long	irq1		# 224	Accounting timer
	long	irq2		# 228	Low battery on NVRAM - or MFP PIT
	long	irq3		# 22c	Over temperature
	long	irq4		# 230	Diagnostic port UART
	long	irq5		# 234	Powerfail
	long	clkint		# 238	PIT 
	long	irq6		# 23c	Diagnostic port nmi

# Priority level 1, vectors 144-159

level1:	global	level1
	global	fixsp
fixsp:	long	fixspi   	# 240   Special stack fixup routine
	global	toutvec
toutvec: long	touthndl	# 244
	long	nullvect	# 248
	long	nullvect	# 24c
	long	nullvect	# 250
	long	nullvect	# 254
	long	nullvect	# 258
	long	nullvect	# 25c
	long	nullvect	# 260
	long	nullvect	# 264
	long	nullvect	# 268
	long	nullvect	# 26c
	long	nullvect	# 270
	long	nullvect	# 274
	long	nullvect	# 278
	long	nullvect	# 27c

# Priority level 2, vectors 160-175

level2:	global	level2
vpbvec:	global	vpbvec
	long	vpbint		# 280
	long	vpbint		# 284
	long	vpbint		# 288
	long	vpbint		# 28c
	long	vpbint		# 290
	long	vpbint		# 294
	long	vpbint		# 298
	long	vpbint		# 29c
	long	nullvect	# 2a0
	long	nullvect	# 2a4
	long	nullvect	# 2a8
	long	nullvect	# 2ac
	long	nullvect	# 2b0
	long	nullvect	# 2b4
	long	nullvect	# 2b8
	long	nullvect	# 2bc

# Priority level 3, vectors 176-191

level3:	global	level3
dskvec:	global	dskvec
	long	dskint		# Disk interrupt
spvec:	global	spvec
	long	spint		# Special event interrupt
htvec:	global	htvec
	long	htint		# Half inch tape interrupt
qtvec:	global	qtvec
	long	qtint		# Quarter inch tape interrupt
	long	nullvect
	long	nullvect
	long	nullvect
	long	nullvect
	long	nullvect	
	long	nullvect
	long	nullvect
	long	nullvect
	long	nullvect
	long	nullvect
	long	nullvect
	long	nullvect

# Priority level 4, vectors 192-207

level4:	global	level4
comvec:	global  comvec
	long	comint		
	long	comint		
	long	comint		
	long	comint		
	long	comint		
	long	comint		
	long	comint		
	long	comint		
	long	comint		
	long	comint		
	long	comint		
	long	comint		
	long	comint		
	long	comint		
	long	comint		
	long	comint		

# Priority level 5, vectors 208-223

level5:	global	level5

	global	res1
res1:	long	nullvect		# 340
	long	nullvect		# 344
	long	nullvect		# 348
	long	nullvect		# 34c
	long	nullvect		# 350
	long	nullvect		# 354
	long	nullvect		# 358
	long	nullvect		# 35c
	long	nullvect		# 360
	long	nullvect		# 364
	long	nullvect		# 368
	long	nullvect		# 36c
	long	nullvect		# 370
	long	nullvect		# 374
	long	nullvect		# 378
	long	nullvect		# 37c

# Priority level 6, vectors 224-239

level6:	global	level6
	long	nullvect	# 380
	long	nullvect	# 384
	long	nullvect	# 388
	long	nullvect	# 38c
	long	nullvect	# 390
	long	nullvect	# 394
	long	nullvect	# 398
	long	nullvect	# 39c
	long	nullvect	# 3a0
	long	nullvect	# 3a4
	long	nullvect	# 3a8
	long	nullvect	# 3ac
	long	nullvect	# 3b0
	long	nullvect	# 3b4
	long	nullvect	# 3b8
	long	nullvect	# 3bc

# Priority level 7, vectors 240-255

level7:	global	level7
	global	nmi_stp
nmi_stp:long	nmi_halt	# 3c0
	global	cpu_int
cpu_int:long	kick_cpu	# 3c4
	global  kdbvec	
kdbvec: long	kdb_nmi		# 3c8
        global  smpvec
smpvec: long    smp_nmi         # 3cc
	long	nullvect	# 3d0
	long	nullvect	# 3d4
	long	nullvect	# 3d8
	long	nullvect	# 3dc
	long	nullvect	# 3e0
	long	nullvect	# 3e4
	long	nullvect	# 3e8
	long	nullvect	# 3ec
	long	nullvect	# 3f0
	long	nullvect	# 3f4
	long	irq5		# 3f8 (Power fail in systems with Explorer)
	long	nullvect	# 3fc

# END OF EXCEPTION VECTORS

# The first page after the exception vectors is reserved for a
# multiprocessor communication area

	global	comtbl
comtbl:	long	0
#
# This is the dump vector used by ROM to enter dump code f(s)000404
#
dmpvec: long	dmpstk		#dump stack pointer
	long	dodump		#dump PC
	long	0		#CRC

# STBM expects DEVMAP address to be at 0x410
	long	devmap

	long	0	# Three spare longs
	long	0
	long	0

# fzero0 MUST be aligned on an address that is a multiple of 16 bytes
# and must be 16 bytes long, filled with zeros.  See fzero() in misc.s.
	global	fzero0
fzero0: long	0
	long	0
	long	0
	long	0

	global	spare
spare:	space	752

#
# Dump stack - initialized by STBM with dump structure
#
	space	200
	global dmpstk
dmpstk:
	space	24

	data

	global	cputype
cputype:
	short	682
	short	0

	text

# Low level exception handlers

# Exception handlers act one of three ways:
# usp is pushed onto the stack and after the handler we just return.
# usp is pushed onto the stack and after the handler we may reschedule.
# usp is not pushed onto the stack and there is not reschedule

# busint, adrint: a page fault (or worse)
#
	text
bus030:	mov.l	cpubaddr+ACCTIMER30,newacct  # get value of acct timer
	bra.b	busin1
busint:	global	busint
adrint:	global	adrint
	or.w	&0700,%sr	# Disable interrupts temporarily
	cmp.l	bdtype,&B68020
	bne.b	bus030
	mov.l	cpubaddr+ACCTIMER,newacct  # get value of acct timer
busin1:
	movm.l	&0xfffe,-(%sp)

	mov.l	%usp,%a0
	mov.l	%a0,-(%sp)

	btst	&SUPER,SR(%sp)	# supervisor mode?
	bne.b	busin3		# yes, then don't add time to utime
	mov.l	newacct,%d1 	# get value of acct timer
	mov.l	%d1,%d2
	sub.l	acctim,%d2	# subtract
	bge.b	busin2		
	add.l	&0x01000000,%d2	# account for rollover
busin2:
	mov.l	%d1,acctim	# store current time as new oldtim
	add.l	%d2,usrtim	# save accumulated time in cpu-local page
busin3:
	mov.b	VOROFF(%sp),%d0 # Check frame type to determine cpu type
	and.w	&0x00f0,%d0
	cmp.w	%d0,&0x70
	blt.w	rtrap		# No SSW, so go call trap()
	bgt.w	bus023

#				# Frame type==7 on a 68040 based machine
	mov.w	SSW040(%sp),%d0 # get function code bits into d0
	mov.l	FA040(%sp),%a0	# get fault address
	mov.l	%dfc,%d1	# save %dfc
	mov.l	%d0,%dfc
#	ptest	(%a0)		# test out fault address
	short	0xf568
	mov.l	%d1,%dfc	# restore %dfc
#	MOVEC	%mmust,%d0
	long	0x4e7a0805
	mov.l	&mmust1,%a0
	mov.l	%d0,(%a0)
	mov.w	SR(%sp),%d0	# restore interrupt level--carefully
	and.w	&0x3700,%d0	#
	or.w	&PS_SUP,%d0	#
	mov.w	%d0,%sr		#

	mov.l	%sfc,%a0
	mov.l	%a0,-(%sp)
	mov.l	%d1,-(%sp)
	jsr	fault040
	mov.l	(%sp)+,%a0
	mov.l	%a0,%dfc
	mov.l	(%sp)+,%a0
	mov.l	%a0,%sfc
	mov.l	(%sp)+,%a0
	mov.l	%a0,%usp
	mov.l	cpubaddr+ACCTIMER30,%d1  # get value of acct timer
	sub.l	acctim,%d1	# subtract
	bge.b	rt%40b		
	add.l	&0x01000000,%d1	# if negative, account for rollover
rt%40b: add.l	%d1,systim	# save accumulated time in cpu-local page
	movm.l	(%sp)+,&0x7fff
	tst.b	7(%sp)		# check low byte of vor
	bne.w	rte%30		# not zero, normal case, just return
#				# User Signal Handler to enter
	mov.w	(%sp),52(%sp)	# copy status register
	mov.l	2(%sp),54(%sp)	# copy pc
	clr.w	58(%sp)		# clear vector offset
	add.l	&52,%sp		# pop old stack frame
	rte			# back to user mode signal handler

bus023:				# A 68020/68030 based machine
	mov.w	SSW(%sp),%d0	# get function code bits into d0
#	ptestr	%d0,DCFA(%sp),0 # test out data cycle fault address
	short	0xf02f,0x8208,DCFA
	mov.l	&mmust1,%a0
#	pmove	MMUSR,(%a0)	# save MMU status reg
	short	0xf010,0x6200
	mov.w	SR(%sp),%d0	# restore interrupt level--carefully
	and.w	&0x3700,%d0	#
	or.w	&PS_SUP,%d0	#
	mov.w	%d0,%sr		#
#
	mov.l	%sfc,%a0
	mov.l	%a0,-(%sp)
	mov.l	%dfc,%a0
	mov.l	%a0,-(%sp)
	jsr	fault
	mov.l	(%sp)+,%a0
	mov.l	%a0,%dfc
	mov.l	(%sp)+,%a0
	mov.l	%a0,%sfc
	mov.l	(%sp)+,%a0
	mov.l	%a0,%usp

	cmp.l	bdtype,&B68020
	beq.b	rt%20
	mov.l	cpubaddr+ACCTIMER30,%d1  # get value of acct timer
	bra.b	rt%20a
rt%20:	mov.l	cpubaddr+ACCTIMER,%d1  # get value of acct timer
rt%20a:
	sub.l	acctim,%d1	# subtract
	bge.b	rt%20b		
	add.l	&0x01000000,%d1	# if negative, account for rollover
rt%20b: add.l	%d1,systim	# save accumulated time in cpu-local page

	movm.l	(%sp)+,&0x7fff
	tst.b	7(%sp)		# check low byte of vor
	bne	rte%		# not zero, normal case, just return
	cmp.b	6(%sp),&0xa0	# check format for type 10
	beq	rte%10		# Go handle short bus cycle fault stack frame
	cmp.b	6(%sp),&0xb0	# check format for type 11
	beq	rte%11		# handle long bys cycle fault stack frame

rte%:				# just return, no rescheduling or signals
	cmp.l	bdtype,&B68020
	bne.b	rte%30
	mov.l	cpubaddr+ACCTIMER,acctim  # store current time as new oldtim
	rte
rte%30:	mov.l	cpubaddr+ACCTIMER30,acctim  # store current time as new oldtim
	rte

# Special handling for sending signals with bus error stack frames.

rte%10:
	mov.w	(%sp),24(%sp)	# copy status register
	mov.l	2(%sp),26(%sp)	# copy pc
	clr.w	30(%sp)		# clear vector offset
	add.l	&24,%sp		# pop old stack frame
	rte			# back to user mode signal handler

rte%11:
	mov.w	(%sp),84(%sp)	# copy status register
	mov.l	2(%sp),86(%sp)	# copy pc
	clr.w	90(%sp)		# clear vector offset
	add.l	&84,%sp		# pop old stack frame
	rte			# back to user mode signal handler

# trap0: a system call

trp030:	mov.l	cpubaddr+ACCTIMER30,newacct  # get value of acct timer
	bra.b	trpin1
trap0:
	cmp.l	bdtype,&B68020
	bne.b	trp030
	mov.l	cpubaddr+ACCTIMER,newacct  # get value of acct timer
trpin1:
	and.w	&0xfffe,(%sp)	# Clear carry bit
	movm.l	&0xfffe,-(%sp)
	mov.l	newacct,%d1 	# get value of acct timer
	mov.l	%d1,%d2
	sub.l	acctim,%d2	# subtract
	blt.b	trap1a		# if negative, go account for rollover
trap0a:
	mov.l	%d1,acctim	# store current time as new oldtim
	add.l	%d2,usrtim	# save accumulated time in cpu-local page
	mov.l	%usp,%a0
	mov.l	%a0,-(%sp)
	jsr	usyscall
					# kick off streams queue scheduling.
	mov.w	%sr,%d0			# Mask interrupts
	or.w	&0x2700,%sr		# Mask interrupts
	tst.b	qrunflag
	beq.b	not_qrun		# don't run if no enabled queues
	tst.b	queueflag
	bne.b	not_qrun		# don't run if already in queuerun()
	mov.l	cpuid,%a0		# bump runrun
	add.w	%a0,%a0
	add.l	&runrun,%a0
	add.w	&1,(%a0)		# bump runrun
not_qrun:
	mov.w	%d0,%sr			# Un-mask interrupts
	bra	rsched
trap1a:
	add.l	&0x01000000,%d2	# account for rollover
	bra.b	trap0a		# go back to mainline code

# irq6		- non-maskable interrupt from the diagnostic port
irq6:
	movm.l	&0xfffe,-(%sp)
	mov.l	%usp,%a0
	mov.l	%a0,-(%sp)
	jsr	nmi
	bra.w	rtn2sup

trap5:
	cmp.l	chiptype,&_040_CHIP
	beq.b	trp1fl
	mov.l	%d1,-(%sp)
	mov.l	ccrflsh,%d1	# enable and flush 68020/030 on-chip cache(s)
#	MOVEC(D1,CACR)
	long	0x4e7b1002
	mov.l	(%sp)+,%d1
	rte
trp1fl:
	nop			# use nop to avoid errata problems
#	CPUSHA  BC
	short	0xf4f8		# cpusha both caches (also invalidates)
	nop			# Ensure cpush didn't leave writebacks!
	rte
	
hfline:
	cmp.l	chiptype,&_040_CHIP # 2c	F line exception
	beq.l	fpsp_fline
	bra.w	Fint
hbsun:
	cmp.l	chiptype,&_040_CHIP # c0 branch on set or unorder condition
	beq.l	fpsp_bsun
	movm.l	&0xfffe,-(%sp)
	mov.l	%usp,%a0
	mov.l	%a0,-(%sp)
#	FMOVE.L FPSR,%D0
	long	0xf200a800
	and.l	&NOT_NAN,%d0	#See note in FBcc section of FPU manual
#	FMOVE.L %D0,FPSR
	long	0xf2008800
	bra.b	rtrap
hinex:
	cmp.l	chiptype,&_040_CHIP # c4	inexact result
	beq.l	fpsp_inex
hdz:
	cmp.l	chiptype,&_040_CHIP # c8	divide by zero
	beq.l	fpsp_dz
hunfl:
	cmp.l	chiptype,&_040_CHIP # cc	underflow
	beq.l	fpsp_unfl
hoperr:
	cmp.l	chiptype,&_040_CHIP # d0	operand error
	beq.l	fpsp_operr
hovfl:
	cmp.l	chiptype,&_040_CHIP # d4	overflow
	beq.l	fpsp_ovfl
hsnan:
	cmp.l	chiptype,&_040_CHIP # d8	signaling NAN
	beq.l	fpsp_snan
	bra.b	fpu_int
hunimp:
	cmp.l	chiptype,&_040_CHIP # dc	Unassigned, Reserved
	beq.l	fpsp_unsupp
	bra.w	ur_int

# common internal exception handler
#
illint:
zdint:
chkint:
tvint:
pvint:
trcint:
Aint:
Fint:
trapn:
fpu_int:
Xtrap:	global	Xtrap
#
cpvint:
fmtint:
uiint:
siint:
mmuint:
	movm.l	&0xfffe,-(%sp)
	mov.l	%usp,%a0
	mov.l	%a0,-(%sp)
rtrap:
	jsr	trap
	btst	&SUPER,SR(%sp)	# supervisor mode?
	bne.w	rtn2sup		# yes, then go rtn immediately.
	bra.w	rsched		# no

# clkint	- handler for PIT interrupts

# irq2		- low battery  OR  MFP PIT interrupt from 68030

irq2:
	mov.l	cpubaddr+ACCTIMER30,newacct  # get value of acct timer
	bra.b	clkin1
clkint:
	cmp.l	bdtype,&B68020
	bne.w	cparity
	mov.l	cpubaddr+ACCTIMER,newacct  # get value of acct timer
clkin1:
	movm.l	&0xfffe,-(%sp)
	mov.l	%usp,%a0
	mov.l	%a0,-(%sp)
#
set     PPID,20
#
	tst.l	tmintsmp1
	beq.b	clkin1b
        mov.l   cpuid,%d0
        lsl.l   &3,%d0
        mov.l   %d0,%a1
        add.l   &smptbl+8,%a1
        mov.l   curproc,%a0
        mov.w   PPID(%a0),(%a1)
        tst.l   idleing
        beq.b   clkin1a
        or.w    &0x8000,(%a1)
clkin1a:
        add.l   &2,%a1
        or.w    &PS_MAS,%sr     # switch to master stack and
        mov.l   %sp,%a0         # get master stack pointer
        and.w   &NPS_MAS,%sr    # now switch back to interrupt stack.
        mov.w   (%a0),(%a1)+
        mov.l   2(%a0),(%a1)
clkin1b:
	clr.l	%d3
	mov.w	SR(%sp),%d3	# get saved status reg.
	mov.w	%d3,%d0		# copy it for testing.
	and.w	&PS_MAS,%d0	# check if already on interrupt stack
	beq.b	clkin3		# when the clock tick occurred.
	or.w	&PS_MAS,%sr	# if not, then switch to master stack and
	mov.w	(%sp),%d3	# get saved status reg from master stk.
	and.w	&NPS_MAS,%sr	# now switch back to interrupt stack.
	mov.w	%d3,%d0
	and.w	&PS_SUP,%d0	# supervisor mode?
	bne.b	clkin3		# yes, then don't add time to utime
	mov.l	newacct,%d6 	# get value of acct timer
	mov.l	%d6,%d2
	sub.l	acctim,%d2	# subtract
	bpl.b	clkin2		# if negative, must account for rollover
	add.l	&0x1000000,%d2	# account for rollover
clkin2:
	mov.l	%d6,acctim	# store current time as new oldtim
	add.l	%d2,usrtim	# save accumulated time in cpu-local page

	jsr	ckuprof		# Check for user process profiling.
	beq.b	clkin3		# Branch if not on for this process;
	add.l	&4,%sp		# else must move to master stack!
	movm.l	(%sp)+,&0x7fff	# Copy contents of interrupt stack to
	mov.l	&kistack,%sp	# the master stack for the process.
	mov.w	&0x3700,%sr	# Switch to master stack.
	movm.l	&0xfffe,-(%sp)	#
	mov.l	%usp,%a0	# Now push usp onto master stack
	mov.l	%a0,-(%sp)
	clr.l	%d3
	mov.w	SR(%sp),%d3	# get saved status reg.
clkin3:
	mov.l	PC(%sp),%d2	# pick up saved pc while 'PC' still valid
	mov.l	%d3,-(%sp)
	mov.l	%d2,-(%sp)
	jsr	clock
	add.l	&8,%sp
	and.w	&PS_SUP,%d3	# supervisor mode?
	beq.b	rsched		# no
rtn2sup:
	mov.l	(%sp)+,%a0	# yes, then just return
	mov.l	%a0,%usp
	movm.l	(%sp)+,&0x7fff
	rte
#
# rsched	- common return point for rescheduling chks after interrupts 
#
rsched:
	mov.l	ot_fwrt,%d0	# test for active forced write
	cmp.w	%d0,&0x0002
	beq.b	hotdly		# if 2 then put process to sleep

	mov.l	cpuid,%a0
	add.w	%a0,%a0
	add.l	&runrun,%a0
	tst.w	(%a0)		# do we need to reschedule ?
	bne.w	rsforce		# yes, then go do it
retrn2u:
	mov.l	(%sp)+,%a0	# Return to user mode execution
	mov.l	%a0,%usp
	cmp.l	bdtype,&B68020
	bne.b	rtn030
	mov.l	cpubaddr+ACCTIMER,%d1  # get value of acct timer
	sub.l	acctim,%d1	# subtract
	blt.b	retrn4		
retrn3:
	add.l	%d1,systim	# save accumulated time in cpu-local page
	movm.l	(%sp)+,&0x7fff
	mov.l	cpubaddr+ACCTIMER,acctim  # store current time as new oldtim
	rte
retrn4:
	add.l	&0x01000000,%d1	# if negative, account for rollover
	bra.b	retrn3
rtn030:	mov.l	cpubaddr+ACCTIMER30,%d1  # get value of acct timer
	sub.l	acctim,%d1	# subtract
	add.l	%d1,systim	# save accumulated time in cpu-local page
	movm.l	(%sp)+,&0x7fff
	mov.l	cpubaddr+ACCTIMER30,acctim  # store current time as new oldtim
	rte
hotdly:
	clr.l	-(%sp)		# push sleeping priority
	pea	hot_sema	# ot semaphore address
	jsr	psema		# go to sleep
	add.l	&8,%sp		#
	bra.b	retrn2u
rsforce:
	mov.w	%sr,%d0
	and.w	&PS_MAS,%d0	# If currently using proc's master stack
	bne.b	rsforc9		# then we can do the forced reschedule now.
	mov.l	(%sp)+,%a0	# Else restore usp from stack
	mov.l	%a0,%usp	#
rsforc1:
	movm.l	(%sp)+,&0x7fff	# copy contents of interrupt stack to
	mov.l	&kistack,%sp	# the master stack for the process
	mov.w	&0x3700,%sr	#
	movm.l	&0xfffe,-(%sp)	#
	mov.l	%usp,%a0	# now push usp onto master stack
	mov.l	%a0,-(%sp)
rsforc9:
	or.w	&0x2700,%sr	# disable interrupts
	and.w	&0xf000,VOROFF(%sp)
	jsr	trap
	bra.w	retrn2u

# irq3
# over temperature interrupt handler
#
irq3:
	movm.l	&0xfffe,-(%sp)		# call otemp subroutine in
	jsr	otemp			# machdep.c
	movm.l	(%sp)+,&0x7fff
	rte

# irq4		- diagnostic port interrupt

irq4:
	movm.l	&0xfffe,-(%sp)
	mov.l	cpuid,-(%sp)	# pass cpuid as device
	jsr	dpint		# process the interrupt
	add.l	&4,%sp		# return
	bra	intret

irq1:				# irq1		- accounting timer
	add.l	&1,msptimer	# Bump time stamp variable
	mov.b	&0x1f,cpubaddr+ACCTCTL # Clear interrupt
	nop			# Force write buffer out before rte.
	rte

# irq2		- low battery
# nullvect	- handler for unsolicited interrupts
# ur_int	- handler for unassigned, reserved exceptions
	global	nullvect
nullvect:
ur_int:
	movm.l	&0xfffe,-(%sp)
	jsr	badint
	movm.l	(%sp)+,&0x7fff
	rte
irq5:				# irq5		- power fail
	movm.l	&0xfffe,-(%sp)	# just in case interrupt is spurious
#				# save regs for dump analysis
	jsr	powerfail
#	........................  No return possible.

# NUBUS INTERRUPT handlers
#
# Interrupt handlers use VECTOR instead of VOROFF to access the vector
# offset register on the stack since the user's stack point is not saved.
#
	set	VECTOR,66
vpbint:
	movm.l	&0xfffe,-(%sp)
	mov.w	VECTOR(%sp),%d0
	and.l	&0xfff,%d0
	sub.l	&vpbvec,%d0
	lsr.l	&2,%d0
	mov.l	%d0,-(%sp)
	jsr	vpbintr
	add.l	&4,%sp
	bra	intret
	
# Embeded Ethernet board interrupt handlers
# There are 16 entry points for it 
seneti0: global seneti0
	movm.l	&0xfffe,-(%sp)
	mov.l	&0,-(%sp)		# push unit number
	jsr	senetintr
	add.l	&4,%sp
	bra	intret
seneti1: global seneti1
	movm.l	&0xfffe,-(%sp)
	mov.l	&1,-(%sp)		# push unit number
	jsr	senetintr
	add.l	&4,%sp
	bra	intret
seneti2: global seneti2
	movm.l	&0xfffe,-(%sp)
	mov.l	&2,-(%sp)		# push unit number
	jsr	senetintr
	add.l	&4,%sp
	bra	intret
seneti3: global seneti3
	movm.l	&0xfffe,-(%sp)
	mov.l	&3,-(%sp)		# push unit number
	jsr	senetintr
	add.l	&4,%sp
	bra	intret
seneti4: global seneti4
	movm.l	&0xfffe,-(%sp)
	mov.l	&4,-(%sp)		# push unit number
	jsr	senetintr
	add.l	&4,%sp
	bra	intret
seneti5: global seneti5
	movm.l	&0xfffe,-(%sp)
	mov.l	&5,-(%sp)		# push unit number
	jsr	senetintr
	add.l	&4,%sp
	bra	intret
seneti6: global seneti6
	movm.l	&0xfffe,-(%sp)
	mov.l	&6,-(%sp)		# push unit number
	jsr	senetintr
	add.l	&4,%sp
	bra	intret
seneti7: global seneti7
	movm.l	&0xfffe,-(%sp)
	mov.l	&7,-(%sp)		# push unit number
	jsr	senetintr
	add.l	&4,%sp
	bra	intret
seneti8: global seneti8
	movm.l	&0xfffe,-(%sp)
	mov.l	&8,-(%sp)		# push unit number
	jsr	senetintr
	add.l	&4,%sp
	bra	intret
seneti9: global seneti9
	movm.l	&0xfffe,-(%sp)
	mov.l	&9,-(%sp)		# push unit number
	jsr	senetintr
	add.l	&4,%sp
	bra	intret
senetia: global senetia
	movm.l	&0xfffe,-(%sp)
	mov.l	&10,-(%sp)		# push unit number
	jsr	senetintr
	add.l	&4,%sp
	bra	intret
senetib: global senetib
	movm.l	&0xfffe,-(%sp)
	mov.l	&11,-(%sp)		# push unit number
	jsr	senetintr
	add.l	&4,%sp
	bra	intret
senetic: global senetic
	movm.l	&0xfffe,-(%sp)
	mov.l	&12,-(%sp)		# push unit number
	jsr	senetintr
	add.l	&4,%sp
	bra	intret
senetid: global senetid
	movm.l	&0xfffe,-(%sp)
	mov.l	&13,-(%sp)		# push unit number
	jsr	senetintr
	add.l	&4,%sp
	bra	intret
senetie: global senetie
	movm.l	&0xfffe,-(%sp)
	mov.l	&14,-(%sp)		# push unit number
	jsr	senetintr
	add.l	&4,%sp
	bra	intret
senetif: global senetif
	movm.l	&0xfffe,-(%sp)
	mov.l	&15,-(%sp)		# push unit number
	jsr	senetintr
	add.l	&4,%sp
	bra	intret

# ccb interrupt
comint:
	movm.l	&0xfffe,-(%sp)
	mov.w	VECTOR(%sp),%d0
	and.l	&0xfff,%d0
	sub.l	&comvec,%d0
	lsr.l	&2,%d0
	mov.l	%d0,-(%sp)		# push controller number
	jsr	comintr
	add.l	&4,%sp
	bra	intret

# TE NuBus Message Service Interrupt
        global  msgint
msgint: 
        movm.l  &0xfffe,-(%sp)
        jsr     nb_intr
        bra     intret

# nupi or msc special event interrupt
spint:
	movm.l	&0xfffe,-(%sp)
###	mov.w	VECTOR(%sp),%d0
###	and.l	&0xfff,%d0
###	sub.l	&spvec,%d0
###	lsr.l	&2,%d0
###	mov.l	%d0,-(%sp)
	jsr	spintr
###	add.l	&4,%sp
	bra	intret

# nupi or msc 1/2" tape interrupt
htint:
	movm.l	&0xfffe,-(%sp)
###	mov.w	VECTOR(%sp),%d0
###	and.l	&0xfff,%d0
###	sub.l	&htvec,%d0
###	lsr.l	&2,%d0
###	mov.l	%d0,-(%sp)		# push controller number
	jsr	htintr
###	add.l	&4,%sp
	bra	intret
 
# nupi or msc 1/4" tape interrupt
qtint:
	movm.l	&0xfffe,-(%sp)
###	mov.w	VECTOR(%sp),%d0
###	and.l	&0xfff,%d0
###	sub.l	&qtvec,%d0
###	lsr.l	&2,%d0
###	mov.l	%d0,-(%sp)		# push controller number
	jsr	qtintr
###	add.l	&4,%sp
	bra	intret

# nupi or msc disk interrupt
dskint:
	movm.l	&0xfffe,-(%sp)
###	mov.w	VECTOR(%sp),%d0
###	and.l	&0xfff,%d0
###	sub.l	&dskvec,%d0
###	lsr.l	&2,%d0
###	mov.l	%d0,-(%sp)
	jsr	dskintr
###	add.l	&4,%sp
####	bra	intret

#interrrupt return routine
intret:
	mov.w	SR-4(%sp),%d3	# get saved status reg.
	mov.l	%d3,%d0		# copy it for testing.
	and.w	&PS_MAS,%d0	# check if already on interrupt stack
	beq.b	intr0		# when the interrupt occurred.
	or.w	&PS_MAS,%sr	# if not, then switch to master stack and
	mov.w	(%sp),%d3	# get saved status reg from master stk.
	and.w	&NPS_MAS,%sr	# now switch back to interrupt stack.
	and.w	&PS_SUP,%d3	# Check if previously in user mode.
	beq.b	intr1		# If so, go check for rescheduling.
intr0:
	movm.l	(%sp)+,&0x7fff	# Return to super mode immediately.
	rte
intr1:	
	mov.l	cpuid,%a0
	add.l	%a0,%a0
	add.l	&runrun,%a0
	tst.w	(%a0)
	bne.b	intr2
					# Streams junk begins here
	mov.w	%sr,%d0			# Mask interrupts
	or.w	&0x2700,%sr		# Mask interrupts
	tst.b	qrunflag
	beq.b	no_qrun			# don't run if no enabled queues
	tst.b	queueflag
	bne.b	no_qrun			# don't run if already in queuerun()
	mov.w	%d0,%sr			# UnMask interrupts
	bra.b	intr2

no_qrun:
	mov.w	%d0,%sr			# Un-mask interrupts
	movm.l	(%sp)+,&0x7fff
	rte

int030:	mov.l	cpubaddr+ACCTIMER30,%d1  # get value of acct timer
	bra.b	intin1
intr2:
	cmp.l	bdtype,&B68020
	bne.b	int030
	mov.l	cpubaddr+ACCTIMER,%d1  # get value of acct timer
intin1:
	mov.l	%d1,%d2
	sub.l	acctim,%d2
	blt.b	intr4
intr3:	mov.l	%d1,acctim
	add.l	%d2,usrtim	# save accumulated time in cpu-local page
	bra	rsforc1
intr4:	add.l	&0x1000000,%d2
	bra.b	intr3	

# Routine for boot utility.
# We must set the vbr with the ROM's vectors,
# and set the LSB in its event word. This
# triggers a L7 interrupt and we're off...
# These addresses are slot and mem-config dependent,
# passed in the stack from the boot driver.

	data
trctl:	long	0x02a07780	#value for translation control reg #
	text
	global	boot
	set	VBRLD, 0x000ffc00
	set	BTVEC, 0x00fff400
	set	STKAD, 0xff000400
  boot: mov.l	4(%sp), %d2	# get slot argument from bootioctl()
        mov.l	8(%sp), %d3	# get memid argument from bootioctl()

# turn off on chip cache

	cmp.l	chiptype,&_040_CHIP
	beq.b	bootd

	mov.l	&0x808,%d0	#flush	
	long	0x4e7b0002	# MOVEC	%d0,%ccr
	bra.b	bootd1
bootd:
	nop			# use nop to avoid errata problems
#	CPUSHA			# Ensure memory has latest data !!
	short	0xf4f8
	nop			# Ensure cpush didn't leave writebacks!
bootd1:
	mov.l	&0,%d0		#disable
	long	0x4e7b0002	# MOVEC	%d0,%ccr

        mov.w	&0x2700, %sr	# Disable interrupts AND use interrupt stk
	mov.l	&VBRLD, %d1	# load up ROM vbr
	or.l	%d3, %d1
	mov.l	%d1, %vbr
	mov.l	&BTVEC, %d1	# load up ROM event vector
	or.l	%d2, %d1
	mov.l	%d1, %a0
	and.l	&STKAD, %d1 	# set stack to 0xfs000400
	mov.l	%d1, %a7
	cmp.l	chiptype,&_040_CHIP
	beq.b	bot40
	mov.l	&trctl, %a1	#address of tc register value
#	pmove.l   (%a1),%tc
	long	0xf0114000	#disable address translation
bot1:
	bset	&0, (%a0)	# set bit to trigger ROM L7 interrupt
bot9:	nop
	bra	bot9
	rte
bot40:
#				# A 68040 based machine
	clr.l	%d0		# new TC register value
#	MOVEC   %d0,%tc
	long	0x4e7b0003	#disable address translation
	bra.b	bot1
	
#
#  Routine to cause crash dump without entering ROM monitor
#
 global  ddump
  ddump: mov.l	4(%sp), %d2	# get slot argument from bootioctl()
         mov.l	8(%sp), %d3	# get memid argument from bootioctl()
 
# turn off on chip cache
 
        or.w	&0x2700,%sr

	cmp.l	chiptype,&_040_CHIP
	beq.b	ddm8

 	mov.l	&0x808,%d0	#flush	
 	long	0x4e7b0002	# MOVEC	%d0,%ccr
	bra.b	ddm8c
ddm8:
	nop			# use nop to avoid errata problems
#	CPUSHA			# Ensure memory has latest data !!
	short	0xf4f8
	nop			# Ensure cpush didn't leave writebacks!
ddm8c:
 	mov.l	&0,%d0		#disable
 	long	0x4e7b0002	# MOVEC	%d0,%ccr
 
 
 	mov.l	&VBRLD, %d1	# load up ROM vbr
 	or.l	%d3, %d1
 	mov.l	%d1, %vbr

	mov.l	&dmpvec, %d0	# load up address of dump vector
	or.l	%d2, %d0
	mov.l   %d0,%a0
	cmp.l	chiptype,&_040_CHIP
	beq.b	ddm40

	mov.l	&trctl, %a1	#address of tc register value
#	pmove.l   (%a1),%tc
	long	0xf0114000	#disable address translation
ddm1:
	mov.l	(%a0), %a7	# dump stack
	add.l	&4, %a7		# compensate for return address
	mov.l	4(%a0), %a1	# dump routine
	jsr	(%a1)		# Enter dump routine
ddm40:
#				# A 68040 based machine
	clr.l	%d0		# new TC register value
#	MOVEC   %d0,%tc
	long	0x4e7b0003	#disable address translation
	bra.b	ddm1

#
# Routine for panic (so we halt all cpus)
#

nmi_halt:
	movm.l	&0xfffe,-(%sp)	# save the registers
	mov.l	%usp,%a0
	mov.l	%a0,-(%sp)	# save usp
	or.w	&PS_MAS,%sr	# switch to master stack and
	mov.l	%sp,%a0		# get master stack pointer
	and.w	&NPS_MAS,%sr	# now switch back to interrupt stack.
	mov.l	cpuid,%d0	# 
	lsl.l	&2,%d0		#
	mov.l	&savedmsp,%a1	# get addr of array to save in
	add.l	%d0,%a1		# index into it.
	mov.l	%a0,(%a1)	# Store msp into array.
	jsr	panics		# panic secondary
	bra	intret

# Routine for kdb to halt a cpu

kdb_nmi:
	tst.l	haltsp
	bne.b	kdb_st2
	movm.l	&0xfffe,-(%sp)	# save the registers
	mov.l	%sp,haltsp
	cmp.l	chiptype,&_040_CHIP
	bne.b	kdb_wt
	nop			# use nop to avoid errata problems
#	CPUSHA  BC
	short	0xf4f8		# cpusha both caches (also invalidates)
	nop			# Ensure cpush didn't leave writebacks!
kdb_wt:
	tst.l	haltsp
	beq.b	kdb_st
	stop	&0x2700		# Stop until another kdb_nmi comes in
	bra.b	kdb_wt
kdb_st: 
	movm.l	(%sp)+,&0x7fff	# restore registers
kdb_st2: 
	clr.l	haltsp		# and then
#	
# Routine for interrupting an idleing cpu
kick_cpu:
	rte			# just return, nothing more . . .

# Special stack fixup routine

fixspi:
	movm.l	&0xfffe,-(%sp)	# save the registers
	mov.l	%usp,%a0
	mov.l	%a0,-(%sp)	# save usp
	jsr	fixsup
	bra	rtn2sup

# Timeout interrupt handler

touthndl:
	movm.l	&0xfffe,-(%sp)	# save the registers
	jsr	timein
	bra	intret
# 
# cache parity error handler (for some board types)
#
cparity:
	movm.l	&0xfffe,-(%sp)		# call cachepar subroutine
	jsr	cachepar
#	-----	no return possible

#
smp_nmi:
        mov.l   %a0,-(%sp)
        mov.l   %a1,-(%sp)
        mov.l   cpuid,%a1
        add.l   %a1,%a1
        add.l   %a1,%a1
        add.l   %a1,%a1
        add.l   &smptbl+8,%a1
        mov.l   curproc,%a0
        mov.w   PPID(%a0),(%a1)
        tst.l   idleing
        beq.b   smp_2
        or.w    &0x8000,(%a1)
smp_2:
        add.l   &2,%a1
        or.w    &PS_MAS,%sr     # switch to master stack and
        mov.l   %sp,%a0         # get master stack pointer
        and.w   &NPS_MAS,%sr    # now switch back to interrupt stack.
        mov.w   (%a0),(%a1)+
        mov.l   2(%a0),(%a1)
        mov.l   (%sp)+,%a1
        mov.l   (%sp)+,%a0
        rte
        data
smptbl:
	global  smptbl
        long    0,0     # space for time stamp
        long    0,0     # cpu 0
        long    0,0     # cpu 1
        long    0,0     # cpu 2
        long    0,0     # cpu 3
        long    0,0     # cpu 4
        long    0,0     # cpu 5
        long    0,0     # cpu 6
        long    0,0     # cpu 7
        long    0,0     # cpu 8
        long    0,0     # cpu 9
        long    0,0     # cpu 10
        long    0,0     # cpu 11
        long    0,0     # cpu 12
        long    0,0     # cpu 13
        long    0,0     # cpu 14
        long    0,0     # cpu 15
        text
