/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"view.h"

/* From type byte the other string comparison variables can be acquired. */

/*
OPERATOR	opview[4];
*/

/*
SCV	showview		(VMETA *A)
{	A->textaddr=		A->host->textaddr+
}
*/

SCV	viewwith		(void)
{	VMETA		*A=	Gz.active.view;
	Gz.active.view=		Gz.to[0];
	*Gz.at=			viewwith;
	argot_next		();
	Gz.active.view=		A;
}

SCV	viewsave		(void)
{	uint8_t		*a;
	size_t		b;
	VMETA		*A=	Gz.active.view;
	a=			A->textaddr;
	b=			A->textlen;
	*Gz.at=			viewsave;
	argot_next		();
	A->textaddr=		a;
	A->textlen=		b;
	argot_next		();
}

SCV	viewfull		(void)
{	VMETA		*A=	Gz.active.view;
	VIEWD		*a=
	viewd			(A);
	A->textaddr=		a->host->textaddr;
	A->textlen=		a->host->textlen;
	*Gz.at=			viewfull;
	argot_next		();
}

__attribute__((always_inline))
static	inline	void	addadd_head_common	(VMETA *A,void (*B)(void))
{	VIEWD		*a=
	viewd			(A);
	uint8_t		*b=	a->view->textaddr;
	uint8_t		*c=	a->host->textaddr+
				a->host->textlen;
	uint8_t		d=	a->head->textaddr[0];
	size_t		e=	a->head->textlen;

	c-=			a->head->textlen;

	if		nay	(1==e)	goto	byte;
	if		nay	(1 >e)	goto	miss;

	uint8_t		*f=	a->head->textaddr;

	for			(;c>=b;b++)
	if		nay	(*b==d)
	if		nay	(memcmpa(b,f,e)==0)
	goto			found;
	goto			miss;

	byte:
	for			(;c>=b;b++)
	if		nay	(*b==d)
	goto			found;

	miss:
	*Gz.at=			B;
	argot_next		();
	return;

	found:
	a->view->textaddr=	b+
				a->head->textlen;
	a->view->textlen=	0;
	*Gz.at=			B;
	argot_skip		();
	return;
}

SCV	addadd_head		(void)
{	addadd_head_common	(Gz.to[0],addadd_head);
}

SCV	viewheadnext		(void)
{	addadd_head_common	(Gz.active.view,viewheadnext);
}

__attribute__((noinline))
SCV	viewbytenext_			(void)
{	Gz.active.view->textaddr++;
	argot_next			();
}

__attribute__((noinline))
SCV	viewbyteback_		(void)
{	Gz.active.view->textaddr--;
	argot_next		();
}

__attribute__((noinline))
SCV	viewbytenextsafe_	(void)
{	VMETA		*A=	Gz.active.view;
	A->textaddr++;
	VMETA		*H=
	viewd			(A)->host;
	uint8_t		*b=	H->textaddr+
				H->textlen;
	argot_jump		(b>A->textaddr);
}

__attribute__((noinline))
SCV	viewbytebacksafe_	(void)
{	VMETA		*A=	Gz.active.view;
	A->textaddr--;
	argot_jump		(A->textaddr>=viewd(A)->host->textaddr);
}

__attribute__((noinline))
SCV	viewchar_			(void)
{	VMETA		*A=		Gz.active.view;
	A->textlen=
	utf8_size			(A->textaddr);
	argot_next			();
}

__attribute__((noinline))
SCV	viewcharnext_			(void)
{	VMETA		*A=		Gz.active.view;
	A->textaddr+=			A->textlen;
	A->textlen=
	utf8_size			(A->textaddr);
	argot_next			();
}

__attribute__((noinline))
SCV	viewcharback_			(void)
{	VMETA		*A=		Gz.active.view;
	uint8_t		*b=		A->textaddr,
			*a=		A->textaddr-1;
	if			nay	((a[0]&0x80)!=0)	a--;
	if			nay	((a[0]&0x80)!=0)	a--;
	if			nay	((a[0]&0x80)!=0)	a--;
	if			nay	((a[0]&0x80)!=0)	a--;
	A->textaddr=			a;
	A->textlen=			b-a;
	argot_next			();
}

__attribute__((noinline))
SCV	viewcharnextsafe_		(void)
{	VMETA		*A=		Gz.active.view;
	A->textaddr+=			A->textlen;
	A->textlen=
	utf8_size			(A->textaddr);
	VMETA		*H=	viewd	(A)->host;
	uint8_t		*b=		H->textaddr+
					H->textlen;
	argot_jump			(b>A->textaddr);
}

__attribute__((noinline))
SCV	viewcharbacksafe_		(void)
{	VMETA		*A=		Gz.active.view;
	uint8_t		*b=		A->textaddr,
			*a=		A->textaddr-1;
	if			nay	((a[0]&0x80)!=0)	a--;
	if			nay	((a[0]&0x80)!=0)	a--;
	if			nay	((a[0]&0x80)!=0)	a--;
	if			nay	((a[0]&0x80)!=0)	a--;
	A->textaddr=			a;
	A->textlen=			b-a;
	argot_jump			(A->textaddr>=viewd(A)->host->textaddr);
}

__attribute__((always_inline))
static	inline	void	subsub_head_common	(VMETA *A,void (*B)(void))
{	VIEWD		*a=
	viewd			(A);
	uint8_t		*b=	a->host->textaddr;
	uint8_t		*c=	a->view->textaddr-
				a->head->textlen-1;
	uint8_t		d=	a->head->textaddr[0];
	size_t		e=	a->head->textlen;

	if		nay	(1==e)	goto	byte;
	if		nay	(1 >e)	goto	miss;

	uint8_t		*f=	a->head->textaddr;

	for			(;c>=b;c--)
	if		nay	(*c==d)
	if		nay	(memcmpa(c,f,e)==0)
	goto			found;
	goto			miss;

	byte:
	for			(;c>=b;c--)
	if		nay	(*c==d)
	goto			found;

	miss:
	*Gz.at=			B;
	argot_next		();
	return;

	found:;
	uint8_t		*g=	a->view->textaddr+
				a->view->textlen;
	a->view->textaddr=	a->head->textlen+c;
	a->view->textlen=	g-
				a->view->textaddr;
	*Gz.at=			B;
	argot_skip		();
	return;
}

SCV	subsub_head		(void)
{	subsub_head_common	(Gz.to[0],subsub_head);
}

SCV	viewheadback		(void)
{	subsub_head_common	(Gz.active.view,viewheadback);
}

__attribute__((always_inline))
static	inline	void	addadd_tail_common	(VMETA *A,void (*B)(void))
{	VIEWD		*a=
	viewd			(A);
	uint8_t		*b=	a->view->textaddr+
				a->view->textlen+1;
	uint8_t		*c=	a->host->textaddr+
				a->host->textlen;
	uint8_t		d=	a->tail->textaddr[0];
	size_t		e=	a->tail->textlen;

	c-=			a->tail->textlen;

	if		nay	(1==e)	goto	byte;
	if		nay	(1 >e)	goto	miss;

	uint8_t		*f=	a->tail->textaddr;

	for			(;c>=b;b++)
	if		nay	(*b==d)
	if		nay	(memcmpa(b,f,e)==0)
	goto			found;
	goto			miss;

	byte:
	for			(;c>=b;b++)
	if		nay	(*b==d)
	goto			found;

	miss:
	*Gz.at=			B;
	argot_next		();
	return;

	found:
	a->view->textlen=	b-a->view->textaddr;
	*Gz.at=			B;
	argot_skip		();
	return;
}

SCV	addadd_tail		(void)
{	addadd_tail_common	(Gz.to[0],addadd_tail);
}

SCV	viewtailnext		(void)
{	addadd_tail_common	(Gz.active.view,viewtailnext);
}


__attribute__((always_inline))
static	inline	void	subsub_tail_common	(VMETA *A,void (*B)(void))
{	VIEWD		*a=
	viewd			(A);
	uint8_t		*b=	a->host->textaddr;
	uint8_t		*c=	a->view->textaddr+
				a->view->textlen;
	uint8_t		d=	a->tail->textaddr[0];
	size_t		e=	a->tail->textlen;

	if		nay	(1==e)	goto	byte;
	if		nay	(1 >e)	goto	miss;

	uint8_t		*f=	a->tail->textaddr;

	for			(;c>=b;c--)
	if		nay	(*c==d)
	if		nay	(memcmpa(c,f,e)==0)
	goto			found;
	goto			miss;

	byte:
	for			(;c>=b;c--)
	if		nay	(*c==d)
	goto			found;

	miss:
	*Gz.at=			B;
	argot_next		();
	return;

	found:
	a->view->textlen=	c-a->view->textaddr;
	*Gz.at=			B;
	argot_skip		();
	return;
}

SCV	subsub_tail		(void)
{	subsub_tail_common	(Gz.to[0],subsub_tail);
}

SCV	viewtailback		(void)
{	subsub_tail_common	(Gz.active.view,viewtailback);
}

/*
SCV	add_from		(void)
{	VMETA		*A=	Gz.to[0];
	VMETA		*B=	Gz.to[1];
	VIEWD		*a=
	viewd			(A);
	a->view->textaddr+=	B->value.i;
	*Gz.at=			add_from;
	argot_next		();
}

SCV	sub_from		(void)
{
	VMETA		*A=	Gz.to[0];
	VMETA		*B=	Gz.to[1];
	VIEWD		*a=
	viewd			(A);
	a->view->textaddr-=	B->value.i;
	*Gz.at=			sub_from;
	argot_next		();
}

SCV	equal_from		(void)
{
	VMETA		*A=	Gz.to[0];
	VMETA		*B=	Gz.to[1];
	VIEWD		*a=
	viewd			(A);
	a->view->textaddr=	a->host->textaddr+B->value.i;
	*Gz.at=			equal_from;
	argot_next		();
}

SCV	addadd_from		(void)
{	VMETA		*A=	Gz.to[0];
	VIEWD		*a=
	viewd			(A);
	a->view->textaddr++;
	*Gz.at=			addadd_from;
	argot_next		();
}

SCV	subsub_from		(void)
{	VMETA		*A=	Gz.to[0];
	VIEWD		*a=
	viewd			(A);
	a->view->textaddr--;
	*Gz.at=			subsub_from;
	argot_next		();
}
*/

/*
SCV	reval_from		(VMETA *A)
{	VIEWD		*a=
	viewd			(A);
	A->value.i=		a->view->textaddr-
				a->host->textaddr;
}

SCV	revise_from		(VMETA *A)
{	VIEWD		*a=
	viewd			(A);
	a->view->textaddr=	a->host->textaddr+A->value.i;
}
*/

SCV	viewheadadd		(void)
{	VMETA		*A=
	parapass		(arga(NULL));
	show			(A);
	VIEWD		*a=
	viewd			(Gz.active.view);
	memcpya			(a->head->textaddr
				+a->head->textlen
				,A->textaddr
				,A->textlen);
	a->head->textlen+=	 A->textlen;
	*Gz.at=			viewheadadd;
	argot_next		();
}

SCV	viewheadequal		(void)
{	VMETA		*A=
	parapass		(arga(NULL));
	show			(A);
	VIEWD		*a=
	viewd			(Gz.active.view);
	memcpya			(a->head->textaddr
				,A->textaddr
				,A->textlen);
	a->head->textlen=	 A->textlen;
	*Gz.at=			viewheadequal;
	argot_next		();
}


SCV	viewtailadd		(void)
{	VMETA		*A=
	parapass		(arga(NULL));
	show			(A);
	VIEWD		*a=
	viewd			(Gz.active.view);
	memcpya			(a->tail->textaddr
				+a->tail->textlen
				,A->textaddr
				,A->textlen);
	a->tail->textlen+=	 A->textlen;
	*Gz.at=			viewtailadd;
	argot_next		();
}

SCV	viewtailequal		(void)
{	VMETA		*A=
	parapass		(arga(NULL));
	show			(A);
	VIEWD		*a=
	viewd			(Gz.active.view);
	memcpya			(a->tail->textaddr
				,A->textaddr
				,A->textlen);
	a->tail->textlen=	 A->textlen;
	*Gz.at=			viewtailequal;
	argot_next		();
}

SCV	view	(void)	{tsubab(viewsubnew,view);}

static	void	viewbytenext	(void)	{(*Gz.at=viewbytenext_)		();}
static	void	viewbyteback	(void)	{(*Gz.at=viewbyteback_)		();}
static	void	viewbytenextsafe(void)	{(*Gz.at=viewbytenextsafe_)	();}
static	void	viewbytebacksafe(void)	{(*Gz.at=viewbytebacksafe_)	();}
static	void	viewchar	(void)	{(*Gz.at=viewchar_)		();}
static	void	viewcharback	(void)	{(*Gz.at=viewcharback_)		();}
static	void	viewcharnext	(void)	{(*Gz.at=viewcharnext_)		();}
static	void	viewcharbacksafe(void)	{(*Gz.at=viewcharbacksafe_)	();}
static	void	viewcharnextsafe(void)	{(*Gz.at=viewcharnextsafe_)	();}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180708",
	.official=	"20180708",
	.update=	"20200828"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(view,			"view");
	aa		(viewbyteback,		"viewbyteback");
	aa		(viewbytenext,		"viewbytenext");
	aa		(viewbytebacksafe,	"viewbytebacksafe");
	aa		(viewbytenextsafe,	"viewbytenextsafe");
	aa		(viewchar,		"viewchar");
	aa		(viewcharback,		"viewcharback");
	aa		(viewcharnext,		"viewcharnext");
	aa		(viewcharbacksafe,	"viewcharbacksafe");
	aa		(viewcharnextsafe,	"viewcharnextsafe");
	aa		(viewsave,		"viewsave");
	aa		(viewfull,		"viewfull");
	aa		(viewwith,		"viewwith");
	aa		(viewheadadd,		"viewheadadd");
	aa		(viewheadback,		"viewheadback");
	aa		(viewheadequal,		"viewheadequal");
	aa		(viewheadnext,		"viewheadnext");
	aa		(viewtailadd,		"viewtailadd");
	aa		(viewtailback,		"viewtailback");
	aa		(viewtailequal,		"viewtailequal");
	aa		(viewtailnext,		"viewtailnext");
	aa_fini		();
};

__attribute__((constructor))
SCV	init			(void)
{	opview[0]=
	opview[1]=
	opview[2]=		opbyte[0];
/*	opview[3]=		opint8[0];	*/

	opview[0].addadd=	NULL;

	opview[1].addadd=	addadd_head;
	opview[1].subsub=	subsub_head;

	opview[2].addadd=	addadd_tail;
	opview[2].subsub=	subsub_tail;

/*	opview[3].add=		add_from;
	opview[3].equal=	equal_from;
	opview[3].add=		add_from;
	opview[3].sub=		sub_from;
	opview[3].addadd=	addadd_from;
	opview[3].subsub=	subsub_from;
*/
}
