/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"int.h"
#include	"node.h"

/* for copying extended attributes */
#include	<e2p/e2p.h>
#include	<sys/ioctl.h>
#include	<sys/syscall.h>

#include	<libgen.h>
#include	<limits.h>

#include	<dirent.h>
#include	<sys/types.h>

static	PALIGN	NODEGLOBAL	ng;

static	CALIGN	int	file		(void);
static	CALIGN	int	file_direct	(void);
static	CALIGN	int	sym		(void);

__attribute__((noinline))
SCV	nodecopy_			(void)
{	show				(ng.at.target);
	show				(ng.at.origin);

	ng.d[1]=
	lstat				(ng.at.origin->textaddr,ng.b+1);

	if			nay	(ng.d[1]!=0)
	goto				fail;

	ng.d[0]=
	lstat				(ng.at.target->textaddr,ng.b+0);
	if			nay	(ng.d[0]==0)
	switch				(ng.b[0].st_mode&S_IFMT)
	{	case	S_IFDIR:
		if		yay	((ng.b[1].st_mode&S_IFMT)==S_IFDIR)
		{	fine:
			argot_skip	();
			return;
		}
		else
		{	errna=		EEXIST;
			fail:
			argot_next	();
			return;
		}
		case	S_IFLNK:
		if		nay	((ng.b[1].st_mode&S_IFMT)==S_IFDIR)
		{	stat		(ng.at.target->textaddr,ng.b);
			if	yay	((ng.b[0].st_mode&S_IFMT)==S_IFDIR)
			goto		fine;
		}
		default:	unlink	(ng.at.target->textaddr);
	}

	uint8_t		*b=		ng.at.target->textaddr;
	struct	stat	*c=		ng.b+1;
	errna=				0;
	int		a;
	switch				(ng.b[1].st_mode&S_IFMT)
	{
		case	S_IFREG:	a=file		();	break;
/*		case	S_IFREG:	a=file_direct	();	break;	*/
		case	S_IFLNK:	a=sym	();		break;
		case	S_IFDIR:	a=mkdir	(b,c->st_mode);	break;
		case	S_IFBLK:
		case	S_IFCHR:	a=mknod	(b,c->st_mode,
						   c->st_rdev);	break;
		case	S_IFIFO:	a=mkfifo(b,c->st_mode);	break;
		default:		a=	0;
	}
	argot_jump			(a==0);
}

static	CALIGN	int	lnk		(void);

__attribute__((noinline))
SCV	nodecopylink_			(void)
{	show				(ng.at.target);
	show				(ng.at.origin);

	ng.d[1]=
	lstat				(ng.at.origin->textaddr,ng.b+1);

	if			nay	(ng.d[1]!=0)
	goto				fail;

	ng.d[0]=
	lstat				(ng.at.target->textaddr,ng.b+0);
	if			nay	(ng.d[0]==0)
	switch				(ng.b[0].st_mode&S_IFMT)
	{	case	S_IFDIR:
		if		yay	((ng.b[1].st_mode&S_IFMT)==S_IFDIR)
		{	fine:
			argot_skip	();
			return;
		}
		else
		{	errna=		EEXIST;
			fail:
			argot_next	();
			return;
		}
		case	S_IFLNK:
		if		nay	((ng.b[1].st_mode&S_IFMT)==S_IFDIR)
		{	stat		(ng.at.target->textaddr,ng.b);
			if	yay	((ng.b[0].st_mode&S_IFMT)==S_IFDIR)
			goto		fine;
		}
		default:	unlink	(ng.at.target->textaddr);
	}

	uint8_t		*b=		ng.at.target->textaddr;
	struct	stat	*c=		ng.b+1;

	errna=				0;
	int		a;
	switch				(ng.b[1].st_mode&S_IFMT)
	{	case	S_IFREG:	if	yay	(ng.b[1].st_nlink==1)
					a=file		();
/*					a=file_direct	();	*/
					else
					a=lnk	();		break;
		case	S_IFLNK:	a=sym	();		break;
		case	S_IFDIR:	a=mkdir	(b,c->st_mode);	break;
		case	S_IFBLK:
		case	S_IFCHR:	a=mknod	(b,c->st_mode,
						   c->st_rdev);	break;
		case	S_IFIFO:	a=mkfifo(b,c->st_mode);	break;
		default:		a=	0;
	}
	argot_jump			(a==0);
}

__attribute__((noinline))
SCV	nodemove_		(void)
{	show			(ng.at.target);
	show			(ng.at.origin);

	int		a=
	rename			(ng.at.origin->textaddr,
				 ng.at.target->textaddr);

	argot_jump		(a==0);
}

__attribute__((noinline))
SCV	nodelink_		(void)
{	show			(ng.at.target);
	show			(ng.at.origin);

	int		a=
	link			(ng.at.origin->textaddr,
				 ng.at.target->textaddr);

	argot_jump		(a==0);
}

__attribute__((noinline))
SCV	nodesymlink_		(void)
{	show			(ng.at.object);
	show			(ng.at.target);

	int		a=
	symlink			(ng.at.target->textaddr,
				 ng.at.object->textaddr);

	argot_jump		(a==0);
}

static	CALIGN	int	content_differ	(void);
static	CALIGN	int	object_differ	(void);

__attribute__((noinline))
SCV	nodesame_			(void)
{	show				(ng.at.target);
	show				(ng.at.origin);

	ng.d[1]=
	stat				(ng.at.origin->textaddr,ng.b+1);

	ng.d[0]=
	stat				(ng.at.target->textaddr,ng.b+0);

	if			nay	(ng.d[0]|ng.d[1])
	goto				fail;

	if			nay	(ng.b[0].st_ino==ng.b[1].st_ino)
	if			nay	(ng.b[0].st_dev==ng.b[1].st_dev)
	goto				pass;

	if			nay	((ng.b[0].st_mode^
					  ng.b[1].st_mode)&S_IFMT)
	goto				fail;

/*	if			nay	(ng.b[0].uid^ng.b[1].uid)
	goto				fail;

	if			nay	(ng.b[0].gid^ng.b[1].gid)
	goto				fail;
*/

	switch				(ng.b[0].st_mode&S_IFMT)
	{	case	S_IFCHR:
		case	S_IFBLK:
		if			(ng.b[0].st_rdev!=
					 ng.b[1].st_rdev)
		goto			fail;
		break;

		case	S_IFLNK:
		if		nay	(object_differ())
		goto			fail;
		break;

		case	S_IFREG:
		if		nay	( ng.b[0].st_size!=
					  ng.b[1].st_size)
		goto			fail;

		if		nay	(content_differ())
		goto			fail;
	}

	pass:
	argot_skip			();
	return;

	fail:
	argot_next			();
}

static	inline	int	ifchown	(char const *a,uid_t b,gid_t c)
{	if		((b!=-1)||(c!=-1))
	return	chown	(a,b,c);
}

static	inline	int	ifchmod	(char const *a,mode_t b)
{	if		(b!=-1)
	return	chmod	(a,b);
}

__attribute__((noinline))
SCV	nodeblock_		(void)
{
/*	hexdenwant		(ng.at.rmajor);
	hexdenwant		(ng.at.rminor);
	octwant			(ng.at.mode);
	denwant			(ng.at.uid);
	denwant			(ng.at.gid);
*/
	show			(ng.at.target);
	uint8_t		*b=	ng.at.target->textaddr;
	int		c=
	mknod			(b,S_IFBLK|0660,
	makedev			(           ng.at.rmajor->value.i,ng.at.rminor->value.i));
	chown			(b,-1,      ng.at.rmajor->value.i);
	ifchown			(b,ng.at.uid->value.i,ng.at.gid->value.i);
	ifchmod			(b,ng.at.mode->value.i);
	argot_jump		(c==0);
}

__attribute__((noinline))
SCV	nodechar_		(void)
{
/*	hexdenwant		(ng.at.rmajor);
	hexdenwant		(ng.at.rminor);
	octwant			(ng.at.mode);
	denwant			(ng.at.uid);
	denwant			(ng.at.gid);
*/
	show			(ng.at.target);
	uint8_t		*b=	ng.at.target->textaddr;
	int		c=
	mknod			(b,S_IFCHR|0660,
	makedev			(           ng.at.rmajor->value.i,ng.at.rminor->value.i));
	chown			(b,-1,      ng.at.rmajor->value.i);
	ifchown			(b,ng.at.uid->value.i,ng.at.gid->value.i);
	ifchmod			(b,ng.at.mode->value.i);
	argot_jump		(c==0);
}

__attribute__((noinline))
SCV	nodedel_		(void)
{	show			(ng.at.target);
	int		a=
	remove			(ng.at.target->textaddr);
	argot_jump		(a==0);
}

static	inline	int	pathmake	(VMETA *);

__attribute__((noinline))
SCV	nodepath_		(void)
{	show			(ng.at.target);
	int		a=
	pathmake		(ng.at.target);
	argot_jump		(a==0);
}

__attribute__((noinline))
SCV	nodefile_		(void)
{
/*	octwant			(ng.at.mode);
	denwant			(ng.at.uid);
	denwant			(ng.at.gid);
*/
	show			(ng.at.target);
	uint8_t		*b=	ng.at.target->textaddr;
	int		c=
	mknod			(b,0666|S_IFREG,0);
	ifchown			(b,ng.at.uid->value.i,ng.at.gid->value.i);
	ifchmod			(b,ng.at.mode->value.i);
	argot_jump		(c==0);
}

__attribute__((noinline))
SCV	nodefifo_		(void)
{
/*	octwant			(ng.at.mode);
	denwant			(ng.at.uid);
	denwant			(ng.at.gid);
*/
	show			(ng.at.target);
	uint8_t		*b=	ng.at.target->textaddr;
	int		c=
	mkfifo			(b,0666);
	ifchown			(b,ng.at.uid->value.i,ng.at.gid->value.i);
	ifchmod			(b,ng.at.mode->value.i);
	argot_jump		(c==0);
}

__attribute__((noinline))
SCV	nodedir_		(void)
{
/*	octwant			(ng.at.mode);
	denwant			(ng.at.uid);
	denwant			(ng.at.gid);
*/
	show			(ng.at.target);
	uint8_t		*b=	ng.at.target->textaddr;

	int		c=
	mkdir			(b,0777);
	ifchown			(b,ng.at.uid->value.i,ng.at.gid->value.i);
	ifchmod			(b,ng.at.mode->value.i);
	argot_jump		(c==0);
}

__attribute__((always_inline))
static	inline	int	pathmake	(VMETA *A)
{
/*	denwant				(ng.at.gid);
	octwant				(ng.at.mode);
	denwant				(ng.at.uid);
*/

	uint8_t		*a=		ng.at.target->textaddr;
	int		b=		ng.at.target->textlen;
	uint8_t		*c=		a+b-1;
	for				(;yay(c>a) && yay(*c!='/');c--);

	uint8_t		*d=		a+1;
	int		e;

	for				(;yay(c>=d) && nay(*d=='/');d++);

	for				(;yay(c>=d);d++)
	{	for			(;nay(*d!='/');d++);
		*d=			0;
		e=
		stat			(a,ng.b);
		*d=			'/';
		if		yay	(e==0)
		if		yay	((ng.b[0].st_mode&S_IFMT)==S_IFDIR)
		continue;
		*d=			0;
		e=
		mkdir			(a,0777);
		ifchown			(a,ng.at.uid ->value.i
					  ,ng.at.gid ->value.i);
		ifchmod			(a,ng.at.mode->value.i);
		*d=			'/';
		if		nay	(e!=0)
		return			1;
	}
	return				0;
}

#define		FPP	MAP_FIXED|MAP_POPULATE|MAP_PRIVATE

SCV	cache_trim			(size_t a)
{	ng.c[0].value.i+=		a;
	ng.c[1].value.i=		a;
	ng.c[2].value.i+=		a;

	if		nay		(ng.c[2].value.i>=ng.c[3].value.i)
	{	ng.c[2].value.i=	0;
		int	b=		errna;
		int	c=
		open			("/proc/sys/vm/drop_caches",O_WRONLY);
		write			(c,"3\n",2);
		close			(c);
		errna=			b;
	}
}

static	CALIGN	int	content_differ	(void)
{	int		A=
	open				(ng.at.target->textaddr,
					 O_NOATIME|O_RDONLY);

	if			nay	(0>A)
	return				1;

	int		B=
	open				(ng.at.origin->textaddr,
					 O_NOATIME|O_RDONLY);
	if			nay	(0>B)
	{	close			(A);
		return			1;
	}

	off_t		C=		ng.b[0].st_size;
	off_t		D=		0;
	off_t		E;
	int		a;

	while			(1)
	{	E=		C;
		if		(E>HUGE)
		E=		   HUGE;
		mmap		(ng.same     ,E,PROT_READ,FPP,A,D);
		mmap		(ng.same+HUGE,E,PROT_READ,FPP,B,D);

		a=	memcmp	(ng.same,ng.same+HUGE,E);

		C-=		E;
		D+=		E;
		if	nay	(a!=0)	break;
		if	nay	(C==0)	break;
	}

/*	ng.c[0].value.i+=		2*(ng.b[0].st_size-C);	*/
	cache_trim			(2*(ng.b[0].st_size-C));

	madvise				(ng.same,HUGE*2,MADV_DONTNEED);
	close				(A);
	close				(B);
	return				a;
}

static	CALIGN	int	object_differ	(void)
{	ssize_t		a=
	readlink			(ng.at.object->textaddr,ng.a,PAGE);

	ssize_t		b=
	readlink			(ng.at.target->textaddr,ng.a+PAGE,PAGE);

	if			nay	(a!=b)
	return				1;

	return
	memcmp				(ng.a,ng.a+PAGE,b);
}

__attribute__((unused))
static	CALIGN	int	file		(void)
{	int		A=
	open				(ng.at.target->textaddr,
					O_CREAT|O_NOATIME|O_WRONLY,0200);
	if			nay	(0>A)
	return				1;

	int		B=
	open				(ng.at.origin->textaddr,
					 O_NOATIME|O_RDONLY);
	if			nay	(0>B)
	{	close			(A);
		return			1;
	}

	off_t		C=		ng.b[1].st_size;

	posix_fadvise			(B,0,0,POSIX_FADV_WILLNEED);
	posix_fallocate			(A,0,C);

	size_t		D=
	copyall				(A,B);
	ftruncate			(A,C);

	if			yay	(D>0)
	{
/*		ng.c[1].value.i=	D;
		ng.c[0].value.i+=	D*2;	*/
		cache_trim		(D*2);
	}

	close				(A);
	close				(B);

	if				(C==D)
	return				0;
	else
	return				1;
}

__attribute__((unused))
static	CALIGN	int	file_direct	(void)
{	int		A=
	open				(ng.at.target->textaddr,
					O_CREAT|O_DIRECT|O_NOATIME|O_WRONLY,0200);
	if			nay	(0>A)
	return				1;

	int		B=
	open				(ng.at.origin->textaddr,
					 O_DIRECT|O_NOATIME|O_RDONLY);
	if			nay	(0>B)
	{	close			(A);
		return			1;
	}

	off_t		C=		ng.b[1].st_size;

/*	posix_fallocate			(A,0,C);
*/

	size_t		D=
	copy_direct			(A,B);

	if			yay	(D>0)
	{
/*		ng.c[1].value.i=	D;
		ng.c[0].value.i+=	D*2;	*/
		cache_trim		(D*2);
	}

	close				(A);
	close				(B);

	if				(C==D)
	return				0;
	else
	return				1;
}

__attribute__((noinline))
static	CALIGN	int	lnk		(void)
{	dev_t		d=		ng.b[1].st_dev;
	ino_t		i=		ng.b[1].st_ino;

	LINK		*a=		(LINK *)	ng.link_addr;
	while				(1)
	{	if		nay	(a->ino==i)
		if		yay	(a->dev==d)
		return	link		(a->name,ng.at.target->textaddr);
		if		nay	(a->ino==0)
		if		yay	(a->dev==0)
		break;
		a++;
	}

	a->ino=				i;
	a->dev=				d;
	a->name=			ng.text_next;
	 ng.text_next+=			ng.at.target->textlen;
	*ng.text_next++=		0;

	ascript_memcpy			(a->name,
					 ng.at.target->textaddr,
					 ng.at.target->textlen);

	size_t		t=		ng.text_next-ng.text_addr;

	if			nay	(PAGE>(ng.text_size-t))
	{	size_t	a=		ng.text_size;
		ng.text_size=		a+HUGE;

		ng.text_addr=
		mremap			(ng.text_addr,a,
					 ng.text_size,MREMAP_MAYMOVE);
		ng.text_next=		ng.text_addr+t;
	}

	t=				(void *)	a-
					(void *)	ng.link_addr;

	if			nay	((ng.link_size-t)==0)
	{	size_t		a=	ng.link_size;
		ng.link_size=		a+
		sizeof			(LINK)*0x400;

		ng.link_addr=
		mremap			(ng.link_addr,a,
					 ng.link_size,MREMAP_MAYMOVE);
	}

	return
	file				();
/*	file_direct			();	*/
}

static	CALIGN	int	sym		(void)
{	ssize_t		a=
	readlink			(ng.at.origin->textaddr,ng.a,PAGE);

	if			nay	(0>a)
	return				1;

	ng.a[a]=			0;
	return
	symlink				(ng.a,ng.at.target->textaddr);
}

__attribute__((noinline))
SCV	nodecopyuid_		(void)
{	show			(ng.at.target);
	show			(ng.at.origin);

	int		a=
	lstat			(ng.at.origin->textaddr,ng.b+1);

	if		yay	(a==0)
	a=
	chown			(ng.at.target->textaddr,ng.b[1].st_uid,-1);
	argot_jump		(a==0);
}

__attribute__((noinline))
SCV	nodecopygid_		(void)
{	show			(ng.at.target);
	show			(ng.at.origin);

	int		a=
	lstat			(ng.at.origin->textaddr,ng.b+1);

	if		yay	(a==0)
	a=
	chown			(ng.at.target->textaddr,-1,ng.b[1].st_gid);
	argot_jump		(a==0);
}

__attribute__((noinline))
SCV	nodecopymode_		(void)
{	show			(ng.at.target);
	show			(ng.at.origin);

	int		a=
	lstat			(ng.at.origin->textaddr,ng.b+1);

	if		yay	(a==0)
	a=
	chmod			(ng.at.target->textaddr,ng.b[1].st_mode);
	argot_jump		(a==0);
}

__attribute__((noinline))
SCV	nodecopytime_		(void)
{	show			(ng.at.target);
	show			(ng.at.origin);

	int		a=
	lstat			(ng.at.origin->textaddr,ng.b+1);


	if		yay	(a==0)
	a=
	utimensat		(AT_FDCWD,
				 ng.at.target->textaddr,
				 &ng.b[1].st_atim,
				 AT_SYMLINK_NOFOLLOW);
	argot_jump		(a==0);
}

static	CALIGN	int	xattrcopy	(void);

__attribute__((noinline))
SCV	nodecopyxattr_		(void)
{	show			(ng.at.target);
	show			(ng.at.origin);

	int		a=
	lstat			(ng.at.origin->textaddr,ng.b+1);


	if		yay	(a==0)
	a=
	xattrcopy		();
	argot_jump		(a==0);
}


#define	XAT	O_NOATIME|O_RDONLY|O_NOCTTY|O_NONBLOCK

__attribute__((noinline))
static	CALIGN	int	xattrcopy	(void)
{	int		a=	open	(ng.at.target->textaddr,XAT);

	if			nay	(0>a)
	return				1;

	int		b=	open	(ng.at.origin->textaddr,XAT);
	if			nay	(0>b)
	{	close			(a);
		return			1;
	}

	ssize_t	list_size=	syscall	(__NR_flistxattr,b,NULL,0);

	char	list			[list_size];
	char	*listp=			list;
	syscall				(__NR_flistxattr,b,list,list_size);
	char	*listend=		list+list_size;
	while				(listend>listp)
	{	ssize_t
		val_size=
		syscall			(__NR_fgetxattr,b,listp,NULL,0);
		char	val		[val_size];
		syscall			(__NR_fgetxattr,b,listp,val,val_size);
		syscall			(__NR_fsetxattr,a,listp,val,val_size,0);
		listp+=
		strlenb			(listp)+1;
	}
	return				0;
}

static	CALIGN	int	attrcopy	(void);

__attribute__((noinline))
SCV	nodecopyattr_		(void)
{	show			(ng.at.target);
	show			(ng.at.origin);

	int		a=
	lstat			(ng.at.origin->textaddr,ng.b+1);


	if		yay	(a==0)
	a=
	attrcopy		();
	argot_jump		(a==0);
}

#define	XAT	O_NOATIME|O_RDONLY|O_NOCTTY|O_NONBLOCK

__attribute__((noinline))
static	CALIGN	int	attrcopy	(void)
{	int		a=	open	(ng.at.target->textaddr,XAT);

	if			nay	(0>a)
	return				1;

	int		b=	open	(ng.at.origin->textaddr,XAT);
	if			nay	(0>b)
	{	close			(a);
		return			1;
	}

	long	L;
	ioctl				(b,EXT2_IOC_GETFLAGS,&L);
	ioctl				(a,EXT2_IOC_SETFLAGS,&L);
	return				0;
}

SCV	nodecopylinkfree	(void)
{	madvise			(ng.link_addr,ng.link_size,MADV_DONTNEED);
	madvise			(ng.text_addr,ng.text_size,MADV_DONTNEED);

	size_t		a=
	sizeof			(ng.link_init),
			b=	 ng.link_size;

	if		nay	(a!=b)
	{	ng.link_size=	a;
		ng.link_addr=
		mremap		(ng.link_addr,b,a,MREMAP_MAYMOVE);
	}

	a=
	sizeof			(ng.text_init);
	b=			 ng.text_size;

	if		nay	(a!=b)
	{	ng.text_size=	a;
		ng.text_next=
		ng.text_addr=
		mremap		(ng.text_addr,b,a,MREMAP_MAYMOVE);
	}

	*Gz.at=		nodecopylinkfree;
	argot_next		();
}

SCV	nodegid_		(void)
{
/*	denwant			(ng.at.gid);
*/
	gid_t		a=	ng.at.gid->value.i;
	int		b;

	VMETA		*A=	ng.at.target;
	if		yay	(A->op->int_compat)
	b=	fchown		(A->value.i,-1,a);
	else
	{	show		(A);
		b=	chown	(A->textaddr,-1,a);
	}
	argot_jump		(b==0);
}

SCV	nodeuid_		(void)
{
/*	denwant			(ng.at.uid);
*/
	gid_t		a=	ng.at.uid->value.i;
	int		b;

	VMETA		*A=	ng.at.target;
	if		yay	(A->op->int_compat)
	b=	fchown		(A->value.i,a,-1);
	else
	{	show		(A);
		b=	chown	(A->textaddr,a,-1);
	}
	argot_jump		(b==0);
}

SCV	nodemode_		(void)
{
/*	octwant			(ng.at.mode);
*/
	mode_t		a=	ng.at.mode->value.i;
	int		b;

	VMETA		*A=	ng.at.target;
	if		yay	(A->op->int_compat)
	b=	fchmod		(A->value.i,a);
	else
	{	show		(A);
		b=	chmod	(A->textaddr,a);
	}
	argot_jump		(b==0);
}

SCV	node_			(void)
{	volatile	/* stack backed force */
	NODEAT		at=	ng.at;
	ng.at.dub=
	ng.at.gid=
	ng.at.mode=
	ng.at.rmajor=
	ng.at.rminor=
	ng.at.uid=		ng.g;
	ng.at.object=
	ng.at.origin=
	ng.at.target=		NULL;
	argot_next		();
	ng.at=			at;
}

SCV			node	(void)
{	(*Gz.at=	node_)	();
}

__attribute__((cold))
static		void	nodecopy	(void)
{	(*Gz.at=	nodecopy_)	();
}

__attribute__((cold))
static		void	nodecopylink	(void)
{	(*Gz.at=	nodecopylink_)	();
}

__attribute__((cold))
static		void	nodecopyuid	(void)
{	(*Gz.at=	nodecopyuid_)	();
}

__attribute__((cold))
static		void	nodecopygid	(void)
{	(*Gz.at=	nodecopygid_)	();
}

__attribute__((cold))
static		void	nodecopymode	(void)
{	(*Gz.at=	nodecopymode_)	();
}

__attribute__((cold))
static		void	nodecopytime	(void)
{	(*Gz.at=	nodecopytime_)	();
}

__attribute__((cold))
static		void	nodecopyxattr	(void)
{	(*Gz.at=	nodecopyxattr_)	();
}

__attribute__((cold))
static		void	nodecopyattr	(void)
{	(*Gz.at=	nodecopyattr_)	();
}

__attribute__((cold))
static		void	nodeblock	(void)
{	(*Gz.at=	nodeblock_)	();
}

__attribute__((cold))
static		void	nodechar	(void)
{	(*Gz.at=	nodechar_)	();
}

__attribute__((cold))
static		void	nodedel		(void)
{	(*Gz.at=	nodedel_)	();
}

__attribute__((cold))
static		void	nodedir		(void)
{	(*Gz.at=	nodedir_)	();
}

__attribute__((cold))
static		void	nodefifo	(void)
{	(*Gz.at=	nodefifo_)	();
}

__attribute__((cold))
static		void	nodefile	(void)
{	(*Gz.at=	nodefile_)	();
}

__attribute__((cold))
static		void	nodegid		(void)
{	(*Gz.at=	nodegid_)	();
}

__attribute__((cold))
static		void	nodemode	(void)
{	(*Gz.at=	nodemode_)	();
}

__attribute__((cold))
static		void	nodemove	(void)
{	(*Gz.at=	nodemove_)	();
}

__attribute__((cold))
static		void	nodelink	(void)
{	(*Gz.at=	nodelink_)	();
}

__attribute__((cold))
static		void	nodepath	(void)
{	(*Gz.at=	nodepath_)	();
}

__attribute__((cold))
static		void	nodesame	(void)
{	(*Gz.at=	nodesame_)	();
}

__attribute__((cold))
static		void	nodesymlink	(void)
{	(*Gz.at=	nodesymlink_)	();
}

__attribute__((cold))
static		void	nodeuid		(void)
{	(*Gz.at=	nodeuid_)	();
}

__attribute__((always_inline))
static	inline	void	pushset	(VMETA **A)
{	VMETA		*B=	*A;
	*A=			Gz.to[0];
	argot_next		();
	*A=			B;
}

__attribute__((always_inline))
static	inline	void	justset	(VMETA **A)
{	*A=			Gz.to[0];
	argot_next		();
}

SCV	nodegidat_	(void)	{justset(&ng.at.gid);}
SCV	nodemodeat_	(void)	{justset(&ng.at.mode);}
SCV	nodeobjectat_	(void)	{justset(&ng.at.object);}
SCV	nodeoriginat_	(void)	{justset(&ng.at.origin);}
SCV	nodermajorat_	(void)	{justset(&ng.at.rmajor);}
SCV	noderminorat_	(void)	{justset(&ng.at.rminor);}
SCV	nodetargetat_	(void)	{justset(&ng.at.target);}
SCV	nodeuidat_	(void)	{justset(&ng.at.uid);}

SCV	nodegidat	(void)	{(*Gz.at=nodegidat_)();}
SCV	nodemodeat	(void)	{(*Gz.at=nodemodeat_)();}
SCV	nodeobjectat	(void)	{(*Gz.at=nodeobjectat_)();}
SCV	nodeoriginat	(void)	{(*Gz.at=nodeoriginat_)();}
SCV	nodermajorat	(void)	{(*Gz.at=nodermajorat_)();}
SCV	noderminorat	(void)	{(*Gz.at=noderminorat_)();}
SCV	nodetargetat	(void)	{(*Gz.at=nodetargetat_)();}
SCV	nodeuidat	(void)	{(*Gz.at=nodeuidat_)();}

__attribute__((cold))
		void	segv	(void)
{	if		(ng.at.target==NULL)
	warnx		("%s","\nThe target pathname is missing?\n");
	if		(ng.at.origin==NULL)
	warnx		("%s","\nThe origin pathname is missing?\n");
	if		(ng.at.object==NULL)
	warnx		("%s","\nThe object          is missing?\n");
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180924",
	.official=	"20180924",
	.update=	"20200814"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(node,			"node");

	aa		(nodegidat,		"nodegidat");
	aa		(nodemodeat,		"nodemodeat");
	aa		(nodeobjectat,		"nodeobjectat");
	aa		(nodeoriginat,		"nodeoriginat");
	aa		(nodermajorat,		"nodermajorat");
	aa		(noderminorat,		"noderminorat");
	aa		(nodetargetat,		"nodetargetat");
	aa		(nodeuidat,		"nodeuidat");

	aa		(nodecopylinkfree,	"nodecopylinkfree");
	aa		(nodecopyxattr,		"nodecopyxattr");
	aa		(nodecopyattr,		"nodecopyattr");
	aa		(nodecopytime,		"nodecopytime");
	aa		(nodecopymode,		"nodecopymode");
	aa		(nodecopygid,		"nodecopygid");
	aa		(nodecopyuid,		"nodecopyuid");
	aa		(nodelink,		"nodelink");
	aa		(nodesymlink,		"nodesymlink");
	aa		(nodecopy,		"nodecopy");
	aa		(nodecopylink,		"nodecopylink");
	aa		(nodeblock,		"nodeblock");
	aa		(nodechar,		"nodechar");
	aa		(nodedel,		"nodedel");
	aa		(nodegid,		"nodegid");
	aa		(nodepath,		"nodepath");
	aa		(nodefifo,		"nodefifo");
	aa		(nodedir,		"nodedir");
	aa		(nodefile,		"nodefile");
	aa		(nodesame,		"nodesame");
	aa		(nodemode,		"nodemode");
	aa		(nodemove,		"nodemove");
	aa		(nodeuid,		"nodeuid");
	aa_fini		();
};

#define	va(a)						\
	map_init		(A);			\
	int8init		(A);			\
	A->len=		strlen	(a);			\
	__builtin_memcpy	(A->name,a,0xc);	\
	vattach_faster		(A,a);			\
	A++

__attribute__((constructor))
SCV	init			(void)
{	ng.text_next=
	ng.text_addr=		 ng.text_init;
	ng.text_size=
	sizeof			(ng.text_init);

	ng.link_addr=		 ng.link_init;
	ng.link_size=
	sizeof			(ng.link_init);

	VMETA		*A=	ng.c;
	va			("nc.byte.all");
	va			("nc.byte.last");
	va			("nc.byte.cache.total");
	va			("nc.byte.cache.limit");
	ng.c[3].value.i=	0x1000000000000000;

	map_init		(ng.g);
	ng.g[0].value.i=	-1;
}
