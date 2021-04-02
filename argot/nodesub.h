/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_NODESUB_H
#define		_A_NODESUB_H

SCV	reval_nodesubattr	(VMETA *);
SCV	reval_nodesubfill	(VMETA *);
SCV	reval_nodesubgid	(VMETA *);
SCV	reval_nodesubmode	(VMETA *);
SCV	reval_nodesubsize	(VMETA *);
SCV	reval_nodesubuid	(VMETA *);

SCV	revise_nodesubaim	(VMETA *);
SCV	revise_nodesubattr	(VMETA *);
SCV	revise_nodesubfill	(VMETA *);
SCV	revise_nodesubgid	(VMETA *);
SCV	revise_nodesubmode	(VMETA *);
SCV	revise_nodesubsize	(VMETA *);
SCV	revise_nodesubuid	(VMETA *);

SCV	show_nodesubaim		(VMETA *);
SCV	show_nodesubreal	(VMETA *);

__attribute__((always_inline))
static	inline	void	nodesubaimsubnew(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".aim",A);
	byteinit		(B);
	map_add			(B,PAGE,0);
	B->revise=		revise_nodesubaim;
	B->show=		show_nodesubaim;
}

__attribute__((always_inline))
static	inline	void	nodesubattrsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".attr",A);
	int8init		(B);
	dex8data		(B);
	B->show=		Gz.out.dex8;
	B->reval=		reval_nodesubattr;
	B->revise=		revise_nodesubattr;
}

__attribute__((always_inline))
static	inline	void	nodesubgidsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".gid",A);
	int8init		(B);
	B->reval=		reval_nodesubgid;
	B->revise=		revise_nodesubgid;
}

__attribute__((always_inline))
static	inline	void	nodesubfillsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".fill",A);
	int8init		(B);
	B->reval=		reval_nodesubfill;
	B->revise=		revise_nodesubfill;
}

__attribute__((always_inline))
static	inline	void	nodesubmodesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".mode",A);
	int4init		(B);
	oct8data		(B);
	B->show=		Gz.out.oct4;
	B->reval=		reval_nodesubmode;
	B->revise=		revise_nodesubmode;
}

__attribute__((always_inline))
static	inline	void	nodesubrealsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".real",A);
	map_add			(B,PAGE,0);
	byteinit		(B);
	B->show=		show_nodesubreal;
}

__attribute__((always_inline))
static	inline	void	nodesubsizesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".size",A);
	int8init		(B);
	B->reval=		reval_nodesubsize;
	B->revise=		revise_nodesubsize;
}

__attribute__((always_inline))
static	inline	void	nodesubuidsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".uid",A);
	int8init		(B);
	B->reval=		reval_nodesubuid;
	B->revise=		revise_nodesubuid;
}
#endif
