/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_ENV_H
#define		_A_ENV_H
#include	"byte.h"

/*	For openv
	map:
	0:	on request 1 huge page is mapped and env content copied.
	1:	one page of uint8_t **
*/

SCV	show_env		(VMETA *A)
{	if		yay	((A->io.flag&textmapunmap)==0)
	map_add			(A,HUGE,0);

	uint8_t		*a=	A->textaddr,
			*b,
			**c=	(uint8_t **)	A->dataaddr;
	uint32_t	d;

	for			(;b=*c;c++)
	{	d=	strlena	(b);
		memcpya		(a,b,d);
		a+=		d+1;
	}

	A->textlen=		a-	A->textaddr;
}

__attribute__((always_inline))
static	inline	void	envinit	(VMETA *A)
{	A->op=		openv;
	A->show=	show_env;
	map_add		(A,0,PAGE);
}

__attribute__((always_inline))
static	inline	void	envbyteinit	(VMETA *A)
{	byteinit	(A);
	map_add		(A,ENV_BYTE_MAX,0);
}
#endif
