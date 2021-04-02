/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"

OPERATOR	varendianop[6];

SCV	show_be16		(VMETA *A)
{	reval			(A->host);
	VMETA		*B=	 A->host;

	*(uint16_t *)
	A->textaddr=
	htobe16			(B->value.i);
}

static	inline	void	be16init(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".be16",A);
	B->op=			varendianop;
	B->textlen=		2;
	B->show=		show_be16;
}

SCV	equal_be16		(void)
{	VMETA		*A=	Gz.to[0],
			*B=	Gz.to[1],
			*C=	A->host;

	C->value.i=
	be16toh			(*(uint16_t *)	B->textaddr);
	*Gz.at=			equal_be16;
	argot_next		();
}


/*
SCV	reval_be16		(VMETA *A)
{	VMETA		*B=	A->host;
*/
/*	intwant			(B);	*/
/*	A->value.i=		B->value.i;
}
*/

SCV	show_be32		(VMETA *A)
{	reval			(A->host);
	VMETA		*B=	 A->host;

	*(uint32_t *)
	A->textaddr=
	htobe32			(B->value.i);
}

static		void	be32init(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".be32",A);
	B->op=			varendianop+1;
	B->textlen=		4;
	B->show=		show_be32;
}

SCV	equal_be32		(void)
{	VMETA		*A=	Gz.to[0],
			*B=	Gz.to[1],
			*C=	A->host;

	C->value.i=
	be32toh			(*(uint32_t *)	B->textaddr);
	*Gz.at=			equal_be32;
	argot_next		();
}

/*
SCV	reval_be32		(VMETA *A)
{	VMETA		*B=	A->host;
	intwant			(B);
	A->value.i=		B->value.i;
}
*/

SCV	show_be64		(VMETA *A)
{	reval			(A->host);
	VMETA		*B=	 A->host;

	*(uint64_t *)
	A->textaddr=
	htobe64			(B->value.i);
}

static	inline	void	be64init(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".be64",A);
	B->op=			varendianop+2;
	B->textlen=		8;
	B->show=		show_be64;
}

SCV	equal_be64		(void)
{	VMETA		*A=	Gz.to[0],
			*B=	Gz.to[1],
			*C=	A->host;

	C->value.i=
	be64toh			(*(uint64_t *)	B->textaddr);
	*Gz.at=			equal_be64;
	argot_next		();
}

/*
SCV	reval_be64		(VMETA *A)
{	VMETA		*B=	A->host;
	intwant			(B);
	A->value.i=		B->value.i;
}
*/

SCV	show_le16		(VMETA *A)
{	reval			(A->host);
	VMETA		*B=	 A->host;

	*(uint16_t *)
	A->textaddr=
	htole16			(B->value.i);
}

static	inline	void	le16init(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".le16",A);
	B->op=			varendianop+3;
	B->textlen=		2;
	B->show=		show_le16;
}

SCV	equal_le16		(void)
{	VMETA		*A=	Gz.to[0],
			*B=	Gz.to[1],
			*C=	A->host;

	C->value.i=
	le16toh			(*(uint16_t *)	B->textaddr);
	*Gz.at=			equal_le16;
	argot_next		();
}

/*
SCV	reval_le16		(VMETA *A)
{	VMETA		*B=	A->host;
	intwant		(B);
	A->value.i=		B->value.i;
}
*/

SCV	show_le32		(VMETA *A)
{	reval			(A->host);
	VMETA		*B=	 A->host;

	*(uint32_t *)
	A->textaddr=
	htole32		(B->value.i);
}

static	inline	void	le32init(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".le32",A);
	B->op=			varendianop+4;
	B->textlen=		4;
	B->show=		show_le32;
}

SCV	equal_le32	(void)
{	VMETA		*A=	Gz.to[0],
			*B=	Gz.to[1],
			*C=	A->host;

	C->value.i=
	le32toh			(*(uint32_t *)	B->textaddr);
	*Gz.at=			equal_le32;
	argot_next		();
}

/*
SCV	reval_le32		(VMETA *A)
{	VMETA		*B=	A->host;
	intwant			(B);
	A->value.i=		B->value.i;
}
*/

SCV	show_le64		(VMETA *A)
{	reval			(A->host);
	VMETA		*B=	 A->host;

	*(uint64_t *)
	A->textaddr=
	htole64			(B->value.i);
}

static	inline	void	le64init(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".le64",A);
	B->op=			varendianop+5;
	B->textlen=		8;
	B->show=		show_le64;
}

SCV	equal_le64		(void)
{	VMETA		*A=	Gz.to[0],
			*B=	Gz.to[1],
			*C=	A->host;

	C->value.i=
	le64toh			(*(uint64_t *)	B->textaddr);
	*Gz.at=			equal_le64;
	argot_next		();
}

/*
SCV	reval_le64		(VMETA *A)
{	VMETA		*B=	A->host;
	intwant			(B);
	A->value.i=		B->value.i;
}
*/

__attribute__((cold))
static		void	endian	(void)
{	argot_next	();
}

SCV	be16	(void)	{tsubab(be16init,be16);}
SCV	be32	(void)	{tsubab(be32init,be32);}
SCV	be64	(void)	{tsubab(be64init,be64);}
SCV	le16	(void)	{tsubab(le16init,le16);}
SCV	le32	(void)	{tsubab(le32init,le32);}
SCV	le64	(void)	{tsubab(le64init,le64);}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180318",
	.official=	"20180318",
	.update=	"20200819"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(endian,	"endian");
	aa		(be16,		"be16");
	aa		(be32,		"be32");
	aa		(be64,		"be64");
	aa		(le16,		"le16");
	aa		(le32,		"le32");
	aa		(le64,		"le64");
	aa_fini		();
};

__attribute__((constructor))
SCV	init				(void)
{	varendianop[0].equal=		equal_be16;
	varendianop[1].equal=		equal_be32;
	varendianop[2].equal=		equal_be64;
	varendianop[3].equal=		equal_le16;
	varendianop[4].equal=		equal_le32;
	varendianop[5].equal=		equal_le64;

/*	varendianop[0].byte_compat=
	varendianop[1].byte_compat=
	varendianop[2].byte_compat=
	varendianop[3].byte_compat=
	varendianop[4].byte_compat=
	varendianop[5].byte_compat=	1;
*/
}
