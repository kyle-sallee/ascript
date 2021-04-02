/*	By Kyle Sallee from 2015 ... 2019 copyrighted.
	Used by ascript.c and argots
	by memcpy.c some functions are provided.
*/

#define		PROGRAM		1
#include	"ascript.h"

/*	With ascript_memcpy
	padding is not required
	with SSE2 opcodes
	memcpy implementation.

	From an argot
	when first invoked
	in the PLT/GOT from symbol name to address resolution
	must become, which is a performance hit.
	On subsequent invocation
	an opcode call opcode jmp combo executes.
	In argot fewer opcodes when required ascript_memcpy
	can be invoked.
	However, from the overhead from the register push/pop
	reduced performance can be anticipated.
	a with the difference between b and a was tried,
	but the compiler doesn't do as told!
*/

	CALIGN	void	ascript_memcpy	(void *a, void const *b, size_t c)
{	if			nay	(8>=c)
	goto				tiny;

	if			nay	( c>=0x40)
	for				(;c>=0x40;a+=0x40,b+=0x40,c-=0x40)
	{	__builtin_memcpy	(a,	b,	0x10);
		__builtin_memcpy	(a+0x10,b+0x10,	0x10);
		__builtin_memcpy	(a+0x20,b+0x20,	0x10);
		__builtin_memcpy	(a+0x30,b+0x30,	0x10);
	}

	if			nay	(c==0)
		return;

	if			nay	(c==0x20)
	{	__builtin_memcpy	(a,	b,	0x10);
		__builtin_memcpy	(a+0x10,b+0x10,	0x10);
		return;
	}

	if			nay	(c>=0x20)
	{	__builtin_memcpy	(a,	b,	0x10);
		__builtin_memcpy	(a+0x10,b+0x10,	0x10);
		a+=			0x20;
		b+=			0x20;
		c-=			0x20;
	}

	if			nay	(c==0x10)
	{	__builtin_memcpy	(a,	b,	0x10);
		return;
	}

	if			nay	(c>0x10)
	{	__builtin_memcpy	(a,	b,	0x10);
		a+=			0x10;
		b+=			0x10;
		c-=			0x10;
	}

	tiny:
	if			nay	(c==0x8)
	{	__builtin_memcpy	(a,	b,	0x8);
		return;
	}

	if			nay	(c>0x8)
	{	__builtin_memcpy	(a,	b,	0x8);
		a+=			0x8;
		b+=			0x8;
		c-=			0x8;
	}

	if			nay	(c==0x4)
	{	__builtin_memcpy	(a,	b,	0x4);
		return;
	}

	if			nay	(c>0x4)
	{	__builtin_memcpy	(a,	b,	0x4);
		a+=			0x4;
		b+=			0x4;
		c-=			0x4;
	}

	if			nay	(c>=0x2)
	{	__builtin_memcpy	(a,	b,	0x2);
		a+=			0x2;
		b+=			0x2;
		c-=			0x2;
	}

	if			nay	(c>0)
	{	__builtin_memcpy	(a,	b,	0x1);
	}
}


__attribute__((unused))
static	CALIGN	void	ascript_memcpyb	(void *a, void const *b, size_t c)
{	if			nay	(8>=c)
	goto				tiny;

	if			nay	( c>=0x40)
	for				(;c>=0x40;a+=0x40,b+=0x40,c-=0x40)
	{	__builtin_memcpy	(a,	b,	0x10);
		__builtin_memcpy	(a+0x10,b+0x10,	0x10);
		__builtin_memcpy	(a+0x20,b+0x20,	0x10);
		__builtin_memcpy	(a+0x30,b+0x30,	0x10);
	}

	if			nay	(c>=0x20)
	{	__builtin_memcpy	(a,	b,	0x10);
		__builtin_memcpy	(a+0x10,b+0x10,	0x10);
		a+=			0x20;
		b+=			0x20;
		c-=			0x20;
	}

	if			nay	(c==0x10)
	{	__builtin_memcpy	(a,	b,	0x10);
		return;
	}

	if			nay	(c>0x10)
	{	__builtin_memcpy	(a,	b,	0x10);
		a+=			0x10;
		b+=			0x10;
		c-=			0x10;
	}

	tiny:
	switch				(c)
	{	case	8:	__builtin_memcpy	(a,b,0x8);return;
		case	7:	__builtin_memcpy	(a,b,0x7);return;
		case	6:	__builtin_memcpy	(a,b,0x6);return;
		case	5:	__builtin_memcpy	(a,b,0x5);return;
		case	4:	__builtin_memcpy	(a,b,0x4);return;
		case	3:	__builtin_memcpy	(a,b,0x3);return;
		case	2:	__builtin_memcpy	(a,b,0x2);return;
		case	1:	__builtin_memcpy	(a,b,0x1);return;
		case	0:	return;
	}
}

__attribute__((unused))
static	CALIGN	void	ascript_memcpyc	(void *a, void const *b, size_t c)
{	if			yay	(0x20>c)
	goto				tiny;

	if			nay	( c>=0x40)
	for				(;c>=0x40;a+=0x40,b+=0x40,c-=0x40)
	{	__builtin_memcpy	(a,	b,	0x10);
		__builtin_memcpy	(a+0x10,b+0x10,	0x10);
		__builtin_memcpy	(a+0x20,b+0x20,	0x10);
		__builtin_memcpy	(a+0x30,b+0x30,	0x10);
	}

	if			nay	(c>=0x20)
	{	__builtin_memcpy	(a,	b,	0x10);
		__builtin_memcpy	(a+0x10,b+0x10,	0x10);
		a+=			0x20;
		b+=			0x20;
		c-=			0x20;
	}

	tiny:
	switch				(c)
	{	case	0x1f:	__builtin_memcpy	(a,b,0x1f);return;
		case	0x1e:	__builtin_memcpy	(a,b,0x1e);return;
		case	0x1d:	__builtin_memcpy	(a,b,0x1d);return;
		case	0x1c:	__builtin_memcpy	(a,b,0x1c);return;
		case	0x1b:	__builtin_memcpy	(a,b,0x1b);return;
		case	0x1a:	__builtin_memcpy	(a,b,0x1a);return;
		case	0x19:	__builtin_memcpy	(a,b,0x19);return;
		case	0x18:	__builtin_memcpy	(a,b,0x18);return;
		case	0x17:	__builtin_memcpy	(a,b,0x17);return;
		case	0x16:	__builtin_memcpy	(a,b,0x16);return;
		case	0x15:	__builtin_memcpy	(a,b,0x15);return;
		case	0x14:	__builtin_memcpy	(a,b,0x14);return;
		case	0x13:	__builtin_memcpy	(a,b,0x13);return;
		case	0x12:	__builtin_memcpy	(a,b,0x12);return;
		case	0x11:	__builtin_memcpy	(a,b,0x11);return;
		case	0x10:	__builtin_memcpy	(a,b,0x10);return;
		case	0xf:	__builtin_memcpy	(a,b,0x0f);return;
		case	0xe:	__builtin_memcpy	(a,b,0x0e);return;
		case	0xd:	__builtin_memcpy	(a,b,0x0d);return;
		case	0xc:	__builtin_memcpy	(a,b,0x0c);return;
		case	0xb:	__builtin_memcpy	(a,b,0x0b);return;
		case	0xa:	__builtin_memcpy	(a,b,0x0a);return;
		case	0x9:	__builtin_memcpy	(a,b,0x09);return;
		case	0x8:	__builtin_memcpy	(a,b,0x08);return;
		case	0x7:	__builtin_memcpy	(a,b,0x07);return;
		case	0x6:	__builtin_memcpy	(a,b,0x06);return;
		case	0x5:	__builtin_memcpy	(a,b,0x05);return;
		case	0x4:	__builtin_memcpy	(a,b,0x04);return;
		case	0x3:	__builtin_memcpy	(a,b,0x03);return;
		case	0x2:	__builtin_memcpy	(a,b,0x02);return;
		case	0x1:	__builtin_memcpy	(a,b,0x01);return;
		case	0x0:	return;
	}
}
