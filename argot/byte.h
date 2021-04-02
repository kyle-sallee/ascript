/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_BYTE_H
#define		_A_BYTE_H

/*	map 0	the byte content
	map 1	the integer or decimal conversion
*/

__attribute__((always_inline))
__attribute__((unused))
static	inline	void	byteinit	(VMETA *A)
{	A->op=		opbyte;
	A->io.flag=	textmapuse;
}

__attribute__((always_inline))
__attribute__((unused))
static	inline	void	byteconstinit	(VMETA *A)
{	A->op=		opbyteconst;
	A->io.flag=	textmapuse;
}

__attribute__((always_inline))
__attribute__((unused))
static	inline	void	bytepageinit	(VMETA *A)
{	A->op=				opbyte;
	A->io.flag=			textmapuse|textmapunmap;
	A->textaddr=	pp		();
	A->textsize=			PAGE;
}

__attribute__((always_inline))
__attribute__((unused))
static	inline	void	byteioinit	(VMETA *A)
{	A->op=				opbyte;
/*	A->io.flag=			textmapuse|textmapunmap;	*/
	map_add				(A,0x20000,0);
}

__attribute__((always_inline))
__attribute__((unused))
static	inline	void	bytesizeinit	(VMETA *A)
{	VMETA		*B=	parapass(arga(NULL));
	A->op=				opbyte;
	map_add				(A,B->value.i4.l,0);
}

__attribute__((always_inline))
__attribute__((unused))
static	inline	void	bytehugeinit	(VMETA *A)
{	A->op=				opbyte;
	A->io.flag=			textmapuse|textmapunmap;
	A->textsize=			HUGE;
	A->io.flag=			textmapuse|textmapunmap;
	void		*a=	mmapanon(HUGE*2,MAP_PRIVATE);
	uintptr_t	b=		(uintptr_t)	a;
	b+=				  HUGE;
	b&=				~(HUGE-1);
	void		*c=
	A->textaddr=			(void *)	b;
	void		*d=		a+HUGE*2;
	void		*e=		c+HUGE;
	uintptr_t	f=		c-a;
	uintptr_t	g=		d-e;
	munmap				(a,f);
	munmap				(e,g);
}
#endif
