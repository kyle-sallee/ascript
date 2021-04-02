/*	By Kyle Sallee from 2015 ... 2019 copyrighted.
	Used by ascript.c and argots
	by memcmp.c a function is provided.
*/

#define		PROGRAM		1
#include	"ascript.h"

#if	__SIZEOF_POINTER__	==	4
	CALIGN	int32_t	ascript_memcmp	(void const *a, void const *b, size_t c)
{	uint32_t	A,B;

	uintptr_t	d=		b-a;
	uint8_t		e=		c&3;
	for				(c-=e;c;a+=4,c-=4)
	if			nay	(( (A=*(int32_t *) a  ))!=
					   (B=*(int32_t *)(a+d)))
	{	return
		be32toh			(A)-
		be32toh			(B);
	}

	if			nay	(e==0)
	return				0;

	uintptr_t	f;
	f=				(uintptr_t)a&(PAGE-1);
	if			nay	((f+e)>PAGE)
	goto				safe;
	f=				(uintptr_t)(a+d)&(PAGE-1);
	if			nay	((f+e)>PAGE)
	goto				safe;

	e=				(8-e)*8;
	A=	be32toh			(*(int32_t *) a   );
	B=	be32toh			(*(int32_t *)(a+d));
	A>>=				e;
	B>>=				e;
	return				A-B;

	safe:
	A=				*(uint8_t *) a;
	B=				*(uint8_t *)(a+d);

	for				(e--;e;e--,a++)
	{	A<<=			8;	A+=	*(uint8_t *) a;
		B<<=			8;	B+=	*(uint8_t *)(a+d);
	}
	return				A-B;
}
#else
	CALIGN	int64_t	ascript_memcmp	(void const *a, void const *b, size_t c)
{	uint64_t	A,B;

	uintptr_t	d=		b-a;
	uint8_t		e=		c&7;
	for				(c-=e;c;a+=8,c-=8)
	if			nay	(( (A=*(int64_t *) a  ))!=
					   (B=*(int64_t *)(a+d)))
	{	return
		be64toh			(A)-
		be64toh			(B);
	}

	if			nay	(e==0)
	return				0;

	uintptr_t	f;
	f=				(uintptr_t)a&(PAGE-1);
	if			nay	((f+e)>PAGE)
	goto				safe;
	f=				(uintptr_t)(a+d)&(PAGE-1);
	if			nay	((f+e)>PAGE)
	goto				safe;

	e=				(8-e)*8;
	A=	be64toh			(*(int64_t *) a   );
	B=	be64toh			(*(int64_t *)(a+d));
	A>>=				e;
	B>>=				e;
	return				A-B;

	safe:
	A=				*(uint8_t *) a;
	B=				*(uint8_t *)(a+d);

	for				(e--;e;e--,a++)
	{	A<<=			8;	A+=	*(uint8_t *) a;
		B<<=			8;	B+=	*(uint8_t *)(a+d);
	}
	return				A-B;
}
#endif
