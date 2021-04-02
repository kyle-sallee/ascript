/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"sire.h"

/*	If   SA_NOCLDWAIT is specified
	then sometimes sigchld does not become.
	For  more than one process termination
	a    single sigchld signal might become.
	Therefore, to gain the exit code for every process
	an explicit wait is required and momentarily zombies can become.
*/

__attribute__((noinline))
SCV	visit				(pid_t p)
{	target_object_to_stack		();
	Gz.to[0]=			pids.target[p];
	Gz.to[1]=			pids.origin[p];

	void		(**L)	(void)=	Gz.at;
/*	Gz.sigin++;	*/
	(*(Gz.at=	pids.pin[p]))	();
/*	Gz.sigin--;	*/
	Gz.at=				L;
	target_object_from_stack	();
}

SCV	schld					(int x)
{	if				nay	(pids.skip)
	{		pids.miss=		1;
			return;
	}

	int			e=		errna;

	while					(1)
	{	siginfo_t	t;
		t.si_pid=			0;
		t.si_status=			0;
		waitid				(P_ALL,0,&t,WEXITED|WNOHANG);
		if			nay	(t.si_pid==0)
		{	errna=			e;
			return;
		}

		pids.exit[0]|=			t.si_status;

		pid_t		p=		t.si_pid;
		pids.exit[p]=			t.si_status;

		pids.stop[p]=			 (t.si_code==CLD_STOPPED);

		uint8_t
		d=				 (t.si_code==CLD_EXITED);
		d|=				-(t.si_code==CLD_KILLED);
		d|=				-(t.si_code==CLD_DUMPED);

		pids.now-=			(d!=0);
		pids.done[p]=			d;

		if			nay	(pids.pin[p]!=NULL)
		visit				(p);
	}
}

SCV	sirecontwait		(void)
{	pid_t		p=	Gz.to[0]->host->value.i;
	pids.skip=		1;
	waitthis		(p,WEXITED|WNOWAIT|WCONTINUED);
	*Gz.at=			sirecontwait;
	argot_next		();
}

SCV	siredonewait		(void)
{	pid_t		p=	Gz.to[0]->host->value.i;
	waitthis		(p,WEXITED|WNOWAIT);
	*Gz.at=			siredonewait;
	argot_next		();
}

SCV	sirestopwait		(void)
{	pid_t		p=	Gz.to[0]->host->value.i;
/*	pids.skip=		1;	*/
	waitthis		(p,WEXITED|WNOWAIT|WSTOPPED);
	*Gz.at=			sirestopwait;
	argot_next		();
}

SCV	sirecont		(void)
{	pid_t		p=	Gz.to[0]->host->value.i;
	sigqueue		(p,SIGCONT,(union sigval){.sival_int=0});
	*Gz.at=			sirecont;
	argot_next		();
}

SCV	sirestop		(void)
{	pid_t		p=	Gz.to[0]->host->value.i;
	sigqueue		(p,SIGSTOP,(union sigval){.sival_int=0});
	*Gz.at=			sirestop;
	argot_next		();
}

SCV	done	(void)	{tsubab(donesubnew,done);}
SCV	exit_	(void)	{tsubab(exitsubnew,exit_);}
SCV	stop	(void)	{tsubab(stopsubnew,stop);}
SCV	sire	(void)	{tvarnewab(siresubnew,sire);}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20181012",
	.official=	"20181012",
	.update=	"20200920"
};

SCV	action_init		(void)
{	Gz.sa[0].sa_flags=	SA_RESTART;
	Gz.sa[0].sa_handler=	schld;
	Gz.sig[SIGCHLD]=	(void *)	-1;
	sigaction		(SIGCHLD,Gz.sa,NULL);
}

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(sire,		"sire");
	aa		(done,		"siredone");
	aa		(exit_,		"sireexit");
	aa		(stop,		"sirestop");
	aa		(sirecont,	"sirecont");
	aa		(sirestop,	"sirestop");
	aa		(sirecontwait,	"sirecontwait");
	aa		(sirestopwait,	"sirestopwait");
	aa		(siredonewait,	"siredonewait");
	aa_fini		();
	action_init	();
};
