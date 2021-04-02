/*	By Kyle Sallee in 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	<sys/resource.h>
#include	<sys/syscall.h>
#include	<sys/time.h>

#ifndef		IOPRIO_CLASS_NONE
#define		IOPRIO_CLASS_NONE	0
#define		IOPRIO_CLASS_RT		1
#define		IOPRIO_CLASS_BE		2
#define		IOPRIO_CLASS_IDLE	3
#define		IOPRIO_WHO_PROCESS	1
#define		IOPRIO_WHO_PGRP		2
#define		IOPRIO_WHO_USER		3
#endif

typedef	struct
{	int	which,who,prio;
}	IOP;

static	IOP	iop;

__attribute__((always_inline))
static	inline	void	set	(int a,void (*A)(void))
{	errna=			0;
	syscall			(__NR_ioprio_set,iop.which,iop.who,
				 iop.prio|(a<<0xd));
	*Gz.at=			A;
	argot_next		();
}

__attribute__((always_inline))
static	inline	void	lvl	(int a,void (*A)(void))
{	iop.prio=		a;
	*Gz.at=			A;
	argot_next		();
}

__attribute__((always_inline))
static	inline	void	who	(int a,void (*A)(void))
{	iop.which=		a;
	*Gz.at=			A;

	VMETA		*B=
	parapass		(arga(NULL));
/*	denwant			(B);	*/
	iop.who=		B->value.i;
	argot_next		();
}

static	void	ionicepid	(void)	{who (IOPRIO_WHO_PROCESS,ionicepid);}
static	void	ionicepidgroup	(void)	{who (IOPRIO_WHO_PGRP,ionicepidgroup);}
static	void	ioniceuid	(void)	{who (IOPRIO_WHO_USER,ioniceuid);}

static	void	ioniceclassbest	(void)	{set (IOPRIO_CLASS_BE,  ioniceclassbest);}
static	void	ioniceclassidle	(void)	{set (IOPRIO_CLASS_IDLE,ioniceclassidle);}
static	void	ioniceclassreal	(void)	{set (IOPRIO_CLASS_RT,  ioniceclassreal);}

static	void	ionicelevel0	(void)	{lvl (0,ionicelevel0);}
static	void	ionicelevel1	(void)	{lvl (0,ionicelevel1);}
static	void	ionicelevel2	(void)	{lvl (0,ionicelevel2);}
static	void	ionicelevel3	(void)	{lvl (0,ionicelevel3);}
static	void	ionicelevel4	(void)	{lvl (0,ionicelevel4);}
static	void	ionicelevel5	(void)	{lvl (0,ionicelevel5);}
static	void	ionicelevel6	(void)	{lvl (0,ionicelevel6);}
static	void	ionicelevel7	(void)	{lvl (0,ionicelevel7);}
static	void	ionice		(void)	{argot_next();}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20190904",
	.official=	"20190904",
	.update=	"20200211"
};

__attribute__((constructor))
static	CALIGN	void	aainit		(void)
{	aa_init		();
	aa		(ionice,		"ionice");
	aa		(ionicepid,		"ionicepid");
	aa		(ionicepidgroup,	"ionicepidgroup");
	aa		(ioniceuid,		"ioniceuid");
	aa		(ionicelevel0,		"ionicelevel0");
	aa		(ionicelevel1,		"ionicelevel1");
	aa		(ionicelevel2,		"ionicelevel2");
	aa		(ionicelevel3,		"ionicelevel3");
	aa		(ionicelevel4,		"ionicelevel4");
	aa		(ionicelevel5,		"ionicelevel5");
	aa		(ionicelevel6,		"ionicelevel6");
	aa		(ionicelevel7,		"ionicelevel7");
	aa		(ioniceclassbest,	"ioniceclassbest");
	aa		(ioniceclassidle,	"ioniceclassidle");
	aa		(ioniceclassreal,	"ioniceclassreal");
	aa_fini		();
};

