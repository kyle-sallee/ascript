/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_DUB_H
#define		_A_DUB_H

/*
extern	OPERATOR	opdub[4];
*/

SCV	show_dubname			(VMETA *B)
{	VMETA		*A=		 B->host;
	if			yay	(A->io.flag&datamapuse)
	{	B->textaddr=		 A->dataaddr;
		B->textlen=		 A->datalen;
		return;
	}
	else
	B->textaddr=			B->text;

	Gz.out.den4			(A);

	__builtin_memcpy		(B->textaddr,
					 "/proc/self/fd/\0",0x10);
	__builtin_memcpy		(B->textaddr+0xe,
					 A->textaddr,8);
	B->textaddr[
	B->textlen=
	A->textlen+0xe]=		0;
}

#ifdef	__linux__
__attribute__((always_inline))
static	inline	void	dubmem_init	(VMETA *B)
{	B->io.flag|=	datamapuse;
	B->value.i=
	syscall		(SYS_memfd_create,"",MFD_ALLOW_SEALING|MFD_CLOEXEC);

}
#else
__attribute__((always_inline))
static	inline	void	dubmem_init	(VMETA *B)
{	B->io.flag|=	datamapuse;
	B->value.i=
	open		("/tmp",O_RDWR|O_TMPFILE,0600);
}
#endif

__attribute__((unused))
SCV	dubfree			(VMETA *A)
{	if		yay	(A->io.flag&datamapuse)
	{	int	a=	errna;
		close		(A->value.i);
		errna=		a;
	}
	var_free		(A);
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	dubfilesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".dub",A);
	B->op=			opdub;
	B->free=		dubfree;
	B->io.flag=		datamapuse;
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	dubtmpsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".dub",A);
	B->op=			opdub+1;
	B->free=		dubfree;
	B->io.flag=		datamapuse;
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	dubmemsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".dub",A);
	B->op=			opdub+2;
	B->free=		dubfree;
	dubmem_init		(B);
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	dubshmsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".dub",A);
	B->op=			opdub+3;
	B->free=		dubfree;
	B->io.flag=		datamapuse;
	map_add			(A,0,PAGE);
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	dubnamesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".name",A);
	byteinit		(B);
	B->show=		show_dubname;
	map_add			(B,PAGE,0);
}

/*
__attribute__((unused))
__attribute__((always_inline))
static	inline	void	dubpollanysubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".poll.any",A);
	B->op=			oppoll+2;
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	dubpollinsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".poll.in",A);
	B->op=			oppoll+0;
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	dubpolloutsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".poll.out",A);
	B->op=			oppoll+1;
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	dubpollprisubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".poll.pri",A);
	B->op=			oppoll+3;
}
*/
#endif
