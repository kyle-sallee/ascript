/*	By Kyle Sallee in 2015 and 2016 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"ksort.h"

__attribute__((unused))
static	CALIGN	SORT_INDEX	*select_unique	(SORT_INDEX *A)
{	SORT_INDEX		*B,*C;
	for			(;A;A=A->next)
	if		nay	(A->again==0)
	break;

	if		nay	(A==NULL)
	return			NULL;

	C=
	B=			A;

	for			(A=A->next;A;A=A->next)
	if			(A->again==0)
	{	B->next=	A;
		B=		A;
	}

	B->next=		NULL;
	return			C;
}

/*
static uint8_t an[0x10]="sortunique";
static	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.email=		"kyle.sallee@gmail.com",
	.home=		"https://kyle-sallee.github.io/ascript/",
	.create=	"20170707",
	.official=	"20170707",
	.update=	"20120201"
};
__attribute__((constructor)) static void _argot_init(void){argot_new(_sortunique,an,&AI);}
__attribute__((destructor )) static void _argot_fini(void){argot_del(_sortunique,an);}
*/
