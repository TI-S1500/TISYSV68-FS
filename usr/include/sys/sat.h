/*
	(C) COPYRIGHT, TEXAS INSTRUMENTS INCORPORATED, 1985.  ALL
	RIGHTS RESERVED.  PROPERTY OF TEXAS INSTRUMENTS INCORPORATED.
	RESTRICTED RIGHTS - USE, DUPLICATION, OR DISCLOSURE IS SUBJECT
	TO RESTRICTIONS SET FORTH IN TI'S PROGRAM LICENSE AGREEMENT AND
	ASSOCIATED DOCUMENTATION.
*/

#ifdef	SCCSID
static char sat_h[] = "@(#)sat.h	1.3 (TI) 86/02/04";
#endif	SCCSID

#define NENTS 84
struct sat_ent {
	daddr_t start;
	daddr_t addr;		/* disk address of beginning of extent */
	int unwcount;		/* number of unwritten blocks */
};

struct sat {
	char s_flags;		/* flags (for future use) */
	char s_nents;		/* Index in stab of where last extent is. */
	short fill1;
	int fill2[3];
	struct sat_ent s_tab[NENTS]; /* extent table */
};	
#define SATALL 1		/* allocation modification done */
/*
 * last extent is the size of the file in blocks, and is always marked as
 * unallocated.  Note that the size in blocks is numerically equal to the
 * first unaddressable block.
*/

/*
 * there can be 4 sats.  They are pointed to out of a table in the inode
 * managed out of the i_addr array.  There are up to 4 2-word entries.
 * The first word is the start block number relative to file beginning
 * of where the sat starts (same contents as the s_tab[0].start field).
 * the second word is the disk address of the sat itself.
 */
