/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"byte.h"
#include	"a.h"
#include	"trim.h"

/*
OPERATOR	optrim[5];
*/

SCV	pare_	(void)	{tsubab(paresubnew,pare_);}
SCV	full_	(void)	{tsubab(fullsubnew,full_);}
SCV	head_	(void)	{tsubab(headsubnew,head_);}
SCV	tail_	(void)	{tsubab(tailsubnew,tail_);}
SCV	host_	(void)	{tsubab(hostsubnew,host_);}

SCV	prepare		(void)
{	show		(Gz.to[0]->host);
	show		(Gz.to[1]);
}

SCV	hostmapsize		(void)
{	VMETA		*B=	 Gz.to[0];

	if			(B->io.flag&textmapunmap)
	munmap			(B->textaddr,B->textsize);
	B->io.flag|=		textmapunmap;

	VMETA		*A=	B->host;
	B->textsize=		A->textsize;
	B->textaddr=
	pool			(B->textsize);
}

__attribute__((noinline))
SCV	equal_pare_			(void)
{	prepare				();
	hostmapsize			();

	VMETA		*B=		Gz.to[0];
	VMETA		*A=		B->host;
	VMETA		*C=		Gz.to[1];
	size_t		cr=		C->textlen;

	if			nay	(cr==0)
	{	memcpy			(B->textaddr,
					 A->textaddr,
					 B->textlen=
					 A->textlen);
		goto			done;
	}

	uint8_t		*c=		C->textaddr;
	uint8_t		*a=		A->textaddr;
	uint8_t		*b=		B->textaddr;
	size_t		ar=		A->textlen;
	uint8_t		*d;
	size_t		dr;

	while				(ar>=cr)
	{	d=	memmem		(a,ar,c,cr);
		if		nay	(d==NULL)
		break;

		dr=			d-a+cr;
		memcpy			(b,a,dr);
		a+=			dr;
		b+=			dr;
		ar-=			dr;

		while			((ar>=cr)&&(memcmpa(a,c,cr)==0))
		{	a+=		cr;
			ar-=		cr;
		}
	}

	if			yay	(ar)
	{	memcpy			(b,a,ar);
		b+=			ar;
	}

	B->textlen=			b-B->textaddr;
	done:
	argot_next			();
}

__attribute__((noinline))
SCV	equal_full_			(void)
{	prepare				();
	hostmapsize			();

	VMETA		*B=		 Gz.to[0];
	VMETA		*A=		B->host;
	VMETA		*C=		Gz.to[1];
	size_t		cr=		C->textlen;

	if			nay	(cr==0)
	{	memcpy			(B->textaddr,
					 A->textaddr,
					 B->textlen=
					 A->textlen);
		goto			done;
	}

	uint8_t		*c=		C->textaddr;
	uint8_t		*a=		A->textaddr;
	uint8_t		*b=		B->textaddr;
	size_t		ar=		A->textlen;
	uint8_t		*d;
	size_t		dr;

	while				(ar>=cr)
	{	d=	memmem		(a,ar,c,cr);
		if		nay	(d==NULL)
		break;

		dr=			d-a;
		memcpy			(b,a,dr);
		a+=			dr;
		b+=			dr;
		ar-=			dr;

		while			((ar>=cr)&&(memcmpa(a,c,cr)==0))
		{	a+=		cr;
			ar-=		cr;
		}
	}

	if			yay	(ar)
	{	memcpy			(b,a,ar);
		b+=			ar;
	}

	B->textlen=			b-B->textaddr;
	done:
	argot_next			();
}

__attribute__((noinline))
SCV	equal_head_			(void)
{	prepare				();
	hostmapsize			();

	VMETA		*B=		 Gz.to[0];
	VMETA		*A=		B->host;
	VMETA		*C=		Gz.to[1];
	size_t		cr=		C->textlen;

	if			nay	(cr==0)
	{	memcpy			(B->textaddr,
					 A->textaddr,
					 B->textlen=
					 A->textlen);
		goto			done;
	}

	uint8_t		*c=		C->textaddr;
	uint8_t		*a=		A->textaddr;
	uint8_t		*b=		B->textaddr;
	size_t		ar=		A->textlen;

	if				(memcmpa(a,c,cr)==0)
	{	a+=			cr;
		ar-=			cr;
	}

	memcpy				(b,a,ar);
	B->textlen=			ar;
	done:
	argot_next			();
}

__attribute__((noinline))
SCV	equal_tail_			(void)
{	prepare				();
	hostmapsize			();

	VMETA		*B=		 Gz.to[0];
	VMETA		*A=		B->host;
	VMETA		*C=		Gz.to[1];
	size_t		cr=		C->textlen;

	if			nay	(cr==0)
	{	memcpy			(B->textaddr,
					 A->textaddr,
					 B->textlen=
					 A->textlen);
		goto			done;
	}

	uint8_t		*c=		C->textaddr;
	uint8_t		*a=		A->textaddr;
	uint8_t		*b=		B->textaddr;
	size_t		ar=		A->textlen;

	if				(memcmpa(a+ar-cr,c,cr)==0)
	ar-=				cr;

	memcpy				(b,a,ar);
	B->textlen=			ar;
	done:
	argot_next			();
}

__attribute__((noinline))
SCV	equal_host_			(void)
{	prepare				();

	VMETA		*B=		 Gz.to[0];
	VMETA		*A=		B->host;
	B->textaddr=			A->textaddr;
	VMETA		*C=		Gz.to[1];
	size_t		cr=		C->textlen;

	uint8_t		*c=		C->textaddr;
	uint8_t		*a=		A->textaddr;
	size_t		ar=		A->textlen;

	if				(memcmpa(a+ar-cr,c,cr)==0)
	ar-=				cr;

	A->textlen=
	B->textlen=			ar;
	A->textaddr[
	A->textlen]=			0;
	argot_next			();
}

static	void	equal_pare	(void)
{	(*Gz.at=equal_pare_)	();
}

static	void	equal_full	(void)
{	(*Gz.at=equal_full_)	();
}

static	void	equal_head	(void)
{	(*Gz.at=equal_head_)	();
}

static	void	equal_tail	(void)
{	(*Gz.at=equal_tail_)	();
}

static	void	equal_host	(void)
{	(*Gz.at=equal_host_)	();
}

static	void	pare	(void)
{	(*Gz.at=pare_)	();
}

static	void	full	(void)
{	(*Gz.at=full_)	();
}

static	void	head	(void)
{	(*Gz.at=head_)	();
}

static	void	tail	(void)
{	(*Gz.at=tail_)	();
}

static	void	host	(void)
{	(*Gz.at=host_)	();
}

static	void	trim	(void)
{	*Gz.at=		trim;
	argot_next	();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20200131",
	.official=	"20200131",
	.update=	"20200808",
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(trim,		"trim");
	aa		(pare,		"trimpare");
	aa		(full,		"trimfull");
	aa		(head,		"trimhead");
	aa		(tail,		"trimtail");
	aa		(host,		"trimtailhost");
	aa_fini		();
};

__attribute__((constructor))
SCV	init			(void)
{	int		a;
	for			(a=0;5>a;a++)
	optrim[a]=		opbyte[0];

	optrim[0].equal=	equal_pare;
	optrim[1].equal=	equal_full;
	optrim[2].equal=	equal_head;
	optrim[3].equal=	equal_tail;
	optrim[4].equal=	equal_host;
}
