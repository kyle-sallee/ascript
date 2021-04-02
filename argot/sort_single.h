/*	By Kyle Sallee in 2015 and 2016 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"ksort.h"

__attribute__((unused))
static	CALIGN	SORT_INDEX	*select_single	(SORT_INDEX *A)
{	SORT_INDEX	*	const
	C=			A;
	for			(;A;A=A->next)	A->again=	0;
	return			C;
}

/* The following compare is never invoked */
/*
static	inline	int	compare	(void const *a,void const *b)
{	return	0;
}
*/

/*
static uint8_t an[0x10]="sortcullsingle";
static	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.email=		"kyle.sallee@gmail.com",
	.home=		"https://kyle-sallee.github.io/ascript/",
	.create=	"20170707",
	.official=	"20170707",
	.update=	"20200201"
};
__attribute__((constructor)) static void _argot_init(void){argot_new(_sortcullsingle,an,&AI);}
__attribute__((destructor )) static void _argot_fini(void){argot_del(_sortcullsingle,an);}
*/
