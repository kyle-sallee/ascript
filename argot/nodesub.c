/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"

#include	"byte.h"
#include	"int.h"
#include	"a.h"
#include	"nodesub.h"

#include	<e2p/e2p.h>
#include	<stdlib.h>	/* for realpath */
#include	<sys/ioctl.h>
#include	<sys/types.h>

SCV	revise_nodesubaim	(VMETA *B)
{	VMETA		*A=	B->host;
	errna=			0;
	unlink			(A->textaddr);
	symlink			(A->textaddr,B->textaddr);
	B->io.success=		errna;
}

SCV	show_nodesubaim			(VMETA *B)
{	VMETA		*A=		B->host;
	ssize_t		a;
	uint8_t		*b=		B->textaddr;
	size_t		c=		B->textsize;

	errna=				0;
	if			yay	(A->op->int_compat==0)
	a=	readlink		(A->textaddr,b,c);
	else
	a=	readlinkat		(A->value.i,"",b,c);
	B->io.success=			errna;

	if			nay	(0>a)
	a=				0;

	B->textaddr[
	B->textlen=a]=			0;
}

SCV	reval_nodesubgid	(VMETA *B)
{	VMETA		*A=	B->host;
	struct	stat	b;

	b.st_gid=		-1;
	errna=			0;
	if			(A->op->int_compat)
	fstat			(A->value.i,&b);
	else
	stat			(A->textaddr,&b);
	B->io.success=		errna;
	B->value.i=		b.st_gid;
}

SCV	revise_nodesubgid	(VMETA *B)
{	gid_t		a=	B->value.i;

	VMETA		*A=	B->host;
	errna=			0;
	if		yay	(A->op->int_compat)
	fchown			(A->value.i  ,-1,a);
	else
	chown			(A->textaddr,-1,a);
	B->io.success=		errna;
}

SCV	reval_nodesubmode	(VMETA *B)
{	VMETA		*A=	B->host;
	struct	stat	b;
	int		c;

	errna=			0;
	if			(A->op->int_compat)
	c=	fstat		(A->value.i,&b);
	else
	c=	stat		(A->textaddr,&b);
	B->io.success=		errna;

	mode_t		d;
	if			(c==0)
	d=			b.st_mode&07777;
	else
	d=			-1;
	B->value.i=		d;
}

SCV	revise_nodesubmode	(VMETA *B)
{	mode_t		a=	B->value.i;

	VMETA		*A=	Gz.to[0]->host;
	errna=			0;
	if		yay	(A->op->int_compat)
	fchmod			(A->value.i,a);
	else
	chmod			(A->textaddr,a);
	B->io.success=		errna;
}

SCV	revise_nodesubsize	(VMETA *B)
{	VMETA		*A=	B->host;
	off_t		b=	B->value.i;

	errna=			0;
	if			(A->op->int_compat)
	ftruncate		(A->value.i,b);
	else
	truncate		(A->textaddr,b);
	B->io.success=		errna;
}

SCV	reval_nodesubsize	(VMETA *B)
{	VMETA		*A=	B->host;
	struct	stat	b;
	b.st_size=		-1;

	errna=			0;
	if			(A->op->int_compat)
	fstat			(A->value.i,&b);
	else
	stat			(A->textaddr,&b);
	B->io.success=		errna;
	B->value.i=		b.st_size;
}

SCV	revise_nodesubfill	(VMETA *B)
{	int		a=	-1,b;
	VMETA		*A=	B->host;

	errna=			0;
	if			(A->op->int_compat)
	b=			A->value.i;
	else
	a=	b=	open	(A->textaddr,O_RDWR);

	off_t		c=	B->value.i;

	posix_fallocate		(b,0,c);

	if			(a>=0)
	close			(a);
	B->io.success=		errna;
}

SCV	reval_nodesubfill	(VMETA *B)
{	VMETA		*A=	B->host;
	struct	stat	b;
	int		c;

	if			(A->op->int_compat)
	c=	fstat		(A->value.i,&b);
	else
	c=	stat		(A->textaddr,&b);

	if		yay	(c==0)
	B->value.i=		b.st_blocks*b.st_blksize;
	else
	B->value.i=		-1;
}

SCV	show_nodesubreal	(VMETA *B)
{	VMETA		*A=	B->host;
	errna=			0;
	char		*a=
	realpath		(A->textaddr,B->textaddr);
	B->io.success=		errna;

	size_t		b;
	if		yay	(a!=NULL)
	b=	strlenb		(B->textaddr);
	else
	b=			0;

	B->textaddr[
	B->textlen=b]=		0;
}

SCV	revise_nodesubuid	(VMETA *B)
{	uid_t		a=	B->value.i;
	VMETA		*A=	B->host;

	errna=			0;
	if		yay	(A->op->int_compat)
	fchown			(A->value.i,a,-1);
	else
	chown			(A->textaddr,a,-1);
	B->io.success=		errna;
}

SCV	reval_nodesubuid	(VMETA *B)
{	VMETA		*A=	B->host;
	struct	stat	b;

	b.st_uid=		-1;
	errna=			0;
	if			(A->op->int_compat)
	fstat			(A->value.i,&b);
	else
	stat			(A->textaddr,&b);
	B->io.success=		errna;
	B->value.i=		b.st_uid;
}

SCV	nodesubgid	(void)	{tsubab(nodesubgidsubnew,nodesubgid);}
SCV	nodesubmode	(void)	{tsubab(nodesubmodesubnew,nodesubmode);}
SCV	nodesubaim	(void)	{tsubab(nodesubaimsubnew,nodesubaim);}
SCV	nodesubsize	(void)	{tsubab(nodesubsizesubnew,nodesubsize);}
SCV	nodesubfill	(void)	{tsubab(nodesubfillsubnew,nodesubfill);}
SCV	nodesubreal	(void)	{tsubab(nodesubrealsubnew,nodesubreal);}
SCV	nodesubuid	(void)	{tsubab(nodesubuidsubnew,nodesubuid);}

#ifdef	__linux__
SCV	revise_nodesubattr	(VMETA *B)
{	int		a=	-1,b;

	VMETA		*A=	B->host;
	errna=			0;
	if		yay	(A->op->int_compat)
	b=			A->value.i;
	else
	a=	b=	open	(A->textaddr,O_RDONLY);

	int		c=	B->value.i;
	ioctl			(b,EXT2_IOC_SETFLAGS,&c);

	if			(a>=0)
	close			(a);
	B->io.success=		errna;
}

SCV	reval_nodesubattr	(VMETA *B)
{	VMETA		*A=	B->host;
	int		b,d=	-1;

	errna=			0;
	if			(A->op->int_compat)
	b=			A->value.i;
	else
	b=	open		(A->textaddr,O_RDONLY);

	ioctl			(b,EXT2_IOC_GETFLAGS,&d);
	B->io.success=		errna;
	B->value.i=		d;

	if			(A->op->int_compat==0)
	close			(b);
}

#define	vmac(z)					\
	{	.name=		#z,		\
		.value.i=	(z),		\
		.len=	strlen	(#z),		\
		.op=		opint8,		\
	},

#define	vinit(z)			\
	map_init	(A);		\
	vattach_faster	(A,#z);		\
	A->show=	Gz.out.dex8;	\
	A->textlen=	0x10;		\
	A++

__attribute__((always_inline))
static	inline	void	nodesubattrinit	(void)
{	static	VMETA	a[]=
	{	vmac	(EXT2_SECRM_FL)
		vmac	(EXT2_UNRM_FL)
		vmac	(EXT2_COMPR_FL)
		vmac	(EXT2_SYNC_FL)
		vmac	(EXT2_IMMUTABLE_FL)
		vmac	(EXT2_APPEND_FL)
		vmac	(EXT2_NODUMP_FL)
		vmac	(EXT2_NOATIME_FL)
		vmac	(EXT2_DIRTY_FL)
		vmac	(EXT2_COMPRBLK_FL)
		vmac	(EXT2_NOCOMPR_FL)
		vmac	(EXT4_ENCRYPT_FL)
		vmac	(EXT2_BTREE_FL)
		vmac	(EXT2_INDEX_FL)
		vmac	(EXT2_IMAGIC_FL)
		vmac	(EXT3_JOURNAL_DATA_FL)
		vmac	(EXT2_NOTAIL_FL)
		vmac	(EXT2_DIRSYNC_FL)
		vmac	(EXT2_TOPDIR_FL)
		vmac	(EXT4_HUGE_FILE_FL)
		vmac	(EXT4_EXTENTS_FL)
		vmac	(EXT4_EA_INODE_FL)
		vmac	(FS_NOCOW_FL)
		vmac	(EXT4_SNAPFILE_FL)
		vmac	(EXT4_SNAPFILE_DELETED_FL)
		vmac	(EXT4_SNAPFILE_SHRUNK_FL)
		vmac	(EXT4_INLINE_DATA_FL)
		vmac	(EXT4_PROJINHERIT_FL)
		vmac	(EXT2_RESERVED_FL)
		vmac	(EXT2_FL_USER_VISIBLE)
		vmac	(EXT2_FL_USER_MODIFIABLE)
	};
/*	EXT2_FL_USER_VISIBLE 	and
	EXT2_FL_USER_MODIFIABLE
	are masks.
*/

	VMETA		*A=	a;
	vinit	(EXT2_SECRM_FL);
	vinit	(EXT2_UNRM_FL);
	vinit	(EXT2_COMPR_FL);
	vinit	(EXT2_SYNC_FL);
	vinit	(EXT2_IMMUTABLE_FL);
	vinit	(EXT2_APPEND_FL);
	vinit	(EXT2_NODUMP_FL);
	vinit	(EXT2_NOATIME_FL);
	vinit	(EXT2_DIRTY_FL);
	vinit	(EXT2_COMPRBLK_FL);
	vinit	(EXT2_NOCOMPR_FL);
	vinit	(EXT4_ENCRYPT_FL);
	vinit	(EXT2_BTREE_FL);
	vinit	(EXT2_INDEX_FL);
	vinit	(EXT2_IMAGIC_FL);
	vinit	(EXT3_JOURNAL_DATA_FL);
	vinit	(EXT2_NOTAIL_FL);
	vinit	(EXT2_DIRSYNC_FL);
	vinit	(EXT2_TOPDIR_FL);
	vinit	(EXT4_HUGE_FILE_FL);
	vinit	(EXT4_EXTENTS_FL);
	vinit	(EXT4_EA_INODE_FL);
	vinit	(FS_NOCOW_FL);
	vinit	(EXT4_SNAPFILE_FL);
	vinit	(EXT4_SNAPFILE_DELETED_FL);
	vinit	(EXT4_SNAPFILE_SHRUNK_FL);
	vinit	(EXT4_INLINE_DATA_FL);
	vinit	(EXT4_PROJINHERIT_FL);
	vinit	(EXT2_RESERVED_FL);
	vinit	(EXT2_FL_USER_VISIBLE);
	vinit	(EXT2_FL_USER_MODIFIABLE);
}

SCV	nodesubattr	(void)
{	static	uint8_t	a=	0;
	if			(a==0)
	{	a=		1;
		nodesubattrinit	();
	}
	tsubab		(nodesubattrsubnew,nodesubattr);
}
#endif

__attribute__((cold))
static		void	nodesub	(void)
{	*Gz.at=		nodesub;
	argot_next	();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180414",
	.official=	"20180414",
	.update=	"20200809"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(nodesub,	"nodesub");
#ifdef	__linux__
	aa		(nodesubattr,	"nodesubattr");
#endif
	aa		(nodesubgid,	"nodesubgid");
	aa		(nodesubfill,	"nodesubfill");
	aa		(nodesubmode,	"nodesubmode");
	aa		(nodesubaim,	"nodesubaim");
	aa		(nodesubreal,	"nodesubreal");
	aa		(nodesubsize,	"nodesubsize");
	aa		(nodesubuid,	"nodesubuid");
	aa_fini		();
};
