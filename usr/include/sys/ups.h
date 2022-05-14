/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ident	"@(#)ups.h	1.4 91/02/14"

/* ioctl arg struct */
struct	UPS	{
			char 	otemp_on;
			int 	cpu_type;
			char 	got_irq;
			char	fw_on;
			char	otemp_shutdown;
			char	on_batteries;
			int 	gpio;
		};

/* ioctl commands */
#define	UPS_ON  	120
#define	UPS_OFF 	121
#define	UPS_GETF 	122
#define	UPS_OTPFON	123
#define	UPS_OTPFOFF	124
#define	UPS_FWON	125
#define	UPS_FWOFF	126

#define	UPS_BIT_MASK	0x00200000		/* UPS active bit mask for GPIO */
