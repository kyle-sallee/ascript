/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_PARA_H
#define		_A_PARA_H

#define		PARA_MAX		0x4000

/*	maps:
	0:	HUGE*2		value 0	byte separated UTF-8 parameter strings
	1:	PARA_MAX*sizeof(char *)	the char *[]
*/

/*
extern	OPERATOR	oppara[1];
*/

__attribute__((always_inline))
static	inline	void	*parabyteaddr	(VMETA *A)
{	return		A->textaddr;
}

__attribute__((always_inline))
static	inline	uint32_t	*parabytelen	(VMETA *A)
{	return		&A->textlen;
}

__attribute__((always_inline))
static	inline	uint8_t		**paraaddrmap	(VMETA *A)
{	return		(uint8_t **)	A->dataaddr;
}

static	inline	uint8_t	*paranext	(uint8_t *a,uint8_t *b)
{	do
	{	if	(a[0x1]==0)	return	a+0x2;
		if	(a[0x2]==0)	return	a+0x3;
		if	(a[0x3]==0)	return	a+0x4;
		if	(a[0x4]==0)	return	a+0x5;
		if	(a[0x5]==0)	return	a+0x6;
		if	(a[0x6]==0)	return	a+0x7;
		if	(a[0x7]==0)	return	a+0x8;
		if	(a[0x8]==0)	return	a+0x9;
		if	(a[0x9]==0)	return	a+0xa;
		if	(a[0xa]==0)	return	a+0xb;
		if	(a[0xb]==0)	return	a+0xc;
		if	(a[0xc]==0)	return	a+0xd;
		if	(a[0xd]==0)	return	a+0xe;
		if	(a[0xe]==0)	return	a+0xf;
		if	(a[0xf]==0)	return	a+0x10;
		if	(a[0x10]==0)	return	a+0x11;
	}	while	((a+=0x10)>b);
					return	a;
}

SCV	reval_para		(VMETA *A)
{	if		nay	(A->datalen==A->textlen)
	return;
	A->datalen=		A->textlen;

	uint8_t		**c=	(uint8_t **)	A->dataaddr;
	uint8_t		*a=	A->textaddr;
	uint8_t		*b=	A->textlen+a;

#pragma GCC unroll 0
	while		yay	(b>a)
	{	*c++=		a;
		a=
		paranext	(a,b);
	};

	*c=			NULL;

	A->value.i=		c-(uint8_t **)	A->dataaddr;
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	parainit	(VMETA *A)
{	A->op=		oppara;
	A->io.flag=	textmapuse;
	A->reval=	reval_para;
	map_add		(A,HUGE*2,PARA_MAX*sizeof(char *));
}
#endif
