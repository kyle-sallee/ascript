/*	By Kyle Sallee in 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_SOFTREQ_H
#define		_A_SOFTREQ_H
#include	"byte.h"

extern	OPERATOR	opsoftreq[8];

/*	In two passes index are generated.
	In pass 1 the counts are accumulated.
	In pass 2 the address space is mapped and
	the addresses are copied.
	Thus for the software name amount
	25% more than the directory file amount
	will definitely suffice.
*/

/*	type softreq maps:
	map[1]			RMETA
*/

/*
enum	IVAL	{	i_required,
			i_optional,
			i_selected,
			i_must_optional,
			i_must_selected,
			i_want_optional,
			i_want_selected,
		};
*/

enum	QVAL	{	q_moil,	q_wait	};

	struct	REF_T;
typedef	struct	REF_T	REF;

	struct	RMAP_T;
typedef	struct	RMAP_T	RMAP;

	struct	RMETA_T;
typedef	struct	RMETA_T	RMETA;

	struct	SMAP_T;
typedef	struct	SMAP_T	SMAP;

	struct	SOFT_T;
typedef	struct	SOFT_T	SOFT;

typedef	struct	REF_T
{	SOFT		**next;		/* Where the next can be placed */
	SOFT		**at;		/* Where the map  begins */
	size_t		size;		/* in bytes */
}		REF;

typedef	struct	RMAP_T
{	SOFT		**next;		/* next available address */
	SOFT		**at;		/* where the list begins */
					/* faster memcpy function */
	uint32_t	amount;		/* pointer amount */
	uint8_t		done;		/* use it */
	uint8_t		entered;	/* recursion detecton */
	uint32_t	count_done;
}		RMAP;

typedef	struct	SOFT_T
{	__attribute__((aligned(0x10)))
	uint8_t		name	[0x80];
	SOFT		*next;
	size_t		len;		/* length for name */
	RMAP		rmap	[7];
	uint8_t		*raw	[3];	/* required optional selected file content */
	uint32_t	size	[3];	/* req opt sel file size +1 */
	uint32_t	unique;		/* to indicate in use */
	uint16_t	index;
	uint8_t		lite;
}		SOFT;

typedef	struct	SMAP_T			/* stores SOFT not SOFT pointer */
{	SOFT		*next;		/* next available address */
	SOFT		*at;		/* where the list begins */
	size_t		size;		/* at's map size in bytes */
	uint32_t	total;		/* software project amount */
}		SMAP;

typedef	struct
{	VMETA		*must_optional,
			*must_selected,
			*ready_load,
			*ready_moil,
			*topic_list,
			*want_optional,
			*want_selected;
}	SVAR;

typedef	struct	RMETA_T
{	SOFT		*name	[0x10000];	/*SOFT name to address matrix*/
	SVAR		var;
	SMAP		smap;
	REF		ref	[7];
	RMAP		queue	[2];
	VMETA		*A;
	uint8_t		pn	[0x20][PAGE];
	uint32_t	unique;
	uint8_t		wait;
	pid_t		pid	[2];
	void		*stack	[2];
}		RMETA;

__attribute__((always_inline))
static	inline	 RMETA *	rmeta	(VMETA *A)
{	return	(RMETA *)	A->dataaddr;
}

static		void	softreqfree	(VMETA *);

static	void	show_load	(VMETA *);
static	void	show_moil	(VMETA *);

static		void	softreqsubnew	(VMETA *A)
{	A->op=				opsoftreq;
	map_add				(A,0,sizeof(RMETA));
	A->free=			softreqfree;
	RMETA		*R=
	rmeta				(A);
	R->A=				A;

	VMETA		*B=
	var_new_sub			(".must.optional",A);
	R->var.must_optional=		B;
	byteinit			(B);
	B->op=				opsoftreq+1;
	map_add				(B,HUGE,0);

	VMETA		*C=
	var_new_sub			(".must.selected",A);
	R->var.must_selected=		C;
	byteinit			(C);
	C->op=				opsoftreq+2;
	map_add				(C,HUGE,0);

	VMETA		*D=
	var_new_sub			(".ready.load",A);
	R->var.ready_load=		D;
	byteinit			(D);
	D->op=				opsoftreq+3;
	D->show=			show_load;
	D->io.flag&=			~textmapuse;
	map_add				(D,PAGE,0);

	VMETA		*E=
	var_new_sub			(".ready.moil",A);
	R->var.ready_moil=		E;
	byteinit			(E);
	E->op=				opsoftreq+4;
	E->show=			show_moil;
	E->io.flag&=			~textmapuse;
	map_add				(E,PAGE,0);

	VMETA		*F=
	var_new_sub			(".topic.list",A);
	R->var.topic_list=		F;
	byteinit			(F);
	F->op=				opsoftreq+5;

	VMETA		*G=
	var_new_sub			(".want.optional",A);
	R->var.want_optional=		G;
	byteinit			(G);
	G->op=				opsoftreq+6;
	map_add				(G,HUGE,0);

	VMETA		*H=
	var_new_sub			(".want.selected",A);
	R->var.want_selected=		H;
	byteinit			(H);
	H->op=				opsoftreq+7;
	map_add				(H,HUGE,0);
}

static	inline	void	slay	(pid_t a)
{	if			(a)
	kill			(a,9);
}

static		void	softreqfree	(VMETA *A)
{	RMETA		*R=
	rmeta				(A);

	if			nay	(R->wait==1)
	{	slay			(R->pid[0]);
		slay			(R->pid[1]);
	}

	uint8_t		a;
	for				(a=0;7>a;a++)
	if				(R->ref[a].size)
	cede				(R->ref[a].at,R->ref[a].size);

	cede				(R->smap.at,R->smap.size);
	cede				(A->dataaddr,A->datasize);
	var_free			(A);
}
#endif
