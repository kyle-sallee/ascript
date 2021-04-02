/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"trek.h"
#include	<sys/sysmacros.h>

/*
PALIGN
struct stat	yn[2];
*/

#define	yn	Gz.yn

typedef	struct
{	uint8_t		name	[0x10][LABEL_SIZE];
	uint16_t	index	[0x10];
}	NTP;

#define	nameset(a,b)	.name[a>>0xc]=b

CALIGN	static	NTP	ntp=
{	nameset		(S_IFSOCK,	"sock"),
	nameset		(S_IFLNK,	"link"),
	nameset		(S_IFREG,	"file"),
	nameset		(S_IFBLK,	"block"),
	nameset		(S_IFDIR,	"dir"),
	nameset		(S_IFCHR,	"char"),
	nameset		(S_IFIFO,	"sock"),
};

__attribute__((aligned(0x20)))
static		void	_yay	(void)
{	argot_next	();
}

static	inline	int	access_grant	(VMETA *A,int a)
{	return	faccessat		(AT_FDCWD,A->textaddr,a,AT_EACCESS);
}

/*
static	inline	int	stat_grant	(VMETA *A,struct stat *a)
{	fix_to_int			(A);
	if				(A->op->int_compat)
	return	fstat			(A->value.i,a);
	else
	return	stat			(A->textaddr,a);
}

static	inline	int	lstat_grant	(VMETA *A,struct stat *a)
{	return	lstat			(A->textaddr,a);
}
*/

/*
__attribute__((noinline))
static	CALIGN	nlink_t	link_grant	(VMETA *A)
{	struct	stat	a;
	a.st_nlink=			0;
	stat_grant			(A,&a);
	return				a.st_nlink;
}
*/

/*
__attribute__((noinline))
static	CALIGN	mode_t	mode_grant	(VMETA *A)
{	struct	stat	a;
	a.st_mode=			0;
	stat_grant			(A,&a);
	return				a.st_mode;
}
*/

/*
__attribute__((noinline))
static	CALIGN	mode_t	lmode_grant	(VMETA *A)
{	struct	stat	a;
	a.st_mode=			0;
	lstat_grant			(A,&a);
	return				a.st_mode;
}

__attribute__((noinline))
static	CALIGN	off_t	size_grant	(VMETA *A)
{	struct	stat	a;
	a.st_size=			0;
	stat_grant			(A,&a);
	return				a.st_size;
}

__attribute__((noinline))
static	CALIGN	gid_t	gid_grant	(VMETA *A)
{	struct	stat	a;
	a.st_gid=			-1;
	stat_grant			(A,&a);
	return				a.st_gid;
}

__attribute__((noinline))
static	CALIGN	uid_t	uid_grant	(VMETA *A)
{	struct	stat	a;
	a.st_uid=			-1;
	stat_grant			(A,&a);
	return				a.st_uid;
}
*/

__attribute__((noinline))
SCV	targetfstat_	(void)
{
/*	denwant		(	Gz.to[0]);	*/
	argot_jump	(fstat(	Gz.to[0]->value.i,yn+0)==0);
}

__attribute__((noinline))
SCV	originfstat_	(void)
{
/*	denwant		(	Gz.to[1]);	*/
	argot_jump	(fstat(	Gz.to[1]->value.i,yn+1)==0);
}

__attribute__((noinline))
SCV	targetlstat_	(void)
{	show		(	Gz.to[0]);
	argot_jump	(lstat(	Gz.to[0]->textaddr,yn+0)==0);
}

__attribute__((noinline))
SCV	originlstat_	(void)
{	show		(	Gz.to[1]);
	argot_jump	(lstat(	Gz.to[1]->textaddr,yn+1)==0);
}

__attribute__((noinline))
SCV	targetstat_	(void)
{	show		(	Gz.to[0]);
	argot_jump	(stat(	Gz.to[0]->textaddr,yn+0)==0);
}

__attribute__((noinline))
SCV	originstat_	(void)
{	show		(	Gz.to[1]);
	argot_jump	(stat(	Gz.to[1]->textaddr,yn+1)==0);
}

#define	NIA	__attribute__((noinline))	static	CALIGN	void


NIA	yayblock_	(void)	{argot_jump((yn[0].st_mode&S_IFMT)==S_IFBLK);}
NIA	yaychar_	(void)	{argot_jump((yn[0].st_mode&S_IFMT)==S_IFCHR);}
NIA	yaydir_		(void)	{argot_jump((yn[0].st_mode&S_IFMT)==S_IFDIR);}
NIA	yayfifo_	(void)	{argot_jump((yn[0].st_mode&S_IFMT)==S_IFIFO);}
NIA	yayfile_	(void)	{argot_jump((yn[0].st_mode&S_IFMT)==S_IFREG);}
NIA	yaysocket_	(void)	{argot_jump((yn[0].st_mode&S_IFMT)==S_IFSOCK);}
NIA	yaysymlink_	(void)	{argot_jump((yn[0].st_mode&S_IFMT)==S_IFLNK);}
NIA	yaysgid_	(void)	{argot_jump((yn[0].st_mode&S_ISGID)!=0);}
NIA	yaysuid_	(void)	{argot_jump((yn[0].st_mode&S_ISUID)!=0);}
NIA	yaysticky_	(void)	{argot_jump((yn[0].st_mode&S_ISVTX)!=0);}
NIA	yaygid_		(void)	{argot_jump(yn[0].st_gid ==yn[1].st_gid);}
NIA	yayuid_		(void)	{argot_jump(yn[0].st_uid ==yn[1].st_uid);}
NIA	yayempty_	(void)	{argot_jump(yn[0].st_size==0);}
NIA	yayexe_		(void)	{argot_jump(access_grant(Gz.to[0],X_OK)==0);}
NIA	yayread_	(void)	{argot_jump(access_grant(Gz.to[0],R_OK)==0);}
NIA	yaywrite_	(void)	{argot_jump(access_grant(Gz.to[0],W_OK)==0);}
NIA	yaynode_	(void)	{argot_jump(access_grant(Gz.to[0],F_OK)==0);}
NIA	yaylink_	(void)	{argot_jump(yn[0].st_nlink>1);}
NIA	yaysizeless_	(void)	{argot_jump(yn[0].st_size <yn[1].st_size);}
NIA	yaysizemore_	(void)	{argot_jump(yn[0].st_size >yn[1].st_size);}
NIA	yaysizesame_	(void)	{argot_jump(yn[0].st_size==yn[1].st_size);}

NIA	yaytty_			(void)
{
/*	denwant			(Gz.to[0]);	*/
	argot_jump		(isatty(Gz.to[0]->value.i));
}

NIA	yaymodified_		(void)
{	int		b=	(yn[0].st_mtim.tv_nsec> yn[0].st_atim.tv_nsec);
	b&=			(yn[0].st_mtim.tv_sec ==yn[0].st_atim.tv_sec);
	b|=			(yn[0].st_mtim.tv_sec > yn[0].st_atim.tv_sec);
	argot_jump		(b);
}

NIA	yaynewer_		(void)
{	int		b=	(yn[0].st_mtim.tv_nsec> yn[1].st_mtim.tv_nsec);
	b&=			(yn[0].st_mtim.tv_sec ==yn[1].st_mtim.tv_sec);
	b|=			(yn[0].st_mtim.tv_sec > yn[1].st_mtim.tv_sec);
	argot_jump		(b);
}

NIA	yayolder_		(void)
{	int		b=	(yn[0].st_mtim.tv_nsec< yn[1].st_mtim.tv_nsec);
	b&=			(yn[0].st_mtim.tv_sec ==yn[1].st_mtim.tv_sec);
	b|=			(yn[0].st_mtim.tv_sec < yn[1].st_mtim.tv_sec);
	argot_jump		(b);
}

NIA	yaysame_		(void)
{	argot_jump		(((yn[0].st_ino^yn[1].st_ino)|
				  (yn[0].st_dev^yn[1].st_dev))==0);
}

NIA	nayblock_	(void)	{argot_jump((yn[0].st_mode&S_IFMT)!=S_IFBLK);}
NIA	naychar_	(void)	{argot_jump((yn[0].st_mode&S_IFMT)!=S_IFCHR);}
NIA	naydir_		(void)	{argot_jump((yn[0].st_mode&S_IFMT)!=S_IFDIR);}
NIA	nayfifo_	(void)	{argot_jump((yn[0].st_mode&S_IFMT)!=S_IFIFO);}
NIA	nayfile_	(void)	{argot_jump((yn[0].st_mode&S_IFMT)!=S_IFREG);}
NIA	naysocket_	(void)	{argot_jump((yn[0].st_mode&S_IFMT)!=S_IFSOCK);}
NIA	naysymlink_	(void)	{argot_jump((yn[0].st_mode&S_IFMT)!=S_IFLNK);}
NIA	naysgid_	(void)	{argot_jump((yn[0].st_mode&S_ISGID)==0);}
NIA	naysuid_	(void)	{argot_jump((yn[0].st_mode&S_ISUID)==0);}
NIA	naysticky_	(void)	{argot_jump((yn[0].st_mode&S_ISVTX)==0);}
NIA	naygid_		(void)	{argot_jump(yn[0].st_gid !=yn[1].st_gid);}
NIA	nayuid_		(void)	{argot_jump(yn[0].st_uid !=yn[1].st_uid);}
NIA	nayempty_	(void)	{argot_jump(yn[0].st_size!=0);}
NIA	nayexe_		(void)	{argot_jump(access_grant(Gz.to[0],X_OK)!=0);}
NIA	nayread_	(void)	{argot_jump(access_grant(Gz.to[0],R_OK)!=0);}
NIA	naywrite_	(void)	{argot_jump(access_grant(Gz.to[0],W_OK)!=0);}
NIA	naynode_	(void)	{argot_jump(access_grant(Gz.to[0],F_OK)!=0);}
NIA	naylink_	(void)	{argot_jump(yn[0].st_nlink==1);}
NIA	naysizeless_	(void)	{argot_jump(yn[0].st_size>=yn[1].st_size);}
NIA	naysizemore_	(void)	{argot_jump(yn[0].st_size<=yn[1].st_size);}
NIA	naysizesame_	(void)	{argot_jump(yn[0].st_size!=yn[1].st_size);}

NIA	naytty_			(void)
{
/*	denwant			(Gz.to[0]);	*/
	argot_jump		(isatty(Gz.to[0]->value.i)==0);
}

NIA	naymodified_		(void)
{	int		b=	(yn[0].st_mtim.tv_nsec> yn[0].st_atim.tv_nsec);
	b&=			(yn[0].st_mtim.tv_sec ==yn[0].st_atim.tv_sec);
	b|=			(yn[0].st_mtim.tv_sec > yn[0].st_atim.tv_sec);
	argot_jump		(b==0);
}

NIA	naynewer_		(void)
{	int		b=	(yn[0].st_mtim.tv_nsec> yn[1].st_mtim.tv_nsec);
	b&=			(yn[0].st_mtim.tv_sec ==yn[1].st_mtim.tv_sec);
	b|=			(yn[0].st_mtim.tv_sec > yn[1].st_mtim.tv_sec);
	argot_jump		(b==0);
}

NIA	nayolder_		(void)
{	int		b=	(yn[0].st_mtim.tv_nsec< yn[1].st_mtim.tv_nsec);
	b&=			(yn[0].st_mtim.tv_sec ==yn[1].st_mtim.tv_sec);
	b|=			(yn[0].st_mtim.tv_sec < yn[1].st_mtim.tv_sec);
	argot_jump		(b==0);
}

NIA	naysame_		(void)
{	argot_jump		(((yn[0].st_ino^yn[1].st_ino)|
				  (yn[0].st_dev^yn[1].st_dev))!=0);
}

NIA	yayexekeep_		(void)
{	int		a=	Gz.to[0]->value.i;
	fcntl			(a,F_GETFD);
	a|=			O_CLOEXEC;
	argot_jump		(a!=0);
}

NIA	yayexegive_		(void)
{	int		a=	Gz.to[0]->value.i;
	fcntl			(a,F_GETFD);
	a|=			O_CLOEXEC;
	argot_jump		(a==0);
}

NIA	yayusewait_		(void)
{	int		a=	Gz.to[0]->value.i;
	fcntl			(a,F_GETFL);
	a|=			O_NONBLOCK;
	argot_jump		(a==0);
}

NIA	yayuserush_		(void)
{	int		a=	Gz.to[0]->value.i;
	fcntl			(a,F_GETFL);
	a|=			O_NONBLOCK;
	argot_jump		(a!=0);
}

NIA	nodetypepin_			(void)
{	mode_t		a=		yn[0].st_mode;
	a>>=				0xc;
	a&=				0xf;
	uint16_t	b=		ntp.index	[a];
	uint8_t	const	*c=		ntp.name	[a];

	void		(**A)	(void)=	Gz.at;

	Gz.at=
	nearfind_faster			(c,partfar(NULL),b);

	(*Gz.at)			();
	(*(Gz.at=A+1))			();
}

NIA	nodetypego_			(void)
{	mode_t		a=		yn[0].st_mode;
	a>>=				0xc;
	a&=				0xf;
	uint16_t	b=		ntp.index	[a];
	uint8_t	const	*c=		ntp.name	[a];

	Gz.at=
	nearfind_faster			(c,partfar(NULL),b);

	(*Gz.at)			();
}

static	void	yayblock	(void){(*Gz.at=yayblock_)	();}
static	void	yaychar		(void){(*Gz.at=yaychar_)	();}
static	void	yaydir		(void){(*Gz.at=yaydir_)		();}
static	void	yayfifo		(void){(*Gz.at=yayfifo_)	();}
static	void	yayfile		(void){(*Gz.at=yayfile_)	();}
static	void	yaysocket	(void){(*Gz.at=yaysocket_)	();}
static	void	yaysymlink	(void){(*Gz.at=yaysymlink_)	();}
static	void	yaytty		(void){(*Gz.at=yaytty_)		();}
static	void	yaysgid		(void){(*Gz.at=yaysgid_)	();}
static	void	yaysuid		(void){(*Gz.at=yaysuid_)	();}
static	void	yaysticky	(void){(*Gz.at=yaysticky_)	();}
static	void	yaygid		(void){(*Gz.at=yaygid_)		();}
static	void	yayuid		(void){(*Gz.at=yayuid_)		();}
static	void	yayempty	(void){(*Gz.at=yayempty_)	();}
static	void	yayexe		(void){(*Gz.at=yayexe_)		();}
static	void	yayread		(void){(*Gz.at=yayread_)	();}
static	void	yaywrite	(void){(*Gz.at=yaywrite_)	();}
static	void	yaynode		(void){(*Gz.at=yaynode_)	();}
static	void	yaylink		(void){(*Gz.at=yaylink_)	();}
static	void	yaymodified	(void){(*Gz.at=yaymodified_)	();}
static	void	yaynewer	(void){(*Gz.at=yaynewer_)	();}
static	void	yayolder	(void){(*Gz.at=yayolder_)	();}
static	void	yaysame		(void){(*Gz.at=yaysame_)	();}
static	void	yaysizeless	(void){(*Gz.at=yaysizeless_)	();}
static	void	yaysizemore	(void){(*Gz.at=yaysizemore_)	();}
static	void	yaysizesame	(void){(*Gz.at=yaysizesame_)	();}


static	void	nayblock	(void){(*Gz.at=nayblock_)	();}
static	void	naychar		(void){(*Gz.at=naychar_)	();}
static	void	naydir		(void){(*Gz.at=naydir_)		();}
static	void	nayfifo		(void){(*Gz.at=nayfifo_)	();}
static	void	nayfile		(void){(*Gz.at=nayfile_)	();}
static	void	naysocket	(void){(*Gz.at=naysocket_)	();}
static	void	naysymlink	(void){(*Gz.at=naysymlink_)	();}
static	void	naytty		(void){(*Gz.at=naytty_)		();}
static	void	naysgid		(void){(*Gz.at=naysgid_)	();}
static	void	naysuid		(void){(*Gz.at=naysuid_)	();}
static	void	naysticky	(void){(*Gz.at=naysticky_)	();}
static	void	naygid		(void){(*Gz.at=naygid_)		();}
static	void	nayuid		(void){(*Gz.at=nayuid_)		();}
static	void	nayempty	(void){(*Gz.at=nayempty_)	();}
static	void	nayexe		(void){(*Gz.at=nayexe_)		();}
static	void	nayread		(void){(*Gz.at=nayread_)	();}
static	void	naywrite	(void){(*Gz.at=naywrite_)	();}
static	void	naynode		(void){(*Gz.at=naynode_)	();}
static	void	naylink		(void){(*Gz.at=naylink_)	();}
static	void	naymodified	(void){(*Gz.at=naymodified_)	();}
static	void	naynewer	(void){(*Gz.at=naynewer_)	();}
static	void	nayolder	(void){(*Gz.at=nayolder_)	();}
static	void	naysame		(void){(*Gz.at=naysame_)	();}
static	void	naysizeless	(void){(*Gz.at=naysizeless_)	();}
static	void	naysizemore	(void){(*Gz.at=naysizemore_)	();}
static	void	naysizesame	(void){(*Gz.at=naysizesame_)	();}

static	void	yayexekeep	(void){(*Gz.at=yayexekeep_)	();}
static	void	yayexegive	(void){(*Gz.at=yayexegive_)	();}
static	void	yayusewait	(void){(*Gz.at=yayusewait_)	();}
static	void	yayuserush	(void){(*Gz.at=yayuserush_)	();}

static	void	nodetypepin	(void){(*Gz.at=nodetypepin_)	();}
static	void	nodetypego	(void){(*Gz.at=nodetypego_)	();}
static	void	targetfstat	(void){(*Gz.at=targetfstat_)	();}
static	void	targetlstat	(void){(*Gz.at=targetlstat_)	();}
static	void	targetstat	(void){(*Gz.at=targetstat_)	();}
static	void	originfstat	(void){(*Gz.at=originfstat_)	();}
static	void	originlstat	(void){(*Gz.at=originlstat_)	();}
static	void	originstat	(void){(*Gz.at=originstat_)	();}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20190814",
	.official=	"20190814",
	.update=	"20200730"
};

typedef	struct
{	uint8_t		name	[LABEL_SIZE];
}	FIT;

#define	indexset(a,b)	\
	ntp.index[a>>0xc]=	bit128_to_bit16((FIT const){.name=b}.name)

__attribute__((always_inline))
static	inline	void	ntp_init	(void)
{	indexset	(S_IFSOCK,	"sock");
	indexset	(S_IFLNK,	"link");
	indexset	(S_IFREG,	"file");
	indexset	(S_IFBLK,	"block");
	indexset	(S_IFDIR,	"dir");
	indexset	(S_IFCHR,	"char");
	indexset	(S_IFIFO,	"sock");
}

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(_yay,		"yay");
	aa		(yayexegive,	"yayexegive");
	aa		(yayexekeep,	"yayexekeep");
	aa		(yayusewait,	"yayusewait");
	aa		(yayuserush,	"yayuserush");
	aa		(yayblock,	"yayblock");
	aa		(yaychar,	"yaychar");
	aa		(yaydir,	"yaydir");
	aa		(yayfifo,	"yayfifo");
	aa		(yayfile,	"yayfile");
	aa		(yaysocket,	"yaysocket");
	aa		(yaysymlink,	"yaysymlink");
	aa		(yaygid,	"yaygid");
	aa		(yayuid,	"yayuid");
	aa		(yayempty,	"yayempty");
	aa		(yayexe,	"yayexe");
	aa		(yayread,	"yayread");
	aa		(yaywrite,	"yaywrite");
	aa		(yaylink,	"yaylink");
	aa		(yaymodified,	"yaymodified");
	aa		(yaynewer,	"yaynewer");
	aa		(yaynode,	"yaynode");
	aa		(yayolder,	"yayolder");
	aa		(yaysgid,	"yaysgid");
	aa		(yaysticky,	"yaysticky");
	aa		(yaysuid,	"yaysuid");
	aa		(yaysame,	"yaysame");
	aa		(yaytty,	"yaytty");
	aa		(yaysizeless,	"yaysizeless");
	aa		(yaysizemore,	"yaysizemore");
	aa		(yaysizesame,	"yaysizesame");
	aa		(nayblock,	"nayblock");
	aa		(naychar,	"naychar");
	aa		(naydir,	"naydir");
	aa		(nayfifo,	"nayfifo");
	aa		(nayfile,	"nayfile");
	aa		(naysocket,	"naysocket");
	aa		(naysymlink,	"naysymlink");
	aa		(naygid,	"naygid");
	aa		(nayuid,	"nayuid");
	aa		(nayempty,	"nayempty");
	aa		(nayexe,	"nayexe");
	aa		(nayread,	"nayread");
	aa		(naywrite,	"naywrite");
	aa		(naylink,	"naylink");
	aa		(naymodified,	"naymodified");
	aa		(naynewer,	"naynewer");
	aa		(naynode,	"naynode");
	aa		(nayolder,	"nayolder");
	aa		(naysgid,	"naysgid");
	aa		(naysticky,	"naysticky");
	aa		(naysuid,	"naysuid");
	aa		(naysame,	"naysame");
	aa		(naytty,	"naytty");
	aa		(naysizeless,	"naysizeless");
	aa		(naysizemore,	"naysizemore");
	aa		(naysizesame,	"naysizesame");
	aa		(nodetypepin,	"nodetypepin");
	aa		(nodetypego,	"nodetypego");
	aa		(targetfstat,	"targetfstat");
	aa		(targetlstat,	"targetlstat");
	aa		(targetstat,	"targetstat");
	aa		(originfstat,	"originfstat");
	aa		(originlstat,	"originlstat");
	aa		(originstat,	"originstat");
	aa_fini		();
	ntp_init	();
};
