/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"int.h"
#include	"a.h"
#include	"nice.h"

__attribute__((always_inline))
static	inline	void	revision(VMETA *B,int w)
{	errna=			0;
	setpriority		(w,B->host->value.i,B->value.i);
	B->io.success=		errna;
}

__attribute__((always_inline))
static	inline	void	revalue(VMETA *B,int w)
{	errna=			0;
	B->value.i=
	getpriority		(w,B->host->value.i);
	B->io.success=		errna;
}

SCV	revise_grp	(VMETA	*B)	{revision(B,PRIO_PGRP);};
SCV	revise_pid	(VMETA	*B)	{revision(B,PRIO_PROCESS);};
SCV	revise_user	(VMETA	*B)	{revision(B,PRIO_USER);};

SCV	reval_grp	(VMETA	*B)	{revalue(B,PRIO_PGRP);};
SCV	reval_pid	(VMETA	*B)	{revalue(B,PRIO_PROCESS);};
SCV	reval_user	(VMETA	*B)	{revalue(B,PRIO_USER);};

SCV	nicepid		(void)	{tsubab(nicepidsubnew,	nicepid);}
SCV	nicepgrp	(void)	{tsubab(nicepgrpsubnew,	nicepgrp);}
SCV	niceuid		(void)	{tsubab(niceuidsubnew,	niceuid);}

static		void	_nice	(void)
{	*Gz.at=		_nice;
	argot_next	();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180523",
	.official=	"20180523",
	.update=	"20200808"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(_nice,		"nice");
	aa		(niceuid,	"niceuid");
	aa		(nicepgrp,	"nicepgrp");
	aa		(nicepid,	"nicepid");
	aa_fini		();
};
