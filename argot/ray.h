/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_RAY_H
#define		_A_RAY_H
#include	"byte.h"
#include	"int.h"
#define		RAY_MAX		0x40000

#define		RAYMETA_MAPADDR	textaddr
#define		RAYDATA_MAPADDR	dataaddr

/*
extern	OPERATOR	opray[1];
*/

typedef	struct
{	uint8_t		name[VAR_NAME_SIZE*2];
	VALUE		pad,now,max;
}	RAYMETA;


/*	opray maps
	textVMETA *[RAY_MAX]
	dataRAYMETA used by .now and .max

	map[?]	the selected varaible's name.
*/

__attribute__((always_inline))
static	inline	RAYMETA	*raymetaaddr	(VMETA *A)
{	return		(RAYMETA *)	A->RAYMETA_MAPADDR;
}

__attribute__((always_inline))
static	inline	VMETA **raydataaddr	(VMETA *A)
{	return		(VMETA **)	A->RAYDATA_MAPADDR;
}

__attribute__((always_inline))
static	inline	VALUE	*raynowaddr	(VMETA *A)
{	return		&raymetaaddr	(A)->now;
}

__attribute__((always_inline))
static	inline	VALUE	*raymaxaddr	(VMETA *A)
{	return		&raymetaaddr	(A)->max;
}

SCV	reval_now	(VMETA *A)
{	A->value.i=	raynowaddr(A->host)->i;
}

SCV	revise_now	(VMETA *A)
{	raynowaddr(A->host)->i=	A->value.i;
}

SCV	reval_max	(VMETA *A)
{	A->value.i=	raymaxaddr(A->host)->i;
}

/*
SCV	revise_max	(VMETA *A)
{	raymaxaddr(A->host)->i=	A->value.i;
}
*/

__attribute__((always_inline))
static	inline	VMETA	**rayrefaddr	(VMETA *A)
{	return		raydataaddr	(A)+
			raynowaddr	(A)->i;
}

SCV	show_ray		(VMETA *A)
{	VMETA		*C=
	*rayrefaddr		(A->host);
	memcpya			(A->textaddr,C->name,
				 A->textlen= C->len);
}

__attribute__((unused))
static	inline	void	raysubnew	(VMETA *A)
{	A->op=		opray;
	map_add		(A,sizeof(RAYMETA),sizeof(VMETA *)*RAY_MAX);
}

__attribute__((unused))
static	inline	void	raynowsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".now",A);
	int4init		(B);

	B->reval=		reval_now;
	B->revise=		revise_now;
/*	B->val=			(void *)
	raynowaddr		(A);
*/
}

__attribute__((unused))
static	inline	void	raymaxsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".max",A);
	int4init		(B);

	B->reval=		reval_max;
/*	B->revise=		revise_max;	*/

/*	B->val=			(void *)
	raymaxaddr		(A);
*/
}

__attribute__((unused))
static	inline	void	raynamesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".name",A);
	byteinit		(B);
	B->show=		show_ray;
}
#endif
