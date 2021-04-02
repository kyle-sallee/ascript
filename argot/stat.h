/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_STAT_H
#define		_A_STAT_H
#include	"int.h"

/*
extern	OPERATOR	opstat[1];
*/

__attribute__((always_inline))
static	inline	 struct stat *	statbuf	(VMETA *A)
{	return	(struct stat *)	A->dataaddr;
}


SCV	reval_stat		(VMETA *A)
{	errna=			0;
	stat			(A->host->textaddr,statbuf(A));
	A->io.success=		errna;
}

SCV	reval_lstat		(VMETA *A)
{	errna=			0;
	lstat			(A->host->textaddr,statbuf(A));
	A->io.success=		errna;
}

SCV	reval_fstat		(VMETA *A)
{	errna=			0;
	fstat			(A->host->value.i,statbuf(A));
	A->io.success=		errna;
}

#define	SV	static	void

SV	reval_dev	(VMETA *A){A->value.i=statbuf(A)->st_dev;}
SV	reval_dev_major	(VMETA *A){A->value.i=major(statbuf(A)->st_dev);}
SV	reval_dev_minor	(VMETA *A){A->value.i=minor(statbuf(A)->st_dev);}

SV	reval_rdev	(VMETA *A){A->value.i=statbuf(A)->st_rdev;}
SV	reval_rdev_major(VMETA *A){A->value.i=major(statbuf(A)->st_rdev);}
SV	reval_rdev_minor(VMETA *A){A->value.i=minor(statbuf(A)->st_rdev);}

SV	reval_blksize	(VMETA *A){A->value.i=statbuf(A)->st_blksize;}
SV	reval_blocks	(VMETA *A){A->value.i=statbuf(A)->st_blocks;}
SV	reval_gid	(VMETA *A){A->value.i=statbuf(A)->st_gid;}
SV	reval_ino	(VMETA *A){A->value.i=statbuf(A)->st_ino;}
SV	reval_mode	(VMETA *A){A->value.i=statbuf(A)->st_mode&07777;}
/*
SV	reval_mode_permit(VMETA *A){A->value.i=statbuf(A)->st_mode&07777;}
*/
SV	reval_nlink	(VMETA *A){A->value.i=statbuf(A)->st_nlink;}
SV	reval_size	(VMETA *A){A->value.i=statbuf(A)->st_size;}
SV	reval_type	(VMETA *A){A->value.i=statbuf(A)->st_mode&S_IFMT;}
SV	reval_uid	(VMETA *A){A->value.i=statbuf(A)->st_uid;}

SV	reval_atim	(VMETA *A){A->value.i=statbuf(A)->st_atim.tv_sec;}
SV	reval_mtim	(VMETA *A){A->value.i=statbuf(A)->st_mtim.tv_sec;}
SV	reval_ctim	(VMETA *A){A->value.i=statbuf(A)->st_ctim.tv_sec;}

SV	reval_atim_nano	(VMETA *A){A->value.i=statbuf(A)->st_atim.tv_nsec;}
SV	reval_mtim_nano	(VMETA *A){A->value.i=statbuf(A)->st_mtim.tv_nsec;}
SV	reval_ctim_nano	(VMETA *A){A->value.i=statbuf(A)->st_ctim.tv_nsec;}

SCV	revise_size		(VMETA *B)
{	errna=			0;
	if			(B->host->value.i==0)
	{	show		(B->host);
		truncate	(B->host->textaddr,B->value.i);
	}
	else	ftruncate	(B->host->value.i,B->value.i);

	B->io.success=		errna;
}

SCV	revise_uid		(VMETA *B)
{	errna=			0;
	if			(B->host->value.i!=0)
	{	show		(B->host);
		chown		(B->host->textaddr,B->value.i,-1);
	}
	else	fchown		(B->host->value.i, B->value.i,-1);
	B->io.success=		errna;
}

SCV	revise_gid		(VMETA *B)
{	errna=			0;
	if			(B->host->value.i!=0)
	{	show		(B->host);
		chown		(B->host->textaddr,-1,B->value.i);
	}
	else	fchown		(B->host->value.i ,-1,B->value.i);
	B->io.success=		errna;
}

SCV	revise_mode		(VMETA *B)
{	errna=			0;
	if			(B->host->value.i!=0)
	{	show		(B->host);
		chmod		(B->host->textaddr,B->value.i);
	}
	else	fchmod		(B->host->value.i ,B->value.i);
	B->io.success=		errna;
}

SCV	revise_tim	(VMETA *B)
{	errna=		0;
	if		(B->host->value.i==0)
	utimensat	(AT_FDCWD,B->host->textaddr,&statbuf(B)->st_atim,0);
	else
	futimens	(B->host->value.i          ,&statbuf(B)->st_atim);
	B->io.success=	errna;
}

SCV	revise_as(VMETA *B){statbuf(B)->st_atim.tv_sec=B->value.i;revise_tim(B);}
SCV	revise_ms(VMETA *B){statbuf(B)->st_mtim.tv_sec=B->value.i;revise_tim(B);}
SCV	revise_an(VMETA *B){statbuf(B)->st_atim.tv_nsec=B->value.i;}
SCV	revise_mn(VMETA *B){statbuf(B)->st_mtim.tv_nsec=B->value.i;}

typedef	struct
{	uint8_t		name	[0x10][LABEL_SIZE];
	uint8_t		len	[0x10];
}	NODETYPE;

#define	nameset(a,b)	.name[a>>0xc]=b,	.len[a>>0xc]=strlen((b))

SCV	show_type		(VMETA *B)
{
	CALIGN	static	const	NODETYPE	t=
{	nameset		(S_IFSOCK,	"sock"),
	nameset		(S_IFLNK,	"link"),
	nameset		(S_IFREG,	"file"),
	nameset		(S_IFBLK,	"block"),
	nameset		(S_IFDIR,	"dir"),
	nameset		(S_IFCHR,	"char"),
	nameset		(S_IFIFO,	"sock"),
};

	uint32_t		c=	statbuf(B)->st_mode;
	B->textaddr=			(uint8_t *)	t.name	[c>>0xc];
	B->textlen=					t.len	[c>>0xc];
}

__attribute__((always_inline))
static	inline	void	statregsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".statreg",A);
	B->reval=		reval_stat;
	B->op=			opstat;
	map_add			(B,0,sizeof(struct stat));
}

__attribute__((always_inline))
static	inline	void	statsymsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".statsym",A);
	B->reval=		reval_lstat;
	B->op=			opstat;
	map_add			(B,0,sizeof(struct stat));
}

__attribute__((always_inline))
static	inline	void	statdubsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".statdub",A);
	B->reval=		reval_fstat;
	B->op=			opstat;
	B->value.i=		A->value.i;
	map_add			(B,0,sizeof(struct stat));
}

__attribute__((always_inline))
static	inline	void	st_devsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".dev",A);
	int8init		(B);
	dex8data		(B);
	B->show=		Gz.out.dex8;
	B->dataaddr=		A->dataaddr;
	B->reval=		reval_dev;
}

__attribute__((always_inline))
static	inline	void	st_dev_majorsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".dev.major",A);
	int8init		(B);
	dex8data		(B);
	B->show=		Gz.out.dex8;
	B->dataaddr=		A->dataaddr;
	B->reval=		reval_dev_major;
}

__attribute__((always_inline))
static	inline	void	st_dev_minorsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".dev.minor",A);
	int4init		(B);
	dex4data		(B);
	B->show=		Gz.out.dex4;
	B->dataaddr=		A->dataaddr;
	B->reval=		reval_dev_minor;
}

__attribute__((always_inline))
static	inline	void	st_gidsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".gid",A);
	int8init		(B);
	B->dataaddr=		A->dataaddr;
	B->reval=		reval_gid;
	B->revise=		revise_gid;
}

__attribute__((always_inline))
static	inline	void	st_blksizesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".blksize",A);
	int4init		(B);
	dex4data		(B);
	B->show=		Gz.out.dex4;
	B->dataaddr=		A->dataaddr;
	B->reval=		reval_blksize;
}

__attribute__((always_inline))
static	inline	void	st_blockssubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".blocks",A);
	int8init		(B);
	B->dataaddr=		A->dataaddr;
	B->reval=		reval_blocks;
}

__attribute__((always_inline))
static	inline	void	st_inosubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".ino",A);
	int8init		(B);
	dex4data		(B);
	B->show=		Gz.out.dex8;
	B->dataaddr=		A->dataaddr;
	B->reval=		reval_ino;
}

__attribute__((always_inline))
static	inline	void	st_modesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".mode",A);
	int4init		(B);
	oct4data		(B);
	B->show=		Gz.out.oct4;
	B->dataaddr=		A->dataaddr;
	B->reval=		reval_mode;
	B->revise=		revise_mode;
}

__attribute__((always_inline))
static	inline	void	st_nlinksubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".nlink",A);
	int4init		(B);
	B->dataaddr=		A->dataaddr;
	B->reval=		reval_nlink;
}

__attribute__((always_inline))
static	inline	void	st_rdevsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".rdev",A);
	int8init		(B);
	dex8data		(B);
	B->show=		Gz.out.dex8;
	B->dataaddr=		A->dataaddr;
	B->reval=		reval_rdev;
}

__attribute__((always_inline))
static	inline	void	st_rdev_majorsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".rdev.major",A);
	int4init		(B);
	dex4data		(B);
	B->show=		Gz.out.dex4;
	B->dataaddr=		A->dataaddr;
	B->reval=		reval_rdev_major;
}

__attribute__((always_inline))
static	inline	void	st_rdev_minorsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".rdev.minor",A);
	int4init		(B);
	dex4data		(B);
	B->show=		Gz.out.dex4;
	B->dataaddr=		A->dataaddr;
	B->reval=		reval_rdev_minor;
}

__attribute__((always_inline))
static	inline	void	st_sizesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".size",A);
	int8init		(B);
	B->dataaddr=		A->dataaddr;
	B->reval=		reval_size;
	B->revise=		revise_size;
}

__attribute__((always_inline))
static	inline	void	st_uidsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".uid",A);
	int8init		(B);
	B->dataaddr=		A->dataaddr;
	B->reval=		reval_uid;
	B->revise=		revise_uid;
}

__attribute__((always_inline))
static	inline	void	st_atim_tv_secsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".atim.sec",A);
	int8init		(B);
	B->dataaddr=		A->dataaddr;
	B->reval=		reval_atim;
	B->revise=		revise_as;
}

__attribute__((always_inline))
static	inline	void	st_atim_tv_nsecsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".atim.nano",A);
	int4init		(B);
	B->show=		Gz.out.nano;
	B->dataaddr=		A->dataaddr;
	B->reval=		reval_atim_nano;
	B->revise=		revise_an;
	nanodata		(B);
}

__attribute__((always_inline))
static	inline	void	st_mtim_tv_secsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".mtim.sec",A);
	int8init		(B);
	B->dataaddr=		A->dataaddr;
	B->reval=		reval_mtim;
	B->revise=		revise_ms;
}

__attribute__((always_inline))
static	inline	void	st_mtim_tv_nsecsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".mtim.nano",A);
	int4init		(B);
	B->show=		Gz.out.nano;
	B->dataaddr=		A->dataaddr;
	B->reval=		reval_mtim_nano;
	B->revise=		revise_mn;
	nanodata		(B);
}

__attribute__((always_inline))
static	inline	void	st_ctim_tv_secsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".ctim.sec",A);
	int8init		(B);
	B->dataaddr=		A->dataaddr;
	B->reval=		reval_ctim;
}

__attribute__((always_inline))
static	inline	void	st_ctim_tv_nsecsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".ctim.nano",A);
	int4init		(B);
	B->show=		Gz.out.nano;
	B->dataaddr=		A->dataaddr;
	B->reval=		reval_ctim_nano;
	nanodata		(B);
}

__attribute__((always_inline))
static	inline	void	st_typesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".type",A);
	byteinit		(B);
	B->dataaddr=		A->dataaddr;
	B->show=		show_type;
	B->reval=		reval_type;
}
#endif
