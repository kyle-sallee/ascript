/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"pam.h"

static	PG	pg=
{	.account.name=		"pam.name",
	.account.len=		8,
	.account.text=		"root",
	.account.textlen=	4,
	.service.name=		"pam.service",
	.service.len=		0xb,
	.service.text=		"system-auth",
	.service.textlen=	0xb,
};

static		void	_pam	(void)
{	*Gz.at=		_pam;
	argot_next	();
}

SCV	_pam_authenticate	(void)
{	pg.data.pam_error.i=
	pam_authenticate	(pg.data.handle,0);
	*Gz.at=			_pam_authenticate;
	argot_jump		(pg.data.pam_error.i==PAM_SUCCESS);
}

SCV	_pam_start		(void)
{	pg.data.pam_error.i=
	pam_start		(pg.service.textaddr,
				 pg.account.textaddr,
				&pg.data.conv,
				&pg.data.handle);
	*Gz.at=			_pam_start;
	argot_jump		(pg.data.pam_error.i==PAM_SUCCESS);
}

SCV	_pam_end		(void)
{	pg.data.pam_error.i=
	pam_end			(pg.data.handle,
				 pg.data.pam_error.i);
	pg.data.handle=		NULL;
	*Gz.at=			_pam_end;
	argot_jump		(pg.data.pam_error.i==PAM_SUCCESS);
}

SCV	_pam_open_session	(void)
{	pam_setcred		(pg.data.handle,PAM_ESTABLISH_CRED);
	pg.data.pam_error.i=
	pam_open_session	(pg.data.handle,0);

	*Gz.at=			_pam_open_session;
	argot_jump		(pg.data.pam_error.i==PAM_SUCCESS);
}

SCV	_pam_close_session	(void)
{	pg.data.pam_error.i=
	pam_close_session	(pg.data.handle,0);
	pam_setcred		(pg.data.handle,PAM_DELETE_CRED);
	*Gz.at=			_pam_close_session;
	argot_jump		(pg.data.pam_error.i==PAM_SUCCESS);
}

SCV	_pam_strerror		(void)
{	if				yay	(pg.error.vam==NULL)
	{	__builtin_memcpy		(pg.error.name,"pam.error",9);
		pg.error.len=			9;
		map_init			(&pg.error);
		byteinit			(&pg.error);
		vattach_faster			(&pg.error,"pam.error");
	}

	uint8_t	const	*a=
	pam_strerror				(pg.data.handle,
						 pg.data.pam_error.i);
	uint8_t	const	*b;
	for					(b=a+4;*b;b++);
	pg.error.textlen=			b-a;
	memcpya					(pg.error.text,a,b-a);
	*Gz.at=					_pam_strerror;
	argot_next				();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180620",
	.official=	"20180620",
	.update=	"20200815"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(_pam,			"pam");
	aa		(_pam_strerror,		"pamstrerror");
	aa		(_pam_authenticate,	"pamauthenticate");
	aa		(_pam_start,		"pamstart");
	aa		(_pam_end,		"pamend");
	aa		(_pam_open_session,	"pamopensession");
	aa		(_pam_close_session,	"pamclosesession");
	aa_fini		();
};

__attribute__((constructor))
SCV	init				(void)
{	pg.data.conv.conv=		misc_conv;

/*	__builtin_memcpy		(pg.account.text,"root",4);
	__builtin_memcpy		(pg.service.text,"system-auth",0xc);

	__builtin_memcpy		(pg.account.name,"pam.name",8);
	__builtin_memcpy		(pg.service.name,"pam.service",0xb);

	pg.account.len=			8;
	pg.service.len=			0xb;

	pg.account.textlen=		4;
	pg.service.textlen=		0xb;


	byteinit			(&pg.account);
	byteinit			(&pg.service);
*/

	map_init			(&pg.account);
	map_init			(&pg.service);
	vattach_faster			(&pg.account,"pam.name");
	vattach_faster			(&pg.service,"pam.service");
}
