/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_TRIM_H
#define		_A_TRIM_H
/*
extern	OPERATOR	optrim[5];
*/

static	inline	void	paresubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub			(".pare",A);
	B->op=				optrim;
	B->io.flag=			textmapuse;
}

static	inline	void	fullsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub			(".full",A);
	B->op=				optrim+1;
	B->io.flag=			textmapuse;
}

static	inline	void	headsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub			(".head",A);
	B->op=				optrim+2;
	B->io.flag=			textmapuse;
}

static	inline	void	tailsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub			(".tail",A);
	B->op=				optrim+3;
	B->io.flag=			textmapuse;
}

static	inline	void	hostsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub			(".tail",A);
	B->op=				optrim+4;
	B->io.flag=			textmapuse;
}
#endif
