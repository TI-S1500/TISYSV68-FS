/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
#ident "@(#)qtrio.h	1.3 (TI) 91/05/17"
#endif	SCCSID

/*
 * Structures and definitions for mag tape io control commands
 */

/* structure for QTRIOCTOP - 1/4-inch tape op command */

struct	qtrop	{
	long	qtr_op;		/* operations defined below */
	long	qtr_count;	/* how many of them */
	char   *qtr_param;      /* parameters, if any */
	int	qtr_dir;	/* transfer direction */
};

/* operations: */
#define QTRWEOF	 0	/* write an end-of-file record */
#define QTRFSF	 1	/* forward space file */
#define QTRBSF	 2	/* backward space file */
#define QTRFSR	 3	/* forward space record */
#define QTRBSR	 4	/* backward space record */
#define QTRREW	 5	/* rewind */
#define QTROFFL	 6	/* rewind and put the drive offline */
#define QTRNOP   7      /* nop */
#define QTRERASE 8      /* erase to end of tape */
#define QTRPASSTHR 9    /* scsi pass-through command */

/* transfer direction */
#define QTRREAD  1	/* read direction, drive to host */
#define QTRWRITE 0	/* write direction, host to drive */

/* controller pass-through command block structure */
struct pass_through_cmd {	    /* ctrl pass-through cmd block structure */
	char *data_ptr;		    /* ptr to data area to read/wrt from/to */
	unsigned long data_len;     /* length of data area */
	char *scsi_status;          /* ptr to memory to put scsi cmd status in*/
	unsigned long status_len;   /* scsi cmd status length */
	struct scsi_cmd_6 *cmd_ptr; /* ptr to scsi cmd block */
	unsigned long cmd_len;	    /* scsi cmd block length */
	};

/*  structure used for building SOME 6 byte SCSI commands */
struct scsi_cmd_6 {		/* scsi 6 byte cmd block structure */
	unsigned long opcode: 8,    /* operation to be performed */
		      lun: 3,	    /* logical scsi unit number */
		      blk_addr: 21; /* logical blk address */
	char length;		    /* xfer/parameter/allocation length */
	char control;		    /* control byte */
	};

#define	INQUIRY		0x12		/* inquiry cmd opcode */


/*  Inquiry data structure containing returned inquiry data.  */
struct inquiry_data {			/* see the SCSI spec for field defs */
	unsigned char p_qualifier: 3,	/* peripheral qualifier */
	             p_devtype: 5;	/* peripheral device type */
	unsigned char rmb: 1,		/* removable media bit */
		     devtype_mod: 7;	/* device type modifier (scsi-1) */
	unsigned char iso_vers: 2,	/* ISO version */
		     ecma_vers: 3,	/* ECMA version */
		     ansi_vers: 3;	/* ANSI apporved version */
	unsigned char aenc: 1,		/* asynch event notification bit */
		     trmiop: 1,		/* terminate IO process msg support */
		     reserved0: 2,	/* reserved bits */
		     resp_data_fmt: 4;	/* response data format(0=scsi-1 fmt) */
	unsigned int add_length: 8,	/* additional length */
			reserved1: 8,	/* reserved byte */
			reserved2: 8,	/* reserved byte */
			reladr: 1,	/* relative addr mode (=1) bit*/
			wbus32: 1,	/* 32 bit wide data xfer bus (=1) */
			wbus16: 1,	/* 16 bit wide data xfer bus (=1) */
			sync: 1,	/* synchronous data xfers (=1) */
			linked: 1,	/* linked command supported (=1) */
			reserved3: 1,	/* reserved bit */
			cmdque: 1,	/* tagged command queueing (=1) */
			sftre: 1;	/* soft reset option supported (=1) */
	unsigned char vendor_ident[8];	/* vendor identification bytes */
	unsigned char product_ident[16];/* product identification bytes */
	unsigned char product_rev[4];	/* product revision level */
	unsigned char vendor_specific[20]; /* vendor specific bytes */
	unsigned char reserved4[40];	/* reserved bytes */
	unsigned char vendor_spec_param[50]; /* vendor specific param bytes */
	};

#define TPTYPE_BITS(mdev) ((mdev>>16)&0x1f) /* Shift & mask NEW tape mode bits*/
