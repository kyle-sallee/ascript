/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	<dirent.h>
#include	<sched.h>

__attribute__((always_inline))
static	inline	void	save	(void (*a)(void),uint8_t *b)
{	int		c=
	open		(b,O_RDONLY);
	c=
	highmake	(c);
	*Gz.at=		a;
	argot_next	();
	setns		(c,0);
	close		(c);
}

__attribute__((always_inline))
static	inline	void	enter	(void (*A) (void),int a)
{	int		b,c,d;
	VMETA		*B=	Gz.to[0];
	if			(B->op->int_compat!=0)
	{	b=		B->value.i;
		c=		-1;
	}
	else
	{	b=
		c=
		open		(B->textaddr,O_RDONLY);
	}
	d=
	setns			(b,a);

	if			(c>=0)
	close			(c);

	*Gz.at=			A;
	argot_jump		(d==0);
}

__attribute__((always_inline))
static	inline	void	leave	(void (*A) (void),int a)
{	int		d=
	unshare			(a);

	*Gz.at=			A;
	argot_jump		(d==0);
}

SCV	newcgroup	(void)	{leave(newcgroup,	CLONE_NEWCGROUP);}
SCV	newfiles	(void)	{leave(newfiles,	CLONE_FILES);}
SCV	newfs		(void)	{leave(newfs,		CLONE_FS);}
SCV	newipc		(void)	{leave(newipc,		CLONE_NEWIPC);}
SCV	newmnt		(void)	{leave(newmnt,		CLONE_NEWNS);}
SCV	newnet		(void)	{leave(newnet,		CLONE_NEWNET);}
SCV	newpid		(void)	{leave(newpid,		CLONE_NEWPID);}
SCV	newsem		(void)	{leave(newsem,		CLONE_SYSVSEM);}
SCV	newuser		(void)	{leave(newuser,		CLONE_NEWUSER);}
SCV	newuts		(void)	{leave(newuts,		CLONE_NEWUTS);}

SCV	oldcgroup	(void)	{enter(oldcgroup,	CLONE_NEWCGROUP);}
/*
SCV	oldfiles	(void)	{enter(oldfiles,	CLONE_FILES);}
SCV	oldfs		(void)	{enter(oldfs,		CLONE_FS);}
*/
SCV	oldipc		(void)	{enter(oldipc,		CLONE_NEWIPC);}
SCV	oldmnt		(void)	{enter(oldmnt,		CLONE_NEWNS);}
SCV	oldnet		(void)	{enter(oldnet,		CLONE_NEWNET);}
SCV	oldpid		(void)	{enter(oldpid,		CLONE_NEWPID);}
SCV	oldsem		(void)	{enter(oldsem,		CLONE_SYSVSEM);}
SCV	olduser		(void)	{enter(olduser,		CLONE_NEWUSER);}
SCV	olduts		(void)	{enter(olduts,		CLONE_NEWUTS);}

SCV	savecgroup	(void)	{save(savecgroup,	"/proc/self/ns/cgroup");}
/*
SCV	savefiles	(void)	{save(savefiles,	"/proc/self/ns/files");}
SCV	savefs		(void)	{save(savefs,		"/proc/self/ns/fs");}
*/
SCV	saveipc		(void)	{save(saveipc,		"/proc/self/ns/ipc");}
SCV	savemnt		(void)	{save(savemnt,		"/proc/self/ns/mnt");}
SCV	savenet		(void)	{save(savenet,		"/proc/self/ns/net");}
SCV	savepid		(void)	{save(savepid,		"/proc/self/ns/pid");}
SCV	savesem		(void)	{save(savesem,		"/proc/self/ns/sem");}
SCV	saveuser	(void)	{save(saveuser,		"/proc/self/ns/user");}
SCV	saveuts		(void)	{save(saveuts,		"/proc/self/ns/uts");}

static	void	_ns	(void)	{argot_next		();}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180614",
	.official=	"20180614",
	.update=	"20200625"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(_ns,		"ns");
	aa		(newcgroup,	"nsnewcgroup");
	aa		(newfiles,	"newfiles");
	aa		(newfs,		"newfs");
	aa		(newipc,	"nsnewipc");
	aa		(newmnt,	"nsnewmnt");
	aa		(newnet,	"nsnewnet");
	aa		(newpid,	"nsnewpid");
	aa		(newsem,	"nsnewsem");
	aa		(newuser,	"nsnewuser");
	aa		(newuts,	"nsnewuts");

	aa		(oldcgroup,	"nsoldcgroup");
/*	aa		(oldfiles,	"oldfiles");
	aa		(oldfs,		"oldfs");
*/
	aa		(oldipc,	"nsoldipc");
	aa		(oldmnt,	"nsoldmnt");
	aa		(oldnet,	"nsoldnet");
	aa		(oldpid,	"nsoldpid");
	aa		(oldsem,	"nsoldsem");
	aa		(olduser,	"nsolduser");
	aa		(olduts,	"nsolduts");

	aa		(savecgroup,	"nssavecgroup");
/*	aa		(savefiles,	"savefiles");
	aa		(savefs,	"savefs");
*/
	aa		(saveipc,	"nssaveipc");
	aa		(savemnt,	"nssavemnt");
	aa		(savenet,	"nssavenet");
	aa		(savepid,	"nssavepid");
	aa		(savesem,	"nssavesem");
	aa		(saveuser,	"nssaveuser");
	aa		(saveuts,	"nssaveuts");
	aa_fini		();
};

