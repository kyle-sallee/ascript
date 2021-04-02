/*	By Kyle Sallee from 2015 ... 2019 copyrighted.
	Used by ascript.c and argots
	By bliss some signals that might be received
	yet if uncaught would terminate ascript
	are caught and ignored.
*/

/*	blissful ignorance
	if enabled
	by some SA errors
	the ascript process
	will not be killed.
*/

#include	"ascript.h"

static		void	bliss		(int,siginfo_t *,void *);

__attribute__((constructor))
static	CALIGN	void	sig_init	(void)
{	static	const
	struct	sigaction	a=
	{	.sa_flags=		SA_SIGINFO,
		.sa_sigaction=		bliss
	};
	sigaction			(SIGHUP ,&a,NULL);
	sigaction			(SIGPIPE,&a,NULL);
	sigaction			(SIGUSR1,&a,NULL);
	sigaction			(SIGUSR2,&a,NULL);
}

__attribute__((cold))
static		void	bliss		(int a,siginfo_t *b,void *c)
{
/*	warnx	("SIGNAL %i received",a);	*/
}
