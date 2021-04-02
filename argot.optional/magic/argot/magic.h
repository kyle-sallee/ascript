/*	By Kyle Sallee in 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_AMAGIC_H
#define		_A_AMAGIC_H
#include	<magic.h>

#define	MAGIC_DEFAULT	MAGIC_PRESERVE_ATIME|MAGIC_RAW|MAGIC_SYMLINK

SCV	magic_free	(VMETA *A)
{	magic_close	(A->value.p);
	var_free	(A);
}

static		void	show_byte	(VMETA *);
static		void	show_dub	(VMETA *);
static		void	show_name	(VMETA *);
static		void	show_all	(VMETA *);
static		void	show_apple	(VMETA *);
static		void	show_error	(VMETA *);
static		void	show_mime	(VMETA *);
static		void	show_text	(VMETA *);

__attribute__((always_inline))
static	inline	void	magicbytesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".magic",A);
	byteinit		(B);
	B->show=		show_byte;
	B->free=		magic_free;
	B->value.p=
	magic_open		(MAGIC_DEFAULT);
	map_add			(B,PAGE,0);
}

__attribute__((always_inline))
static	inline	void	magicdubsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".magic",A);
	byteinit		(B);
	B->show=		show_dub;
	B->free=		magic_free;
	B->value.p=
	magic_open		(MAGIC_DEFAULT);
	map_add			(B,PAGE,0);
}

__attribute__((always_inline))
static	inline	void	magicnamesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".magic",A);
	byteinit		(B);
	B->show=		show_name;
	B->free=		magic_free;
	B->value.p=
	magic_open		(MAGIC_DEFAULT);
	map_add			(B,PAGE,0);
}

__attribute__((always_inline))
static	inline	void	magicallsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".all",A);
	byteinit		(B);
	B->show=		show_all;
}

__attribute__((always_inline))
static	inline	void	magicapplesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".apple",A);
	byteinit		(B);
	B->show=		show_apple;
}

__attribute__((always_inline))
static	inline	void	magicerrorsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".error",A);
	byteinit		(B);
	B->show=		show_error;
}

__attribute__((always_inline))
static	inline	void	magicmimesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".mime",A);
	byteinit		(B);
	B->show=		show_mime;
}

__attribute__((always_inline))
static	inline	void	magictextsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".text",A);
	byteinit		(B);
	B->show=		show_text;
}
#endif
