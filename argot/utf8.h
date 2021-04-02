/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_UTF8_H
#define		_A_UTF8_H

/*	explicit jump table use precludes function inlining
*/
__attribute__((unused))
__attribute__((noinline))
static	CALIGN	uint32_t	utf8_in_j	(uint8_t **a)
{	static	const	uint8_t	J[0x100]=
	{	&&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1,
		&&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1,

		&&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1,
		&&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1,

		&&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1,
		&&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1,

		&&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1,
		&&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1,

		&&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1,
		&&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1,

		&&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1,
		&&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1,

		&&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1,
		&&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1,

		&&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1,
		&&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1,

		&&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1,
		&&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1,

		&&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1,
		&&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1,

		&&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1,
		&&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1,

		&&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1,
		&&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1,

		&&b2-&&b1, &&b2-&&b1, &&b2-&&b1, &&b2-&&b1, &&b2-&&b1, &&b2-&&b1, &&b2-&&b1, &&b2-&&b1,
		&&b2-&&b1, &&b2-&&b1, &&b2-&&b1, &&b2-&&b1, &&b2-&&b1, &&b2-&&b1, &&b2-&&b1, &&b2-&&b1,

		&&b2-&&b1, &&b2-&&b1, &&b2-&&b1, &&b2-&&b1, &&b2-&&b1, &&b2-&&b1, &&b2-&&b1, &&b2-&&b1,
		&&b2-&&b1, &&b2-&&b1, &&b2-&&b1, &&b2-&&b1, &&b2-&&b1, &&b2-&&b1, &&b2-&&b1, &&b2-&&b1,

		&&b3-&&b1, &&b3-&&b1, &&b3-&&b1, &&b3-&&b1, &&b3-&&b1, &&b3-&&b1, &&b3-&&b1, &&b3-&&b1,
		&&b3-&&b1, &&b3-&&b1, &&b3-&&b1, &&b3-&&b1, &&b3-&&b1, &&b3-&&b1, &&b3-&&b1, &&b3-&&b1,

		&&b4-&&b1, &&b4-&&b1, &&b4-&&b1, &&b4-&&b1, &&b4-&&b1, &&b4-&&b1, &&b4-&&b1, &&b4-&&b1,
		&&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1, &&b1-&&b1,
	};

	uint32_t	b;
	uint8_t		c;
	c=		*(*a)++;

	goto		*(&&b1+J[c]);

	b1:
	return		c;

	b2:
	b=		c&0x1f;
	b<<=		6;
	b|=		*(*a)++&0x3f;
	return		b;

	b3:
	b=		c&0xf;
	b<<=		6;
	b|=		*(*a)++&0x3f;
	b<<=		6;
	b|=		*(*a)++&0x3f;
	return		b;

	b4:
	b=		c&0x7;
	b<<=		6;
	b|=		*(*a)++&0x3f;
	b<<=		6;
	b|=		*(*a)++&0x3f;
	b<<=		6;
	b|=		*(*a)++&0x3f;
	return		b;
}

__attribute__((noinline))
__attribute__((unused))
static	CALIGN	uint32_t	utf8_in	(uint8_t **a)
{	uint32_t	b;
	uint8_t		c;
	c=		*(*a)++;

	if	yay	((c&0x7f)==0)
	goto		ascii;

	switch		(c)
	{	ascii:
		default:
		return	c;

		case	0xc0:
		case	0xc1:
		case	0xc2:
		case	0xc3:
		case	0xc4:
		case	0xc5:
		case	0xc6:
		case	0xc7:
		case	0xc8:
		case	0xc9:
		case	0xca:
		case	0xcb:
		case	0xcc:
		case	0xcd:
		case	0xce:
		case	0xcf:
		case	0xd0:
		case	0xd1:
		case	0xd2:
		case	0xd3:
		case	0xd4:
		case	0xd5:
		case	0xd6:
		case	0xd7:
		case	0xd8:
		case	0xd9:
		case	0xda:
		case	0xdb:
		case	0xdc:
		case	0xdd:
		case	0xde:
		case	0xdf:
		b=	c&0x1f;
		b<<=	6;
		b|=	*(*a)++&0x3f;
		return	b;
		case	0xe0:
		case	0xe1:
		case	0xe2:
		case	0xe3:
		case	0xe4:
		case	0xe5:
		case	0xe6:
		case	0xe7:
		case	0xe8:
		case	0xe9:
		case	0xea:
		case	0xeb:
		case	0xec:
		case	0xed:
		case	0xee:
		case	0xef:
		b=	c&0xf;
		b<<=	6;
		b|=	*(*a)++&0x3f;
		b<<=	6;
		b|=	*(*a)++&0x3f;
		return	b;

		case	0xf0:
		case	0xf1:
		case	0xf2:
		case	0xf3:
		case	0xf4:
		case	0xf5:
		case	0xf6:
		case	0xf7:
		b=	c&0x7;
		b<<=	6;
		b|=	*(*a)++&0x3f;
		b<<=	6;
		b|=	*(*a)++&0x3f;
		b<<=	6;
		b|=	*(*a)++&0x3f;
		return	b;
	}
}

__attribute__((unused))
static	CALIGN	void	utf8_out	(uint8_t **a,uint32_t b)
{	if			yay	(0x80   >b)
		*(*a)++=		b;
	else	if		nay	(0x800  >b)
	{	*(*a)++=		(b>>6)		|0xc0;
		*(*a)++=		(b&0x3f)	|0x80;
	}
	else	if		nay	(0x10000>b)
	{	*(*a)++=		(b>>0xc)	|0xe0;
		*(*a)++=		((b>>6)&0x3f)	|0x80;
		*(*a)++=		(b&0x3f)	|0x80;
	}
	else
	{	*(*a)++=		(b>>0x12)	|0xf7;
		*(*a)++=		((b>>0xc)&0x3f)	|0x80;
		*(*a)++=		((b>>6  )&0x3f)	|0x80;
		*(*a)++=		(b&0x3f)	|0x80;
	}
}

__attribute__((always_inline))
static	inline	uint8_t	utf8_size	(uint8_t *a)
{	uint8_t		b=		*a;
	if			yay	((b&0x80)==0)	return	1;
	if			nay	((b&0x40)==0)	return	1;
	if			nay	((b&0x20)==0)	return	2;
	if			nay	((b&0x10)==0)	return	3;
	if			nay	((b&0x08)==0)	return	4;
							return	1;
}

__attribute__((always_inline))
static	inline	void	utf8_back	(uint8_t **a)
{	if	yay	((*--*a&0xc0)!=0x80)	return;
	if	yay	((*--*a&0xc0)!=0x80)	return;
	if	yay	((*--*a&0xc0)!=0x80)	return;
			   --*a;		return;
/*	if	nay	((*--*a&0xc0)==0x80)	return;
	if	nay	((*--*a&0xc0)==0x80)	return;
	if	nay	((*--*a&0xc0)==0x80)	return;
			   --*a;		return;
*/
}
#endif
