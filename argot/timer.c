/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"timer.h"

SCV	timerinit			(void)
{	VMETA		*A=		Gz.to[0];
	TDATA		*a=
	tdata				(A);

	VMETA		*B=		a->sig;
	a->s.sigev_signo=		B->value.i;

/*	a->i.it_value.tv_sec=		a->it_value_tv_sec.i;
	a->i.it_value.tv_nsec=		a->it_value_tv_nsec.i;
	a->i.it_interval.tv_sec=	a->it_interval_tv_sec.i;
	a->i.it_interval.tv_nsec=	a->it_interval_tv_nsec.i;
*/

	if			yay	((a->i.it_value.tv_sec|
					  a->i.it_value.tv_nsec)==0)
	{	a->i.it_value.tv_sec=	a->i.it_interval.tv_sec;
		a->i.it_value.tv_nsec=	a->i.it_interval.tv_nsec;
	}

	clockid_t	c=		a->clockid.i;
	int		f=		a->flags.i;

	timer_create			(c,&a->s,&a->t);
	timer_settime			(         a->t,f,&a->i,NULL);
	*Gz.at=				timerinit;
	argot_next			();
}

SCV	timerabsolute		(void)
{	VMETA		*A=	Gz.to[0];
	TDATA		*a=
	tdata			(A);
	a->flags.i=		TIMER_ABSTIME;
	*Gz.at=			timerabsolute;
	argot_next		();
}

SCV	timerfini		(void)
{	VMETA		*A=	Gz.to[0];
	timerrelease		(A);
	*Gz.at=			timerfini;
	argot_next		();
}

__attribute__((always_inline))
static	inline	void	tc	(clockid_t a,void (*b)(void))
{	VMETA		*c=	Gz.to[0];
	TDATA		*d=
	tdata			(c);
	d->clockid.i=		a;
	*Gz.at=		b;
	argot_next		();
}

SCV	timerreal	(void){tc(CLOCK_REALTIME,timerreal);}
SCV	timermono	(void){tc(CLOCK_REALTIME,timermono);}
SCV	timerprocess	(void){tc(CLOCK_REALTIME,timerprocess);}
SCV	timerthread	(void){tc(CLOCK_REALTIME,timerthread);}
SCV	_timer		(void){tvarnewab(timersubnew,_timer);}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180528",
	.official=	"20180528",
	.update=	"20200811"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(_timer,	"timer");
	aa		(timerreal,	"timerreal");
	aa		(timermono,	"timermono");
	aa		(timerprocess,	"timerprocess");
	aa		(timerthread,	"timerthread");
	aa		(timerabsolute,	"timerabsolute");
	aa		(timerfini,	"timerfini");
	aa		(timerinit,	"timerinit");
	aa_fini		();
};
