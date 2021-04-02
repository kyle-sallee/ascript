/*	By Kyle Sallee in 2017, 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"sort.h"
#include	"sort_single.h"
#include	"sort_repeat.h"
#include	"sort_unique.h"

OPERATOR	varsortop[0xb];

/* bad bad bad, but it works for now */
/*
int64_t		SMP_SORT=	1;
*/

extern		SORT_INDEX	*sort_back	(SORT_INDEX *,int const,uint8_t);
extern		SORT_INDEX	*sortb_inc	(SORT_INDEX *,int const);
extern		SORT_INDEX	*sort_dec	(SORT_INDEX *,int const,uint8_t);
extern		SORT_INDEX	*sort_inc	(SORT_INDEX *,int const,uint8_t);
extern		SORT_INDEX	*sort_long	(SORT_INDEX *,int const,uint8_t);
extern		SORT_INDEX	*sort_same	(SORT_INDEX *,int const,uint8_t);
extern		SORT_INDEX	*sort_tiny	(SORT_INDEX *,int const,uint8_t);
extern		SORT_INDEX	*select_single	(SORT_INDEX *);
extern		SORT_INDEX	*select_repeat	(SORT_INDEX *);
extern		SORT_INDEX	*select_unique	(SORT_INDEX *);

/*
static		void	sort	(VMETA *,
				 SORT_INDEX	*(*F)	(SORT_INDEX *,
							 int const),
				 SORT_INDEX	*(*S)	(SORT_INDEX *),
				 uint8_t);
*/

SCV	data_init		(VMETA *B)
{	VMETA		*A=	B->host;
	SORTMETA	*a=
	sortmeta		(B);

	if		yay	(a->ambit==NULL)
	a->amb=			'\n';
	else
	a->amb=			a->ambit->textaddr[0];

	if		yay	(               A->textlen>0)
	if		nay	(A->textaddr[A->textlen-1]!=a->amb)
	A->textaddr[
	A->textlen++]=		a->amb;

	if		yay	(B->textaddr==NULL)
	B->textaddr=
	pool			(B->textsize=BYTEMAX);

/*	if		yay	(B->dataaddr==NULL)
	B->dataaddr=
	pool			(B->datasize=LINEMAX);
*/

	if		yay	(a->sort_index==NULL)
	a->sort_index=
	pool			(a->sort_index_size=LINEMAX);

	uint64_t   * const b=	(uint64_t *)	byte_index	(B);
	SORT_INDEX * const i=			sort_index	(B);

	uint32_t	e;

	if		nay	(a->pre.i)
	{	e=
		index_pre	(A,b,i,a->amb);
	}
	else	e=
		index_l		(A,b,i,a->amb);

	a->count=		e;

	if		nay	(a->free.i)
	{	A->textlen=	0;
		madvise		(A->textaddr,
				 A->textsize,MADV_DONTNEED);
	}
}

SCV	revise_bit		(VMETA *B)
{	VMETA		*A=	B->host;
	SORTMETA	*a=
	sortmeta		(B);

	if		yay	(a->ambit==NULL)
	a->amb=			'\n';
	else
	a->amb=			a->ambit->textaddr[0];

	if		yay	(               A->textlen>0)
	if		nay	(A->textaddr[A->textlen-1]!=a->amb)
	A->textaddr[
	A->textlen++]=		a->amb;

/*	if		yay	(B->dataaddr==NULL)
	B->dataaddr=
	pool			(B->datasize=LINEMAX);
*/
	if		yay	(a->sort_index==NULL)
	a->sort_index=
	pool			(a->sort_index_size=LINEMAX);

	SORT_INDEX * const i=
	sort_index		(B);

	uint32_t		e=
	indexb			(A,i,a->amb);

	a->count=		e;
}

static	inline	int	compare	(SORT_INDEX const * const a,
				 SORT_INDEX const * const b)
{return 0;}


SCV	revise_partback		(VMETA *B)
{	data_init		(B);
	SORTMETA	*a=
	sortmeta		(B);
	a->first=
	sort_back		(sort_index(B),a->count,a->smp.i);
}

SCV	revise_bitless		(VMETA *B)
{	revise_bit		(B);
	SORTMETA	*a=
	sortmeta		(B);
	if		yay	(a->count>1)
	a->first=
	sortb_inc		(sort_index(B),a->count);
	else
	a->first=		(sort_index(B));
}

SCV	revise_byteless		(VMETA *B)
{	data_init		(B);
	SORTMETA	*a=
	sortmeta		(B);
	a->first=
	sort_inc		(sort_index(B),a->count,a->smp.i);
}

SCV	revise_bytemore		(VMETA *B)
{	data_init		(B);
	SORTMETA	*a=
	sortmeta		(B);
	a->first=
	sort_dec		(sort_index(B),a->count,a->smp.i);
}

SCV	revise_lenless		(VMETA *B)
{	data_init		(B);
	SORTMETA	*a=
	sortmeta		(B);
	a->first=
	sort_tiny		(sort_index(B),a->count,a->smp.i);
}

SCV	revise_lenmore		(VMETA *B)
{	data_init		(B);
	SORTMETA	*a=
	sortmeta		(B);
	a->first=
	sort_long		(sort_index(B),a->count,a->smp.i);
}

SCV	revise_partsame		(VMETA *B)
{	data_init		(B);
	SORTMETA	*a=
	sortmeta		(B);
	a->first=
	sort_same		(sort_index(B),a->count,a->smp.i);
}

SCV	show_entire		(VMETA *C)
{	VMETA		*B=	C->host;
	VMETA		*A=	B->host;
	C->textlen=		0;
	text_check		(C,A->textlen+0x10);

/*	B->op->mapuse[1]	(B);	*/
	B->revise	(B);

	SORTMETA	*a=
	sortmeta		(B);
	SORT_INDEX	*b=	a->first;
	if			(B->textaddr!=NULL)
	{	neworder	(C,b,a->amb);
		munmap		(B->textaddr,B->textsize);
	}
	else
	neworderb		(C,b,a->amb);
	munmap			(a->sort_index,a->sort_index_size);
	a->sort_index=		NULL;
/*	munmap			(B->dataaddr,B->datasize);	*/
}

SCV	show_repeat		(VMETA *C)
{	VMETA		*B=	C->host;
	VMETA		*A=	B->host;
	C->textlen=		0;
	text_check		(C,A->textlen+0x10);

/*	B->op->mapuse[1]	(B);	*/
	B->revise	(B);

	SORTMETA	*a=
	sortmeta		(B);
	SORT_INDEX	*b=
	select_repeat		(a->first);

	if			(B->textaddr!=NULL)
	{	neworder	(C,b,a->amb);
		munmap		(B->textaddr,B->textsize);
	}
	else
	neworderb		(C,b,a->amb);
	munmap			(a->sort_index,a->sort_index_size);
	a->sort_index=		NULL;
/*	munmap			(B->dataaddr,B->datasize);	*/
}

SCV	show_single		(VMETA *C)
{	VMETA		*B=	C->host;
	VMETA		*A=	B->host;
	C->textlen=		0;
	text_check		(C,A->textlen+0x10);

/*	B->op->mapuse[1]	(B);	*/
	B->revise	(B);

	SORTMETA	*a=
	sortmeta		(B);
	SORT_INDEX	*b=
	select_single		(a->first);

	if			(B->textaddr!=NULL)
	{	neworder	(C,b,a->amb);
		munmap		(B->textaddr,B->textsize);
	}
	else
	neworderb		(C,b,a->amb);
	munmap			(a->sort_index,a->sort_index_size);
	a->sort_index=		NULL;
/*	munmap			(B->dataaddr,B->datasize);	*/
}

SCV	show_unique		(VMETA *C)
{	VMETA		*B=	C->host;
	VMETA		*A=	B->host;
	C->textlen=		0;
	text_check		(C,A->textlen+0x10);

/*	B->op->mapuse[1]	(B);	*/
	B->revise	(B);

	SORTMETA	*a=
	sortmeta		(B);
	SORT_INDEX	*b=
	select_unique		(a->first);

	if			(B->textaddr!=NULL)
	{	neworder	(C,b,a->amb);
		munmap		(B->textaddr,B->textsize);
	}
	else
	neworderb		(C,b,a->amb);
	munmap			(a->sort_index,a->sort_index_size);
	a->sort_index=		NULL;
/*	munmap			(B->dataaddr,B->datasize);	*/
}

/*
static	void	revise_partback	(VMETA *);
static	void	revise_byteless	(VMETA *);
static	void	revise_bytemore	(VMETA *);
static	void	revise_lenless	(VMETA *);
static	void	revise_lenmore	(VMETA *);
static	void	revise_partsame	(VMETA *);
static	void	revise_bitless	(VMETA *);

static	void	show_entire	(VMETA *);
static	void	show_repeat	(VMETA *);
static	void	show_single	(VMETA *);
static	void	show_unique	(VMETA *);
*/

__attribute__((always_inline))
static	inline	void	sortpartbacksubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".back",A);
	B->op=			varsortop;
	B->revise=	revise_partback;
	map_add			(B,BYTEMAX,sizeof(SORTMETA));
/*	map_add			(B,BYTEMAX,LINEMAX);	*/
}

__attribute__((always_inline))
static	inline	void	sortbitlesssubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".less",A);
	B->op=			varsortop+0xa;
	B->revise=	revise_bitless;
	map_add			(B,BYTEMAX,sizeof(SORTMETA));
/*	map_add			(B,BYTEMAX,LINEMAX);	*/

	SORTMETA	*a=
	sortmeta		(B);
	a->smp.i=		0;
	a->pre.i=		0;
}

__attribute__((always_inline))
static	inline	void	sortbytelesssubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".less",A);
	B->op=			varsortop+1;
	B->revise=	revise_byteless;
	map_add			(B,BYTEMAX,sizeof(SORTMETA));
/*	map_add			(B,BYTEMAX,LINEMAX);	*/

	SORTMETA	*a=
	sortmeta		(B);
	a->smp.i=		1;
	a->pre.i=		1;
}

__attribute__((always_inline))
static	inline	void	sortbytemoresubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".more",A);
	B->op=			varsortop+2;
	B->revise=	revise_bytemore;
	map_add			(B,BYTEMAX,sizeof(SORTMETA));
/*	map_add			(B,BYTEMAX,LINEMAX);	*/

	SORTMETA	*a=
	sortmeta		(B);
	a->smp.i=		1;
	a->pre.i=		1;
}

__attribute__((always_inline))
static	inline	void	sortlenlesssubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".less",A);
	B->op=			varsortop+3;
	B->revise=	revise_lenless;
	map_add			(B,BYTEMAX,sizeof(SORTMETA));
/*	map_add			(B,BYTEMAX,LINEMAX);	*/

	SORTMETA	*a=
	sortmeta		(B);
	a->smp.i=		1;
}

__attribute__((always_inline))
static	inline	void	sortlenmoresubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".more",A);
	B->op=			varsortop+4;
	B->revise=	revise_lenmore;
	map_add			(B,BYTEMAX,sizeof(SORTMETA));
/*	map_add			(B,BYTEMAX,LINEMAX);	*/

	SORTMETA	*a=
	sortmeta		(B);
	a->smp.i=		1;
}

__attribute__((always_inline))
static	inline	void	sortpartsamesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".same",A);
	B->op=			varsortop+5;
	B->revise=	revise_partsame;
	map_add			(B,BYTEMAX,sizeof(SORTMETA));
/*	map_add			(B,BYTEMAX,LINEMAX);	*/
}

__attribute__((always_inline))
static	inline	void	sortwantentiresubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".entire",A);
	B->op=			varsortop+6;
	B->show=		show_entire;
}

__attribute__((always_inline))
static	inline	void	sortwantrepeatsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".repeat",A);
	B->op=			varsortop+7;
	B->show=		show_repeat;
}

__attribute__((always_inline))
static	inline	void	sortwantsinglesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".single",A);
	B->op=			varsortop+8;
	B->show=		show_single;
}

__attribute__((always_inline))
static	inline	void	sortwantuniquesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".unique",A);
	B->op=			varsortop+9;
	B->show=		show_unique;
}

__attribute__((always_inline))
static	inline	void	sortambitsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".ambit",A);
	byteinit		(B);
	SORTMETA	*a=
	sortmeta		(A);
	a->ambit=		B;
}

SCV	reval_free	(VMETA *A){A->value.i=sortmeta(A->host)->free.i;}
SCV	revise_free	(VMETA *A){sortmeta(A->host)->free.i=A->value.i;}
SCV	reval_pre	(VMETA *A){A->value.i=sortmeta(A->host)->pre.i;}
SCV	revise_pre	(VMETA *A){sortmeta(A->host)->pre.i=A->value.i;}
SCV	reval_smp	(VMETA *A){A->value.i=sortmeta(A->host)->smp.i;}
SCV	revise_smp	(VMETA *A){sortmeta(A->host)->smp.i=A->value.i;}

__attribute__((always_inline))
static	inline	void	sortfreesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".free",A);
	int4init		(B);
	B->reval=		reval_free;
	B->revise=		revise_free;
/*	SORTMETA	*a=
	sortmeta		(A);
	B->val=			&a->free;
*/
}

__attribute__((always_inline))
static	inline	void	sortpresubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".pre",A);
	int4init		(B);
	B->reval=		reval_pre;
	B->revise=		revise_pre;
/*	SORTMETA	*a=
	sortmeta		(A);
	B->val=			&a->pre;
*/
}

__attribute__((always_inline))
static	inline	void	sortsmpsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".smp",A);
	int4init		(B);
	B->reval=		reval_smp;
	B->revise=		revise_smp;
/*	SORTMETA	*a=
	sortmeta		(A);
	B->val=			&a->smp;
*/
}

SCV	sort		(void)
{	*Gz.at=		sort;
	argot_next	();
}

SCV	sortpartback	(void)	{tsubab(sortpartbacksubnew,	sortpartback);}
SCV	sortpartsame	(void)	{tsubab(sortpartsamesubnew,	sortpartsame);}
SCV	sortbitless	(void)	{tsubab(sortbitlesssubnew,	sortbitless);}
SCV	sortbyteless	(void)	{tsubab(sortbytelesssubnew,	sortbyteless);}
SCV	sortbytemore	(void)	{tsubab(sortbytemoresubnew,	sortbytemore);}
SCV	sortlenless	(void)	{tsubab(sortlenlesssubnew,	sortlenless);}
SCV	sortlenmore	(void)	{tsubab(sortlenmoresubnew,	sortlenmore);}
SCV	sortwantentire	(void)	{tsubab(sortwantentiresubnew,	sortwantentire);}
SCV	sortwantrepeat	(void)	{tsubab(sortwantrepeatsubnew,	sortwantrepeat);}
SCV	sortwantsingle	(void)	{tsubab(sortwantsinglesubnew,	sortwantsingle);}
SCV	sortwantunique	(void)	{tsubab(sortwantuniquesubnew,	sortwantunique);}
SCV	sortambit	(void)	{tsubab(sortambitsubnew,	sortambit);}
SCV	sortfree	(void)	{tsubab(sortfreesubnew,	sortfree);}
SCV	sortpre		(void)	{tsubab(sortpresubnew,	sortpre);}
SCV	sortsmp		(void)	{tsubab(sortsmpsubnew,	sortsmp);}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20170707",
	.official=	"20170707",
	.update=	"20200810"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(sort,			"sort");
	aa		(sortsmp,		"sortsmp");
	aa		(sortpre,		"sortpre");
	aa		(sortfree,		"sortfree");
	aa		(sortambit,		"sortambit");
	aa		(sortlenless,		"sortlenless");
	aa		(sortlenmore,		"sortlenmore");
	aa		(sortbitless,		"sortbitless");
	aa		(sortbyteless,		"sortbyteless");
	aa		(sortbytemore,		"sortbytemore");
	aa		(sortpartback,		"sortpartback");
	aa		(sortpartsame,		"sortpartsame");
	aa		(sortwantsingle,	"sortwantsingle");
	aa		(sortwantunique,	"sortwantunique");
	aa		(sortwantrepeat,	"sortwantrepeat");
	aa		(sortwantentire,	"sortwantentire");
	aa_fini		();
};

__attribute__((constructor))
SCV	init				(void)
{	int		a;
	for				(a=6;0xb>a;a++)
	varsortop[a]=			opbyte[0];

/*	varsortop[0].mapuse[1]=		revise_partback;
	varsortop[1].mapuse[1]=		revise_byteless;
	varsortop[2].mapuse[1]=		revise_bytemore;
	varsortop[3].mapuse[1]=		revise_lenless;
	varsortop[4].mapuse[1]=		revise_lenmore;
	varsortop[5].mapuse[1]=		revise_partsame;

	varsortop[6].mapuse[0]=		show_entire;
	varsortop[7].mapuse[0]=		show_repeat;
	varsortop[8].mapuse[0]=		show_single;
	varsortop[9].mapuse[0]=		show_unique;

	varsortop[0xa].mapuse[1]=	revise_bitless;
*/
}
