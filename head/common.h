/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

/*	For a static declaration
	some small            functions are unworthy.
	But  duplication is too tedious.
	Thus as static inline functions here they reside.

	When included, tacit    with      ascript.h,
	the  compile   duration           will     increase.
	When static    inline   functions are  not invoked
	the  code      size               will not increase
*/

/*	By ascript.h ascript-inline.h is included.	*/

/*
typedef	uint64_t	vector8x16	__attribute__((vector_size(0x10)));
typedef	uint64_t	vector8x8	__attribute__((vector_size(8)));
typedef	uint32_t	vector4x8	__attribute__((vector_size(8)));
typedef	uint16_t	vector2x4	__attribute__((vector_size(4)));
*/

#include	"string.h"

#include	<sched.h>
#include	<sys/syscall.h>

#ifdef		PROGRAM
extern	GzT	Gz;
#else
/*
#ifdef		SANS_GOT_GZ
*/
#include	"ascript-sans-got-gz.h"
/*
#else
extern	GzT	Gz;
#endif
*/
#endif

#include	"io.h"

/*	For line     advancement
	by  inline   function invocation
	the compiler seems     more yay
	to  emit     tail      calls
	Not 100%     reliable.
*/

__attribute__((always_inline))
__attribute__((unused))
static	inline	void	argot_next	(void)
{	(*(++(Gz.at)))	();
}

__attribute__((always_inline))
__attribute__((unused))
static	inline	void	argot_skip	(void)
{	(*(Gz.at+=2))	();
}

__attribute__((always_inline))
__attribute__((unused))
static	inline	void	argot_jump	(int a)
{	(*(Gz.at+=1+a))	();
}

__attribute__((unused))
inline
SCV	private_pool_fill	(void)
{	Gz.next.pool.a=
	mmap			(NULL,
	Gz.next.pool.b=		 POOL_MAX
				,PROT_READ|PROT_WRITE
				,MAP_ANONYMOUS|MAP_PRIVATE,-1,0);
}

__attribute__((unused))
__attribute__((malloc))
__attribute__((noinline))
SCV	*private_from_mmap	(uint32_t a)
{	return	mmap		(NULL
				,a
				,PROT_READ|PROT_WRITE
				,MAP_ANONYMOUS|MAP_PRIVATE,-1,0);
}

__attribute__((unused))
__attribute__((malloc))
__attribute__((noinline))
SCV	*private_page_from_mmap	(void)
{	return	mmap		(NULL
				,PAGE
				,PROT_READ|PROT_WRITE
				,MAP_ANONYMOUS|MAP_PRIVATE,-1,0);
}

/* Function pp_fill do not invoke! */
__attribute__((unused))
__attribute__((malloc))
__attribute__((noinline))
SCV	*pp_fill		(void)
{	private_pool_fill	();

	uint8_t		*a=	Gz.next.pool.a;
	Gz.next.pool.b-=	PAGE;
	Gz.next.pool.a+=	PAGE;
	__asm__ __volatile__	("":::"memory");
	Gz.next.pool.c=		0;
	return			a;
}

__attribute__((unused))
__attribute__((malloc))
/*
__attribute__((noinline))
*/
inline
SCV	*pp_aide			(void)
{	uint8_t		c=
	__atomic_exchange_n		(&Gz.next.pool.c,1,__ATOMIC_RELAXED);
	if			nay	(c)
	return	private_page_from_mmap	();

	if			nay	(Gz.next.pool.b==0)
	return	pp_fill			();

	uint8_t		*a=		Gz.next.pool.a;
	Gz.next.pool.b-=		PAGE;
	Gz.next.pool.a+=		PAGE;
	__asm__ __volatile__		("":::"memory");
	Gz.next.pool.c=			0;
	return				a;
}

__attribute__((always_inline))
__attribute__((pure))
static	inline	uint32_t	page_round	(uint32_t a)
{	return		(a+PAGE-1)&~(PAGE-1);
}

/* Function pps_fill do not invoke! */
__attribute__((unused))
__attribute__((malloc))
__attribute__((noinline))
SCV	*pps_fill			(uint32_t a)
{	if			yay	(Gz.next.pool.b!=0)
	munmap				(Gz.next.pool.a
					,Gz.next.pool.b);

	private_pool_fill		();

	uint32_t		b=
	page_round			(a);
	uint8_t		*A=		Gz.next.pool.a;
	Gz.next.pool.b-=		b;
	Gz.next.pool.a+=		b*PAGE;
	__asm__ __volatile__		("":::"memory");
	Gz.next.pool.c=			0;
	return				A;
}

__attribute__((unused))
__attribute__((malloc))
__attribute__((noinline))
SCV	*pps_aide			(uint32_t a)
{	uint8_t		c=
	__atomic_exchange_n		(&Gz.next.pool.c,1,__ATOMIC_RELAXED);
	if			nay	(c)
	mapit:
	return	private_from_mmap	(a);

	uint32_t	b;
	uint8_t		*A;
	b=
	page_round			(a);
	if			yay	(Gz.next.pool.b>=b)
	{	A=			 Gz.next.pool.a;
		Gz.next.pool.b-=	b;
		Gz.next.pool.a+=	b;
		__asm__ __volatile__	("":::"memory");
		Gz.next.pool.c=		0;
		return			A;
	}

	if			nay	(a>POOL_MAX)
	{	Gz.next.pool.c=		0;
		goto			mapit;
	}

	return	pps_fill		(a);
}

__attribute__((unused))
__attribute__((malloc))
__attribute__((always_inline))
static	inline	void	*pool	(uint32_t a)
{	return	mmap	(NULL,a,PROT_READ|PROT_WRITE,
			 MAP_ANONYMOUS|MAP_PRIVATE,-1,0);
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	int	cede	(void *a,uint32_t b)
{	return		munmap	(a,b);
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	map_add			(VMETA *A
						,uint32_t const a
						,uint32_t const b)
{	if					(a)
	{	A->io.flag|=			textmapunmap;
		if				(PAGE>=a)
		{	A->textsize=		PAGE;
			A->textaddr=	pp	();
		}
		else
		{	A->textsize=		a;
			A->textaddr=	pps	(a);
		}
	}

	if					(b)
	{	A->io.flag|=			datamapunmap;
		if				(PAGE>=b)
		{	A->datasize=		PAGE;
			A->dataaddr=	pp	();
		}
		else
		{	A->datasize=		b;
			A->dataaddr=	pps	(b);
		}
	}
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	pid_t	gettid_		(void)
{	return	syscall	(SYS_gettid);
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	int	closemust	(int const a)
{	int		c=
	close		(a);
	if	yay	(c==0)
	return		c;
	else
	closeretry	(a);
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	pipemust	(int * const a)
{	int		b=
	pipe			(a);
	if		yay	(b==0)
	return;
	else
	err			(errna,"%-60s","pipe");
}

#ifdef		__linux__
#include	<linux/memfd.h>
__attribute__((unused))
__attribute__((always_inline))
static	inline	int	mfdmust	(void)
{	return
	syscall			(SYS_memfd_create,"",0);
}
#endif

__attribute__((unused))
__attribute__((always_inline))
static	inline	int	shmmust	(void)
{	int		a=
	shm_open		("...",O_RDWR|O_CREAT|O_EXCL,0600);
	shm_unlink		("...");
	return			a;
}

/* byte join.c memmust is invoked */
/*
__attribute__((unused))
static		int	memmust	(void)
{
#ifdef		__linux__
return		mfdmust		();
#else
return		shmmust		();
#endif
}
*/

__attribute__((unused))
__attribute__((always_inline))
static	inline	int	dupmust	(int const a)
{	int	c=
	dup			(a);
	if		yay	(c>=0)
	return			c;
	else
	dupretry		(a);
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	int	dup2must(int const a,int const b)
{	int	c=
	dup2			(a,b);
	if		yay	(c>=0)
	return			c;
	else
	dup2retry		(a,b);
}

#ifndef		__linux__
__attribute__((unused))
__attribute__((always_inline))
static	inline	int	dup3	(int const a,int const b,int const c)
{	int		d=
	dup2must		(a,b);
	if		yay	(c)
	fcntl			(d,F_SETFD,c);
	return			d;
}
#endif


/*	By optional/pts/argot/pts.c dup3must is invoked.
	I might want to reconsider.
*/

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	dup3must	(int const a,int const b,int const c)
{	int		d=
	dup3			(a,b,c);
	if		yay	(d>=0)
	return;
	else
	err			(errna,"%s %i %i %i","dup3",a,b,c);
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	int	highwant	(int const o)
{	return
	fcntl                   (o,F_DUPFD_CLOEXEC,FDHIGH);

	int		n=
	fcntl			(o,F_DUPFD_CLOEXEC,FDHIGH);
	if		yay	(n>=0)
	return			n;
	else
	{	errna=		0;
		return
		fcntl		(o,F_DUPFD_CLOEXEC,3);
	}
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	int	highmake	(int const d)
{	int		n=
	highwant	(d);
	closemust	(d);
	return		n;
}

__attribute__((unused))
__attribute__((noinline))
SCV	text_write 		(VMETA *A)
{	writeall		(A->io.log,A->textaddr,A->textlen);
	A->textlen=		0;
/* In page amounts write is not faster */
}

__attribute__((unused))
__attribute__((malloc))
__attribute__((always_inline))
static	inline	void	*mmapmust	(uint32_t const s
					,uint32_t const p
					,int const f
					,int const d)
{	return
	mmap		(NULL,s,p,f,d,0);
}

__attribute__((unused))
__attribute__((malloc))
__attribute__((always_inline))
static	inline	void	*mmapanon	(uint32_t const s,int f)
{	return	mmapmust	(s,PROT_READ|PROT_WRITE,MAP_ANONYMOUS|f,-1);
}

__attribute__((unused))
__attribute__((malloc))
__attribute__((always_inline))
static	inline	void	*mmaphuge	(uint32_t const A,int const B)
{	uintptr_t	s=		A+HUGE*2;
	void		*a=	mmapanon(s,B);
	uintptr_t	b=		(uintptr_t)	a;
	b+=				  HUGE;
	b&=				~(HUGE-1);
	void		*c=		(void *)	b;
	void		*d=		a+s;
	void		*e=		c+A;
	uintptr_t	f=		c-a;
	uintptr_t	g=		d-e;
	munmap				(a,f);
	munmap				(e,g);
	return				c;
}

__attribute__((unused))
__attribute__((malloc))
__attribute__((always_inline))
static	inline	void	*mmaphuge_old	(uint32_t const a,int const b)
{	size_t		c=	(a+PAGE-1)&~(PAGE-1);
	size_t		d=	c+HUGE-PAGE;
	void		*e=
	mmapanon		(d,b);

	void		*f=	(void *)(((uintptr_t)e+HUGE-1)&~(HUGE-1));
	size_t		g=	f-e;
	size_t		h=	d-g-c;

	if		yay	(g!=0)	munmap	(e,g);
	if		yay	(h!=0)	munmap	(f+c,h);
	return			f;
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	*remust	(void *oa,uint32_t os,uint32_t ns,int f)
{	return
	mremap		(oa,os,ns,f);
}

/*	With a 2 megabyte stack variable
	function bufcopy is seldom inlined
	A better place for the data would be nice,
	especially if within a signal bufcopy is invoked.
	But function mmap and munmap per invocation also is expensive.
*/

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	dupclose	(int const a,int const b)
{	dup3must	(a,b,O_CLOEXEC);
	closemust	(a);
}

/*
as compared with function fstat
if not twice invoked
the function lseek
could be faster
*/
__attribute__((unused))
__attribute__((noinline))
static	CALIGN	off_t	dsize	(int const d)
{	struct stat	b;
	b.st_size=	-1;
	fstat		(d,&b);
	return		b.st_size;
}

__attribute__((unused))
__attribute__((noinline))
static	CALIGN	off_t	nsize	(uint8_t * const n)
{	struct	stat	b;
	b.st_size=	-1;
	stat		(n,&b);
	return		b.st_size;
}

static	inline	uint32_t	rolx20x1	(uint32_t a)
{	return					(a<<1)+(a>>0x1f);
}

static	inline	uint16_t	rolx10x1	(uint16_t a)
{	return					(a<<1)+(a>>0x0f);
}

/*	Function bit128_to_bit24
	function bit128_to_bit16
	function bit128_to_bit16_slow
	by Kyle Sallee
	were originally created.
	Do not copy!
	For the argot name plethora only
	these functions suffice.
	No other corpus was tested.
*/

/* 10 opcodes */
__attribute__((unused))
__attribute__((const))
__attribute__((always_inline))
static	inline	uint16_t	bit128_to_bit16_slow	(uint8_t const *a)
{	uint64_t	b=	*(uint64_t *)	(a+8)-
				*(uint64_t *)	a;
	uint32_t	c=	b-rolx20x1(b>>0x20);
	uint16_t	d=	c-rolx10x1(c>>0x10);
	return			d;
}

/* bit128_to_bit16 is 2 opcodes faster, 20% faster, but
   for names with symmetry the same return value becomes.

 abcdefghabcdefgh smack
   abcdabcd smack
   abab smack
*/


/*
#define			bit128_to_bit16_macro_b(a)			\
			*(int64_t *)			((a)+8)-	\
			*(int64_t *)			(a)

#define			 bit128_to_bit16_macro_c(a)			\
	(uint32_t)	(bit128_to_bit16_macro_b	((a))-		\
			(bit128_to_bit16_macro_b	((a))>>0x20)	)

#define			bit128_to_bit16_macro(a)			\
	(uint16_t)	(bit128_to_bit16_macro_c	((a))-		\
			(bit128_to_bit16_macro_c	((a))>>0x10)	)
*/

/* 8 opcodes */
__attribute__((unused))
__attribute__((const))
__attribute__((always_inline))
static	inline	uint16_t	bit128_to_bit16	(uint8_t const *a)
{	uint64_t	b=	*(uint64_t *)	(a+8)-
				*(uint64_t *)	a;
	uint32_t	c=	b-(b>>0x20);
	uint16_t	d=	c-(c>>0x10);
	return			d;
}

/* For vector use bit128_to_bit24 is not suited */
/* 16-bit indexing is often more than sufficient
   bit128_to_bit16 should instead be invoked.
*/

__attribute__((unused))
__attribute__((const))
__attribute__((always_inline))
static	inline	uint32_t	bit128_to_bit24	(uint8_t const *a)
{	uint64_t
	b=			*(uint64_t *)	(a+8)-
				*(uint64_t *)	a;

	uint32_t
	c=			b-(b>>0x20);
	c=			c-(c>>0x18);
	return			c&0xffffff;
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	vattach	(VMETA * const A)
{	VMETA		**M=
	A->vam=			&Gz.hash.var[bit128_to_bit16(A->name)];
	A->fore=		*M;
	*M=			A;
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	vattach_fast	(VMETA * const A)
{	VMETA
	**M=		A->vam;
	A->fore=	*M;
	*M=		A;
}

/*
For vattach_faster
for vam_fast
at compile time NAME content must be known.
*/

#define	vam_fast(VMA,NAME)					\
	(VMA)->vam=	&Gz.hash.var[bit128_to_bit16(		\
			(VAMFIT const){.name=NAME}.name)]

#define	vattach_faster(VMA,NAME)	\
	vam_fast      (VMA,NAME);	\
	vattach_fast  (VMA)

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	vdetach	(VMETA * const A)
{	VMETA		*C,*B;
/*	if			nay	(A->vam==NULL)
	return;
*/

	B=			*A->vam;
	if		yay	(A==B)
	{	*A->vam=	A->fore;
		return;
	}

	while			(1)
	if		yay	(A==(C=B->fore))
	{	B->fore=	A->fore;
		return;
	}
	else
	B=			C;
}

__attribute__((unused))
__attribute__((unused))
__attribute__((always_inline))
static	inline	uint8_t	unused_fd	(int const d)
{	int		i,r=
	fcntl			(d,F_GETFL,&i);
	if		yay	(0>r)
	return			1;
	else
	return			0;
}

__attribute__((unused))
__attribute__((noinline))
static	CALIGN	uint8_t	fifosock	(int const d)
{	if		nay	(unused_fd(d))
	return			0;
	struct	stat	b;
	fstat			(d,&b);
	switch			(b.st_mode&S_IFMT)
	{	case	S_IFIFO:
		case	S_IFSOCK:	return	1;
		default:		return	0;
	}
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	reval	(VMETA * const A)
{	if	nay (A->    reval!=NULL) A->    reval	(A);
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	revise	(VMETA * const A)
{	if	nay (A->    revise!=NULL) A->    revise	(A);
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	show	(VMETA * const A)
{	if		(A->reval!=NULL)
	A->reval	(A);
	if		(A->show !=NULL)
	A->show		(A);
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	show_origin	(void)
{	if				(Gz.to[1]->reval!=NULL)
	Gz.to[1]->reval			(Gz.to[1]);
	if				(Gz.to[1]->show !=NULL)
	Gz.to[1]->show			(Gz.to[1]);
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	show_target	(void)
{	if				(Gz.to[0]->reval!=NULL)
	Gz.to[0]->reval			(Gz.to[0]);
	if				(Gz.to[0]->show !=NULL)
	Gz.to[0]->show			(Gz.to[0]);
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	data	(VMETA * const A)
{	if	nay	(A->op->data!=NULL)
			 A->op->data		(A);
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	uint32_t	int4want	(VMETA * const A)
{	if	nay	(A->reval!=NULL)
	A->reval	(A);
	return		A->value.i4.l;
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	uint64_t	int8want	(VMETA * const A)
{	if	nay	(A->reval!=NULL)
	A->reval	(A);
	return		A->value.i;
}

/*
Function map_check
afore invocation
the map length
must not be increased.
From mmap
a map
if acquired
into the acquired map
the prior content
up to length
is copied.
*/

__attribute__((unused))
__attribute__((noinline))
SCV	text_resize		(VMETA *A,uint32_t o,uint32_t n)
{	A->textaddr=
	mremap			(A->textaddr,o,n,MREMAP_MAYMOVE);
	if		nay	(A->io.map)
	ftruncate		(A->io.map,n);
}

__attribute__((unused))
__attribute__((noinline))
SCV	text_acquire		(VMETA *A,uint32_t n)
{	A->io.flag|=		textmapunmap;
	void		*v=
	pps			(n);
	int		a;
	for			(a=0;sizeof(A->text)>a;a+=0x10)
	__builtin_memcpy	(v+a,A->textaddr+a,0x10);
	A->textaddr=		v;
}
/*
The xmm opcodes
to select
with __builtin_memcpy
the 0x10 size
is required.
*/

__attribute__((unused))
__attribute__((noinline))
SCV	text_expand		(VMETA *A,uint32_t s)
{	uint32_t	o=	A->textsize;
	uint32_t	n=	(o+s+0x200000)&(~0x1fffff);
	A->textsize=		n;

	if			(A->io.flag&textmapunmap)
	text_resize		(A,o,n);
	else
	text_acquire		(A,n);
}

__attribute__((unused))
__attribute__((noinline))
SCV	text_flush_expand	(VMETA *A,uint32_t s)
{	text_write		(A);
	text_expand		(A,s);
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	text_flush_just	(VMETA *A)
{	text_write			(A);
}

__attribute__((unused))
__attribute__((noinline))
SCV	text_flush			(VMETA *A,uint32_t s)
{	int			a=	errna;
	errna=				0;

	if			yay	(A->textsize>=s)
	text_flush_just			(A);
	else
	text_flush_expand		(A,s);

	int			b=	errna;
	if			nay	(b!=0)
	A->io.success=			b;
	errna=				a;
}

/* For text_adjust_aide a macroname called text_adjust is provided */

__attribute__((unused))
__attribute__((noinline))
SCV	text_adjust_aide	(VMETA *A,uint32_t s)
{	if		yay	(A->io.log)
	text_flush		(A,s);
	else
	text_expand		(A,s);
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	text_check	(VMETA *A,uint32_t s)
{	if			yay	(A->textsize>=(A->textlen+s+8))
	return;
	else
	text_adjust			(A,s);
}

/*
In  file self.c
by  function equal_root
by  function equal_dir
the function pathname_concatenate
is  invoked.
*/

__attribute__((unused))
__attribute__((always_inline))
static	inline	uint32_t	pathname_concatenate	(uint8_t *a,VMETA **V)
{	VMETA		*A;
	uint8_t		*b;
	for		(b=a;A=*V++;a+=     A->textlen)
	memcpya		(  a,A->textaddr,A->textlen);
	*a=		0;
	return		b-a;
}

__attribute__((always_inline))
__attribute__((unused))
static	inline	void	*scratch_do	(uint16_t a)
{	return
	__atomic_fetch_add	(&Gz.next.scratch,a,__ATOMIC_RELAXED);
}

__attribute__((always_inline))
__attribute__((unused))
static	inline	void	scratch_done	(uint16_t a)
{	__atomic_sub_fetch	(&Gz.next.scratch,a,__ATOMIC_RELAXED);
}

__attribute__((always_inline))
__attribute__((unused))
static	inline	uint32_t	atindex	(void (**A)(void))
{	if			(A==NULL)
	A=			Gz.at;
	return			A-Gz.heap.func;
}

/*
At runtime
the Gz.heap.func and Gz.at
are not subtracted.
Rather the difference
between Gz.heap.whatever and Gz.heap.func
is added.
How?
By the compiler
at compile time
even for argot
the Gz address
is known.
Thus sans indexing the desired address is typically calculated.
The pointer value when the same
this trick works.
Proper indexing
if used
by the compiler
many more opcodes
would be emitted.
By asm hackers
the indexing method
would not be used.
Rather the address difference
would be added.
Ambiguity,
such as
at copile time
the Gz's address
if not known
many more opcodes
must execute.
*/

__attribute__((always_inline))
__attribute__((unused))
static	inline	VALUE	*partsave	(void (**A)(void))
{	if		(A==NULL)
	A=		Gz.at;

	if		(sizeof(VALUE)==sizeof(void *))
	return		(void *)A-
			(void *)Gz.heap.func+
			(void *)Gz.heap.save;
	else
	return		Gz.heap.save+
	atindex		(A);
}

__attribute__((always_inline))
__attribute__((unused))
static	inline	VLESS	*arga_proper_slow	(void (**A)(void))
{	return		Gz.heap.arga[atindex(A)];
}

__attribute__((always_inline))
__attribute__((unused))
static	inline	VLESS	*arga		(void (**A)(void))
{	if		(A==NULL)
	A=		Gz.at;
	return		*(VLESS **)(
			(void *)A-
			(void *)Gz.heap.func+
			(void *)Gz.heap.arga);
}

__attribute__((always_inline))
__attribute__((unused))
static	inline	VLESS	**aarga		(void (**A)(void))
{	if		(A==NULL)
	A=		Gz.at;
	return		(void *)A-
			(void *)Gz.heap.func+
			(void *)Gz.heap.arga;
}

__attribute__((always_inline))
__attribute__((unused))
static	inline	farint	partfar	(void (**A)(void))
{	if		(A==NULL)
	A=		Gz.at;
	return		*(farint *)(
			(void *)A-
			(void *)Gz.heap.func+
			(void *)Gz.heap.far);
}

__attribute__((always_inline))
__attribute__((unused))
static	inline	uint32_t partfar_proper_slow	(void (**A)(void))
{	return	Gz.heap.far[atindex(A)];
}

__attribute__((always_inline))
__attribute__((unused))
static	inline	uint8_t	*partfrom_proper_slow	(void (**A)(void))
{	return	Gz.heap.from[atindex(A)];
}

__attribute__((always_inline))
__attribute__((unused))
static	inline	uint8_t	*partfrom		(void (**A)(void))
{	if		(A==NULL)
	A=		Gz.at;
	return		*(uint8_t **)(
			(void *)A-
			(void *)Gz.heap.func+
			(void *)Gz.heap.from);
}

__attribute__((unused))
static	CALIGN	ZYGOTE		*script_zygote	(void)
{	ZYGOTE		*z;
	for			(z=Gz.heap.zygote;Gz.at>z->head;z++);
	return			z-1;
}

__attribute__((unused))
static	CALIGN	uint8_t	*script_name	(void)
{	return	script_zygote	()->file_name;
}

__attribute__((unused))
static	CALIGN	uint8_t	*script_argot	(void)
{	return		Gz.heap.name[Gz.at-Gz.heap.func];
}

__attribute__((unused))
static	CALIGN	uint32_t	script_line_number	(void)
{	ZYGOTE		*z=
	script_zygote		();

	uint32_t	a[0x100];
	a['\n']=		1;
	uint8_t		*b,*c=
	partfrom		(NULL);
	for			(b=z->file_head;c>b;a[*b++]++);
	return			a['\n'];
}

__attribute__((unused))
static	CALIGN	uint32_t	partlen	(void)
{	uint8_t			*a,*b;
	a=
	b=
	partfrom		(NULL);
	for			(;(*a!='\n')&&(*a!=',');a++);
	return			a-b;
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	uint32_t	argarange	(void (**A)(void)
						,VLESS **c
						,VLESS **d)
{	VLESS		**a=	aarga		(A);
	*c=			a[0];
	*d=			a[1];
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	uint32_t	argaamount	(void (**A)(void))
{	VLESS		*a,*b;
	argarange		(A,&a,&b);
	return			b-a;
}

#include	"var.h"
#include	"aaa.h"
