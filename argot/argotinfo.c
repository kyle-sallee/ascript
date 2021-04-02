/*	By Kyle Sallee in 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"argot.h"
#include	"byte.h"
#include	"a.h"
#include	<dlfcn.h>

static	inline	void	*acquire	(VMETA *A)
{	if				(A->value.p!=NULL)
	return				 A->value.p;

	A->textaddr[
	A->textlen]=			0;

	A->value.p=
	ahandle				(A->textaddr);

	return				A->value.p;
}

static		void	show_author	(VMETA *Z)
{	VMETA		*A=		Z->host;
	void		*v=
	acquire				(A);
	if			nay	(v==NULL)
	return;

	ARGOT_INFO	*i=
	dlsym				(v,"AI");

	if			yay	(i!=NULL)
	{	Z->textaddr=		i->author;
		Z->textlen=
		strlenb			(i->author);
	}

/*	dlclose				(v);	*/
}

static		void	show_author_email	(VMETA *Z)
{	VMETA		*A=		Z->host;
	void		*v=
	acquire				(A);
	if			nay	(v==NULL)
	return;

	ARGOT_INFO	*i=
	dlsym				(v,"AI");

	if			yay	(i!=NULL)
	{	Z->textaddr=		i->author_email;
		Z->textlen=
		strlenb			(i->author_email);
	}
/*	dlclose				(v);	*/
}

static		void	show_contact	(VMETA *Z)
{	VMETA		*A=		Z->host;
	void		*v=
	acquire				(A);
	if			nay	(v==NULL)
	return;

	ARGOT_INFO	*i=
	dlsym				(v,"AI");

	if			yay	(i!=NULL)
	{	Z->textaddr=		i->contact;
		Z->textlen=
		strlenb			(i->contact);
	}
/*	dlclose				(v);	*/
}

static		void	show_contact_email	(VMETA *Z)
{	VMETA		*A=		Z->host;
	void		*v=
	acquire				(A);
	if			nay	(v==NULL)
	return;

	ARGOT_INFO	*i=
	dlsym				(v,"AI");

	if			yay	(i!=NULL)
	{	Z->textaddr=		i->contact_email;
		Z->textlen=
		strlenb			(i->contact_email);
	}
/*	dlclose				(v);	*/
}

static		void	show_homepage	(VMETA *Z)
{	VMETA		*A=		Z->host;
	void		*v=
	acquire				(A);
	if			nay	(v==NULL)
	return;

	ARGOT_INFO	*i=
	dlsym				(v,"AI");

	if			yay	(i!=NULL)
	{	Z->textaddr=		i->homepage;
		Z->textlen=
		strlenb			(i->homepage);
	}
/*	dlclose				(v);	*/
}

static		void	show_create	(VMETA *Z)
{	VMETA		*A=		Z->host;
	void		*v=
	acquire				(A);
	if			nay	(v==NULL)
	return;

	ARGOT_INFO	*i=
	dlsym				(v,"AI");

	if			yay	(i!=NULL)
	{	Z->textaddr=		i->create;
		Z->textlen=		8;
	}
/*	dlclose				(v);	*/
}

static		void	show_official	(VMETA *Z)
{	VMETA		*A=		Z->host;
	void		*v=
	acquire				(A);
	if			nay	(v==NULL)
	return;

	ARGOT_INFO	*i=
	dlsym				(v,"AI");

	if			yay	(i!=NULL)
	{	Z->textaddr=		i->official;
		Z->textlen=		8;
	}
/*	dlclose				(v);	*/
}

static		void	show_update	(VMETA *Z)
{	VMETA		*A=		Z->host;
	void		*v=
	acquire				(A);
	if			nay	(v==NULL)
	return;

	ARGOT_INFO	*i=
	dlsym				(v,"AI");

	if			yay	(i!=NULL)
	{	Z->textaddr=		i->update;
		Z->textlen=		8;
	}
/*	dlclose				(v);	*/
}


static	inline	void	subnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".author",A);
	byteinit		(B);
	B->show=		show_author;

	VMETA		*C=
	var_new_sub		(".author.email",A);
	byteinit		(C);
	C->show=		show_author_email;

	VMETA		*D=
	var_new_sub		(".contact",A);
	byteinit		(D);
	D->show=		show_contact;

	VMETA		*E=
	var_new_sub		(".contact.email",A);
	byteinit		(E);
	E->show=		show_contact_email;

	VMETA		*F=
	var_new_sub		(".homepage",A);
	byteinit		(F);
	F->show=		show_homepage;

	VMETA		*G=
	var_new_sub		(".create",A);
	byteinit		(G);
	G->show=		show_create;

	VMETA		*H=
	var_new_sub		(".official",A);
	byteinit		(H);
	H->show=		show_official;

	VMETA		*I=
	var_new_sub		(".update",A);
	byteinit		(I);
	I->show=		show_update;
}

static	void	argot_info	(void)	{tvarnewab(subnew,argot_info);}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20190729",
	.official=	"20190729",
	.update=	"20200815"
};

__attribute__((constructor))
static	void	aainit		(void)
{	aa_init		();
	aa		(argot_info,	"argotinfo");
	aa_fini		();
};
