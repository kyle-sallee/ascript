/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"byte.h"
#include	"int.h"
#include	"a.h"
#include	"swap.h"

#include	<linux/fs.h>
#include	<sys/ioctl.h>

static
PALIGN	SWAPDATA	sd;

__attribute__((always_inline))
static	inline	uint8_t	nibble		(uint8_t b)
{	if		('9'>=b)
	return		b-'0';
	else
	return		b+10-'a';
}

static		void	uuid_acquire	(uint8_t *a,uint8_t *u)
{	errna=		0;
	int		b=
	open			("/proc/sys/kernel/random/uuid",O_RDONLY);
	if		nay	(0>b)	return;

	read			(b,a,0x25);
	close			(b);
	a[0x24]=		0;

	uint32_t
	i=	nibble		(a[0]);		i<<=	4;
	i|=	nibble		(a[1]);		i<<=	4;
	i|=	nibble		(a[2]);		i<<=	4;
	i|=	nibble		(a[3]);		i<<=	4;
	i|=	nibble		(a[4]);		i<<=	4;
	i|=	nibble		(a[5]);		i<<=	4;
	i|=	nibble		(a[6]);		i<<=	4;
	i|=	nibble		(a[7]);

	*(uint32_t *)
	u=
	htobe32			(i);
	u+=			4;

	i=	nibble		(a[9]);		i<<=	4;
	i|=	nibble		(a[0xa]);	i<<=	4;
	i|=	nibble		(a[0xb]);	i<<=	4;
	i|=	nibble		(a[0xc]);

	*(uint16_t *)
	u=
	htobe16			(i);
	u+=			2;

	i=	nibble		(a[0xe]);	i<<=	4;
	i|=	nibble		(a[0xf]);	i<<=	4;
	i|=	nibble		(a[0x10]);	i<<=	4;
	i|=	nibble		(a[0x11]);

	*(uint16_t *)
	u=
	htobe16			(i);
	u+=			2;

	i=	nibble		(a[0x13]);	i<<=	4;
	i|=	nibble		(a[0x14]);	i<<=	4;
	i|=	nibble		(a[0x15]);	i<<=	4;
	i|=	nibble		(a[0x16]);

	*(uint16_t *)
	u=
	htobe16			(i);
	u+=			2;

	i=	nibble		(a[0x18]);	i<<=	4;
	i|=	nibble		(a[0x19]);	i<<=	4;
	i|=	nibble		(a[0x1a]);	i<<=	4;
	i|=	nibble		(a[0x1b]);	i<<=	4;
	i|=	nibble		(a[0x1c]);	i<<=	4;
	i|=	nibble		(a[0x1d]);	i<<=	4;
	i|=	nibble		(a[0x1e]);	i<<=	4;
	i|=	nibble		(a[0x1f]);

	*(uint32_t *)
	u=
	htobe32			(i);
	u+=			4;

	i=	nibble		(a[0x20]);	i<<=	4;
	i|=	nibble		(a[0x21]);	i<<=	4;
	i|=	nibble		(a[0x22]);	i<<=	4;
	i|=	nibble		(a[0x23]);

	*(uint16_t *)
	u=
	htobe16			(i);
}

__attribute__((noinline))
static	CALIGN	int	swapinit_	(void)
{	errna=				0;

	int		b=
	open				(sd.pathname.textaddr,O_WRONLY);
	if				(b>=0)
	{	fstat			(b,&sd.b);
		mode_t		m=	sd.b.st_mode&S_IFMT;
		if			(m==S_IFBLK)
		ioctl			(b,BLKGETSIZE64,&sd.sv);
		else	if		(m==S_IFREG)
		{	sd.sv=		sd.b.st_size;
			posix_fallocate	(b,0,sd.sv);
		}
		else
		{	close		(b);
			return		1;
		}
	}
	else
	{	b=	open		(sd.pathname.textaddr,
					 O_CREAT|O_WRONLY,0400);
		if		nay	(0>b)
		return			1;
		sd.sv=			sd.size.value.i;
		posix_fallocate		(b,0,sd.sv);
	}

	memset				(&sd.s,0,sizeof(sd.s));
	sd.s.version=			1;
	__builtin_memcpy		(sd.s.sig,"SWAPSPACE2",0xa);

	if				(             sd.label.textlen>0)
	__builtin_memcpy		(sd.s.volname,sd.label.textaddr,
					 0x10);

	sd.uuid.textlen=		0x24;
	uuid_acquire			(sd.uuid.textaddr,sd.s.uuid);

	sd.s.last_page=			(sd.sv/PAGE)-1;
	write				(b,&sd.s,sizeof(sd.s));
	fchown				(b,0,0);
	fchmod				(b,0);
	close				(b);
	return				0;
}

SCV	swapon_			(void)
{	int		b=	sd.prefer;
	if		yay	(b==0)
	b=			(sd.priority.value.i<<
				SWAP_FLAG_PRIO_SHIFT) &
				SWAP_FLAG_PRIO_MASK;

	int		c=
	swapon			(sd.pathname.textaddr,b);
	*Gz.at=			swapon_;
	argot_jump		(c==0);
}

SCV	swapoff_		(void)
{	int		c=
	swapoff			(sd.pathname.textaddr);
	*Gz.at=			swapoff_;
	argot_jump		(c==0);
}

SCV	swapprefer		(void)
{	sd.prefer=		SWAP_FLAG_PREFER;
	*Gz.at=			swapprefer;
	argot_next		();
}

SCV	swapinit		(void)
{	int		a=
	swapinit_		();
	*Gz.at=			swapinit;
	argot_jump		(a==0);
}

static		void	swap	(void)
{	*Gz.at=		swap;
	argot_next	();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180408",
	.official=	"20180408",
	.update=	"20200625"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(swap,		"swap");
	aa		(swapinit,	"swapinit");
	aa		(swapon_,	"swapon");
	aa		(swapoff_,	"swapoff");
	aa		(swapprefer,	"swapprefer");
	aa_fini		();
};


__attribute__((constructor))
SCV	init			(void)
{	__builtin_memcpy	(sd.label.name,		"swap.label",0xa);
	__builtin_memcpy	(sd.pathname.name,	"swap.pathname\0\0",0x10);
	__builtin_memcpy	(sd.priority.name,	"swap.priority\0\0",0x10);
	__builtin_memcpy	(sd.size.name,		"swap.size",9);
	__builtin_memcpy	(sd.uuid.name,		"swap.uuid",9);

	sd.label.len=		0xa;
	sd.pathname.len=	0xd;
	sd.priority.len=	0xd;
	sd.size.len=		9;
	sd.uuid.len=		9;

	map_init		(&sd.label);
	map_init		(&sd.pathname);
	map_init		(&sd.priority);
	map_init		(&sd.size);
	map_init		(&sd.uuid);

	byteinit		(&sd.label);
	byteinit		(&sd.pathname);
	int4init		(&sd.priority);
	int8init		(&sd.size);
	dex8data		(&sd.size);
	sd.size.show=		Gz.out.dex8;
	byteinit		(&sd.uuid);

	vattach			(&sd.label);
	vattach			(&sd.pathname);
	vattach			(&sd.priority);
	vattach			(&sd.size);
	vattach			(&sd.uuid);
}
