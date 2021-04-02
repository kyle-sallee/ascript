/*	By Kyle Sallee in 2020 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef	A_VALUE
#define	A_VALUE	1

CALIGN
__attribute__((always_inline))
static	inline	uint8_t	asbin	(uint8_t *a,uint64_t *z)
{	uint64_t	b;
	uint8_t		c;
	if		nay	((c=*a-'0')>1)
	return			EINVAL;

	for			(a++,b=c;2>(c=*a-'0');a++)
	{	b<<=		1;
		b+=		c;
	}
	*z=			b;
	return			0;
}

CALIGN
__attribute__((always_inline))
static	inline	uint8_t	asoct	(uint8_t *a,uint64_t *z)
{	uint64_t	b;
	uint8_t		c;
	if		nay	((c=*a-'0')>7)
	return			EINVAL;

	for			(a++,b=c;8>(c=*a-'0');a++)
	{	b<<=		3;
		b+=		c;
	}
	*z=			b;
	return			0;
}

CALIGN
__attribute__((always_inline))
static	inline	int8_t	asdenneg(uint8_t *a,uint64_t *z)
{	uint64_t	b;
	uint8_t		c;
	a++;
	if		nay	((c=*a-'0')>9)
	return			EINVAL;

	for			(b=c,a++;0xa>(c=*a-'0');a++)
	{	b*=		0xa;
		b+=		c;
	}

	*z=			-b;
	return			0;
}

CALIGN
__attribute__((always_inline))
static	inline	int8_t	asden	(uint8_t *a,uint64_t *z)
{	if		nay	(*a=='-')
	return	asdenneg	(a,z);

	uint64_t	b;
	uint8_t		c;

	if		nay	((c=*a-'0')>9)
	return			EINVAL;

	for			(a++,b=c;0xa>(c=*a-'0');a++)
	{	b*=		0xa;
		b+=		c;
	}
	*z=			b;
	return			0;
}

CALIGN
__attribute__((always_inline))
static	inline	int8_t	asdex	(uint8_t *a,uint64_t *z)
{
CALIGN
static	const	uint8_t
xX[]=	{  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	    0,   1,   2,   3,   4,   5,   6,   7,
	    8,   9,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  10,  11,  12,  13,  14,  15,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  10,  11,  12,  13,  14,  15,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	};

	uint64_t	b;
	uint8_t		c;

	if		nay	((c=xX[*a])>0xf)
	return			EINVAL;

	for			(a++,b=c;0x10>(c=xX[*a]);a++)
	{	b<<=		4;
		b+=		c;
	}
	*z=			b;
	return			0;
}

CALIGN
__attribute__((always_inline))
static	inline	uint8_t	asfixneg(uint8_t *a,uint64_t *z)
{	uint64_t	b;
	uint8_t		c;

	a++;
	if		nay	((c=*a-'0')>9)
	return			EINVAL;

	for			(a++,b=c;0xa>(c=*a-'0');a++)
	{	b*=		0xa;
		b+=		c;
	}

	int64_t		w=	b<<0x10;
	if		yay	(*a=='.')
	{	uint8_t	e;
		for		(a++,b=0,e=0;0xa>(c=*a-'0');a++,e++)
		{	b*=	0xa;
			b+=	c;
		}
		for		(;4>e;e++,b*=0xa);
		for		(;4<e;e--,b/=0xa);
		b*=		0x10000;
		b+=		   5000;
		b/=		  10000;
		w+=		b;
	}

	*z=			-w;
	return			0;
}

CALIGN
__attribute__((always_inline))
static	inline	uint8_t	asfix	(uint8_t *a,uint64_t *z)
{	if		nay	(*a=='-')
	return	asfixneg	(a,z);

	uint64_t	b;
	uint8_t		c;

	if		nay	((c=*a-'0')>9)
	return			EINVAL;

	for			(a++,b=c;0xa>(c=*a-'0');a++)
	{	b*=		0xa;
		b+=		c;
	}

	int64_t		w=	b<<0x10;
	if		yay	(*a=='.')
	{	uint8_t	e;
		for		(a++,b=0,e=0;0xa>(c=*a-'0');a++,e++)
		{	b*=	0xa;
			b+=	c;
		}
		for		(;4>e;e++,b*=0xa);
		for		(;4<e;e--,b/=0xa);
		b*=		0x10000;
		b+=		   5000;
		b/=		  10000;
		w+=		b;
	}
	*z=			w;
	return			0;
}

CALIGN
__attribute__((always_inline))
static	inline	uint8_t	value	(VLESS *A)
{
/*	A->vam=			A;	*/
	uint8_t		*a=	A->textaddr;
	uint64_t	*b=	&A->value.i;
	uint8_t		c=	a[A->textlen-1];
	uint8_t		e;
	if		nay	(c=='d')	e=	asden	(a,b);	else
	if		nay	(c=='x')	e=	asdex	(a,b);	else
	if		nay	(c=='o')	e=	asoct	(a,b);	else
	if		nay	(c=='f')	e=	asfix	(a,b);	else
	if		nay	(c=='b')	e=	asbin	(a,b);	else
	return			1;
	return			e;
}
#endif
