/************************************************************************/
/*      (C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1992.  ALL       */
/*      RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.   */
/*      RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT  */
/*      TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND */
/*      ASSOCIATED DOCUMENTATION.                                       */
/************************************************************************/

/* This is the header file for console logging */

/* values for logcon */
#define CL_DP       0  /* do not log console msgs */
#define CL_LOGKERN  1  /* log kernel msgs (printfs) */
#define CL_LOGALL   2  /* log all console msgs */

/* cnl driver ioctl opcodes */
#define SETOPENFLG   1
#define CHKOPENFLG   2
#define GETCREC      3
#define SETLOGDPIN   4
#define RESETLOGDPIN 5

/* printfx flag values */
#define PF_LOG 0  /* prints to the system console and to the console
                   *  log if the cband parameter "console" selects it.
                   */
#define PF_CR  1  /* prints to the system console and to the current
                   *  crash record in NVRAM. This is used by panic and by
                   *  code that prints panic info just prior to a panic. 
                   */
#define PF_CON 2  /* prints to the system console only, regardless of
                   *  the value of the cband parameter "console". 
                   * This is used only in very special cases, such
                   *  as in the console logging code itself.
                   */
