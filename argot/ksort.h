/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_KSORT_H
#define		_A_KSORT_H

#ifndef		_GNU_SOURCE
#define		_GNU_SOURCE
#endif
#include	"ascript.h"
#include	"sire.h"
#include	<alloca.h>
#include	<endian.h>
#include	<sched.h>

/*
extern		int64_t		SMP_SORT;
*/

	struct	SORT_INDEX_STRUCT;
typedef	struct	SORT_INDEX_STRUCT	SORT_INDEX;

typedef	struct	SORT_INDEX_STRUCT
{	void		*text;
	SORT_INDEX	*next;
	SORT_INDEX	*last;
/*	void		*origin;	*/
	uint32_t	len;
	uint32_t	again;
}	SORT_INDEX;

typedef	struct
{	void	(*sort_selection)	(void *,int const);
	void	(*addr_selection)	(SORT_INDEX *);
	int	(*line_selection)	(uint8_t *,size_t const,int const);
}	SORT_FUNC;

PALIGN	SORT_FUNC	sort_func;

typedef	struct
{	SORT_INDEX	*	const	data;
	int			const	limit;
}	KSORT_DATA;

static	inline	int	compare			(SORT_INDEX const *,
						 SORT_INDEX const *);
__attribute__((unused))
/*
__attribute__((noinline))
*/
__attribute__((always_inline))
inline
static	CALIGN	SORT_INDEX	*kmerge	(SORT_INDEX *L, SORT_INDEX *R)
{	SORT_INDEX	*d,*I;

/*	SORT_INDEX	* const	LL=	L->last;
	SORT_INDEX	* const RL=	R->last;
*/

	int	c=	compare		(L,R);
	if			yay	(c<0)
	{	d=			L;
		goto			left;
	}
	else
	if			yay	(c>0)
	{	d=			R;
		goto			right;
	}
	else
	{	d=			L;
		goto			both;
	}

	again:
	c=	compare			(L,R);

	if			yay	(c<0)
	{	I->next=		L;
		left:
		I=			L;
		L=			L->next;
		if		yay	(L!=NULL)	goto	again;
		else					goto	left_done;
	}
	else
	if			yay	(c>0)
	{	I->next=		R;
		right:
		I=			R;
		R=			R->next;
		if		yay	(R!=NULL)	goto	again;
		else					goto	right_done;
	}
	else
	{	I->next=		L;
		both:
		L->again+=		R->again+1;
		I=			L;
		L=			L->next;
		R=			R->next;
		if		nay	(R==NULL)	goto	right_done;
		if		nay	(L==NULL)	goto	left_done;
							goto	again;
	}

	left_done:
	I->next=			R;
/*	d->last=			RL;	*/
	return				d;

	right_done:
	I->next=			L;
/*	d->last=			LL;	*/
	return				d;
}

__attribute__((unused))
/*
__attribute__((noinline))
*/
__attribute__((always_inline))
inline
static	CALIGN	SORT_INDEX	*kmergeT(SORT_INDEX *L, SORT_INDEX *R)
{	SORT_INDEX	*d,*I;

	SORT_INDEX	* const	LL=	L->last;
	SORT_INDEX	* const RL=	R->last;

	int	c=	compare		(L,R);
	if			yay	(c<0)
	{
		c=	compare		(LL,R);
		if		nay	(c<0)
		{	LL->next=	R;
			L->last=	RL;
/*write(2,"L",1);*/
			return		L;
		}

		d=			L;
		goto			left;
	}
	else
	if			yay	(c>0)
	{
		c=	compare		(RL,L);
		if		nay	(c<0)
		{	RL->next=	L;
			R->last=	LL;
/*write(2,"R",1);*/
			return		R;
		}

		d=			R;
		goto			right;
	}
	else
	{	d=			L;
		goto			both;
	}

	again:
	c=	compare			(L,R);

	if			yay	(c<0)
	{	I->next=		L;
		left:
		I=			L;
		L=			L->next;
		if		yay	(L!=NULL)	goto	again;
		else					goto	left_done;
	}
	else
	if			yay	(c>0)
	{	I->next=		R;
		right:
		I=			R;
		R=			R->next;
		if		yay	(R!=NULL)	goto	again;
		else					goto	right_done;
	}
	else
	{	I->next=		L;
		both:
		L->again+=		R->again+1;
		I=			L;
		L=			L->next;
		R=			R->next;
		if		nay	(R==NULL)	goto	right_done;
		if		nay	(L==NULL)	goto	left_done;
							goto	again;
	}

	left_done:
	I->next=			R;
	d->last=			RL;
	return				d;

	right_done:
	I->next=			L;
	d->last=			LL;
	return				d;
}

/*
__attribute__((unused))
__attribute__((noinline))
static	CALIGN	SORT_INDEX	*kmerge21	(SORT_INDEX *L, SORT_INDEX *R)
{	int	c=	compare		(L,R);
	if				(c>0)
	{	R->next=		L;
		return			R;
	}

	if				(c==0)
	{	L->again++;
		return			L;
	}

	SORT_INDEX	*M=		L->next;
	if				(M==NULL)
	{	L->next=		R;
		return			L;
	}

	c=	compare			(M,R);
	if				(c<0)
	{	M->next=		R;
		return			L;
	}

	if				(c>0)
	{	R->next=		M;
		L->next=		R;
		return			L;
	}

	if				(c==0)
	{	M->again=		1;
		return			L;
	}
}
*/

/*__attribute__((noinline))
*/
__attribute__((unused))
__attribute__((always_inline))
inline
static	CALIGN	SORT_INDEX	*kmerge3	(SORT_INDEX * const d)
{	int	c=	compare		(d+0,d+1);

	if			yay	(c<0)		/* 0 < 1 */
	{	c=	compare		(d+1,d+2);

		if		yay	(c<0)
		{	d[0].next=	d+1;
			d[0].last=
			d[1].next=	d+2;
			return		d;		/* 0 1 2 */
		}

		if		yay	(c==0)
		{	d[1].again=	1;
			d[0].last=
			d[0].next=	d+1;
			return		d;		/* 0 1 1 */
		}

							/* 0 < 1, 2 < 1 */
		c=	compare		(d+0,d+2);

		if		yay	(c<0)
		{	d[0].next=	d+2;
			d[0].last=
			d[2].next=	d+1;
			return		d;		/* 0 2 1 */
		}

		if			(c>0)
		{	d[2].next=	d+0;
			d[2].last=
			d[0].next=	d+1;
			return		d+2;		/* 2 0 1 */
		}

		{	d[0].again=	1;
			d[0].last=
			d[0].next=	d+1;
			return		d;		/* 0 0 1 */
		}
	}
	else	if			(c>0)		/* 1 < 0 */
	{	c=	compare		(d+0,d+2);

		if			(c<0)
		{	d[1].next=	d;
			d[1].last=
			d[0].next=	d+2;
			return		d+1;		/* 1 0 2 */
		}

		if			(c==0)
		{	d[0].again=	1;
			d[1].last=
			d[1].next=	d+0;
			return		d+1;		/* 1 0 0 */
		}

							/* 1 < 0, 2 < 0 */
		c=	compare		(d+1,d+2);
		if			(c<0)
		{	d[1].next=	d+2;
			d[1].last=
			d[2].next=	d+0;
			return		d+1;		/* 1 2 0 */
		}

		if			(c>0)
		{	d[2].next=	d+1;
			d[2].last=
			d[1].next=	d+0;
			return		d+2;		/* 2 1 0 */
		}

		{	d[1].again=	1;
			d[1].last=
			d[1].next=	d+0;
			return		d+1;		/* 1 1 0 */
		}
	}
	{						/* 0 == 1 */
		c=	compare		(d+0,d+2);	/* 0 0 ? */
		if			(c<0)
		{	d[0].again=	1;
			d[0].last=
			d[0].next=	d+2;
			return		d;		/* 0 0 2 */
		}
		if			(c>0)
		{	d[0].again=	1;
			d[2].last=
			d[2].next=	d+0;
			return		d+2;		/* 2 0 0 */
		}
		{	d[0].again=	2;
			d[0].last=	d+0;
			return		d+0;		/* 0 0 0 */
		}
	}
}

__attribute__((unused))
static	CALIGN	void	kmerge3_check	(SORT_INDEX * const D)
{	if		(D->again==2)
	if		(D->last==D)
	return;

	if		(D->again==1)
	if		(compare(D,D->next)<0)
	if		(D->last==D->next)
	return;

	if		(D->next->again==1)
	if		(compare(D,D->next)<0)
	if		(D->last==D->next)
	return;

	if		(compare(D,D->next)<0)
	if		(compare(  D->next,D->next->next)<0)
	if		(D->last==D->next->next)
	return;

warnx	("kmerge3 faulty");

}

/* Two or more comparisons when involved
   cmova instruction is not emitted.
*/

__attribute__((unused))
__attribute__((always_inline))
inline
static	CALIGN	SORT_INDEX	*kmerge2	(SORT_INDEX * const D)
{	int		c=
	compare			(D,D+1);

	if		yay	(c<0)
	{	D[0].last=
		D[0].next=	D+1;
		return		D;
	}

	if			(c>0)
	{	D[1].last=
		D[1].next=	D;
		return		D+1;
	}

	{	D[0].again=	1;
		D[0].last=	D;
		return		D;
	}
}

static		SORT_INDEX	*ksorts	(KSORT_DATA const * const,
					 int const,int const);

/* kmerge21 is interesting, but not as fast as simply invoking kmerge3 */
/*
__attribute__((unused))
__attribute__((noinline))
static	CALIGN	SORT_INDEX	*ksorts_simple	(KSORT_DATA const * const A,
					 int const a,int const e)
{	SORT_INDEX	*L,*R;

	if				(e>3)
	{	int
		h=			e/2;
		L=	ksorts		(A,a,h);
		R=	ksorts		(A,a+h,e-h);
		return	kmerge		(L,R);
	}
	else
	{	L=			A->data+a;
		R=			L+2;
		L=	kmerge2		(L);
		if			(e==2)
		return			L;
		else
		return	kmerge21	(L,R);
	}
}
*/

__attribute__((always_inline))
inline
static	CALIGN	SORT_INDEX	*ksortsz(KSORT_DATA const * const A,
					 int const a,int const e)
{	SORT_INDEX * const	L=	A->data+a;
	if				(e==2)
	return	kmerge2			(L);
	return	kmerge3			(L);
}

__attribute__((unused))
__attribute__((noinline))
static	CALIGN	SORT_INDEX	*ksortsT(KSORT_DATA const * const A,
					 int const a,int const e)
{	SORT_INDEX	*L,*R;


	if			nay	(e>3)
	{	int
		h=			e/2;
		L=	ksortsT		(A,a,h);
		R=	ksortsT		(A,a+h,e-h);
		return	kmergeT		(L,R);
	}
	return		ksortsz		(A,a,e);

/*	{	SORT_INDEX	*	const
		L=			A->data+a;
		if			(e==2)
		return	kmerge2		(L);
		else
		return	kmerge3		(L);
	}
*/
}

__attribute__((unused))
__attribute__((noinline))
static	CALIGN	SORT_INDEX	*ksorts	(KSORT_DATA const * const A,
					 int const a,int const e)
{	SORT_INDEX	*L,*R;

	if			yay	(e>0x20)
	{	int
		h=			e/2;
		L=	ksorts		(A,a,h);
		R=	ksorts		(A,a+h,e-h);
		return	kmerge		(L,R);
	}
	return		ksortsT		(A,a,e);
}

typedef	struct
{	pid_t			pid;
	void			*map;
	SORT_INDEX		*si;
	KSORT_DATA	const	*A;
	int 			a;
	int 			e;
}	PDATA;

static		void	ksortc		(PDATA *);

__attribute__((unused))
__attribute__((noinline))
static	CALIGN	int	ksortt		(void *v)
{	PDATA		L,R;
	PDATA		*V=		v;
	int		h=		V->e/2;

	L.A=
	R.A=				V->A;

	L.a=				V->a;
	L.e=				h;
	R.a=				V->a+h;
	R.e=				V->e-h;

	ksortc				(&L);
	ksortc				(&R);

	if				(L.pid)
	{	waitthis		(L.pid,WEXITED);
		munmap			(L.map,PAGE*8);
	}

	if				(R.pid)
	{	waitthis		(R.pid,WEXITED);
		munmap			(R.map,PAGE*8);
	}

	V->si=
	kmerge				(L.si,R.si);
	return				0;
}

__attribute__((unused))
__attribute__((noinline))
static	CALIGN	void	ksortc		(PDATA *M)
{	if			yay	(M->e >= M->A->limit)
	{	M->map=	mmapmust	(PAGE*8,
					 PROT_READ|PROT_WRITE,
					 MAP_ANONYMOUS|MAP_SHARED,-1);

		M->pid=	clone		(ksortt,M->map+PAGE*8,
					 CLONE_VM|CLONE_SIGHAND|SIGCHLD,M);
		if		yay	(M->pid>0)
		pids.now++;
		else
		goto			slow;
	}
	else
	{	slow:
		M->pid=			0;
		M->si=
		ksorts			(M->A,M->a,M->e);
	}
}

/*	While   conceptually similar;
	ksort   and          merge    sort  differ.
	By      merge        sort
	a       dedicated
	2-way   comparison   and
	3-way   comparison
	are     not          required
	are     not          used.
	By      merge        sort
	linked  lists
	are     not          required
	are     not          used.
	ksort   partition    locations
	also    differ.

	Because ksort        design   differs.
	Thus    performance           differs.
	ksort   is           extra    ordinarily fast.

	Identifying and      using  specialized  functions
	to      perform      both   2-way and    3-way comparisons
	are     hallmarks.
	An      index        array  with
	linked  list         concurrent          use
	is      a            hallmark.

	This    method
	sans    permission
	in      other        software     projects
	if      used
	if      copied
	then    copyright    infringement became.

	Do not steal the      fastest sort method!
	Design and   create a faster  sort method!

	If     I     can      create
	a      sort  method
	the    task
	is     certainly      possible.
	After  all
	I      do    not      even    have
	a      computer       science degree.
	Haha,  as    if       CS      could
	compete      with     modern  magic!

	For    ksort
	minimal      looping
	is     required.
	Thus   performance
	is     preserved.

	Sans   comparison
        line   sorting
        is     possible.
	Mere   array          indexing
	could  be             used    or
	set    bits           can
	be     counted.
	However,
	from   the            excessive    looping
	better performance
	does   not            result.
	But    it             is           fun.
	By     learning       from         that
	into   ksort
	linked lists
	were   introduced.

	Try    everything     imaginable
	then   combine        it
	and    a              new          method
	is     discovered.
	Simple!

	Or the C library provided qsort function can be used.
	For those who are unable to do create better.
	the C library provided qsort function exists.

	- Kyle Sallee.

	P.S.
	To exceed the mundane one method only exists.
	Do not copy!
*/

#include	<time.h>

__attribute__((unused))
__attribute__((noinline))
static	CALIGN	SORT_INDEX	*ksortm	(KSORT_DATA const * const A,
					 int const e)
{	int		h=		e/2;
	PDATA		L,R;

	L.A=
	R.A=				A;
	L.a=				0;
	L.e=
	R.a=				h;
	R.e=				e-h;

	ksortc				(&L);
	ksortc				(&R);

	if				(L.pid)
	{	waitthis		(L.pid,WEXITED);
		munmap			(L.map,PAGE*8);
	}

	if				(R.pid)
	{	waitthis		(R.pid,WEXITED);
		munmap			(R.map,PAGE*8);
	}

	return
	kmerge				(L.si,R.si);
}

__attribute__((unused))
static	CALIGN	SORT_INDEX	*ksort	(SORT_INDEX *v,int const e,uint8_t smp)
{	if		nay	(2>e)
	return			v;

	int
	klimit=			e/32;
	if			(0x1000>klimit)
	klimit=			 0x1000;

	KSORT_DATA	const	A=
	{	.data=		v,
		.limit=		klimit
	};

	if		yay	((smp!=0)&&(e>0x1000))
	return	ksortm		(&A,e);
	else
	return	ksorts		(&A,0,e);
}

/*
__attribute__((unused))
__attribute__((cold))
static		void	show_index	(uint64_t **I)
{	uint8_t	**A=	(uint8_t **)I;
	uint8_t	*s;
	while	(s=*A++)
	{	if	(s[0]!=0)
		write	(2,s,16);
		write	(2,"\n",1);
	}
}
*/

/*	Creating the   data   area
	by   loading   bytes into a 64-bit integer   and
	then writing   that         64-bit integer   into
        the  data      area   is  a hallmark.
	If   this      method is    used   elsewhere sans permission
	then copyright infringement became.
	- Kyle Sallee.
*/


static	inline	void	cram2		(SORT_INDEX **,SORT_INDEX *,uint8_t c);

__attribute__((unused))
__attribute__((noinline))
static	CALIGN	uint32_t	index_pre(VMETA			*A,
					 uint64_t		*b,
					 SORT_INDEX		*p,
					 uint8_t	const	sep)
{	SORT_INDEX * const P=
	mmap				(NULL,LINEMAX,PROT_READ|PROT_WRITE,
					 MAP_ANONYMOUS|MAP_PRIVATE,-1,0);
	SORT_INDEX *	i=		P;

	uint8_t		*a=		A->textaddr;
	size_t		T=		A->textlen;
	SORT_INDEX	*e[0x100];
	memset				(e,0,sizeof(e));
/*	memset				(e,0,0x100*sizeof(void *));	*/
	SORT_INDEX *	const	I=	i;
	uint8_t		const	*E=	a+T;

	uintptr_t		f=	0;	/* empty line count */
	register uint64_t	L;		/* generated big endian */

	again_start:
	if			nay	(a>=E)
	goto				done;

	uint8_t
	c=				*a++;

	if			nay	(c==sep)
	{	f++;
		goto			again_start;
	}

	cram2				(e,i,c);
	i->text=			b;
/*	i->origin=			a-1;	*/

	L=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len=			1;
		i++;
		*b++=			L<<0x38;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len=			2;
		i++;
		*b++=			L<<0x30;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len=			3;
		i++;
		*b++=			L<<0x28;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len=			4;
		i++;
		*b++=			L<<0x20;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len=			5;
		i++;
		*b++=			L<<0x18;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len=			6;
		i++;
		*b++=			L<<0x10;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len=			7;
		i++;
		*b++=			L<<8;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len=			8;
		i++;
		*b++=			L;
		goto			again_start;
	}

	again_long:
	i->len+=			8;
	*b++=				L;
	L=				c;

	c=				*a++;
	if			nay	(c==sep)
	{	i->len+=		1;
		i++;
		*b++=			L<<0x38;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len+=		2;
		i++;
		*b++=			L<<0x30;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len+=		3;
		i++;
		*b++=			L<<0x28;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len+=		4;
		i++;
		*b++=			L<<0x20;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len+=		5;
		i++;
		*b++=			L<<0x18;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len+=		6;
		i++;
		*b++=			L<<0x10;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len+=		7;
		i++;
		*b++=			L<<8;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len+=		8;
		i++;
		*b++=			L;
		goto			again_start;
	}

	goto				again_long;

	done:
/*	if			yay	(f>0)	*/
	{	p[0].text=		b;
		p[0].again=		f-1;
/*		p[0].origin=		A->textaddr+A->textlen-1;	*/
		p++;
		i++;
	}

	uint32_t	r=		i-I;
/*	madvise				(A->textaddr,A->textsize,MADV_DONTNEED);
*/

	uint16_t	g;
	for				(g=0;0x100>g;g++)
	for				(i=e[g];i;i=i->next)
	{	p->text=		i->text;
		p->len=			i->len;
/*		p->origin=		i->origin;	*/
		p++;
	}

	munmap				(P,LINEMAX);
	return				r;
}

static	inline	void	cram2		(SORT_INDEX **a,SORT_INDEX *b,uint8_t c)
{	b->next=			a[c];
	a[c]=				b;
}

__attribute__((unused))
__attribute__((noinline))
static	CALIGN	uint32_t	index_l	(VMETA			*A,
					 uint64_t		*b,
					 SORT_INDEX		*i,
					 uint8_t	const	sep)
{	uint8_t			*a=	A->textaddr;
	size_t			T=	A->textlen;
	SORT_INDEX *	const	I=	i;
	uint8_t		const	*E=	a+T;

	uintptr_t		f=	0;	/* empty line count */
	register uint64_t	L;		/* generated big endian */

	again_start:
	if			nay	(a>=E)
	goto				done;

	uint8_t
	c=				*a++;

	if			nay	(c==sep)
	{	f++;
		goto			again_start;
	}

	i->text=			b;
/*	i->origin=			a-1;	*/

	L=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len=			1;
		i++;
		*b++=			L<<0x38;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len=			2;
		i++;
		*b++=			L<<0x30;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len=			3;
		i++;
		*b++=			L<<0x28;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len=			4;
		i++;
		*b++=			L<<0x20;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len=			5;
		i++;
		*b++=			L<<0x18;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len=			6;
		i++;
		*b++=			L<<0x10;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len=			7;
		i++;
		*b++=			L<<8;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len=			8;
		i++;
		*b++=			L;
		goto			again_start;
	}

	again_long:
	i->len+=			8;
	*b++=				L;
	L=				c;

	c=				*a++;
	if			nay	(c==sep)
	{	i->len+=		1;
		i++;
		*b++=			L<<0x38;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len+=		2;
		i++;
		*b++=			L<<0x30;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len+=		3;
		i++;
		*b++=			L<<0x28;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len+=		4;
		i++;
		*b++=			L<<0x20;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len+=		5;
		i++;
		*b++=			L<<0x18;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len+=		6;
		i++;
		*b++=			L<<0x10;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len+=		7;
		i++;
		*b++=			L<<8;
		goto			again_start;
	}

	L<<=				8;
	L+=				c;
	c=				*a++;
	if			nay	(c==sep)
	{	i->len+=		8;
		i++;
		*b++=			L;
		goto			again_start;
	}

	goto				again_long;

	done:
/*	if			yay	(f>0)	*/
	{	i->text=		b;
		i->again=		f-1;
/*		i->origin=		A->textaddr+A->textlen-1;	*/
		i++;
	}
	uint32_t	r=		i-I;
	return				r;
}

__attribute__((always_inline))
static	inline	void	fillsep	(uint8_t *a,uint8_t b,int32_t c)
{	for			(;c>0;c-=0x10,a+=0x10)
	__builtin_memset	(a,b,0x10);
}

__attribute__((always_inline))
static	inline	void	fastcopy	(uint8_t *a,uint8_t *b,int32_t c)
{	__builtin_memcpy		(a,b,0x10);
	if				(0x10>=c)
	return;
	c-=				0x10;
	int		d=		0x10;

	for				(;c>0x40;c-=0x40,d+=0x40)
	{	__builtin_memcpy	(a+d+0x00,b+d+0x00,0x10);
		__builtin_memcpy	(a+d+0x10,b+d+0x10,0x10);
		__builtin_memcpy	(a+d+0x20,b+d+0x20,0x10);
		__builtin_memcpy	(a+d+0x30,b+d+0x30,0x10);
	}

	switch				(c)
	{	default:
		case	0x40:
		case	0x3f:
		case	0x3e:
		case	0x3d:
		case	0x3c:
		case	0x3b:
		case	0x3a:
		case	0x39:	__builtin_memcpy	(a+d,b+d,8);	d+=8;
		case	0x38:
		case	0x37:
		case	0x36:
		case	0x35:
		case	0x34:
		case	0x33:
		case	0x32:
		case	0x31:	__builtin_memcpy	(a+d,b+d,8);	d+=8;
		case	0x30:
		case	0x2f:
		case	0x2e:
		case	0x2d:
		case	0x2c:
		case	0x2b:
		case	0x2a:
		case	0x29:	__builtin_memcpy	(a+d,b+d,8);	d+=8;
		case	0x28:
		case	0x27:
		case	0x26:
		case	0x25:
		case	0x24:
		case	0x23:
		case	0x22:
		case	0x21:	__builtin_memcpy	(a+d,b+d,8);	d+=8;
		case	0x20:
		case	0x1f:
		case	0x1e:
		case	0x1d:
		case	0x1c:
		case	0x1b:
		case	0x1a:
		case	0x19:	__builtin_memcpy	(a+d,b+d,8);	d+=8;
		case	0x18:
		case	0x17:
		case	0x16:
		case	0x15:
		case	0x14:
		case	0x13:
		case	0x12:
		case	0x11:	__builtin_memcpy	(a+d,b+d,8);	d+=8;
		case	0x10:
		case	0x0f:
		case	0x0e:
		case	0x0d:
		case	0x0c:
		case	0x0b:
		case	0x0a:
		case	0x09:	__builtin_memcpy	(a+d,b+d,8);	d+=8;
		case	0x08:
		case	0x07:
		case	0x06:
		case	0x05:
		case	0x04:
		case	0x03:
		case	0x02:
		case	0x01:	__builtin_memcpy	(a+d,b+d,8);
		case	0x00:	break;
	}
}

/* I have not surmised why neworder_slow is slower.
*/

/*
__attribute__((noinline))
__attribute__((unused))
static	CALIGN	void	neworder_slow	(VMETA *A,SORT_INDEX *i,uint8_t sep)
{	uint8_t		*a;
	int32_t		b;

	for				(a=A->textaddr;i;i=i->next)
	for				(b=i->again;b>=0;b--)
	{	memcpya			(a,i->origin,i->len);
		a+=			i->len;
		*a++=			sep;
	}

	A->textlen=			a-A->textaddr;
}
*/

static	inline	void	nosweat		(uint8_t **,uint8_t,SORT_INDEX *);

__attribute__((noinline))
__attribute__((unused))
static	CALIGN	void	neworder	(VMETA *A,SORT_INDEX *i,uint8_t sep)
{	uint8_t		*a;
	register
	uint8_t		*b;
	uintptr_t	c,d;

	for				(a=A->textaddr;i;i=i->next)
	{	nosweat			(&a,sep,i);
		if		nay	(c=i->again)
		for			(d=i->len+1,b=a-d;c;c--)
		{	memcpya		(a,b,d);
			a+=		d;
		}
	}
	A->textlen=			a-A->textaddr;
}

static	inline	void	nosweat		(uint8_t **a,uint8_t sep,SORT_INDEX *I)
{	uintptr_t	X=		I->len;
	uint64_t	*b=		I->text;
	switch				(X)
	{	default:
		do
		{	**(uint64_t **)a=
			be64toh		(*b++);
			(*a)+=		8;
			X-=		8;
		}	while		(X>0x2f);


		case	0x2f:
		case	0x2e:
		case	0x2d:
		case	0x2c:
		case	0x2b:
		case	0x2a:
		case	0x29:
		case	0x28:
		**(uint64_t **)a=
		be64toh			(*b++);
		(*a)+=			8;

		case	0x27:
		case	0x26:
		case	0x25:
		case	0x24:
		case	0x23:
		case	0x22:
		case	0x21:
		case	0x20:
		**(uint64_t **)a=
		be64toh			(*b++);
		(*a)+=			8;

		case	0x1f:
		case	0x1e:
		case	0x1d:
		case	0x1c:
		case	0x1b:
		case	0x1a:
		case	0x19:
		case	0x18:
		**(uint64_t **)a=
		be64toh			(*b++);
		(*a)+=			8;
		X-=			8;

		case	0x17:
		case	0x16:
		case	0x15:
		case	0x14:
		case	0x13:
		case	0x12:
		case	0x11:
		case	0x10:
		**(uint64_t **)a=
		be64toh			(*b++);
		(*a)+=			8;

		case	0xf:
		case	0xe:
		case	0xd:
		case	0xc:
		case	0xb:
		case	0xa:
		case	9:
		case	8:
		**(uint64_t **)a=
		be64toh			(*b++);
		(*a)+=			8;

		case	7:
		case	6:
		case	5:
		case	4:
		case	3:
		case	2:
		case	1:
		case	0:
		**(uint64_t **)a=
		be64toh			(*b++);
		(*a)+=			X&7;
		**a=			sep;
		(*a)++;
	}
}

static		void	cram		(SORT_INDEX **,SORT_INDEX *);

/* presort requires revision,
   presort is not being used.
   index_pre is being used.
*/

__attribute__((unused))
static	CALIGN	void	presort		(SORT_INDEX *a,int c)
{	size_t		d=
	sizeof				(SORT_INDEX)*c;

	SORT_INDEX	*b=
	pool				(d);

	memcpy				(b,a,d);

	SORT_INDEX	*e[0x100];
	memset				(e,0,0x100*sizeof(void *));
	SORT_INDEX	*f;

	for				(f=b;c>=0x40;c-=0x40,f+=0x40)
	{	cram(e,f+0x00);	cram(e,f+0x01);	cram(e,f+0x02); cram(e,f+0x03);
		cram(e,f+0x04);	cram(e,f+0x05);	cram(e,f+0x06); cram(e,f+0x07);
		cram(e,f+0x08);	cram(e,f+0x09);	cram(e,f+0x0a); cram(e,f+0x0b);
		cram(e,f+0x0c);	cram(e,f+0x0d);	cram(e,f+0x0e); cram(e,f+0x0f);

		cram(e,f+0x10);	cram(e,f+0x11);	cram(e,f+0x12); cram(e,f+0x13);
		cram(e,f+0x14);	cram(e,f+0x15);	cram(e,f+0x16); cram(e,f+0x17);
		cram(e,f+0x18);	cram(e,f+0x19);	cram(e,f+0x1a); cram(e,f+0x1b);
		cram(e,f+0x1c);	cram(e,f+0x1d);	cram(e,f+0x1e); cram(e,f+0x1f);

		cram(e,f+0x20);	cram(e,f+0x21);	cram(e,f+0x22); cram(e,f+0x23);
		cram(e,f+0x24);	cram(e,f+0x25);	cram(e,f+0x26); cram(e,f+0x27);
		cram(e,f+0x28);	cram(e,f+0x29);	cram(e,f+0x2a); cram(e,f+0x2b);
		cram(e,f+0x2c);	cram(e,f+0x2d);	cram(e,f+0x2e); cram(e,f+0x2f);

		cram(e,f+0x30);	cram(e,f+0x31);	cram(e,f+0x32); cram(e,f+0x33);
		cram(e,f+0x34);	cram(e,f+0x35);	cram(e,f+0x36); cram(e,f+0x37);
		cram(e,f+0x38);	cram(e,f+0x39);	cram(e,f+0x3a); cram(e,f+0x3b);
		cram(e,f+0x3c);	cram(e,f+0x3d);	cram(e,f+0x3e); cram(e,f+0x3f);
	}

	if				(c>=0x20)
	{	cram(e,f+0x00);	cram(e,f+0x01);	cram(e,f+0x02); cram(e,f+0x03);
		cram(e,f+0x04);	cram(e,f+0x05);	cram(e,f+0x06); cram(e,f+0x07);
		cram(e,f+0x08);	cram(e,f+0x09);	cram(e,f+0x0a); cram(e,f+0x0b);
		cram(e,f+0x0c);	cram(e,f+0x0d);	cram(e,f+0x0e); cram(e,f+0x0f);

		cram(e,f+0x10);	cram(e,f+0x11);	cram(e,f+0x12); cram(e,f+0x13);
		cram(e,f+0x14);	cram(e,f+0x15);	cram(e,f+0x16); cram(e,f+0x17);
		cram(e,f+0x18);	cram(e,f+0x19);	cram(e,f+0x1a); cram(e,f+0x1b);
		cram(e,f+0x1c);	cram(e,f+0x1d);	cram(e,f+0x1e); cram(e,f+0x1f);
		c-=			0x20;
		f+=			0x20;
	}

	if				(c>=0x10)
	{	cram(e,f+0x00);	cram(e,f+0x01);	cram(e,f+0x02); cram(e,f+0x03);
		cram(e,f+0x04);	cram(e,f+0x05);	cram(e,f+0x06); cram(e,f+0x07);
		cram(e,f+0x08);	cram(e,f+0x09);	cram(e,f+0x0a); cram(e,f+0x0b);
		cram(e,f+0x0c);	cram(e,f+0x0d);	cram(e,f+0x0e); cram(e,f+0x0f);
		c-=			0x10;
		f+=			0x10;
	}

	for				(;c;c--,f++)
	cram				(e,f);

	uint16_t	g;
	for				(g=0;0x100>g;g++)
	for				(f=e[g];f;f=f->next)
	{	a[0].text=		f->text;
		a[0].len=		f->len;
		a++;
	}

	cede				(b,d);
}

static	inline	void	cram		(SORT_INDEX **a,SORT_INDEX *b)
{	uint8_t		c=		*(uint8_t *)	b->text;
	b->next=			a[c];
	a[c]=				b;
}
#endif
