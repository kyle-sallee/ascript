/*	By Kyle Sallee in 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_TREK_H
#define		_A_TREK_H

	struct	COMPOSITE_T;
typedef	struct	COMPOSITE_T	COMPOSITE;

typedef	struct	COMPOSITE_T
{		__attribute__((aligned(0x10)))
		uint8_t		name	[LABEL_SIZE];
		uint8_t		wrap;
}		COMPOSITE;

extern		COMPOSITE	*composite_tag;

__attribute__((hot))
__attribute__((unused))
__attribute__((always_inline))
static	inline	uint16_t	jidx	(uint8_t const *a)
{	return	bit128_to_bit16	(a);
}

__attribute__((hot))
__attribute__((unused))
__attribute__((always_inline))
static	inline	PART_REFER	**farm	(uint8_t const *a)
{	return			&Gz.hash.far[jidx(a)];
}

__attribute__((hot))
__attribute__((unused))
__attribute__((always_inline))
static	inline	PART_REFER	**nearm	(uint8_t const *a,farint b)
{	return			&Gz.hash.near[(uint16_t)(jidx(a)+b)];
}

__attribute__((always_inline))
static	inline	int	near_match	(uint64_t   const  a
					,uint64_t   const  b
					,PART_REFER const *c
					,farint     const  d)
{	if			yay	(c->fore==NULL)
	return				1;
	if			yay	(*(uint64_t *)(c->name+0)==a)
	if			yay	(*(uint64_t *)(c->name+8)==b)
	if			yay	(partfar(NULL)==d)
	return				1;
	return				0;
}

__attribute__((always_inline))
static	inline	int	far_match	(uint64_t   const  a
					,uint64_t   const  b
					,PART_REFER const *c)
{	if			yay	(c->fore==NULL)
	return				1;
	if			yay	(*(uint64_t *)(c->name+0)==a)
	if			yay	(*(uint64_t *)(c->name+8)==b)
	return				1;
	return				0;
}

__attribute__((hot))
__attribute__((unused))
SCV	(**nearfind_fast(uint8_t const *a,farint b))(void)
{	PART_REFER	*A=
	*nearm				(a,b);

	uint64_t	d=		*(uint64_t *)(a+0),
			e=		*(uint64_t *)(a+8);

	while				(1)
	{	if		yay	(near_match(d,e,A,b))
		return			A->part;
		else
		A=			A->fore;
	}
}

__attribute__((hot))
__attribute__((unused))
SCV	(**nearfind_faster		(uint8_t const *a
					,farint b
					,uint16_t c)
					)(void)
{	PART_REFER	*A=		Gz.hash.near[(uint16_t)((b+c))];

	uint64_t	d=		*(uint64_t *)(a+0),
			e=		*(uint64_t *)(a+8);

	while				(1)
	{	if		yay	(near_match(d,e,A,b))
		return			A->part;
		else
		A=			A->fore;
	}
}

__attribute__((hot))
__attribute__((unused))
SCV	(**nearfind_safe(uint8_t const *a,farint b))(void)
{	PART_REFER	*A=
	*nearm				(a,b);

	uint64_t	d=		*(uint64_t *)(a+0),
			e=		*(uint64_t *)(a+8);

	while				(A)
	{	if		yay	(near_match(d,e,A,b))
		return			A->part;
		else
		A=			A->fore;
	}
	return				NULL;
}

__attribute__((hot))
__attribute__((unused))
SCV	(**farmfind_fast(uint8_t const *a,PART_REFER **L))(void)
{	PART_REFER	*A=		*L;

	if		yay		(A->fore!=NULL)
	return				A->part;

	uint64_t	d=		*(uint64_t *)(a+0),
			e=		*(uint64_t *)(a+8);

	while				(1)
	{	if		yay	(far_match(d,e,A))
		return			A->part;
		else
		A=			A->fore;
	}
}

__attribute__((hot))
__attribute__((unused))
SCV	(**farfind_fast(uint8_t const *a))(void)
{	uint16_t	c=
	bit128_to_bit16			(a);
	PART_REFER	*A=		Gz.hash.far[c];

	if			yay	(A->fore==NULL)
	return				A->part;

	uint64_t	d=		*(uint64_t *)(a+0),
			e=		*(uint64_t *)(a+8);

	while				(1)
	{	if		yay	(far_match(d,e,A))
		return			A->part;
		else
		A=			A->fore;
	}
}

__attribute__((hot))
__attribute__((unused))
SCV	(**farfind_safe(uint8_t const *a))(void)
{	uint16_t	c=
	bit128_to_bit16			(a);
	PART_REFER	*A=		Gz.hash.far[c];

	uint64_t	d=		*(uint64_t *)(a+0),
			e=		*(uint64_t *)(a+8);

	while			(A)
	{	if		yay	(far_match(d,e,A))
		return			A->part;
		else
		A=			A->fore;
	}
	return				NULL;
}
#endif
