/*	By Kyle Sallee in 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"int.h"
#include	"a.h"
#include	"statvfs.h"

/*
OPERATOR	varstatvfsop[1];
*/

SCV	_statvfs	(void)	{tsubab(statvfssubnew,	_statvfs);}
SCV	f_bavail	(void)	{tsubab(f_bavailsubnew,	f_bavail);}
SCV	f_bfree		(void)	{tsubab(f_bfreesubnew,	f_bfree);}
SCV	f_blocks	(void)	{tsubab(f_blockssubnew,	f_blocks);}
SCV	f_bsize		(void)	{tsubab(f_bsizesubnew,	f_bsize);}
SCV	f_favail	(void)	{tsubab(f_favailsubnew,	f_favail);}
SCV	f_ffree		(void)	{tsubab(f_ffreesubnew,	f_ffree);}
SCV	f_files		(void)	{tsubab(f_filessubnew,	f_files);}
SCV	f_flags		(void)	{tsubab(f_flagssubnew,	f_flags);}
SCV	f_frsize	(void)	{tsubab(f_frsizesubnew,	f_frsize);}
SCV	f_fsid		(void)	{tsubab(f_fsidsubnew,		f_fsid);}
SCV	f_namemax	(void)	{tsubab(f_namemaxsubnew,	f_namemax);}

SCV	statvfsget		(void)
{	Gz.to[0]->reval		(Gz.to[0]);
	*Gz.at=			statvfsget;
	argot_next		();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20190704",
	.official=	"20190704",
	.update=	"20200826"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(_statvfs,	"statvfs");
	aa		(f_bavail,	"f_bavail");
	aa		(f_bfree,	"f_bfree");
	aa		(f_blocks,	"f_blocks");
	aa		(f_bsize,	"f_bsize");
	aa		(f_favail,	"f_favail");
	aa		(f_ffree,	"f_ffree");
	aa		(f_files,	"f_files");
	aa		(f_flags,	"f_flags");
	aa		(f_frsize,	"f_frsize");
	aa		(f_fsid,	"f_fsid");
	aa		(f_namemax,	"f_namemax");
	aa		(statvfsget,	"statvfsget");
	aa_fini		();

/*	varstatvfsop[0]=		varintop[0];	*/
};
