/*	By Kyle Sallee from 2015 .. 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	<stdio.h>

SCV	varcall				(void)
{	show				(Gz.to[0]);

	VMETA		*A=		Gz.to[0],
			*B=		Gz.to[1];

	__builtin_memset		(A->textaddr
					+A->textlen
					,0
					,VAR_NAME_SIZE);

	vdetach				(B);
	__builtin_memcpy		(B->name,A->textaddr,VAR_NAME_SIZE);
	B->len=				A->textlen;
	vattach				(B);
	*Gz.at=				varcall;
	argot_next			();
}

SCV	reval_size	(VMETA *B)	{B->value.i=B->host->textsize;}
SCV	revise_size			(VMETA *B)
{	VMETA		*A=		B->host;
	uint64_t	t=		B->value.i;

	void		*v;
	if			yay	((A->io.flag&textmapunmap)==0)
	{	A->io.flag|=		textmapunmap;
		v=
		pps			(t);
		int		a;
		for			(a=0;sizeof(A->text)>a;a+=0x10)
		__builtin_memcpy	(v+a,A->textaddr+a,0x10);
		A->textaddr=		v;
		A->textsize=		t;
	}
	else
	{	v=
		mremap			(A->textaddr,
					 A->textsize,
					 t,
					 MREMAP_MAYMOVE);
		A->textaddr=		v;
		A->textsize=		t;

		if		nay	(A->io.map)
		{
/*			ftruncate	(A->io.map,t);	*/
			posix_fallocate	(A->io.map,0,t);
/*			madvise		(v,t,MADV_WILLNEED);
*/
/* not much difference either way */
		}
	}
}

#include	"argot.h"
#include	"int.h"

static	inline	void	varsizesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".size",A);
	int4init		(B);
/*	B->op=			varsizeop;	*/
	B->reval=		reval_size;
	B->revise=		revise_size;
/*	B->val=			(void *)	&A->textsize;	*/
}

SCV	reval_len	(VMETA *B)	{B->value.i=B->host->textlen;}
SCV	revise_len	(VMETA *B)	{B->host->textlen=B->value.i;}

SCV	varlensubnew		(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".len",A);
	int4init		(B);
	B->reval=		reval_len;
	B->revise=		revise_len;
/*	B->val=			(void *)	&A->textlen;	*/
}

SCV	varsize_(void)	{tsuba(varsizesubnew);}
SCV	varlen_	(void)	{tsuba(varlensubnew);}
SCV	varsize	(void)	{(*Gz.at=varsize_)();}
SCV	varlen	(void)	{(*Gz.at=varlen_)();}

SCV	varname			(void)
{	VMETA		*A=	Gz.to[0],
			*B=	Gz.to[1];
	A->textlen= 		B->len;
	__builtin_memcpy	(A->textaddr,B->name,VAR_NAME_SIZE);
	*Gz.at=			varname;
	argot_next		();
}

SCV	show_var_terse			(VMETA *A)
{	VMETA		*B,**E,**M;

	uint8_t		*a=		A->textaddr;

	E=
	M=				(VMETA **)	Gz.hash.var;
	E+=				0x10000;

	while				(E>M)
	if				(B=*M++)
	while				(B)
	{	memcpya			(a,B->name,B->len);
		a+=			           B->len;
		*a++=			'\n';
		B=			B->fore;
	}

	A->textlen=			a-A->textaddr;
}

static	inline	void	expound	(VMETA *A,VMETA *B)
{	uint8_t		*a=	A->textaddr+
				A->textlen;

	a+=	sprintf		(a,"%s%s\n","name=\t\t",B->name);
	a+=	sprintf		(a,"%s%#x\n","len=\t\t",B->len);
	if			(B->op!=NULL)
	if			(B->op->int_compat)
	a+=	sprintf		(a,"%s%#x\n","*value.i=\t\t",B->value.i);
	else
	a+=	sprintf		(a,"%s%p\n","*value.p=\t\t",B->value.p);

	a+=	sprintf		(a,"%s%#x\n","io.flag=\t",B->io.flag);
	a+=	sprintf		(a,"%s%p\n","addr=\t\t",B);
	a+=	sprintf		(a,"%s%p\n","op=\t\t",	B->op);

	if			(B->textaddr!=NULL)
	{	a+=
		sprintf		(a,"textaddr=\t%p\n",B->textaddr);
		a+=
		sprintf		(a,"textlen=\t%#lx\n",B->textlen);
		a+=
		sprintf		(a,"textsize=\t%#lx\n",B->textsize);
	}

	if			(B->dataaddr!=NULL)
	{	a+=
		sprintf		(a,"dataaddr=\t%p\n",B->dataaddr);
		a+=
		sprintf		(a,"datalen=\t%#lx\n",B->datalen);
		a+=
		sprintf		(a,"datasize=\t%#lx\n",B->datasize);
	}

	*a++=			'\n';

	A->textlen=		a-A->textaddr;
}

SCV	show_var_verbose		(VMETA *A)
{	VMETA		*B,**E,**M;

	E=
	M=				(VMETA **)	Gz.hash.var;
	E+=				0x10000;

	while				(E>M)
	if				(B=*M++)
	while				(B)
	{	text_check		(A,PAGE);
		expound			(A,B);
		B=			B->fore;
	}
}

#define		namelen(z)	.name=(z),	.len=strlen(z)

SCV	varterse		(void)
{	static	VMETA		a=
	{	namelen	("var.terse"),
		.op=	opbyte,
	};

/*	uint8_t			c[HUGE];	*/

	if		nay	(a.textaddr!=NULL)
	goto			done;

	map_init		(&a);
/*	a.op=			opbyte;	*/
	a.show=			show_var_terse;
/*	a.textaddr=		c;	*/
	a.textaddr=	pps	(HUGE);
	vattach_faster		(&a,"var.terse");

	done:
	*Gz.at=			varterse;
	argot_next		();
}

SCV	varverbose		(void)
{	static	VMETA		a=
	{	namelen	("var.verbose"),
		.op=	opbyte,
	};
/*	static	uint8_t		c[HUGE];	*/

	if		nay	(a.textaddr!=NULL)
	goto			done;

	map_init		(&a);
/*	a.op=			opbyte;	*/
	a.show=			show_var_verbose;
/*	a.textaddr=		c;			*/
	a.textaddr=	pps	(HUGE);
	vattach_faster		(&a,"var.verbose");

	done:
	*Gz.at=			varverbose;
	argot_next		();
}

SCV	var		(void)
{	*Gz.at=		var;
	argot_next	();
}

const	ARGOT_INFO	AI=
{	.author=		"Kyle David Sallee",
	.author_email=		"kyle.sallee@gmail.com",
	.homepage=		"https://kyle-sallee.github.io/ascript/",
	.create=		"20170707",
	.official=		"20170707",
	.update=		"20200823",
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(var,		"var");
	aa		(varsize,	"varsize");
	aa		(varlen,	"varlen");
	aa		(varcall,	"varcall");
	aa		(varname,	"varname");
	aa		(varverbose,	"varverbose");
	aa		(varterse,	"varterse");
	aa_fini		();
};
