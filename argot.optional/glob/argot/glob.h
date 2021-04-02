/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef	_A_GLOB_H
#define	_A_GLOB_H
#include	<glob.h>

extern	OPERATOR	opglob[1];

typedef	struct
{	VALUE		a;
	glob_t		t;	/* typedef struct glob_t */
	int		flag;
	uint32_t	c;	/* the index */
}	GLOBDATA;

__attribute__((always_inline))
static	inline	 GLOBDATA *	globdata	(VMETA *A)
{	return	(GLOBDATA *)	A->dataaddr;
}

__attribute__((unused))
__attribute__((noinline))
SCV	globfree_		(VMETA *A)
{	GLOBDATA	*a=
	globdata		(A);

	A->textlen=		0;
	A->textaddr[0]=	0;
	if		yay	( a->t.gl_pathv!=NULL)
	globfree		(&a->t);
	memset			(a,0,sizeof(GLOBDATA));
}

__attribute__((unused))
__attribute__((noinline))
SCV	globend		(VMETA *A)
{	globfree_	(A);
	var_free	(A);
}

__attribute__((always_inline))
static	inline	void	globsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".glob",A);
	B->op=			opglob;
	B->free=		globend;
	B->io.flag=		textmapuse;
	map_add			(B,PAGE,PAGE);
	GLOBDATA	*b=
	globdata		(B);
	b->flag=		GLOB_NOSORT;
}
#endif
