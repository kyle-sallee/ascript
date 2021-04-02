/*	By Kyle Sallee from 2019 copyrighted.
*/

/*	On a script interpreter
	the suid bit
	must never be enabled.
*/

#include	"ascript.h"

__attribute__((constructor))
static	CALIGN	void	bold_init	(void)
{	if	nay	(getuid()!=geteuid())
	err		(errno=EPERM,"getuid()!=geteuid()  "
			 "SUID ascript probable.  "
			 "Process terminating.");
}
