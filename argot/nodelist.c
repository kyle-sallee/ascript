/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"byte.h"
#include	"int.h"
#include	"a.h"
#include	"nodelist.h"

static		uint8_t	next_above	(void);
static		uint8_t	next_done	(void);
static		uint8_t	next_enter	(void);
static		uint8_t	next_read	(void);
static		uint8_t	next_start	(void);

SCV	nodelistpathname	(void)
{	VMETA		*B=	Gz.to[0];
	NODELISTDATA	*a=
	nodelistdata		(Gz.active.nodelist);

	closedir_all		(a);

	a->host=		B->textaddr;
	a->host_len=		B->textlen;
	while			(a->host[a->host_len-1]==0)
	a->host_len--;
	a->next=		next_start;

	unsigned char	*b=	a->level[0].ent->d_name;

	getcwd			(b,PATH_MAX);
	a->level[0].len=
	strlenb			(b);

	/* highmake */
	a->level[0].des=
	open			(".",
				 O_CLOEXEC|O_DIRECTORY|
				 O_NOATIME,O_PATH);

/*	if		nay	(a->level[0].des>c)
	a->next=		next_done;
*/

	*Gz.at=			nodelistpathname;
	argot_next		();
}

SCV	nodeliststat		(void)
{	VMETA		*A=	Gz.to[0];
	NODELISTDATA	*a=
	nodelistdata		(Gz.active.nodelist);
	a->stat_buf=
	statbuf			(A);
	*Gz.at=			nodeliststat;
	argot_next		();
}

SCV	nodelistdirhead		(void)
{	NODELISTDATA	*a=
	nodelistdata		(Gz.active.nodelist);
	a->dir_first=		1;
	a->dir_last=		0;
	*Gz.at=			nodelistdirhead;
	argot_next		();
}

SCV	nodelistdirtail		(void)
{	NODELISTDATA	*a=
	nodelistdata		(Gz.active.nodelist);
	a->dir_first=		0;
	a->dir_last=		1;
	*Gz.at=			nodelistdirtail;
	argot_next		();
}

SCV	nodelistsymlist		(void)
{	NODELISTDATA	*a=
	nodelistdata		(Gz.active.nodelist);
	if		yay	( a->lp->ent!=NULL)
	if			((a->lp->ent->d_type==DT_DIR)||
				 (a->lp->ent->d_type==DT_LNK))
	a->next=		next_enter;
	*Gz.at=			nodelistsymlist;
	argot_next		();
}

SCV	nodelistdirskip		(void)
{	NODELISTDATA	*a=
	nodelistdata		(Gz.active.nodelist);
	if		yay	(a->next==next_enter)
	a->next=		next_read;
	*Gz.at=			nodelistdirskip;
	argot_next		();
}

__attribute__((noinline))
SCV	nodelistnext_		(void)
{	NODELISTDATA	*a=
	nodelistdata		(Gz.active.nodelist);
	(*(Gz.at+=a->next()))	();
}

SCV		nodelistnext	(void)
{	(*Gz.at=nodelistnext_)	();
}

SCV	nodelistdirdone		(void)
{	NODELISTDATA	*a=
	nodelistdata		(Gz.active.nodelist);
	a->next=		next_above;
	*Gz.at=			nodelistdirdone;
	argot_next		();
}

__attribute__((unused))
static	inline	uint8_t	sif_to_dt	(int a)
{	switch		(a)
	{	case	S_IFREG:	return	DT_REG;
		case	S_IFDIR:	return	DT_DIR;
		case	S_IFLNK:	return	DT_LNK;
		case	S_IFBLK:	return	DT_BLK;
		case	S_IFCHR:	return	DT_CHR;
		case	S_IFIFO:	return	DT_FIFO;
		case	S_IFSOCK:	return	DT_SOCK;
	}
}

__attribute__((noinline))
static	CALIGN	uint8_t	next_done	(void)
{
/*	*Gz.at=	next_done;	*/

	return		1;
}

static	CALIGN	void	tacit_stat	(NODELISTDATA *);
static		unsigned char		mode_t_to_dt	(mode_t);

__attribute__((noinline))
static	CALIGN	uint8_t	next_start	(void)
{	errna=				0;
	NODELISTDATA	*a=
	nodelistdata			(Gz.active.nodelist);

/*
	unsigned char	*b=		a->level[0].ent->d_name;

	getcwd				(b,PATH_MAX);
	a->level[0].len=
	strlenb				(b);

	int		c=
	open				(".",
					 O_CLOEXEC|O_DIRECTORY|
					 O_NOATIME,O_PATH);

	if			nay	(0>c)
	{	fail:
		a->next=		next_done;
		argot_next		();
		return;
	}

	a->level[0].des=
	highmake			(c);
*/

	errna=				0;
	unsigned char	*name=		a->level[1].ent->d_name;

	a->level[1].len=		a->host_len;
	ascript_memcpy			(name,a->host,a->host_len+1);

	a->next=			next_enter;

	LEVEL		*lp=
	a->lp=				a->level+1;

	int		e=
	lstat				(name,a->stat_buf);

	if			nay	(e!=0)
	{	a->next=		next_done;
		return			1;
	}

	struct	stat	*s=		a->stat_buf;

	unsigned	char	type=
	lp->ent->d_type=
	mode_t_to_dt			(s->st_mode);

	if			nay	(type==DT_DIR)
	{	if		nay	(a->dir_first==0)
		return	a->next		();
	}
	else
	a->next=			next_done;

	return				2;
}

__attribute__((noinline))
static	CALIGN	uint8_t	next_enter	(void)
{	errna=				0;
	NODELISTDATA	*a=
	nodelistdata			(Gz.active.nodelist);
	a->next=			next_read;
	LEVEL		*lp=		a->lp;

	int		d=
	openat				(lp[-1].des,
					 lp->ent->d_name,
					 O_DIRECTORY|O_RDONLY);

	if			nay	(0>d)
	return				1;

/*	d=	highmake		(d);	*/
	lp->des=			d;

	DIR		*dirp=
	fdopendir			(d);

	if			yay	(dirp!=NULL)
	{	lp=			++(a->lp);
/*		lp->d_type=		lp[-1].ent->d_type;	*/
		lp->dirp=		dirp;
		return
		next_read		();
	}
	else
	return				1;
}

__attribute__((noinline))
static	CALIGN	uint8_t	next_above	(void)
{	NODELISTDATA	*a=
	nodelistdata			(Gz.active.nodelist);

	LEVEL		*lp=		a->lp;
	closedir			(lp->dirp);
	lp->dirp=			NULL;
	lp->ent=			NULL;
	lp=				--(a->lp);

	if				(lp>a->level+1)
	a->next=			next_read;
	else
	a->next=			next_done;

/*	unsigned char	type=		lp->d_type;
*/
	unsigned char	type=		lp->ent->d_type;


	if			yay	(type==DT_DIR)
	if			yay	(a->dir_last==0)
	return	a->next			();

	return				2;
}

__attribute__((noinline))
static	CALIGN	uint8_t	next_read	(void)
{	errna=				0;
	NODELISTDATA	*a=
	nodelistdata			(Gz.active.nodelist);
	LEVEL		*lp=		a->lp;
	struct dirent	*ent;

	while				(1)
	{	ent=	readdir		(lp->dirp);

		if		nay	(ent==NULL)
		return
		(a->next=next_above)	();
		uint8_t		*b=	ent->d_name;
		if		yay	(b[0]!='.')	break;
		if		nay	(b[1]==0)	continue;
		if		nay	(b[1]!='.')	break;
		if		yay	(b[2]!=0)	break;
	}

	lp->ent=			ent;
/*	tacit_stat			(A,a);	*/
	tacit_stat			(a);
	lp->len=
	strlenb				(lp->ent->d_name);

	unsigned	char	type=	ent->d_type;

	if			nay	(type==DT_DIR)
	{	a->next=		next_enter;

		if		yay	(a->dir_first==0)
		return	a->next		();
	}

	return				2;
}

__attribute__((noinline))
__attribute__((unused))
static	CALIGN	uint8_t	next_read_old	(void)
{	errna=				0;
	NODELISTDATA	*a=
	nodelistdata			(Gz.active.nodelist);
	LEVEL		*lp=		a->lp;
	struct dirent	*ent;

	again:
	ent=	readdir			(lp->dirp);

	if			nay	(ent==NULL)
	return	(a->next=next_above)	();

	if			nay	(ent->d_name[0]=='.')
	{	if		nay	(ent->d_name[1]==0)
		goto			again;
		if		yay	(ent->d_name[1]=='.')
		if		yay	(ent->d_name[2]==0)
		goto			again;
	}

	lp->ent=			ent;
/*	tacit_stat			(A,a);	*/
	tacit_stat			(a);
	lp->len=
	strlenb				(lp->ent->d_name);

	unsigned	char	type=	ent->d_type;

	if			nay	(type==DT_DIR)
	{	a->next=		next_enter;

		if		yay	(a->dir_first==0)
		return	a->next		();
	}

	return				2;
}

static	inline	unsigned char		mode_t_to_dt	(mode_t a)
{	switch				(a&S_IFMT)
	{	case	S_IFREG:	return	DT_REG;
		case	S_IFDIR:	return	DT_DIR;
		case	S_IFLNK:	return	DT_LNK;
		case	S_IFIFO:	return	DT_FIFO;
		case	S_IFCHR:	return	DT_CHR;
		case	S_IFBLK:	return	DT_BLK;
		case	S_IFSOCK:	return	DT_SOCK;
		default:		return	DT_UNKNOWN;
	}
}

SCV	tacit_stat		(NODELISTDATA *a)
{	LEVEL		*lp=	a->lp;
	unsigned char	t=	lp->ent->d_type;

	if		yay	(t!=DT_UNKNOWN)
	if		yay	(a->stat_buf==a->stat_back)
	return;

	int		e=
	fstatat			(dirfd(lp->dirp),
				       lp->ent->d_name,
				 a->stat_buf,
				 AT_SYMLINK_NOFOLLOW);

	if		nay	(t==DT_UNKNOWN)
	if		yay	(e==0)
	t=
	lp->ent->d_type=
	mode_t_to_dt		(a->stat_buf->st_mode);
}

SCV	nodelistwith		(void)
{	VMETA		*A=	Gz.active.nodelist;
	Gz.active.nodelist=	Gz.to[0];
	*Gz.at=			nodelistwith;
	argot_next		();
	Gz.active.nodelist=	A;
}

SCV	nodelist	(void)	{tvarnewab(nodelistsubnew,	nodelist);}
SCV	nodelistdeep	(void)	{tsubab(nodelistdeepsubnew,	nodelistdeep);}
SCV	nodelistfull	(void)	{tsubab(nodelistfullsubnew,	nodelistfull);}
SCV	nodelistlean	(void)	{tsubab(nodelistleansubnew,	nodelistlean);}
SCV	nodelistless	(void)	{tsubab(nodelistlesssubnew,	nodelistless);}
SCV	nodelistlink	(void)	{tsubab(nodelistlinksubnew,	nodelistlink);}
SCV	nodelistmost	(void)	{tsubab(nodelistmostsubnew,	nodelistmost);}
SCV	nodelistname	(void)	{tsubab(nodelistnamesubnew,	nodelistname);}
SCV	nodelistpath	(void)	{tsubab(nodelistpathsubnew,	nodelistpath);}
SCV	nodelisttype	(void)	{tsubab(nodelisttypesubnew,	nodelisttype);}

__attribute__((cold))
void	segv		(void)
{	if		(Gz.active.nodelist==NULL)
	warnx		("%s", "\nThe argot node list with was not invoked?\n");
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180924",
	.official=	"20180924",
	.update=	"20200807"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(nodelist,		"nodelist");
	aa		(nodeliststat,		"nodeliststat");
	aa		(nodelistdeep,		"nodelistdeep");
	aa		(nodelistfull,		"nodelistfull");
	aa		(nodelistlean,		"nodelistlean");
	aa		(nodelistless,		"nodelistless");
	aa		(nodelistlink,		"nodelistlink");
	aa		(nodelistmost,		"nodelistmost");
	aa		(nodelistname,		"nodelistname");
	aa		(nodelistpath,		"nodelistpath");
	aa		(nodelisttype,		"nodelisttype");
	aa		(nodelistwith,		"nodelistwith");
	aa		(nodelistsymlist,	"nodelistsymlist");
	aa		(nodelistdirhead,	"nodelistdirhead");
	aa		(nodelistdirtail,	"nodelistdirtail");
	aa		(nodelistdirskip,	"nodelistdirskip");
	aa		(nodelistdirdone,	"nodelistdirdone");
	aa		(nodelistnext,		"nodelistnext");
	aa		(nodelistpathname,	"nodelistpathname");
	aa_fini		();
};
