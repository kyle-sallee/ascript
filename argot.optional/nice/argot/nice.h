/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_NICE_H
#define		_A_NICE_H
#include	<sys/resource.h>
#include	<sys/time.h>

static		void	revise_pid	(VMETA *);
static		void	revise_grp	(VMETA *);
static		void	revise_user	(VMETA *);

static		void	reval_pid	(VMETA *);
static		void	reval_grp	(VMETA *);
static		void	reval_user	(VMETA *);

__attribute__((always_inline))
__attribute__((unused))
static	inline	void	nicepidsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".nice",A);
	int4init		(B);
	B->reval=		reval_pid;
	B->revise=		revise_pid;
}

__attribute__((always_inline))
__attribute__((unused))
static	inline	void	nicepgrpsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".nice",A);
	int8init		(B);
	B->reval=		reval_grp;
	B->revise=		revise_grp;
}

__attribute__((always_inline))
__attribute__((unused))
static	inline	void	niceuidsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".nice",A);
	int8init		(B);
	B->reval=		reval_user;
	B->revise=		revise_user;
}
#endif
