/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_CPIONEWC_H
#define		_A_CPIONEWC_H
#include	<sys/mount.h>
#include	"byte.h"
#include	"stat.h"

extern	OPERATOR	opcpionewc[1];

typedef	struct
{	uint8_t		magic		[6];
	uint8_t		ino		[8];
	uint8_t		mode		[8];
	uint8_t		uid		[8];
	uint8_t		gid		[8];
	uint8_t		nlink		[8];
	uint8_t		mtime		[8];
	uint8_t		size		[8];
	uint8_t		devmajor	[8];
	uint8_t		devminor	[8];
	uint8_t		rdevmajor	[8];
	uint8_t		rdevminor	[8];
	uint8_t		namelen		[8];
	uint8_t		empty		[8];
}	NEWC;

typedef	struct
{	uint8_t		*name;
	void		*same;
	struct stat	buf;
	uint8_t		counted;
}	NODEMETA;

typedef	struct
{	uint8_t		safename	[PATH_MAX];
	NEWC		newc;
}	OUTDATA;

	struct	SEEN_T;
typedef	struct	SEEN_T	SEEN;

typedef	struct	SEEN_T
{	uint8_t		name	[PATH_MAX];
	SEEN		*next;
	ino_t		ino;
	dev_t		dev;
	int		len;
}	SEEN;

typedef	struct
{	uint8_t			*name;
	uint8_t			*data;
	NEWC			c;
	struct	stat		s;
	size_t			off;
	size_t			off_old;
	SEEN			*seen;
	VMETA			*vardata,*varhead,*varname,*varstat;
	struct	timespec	T[2];
	uint16_t		namelen;
}	CPIODATA;

__attribute__((always_inline))
static	inline	 CPIODATA *	cpiodata	(VMETA *A)
{	return	(CPIODATA *)	A->dataaddr;
}

/*	The following was gleaned from the cpio.5 manual page */
/*	magic is 070701
	header + pathname + pad until divisible by 4.
	file data         + pad until divisible by 4.
	For  hard linked files size is 0 until the last link.
	The archive end is indicated with special record with
	the pathname TRAILER!!!
*/

/*	The following was gleaned from looking at a cpio file */
/*	The namelen includes the termination 0 byte in the count.
	The trailer record has magic, 0 for all fields except link
	and namelen.  link count is 1.  namelen is B.
	The numbers are odd, it's not little endian nor big endian.
	It's ASCII hexadecimal representation with capital letters.
	That explains the size limitation.
	Terrible format!
	Waste of CPU cycles!
*/

__attribute__((unused))
static	CALIGN	void	cpionewcfree	(VMETA *A)
{	CPIODATA	*a=
	cpiodata		(A);
	SEEN		*b,*c;
	for			(b=a->seen;b;b=c)
	{	c=		 b->next;
		munmap		(b,sizeof(SEEN));
	}
	munmap			(A->textaddr,A->textsize);
	vmeta_free		(A);
}

static	void	show_cpionewc	(VMETA *);

__attribute__((always_inline))
static	inline	void	cpionewcsubnew	(VMETA *A)
{	A->op=			opcpionewc;
	A->show=		show_cpionewc;
	A->free=		cpionewcfree;
	map_add			(A,HUGE,sizeof(CPIODATA));
	CPIODATA	*a=
	cpiodata		(A);
	__builtin_memcpy	(a->c.magic,"070701",6);
}

__attribute__((always_inline))
static	inline	void	cpionewcdatasubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".data",A);
	byteinit		(B);
	CPIODATA	*a=
	cpiodata		(A);
	a->vardata=		B;
}

__attribute__((always_inline))
static	inline	void	cpionewcheadsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".head",A);
	byteinit		(B);
	CPIODATA	*a=
	cpiodata		(A);
	a->varhead=		B;
}

__attribute__((always_inline))
static	inline	void	cpionewcnamesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".name",A);
	byteinit		(B);
	cpiodata(A)->varname=	B;
}

__attribute__((always_inline))
static	inline	void	cpionewcstatsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".stat",A);
	B->op=			opstat;
	CPIODATA	*a=
	cpiodata		(A);
	a->varstat=		B;
	B->dataaddr=		(void *)	&a->s;
	B->host=		a->varname;
}
#endif
