/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"int.h"
#include	<sys/socket.h>
#include	<sys/un.h>

#define		IFA_FAMILY	AF_UNIX
#define		SOCKADDR_IN	struct	sockaddr_un
#define		SUN_PATH(a)	((SOCKADDR_IN *)(a))->sun_path
#define		SUN_FAMILY(a)	((SOCKADDR_IN *)(a))->sun_family

static	VMETA	SS[2]=
{{.name="sockrecv",.len=8,.op=opint8},
 {.name="socksend",.len=8,.op=opint8}};


SCV	sockfree	(VMETA *A)
{	if		(A->value.i4.l>0)
	close		(A->value.i4.l);
	var_free	(A);
}

ALIVE	dgraminit			(VMETA *A)
{	A->free=			sockfree;
	int4init			(A);
	errna=				0;
	A->value.i4.l=
	socket				(IFA_FAMILY
					,SOCK_DGRAM|SOCK_NONBLOCK|SOCK_CLOEXEC
					,0);
	A->io.success=			errna;
	map_add				(A,0,PAGE);
	SUN_FAMILY(A->dataaddr)=	IFA_FAMILY;
}

ALIVE	streaminit			(VMETA *A)
{	A->free=			sockfree;
	int4init			(A);
	errna=				0;
	A->value.i4.l=
	socket				(IFA_FAMILY
					,SOCK_STREAM|SOCK_NONBLOCK|SOCK_CLOEXEC
					,0);
	A->io.success=			errna;
	map_add				(A,0,PAGE);
	SUN_FAMILY(A->dataaddr)=	IFA_FAMILY;
}

ALIVE	acceptinit			(VMETA *A)
{	A->free=			sockfree;
	A->host=			Gz.to[1];
	int4init			(A);
	socklen_t	addrlen=
	sizeof				(struct sockaddr_un);
	errna=				0;
	A->value.i4.l=
	accept4				(A->host->value.i4.l
					,(struct sockaddr_un *)
					A->host->dataaddr
					,&addrlen
					,SOCK_CLOEXEC);
	A->io.success=			errna;
	map_add				(A,0,PAGE);
	SUN_FAMILY(A->dataaddr)=	IFA_FAMILY;
}

SCV	sockdgram	(void){tvarnewa	(dgraminit);}
SCV	sockstream	(void){tvarnewa	(streaminit);}
SCV	sockaccept	(void){tvarnewa	(acceptinit);}

SCV	sock		(void)
{	*Gz.at=		sock;
	argot_next	();
}

SCV	sockbind		(void)
{	VMETA		*A=	Gz.to[0],
			*B=	Gz.to[1];
	__builtin_memcpy	(SUN_PATH(A->dataaddr)
				,B->textaddr
				,sizeof(((struct sockaddr_un *)	A->dataaddr)->sun_path));

	errna=			0;
	int		e=
	bind			(A->value.i4.l
				,	(struct sockaddr_un *)	A->dataaddr
				,sizeof	(struct sockaddr_un));
	A->io.success=		errna;
	*Gz.at=			sockbind;
	argot_jump		(e==0);
}

SCV	socklisten		(void)
{	VMETA		*A=	Gz.to[0],
			*B=	Gz.to[1];
	errna=			0;
	int		e=
	listen			(A->value.i4.l
				,B->value.i4.l);
	A->io.success=		errna;
	*Gz.at=			socklisten;
	argot_jump		(e==0);
}

SCV	sockconnect		(void)
{	VMETA		*A=	Gz.to[0],
			*B=	Gz.to[1];
	__builtin_memcpy	(SUN_PATH(A->dataaddr)
				,B->textaddr
				,sizeof(((struct sockaddr_un *)	A->dataaddr)->sun_path));

	errna=			0;
	int		e=
	connect			(A->value.i4.l
				,	(struct sockaddr_un *)	A->dataaddr
				,sizeof	(struct sockaddr_un));
	A->io.success=		errna;
	*Gz.at=			sockconnect;
	argot_jump		(e==0);
}

SCV	socksend		(void)
{	errna=			0;
	ssize_t		a=
	send			(Gz.to[0]->value.i4.l
				,Gz.to[1]->textaddr
				,Gz.to[1]->textlen
				,0);
	Gz.to[0]->io.success=	errna;
	SS[1].value.i=		a;
	*Gz.at=			socksend;
	argot_jump		(a>=0);
}

SCV	sockrecv		(void)
{	errna=			0;
	ssize_t			a=
	recv			(Gz.to[1]->value.i4.l
				,Gz.to[0]->textaddr
				+Gz.to[0]->textlen
				,Gz.to[0]->textsize
				-Gz.to[0]->textlen
				,0);
	Gz.to[1]->io.success=	errna;
	SS[0].value.i=		a;
	if		yay	(a>0)
	Gz.to[0]->textlen+=	a;
	*Gz.at=			sockrecv;
	argot_jump		(a>=0);
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20200907",
	.official=	"20200907",
	.update=	"20200907"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(sock,			"sock");

	aa		(sockdgram,		"sockdgram");
	aa		(sockstream,		"sockstream");

	aa		(sockbind,		"sockbind");
	aa		(socklisten,		"socklisten");
	aa		(sockaccept,		"sockaccept");
	aa		(sockconnect,		"sockconnect");

	aa		(sockrecv,		"sockrecv");
	aa		(socksend,		"socksend");

	aa_fini		();

	SS[0].show=
	SS[1].show=	Gz.out.den8;
	vattach_faster	(SS+0,"sockrecv");
	vattach_faster	(SS+1,"socksend");
}
