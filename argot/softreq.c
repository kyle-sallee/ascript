/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"futex.h"
#include	"sire.h"
#include	"softreq.h"
#include	<dirent.h>

OPERATOR	opsoftreq[8];

static		SOFT	*soft_find		(RMETA *,uint8_t *,uint8_t);
static		SOFT	*soft_find_make		(RMETA *,uint8_t *,uint8_t);
static		SOFT	*soft_make		(RMETA *,uint8_t *,uint8_t);

static		void	pathname_acquire	(RMETA *,uint8_t *,uint32_t);
static		void	required_content	(RMETA *);
static		void	optional_content	(RMETA *);
static		void	selected_content	(RMETA *);
static		void	lite_content		(RMETA *);

static		void	required_index		(RMETA *);
static		void	optional_index		(RMETA *);
static		void	selected_index		(RMETA *);
static		void	topic_index		(RMETA *);

static		void	must_optional_index	(RMETA *);
static		void	must_selected_index	(RMETA *);
static		void	want_optional_index	(RMETA *);
static		void	want_selected_index	(RMETA *);

static		int	equal0_			(void *);

typedef	struct
{	FUTEX		f;
	RMETA		*R;
}	FR;

static	void	equal0_delegate		(void);
static	void	equal0_wait		(void);
__attribute__((unused))
SCV		equal0			(void)
{	*Gz.at=		equal0;
	RMETA		*R=
	rmeta					(Gz.to[0]);
	switch					(R->wait)
	{	case	0:	equal0_delegate	();	break;
		case	1:	equal0_wait	();	break;
		default:	argot_next	();
	}
}

static		int	equal0_late		(void *);

__attribute__((noinline))
SCV	equal0_delegate				(void)
{	RMETA		*R=
	rmeta					(Gz.to[0]);
	R->A=					Gz.to[0];
	R->wait=				1;
	pathname_acquire			(R,
						 Gz.to[1]->textaddr,
						 Gz.to[1]->textlen);

	R->stack[0]=
	pool					(0x800000);

	pids.last=
	R->pid[0]=
	clone					(equal0_late,
						 R->stack[0]+0x800000,
						 CLONE_VM|SIGCHLD,R);
	argot_next				();
}

__attribute__((noinline))
SCV	equal0_wait				(void)
{	RMETA		*R=
	rmeta					(Gz.to[0]);
	waitthis				(R->pid[0],WEXITED);
	argot_next				();
}

static	CALIGN	int	equal0_late		(void *r)
{	RMETA		*R=			r;
	R->stack[1]=
	pool					(0x800000);

	FR		c;

	futex_inc				(&c.f);
	c.R=
	rmeta					(Gz.to[0]);

	pids.last=
	R->pid[1]=
	clone					(equal0_,
						 R->stack[1]+0x800000,
						 CLONE_VM|SIGCHLD,&c);

	required_content			(R);
	optional_content			(R);
	selected_content			(R);
	lite_content				(R);

	required_index				(R);
	optional_index				(R);
	selected_index				(R);
	topic_index				(R);

	must_optional_index			(R);
	want_optional_index			(R);

/*	selected index generation is delgated */
/*	must_selected_index			(R);
	want_selected_index			(R);
*/
	futex_release				(&c.f);
	waitthis				(R->pid[1],WEXITED);

	cede					(R->ref[0].at,R->ref[0].size);
	cede					(R->ref[1].at,R->ref[1].size);
	cede					(R->ref[2].at,R->ref[2].size);

	R->ref[0].at=
	R->ref[1].at=
	R->ref[2].at=				NULL;

	R->ref[0].size=
	R->ref[1].size=
	R->ref[2].size=				0;

	size_t		s;

/*	Those maps if shaved a segfault is solicted
	Perhaps elsewhere a bug exists?
*/

/*
	s=					(void *)	R->ref[3].next-
						(void *)	R->ref[3].at;
	mremap					(R->ref[3].at,
						 R->ref[3].size,s,0);

	s=					(void *)	R->ref[4].next-
						(void *)	R->ref[4].at;
	mremap					(R->ref[4].at,
						 R->ref[4].size,s,0);
*/


	s=					(void *)	R->smap.next-
						(void *)	R->smap.at;
	mremap					(R->smap.at,
						 R->smap.size,s,0);
	R->smap.size=				s;
	R->wait=				2;
	return					0;
}

static	CALIGN	int	equal0_			(void *v)
{	FR		*c=			v;
	futex_acquire				(&c->f,1);
	must_selected_index			(c->R);
	want_selected_index			(c->R);
	return					0;
}

static	inline	void	equalx			(void (*)(void),uint8_t);
SCV	equal1	(void)		{equalx(equal1,3);}
SCV	equal2	(void)		{equalx(equal2,4);}
SCV	equal6	(void)		{equalx(equal6,6);}
SCV	equal7	(void)		{equalx(equal7,7);}

static		size_t	soft_list_name_copy	(uint8_t *,SOFT *,uint8_t);
static	inline	void	equalx			(void (*F)(void),uint8_t a)
{	VMETA		*B=			Gz.to[0];
	VMETA		*A=			B->host;
	RMETA		*R=
	rmeta					(A);
	SOFT		*S=
	soft_find				(R,
						 Gz.to[1]->textaddr,
						 Gz.to[1]->textlen);
	B->textlen=
	soft_list_name_copy			(B->textaddr,S,a);
	*Gz.at=				F;
	argot_next				();
}

static	CALIGN	size_t	soft_list_name_copy	(uint8_t *a,SOFT *b,uint8_t c)
{	if				(b==NULL)
	return				0;

	uint8_t		*d=		a;
	SOFT		**e=		b->rmap[c].at;
	if				(  e!=NULL)
	for				(;*e!=NULL;e++)
	{	memcpya			(a,
					 e[0]->name,
					 e[0]->len);
		a+=			 e[0]->len;
		*a++=			'\n';
	}
	return				a-d;
}

SCV	pathname_acquire		(RMETA *R,uint8_t *a,uint32_t b)
{	uint8_t		*c=		a+b;
	int		d;
	size_t		e;
	for				(d=0;0x20>d;d++)
	{	e=
		strlenb			(a)+1;
		memcpya			(R->pn[d],a,e);
		a+=			e;
		if		nay	(a>=c)
		return;
	}
}

static		void	blocker_set		(RMETA *,uint8_t *);
static		SOFT	*unblocked		(RMETA *,uint8_t *,uint32_t,
						 uint8_t);

static		void	plan_moil_blocker_load	(RMETA *);
static		SOFT	*plan_moil_load		(RMETA *);

static		void	plan_load_blocker_load	(RMETA *);
static		SOFT	*plan_load_load		(RMETA *);

SCV	show_load			(VMETA *D)
{	VMETA		*A=		D->host;
	RMETA		*R=
	rmeta				(A);

	plan_load_blocker_load		(R);
	SOFT		*S=
	plan_load_load			(R);

	if				(S!=NULL)
	{	memcpya			(D->textaddr,S->name,
					 D->textlen= S->len);
	}
	else
	D->textlen=			0;
}

SCV	plan_load_blocker_load		(RMETA *R)
{	R->unique++;
	struct dirent	*e;
	DIR		*d=
	opendir				(R->pn[4]);

	while				(  e=readdir(d))
	if				(  e->d_name[0]!='.')
	blocker_set			(R,e->d_name);
	closedir			(d);
}

static	CALIGN	SOFT	*plan_load_load		(RMETA *R)
{	DIR		*d=
	opendir					(R->pn[4]);

	uint32_t	u=			R->unique;
	SOFT		*S;
	struct dirent	*e;
	while					(e=readdir(d))
	if			yay		(e->d_name[0]!='.')
	{	S=
		unblocked			(R,e->d_name,u,1);
		if		nay		(S!=NULL)
		{	closedir		(d);
			return			S;
		}
	}

	rewinddir				(d);
	while					(e=readdir(d))
	if			yay		(e->d_name[0]!='.')
	{	S=
		unblocked			(R,e->d_name,u,0);
		if		nay		(S!=NULL)
		{	closedir		(d);
			return			S;
		}
	}

	closedir				(d);
	return					NULL;
}

SCV	show_moil			(VMETA *E)
{	VMETA		*A=		E->host;
	RMETA		*R=
	rmeta				(A);

	plan_moil_blocker_load		(R);
	SOFT		*S=
	plan_moil_load			(R);

	if				(S!=NULL)
	{	memcpya			(E->textaddr,S->name,
					 E->textlen= S->len);
	}
	else
	E->textlen=			0;
}

SCV	plan_moil_blocker_load		(RMETA *R)
{	R->unique++;
	struct dirent		*e;
	uint8_t			a;
	for				(a=4;0x20>a;a++)
	if				(R->pn[a][0]!=0)
	{	DIR		*d=
		opendir			(R->pn[a]);

		while			(  e=readdir(d))
		if			(  e->d_name[0]!='.')
		blocker_set		(R,e->d_name);
		closedir		(d);
	}
}

static	CALIGN	SOFT	*plan_moil_load		(RMETA *R)
{	DIR		*d=
	opendir					(R->pn[5]);

	uint32_t	u=			R->unique;
	SOFT		*S;
	struct dirent	*e;
	while					(e=readdir(d))
	if			yay		(e->d_name[0]!='.')
	{	S=
		unblocked			(R,e->d_name,u,1);
		if		nay		(S!=NULL)
		{	closedir		(d);
			return			S;
		}
	}

	rewinddir				(d);
	while					(e=readdir(d))
	if			yay		(e->d_name[0]!='.')
	{	S=
		unblocked			(R,e->d_name,u,0);
		if		nay		(S!=NULL)
		{	closedir		(d);
			return			S;
		}
	}

	closedir				(d);
	return					NULL;
}

SCV	blocker_set			(RMETA *R,uint8_t *a)
{	SOFT		*S=
	soft_find			(R,a,strlenb(a));
	if			yay	(S!=NULL)
	S->unique=			R->unique;
}

static	CALIGN	SOFT	*unblocked		(RMETA *R,uint8_t *a,
						 uint32_t u,uint8_t b)
{	static	CALIGN	SOFT	t;
	size_t			c;

	SOFT			*S=
	soft_find				(R,a,c=strlenb(a));
	if			nay		(S==NULL)
	{	t.len=				c;
		memcpya				(t.name,a,c+1);
		return				&t;
	}

	if			nay		(S->lite!=b)
	return					NULL;

	SOFT			**s=		S->rmap[3].at;
	if			nay		(s==NULL)
	return					S;

	for					(;*s;s++)
	if					(s[0]->unique==u)
	return					NULL;
	return					S;
}

static	inline	void	required_content_	(RMETA *,uint8_t *,int);

__attribute__((noinline))
SCV	required_content		(RMETA *R)
{	int		D=
	open				(R->pn[0],O_RDONLY);
	DIR		*d=
	fdopendir			(D);

	int		c=		0;
	struct dirent	*e;
	while				(e=readdir(d))
	if				(e->d_name[0]!='.')	c++;

	SMAP		*S=		&R->smap;

	S->size=
	sizeof				(SOFT)*2*c;
	S->at=
	S->next=
	pool				(S->size);

	rewinddir			(d);
	while				(  e=readdir(d))
	if				(  e->d_name[0]!='.')
	required_content_		(R,e->d_name,D);
	closedir			(d);
}

static	inline	void	required_content_	(RMETA *R,uint8_t *a,int b)
{	SOFT		*S=
	soft_make		(R,a,strlenb(a));

	struct	stat	s;
	int		d;

	if		nay		(0>(d=openat(b,a,O_RDONLY)))	return;
	if		nay		(0>fstat(d,&s))			return;

	uint32_t	e=		s.st_size+1;
	S->size[0]=			e;
	uint8_t		*f=
	S->raw[0]=
	pool				(e);
	read				(d,f,e-1);
	close				(d);
}

static	inline	void	optional_content_	(RMETA *,uint8_t *,int);

__attribute__((noinline))
SCV	optional_content		(RMETA *R)
{	int		D=
	open				(R->pn[1],O_RDONLY);
	DIR		*d=
	fdopendir			(D);

	struct dirent	*e;
	while				(  e=readdir(d))
	if				(  e->d_name[0]!='.')
	optional_content_		(R,e->d_name,D);
	closedir			(d);
}

static	inline	void	optional_content_	(RMETA *R,uint8_t *a,int b)
{	SOFT		*S=
	soft_find_make			(R,a,strlenb(a));

	struct	stat	s;
	int		d;

	if		nay		(0>(d=openat(b,a,O_RDONLY)))	return;
	if		nay		(0>fstat(d,&s))			return;

	uint32_t	e=		s.st_size+1;
	S->size[1]=			e;
	uint8_t		*f=
	S->raw[1]=
	pool				(e);
	read				(d,f,e-1);
	close				(d);
}

static	inline	void	selected_content_	(RMETA *,uint8_t *,int);

__attribute__((noinline))
SCV	selected_content		(RMETA *R)
{	int		D=
	open				(R->pn[3],O_RDONLY);
	DIR		*d=
	fdopendir			(D);

	struct dirent	*e;
	while				(  e=readdir(d))
	if				(  e->d_name[0]!='.')
	selected_content_		(R,e->d_name,D);
	closedir			(d);
}

static	inline	void	selected_content_	(RMETA *R,uint8_t *a,int b)
{	SOFT		*S=
	soft_find_make			(R,a,strlenb(a));

	struct	stat	s;
	int		d;

	if		nay		(0>(d=openat(b,a,O_RDONLY)))	return;
	if		nay		(0>fstat(d,&s))			return;

	uint32_t	e=		s.st_size+1;
	S->size[2]=			e;
	uint8_t		*f=
	S->raw[2]=
	pool				(e);
	read				(d,f,e-1);
	close				(d);
}

static	inline	void	lite_content_	(RMETA *,uint8_t *);

__attribute__((noinline))
SCV	lite_content			(RMETA *R)
{	int		D=
	open				(R->pn[3],O_RDONLY);
	DIR		*d=
	fdopendir			(D);

	struct dirent	*e;
	while				(  e=readdir(d))
	if				(  e->d_name[0]!='.')
	lite_content_			(R,e->d_name);
	closedir			(d);
}

static	inline	void	lite_content_	(RMETA *R,uint8_t *a)
{	SOFT		*S=
	soft_find_make			(R,a,strlenb(a));
	S->lite=			1;
}

static	inline	uint32_t	line_count	(uint8_t *);


static	inline	void	required_index_	(RMETA *,SOFT *,SOFT ***);

__attribute__((noinline))
SCV	required_index			(RMETA *R)
{	uint32_t	c;
	SOFT		*S=		R->smap.at;
	SOFT		*T=		R->smap.next;
	for				(c=T-S;T>S;S++)
	if		yay		(S->raw[0]!=NULL)
	c+=		line_count	(S->raw[0]);

	REF		*r=		R->ref;

	r->size=
	sizeof				(SOFT *)*c;
	r->at=
	r->next=
	pool				(r->size);

	SOFT		**t=		r->at;
	S=				R->smap.at;
	for				(;T>S;S++)
	required_index_			(R,S,&t);
}

inline
SCV	required_index_			(RMETA *R, SOFT *S, SOFT ***T)
{	if		nay		(S->raw[0]==NULL)
	return;

	RMAP		*r=		&S->rmap[0];
	r->next=
	r->at=				*T;

	SOFT		**t=		*T;
	uint8_t		*a,*b;
	for				(a=S->raw[0];*a!=0;a++)
	{	for			(   ;*a=='\n';a++);
		for			(b=a;*a!='\n';a++);
		*t++=
		soft_find_make		(R,b,a-b);
	}

	r->amount=			t-*T;
	*T=				t+1;

/*	r->size=			r->amount*sizeof(SOFT **);
*/
	cede				(S->raw[0],S->size[0]);
}


static	inline	void	optional_index_	(RMETA *,SOFT *,SOFT ***);

__attribute__((noinline))
SCV	optional_index			(RMETA *R)
{	uint32_t	c;
	SOFT		*S=		R->smap.at;
	SOFT		*T=		R->smap.next;
	for				(c=T-S;T>S;S++)
	if		yay		(S->raw[1]!=NULL)
	c+=		line_count	(S->raw[1]);

	REF		*r=		R->ref+1;

	r->size=
	sizeof				(SOFT *)*c;
	r->at=
	r->next=
	pool				(r->size);

	SOFT		**t=		r->at;
	S=				R->smap.at;
	for				(;T>S;S++)
	optional_index_			(R,S,&t);
}

static	inline	void	optional_index_	(RMETA *R, SOFT *S, SOFT ***T)
{	if		yay		(S->raw[1]==NULL)
	return;

	RMAP		*r=		&S->rmap[1];
	r->next=
	r->at=				*T;

	SOFT		**v=		S->rmap[0].at;
	SOFT		**t=		*T;
	uint8_t		*a=		S->raw[1],
			*b;
	if				(v!=NULL)
	for				(;*a!=0;a++)
	{	for			(   ;*a=='\n';a++);
		for			(b=a;*a!='\n';a++);
		SOFT	*s=
		soft_find_make		(R,b,a-b);

		SOFT	**f;
		for			(f=v;*f;f++)
		if			(*f==s)
		break;

		if			(*f!=s)
		*t++=			s;
	}
	else
	for				(;*a!=0;a++)
	{	for			(   ;*a=='\n';a++);
		for			(b=a;*a!='\n';a++);
		*t++=
		soft_find_make		(R,b,a-b);
	}

	r->amount=			t-*T;
	*T=				t+1;

/*	r->size=			r->amount*sizeof(SOFT **);
*/

	cede				(S->raw[1],S->size[1]);
}

static	inline	void	selected_index_	(RMETA *,SOFT *,SOFT ***);

__attribute__((noinline))
SCV	selected_index			(RMETA *R)
{	uint32_t	c;
	SOFT		*S=		R->smap.at;
	SOFT		*T=		R->smap.next;
	for				(c=T-S;T>S;S++)
	if		yay		(S->raw[2]!=NULL)
	c+=		line_count	(S->raw[2]);

	REF		*r=		R->ref+2;

	r->size=
	sizeof				(SOFT *)*c;
	r->at=
	r->next=
	pool				(r->size);

	SOFT		**t=		r->at;
	S=				R->smap.at;
	for				(;T>S;S++)
	selected_index_			(R,S,&t);
}

static	inline	void	selected_index_	(RMETA *R, SOFT *S, SOFT ***T)
{	if			yay	(S->raw[2]==NULL)
	return;

	RMAP		*r;
	r=				S->rmap+2;
	r->next=
	r->at=				*T;

	SOFT		**v=		S->rmap[1].at;
	SOFT		**t=		*T;
	uint8_t		*a=		S->raw[2],
			*b;
	if				(v!=NULL)
	for				(;*a!=0;a++)
	{	for			(   ;*a=='\n';a++);
		for			(b=a;*a!='\n';a++);
		SOFT	*s=
		soft_find		(R,b,a-b);
		/* must already be known */
		if		nay	(s==NULL)
		continue;

		/* must be optional */
		SOFT	**f;
		for			(f=v;*f;f++)
		if			(*f==s)
		{	*t++=		s;
			break;
		}
	}
	else
	for				(a=S->raw[2];*a!=0;a++)
	{	for			(   ;*a=='\n';a++);
		for			(b=a;*a!='\n';a++);
		SOFT	*s=
		soft_find		(R,b,a-b);
		/* must already be known */
		if		yay	(s!=NULL)
		*t++=			s;
	}

	r->amount=			t-*T;
	*T=				t+1;

/*	r->size=			r->amount*sizeof(SOFT **);
*/
	cede				(S->raw[2],S->size[2]);
}


static		uint32_t	must_optional_count	(RMETA *,SOFT *);
static		void		must_optional_index_	(RMETA *,SOFT *,SOFT ***);

__attribute__((noinline))
SCV	must_optional_index		(RMETA *R)
{	uint32_t	c,e;
	SOFT		*S=		R->smap.at;
	SOFT		*T=		R->smap.next;

	for				(c=0,e=1;T>S;S++)
	if				(S->rmap[3].count_done!=0)
	c+=				 S->rmap[3].amount;
	else
	{	S->rmap[3].count_done=	e++;
		c+=
		must_optional_count	(R,S);
	}

	REF		*r=		R->ref+3;

	r->size=
	sizeof				(SOFT *)*c;
	r->at=
	r->next=
	pool				(r->size);

	SOFT		**t=		r->at;
	for				(S=R->smap.at;T>S;S++)
	if				(S->rmap[3].done==0)
	must_optional_index_		(R,S,&t);
	r->next=			t;
}

__attribute__((noinline))
static		uint32_t	must_optional_count	(RMETA *R,SOFT *S)
{	RMAP		*r;
	r=					S->rmap+3;
	uint32_t	d=			r->count_done;
	SOFT		**s;

	r=					S->rmap;
	s=					r->at;
	uint32_t	a=			1;		/* itself */
	if					(  s!=NULL)
	for					(;*s!=NULL;s++)
	{	RMAP	*r=			s[0]->rmap+3;
		if	yay			(r->count_done!=d)
		if				(r->count_done!=0)
		{	r->count_done=		d;
			a+=			 r->amount;
		}
		else
		{	r->count_done=		d;
			a+=
			must_optional_count	(R,*s);
		}
	}

	r=					S->rmap+1;
	s=					r->at;
	if					(  s!=NULL)
	for					(;*s!=NULL;s++)
	{	RMAP	*r=			s[0]->rmap+3;
		if	yay			(r->count_done!=d)
		if				(r->count_done!=0)
		{	r->count_done=		d;
			a+=			 r->amount;
		}
		else
		{	r->count_done=		d;
			a+=
			must_optional_count	(R,*s);
		}
	}

	r=					S->rmap+3;
	r->amount=				a;
	return					a;
}

static		int	contained		(SOFT  **,SOFT *);
static		void	list_unique_copy	(SOFT ***,SOFT **,uint32_t);
static		void	list_unique_add		(SOFT ***,SOFT  *,uint32_t);

__attribute__((noinline))
SCV	must_optional_index_		(RMETA *R, SOFT *S, SOFT ***T)
{	RMAP		*r;
	SOFT		**s;

	r=				S->rmap+3;
	r->entered=			1;

	r=				S->rmap;
	s=				r->at;
	if		yay		(  s!=NULL)
	for				(;*s!=NULL;s++)
	{	RMAP	*r=		s[0]->rmap+3;
		if	nay		(r->done==0)
		if	yay		(r->entered==0)
		must_optional_index_	(R,*s,T);
		else
		warnx			("%s%s	%s","RR:	",
					 (*s)->name,S->name);
	}

	r=				S->rmap+1;
	s=				r->at;
	if		yay		(  s!=NULL)
	for				(;*s!=NULL;s++)
	{	RMAP	*r=		s[0]->rmap+3;
		if	nay		(r->done==0)
		if	yay		(r->entered==0)
		must_optional_index_	(R,*s,T);
		else
		warnx			("%s%s	%s","RR:	",
					 (*s)->name,S->name);
	}

	SOFT		**t=		*T;
	r=				S->rmap+3;
	r->next=
	r->at=				*T;

	uint32_t	u=		++(R->unique);

	r=				S->rmap;
	s=				r->at;
	if		yay		(  s!=NULL)
	for				(;*s!=NULL;s++)
	{	list_unique_copy	(&t,s[0]->rmap[3].at,u);
		list_unique_add		(&t,*s,u);
	}

	r=				S->rmap+1;
	s=				r->at;
	if		yay		(  s!=NULL)
	for				(;*s!=NULL;s++)
	{	list_unique_copy	(&t,s[0]->rmap[3].at,u);
		list_unique_add		(&t,*s,u);
	}

	r=				S->rmap+3;
	r->done=			1;
	r->amount=			t-*T;
	*T=				t+1;
/*	r->size=			r->amount*sizeof(SOFT **);
*/
}


static		uint32_t	must_selected_count	(RMETA *,SOFT *);
static		void		must_selected_index_	(RMETA *,SOFT *,SOFT ***);

__attribute__((noinline))
SCV	must_selected_index		(RMETA *R)
{	uint32_t	c,e;
	SOFT		*S=		R->smap.at;
	SOFT		*T=		R->smap.next;

	for				(c=0,e=1;T>S;S++)
	if				(S->rmap[4].count_done!=0)
	c+=				 S->rmap[4].amount;
	else
	{	S->rmap[4].count_done=	e++;
		c+=
		must_selected_count	(R,S);
	}

	REF		*r=		R->ref+4;

	r->size=
	sizeof				(SOFT *)*c;
	r->at=
	r->next=
	pool				(r->size);

	SOFT		**t=		r->at;
	for				(S=R->smap.at;T>S;S++)
	if				(S->rmap[4].done==0)
	must_selected_index_		(R,S,&t);
	r->next=			t;
}

static	CALIGN	uint32_t	must_selected_count	(RMETA *R,SOFT *S)
{	RMAP		*r;
	r=					S->rmap+4;
	uint32_t	d=			r->count_done;
	SOFT		**s;

	r=					S->rmap;
	s=					r->at;
	uint32_t	a=			1;		/* itself */
	if					(  s!=NULL)
	for					(;*s!=NULL;s++)
	{	RMAP	*r=			s[0]->rmap+4;
		if	yay			(r->count_done!=d)
		if				(r->count_done!=0)
		{	r->count_done=		d;
			a+=			 r->amount;
		}
		else
		{	r->count_done=		d;
			a+=
			must_selected_count	(R,*s);
		}
	}

	r=					S->rmap+2;
	s=					r->at;
	if					(  s!=NULL)
	for					(;*s!=NULL;s++)
	{	RMAP	*r=			s[0]->rmap+4;
		if	yay			(r->count_done!=d)
		if				(r->count_done!=0)
		{	r->count_done=		d;
			a+=			 r->amount;
		}
		else
		{	r->count_done=		d;
			a+=
			must_selected_count	(R,*s);
		}
	}

	r=					S->rmap+4;
	r->amount=				a;
	return					a;
}

SCV	must_selected_index_		(RMETA *R, SOFT *S, SOFT ***T)
{	RMAP		*r;
	SOFT		**s;

	r=				S->rmap+4;
	r->entered=			1;

	r=				S->rmap;
	s=				r->at;
	if		yay		(  s!=NULL)
	for				(;*s!=NULL;s++)
	{	RMAP	*r=		s[0]->rmap+4;
		if	nay		(r->done==0)
		if	yay		(r->entered==0)
		must_selected_index_	(R,*s,T);
	}

	r=				S->rmap+2;
	s=				r->at;
	if		yay		(  s!=NULL)
	for				(;*s!=NULL;s++)
	{	RMAP	*r=		s[0]->rmap+4;
		if	nay		(r->done==0)
		if	yay		(r->entered==0)
		must_selected_index_	(R,*s,T);
	}

	SOFT		**t=		*T;
	r=				S->rmap+4;
	r->next=
	r->at=				*T;

	uint32_t	u=		++(R->unique);

	r=				S->rmap;
	s=				r->at;
	if		yay		(  s!=NULL)
	for				(;*s!=NULL;s++)
	{	list_unique_copy	(&t,s[0]->rmap[4].at,u);
		list_unique_add		(&t,*s,u);
	}

	r=				S->rmap+2;
	s=				r->at;
	if		yay		(  s!=NULL)
	for				(;*s!=NULL;s++)
	{	list_unique_copy	(&t,s[0]->rmap[4].at,u);
		list_unique_add		(&t,*s,u);
	}

	r=				S->rmap+4;
	r->done=			1;
	r->amount=			t-*T;
	*T=				t+1;
/*	r->size=			r->amount*sizeof(SOFT **);
*/
}


static		void		want_optional_count	(RMETA *,SOFT *);
static		void		want_optional_index_	(RMETA *,SOFT *);

__attribute__((noinline))
SCV	want_optional_index		(RMETA *R)
{	SOFT		*S,*T=		R->smap.next;

	for				(S=R->smap.at;T>S;S++)
	want_optional_count		(R,S);

	uint32_t	c;
	for				(S=R->smap.at,c=T-S;T>S;S++)
	c+=				S->rmap[5].amount;

	REF		*r=		R->ref+5;

	r->size=
	sizeof				(SOFT *)*c;
	r->at=
	r->next=
	pool				(r->size);

	SOFT		**s=		r->at;
	for				(S=R->smap.at;T>S;S++)
	{	S->rmap[5].at=
		S->rmap[5].next=	s;
		s+=			S->rmap[5].amount+1;
	}

	for				(S=R->smap.at;T>S;S++)
	want_optional_index_		(R,S);
}

__attribute__((noinline))
SCV	want_optional_count			(RMETA *R,SOFT *S)
{	RMAP		*r=			S->rmap+3;
	SOFT		**s=			r->at;
	if					(  s!=NULL)
	for					(;*s!=NULL;s++)
	s[0]->rmap[5].amount++;
}

static	CALIGN	void	want_optional_index_	(RMETA *R, SOFT *S)
{	RMAP		*r=			S->rmap+3;
	SOFT		**s=			r->at;

	if					(  s!=NULL)
	for					(;*s!=NULL;s++)
	{	s[0]->rmap[5].next[0]=		S;
		s[0]->rmap[5].next++;
	}

/*	r=					S->rmap+5;
	r->size=				r->amount*sizeof(SOFT **);
*/
}

static		void		want_selected_count	(RMETA *,SOFT *);
static		void		want_selected_index_	(RMETA *,SOFT *);

__attribute__((noinline))
SCV	want_selected_index		(RMETA *R)
{	SOFT		*S,*T=		R->smap.next;

	for				(S=R->smap.at;T>S;S++)
	want_selected_count		(R,S);

	uint32_t	c;
	for				(S=R->smap.at,c=T-S;T>S;S++)
	c+=				S->rmap[6].amount;

	REF		*r=		R->ref+6;

	r->size=
	sizeof				(SOFT *)*c;
	r->at=
	r->next=
	pool				(r->size);

	SOFT		**s=		r->at;
	for				(S=R->smap.at;T>S;S++)
	{	S->rmap[6].at=
		S->rmap[6].next=	s;
		s+=			S->rmap[6].amount+1;
	}

	for				(S=R->smap.at;T>S;S++)
	want_selected_index_		(R,S);
}

__attribute__((noinline))
SCV	want_selected_count		(RMETA *R,SOFT *S)
{	RMAP		*r=		S->rmap+4;
	SOFT		**s=		r->at;
	if				(  s!=NULL)
	for				(;*s!=NULL;s++)
	s[0]->rmap[6].amount++;
}

SCV	want_selected_index_		(RMETA *R, SOFT *S)
{	RMAP		*r=		S->rmap+4;
	SOFT		**s=		r->at;

	if				(  s!=NULL)
	for				(;*s!=NULL;s++)
	{	s[0]->rmap[6].next[0]=	S;
		s[0]->rmap[6].next++;
	}

/*	r=				S->rmap+6;
	r->size=			r->amount*sizeof(SOFT **);
*/
}

SCV	list_unique_copy	(SOFT ***T,SOFT **s,uint32_t u)
{	SOFT		**t=	*T;
	for			(;*s;s++)
	if		yay	(s[0]->unique!=u)
	{	s[0]->unique=	u;
		*t++=		*s;
	}
	*T=			t;
}

SCV	list_unique_add		(SOFT ***T,SOFT *s,uint32_t u)
{	SOFT		**t=	*T;
	if		yay	(s->unique!=u)
	{	s->unique=	u;
		*t++=		s;
		*T=		t;
	}
}

__attribute__((unused))
static	CALIGN	int	contained	(SOFT **a, SOFT *s)
{	SOFT		*b;
	for				(;b=*a;a++)
	if		nay		(b==s)
	return				1;
	return				0;
}

static	CALIGN	uint32_t	topic_index_count	(SOFT *);
SCV	topic_index_append		(uint8_t **,SOFT *);
SCV	topic_index			(RMETA *R)
{	VMETA		*F=		R->var.topic_list;
	SOFT		*S,*T=		R->smap.next;
	uint32_t	c;
	for				(c=0,S=R->smap.at;T>S;S++)
	c+=	topic_index_count	(S);

	map_add				(F,c+0x40,0);
	F->textlen=			c;

	uint8_t		*a=		F->textaddr;
	for				(S=R->smap.at;T>S;S++)
	topic_index_append		(&a,S);
}

static	CALIGN	uint32_t	topic_index_count	(SOFT *S)
{	uint32_t	a=		S->rmap[0].amount+
					S->rmap[1].amount;
	if		nay		(a==0)
	return				(S->len+1)*2;

	a*=				S->len+2;

	SOFT		**s=		S->rmap[0].at;
	if				(  s!=NULL)
	for				(;*s!=NULL;s++)
	a+=				s[0]->len;

	s=				S->rmap[1].at;
	if				(  s!=NULL)
	for				(;*s!=NULL;s++)
	a+=				s[0]->len;

	return				a;
}

SCV	topic_index_append		(uint8_t **A,SOFT *S)
{	uint32_t	a=		S->rmap[0].amount+
					S->rmap[1].amount;
	if		nay		(a==0)
	{	memcpya			(*A,S->name,S->len);
		(*A)+=			S->len;
		A[0][0]=		'\t';
		(*A)++;
		memcpya			(*A,S->name,S->len);
		(*A)+=			S->len;
		A[0][0]=		'\n';
		(*A)++;
		return;
	}

	SOFT		**s=		S->rmap[0].at;
	if				(  s!=NULL)
	for				(;*s!=NULL;s++)
	{	memcpya			(*A,S->name,S->len);
		(*A)+=			S->len;
		A[0][0]=		'\t';
		(*A)++;
		memcpya			(*A,s[0]->name,s[0]->len);
		(*A)+=			s[0]->len;
		A[0][0]=		'\n';
		(*A)++;
	}

	s=				S->rmap[1].at;
	if				(  s!=NULL)
	for				(;*s!=NULL;s++)
	{	memcpya			(*A,S->name,S->len);
		(*A)+=			S->len;
		A[0][0]=		'\t';
		(*A)++;
		memcpya			(*A,s[0]->name,s[0]->len);
		(*A)+=			s[0]->len;
		A[0][0]=		'\n';
		(*A)++;
	}
}

static	inline	uint32_t	line_count	(uint8_t *a)
{	uint32_t	b;
	uint8_t		c;
	for				(b=0;c=*a;a++)
	if		nay		(c=='\n')
	b++;
	return				b;
}

static	CALIGN	SOFT	*soft_make	(RMETA *R, uint8_t *a, uint8_t b)
{	SOFT		*s=		R->smap.next;
	R->smap.next++;
	memcpy				(s->name,a,s->len=b);

	SOFT		**S=		R->name+
	bit128_to_bit16			(s->name);

	s->next=			*S;
	*S=				s;
	return				s;
}

static	CALIGN	SOFT	*soft_find_make	(RMETA *R, uint8_t *a, uint8_t b)
{	SOFT		*s=		R->smap.next;
	memcpy				(s->name,a,s->len=b);
	s->name[b]=			0;

	SOFT		**S=		R->name+
	bit128_to_bit16			(s->name);

	if		yay		(*S==NULL)
	{	R->smap.next++;
		*S=			s;
		return			s;
	}

	SOFT		*f;
	for				(b++,f=*S;f!=NULL;f=f->next)
	if		yay		(memcmp(f->name,s->name,b)==0)
	{	memset			(s->name,0,0x10);
		return			f;
	}

	R->smap.next++;
	s->next=			*S;
	*S=				s;
	return				s;
}

static	CALIGN	SOFT	*soft_find	(RMETA *R, uint8_t *a, uint8_t b)
{	SOFT		*s=		R->smap.next;
	memcpy				(s->name,a,b);
	s->name[b]=			0;

	SOFT		**S=		R->name+
	bit128_to_bit16			(s->name);

	SOFT		*f;
	for				(b++,f=*S;f!=NULL;f=f->next)
	if		yay		(memcmp(f->name,s->name,b)==0)
	{	memset			(s->name,0,0x10);
		return			f;
	}

	memset				(s->name,0,0x10);
	return				NULL;
}

SCV	softreq	(void)	{tvarnewab(softreqsubnew,softreq);}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180829",
	.official=	"20180829",
	.update=	"20200924"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(softreq,	"softreq");
	aa_fini		();
};

__attribute__((constructor))
SCV	init				(void)
{	opsoftreq[0].equal=		equal0_delegate;
	opsoftreq[0].query=		equal0_wait;
	opsoftreq[1].equal=		equal1;
	opsoftreq[2].equal=		equal2;
/*	opsoftreq[3].show=		show_load;
	opsoftreq[4].show=		show_moil;
*/
	opsoftreq[6].equal=		equal6;
	opsoftreq[7].equal=		equal7;
}
