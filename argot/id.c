/*	By Kyle Sallee in 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"byte.h"
#include	"int.h"
#include	"a.h"
#include	<grp.h>
#include	<pwd.h>

__attribute__((cold))
static		void	id	(void)
{	*Gz.at=		id;
	argot_next	();
}

SCV	reval_gid		(VMETA *B)
{	VMETA		*A=	B->host;
	show			(A);

	errna=			0;
	struct group	*G=
	getgrnam		(A->textaddr);
	B->io.success=		errna;

	if			(G!=NULL)
	B->value.i4.l=		G->gr_gid;

}

SCV	revise_gid		(VMETA *B)
{	VMETA		*A=	B->host;

	errna=			0;
	struct group	*G=
	getgrgid		(B->value.i4.l);
	B->io.success=		errna;

	if		yay	(G!=NULL)
	{	A->textlen=
		strcpya		(A->textaddr,G->gr_name);
		if		(A->revise)
		A->revise	(A);
	}
}

SCV	reval_uid		(VMETA *B)
{	VMETA		*A=	B->host;
	show			(A);

	errna=			0;
	struct passwd	*P=
	getpwnam		(A->textaddr);
	B->io.success=		errna;

	if			(P!=NULL)
	B->value.i4.l=		P->pw_uid;
}

SCV	revise_uid		(VMETA *B)
{	VMETA		*A=	B->host;

	errna=			0;
	struct passwd	*P=
	getpwuid		(B->value.i4.l);
	B->io.success=		errna;

	if		yay	(P!=NULL)
	{	A->textlen=
		strcpya		(A->textaddr,P->pw_name);
		if		(A->revise)
		A->revise	(A);
	}
}

SCV	revise_group		(VMETA *B)
{	VMETA		*A=	B->host;

	errna=			0;
	struct group	*G=
	getgrnam		(A->textaddr);
	B->io.success=		errna;

	if		yay	(G!=NULL)
	{	A->value.i4.l=	G->gr_gid;
		if		(A->revise)
		A->revise	(A);
	}
}

SCV	show_group		(VMETA *B)
{	VMETA		*A=	B->host;
/*	denwant			(A);	*/

	errna=			0;
	struct group	*G=
	getgrgid		(A->value.i4.l);
	B->io.success=		errna;

	if		yay	(G!=NULL)
	B->textlen=
	strcpya			(B->textaddr,G->gr_name);
}

SCV	revise_user		(VMETA *B)
{	VMETA		*A=	B->host;

	errna=			0;
	struct passwd	*P=
	getpwnam		(B->textaddr);
	B->io.success=		errna;

	if		yay	(P!=NULL)
	{	A->value.i4.l=	P->pw_uid;
		if		(A->revise)
		A->revise	(A);
	}
}

SCV	show_user		(VMETA *B)
{	VMETA		*A=	B->host;
/*	denwant			(A);	*/

	errna=			0;
	struct passwd	*P=
	getpwuid		(A->value.i4.l);
	B->io.success=		errna;

	if		yay	(P!=NULL)
	{	B->textlen=
		strcpya		(B->textaddr,P->pw_name);
	}
}

static	inline	void	gidinit	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".gid",A);
	int4init		(B);
	B->revise=		revise_gid;
	B->reval=		reval_gid;
}

static	inline	void	uidinit	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".uid",A);
	int4init		(B);
	B->revise=		revise_uid;
	B->reval=		reval_uid;
}

static	inline	void	groupinit	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".group",A);
	byteinit		(B);
	map_add			(B,PAGE,0);
	B->revise=		revise_group;
	B->show=		show_group;
}

static	inline	void	userinit	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".user",A);
	byteinit		(B);
	map_add			(B,PAGE,0);
	B->revise=		revise_user;
	B->show=		show_user;
}

SCV	gid	(void)	{tsubab(gidinit,	gid);}
SCV	uid	(void)	{tsubab(uidinit,	uid);}
SCV	group	(void)	{tsubab(groupinit,	group);}
SCV	user	(void)	{tsubab(userinit,	user);}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20190227",
	.official=	"20190227",
	.update=	"20200923"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(id,	"id");
	aa		(gid,	"gid");
	aa		(uid,	"uid");
	aa		(group,	"group");
	aa		(user,	"user");
	aa_fini		();
};
