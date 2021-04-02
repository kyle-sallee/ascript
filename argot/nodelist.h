/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_NODELIST_H
#define		_A_NODELIST_H
#include	"stat.h"
#include	<dirent.h>
#include	<sys/types.h>

struct	direntm
{	ino_t			d_ino;
	off_t			d_off;
	unsigned	short	d_reclen;
	unsigned	char	d_type;
			char	d_name[PATH_MAX];
};

/*	To  avoid some confusion in the future.
	The des  to use is always in the -1  offset  structure
	The dirp to use is always in the [0] offset  structure.
	the ent  to use is always in the [0] offset  structure.
	level[0].des is open for the present working directory.
	level[0].ent describes the   present working directory.

	level[1].ent descripbes the  v[...]          directory.
	Thus when entering directory at lp
	the earlier descriptor for lp's container directory
	is required by funtion openat.
	After a moment's consideration
	it should make sense.
*/

typedef	struct
{	struct dirent	*ent;
	int		des;
	DIR		*dirp;
	size_t		len;
}	LEVEL;

typedef	struct
{	uint8_t		(*next)		(void);
	uint8_t		*host;
	int		host_len;

	LEVEL		*lp;
	LEVEL		level		[0x100];

	struct	stat	*stat_buf;

	struct	direntm	ent[2];			/* level[0].ent level[1].ent */

	uint8_t		dir_first;		/*	+		*/
	uint8_t		dir_last;		/*	-		*/

/*	CALIGN
	uint8_t		want[0x100];	*/	/*	=	|	*/
	/* block char dir fifo file sym socket */

	PALIGN
	uint8_t		full[PAGE];
	uint8_t		lean[PAGE];
	uint8_t		less[PAGE];
	uint8_t		link[PAGE];
	uint8_t		most[PAGE];
	uint8_t		name[PAGE];
	uint8_t		path[PAGE];
	struct	stat	stat_back[2];

}	NODELISTDATA;

__attribute__((always_inline))
static	inline	 NODELISTDATA *	nodelistdata	(VMETA *A)
{	return	(NODELISTDATA *)	A->dataaddr;
}

SCV	reval_link		(VMETA *A)
{	NODELISTDATA	*a=
	nodelistdata		(A);
/*	A->datause=		0;	*/
	A->textaddr[
	A->textlen=0]=		0;

	size_t		T;
	LEVEL		*lp=	a->lp;
	if		yay	((lp->ent!=NULL)&&
				 (lp->ent->d_type==DT_LNK))
/*	if		nay	((lp=D->lp)!=D->level)	*/
	{	int	e=	errna;
		errna=		0;
		T=
		readlinkat	(lp[-1].des,
				 lp->ent->d_name,
				 A->textaddr,
				 A->textsize);
		errna=		e;
		if	nay	(0>T)
		T=		0;
		A->textaddr[
		A->textlen=T]=	0;
	}
	else
	A->textaddr[
	A->textlen=0]=		0;
}

SCV	reval_full		(VMETA *A)
{	NODELISTDATA	*a=
	nodelistdata		(A);
	LEVEL		*lp;
	uint8_t		*t;

	t=			A->textaddr;
	if			(a->level[1].ent->d_name[0]!='/')
	lp=			a->level;
	else
	lp=			a->level+1;

	for			(;lp->ent;lp++)
	{	memcpya		(t,
				 lp->ent->d_name,
				 lp->len);
		t+=		 lp->len;
		*t++=		'/';
	}
	*(--t)=			0;
	A->textlen=		t-A->textaddr;
}

SCV	reval_most		(VMETA *A)
{	NODELISTDATA	*a=
	nodelistdata		(A);
	LEVEL		*lp=	a->level+1;

	uint8_t		*t;
	t=			A->textaddr;

	for			(;lp->ent;lp++)
	{	memcpya		(t,lp->ent->d_name,lp->len);
		t+=		lp->len;
		*t++=		'/';
	}
	*(--t)=			0;
	A->textlen=		t-A->textaddr;
}

SCV	reval_path		(VMETA *A)
{	NODELISTDATA	*a=
	nodelistdata		(A);
	LEVEL		*lp=	a->level+1;

	uint8_t		*t;
	t=			A->textaddr;

	for			(;a->lp>lp;lp++)
	{	memcpya		(t,lp->ent->d_name,lp->len);
		t+=		lp->len;
		*t++=		'/';
	}
/*	*(--t)=			0;	*/
	*t=			0;
	A->textlen=		t-A->textaddr;
}

SCV	reval_less		(VMETA *A)
{	NODELISTDATA	*a=
	nodelistdata		(A);
	LEVEL		*lp=	a->level+2;

	uint8_t		*t;
	t=			A->textaddr;

	for			(;a->lp>lp;lp++)
	{	memcpya		(t,lp->ent->d_name,lp->len);
		t+=		lp->len;
		*t++=		'/';
	}
/*	*(--t)=			0;	*/
	*t=			0;
	A->textlen=		t-A->textaddr;
}

SCV	reval_lean		(VMETA *A)
{	NODELISTDATA	*a=
	nodelistdata		(A);
	LEVEL		*lp=	a->level+2;

	uint8_t		*t;
	t=			A->textaddr;

	if		yay	( lp->ent!=NULL)
	{	for		(;lp->ent;lp++)
		{	memcpya	(t,lp->ent->d_name,lp->len);
			t+=	lp->len;
			*t++=	'/';
		}
		--t;
	}

	*t=			0;
	A->textlen=		t-A->textaddr;
}

SCV	reval_name		(VMETA *A)
{	NODELISTDATA	*a=
	nodelistdata		(A);
	LEVEL		*lp=	a->lp;
	if		yay	(lp->ent!=NULL)
	{	A->textlen=	lp->len;
		memcpya		(A->textaddr,
				 lp->ent->d_name,
				 lp->len+1);
	}
	else
	A->textaddr[
	A->textlen=0]=		0;
}


__attribute__((noinline))
SCV	reval_nl_type		(VMETA *A)
{	NODELISTDATA	*a=
	nodelistdata		(A);
	LEVEL		*lp=	a->lp;

	if		yay	(a->stat_buf==a->stat_back)
	if		yay	(lp->dirp!=NULL)
	fstatat			(dirfd(lp->dirp),
				       lp->ent->d_name,
				 a->stat_buf,
				 AT_SYMLINK_NOFOLLOW);
	else
	lstat			(lp->ent->d_name,a->stat_buf);
	A->value.i=		a->stat_buf->st_mode&S_IFMT;
}

SCV	reval_deep		(VMETA *A)
{	NODELISTDATA	*a=
	nodelistdata		(A);
	A->value.i=		a->lp-a->level-1;
}

typedef	struct	{uint8_t b[7],a;}	TYPECONST;

SCV	reval_typetext	(VMETA *A)
{	static	const	TYPECONST	a[0x10]=
	{	[S_IFREG>>0xc]={"file",4},
		[S_IFDIR>>0xc]={"dir",3},
		[S_IFLNK>>0xc]={"sym",3},
		[S_IFBLK>>0xc]={"block",5},
		[S_IFCHR>>0xc]={"char",4},
		[S_IFIFO>>0xc]={"fifo",4},
		[S_IFSOCK>>0xc]={"sock",4}
	};

	reval_nl_type		(A);
	uint8_t		b=	A->value.i>>0xc;
	A->textlen=		a[b].a;
	__builtin_memcpy	(A->textaddr,a[b].b,8);
}

static	inline	void	closedir_all	(NODELISTDATA *D)
{	LEVEL		*L;
	for				(L=D->level+1;L->dirp;L++)
	closedir			(L->dirp);

	int		d=		D->level[0].des;
	if			nay	(d)
	close				(d);
}

static	CALIGN	void	nodelistfree	(VMETA *A)
{	closedir_all			(nodelistdata(A));
	munmap				(A->dataaddr,A->datasize);
	vmeta_free			(A);
}

static	inline	void	nodelistsubnew	(VMETA *A)
{	A->op=			opnodelist;
	A->free=		nodelistfree;
	map_add			(A,0,sizeof(NODELISTDATA));
	NODELISTDATA	*a=
	nodelistdata		(A);
	a->stat_buf=		a->stat_back;
	a->dir_first=		1;
	a->lp=			a->level;
	a->level[0].ent=	(struct dirent *)	&a->ent[0];
	a->level[1].ent=	(struct dirent *)	&a->ent[1];
}

static	inline	void	nodelistdeepsubnew	(VMETA *A)
{	VMETA		*B;
	B=	var_new_sub	(".deep",A);
	int4init		(B);
	B->reval=		reval_deep;
	B->dataaddr=		A->dataaddr;
}

static	inline	void	nodelistfullsubnew	(VMETA *A)
{	VMETA		*B;
	B=	var_new_sub	(".full",A);
	byteinit		(B);
	B->reval=		reval_full;
	B->dataaddr=		A->dataaddr;
	NODELISTDATA	*a=
	nodelistdata		(B);
	B->textaddr=		a->full;
}

static	inline	void	nodelistleansubnew	(VMETA *A)
{	VMETA		*B;
	B=	var_new_sub	(".lean",A);
	byteinit		(B);
	B->reval=		reval_lean;
	B->dataaddr=		A->dataaddr;
	NODELISTDATA	*a=
	nodelistdata		(B);
	B->textaddr=		a->lean;
}

static	inline	void	nodelistlesssubnew	(VMETA *A)
{	VMETA		*B;
	B=	var_new_sub	(".less",A);
	byteinit		(B);
	B->reval=		reval_less;
	B->dataaddr=		A->dataaddr;
	NODELISTDATA	*a=
	nodelistdata		(B);
	B->textaddr=		a->less;
}

static	inline	void	nodelistlinksubnew	(VMETA *A)
{	VMETA		*B;
	B=	var_new_sub	(".link",A);
	byteinit		(B);
	B->reval=		reval_link;
	B->dataaddr=		A->dataaddr;
	NODELISTDATA	*a=
	nodelistdata		(B);
	B->textaddr=		a->link;
}

static	inline	void	nodelistmostsubnew	(VMETA *A)
{	VMETA		*B;
	B=	var_new_sub	(".most",A);
	byteinit		(B);
	B->reval=		reval_most;
	B->dataaddr=		A->dataaddr;
	NODELISTDATA	*a=
	nodelistdata		(B);
	B->textaddr=		a->most;
}

static	inline	void	nodelistnamesubnew	(VMETA *A)
{	VMETA		*B;
	B=	var_new_sub	(".name",A);
	byteinit		(B);
	B->reval=		reval_name;
	B->dataaddr=		A->dataaddr;
	NODELISTDATA	*a=
	nodelistdata		(B);
	B->textaddr=		a->name;
}

static	inline	void	nodelistpathsubnew	(VMETA *A)
{	VMETA		*B;
	B=	var_new_sub	(".path",A);
	byteinit		(B);
	B->reval=		reval_path;
	B->dataaddr=		A->dataaddr;
	NODELISTDATA	*a=
	nodelistdata		(B);
	B->textaddr=		a->path;
}

static	inline	void	nodelisttypesubnew	(VMETA *A)
{	VMETA		*B;
	B=	var_new_sub	(".type",A);
	byteinit		(B);
	B->reval=		reval_typetext;
	B->dataaddr=		A->dataaddr;
}
#endif
