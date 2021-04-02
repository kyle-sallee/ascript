/*	By Kyle Sallee in 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#define	rep0	void	(**L)	(void)=	Gz.at+1;	argot_next	();
#define	rep1	(*(Gz.at=L))	();
#define	rep2		rep1
#define	rep3	rep2	rep1
#define	rep4	rep3	rep1
#define rep5	rep4	rep1
#define rep6	rep5	rep1
#define rep7	rep6	rep1
#define rep8	rep7	rep1
#define rep9	rep8	rep1
#define repa	rep9	rep1
#define repb	repa	rep1
#define repc	repb	rep1
#define repd	repc	rep1
#define repe	repd	rep1
#define repf	repe	rep1
#define rep10	repf	rep1
#define rep20	rep10	rep10	rep1
#define	rep40	rep20	rep20	rep1
#define	rep80	rep40	rep40	rep1
#define	rep100	rep80	rep80	rep1

#define	NI	__attribute__((noinline))
#define	NIH	__attribute__((noinline))	__attribute__((hot))
#define	SHV	__attribute__((aligned(0x20)))	static	void

PALIGN
/*
NIH	SCV	re100_	(void)	{rep0	rep100	argot_next();}
*/
NIH	SCV	re10_	(void)	{rep0	rep10	argot_next();}
NIH	SCV	ref_	(void)	{rep0	repf	argot_next();}
NIH	SCV	ree_	(void)	{rep0	repe	argot_next();}
NIH	SCV	red_	(void)	{rep0	repd	argot_next();}
NIH	SCV	rec_	(void)	{rep0	repc	argot_next();}
NIH	SCV	reb_	(void)	{rep0	repb	argot_next();}
NIH	SCV	rea_	(void)	{rep0	repa	argot_next();}
NIH	SCV	re9_	(void)	{rep0	rep9	argot_next();}
NIH	SCV	re8_	(void)	{rep0	rep8	argot_next();}
NIH	SCV	re7_	(void)	{rep0	rep7	argot_next();}
NIH	SCV	re6_	(void)	{rep0	rep6	argot_next();}
NIH	SCV	re5_	(void)	{rep0	rep5	argot_next();}
NIH	SCV	re4_	(void)	{rep0	rep4	argot_next();}
NIH	SCV	re3_	(void)	{rep0	rep3	argot_next();}
NIH	SCV	re2_	(void)	{rep0	rep2	argot_next();}
NIH	SCV	re1_	(void)	{rep0	rep1	argot_next();}

/*
SHV		re100	(void)	{(*Gz.at=re100_)();}
*/
SHV		re10	(void)	{(*Gz.at=re10_)();}
SHV		ref	(void)	{(*Gz.at=ref_)();}
SHV		ree	(void)	{(*Gz.at=ree_)();}
SHV		red	(void)	{(*Gz.at=red_)();}
SHV		rec	(void)	{(*Gz.at=rec_)();}
SHV		reb	(void)	{(*Gz.at=reb_)();}
SHV		rea	(void)	{(*Gz.at=rea_)();}
SHV		re9	(void)	{(*Gz.at=re9_)();}
SHV		re8	(void)	{(*Gz.at=re8_)();}
SHV		re7	(void)	{(*Gz.at=re7_)();}
SHV		re6	(void)	{(*Gz.at=re6_)();}
SHV		re5	(void)	{(*Gz.at=re5_)();}
SHV		re4	(void)	{(*Gz.at=re4_)();}
SHV		re3	(void)	{(*Gz.at=re3_)();}
SHV		re2	(void)	{(*Gz.at=re2_)();}
__attribute__((unused))
SHV		re1	(void)	{(*Gz.at=re1_)();}
/*
SCV		re	(void)	{*Gz.at=re;argot_next	();}
*/

/*
const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20190529",
	.official=	"20190529",
	.update=	"20200922",
};
*/

SCV	re		(void)
{	static	uint8_t	did;
	*Gz.at=		re;
	if	nay	(did!=0)
	goto		done;

	did=		1;
	aa_init		();
	aa		(re,	"re");
	aa		(re10,	"re10");
	aa		(ref,	"ref");
	aa		(ree,	"ree");
	aa		(red,	"red");
	aa		(rec,	"rec");
	aa		(reb,	"reb");
	aa		(rea,	"rea");
	aa		(re9,	"re9");
	aa		(re8,	"re8");
	aa		(re7,	"re7");
	aa		(re6,	"re6");
	aa		(re5,	"re5");
	aa		(re4,	"re4");
	aa		(re3,	"re3");
	aa		(re2,	"re2");
	aa_fini		();
	done:
	argot_next	();
};
