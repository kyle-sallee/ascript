/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"

#include	<stdio.h>
#include	<sys/ioctl.h>
#include	<sys/reboot.h>
#include	<sys/sysmacros.h>
#include	<sys/vt.h>

__attribute__((noinline))
SCV	vts_get			(struct	vt_stat	*vts)
{	int		a=
	open			("/dev/console",O_NONBLOCK|O_NOCTTY|O_RDONLY);
	ioctl			(a,VT_GETSTATE,vts);
	ioctl			(a,VT_ACTIVATE,1);
	close			(a);
}

__attribute__((noinline))
SCV	vts_set			(struct	vt_stat	*vts)
{	int		a=
	open			("/dev/console",O_NONBLOCK|O_NOCTTY|O_RDONLY);
	ioctl			(a,VT_ACTIVATE,vts->v_active);
	close			(a);
}

__attribute__((noinline))
SCV	drop			(void)
{	sync			();
	int		a=
	open			("/proc/sys/vm/drop_caches",O_WRONLY);
	write			(a,"3\n",2);
	close			(a);

	a=
	open			("/proc/sys/vm/compact_memory",O_WRONLY);
	write			(a,"1\n",2);
	close			(a);
}

static	inline	void	disk	(uint8_t *a)
{	int		b=
	open			("/sys/power/disk",O_WRONLY);
	write			(b,a,strlen(a));
	close			(b);
}

static	inline	void	state	(uint8_t *a)
{	int		b=
	open			("/sys/power/state",O_WRONLY);
	write			(b,a,strlen(a));
	close			(b);
}

__attribute__((noinline))
SCV	powerimagesize		(void)
{
/*	denwant			(Gz.to[0]);	*/
	VMETA		*A=	 Gz.to[0];

	int		a=
	open			("/sys/power/image_size",O_WRONLY);
	write			(a,A->textaddr,A->textlen);
	close			(a);
	*Gz.at=			powerimagesize;
	argot_next		();
}

SCV	powerhalt	(void)
{	drop		();
	reboot		(RB_POWER_OFF);
	argot_next	();
}

SCV	powerreboot	(void)
{	drop		();
	reboot		(RB_AUTOBOOT);
	argot_next	();
}

SCV	powersuspenddisk	(void)
{	struct	vt_stat	v;
	vts_get			(&v);
	drop			();
	disk			("shutdown\n");
	state			("disk\n");
	vts_set			(&v);
	argot_next		();
}

SCV	powersuspendram		(void)
{	struct	vt_stat	v;
	vts_get			(&v);
	drop			();
	disk			("suspend\n");
	state			("disk\n");
	vts_set			(&v);
	argot_next		();
}

SCV	powerresume		(void)
{	show			(Gz.to[0]);
	VMETA		*A=	 Gz.to[0];

	struct stat	a;
	stat			(A->textaddr,&a);

	int		b=
	open			("/sys/power/resume",O_WRONLY);
	dprintf			(b,"%i:%i\n",
				 major(a.st_rdev),
				 minor(a.st_rdev));
	close			(b);
	argot_next		();
}

static		void	power	(void)
{	argot_next		();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180410",
	.official=	"20180410",
	.update=	"20200625"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(power,			"power");
	aa		(powerimagesize,	"powerimagesize");
	aa		(powerhalt,		"powerhalt");
	aa		(powerreboot,		"powerreboot");
	aa		(powerresume,		"powerresume");
	aa		(powersuspenddisk,	"powersuspenddisk");
	aa		(powersuspendram,	"powersuspendram");
	aa_fini		();
};

