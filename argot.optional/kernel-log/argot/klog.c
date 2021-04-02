/*	By   Kyle  Sallee   in     2018  copyrighted.
	From other projects source code  was not        copied.
	In   the   ascript  manual page; the license is provided.
*/

#include	"ascript.h"
#include	"byte.h"
#include	"klog.h"
#include	"a.h"
#include	"sire.h"
#include	<stdnoreturn.h>
#include	<sys/klog.h>
#include	<sys/prctl.h>
#include	<time.h>

static	KLD	kld=
{	.pathname=	"/+/boot/var/log/kernel/%Y%m%d\0\0",	};

static	inline	void	logdir	(uint8_t *d)
{	uint8_t 	c,*p;
	for			(p=d;c=*p;p++)
	if		nay	(c=='/')
	{	*p=		0;
		mkdir		(d,0750);
		*p=		'/';
	}
}

__attribute__((noinline))
noreturn
SCV	klogd			(void)
{	close			(0);
	close			(1);
	close			(2);
	setsid			();
	prctl			(PR_SET_NAME,"klog");
	strncpy			(Gz.arg.v[0], "klog",strlen(Gz.arg.v[0]));

/*	munmap			(&Gz,sizeof(Gz));	*/
/* Due to errna and aide Gz must be retained */

	uint8_t		n	[PATH_MAX];

	int		s=
	klogctl			(10,NULL,0);

	uint8_t		b	[s];
	int		d;

	while			(1)
	{	s=
		klogctl		(2,b,s);
		time		(&kld.t);
		localtime_r	(&kld.t,&kld.tm);
		strftime	(n,PATH_MAX,kld.pathname,&kld.tm);
		logdir		(n);
		d=	open	(n,O_APPEND|O_CREAT|O_DSYNC|O_WRONLY,0200);
		write		(d,b,s);
		close		(d);
	}
}

SCV	klog			(void)
{	if		nay	(arga(Gz.at+0)!=arga(Gz.at+1))
	{	VMETA	*A=
		parapass	(arga(Gz.at+0));
		memcpya		(kld.pathname
				,A->textaddr
				,A->textlen+1);
	}
/*	else
	__builtin_memcpy	(kld.pathname
				,"/+/boot/var/log/kernel/%Y%m%d\0\0"
				,0x20);
*/
	pid_t		a=
	fork			();

	if			(a==0)
	klogd			();

	pids.last=		a;
	*Gz.at=			klog;
	argot_next		();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180530",
	.official=	"20180530",
	.update=	"20200907"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(klog,	"klog");
	aa_fini		();
};
