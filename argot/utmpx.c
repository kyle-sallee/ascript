/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"byte.h"
#include	"int.h"
#include	"a.h"
#include	<pwd.h>
#include	<utmpx.h>

OPERATOR	varutmpxop[1];

typedef	struct
{	VALUE		*type;
	VALUE		*pid;
	VMETA		*line;
	VMETA		*id;
	VMETA		*user;
	VMETA		*host;
	struct	utmpx	a;
}	UTMPXDATA;

static	inline	void	utmpxsubnew	(VMETA *A)
{	A->op=			varutmpxop;
	map_add			(A,sizeof(UTMPXDATA),0);
	UTMPXDATA	*u=	(UTMPXDATA *)	A->textaddr;


	VMETA		*B=
	var_new_sub		(".type",A);
	int4init		(B);
	u->type=		&B->value;
/*	B->val=			&u->type;	*/

	VMETA		*C=
	var_new_sub		(".pid",A);
	int4init		(C);
	u->pid=			&C->value;
/*	C->val=			&u->pid;	*/

	u->type->i=		7;
	u->pid->i4.l=
	getpid			();

	VMETA		*D=
	var_new_sub		(".line",A);
	byteinit		(D);
	u->line=		D;

	char		*a=
	ttyname			(0);
	size_t		b=
	strlenb			(a);

	memcpy			(D->textaddr,a+strlen("/dev/"),
				 D->textlen= b-strlen("/dev/"));

	VMETA		*E=
	var_new_sub		(".id",A);
	byteinit		(E);
	u->id=			E;
	if			(strncmp(a,"/dev/tty",8)==0)
	memcpy			(E->textaddr,a+strlen("/dev/tty"),
				 E->textlen= b-strlen("/dev/tty"));
	else	if		(strncmp(a,"/dev/pts/",9)==0)
	memcpy			(E->textaddr,a+strlen("/dev/pts/"),
				 E->textlen= b-strlen("/dev/pts/"));

	VMETA		*F=
	var_new_sub		(".user",A);
	map_add			(F,PAGE,0);
	byteinit		(F);
	u->user=		F;

	struct	passwd		*P=
	getpwuid		(getuid());
	F->textlen=
	b=
	strlenb			(P->pw_name)+1;
	memcpy			(F->textaddr,P->pw_name,b+1);

	VMETA		*G=
	var_new_sub		(".host",A);
	u->host=		G;
}

SCV	add			(void)
{	VMETA		*A=	Gz.to[0];
	UTMPXDATA	*u=	(UTMPXDATA *)	A->textaddr;

	struct utmpx	*a=	&u->a;
	memset			(a,0,sizeof(struct utmpx));

	a->ut_type=		u->type->i;
	a->ut_pid=		u->pid->i;

	memcpy			(a->ut_line,
				 u->line->textaddr,
	MIN			(u->line->textlen,
	sizeof			(a->ut_line)));
	memcpy			(a->ut_id,
				 u->id->textaddr,
	MIN			(u->id->textlen,
	sizeof			(a->ut_id)));
	memcpy			(a->ut_user,
				 u->user->textaddr,
	MIN			(u->user->textlen,
	sizeof			(a->ut_user)));
	memcpy			(a->ut_host,
				 u->host->textaddr,
	MIN			(u->host->textlen,
	sizeof			(a->ut_host)));

	setutxent		();
	void		*b=
	pututxline		(a);
	endutxent		();
	*Gz.at=		add;
	argot_jump		(b!=NULL);
}

SCV	query			(void)
{	VMETA		*A=	Gz.to[0];
	UTMPXDATA	*u=	(UTMPXDATA *)	A->textaddr;

	struct utmpx	*a=	&u->a;
	memset			(a,0,sizeof(struct utmpx));

	a->ut_type=		u->type->i;
	a->ut_pid=		u->pid->i;

	memcpy			(a->ut_line,
				 u->line->textaddr,
	MIN			(u->line->textlen,
	sizeof			(a->ut_line)));
	memcpy			(a->ut_id,
				 u->id->textaddr,
	MIN			(u->id->textlen,
	sizeof			(a->ut_id)));
	memcpy			(a->ut_user,
				 u->user->textaddr,
	MIN			(u->user->textlen,
	sizeof			(a->ut_user)));
	memcpy			(a->ut_host,
				 u->host->textaddr,
	MIN			(u->host->textlen,
	sizeof			(a->ut_host)));

	setutxent		();
	a=
	getutxline		(a);
	endutxent		();

	if		nay	(a==NULL)
	{	*Gz.at=	query;
		argot_next	();
		return;
	}

	u->pid->i=		a->ut_pid;

	ssize_t		b;

	u->user->textlen=
	b=
	strlenb			(a->ut_user);
	memcpy			(u->user->textaddr,a->ut_user,b);

	u->host->textlen=
	b=
	strlenb			(a->ut_host);
	memcpy			(u->host->textaddr,a->ut_host,b);

	*Gz.at=			query;
	argot_skip		();
}

SCV	utmpx	(void)	{tvarnewab(utmpxsubnew,utmpx);}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20190709",
	.official=	"20190709",
	.update=	"20200923"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(utmpx,		"utmpx");
	aa_fini		();

	varutmpxop[0].add=	add;
	varutmpxop[0].query=	query;
};
