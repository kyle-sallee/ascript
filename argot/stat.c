/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"byte.h"
#include	"stat.h"
#include	<sys/sysmacros.h>

SCV	statreg		(void){tsubab(statregsubnew,		statreg);}
SCV	statsym		(void){tsubab(statsymsubnew,		statsym);}
SCV	statdub		(void){tsubab(statdubsubnew,		statdub);}
SCV	st_dev		(void){tsubab(st_devsubnew,		st_dev);}
SCV	st_dev_major	(void){tsubab(st_dev_majorsubnew,	st_dev_major);}
SCV	st_dev_minor	(void){tsubab(st_dev_minorsubnew,	st_dev_minor);}
SCV	st_gid		(void){tsubab(st_gidsubnew,		st_gid);}
SCV	st_blksize	(void){tsubab(st_blksizesubnew,	st_blksize);}
SCV	st_blocks	(void){tsubab(st_blockssubnew,	st_blocks);}
SCV	st_ino		(void){tsubab(st_inosubnew,		st_ino);}
SCV	st_mode		(void){tsubab(st_modesubnew,		st_mode);}
SCV	st_nlink	(void){tsubab(st_nlinksubnew,		st_nlink);}
SCV	st_rdev		(void){tsubab(st_rdevsubnew,		st_rdev);}
SCV	st_rdev_major	(void){tsubab(st_rdev_majorsubnew,	st_rdev_major);}
SCV	st_rdev_minor	(void){tsubab(st_rdev_minorsubnew,	st_rdev_minor);}
SCV	st_size		(void){tsubab(st_sizesubnew,		st_size);}
SCV	st_uid		(void){tsubab(st_uidsubnew,		st_uid);}

SCV	st_atim_tv_sec	(void){tsubab(st_atim_tv_secsubnew,	st_atim_tv_sec);}
SCV	st_atim_tv_nsec	(void){tsubab(st_atim_tv_nsecsubnew,	st_atim_tv_nsec);}
SCV	st_ctim_tv_sec	(void){tsubab(st_ctim_tv_secsubnew,	st_ctim_tv_sec);}
SCV	st_ctim_tv_nsec	(void){tsubab(st_ctim_tv_nsecsubnew,	st_ctim_tv_nsec);}
SCV	st_mtim_tv_sec	(void){tsubab(st_mtim_tv_secsubnew,	st_mtim_tv_sec);}
SCV	st_mtim_tv_nsec	(void){tsubab(st_mtim_tv_nsecsubnew,	st_mtim_tv_nsec);}


SCV	st_type		(void){tsubab(st_typesubnew,		st_type);}

SCV	statget			(void)
{	VMETA		*B=	Gz.to[0],
			*A=	B->host;
	if			(A->op!=opstat)
	A=			B;

	errna=			0;
	A->reval		(A);
	B->io.success=		errna;
	*Gz.at=			statget;
	argot_next		();
}

SCV	utime_now		(void)
{	Gz.to[0]->value.i=	UTIME_NOW;
	*Gz.at=			utime_now;
	argot_next		();
}

SCV	utime_omit		(void)
{	Gz.to[0]->value.i=	UTIME_OMIT;
	*Gz.at=			utime_omit;
	argot_next		();
}

static	void		_stat	(void)
{	*Gz.at=		_stat;
	argot_next	();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180302",
	.official=	"20180302",
	.update=	"20200826"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();

	aa		(st_rdev,		"statrdev");
	aa		(st_rdev_major,		"statrdevmajor");
	aa		(st_rdev_minor,		"statrdevminor");

	aa		(st_dev,		"statdev");
	aa		(st_dev_major,		"statdevmajor");
	aa		(st_dev_minor,		"statdevminor");

	aa		(utime_now,		"UTIME_NOW");
	aa		(utime_omit,		"UTIME_OMIT");
	aa		(_stat,			"stat");

	aa		(statreg,		"statreg");
	aa		(statsym,		"statsym");
	aa		(statdub,		"statdub");

	aa		(st_blksize,		"statblksize");
	aa		(st_blocks,		"statblocks");
	aa		(st_ino,		"statino");
	aa		(st_mode,		"statmode");
	aa		(st_nlink,		"statnlink");

	aa		(st_atim_tv_sec,	"statatimsec");
	aa		(st_atim_tv_nsec,	"statatimnano");
	aa		(st_ctim_tv_sec,	"statctimsec");
	aa		(st_ctim_tv_nsec,	"statctimnano");
	aa		(st_mtim_tv_sec,	"statmtimsec");
	aa		(st_mtim_tv_nsec,	"statmtimnano");

	aa		(st_gid,		"statgid");
	aa		(st_uid,		"statuid");
	aa		(st_size,		"statsize");
	aa		(st_type,		"stattype");
	aa		(statget,		"statget");
	aa_fini		();
}
