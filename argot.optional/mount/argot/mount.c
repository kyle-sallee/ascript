/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"byte.h"
#include	"a.h"
#include	"mount.h"
#include	<dirent.h>
#include	<iconv.h>
#include	<stdio.h>

PALIGN
static	MNT_DATA	md;

#define	va(a)					\
{	.name=		(a),			\
	.len=	strlen	((a)),			\
	.op=		opbyte,			\
	.io.flag=	textmapuse|textmapunmap	\
}

PALIGN
static	VMETA	mv[5]=
{	va	("mount.data"),
	va	("mount.filesystem"),
	va	("mount.partlabel"),
	va	("mount.source"),
	va	("mount.target"),
};

#define	vc(a)				\
	map_init		(A);	\
	vattach_faster		(A,a);	\
	A++

__attribute__((constructor))
SCV	var_init		(void)
{	VMETA		*A=	mv;
	vc			("mount.data");
	vc			("mount.filesystem");
	vc			("mount.partlabel");
	vc			("mount.source");
	vc			("mount.target");

	mv[0].textaddr=		md.data_p;
	mv[1].textaddr=		md.filesystem_p;
	mv[2].textaddr=		md.partlabel_p;
	mv[3].textaddr=		md.source_p;
	mv[4].textaddr=		md.target_p;

	mv[0].textsize=
	mv[1].textsize=
	mv[2].textsize=
	mv[3].textsize=
	mv[4].textsize=		PAGE;
}

static		void	from_partlabel	(void);
static		void	_mount		(void)
{	*Gz.at=		_mount;
	if			nay	(mv_target.textlen==0)
	{	argot_next		();
		return;
	}

	mv_partlabel.textaddr[
	mv_partlabel.textlen]=		0;

	if				(mv_partlabel.textlen>0)
	from_partlabel			();

	mv_data.textaddr[
	mv_data.textlen]=		0;
	mv_filesystem.textaddr[
	mv_filesystem.textlen]=		0;
	mv_source.textaddr[
	mv_source.textlen]=		0;
	mv_target.textaddr[
	mv_target.textlen]=		0;

	errna=		0;
	int		a=
	mount				(md.source_p,
					 md.target_p,
					 md.filesystem_p,
					 md.mflag.i,
					 md.data_p);

	argot_jump			(a==0);
}

SCV	_umount				(void)
{	errna=				0;
	mv_target.textaddr[
	mv_target.textlen]=		0;

	int		a=
	umount2				(mv_target.textaddr,md.uflag.i);
	*Gz.at=				_umount;
	argot_jump			(a==0);
}

SCV	proc_mounts			(void);
SCV	_mounted			(void)
{	proc_mounts			();

	uint8_t		*a=		mv_target.textaddr;
	int64_t		b=		mv_target.textlen;
	uint8_t		*c=		md.proc_mounts;
	int		d=		md.proc_mounts_len;

	if				(a[b-1]==0)
	b--;

	if			nay	(c[b]==' ')
	if			nay	(memcmpa(c,a,b)==0)
	goto				found;

	uint8_t		*e;

	while				((d>0)&&(e=memmem(c,d,a,b)))
	{	if		nay	(e[ b]==' ')
		if		nay	(e[-1]==' ')
		goto			found;
		e+=			1;
		d-=			(e-c);
		c=			e+1;
	}

	*Gz.at=				_mounted;
	argot_next			();
	return;

	found:
	*Gz.at=				_mounted;
	argot_skip			();
}

__attribute__((always_inline))
static	inline	uint8_t	memcmpx48	(void const *a, void const *b)
{	if	nay	(*(uint64_t *)(a+0x00)!=*(uint64_t *)(b+0x00))return 1;
	if	nay	(*(uint64_t *)(a+0x08)!=*(uint64_t *)(b+0x08))return 1;
	if	nay	(*(uint64_t *)(a+0x10)!=*(uint64_t *)(b+0x10))return 1;
	if	nay	(*(uint64_t *)(a+0x18)!=*(uint64_t *)(b+0x18))return 1;
	if	nay	(*(uint64_t *)(a+0x20)!=*(uint64_t *)(b+0x20))return 1;
	if	nay	(*(uint64_t *)(a+0x28)!=*(uint64_t *)(b+0x28))return 1;
	if	nay	(*(uint64_t *)(a+0x30)!=*(uint64_t *)(b+0x30))return 1;
	if	nay	(*(uint64_t *)(a+0x38)!=*(uint64_t *)(b+0x38))return 1;
	if	nay	(*(uint64_t *)(a+0x40)!=*(uint64_t *)(b+0x40))return 1;
								      return 0;
}

static	void	mount_cache		(void);
SCV		from_partlabel		(void)
{	if				(md.sys_class_block_len==0)
	mount_cache			();

	mv_source.textaddr[
	mv_source.textlen=0]=	0;

	iconv_t	cd=
	iconv_open			("UTF-16LE","UTF-8");
	md.ibl=				mv_partlabel.textlen;
	md.obl=				0x48;
	md.ib=				mv_partlabel.textaddr;
	md.ob=				md.temp;
	memset				(md.temp,0,0x48);

	size_t		a=
	iconv				(cd,&md.ib,&md.ibl,&md.ob,&md.obl);
	iconv_close			(cd);
	if			nay	(0>a)
	return;

	uint8_t		*b=		md.temp;
	uint8_t		*c=		md.sys_class_block;

	uint8_t		*d;
	int		e;
	for				(;c[0x780];c+=0x800)
	for				(d=c+0x38,e=0xf;e;e--,d+=0x80)
/*	if			nay	(__builtin_memcmp(d,b,0x48)==0)	*/
	if			nay	(memcmpx48(d,b)==0)
	goto				found;
	return;

	found:;
	mv_source.textlen=
	snprintf			(mv_source.textaddr,
					 mv_source.textsize,
					 "%s%i",c+0x780,(d-c)/0x80+1);
}

static		void	gptread		(uint8_t *,uint8_t *);
static		int	disk		(int,uint8_t *);
static		void	mount_cache	(void)
{	uint8_t		*a=		md.sys_class_block;
	int		b=
	open				("/sys/class/block",
					 O_DIRECTORY|O_RDONLY);
	if			nay	(0>b)
	return;

	DIR		*c=
	fdopendir			(b);

	struct	dirent	*d;

	while				(d=readdir(c))
	{	if		nay	(d->d_name[0]=='.')	continue;
/*		if		yay	(disk(b,d->d_name))	continue;
*/
		gptread			(d->d_name,a);
		a+=			0x800;
	}
	closedir			(c);

	md.sys_class_block_len=		a-md.sys_class_block;
}

__attribute__((unused))
static	inline	int	disk		(int a,uint8_t *b)
{	int		c=
	openat				(a,b,O_RDONLY);

	if			nay	(0>c)
	return				1;

	int		d=
	faccessat			(c,"removable",F_OK,0);

	close				(c);
	return				d;
}

static		void	gptread	(uint8_t *a,uint8_t *b)
{	uint8_t		*c=	b+0x780;
	memcpy			(c,"/dev/",5);
	int		d=
	strlenb			(a);
	memcpya			(c+5,a,d);

	d=
	open			(c,O_RDONLY);
	if			(0>d)
	return;
	lseek			(d,0x400,SEEK_SET);
	read			(d,b,0x780);
	close			(d);
}

__attribute__((noinline))
SCV	proc_mounts		(void)
{	int		a=
	open			("/proc/mounts",O_RDONLY);
	if		nay	(0>a)
	return;

	ssize_t		b=
	read			(a,md.proc_mounts,sizeof(md.proc_mounts));
	close			(a);

	if		yay	(b>=0)
	md.proc_mounts_len=	b;
	else
	md.proc_mounts_len=	0;
}

__attribute__((always_inline))
static	inline	void	mflag_or	(int64_t a,void (*A)(void))
{	md.mflag.i|=	a;
	*Gz.at=		A;
	argot_next	();
}

__attribute__((always_inline))
static	inline	void	uflag_or	(int64_t a,void (*A)(void))
{	md.uflag.i|=	a;
	*Gz.at=		A;
	argot_next	();
}


#ifdef	MS_RDONLY
static		void	ms_RDONLY	(void)	{mflag_or(MS_RDONLY,ms_RDONLY);}
#endif
#ifdef	MS_NOSUID
static		void	ms_NOSUID	(void)	{mflag_or(MS_NOSUID,ms_NOSUID);}
#endif
#ifdef	MS_NODEV
static		void	ms_NODEV	(void)	{mflag_or(MS_NODEV,ms_NODEV);}
#endif
#ifdef	MS_NOEXEC
static		void	ms_NOEXEC	(void)	{mflag_or(MS_NOEXEC,ms_NOEXEC);}
#endif
#ifdef	MS_SYNCHRONOUS
static		void	ms_SYNCHRONOUS	(void)	{mflag_or(MS_SYNCHRONOUS,ms_SYNCHRONOUS);}
#endif
#ifdef	MS_REMOUNT
static		void	ms_REMOUNT	(void)	{mflag_or(MS_REMOUNT,ms_REMOUNT);}
#endif
#ifdef	MS_MANDLOCK
static		void	ms_MANDLOCK	(void)	{mflag_or(MS_MANDLOCK,ms_MANDLOCK);}
#endif
#ifdef	MS_DIRSYNC
static		void	ms_DIRSYNC	(void)	{mflag_or(MS_DIRSYNC,ms_DIRSYNC);}
#endif
#ifdef	MS_NOATIME
static		void	ms_NOATIME	(void)	{mflag_or(MS_NOATIME,ms_NOATIME);}
#endif
#ifdef	MS_NODIRATIME
static		void	ms_NODIRATIME	(void)	{mflag_or(MS_NODIRATIME,ms_NODIRATIME);}
#endif
#ifdef	MS_BIND
static		void	ms_BIND		(void)	{mflag_or(MS_BIND,ms_BIND);}
#endif
#ifdef	MS_MOVE
static		void	ms_MOVE		(void)	{mflag_or(MS_MOVE,ms_MOVE);}
#endif
#ifdef	MS_REC
static		void	ms_REC		(void)	{mflag_or(MS_REC,ms_REC);}
#endif
#ifdef	MS_SILENT
static		void	ms_SILENT	(void)	{mflag_or(MS_SILENT,ms_SILENT);}
#endif
#ifdef	MS_POSIXACL
static		void	ms_POSIXACL	(void)	{mflag_or(MS_POSIXACL,ms_POSIXACL);}
#endif
#ifdef	MS_UNBINDABLE
static		void	ms_UNBINDABLE	(void)	{mflag_or(MS_UNBINDABLE,ms_UNBINDABLE);}
#endif
#ifdef	MS_PRIVATE
static		void	ms_PRIVATE	(void)	{mflag_or(MS_PRIVATE,ms_PRIVATE);}
#endif
#ifdef	MS_SLAVE
static		void	ms_SLAVE	(void)	{mflag_or(MS_SLAVE,ms_SLAVE);}
#endif
#ifdef	MS_SHARED
static		void	ms_SHARED	(void)	{mflag_or(MS_SHARED,ms_SHARED);}
#endif
#ifdef	MS_RELATIME
static		void	ms_RELATIME	(void)	{mflag_or(MS_RELATIME,ms_RELATIME);}
#endif
#ifdef	MS_KERNMOUNT
static		void	ms_KERNMOUNT	(void)	{mflag_or(MS_KERNMOUNT,ms_KERNMOUNT);}
#endif
#ifdef	MS_I_VERSION
static		void	ms_I_VERSION	(void)	{mflag_or(MS_I_VERSION,ms_I_VERSION);}
#endif
#ifdef	MS_STRICTATIME
static		void	ms_STRICTATIME	(void)	{mflag_or(MS_STRICTATIME,ms_STRICTATIME);}
#endif
#ifdef	MS_LAZYTIME
static		void	ms_LAZYTIME	(void)	{mflag_or(MS_LAZYTIME,ms_LAZYTIME);}
#endif

#ifdef	MNT_FORCE
static		void	mnt_FORCE	(void)	{uflag_or(MNT_FORCE,mnt_FORCE);}
#endif
#ifdef	MNT_DETACH
static		void	mnt_DETACH	(void)	{uflag_or(MNT_DETACH,mnt_DETACH);}
#endif
#ifdef	MNT_EXPIRE
static		void	mnt_EXPIRE	(void)	{uflag_or(MNT_EXPIRE,mnt_EXPIRE);}
#endif
#ifdef	UMOUNT_NO_FOLLOW
static		void	umount_NO_FOLLOW(void)	{uflag_or(UMOUNT_NO_FOLLOW,umount_NO_FOLLOW);}
#endif

static		void	ms_ZERO		(void)
{	*Gz.at=		ms_ZERO;
	md.mflag.i=	0;
	argot_next	();
}

static		void	mnt_ZERO	(void)
{	*Gz.at=		mnt_ZERO;
	md.uflag.i=	0;
	argot_next	();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180409",
	.official=	"20180409",
	.update=	"20200719"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
#ifdef	MS_RDONLY
	aa		(ms_RDONLY,		"MS_RDONLY");
#endif
#ifdef	MS_NOSUID
	aa		(ms_NOSUID,		"MS_NOSUID");
#endif
#ifdef	MS_NODEV
	aa		(ms_NODEV,		"MS_NODEV");
#endif
#ifdef	MS_NOEXEC
	aa		(ms_NOEXEC,		"MS_NOEXEC");
#endif
#ifdef	MS_SYNCHRONOUS
	aa		(ms_SYNCHRONOUS,	"MS_SYNCHRONOUS");
#endif
#ifdef	MS_REMOUNT
	aa		(ms_REMOUNT,		"MS_REMOUNT");
#endif
#ifdef	MS_MANDLOCK
	aa		(ms_MANDLOCK,		"MS_MANDLOCK");
#endif
#ifdef	MS_DIRSYNC
	aa		(ms_DIRSYNC,		"MS_DIRSYNC");
#endif
#ifdef	MS_NOATIME
	aa		(ms_NOATIME,		"MS_NOATIME");
#endif
#ifdef	MS_NODIRATIME
	aa		(ms_NODIRATIME,		"MS_NODIRATIME");
#endif
#ifdef	MS_BIND
	aa		(ms_BIND,		"MS_BIND");
#endif
#ifdef	MS_MOVE
	aa		(ms_MOVE,		"MS_MOVE");
#endif
#ifdef	MS_REC
	aa		(ms_REC,		"MS_REC");
#endif
#ifdef	MS_SILENT
	aa		(ms_SILENT,		"MS_SILENT");
#endif
#ifdef	MS_POSIXACL
	aa		(ms_POSIXACL,		"MS_POSIXACL");
#endif
#ifdef	MS_UNBINDABLE
	aa		(ms_UNBINDABLE,		"MS_UNBINDABLE");
#endif
#ifdef	MS_PRIVATE
	aa		(ms_PRIVATE,		"MS_PRIVATE");
#endif
#ifdef	MS_SLAVE
	aa		(ms_SLAVE,		"MS_SLAVE");
#endif
#ifdef	MS_SHARED
	aa		(ms_SHARED,		"MS_SHARED");
#endif
#ifdef	MS_RELATIME
	aa		(ms_RELATIME,		"MS_RELATIME");
#endif
#ifdef	MS_KERNMOUNT
	aa		(ms_KERNMOUNT,		"MS_KERNMOUNT");
#endif
#ifdef	MS_I_VERSION
	aa		(ms_I_VERSION,		"MS_I_VERSION");
#endif
#ifdef	MS_STRICTATIME
	aa		(ms_STRICTATIME,	"MS_STRICTATIME");
#endif
#ifdef	MS_LAZYTIME
	aa		(ms_LAZYTIME,		"MS_LAZYTIME");
#endif
#ifdef	MNT_FORCE
	aa		(mnt_FORCE,		"MNT_FORCE");
#endif
#ifdef	MNT_DETACH
	aa		(mnt_DETACH,		"MNT_DETACH");
#endif
#ifdef	MNT_EXPIRE
	aa		(mnt_EXPIRE,		"MNT_EXPIRE");
#endif
#ifdef	UMOUNT_NO_FOLLOW
	aa		(umount_NO_FOLLOW,	"UMOUNT_NO_FOLLOW");
#endif

	aa		(ms_ZERO,		"MS_ZERO");
	aa		(mnt_ZERO,		"MNT_ZERO");
	aa		(_mounted,		"mounted");
	aa		(_umount,		"umount");
	aa		(_mount,		"mount");
	aa_fini		();
};

/*
__attribute__((constructor))
SCV	init_old	(void)
{	__builtin_memcpy(mv_data.name,		"mount.data",0xa);
	__builtin_memcpy(mv_filesystem.name,	"mount.filesystem",0x10);
	__builtin_memcpy(mv_partlabel.name,	"mount.partlabel",0x10);
	__builtin_memcpy(mv_source.name,	"mount.source\0\0\0",0x10);
	__builtin_memcpy(mv_target.name,	"mount.target\0\0\0",0x10);

	mv_data.len=			0xa;
	mv_filesystem.len=		0x10;
	mv_partlabel.len=		0xf;
	mv_source.len=			0xc;
	mv_target.len=			0xc;

	VMETA		*A=		&mv_data;
	int		b;
	uint8_t		*c=		mv_data_p;
	for				(b=0;5>b;b++,c+=PAGE)
	{	map_init		(A+b);
		bytesubnew		(A+b);
		A[b].textaddr=	c;
		A[b].textsize=	PAGE;
		vattach			(A+b);
	}
}
*/
