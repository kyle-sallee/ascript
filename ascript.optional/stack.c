/*	By Kyle Sallee 2019 copyrighted.
	By ascript and
	by argot
	rather than
	by call
	by jmp
	code addresses are often reached.

	The  stack size
	when reduced
	by   excessive unexpected call instruction emission
	the  stack
	will underflow.
	When underflown
	a    segfault
	is   solicited.

	For most Linux configurations
	the default stack size is 8 megabytes
	the hard limit is 2 gigabytes.

	A    64 megabyte stack size default
	when requested
	no   harm becomes.
	More than 6      megabytes
	is   rarely      used.
	By   larger stack size
	the  virtual use increases.
	But until required
	the RAM is not paged in.
	More succinctly stated
	for the larger stack boon
	additional RAM
	is not consumed.

	By  ascript
	not for data    holding,
	but for address holding,
	the stack
	is  used.
*/

#include	"ascript.h"
#include	<sys/time.h>
#include	<sys/resource.h>

#define	MUCH	0x4000000	/* 64 megabytes */
#define	SOME	0x100000;	/*  1 megabyte	*/
#define	SCANT	0x10000;	/* 64 kilobytes */

__attribute__((constructor))
static	CALIGN	void	stack_expand	(void)
{	struct	rlimit	r;
	getrlimit		(RLIMIT_STACK,&r);
	r.rlim_cur=		MUCH;
	setrlimit		(RLIMIT_STACK,&r);
}
