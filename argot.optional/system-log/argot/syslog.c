/*	By   Kyle  Sallee   in     2018  copyrighted.
	From other projects source code  was not        copied.
	In   the   ascript  manual page; the license is provided.
*/

#include	"ascript.h"
#include	"byte.h"
#include	"int.h"
#include	"a.h"
#include	"sire.h"
#include	"syslog.h"
#include	<stdnoreturn.h>
#include	<sys/prctl.h>
#include	<sys/socket.h>
#include	<sys/un.h>
#include	<time.h>

static	SLD	sld;

SCV	not_message		(void)
{	int		a=	errna;
	errna=			0;
	openlog			(sld.self.textaddr,
				 LOG_CONS|LOG_NDELAY|LOG_PID,
				 sld.priority);

	sld.message.textaddr[
	sld.message.textlen]=0;

	syslog			(sld.priority,"%s",sld.message.textaddr);
	sld.message.textlen=	0;
	closelog		();

	int		b=	errna;
	errna=			a;
	if		nay	(b!=0)
	sld.message.io.success=	b;

	*Gz.at=			not_message;
	argot_next		();
}

SCV	action_pipe		(int s,siginfo_t *i,void *v)
{	int		a=	errna;
	errna=			0;
	openlog			(sld.self.textaddr,
				 LOG_CONS|LOG_NDELAY|LOG_PID,
				 sld.priority);

	ssize_t		b;
	while			((b=read(	sld.p[2],
						sld.mess,
					sizeof(	sld.mess)-1))>0)
	{	sld.mess[b]=	0;
		syslog		(sld.priority,"%s",a);
	}

	closelog		();
	int		c=	errna;
	errna=			a;
	if		nay	(c!=0)
	sld.message.io.success=	c;
}

static	inline	void	logdir		(uint8_t *d)
{	uint8_t 	c,*p;
	for				(p=d;c=*p;p++)
	if			nay	(c=='/')
	{	*p=			0;
		mkdir			(d,0750);
		*p=			'/';
	}
}

static	inline	void	save	(void)
{	time			(&sld.t);
	localtime_r		(&sld.t,&sld.tm);
	strftime		(sld.logname,PATH_MAX,
				 sld.pathname.textaddr,
				&sld.tm);
	logdir			(sld.logname);

	int		a=
	open			(sld.logname,
				 O_APPEND|O_CREAT|O_DSYNC|O_WRONLY,0200);
	sld.mess[
	sld.mess_len]=		'\n';
	write			(a,sld.mess,sld.mess_len+1);
	close			(a);
}

SCV	action_socket		(int s,siginfo_t *i,void *v)
{	sld.mess_len=
	read			(sld.socket,
				 sld.mess,sizeof(
				 sld.mess)-1);

	if		yay	(sld.mess_len>0)
	save			();
}

noreturn
inline
static	CALIGN	int	syslogd		(void *z)
{	close				(0);
	close				(1);
	close				(2);
	setsid				();

	prctl				(PR_SET_NAME,"syslog");
	strncpy				(Gz.arg.v[0], "syslog",strlenb(Gz.arg.v[0]));

	int		s;
	for				(s=SIGRTMIN;Gz.sig[s];s++);
	Gz.sig[s]=			&sld;

	Gz.sa[0].sa_sigaction=		action_socket;
	Gz.sa[0].sa_flags=		SA_RESTART;
	sigaction			(s,		Gz.sa,NULL);
	sigaction			(SIGCHLD,	Gz.sa,NULL);

	CALIGN
	static	struct	sockaddr_un	a=
	{	.sun_family=	AF_UNIX,
		.sun_path=	"/dev/log"
	};

	unlink				(a.sun_path);

	int		k=
	socket				(AF_UNIX,SOCK_DGRAM|SOCK_NONBLOCK,0);
	if			nay	(0>k)
	err				(errna,"socket");

	sld.socket=			k;

	int		r=
	bind				(k,
					 (struct sockaddr *)&a,
					 sizeof(struct sockaddr_un));

	if			nay	(0>r)
	err				(errna,"bind");

/*	fchmod				(k,0666);		*/
/* fchmod did not work */
	chmod				("/dev/log",0666);
        fcntl				(k,F_SETOWN,gettid_());
        fcntl				(k,F_SETFL,O_ASYNC|O_NONBLOCK);
        fcntl				(k,F_SETSIG,s);

/*	munmap				(&Gz,sizeof(Gz));
*/
/*
The Gz global var
if unmapped errna and aide functions
can not be used
*/

	while				(1)
	pause				();
}


__attribute__((unused))
SCV	sysloginit		(void)
{	pid_t		a=
	fork			();

	if			(a==0)
	syslogd			(NULL);

	pids.last=		a;
	argot_next		();
}

SCV	syslogpipe		(void)
{	if		nay	(sld.pipe.name[0]!=0)
	{	argot_next	();
		return;
	}

	pipe2			(sld.p,O_DIRECT);
	sld.p[2]=	fcntl	(sld.p[0],F_DUPFD_CLOEXEC,FDHIGH);
	sld.p[3]=	fcntl	(sld.p[1],F_DUPFD_CLOEXEC,FDHIGH);
	close			(sld.p[0]);
	close			(sld.p[1]);
        fcntl   		(sld.p[2],F_SETOWN,getpid());
        fcntl   		(sld.p[2],F_SETFL,O_ASYNC|O_NONBLOCK);

	int			a;
	for			(a=SIGRTMIN;Gz.sig[a];a++);
	Gz.sig[a]=		&sld;

	Gz.sa[0].sa_sigaction=	action_pipe;
	Gz.sa[0].sa_flags=	SA_RESTART;
	sigaction		(a,Gz.sa,NULL);
        fcntl   		(sld.p[2],F_SETSIG,a);

	sld.pipe.len=		0xb;
	__builtin_memcpy	(sld.pipe.name,"syslog.pipe",0xb);
	map_init		(&sld.pipe);
	int4init		(&sld.pipe);
	sld.pipe.value.i=	sld.p[3];
	vattach			(&sld.pipe);
	argot_next		();
}

SCV	syslogself		(void)
{	if		nay	(sld.self.name[0]!=0)
	{	argot_next	();
		return;
	}

	sld.self.len=		0xb;
	__builtin_memcpy	(sld.self.name,"syslog.self",0xc);
	byteinit		(&sld.self);
	vattach			(&sld.self);
	argot_next		();
}

SCV	syslogpathname		(void)
{	if		nay	(sld.pathname.name[0]!=0)
	{	argot_next	();
		return;
	}

	sld.pathname.len=	0xf;
	__builtin_memcpy	(sld.pathname.name,"syslog.pathname",0x10);

	byteinit		(&sld.pathname);
	vattach			(&sld.pathname);
	argot_next		();
}

SCV	LOG_AUTH_	(void)
{	sld.priority&=	0x7;
	sld.priority|=	LOG_AUTH;
	*Gz.at=		LOG_AUTH_;
	argot_next	();
}

SCV	LOG_AUTHPRIV_	(void)
{	sld.priority&=	0x7;
	sld.priority|=	LOG_AUTHPRIV;
	*Gz.at=		LOG_AUTHPRIV_;
	argot_next	();
}

SCV	LOG_CRON_	(void)
{	sld.priority&=	0x7;
	sld.priority|=	LOG_CRON;
	*Gz.at=		LOG_CRON_;
	argot_next	();
}

SCV	LOG_DAEMON_	(void)
{	sld.priority&=	0x7;
	sld.priority|=	LOG_DAEMON;
	*Gz.at=		LOG_DAEMON_;
	argot_next	();
}

SCV	LOG_FTP_	(void)
{	sld.priority&=	0x7;
	sld.priority|=	LOG_FTP;
	*Gz.at=		LOG_FTP_;
	argot_next	();
}

SCV	LOG_KERN_	(void)
{	sld.priority&=	0x7;
	sld.priority|=	LOG_KERN;
	*Gz.at=		LOG_KERN_;
	argot_next	();
}

SCV	LOG_LPR_	(void)
{	sld.priority&=	0x7;
	sld.priority|=	LOG_LPR;
	*Gz.at=		LOG_LPR_;
	argot_next	();
}

SCV	LOG_MAIL_	(void)
{	sld.priority&=	0x7;
	sld.priority|=	LOG_MAIL;
	*Gz.at=		LOG_MAIL_;
	argot_next	();
}

SCV	LOG_NEWS_	(void)
{	sld.priority&=	0x7;
	sld.priority|=	LOG_NEWS;
	*Gz.at=		LOG_NEWS_;
	argot_next	();
}

SCV	LOG_SYSLOG_	(void)
{	sld.priority&=	0x7;
	sld.priority|=	LOG_SYSLOG;
	*Gz.at=		LOG_SYSLOG_;
	argot_next	();
}

SCV	LOG_USER_	(void)
{	sld.priority&=	0x7;
	sld.priority|=	LOG_USER;
	*Gz.at=		LOG_USER_;
	argot_next	();
}

SCV	LOG_UUCP_	(void)
{	sld.priority&=	0x7;
	sld.priority|=	LOG_UUCP;
	*Gz.at=		LOG_UUCP_;
	argot_next	();
}

SCV	LOG_EMERG_	(void)
{	sld.priority&=	~0x7;
	sld.priority|=	LOG_EMERG;
	*Gz.at=		LOG_EMERG_;
	argot_next	();
}

SCV	LOG_ALERT_	(void)
{	sld.priority&=	~0x7;
	sld.priority|=	LOG_ALERT;
	*Gz.at=		LOG_ALERT_;
	argot_next	();
}

SCV	LOG_CRIT_	(void)
{	sld.priority&=	~0x7;
	sld.priority|=	LOG_CRIT;
	*Gz.at=		LOG_CRIT_;
	argot_next	();
}

SCV	LOG_ERR_	(void)
{	sld.priority&=	~0x7;
	sld.priority|=	LOG_ERR;
	*Gz.at=		LOG_ERR_;
	argot_next	();
}

SCV	LOG_WARNING_	(void)
{	sld.priority&=	~0x7;
	sld.priority|=	LOG_WARNING;
	*Gz.at=		LOG_WARNING_;
	argot_next	();
}

SCV	LOG_NOTICE_	(void)
{	sld.priority&=	~0x7;
	sld.priority|=	LOG_NOTICE;
	*Gz.at=		LOG_NOTICE_;
	argot_next	();
}

SCV	LOG_INFO_	(void)
{	sld.priority&=	~0x7;
	sld.priority|=	LOG_INFO;
	*Gz.at=		LOG_INFO_;
	argot_next	();
}

SCV	LOG_DEBUG_	(void)
{	sld.priority&=	~0x7;
	sld.priority|=	LOG_DEBUG;
	*Gz.at=		LOG_DEBUG_;
	argot_next	();
}

static		void	_syslog	(void)
{	*Gz.at=		_syslog;
	argot_next	();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180531",
	.official=	"20180531",
	.update=	"20200907"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(_syslog,		"syslog");
	aa		(sysloginit,		"sysloginit");
	aa		(syslogpathname,	"syslogpathname");
	aa		(syslogpipe,		"syslogpipe");
	aa		(syslogself,		"syslogself");
	aa		(LOG_AUTH_,		"LOG_AUTH");
	aa		(LOG_AUTHPRIV_,		"LOG_AUTHPRIV");
	aa		(LOG_CRON_,		"LOG_CRON");
	aa		(LOG_DAEMON_,		"LOG_DAEMON");
	aa		(LOG_FTP_,		"LOG_FTP");
	aa		(LOG_KERN_,		"LOG_KERN");
	aa		(LOG_LPR_,		"LOG_LPR");
	aa		(LOG_MAIL_,		"LOG_MAIL");
	aa		(LOG_NEWS_,		"LOG_NEWS");
	aa		(LOG_SYSLOG_,		"LOG_SYSLOG");
	aa		(LOG_USER_,		"LOG_USER");
	aa		(LOG_UUCP_,		"LOG_UUCP");
	aa		(LOG_EMERG_,		"LOG_EMERG");
	aa		(LOG_ALERT_,		"LOG_ALERT");
	aa		(LOG_CRIT_,		"LOG_CRIT");
	aa		(LOG_ERR_,		"LOG_ERR");
	aa		(LOG_WARNING_,		"LOG_WARNING");
	aa		(LOG_NOTICE_,		"LOG_NOTICE");
	aa		(LOG_INFO_,		"LOG_INFO");
	aa		(LOG_DEBUG_,		"LOG_DEBUG");
	aa_fini		();
};

__attribute__((constructor))
SCV	init			(void)
{	sld.opsyslog[0]=	opbyte[0];
	sld.opsyslog[0].not=	not_message;

	sld.priority=		LOG_INFO|LOG_USER;

	map_init		(&sld.pathname);
	map_init		(&sld.message);
	map_init		(&sld.self);
	sld.self.textaddr=	  sld.selfname;

	sld.message.op=		sld.opsyslog;
	sld.message.io.flag=	textmapuse;
	sld.message.len=	6;
	__builtin_memcpy	(sld.message.name,"syslog\0",8);
	vattach			(&sld.message);

	sld.pathname.textlen=0x1d;
	__builtin_memcpy	(sld.pathname.text,
				 "/+/boot/var/log/system/%Y%m%d\0\0",0x20);

	sld.self.textlen=
	strlenb			(			Gz.arg.v[1]);
	memcpya			(sld.self.textaddr,	Gz.arg.v[1],
				 sld.self.textlen);
}
