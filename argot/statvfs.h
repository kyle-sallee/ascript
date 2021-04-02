/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_STATVFS_H
#define		_A_STATVFS_H
#include	<sys/statvfs.h>

/*
extern	OPERATOR	opstatvfs[1];
*/

#define	PPALIGN	__attribute__((aligned(0x10)))

__attribute__((always_inline))
static	inline	 struct statvfs *	statvfsbuf	(VMETA *A)
{	return	(struct statvfs *)	A->dataaddr;
}

SCV	reval_statvfs_byte	(VMETA *B)
{	errna=			0;
	struct	statvfs	*a=
	statvfsbuf		(B);
	statvfs			(B->host->textaddr,a);
	B->io.success=		errna;
}

SCV	reval_statvfs_dub	(VMETA *B)
{	errna=			0;
	struct	statvfs	*a=
	statvfsbuf		(B);
	fstatvfs		(B->host->value.i,a);
	B->io.success=		errna;
}

#define	SPV	static	PPALIGN	void

SPV	reval_bsize	(VMETA *C){C->value.i=statvfsbuf(C)->f_bsize;}
SPV	reval_frsize	(VMETA *C){C->value.i=statvfsbuf(C)->f_frsize;}
SPV	reval_blocks	(VMETA *C){C->value.i=statvfsbuf(C)->f_blocks;}
SPV	reval_bfree	(VMETA *C){C->value.i=statvfsbuf(C)->f_bfree;}
SPV	reval_bavail	(VMETA *C){C->value.i=statvfsbuf(C)->f_bavail;}
SPV	reval_files	(VMETA *C){C->value.i=statvfsbuf(C)->f_files;}
SPV	reval_ffree	(VMETA *C){C->value.i=statvfsbuf(C)->f_ffree;}
SPV	reval_favail	(VMETA *C){C->value.i=statvfsbuf(C)->f_favail;}
SPV	reval_fsid	(VMETA *C){C->value.i=statvfsbuf(C)->f_fsid;}
SPV	reval_flag	(VMETA *C){C->value.i=statvfsbuf(C)->f_flag;}
SPV	reval_namemax	(VMETA *C){C->value.i=statvfsbuf(C)->f_namemax;}

/*
SPV	reval_ftype	(VMETA *C){C->value.i=	statvfsbuf(C)->f_ftype;}
*/

static	inline	void	statvfssubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".statvfs",A);
	B->op=			opstatvfs;
	map_add			(B,0,sizeof(struct statvfs));
	if			(A->op->byte_compat)
	B->reval=		reval_statvfs_byte;
	else
	B->reval=		reval_statvfs_dub;
}

static	inline	void	f_bavailsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".f_bavail",A);
	int8init		(B);
	dex8data		(B);
	B->show=		Gz.out.dex8;
	B->dataaddr=		A->dataaddr;
	B->host=		A->host;
	B->reval=		reval_bavail;
}

static	inline	void	f_bfreesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".f_bfree",A);
	int8init		(B);
	dex8data		(B);
	B->show=		Gz.out.dex8;
	B->dataaddr=		A->dataaddr;
	B->host=		A->host;
	B->reval=		reval_bfree;
}

static	inline	void	f_blockssubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".f_blocks",A);
	int8init		(B);
	dex8data		(B);
	B->show=		Gz.out.dex8;
	B->dataaddr=		A->dataaddr;
	B->host=		A->host;
	B->reval=		reval_blocks;
}

static	inline	void	f_bsizesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".f_bsize",A);
	int8init		(B);
	dex8data		(B);
	B->show=		Gz.out.dex8;
	B->dataaddr=		A->dataaddr;
	B->host=		A->host;
	B->reval=		reval_bsize;
}

static	inline	void	f_favailsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".f_favail",A);
	int8init		(B);
	dex8data		(B);
	B->show=		Gz.out.dex8;
	B->dataaddr=		A->dataaddr;
	B->host=		A->host;
	B->reval=		reval_favail;
}

static	inline	void	f_ffreesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".f_ffree",A);
	int8init		(B);
	dex8data		(B);
	B->show=		Gz.out.dex8;
	B->dataaddr=		A->dataaddr;
	B->host=		A->host;
	B->reval=		reval_ffree;
}

static	inline	void	f_filessubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".f_files",A);
	int8init		(B);
	dex8data		(B);
	B->show=		Gz.out.dex8;
	B->dataaddr=		A->dataaddr;
	B->host=		A->host;
	B->reval=		reval_files;
}

static	inline	void	f_flagssubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".f_flags",A);
	int8init		(B);
	dex8data		(B);
	B->dataaddr=		A->dataaddr;
	B->host=		A->host;
	B->reval=		reval_flag;
}

static	inline	void	f_frsizesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".f_frsize",A);
	int8init		(B);
	dex8data		(B);
	B->show=		Gz.out.dex8;
	B->dataaddr=		A->dataaddr;
	B->host=		A->host;
	B->reval=		reval_frsize;
}

static	inline	void	f_fsidsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".f_fsid",A);
	int8init		(B);
	dex8data		(B);
	B->show=		Gz.out.dex8;
	B->dataaddr=		A->dataaddr;
	B->host=		A->host;
	B->reval=		reval_fsid;
}

static	inline	void	f_namemaxsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".f_namemax",A);
	int4init		(B);
	B->dataaddr=		A->dataaddr;
	B->host=		A->host;
	B->reval=		reval_namemax;
}
#endif
