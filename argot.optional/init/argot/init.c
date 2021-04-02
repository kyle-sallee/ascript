/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"sire.h"
#include	<sched.h>
#include	<sys/ioctl.h>

SCV	initroot			(void)
{	if				(fork()==0)
	{	sched_yield		();
		argot_next		();
		return;
	}

	ioctl				(0,TIOCNOTTY);
	close				(0);
	close				(1);
	open				("/dev/console",O_NOCTTY|O_RDONLY);
	open				("/dev/console",O_NOCTTY|O_WRONLY);
	dup2				(1,2);
	execv				("/sbin/initroot",(char **)Gz.arg.v);
	warn				("/sbin/initroot execution failed");
	_exit				(errna);
}

SCV	initreal		(void)
{	pid_t	volatile
	*pv=
	mmapmust		(PAGE,PROT_READ|PROT_WRITE,
				 MAP_ANONYMOUS|MAP_SHARED,-1);
	pid_t		p=
	fork			();

	if			(p>0)
	{	while		((p=*pv)==0)
		sched_yield	();
		pids.last=	p;
		munmap		((void *)pv,PAGE);
		*Gz.at=		initreal;
		argot_next	();
		return;
	}
	else
	if	nay		(0>p)
	{	warn		("%-19s %-40s","fork",
				 "argot initreal process creation 0 failed");
		warn		("/sbin/initreal will not be executed.");
		argot_next	();
		return;
	}


	/*	In   the Linux kernel configuration
		each namespace if not enabled
		then function  unshare invocations can fail.
		Thus with individual name space associated flags
		the  unshared function is invoked.
		The  unsupported namespace selections fail.
	*/

	uint8_t		*d=	Gz.to[0]->textaddr;
	chdir			(d);
	chroot			(".");

/* new */
/*
#ifdef	CLONE_NEWUSER
	unshare			(CLONE_NEWUSER);
#endif
*/

#ifdef	CLONE_NEWIPC
	unshare			(CLONE_NEWIPC);
#endif

#ifdef	CLONE_NEWNET
	unshare			(CLONE_NEWNET);
#endif

#ifdef	CLONE_NEWNS
	unshare			(CLONE_NEWNS);
#endif

#ifdef	CLONE_NEWUTS
	unshare			(CLONE_NEWUTS);
#endif

/* new */
/*
#ifdef	CLONE_FILES
	unshare			(CLONE_FILES);
#endif
*/

/* new */
/*
#ifdef	CLONE_FS
	unshare			(CLONE_FS);
#endif
*/

/* new */
#ifdef	CLONE_NEWCGROUP
	unshare			(CLONE_NEWCGROUP);
#endif

/* new */
#ifdef	CLONE_SYSVSEM
	unshare			(CLONE_SYSVSEM);
#endif

#ifdef	CLONE_NEWPID
	unshare			(CLONE_NEWPID);
#endif

	/*	From file setsid.2,
		"In order to be sure that setsid() will succeed,
		fork(2) and _exit(2), and have the child do setsid().
	*/

	pid_t		q=
	fork			();

	if		yay	(q>0)
	{	*pv=		q;
		_exit		(0);
	}
	else
	if		nay	(0>p)
	{	*pv=		p;
		warn		("%-19s %-40s",
				 "fork",
				 "argot initreal process creation 1 failed");
		warn		("/sbin/initreal execution will still be attempted.");
	}

	setsid			();
/* The setsid aft invocation the ioctl TIOCNOTTY is not required? */
/*	ioctl			(1,TIOCNOTTY);	*/
	close			(0);
	close			(1);
	open			("/dev/console",O_NOCTTY|O_RDONLY);
	open			("/dev/console",O_NOCTTY|O_WRONLY);
	dup2			(1,2);
	execv			("/sbin/initreal",(char * const[])
				{"/sbin/initreal",NULL});
	warn			("/sbin/initreal execution failed");
	_exit			(errna);
}

static		void	init	(void)	{argot_next();}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20171007",
	.official=	"20171007",
	.update=	"20200625"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(init,		"init");
	aa		(initreal,	"initreal");
	aa		(initroot,	"initroot");
	aa_fini		();
};
