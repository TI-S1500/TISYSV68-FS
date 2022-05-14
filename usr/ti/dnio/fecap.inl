# @(#)fecap.inl	1.11 91/02/01
# Real Ti931 terminal
#
x5_dnio|X5_dnio|ti931r_dnio|Texas Instruments 931 VDT:\
	:f1=\Ei1:f2=\Ei2:f3=\Ei3:f4=\Ei4:f5=\Ei5:f6=\Ei6:f7=\Ei7:f8=\Ei8:\
	:f9=\Ei9:f10=\Ei\072:f11=\Ei;:f12=\Ei<:\
	:f13=\Ei=:f14=\Ei>:f15=\Ei?:f16=\Ei@:f17=\EiA:\
	:f18=\EiB:f19=\EiC:f20=\EiD:f21=\EiE:f22=\EiF:f23=\EiG:f24=\EiH:\
	:rtn_key=^m:home_key=\EH:enter_key=\Eiq:cmd_key=\Eh:\
	:print_key=\EW:up_key=\EA:down_key=\EB:left_key=\ED:right_key=\EC:\
	:fld_rt_key=\Eio:fld_lf_key=\Et:tab_key=\t:back_tab_key=\E2:\
	:blk_grey_key=\EN:erase_input_key=\EK:skip_key=\Es:esc_key=\Ef:\
	:erase_all=\EL:erase_eos=\EJ:erase_eol=\EI:\
	:back_space_key=^h:insert_key=\EP:delete_key=\EQ:erase_field_key=\E=:\
	:blank_orange_key=\Eg:\
	:print_screen_key=^p:redraw_screen_key=^r:\
	:cursor_up=\EA:cursor_down=\EB:cursor_right=\EC:\
	:cursor_motion=\EY%+ %+ :\
	:cursor_solid=\EV0:cursor_blink=\EV1:\
	:cursor_bright=\EM:cursor_dark=\ER:\
	:sgr_mask=\E4%:\
	:sgr0=@:sgr1=A:sgr2=B:sgr3=C:sgr4=D:sgr5=E:sgr6=F:sgr7=G:sgr8=P:\
	:sgr9=Q:sgr10=R:sgr11=S:sgr12=T:sgr13=U:sgr14=V:sgr15=W:\
	:status_line_bb=\EGK\E(:status_line_eb=\E):\
	:insert_line=\EN:delete_line=\EO:\
        :open=\EGB\E(BB@@\E):\
        :close=\EGB\E(@B@@\E):

t1_dnio|ti924_dnio|Texas Instruments 924 VDT (7 bit):\
	:f1=\217P:f2=\217Q:f3=\217R:f4=\217S:\
	:f5=\C16~:f6=\C17~:f7=\C18~:f8=\C19~:\
	:f9=\C20~:f10=\C21~:f11=\C23~:f12=\C24~:f13=\C25~:f14=\C26~:\
	:f15=\C40~:f16=\C41~:f17=\C42~:f18=\C43~:f19=\C44~:f20=\C45~:\
	:f21=\C46~:f22=\C47~:f23=\C48~:f24=\C49~:\
	:f25=\C28~:f26=\C32~:sticky_margin:\
	:enter_key=\C1~:cmd_key=\C29~:print_key=\C34~:\
	:rtn_key=^m:home_key=\CH:up_key=\CA:down_key=\CB:\
	:left_key=\CD:right_key=\CC:fld_rt_key=\C6~:fld_lf_key=\C5~:\
	:tab_key=\t:back_tab_key=\CZ:\
	:print_screen_key=^p:redraw_screen_key=^r:\
	:insert_key=\C@:delete_key=\CP:erase_field_key=\C7~:\
	:blk_grey_key=\CL:erase_input_key=\CM:skip_key=\C4~:esc_key=\C31~:\
	:cursor_solid=\C33h:cursor_blink=\C33l:\
        :open=\E[?7h\E)1:\
        :close=\E[?7h\E)0:\
	:back_space_key=^h:tc=ansi_dnio:

t2_dnio|ti924-8_dnio|Texas Instruments 924 VDT (8 bit):\
	:8bit:sticky_margin:tc=ti924_dnio:

t3_dnio|ti924-132_dnio|Texas Instruments 924 VDT (132 column mode):\
	:max_col#132:sticky_margin:tc=t1_dnio:

t4_dnio|ti924-8-132_dnio|Texas Instruments 924 VDT (8-bit, 132 column mode):\
	:8bit:max_col#132:sticky_margin:tc=t1_dnio:

t5_dnio|ti926_dnio|Texas Instruments 926 VDT 931 mode 7 bit CTRL:\
	:tc=t9_dnio:

t6_dnio|em924_dnio|Texas Instruments 924 Emulator in 924 mode:\
	:tc=t1_dnio:

t7_dnio|em924_dnio|Texas Instruments 924 Emulator in 924 mode 8-bit:\
	:8bit:tc=t1_dnio:

t8_dnio|em931_dnio|Texas Instruments 931 emulator:\
	:sticky_margin:tc=t9_dnio:

x1_dnio|ti928_dnio|Texas Instruments 928 VDT (7 bit):\
	:f1=\C17~:f2=\C18~:f3=\C19~:f4=\C20~:\
	:f5=\C21~:f6=\C23~:f7=\C24~:f8=\C25~:\
	:f9=\C26~:f10=\C28~:f11=\C29~:f12=\C31~:\
	:f13=\C32~:f15=\C34~:f16=\C37~:\
	:f17=\C38~:f18=\C39~:f19=\C40~:f20=\C41~:\
	:f21=\C43~:f22=\C44~:f23=\C45~:f24=\C46~:\
	:f25=\C48~:f26=\C49~:f27=\C51~:f28=\C52~:\
	:f29=\C53~:f30=\C54~:f31=\C36~:f32=\C56~:\
	:f33=\CS:f34=\CU:f35=\CT:f36=\CV:f37=\E_2\E\\:\
	:sticky_margin:\
	:enter_key=\C8~:cmd_key=\C33~:print_key=\C35~:\
	:rtn_key=^m:home_key=\CH:up_key=\CA:down_key=\CB:\
	:left_key=\CD:right_key=\CC:fld_rt_key=\C6~:fld_lf_key=\C5~:\
	:tab_key=\t:back_tab_key=\CZ:\
	:print_screen_key=^p:redraw_screen_key=^r:\
	:insert_key=\C@:delete_key=\CP:erase_field_key=\CN:\
	:blk_grey_key=\CL:erase_input_key=\CM:skip_key=\E_1\E\\:\
	:esc_key=\E_0\E\\:\
	:cursor_solid=\C33h:cursor_blink=\C33l:\
	:back_space_key=^h:tc=ansi_dnio:

x2_dnio|ti928-8_dnio|Texas Instruments 928 VDT (8 bit):\
	:8bit:f37=\237\062\234:skip_key=\237\061\234:esc_key=\237\060\234:\
	:sticky_margin:tc=x1_dnio:

x3_dnio|ti928-132_dnio|Texas Instruments 928 VDT (132 column mode):\
	:max_col#132:sticky_margin:tc=x1_dnio:

x4_dnio|ti928-8-132_dnio|Texas Instruments 928 VDT (8-bit, 132 column mode):\
	:8bit:max_col#132:sticky_margin:tc=x2_dnio:

#
# Texas Instruments 924 in 931 mode. NOT a real ti931
#
t9_dnio|T9_dnio|ti931_dnio|Texas Instruments 924 in 931 mode VDT:\
	:tc=x5_dnio:

d0_dnio|vt100_dnio|vt100-am_dnio|dec vt100:\
	:f1=\EOP:f2=\EOQ:f3=\EOR:cmd_key=\EOS:\
	:rtn_key=^m:delete_key=\177:up_key=\CA:\
	:enter_key=^j:tab_key=^i:\
	:print_screen_key=^p:redraw_screen_key=^r:\
	:down_key=\CB:right_key=\CC:back_space_key=^h:\
	:left_key=\CD:sticky_margin:tc=ansi_dnio:

d1_dnio|vt220_dnio|dec vt220 7 bit mode:\
	:f1=\C17~:f2=\C18~:f3=\C19~:f4=\C20~:f5=\C21~:f6=\C23~:\
	:f7=\C24~:f8=\C25~:f9=\C26~:f10=\C31~:f11=\C32~:f12=\C33~:\
	:f13=\C34~:f14=\217P:f15=\217Q:f16=\217R:f17=\217S:\
	:tab_key=^i:sticky_margin:\
	:cmd_key=\C28~:skip_key=\C4~:erase_field_key=\C3~:f18=\C1~:\
	:delete_key=\177:rtn_key=^m:\
	:print_screen_key=^p:redraw_screen_key=^r:\
	:back_space_key=^h:insert_key=\C2~:\
	:home_key=\C29~:fld_lf_key=\C5~:fld_rt_key=\C6~:\
	:enter_key=^j:up_key=\CA:down_key=\CB:\
	:right_key=\CC:left_key=\CD:tc=ansi_dnio:

d2_dnio|vt220-8_dnio|dec vt220 8-bit mode:\
	:8bit:sticky_margin:tc=d1_dnio:

d3_dnio|vt220-132_dnio|dec vt220 132-column mode:\
	:max_col#132:sticky_margin:tc=d1_dnio:

d4_dnio|vt220-8-132_dnio|dec vt220 8-bit 132-column mode:\
	:8bit:sticky_margin:tc=d3_dnio:

Mw_dnio|wyse_dnio|75_dnio|wy75_dnio|wyse75:\
	:f1=\C?5i:f2=\C?3i:f3=\C2i:f4=\C@:f5=\CM:f6=\C17~:\
	:f7=\C18~:f8=\C19~:f9=\C20~:f10=\C21~:f11=\C23~:f12=\C24~:\
	:f13=\C25~:f14=\C26~:f15=\C28~:f16=\C29~:f17=\C5i:\
	:f18=\C?1i:f19=\C0i:f20=\CL:f21=\CK:f22=\C31~:f23=\C32~:\
	:f24=\C33~:f25=\C34~:f26=\C35~:\
	:f27=\C1~:f28=\C2~:f29=\C3~:f30=\C4~:cmd_key=\C5~:f31=\C6~:\
	:insert_key=\EOP:back_tab_key=\EOQ:skip_key=\EOR:\
	:erase_field_key=\EOS:\
	:print_screen_key=^p:redraw_screen_key=^r:\
	:home_key=\CH:enter_key=^j:tab_key=^i:\
	:rtn_key=^m:back_space_key=^h:\
	:up_key=\CA:down_key=\CB:right_key=\CC:left_key=\CD:\
	:delete_key=\177:sticky_margin:\
	:open=\C0t\C1m:\
	:sgr_mask=\C%m:\
	:sgr0=1:sgr1=0:sgr2=0:sgr3=0:sgr4=0:sgr5=0:\
	:sgr6=0:sgr7=0:\
	:sgr8=0:sgr9=0:sgr10=0:sgr11=0:sgr12=0:\
	:sgr13=0:sgr14=0:sgr15=0:tc=ansi_dnio:

i1_dnio|ti926-7_dnio|TI 926 TERMINAL 7-BIT MODE:\
        :open=\E[?7h\E)1:\
        :close=\E[?7h\E-A:\
	:tc=t1_dnio:

i2_dnio|ti926-8_dnio|TI 926 TERMINAL 8-BIT MODE:\
        :open=\E[?7h\E)1:\
        :close=\E[?7h\E-A:\
	:tc=t2_dnio:


bpc_dnio|Business Pro Console:\
	:8bit:rtn_key=\015:enter_key=\E[E:\
	:cmd_key=\E[F:insert_key=\E[L:\
	:f1=\E[M:f2=\E[N:f3=\E[O:f4=\E[P:f5=\E[Q:f6=\E[R:\
	:f7=\E[S:f8=\E[T:f9=\E[U:f10=\E[V:\
	:f11=\E[Y:f12=\E[a:\
	:f13=\E[b:f14=\E[c:f15=\E[d:f16=\E[e:f17=\E[f:\
	:f18=\E[g:f19=\E[h:f20=\E[k:f21=\E[l:f22=\E[m:f23=\E[n:\
	:f24=\E[o:f25=\E[p:f26=\E[q:f27=\E[r:f28=\E[s:f29=\E[t:\
	:f128=\E\E:\
	:up_key=\E[A:delete_key=\177:print_key=\255:\
	:down_key=\E[B:left_key=\E[D:right_key=\E[C:\
	:tab_key=\t:back_tab_key=\E[Z:\
	:erase_field_key=\E[I:home_key=\E[H:skip_key=\E[G:\
	:sgr_mask=\E[%m:\
	:sgr0=0:sgr1=0;1:sgr2=0:sgr3=0;1:sgr4=0:sgr5=0;1:\
	:sgr6=0:sgr7=0;1:sgr8=0;5:sgr9=0;5;1:\
	:sgr10=0;5:sgr11=0;5;1:sgr12=0;5:\
	:sgr13=0;5;1:sgr14=0;5:sgr15=0;1;5:\
	:back_space_key=^h:\
	:insert_line=\E[L:delete_line=\E[M:\
	:erase_all=\E[2J:erase_eos=\E[J:erase_eol=\E[K:\
	:cursor_up=\215:cursor_down=\204:cursor_right=\E[C:\
	:cursor_motion=\E[%i%d;%dH:\
	:cursor_bright=\E[7m:cursor_dark=\E[m:\
	:max_row#25:\
	:print_screen_key=^p:redraw_screen_key=^r:

ansi_dnio|Standard Ansi terminal:\
	:insert_line=\CL:delete_line=\CM:\
	:erase_all=\C2J:erase_eos=\CJ:erase_eol=\CK:\
	:cursor_up=\215:cursor_down=\204:cursor_right=\CC:\
	:cursor_motion=\C%i%d;%dH:\
	:cursor_bright=\C?25h:cursor_dark=\C?25l:\
	:print_screen_key=^p:redraw_screen_key=^r:\
	:sgr_mask=\C%m:\
	:sgr0=0:sgr1=0;1:sgr2=0;7:sgr3=0;1;7:sgr4=0;4:sgr5=0;4;1:\
	:sgr6=0;4;7:sgr7=0;1;4;7:\
	:sgr8=0;5:sgr9=0;5;1:sgr10=0;5;7:sgr11=0;5;7;1:sgr12=0;5;4:\
	:sgr13=0;5;4;1:sgr14=0;5;4;7:sgr15=0;1;4;5;7:

h19_dnio|H19_dnio|heath_dnio|heathkit_dnio|heathkit h19:\
	:insert_line=\EL:erase_eos=\EJ:\
	:erase_eol=\EK:erase_all=\EE:cursor_motion=\EY%+ %+ :co#80:\
	:delete_character=\EN:delete_line=\EM:ei=\EO:\
	:insert_mode=\E@:li#24:mi:\
	:nod_destructive_space=\EC:hardware_tabs:se=\Eq:so=\Ep:up=\EA:\
	:vs=\Ex4\Ex1\Ej\EY8h\Ek:ve=\Ey4\Ey1:\
	:cursor_up=\EA:cursor_down=\EB:cursor_left=\ED:cursor_right=\EC:\
	:cursor_home=\EH:kn#8:\
	:insert_key=\E@:delete_key=\EN:erase_input_key=\EM:\
	:blank_gray_key=\EL:\
	:f1=\ES:f2=\ET:f3=\EU:f4=\EV:f5=\EW:\
	:f6=\EP:f7=\EQ:f8=\ER:cmd_key=\177:\
	:sgr0=\Eq:sgr1=\Ep:sgr2=\Ep:sgr4=\Ep:

tm_dnio|Travelmate 7 bit mode:\
	:f1=\E[23~:f2=\E[24~:f3=\E[25~:f4=\E[26~:f5=\E[28~:\
	:f6=\E[29~:f7=\E[31~:f8=\E[32~:f9=\E[33~:cmd_key=\EOP:\
	:up_key=\E[A:down_key=\E[B:enter_key=\037:\
	:insert_line=\CL:delete_line=\CM:\
	:back_tab_key=\EOS:left_key=\E[D:right_key=\E[C:\
	:erase_all=\E[2J:erase_eos=\E[J:erase_eol=\E[K:\
	:cursor_motion=\C%i%d;%dH:\
	:cursor_up=\E[A:cursor_down=\E[B:cursor_right=\E[C:\
	:print_screen_key=^p:redraw_screen_key=^r:\
	:back_space_key=^h:\
	:right_key=\E[C:left_key=\E[D:\
	:rtn_key=^m:\
	:up_key=\E[A:down_key=\E[B:

nc_dnio|ncsa_dnio|NCSA telnet terminal definition:\
	:f1=\EOP:f2=\EOQ:f3=\EOR:f4=\EOS:\
	:f5=\C16~:f6=\C17~:f7=\C18~:f8=\C19~:\
	:f9=\C20~:f10=\C21~:f11=\C23~:f12=\C24~:\
	:f13=\C25~:f14=\C26~:f15=\C28~:f16=\C29~:\
	:f17=\C31~:f18=\C32~:f19=\C33~:f20=\C34~:\
	:enter_key=^j:\
	:sticky_margin:\
	:cmd_key=\E?i:home_key=\E[1~:\
	:rtn_key=^m:up_key=\E[A:down_key=\E[B:\
	:left_key=\E[D:right_key=\E[C:\
	:tab_key=\t:back_tab_key=\CZ:\
	:print_screen_key=^p:redraw_screen_key=^r:\
	:insert_key=\C2~:delete_key=\C3~:\
	:cursor_solid=\C33h:cursor_blink=\C33l:\
	:erase_input_key=\E?A:erase_field_key=\E?B:blk_grey_key=\E?C:\
	:back_space_key=^h:tc=ansi_dnio:

vs_dnio|xterm_dnio|vs100_dnio|xterm terminal emulator (X Window System):\
	:f1=\C11~:f2=\C12~:f3=\C13~:f4=\C14~:f5=\C15~:f6=\C17~:\
	:f7=\C18~:f8=\C19~:f9=\C20~:f10=\C21~:.f11=\C23~:f12=\C24~:\
	:f13=\C25~:f14=\C26~:f15=\C28~:f16=\C29~:f17=\C31~:.f18=\C32~:\
	:f19=\C33~:.f20=\C34~:f21=\C35~:f22=\C36~:f23=\C37~:f24=\C38~:\
	:.f25=\C39~:.f26=\C40~:.f27=\C41~:.f28=\C42~:f29=\C43~:f30=\C44~:\
	:.f31=\C45~:.f32=\C46~:f33=\C47~:f34=\C48~:f35=\C49~:\
	:enter_key=^j:cmd_key=\C23~:rtn_key=^m:\
	:up_key=\CA:down_key=\CB:left_key=\CD:right_key=\CC:\
	:fld_rt_key=\C41~:fld_lf_key=\C42~:tab_key=^i:back_tab_key=\C39~:\
	:blk_grey_key=\C34~:erase_input_key=\C32~:skip_key=\C40~:\
	:esc_key=\C46~:back_space_key=^h:insert_key=\C2~:delete_key=\177:\
	:home_key=\CH:erase_field_key=\C45~:cursor_up=\CA:cursor_down=\CB:\
	:cursor_right=\CC:sgr1=0;7:sticky_margin:tc=ansi_dnio:

v2_dnio|xterms_dnio|vs100s_dnio|xterm terminal emulator - small:\
	:tc=xterm_dnio:

#
#
#   The following keys can be defined for each terminal type
#
#
#		 "f1","f2","f3","f4","f5","f6","f7","f8","f9","f10",
#		"f11","f12","f13","f14","f15","f16","f17","f18","f19","f20",
#		"f21","f22","f23","f24",..."f128"/* 128 function keys*/
#		"enter_key",		/* the ENTER key	*/
#		"cmd_key",		/* Command key		*/
#		"print_key",		/* PRINT key		*/
#		"rtn_key",		/* RETURN key (xenix name)*/
#		"up_key",		/* up arrow key	*/
#		"down_key",		/* down arrorw		*/
#		"left_key",		/* left arrow		*/
#		"right_key",		/* right arrow		*/
#		"fld_rt_key",		/* FIELD right		*/
#		"fld_lf_key",		/* FIELD left		*/
#		"tab_key",		/* TAB key		*/
#		"back_tab_key",		/* back tab key	*/
#		"blk_grey_key",		/* BLANK GRAY key	*/
#		"erase_input_key",	/* Erase Input key	*/
#		"skip_key",		/* SKIP key		*/
#		"esc_key",		/* ESCAPE event shift/esc */
#		"back_space_key",	/* backspace key    */
#		"insert_key",		/* insert charcter	*/
#		"delete_key",		/* delete character */
#		"home_key",		/* HOME			*/
#		"erase_field_key",	/* ERASE FIELD		*/
#		"print_screen_key",     /* print screen image   */
#		"redraw_screen_key",    /* redraw screen image  */
#
#   	The following output strings MUST be defined for 
#	minumum FE functionality:
#
#		"erase_all",	 	/* clear entire screen */
#		"erase_eos",		/* clear to end of screen */
#		"erase_eol",		/* clear to end of line */
#		"cursor_up",		/* cursor up one position */
#		"cursor_down",		/* cursor down one position */
#		"cursor_right",		/* cursor right one position */
#		"cursor_motion",	/* random cursor motion */
#
#   	The following output strings should be defined for 
#   	maximum FE functionality:
#
#		"cursor_solid",	 	/* set cursor to normal */
#		"cursor_blink",		/* set cursor to blinking */
#		"cursor_bright",	/* make cursor visible */
#		"cursor_dark",		/* make cursor invisible */
#		"sgr_mask,"		/* select graphic rendition template*/
#		"sgr0",		/* default display attributes */
#		"sgr1",		/* hi_lite */
#		"sgr2",		/* Reverse video */	
#		"sgr3",		/* Reverse video, hi_lite */
#		"sgr4",		/* Underline */
#		"sgr5",		/* Underline, hi_lite  */
#		"sgr6",		/* Underline, Reverse video */
#		"sgr7",		/* Underline, Reverse video, hi_lite */
#		"sgr8",		/* Blink */
#		"sgr9",		/* Blink, hi_lite*/
#		"sgr10",	/* Blink, Reverse video */
#		"sgr11",	/* Blink, Reverse video, hi_lite*/
#		"sgr12",	/* Blink, Underline */
#		"sgr13",	/* Blink, Underline, hi_lite*/
#		"sgr14",	/* Blink, Underline, Reverse video */
#		"sgr15",	/* Blink, Underline, Reverse video, hi_lite */
#
#		"status_line_bb",	/* status line begin bracket */
#		"status_line_eb",	/* status line end bracket */
#		"status_line_restore",	/* Restore default status line */
#
#		"open", 	/* string to send at FE_open */
#		"close", 	/* string to send at FE_close */
#		"scroll",	/* string to make screen scroll up */
#
#	The following numeric values can be used to specify a terminal 
#	that does not use the default(24/80) max row/col.
#
#		"max_row",	/* maximum row of terminal (1 relative) */
#		"max_col",	/* maximum col of terminal (1 relative) */
#
#	The following flags can be defined to tell the FE driver not to do 
#	certain optimizations.  The default mode is optimization, which will 
#	occure if the flag is not defined.  These flags should only need to be
#	specified if applications run "mixed mode" (i.e. tty and FE).
#
#		"no_sgr_opt",	/* Don't optimize sgr output */
#		"no_cm_opt",	/* Don't optimize cm output */ 
#		"no_buf_wrts",  /* Don't buffer writes */
#		"no_raw_wrts",	/* Don't set tty driver "opost" off */
#		"nodisplay_cursor", /* turn cursor off except when reading */
#
#	The following flag should be defined if the cursor does not
#	automatically wrap from column 80 to column 1 of the next line.
#	
#		"sticky_margin"	/* send cursor position at margin */



	