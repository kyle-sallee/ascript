/*	By Kyle Sallee in 2015 through 2020 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_ASCRIPT_H
#define		_ASCRIPT_H

#ifndef		_GNU_SOURCE	/* for dup3 if available */
#define		_GNU_SOURCE	/* before unistd.h */
#endif

#ifndef		_POSIX_C_SOURCE
#define		_POSIX_C_SOURCE	200809L	/* for renameat2 */
#endif

#define		as_string(a)	as_named(a)
#define		as_named(a)	#a

#include	<err.h>
#include	<errno.h>
#include	<dirent.h>
#include	<fcntl.h>
#include	<limits.h>		/*	PATH_MAX	*/
#include	<poll.h>		/* to wrap poll */
#include	<signal.h>
#include	<stdatomic.h>
#include	<stdint.h>		/*	uint32_t	*/
#include	<string.h>
#include	<sys/ioctl.h>
#include	<sys/mman.h>
#include	<sys/socket.h>
#include	<sys/stat.h>
#include	<sys/syscall.h>
#include	<sys/time.h>
#include	<sys/types.h>
#include	<time.h>
#include	<unistd.h>

#define		_FILE_OFFSET_BITS	64

/*
With glibc provided fts_* functions
#define		_FILE_OFFSET_BITS	64
#define		_LARGEFILE64_SOURCE
are incompatible.

Fortunately,
by decent argot hackers
fts_* functions
are not required.
*/

/*
#define		_LARGEFILE64_SOURCE
*/

/*	in /usr/include/features.h
#define	_LARGEFILE64_SOURCE
exists
*/

/*	At 0x100 for internal use descriptors begin.
*/

/*
*_MAX
if changed
ascript and all argot
must be recompiled.
*/

#define		DATA_MAX	0x4000000	/* 64M script data */
#define		POOL_MAX	0x4000000	/* 64M already mapped pages */
#define		PART_MAX	0x100000	/* 1M parsed parts */
#define		VLESS_MAX	0x100000	/* 1M VLESS * 64 bytes  */
#define		PART_REFER_MAX	0x40000		/* 1/4M near/far * 32 bytes */
#define		VMETA_MAX	0x40000		/* 1/4M var * 256 bytes */
#define		ZYGOTE_MAX	0x40000		/* 1/4M zyg * 32 or 64 bytes */
#define		ARGOT_MAX	0x1000		/* 4096 argot can load */
#define		SCRATCH_MAX	0x10000

/* The following defines aught not be changed. */

#define		FDHIGH		0x100
#define		ENV_MAX		0x100		/* environment var max */
#define		ARGC_MAX	0x100
#define		LONG		8		/* do not change */
#define		HUGE		0x200000L	/* do not change */
#define		PAGE		0x1000L		/* do not change */
#define		ENV_BYTE_MAX	0x20*PAGE	/* Linux thing do not change */

/* paragraph */
#define		PARA		0x10		/* do not change */

/* common CPU cache line length */
#define		CLEN		0x40		/* do not change */

#define		PALIGN		__attribute__((aligned(PAGE)))
#define		HALIGN		__attribute__((aligned(HUGE)))
#define		LALIGN		__attribute__((aligned(LONG)))
#define		CALIGN		__attribute__((aligned(CLEN)))

#define		SCV	static	CALIGN	void
#define		ALIVE	__attribute__((always_inline)) static inline void

typedef	uintptr_t	farint;

/*	Using val, with a single cmp
	all 8 bytes in text are compared
*/
typedef	union
{	uint8_t		text[8];
	uint64_t	val;
}	text8;

typedef	union
{	uint8_t		text[4];
	uint32_t	val;
}	text4;

/*
enum	READYVAL
{	ready_not,
	ready_int,
	ready_dec,
	ready_address,
};
*/

#define		VAR_TYPE_MAX	0x200		/* 0x200 or 0x400 */
#define		VAR_NAME_SIZE	0x20		/* do not change */
#define		ARGOT_NAME_SIZE	0x10		/* do not change */
#define		LABEL_SIZE	0x10		/* do not change */

/*	VAR_NAME_SIZE sans remainder divisble by 16
	when not varname_match will not properly work.
	Thus do not expect changing defined lengths
	will produce fast or even runable code.
	Why?
	Vectors!
*/

/*	Compiler assumptions might not suffice.	*/

#if		defined (__GNUC__)||defined (__LLVM__)||defined (__CLANG__)
#define		yay(x)	(__builtin_expect((x),1))
#define		nay(x)	(__builtin_expect((x),0))
#define		NAY(x)	(__builtin_expect_with_probability((x),0,0.99))

#define		prefetch(x...)	__builtin_prefetch(x)
#define		impossible(x)	if	((x))	{__builtin_unreachable();}
#else
#define		yay(x)	(x)
#define		nay(x)	(x)
#define		prefetch(x...)
#define		impossible(x)
#warning	"gcc/llvm provided __builtin_expect is unavailable."
#endif

/*	In the cache
	anywhere but page start
	frequently accessed data
	often remains.

	On stack
	the data
	when backed
	in the cache also
	the data often resides.
	Explicit prefetch is seldom useful.
*/

#define		MIN(a,b)	(((a)<(b))?(a):(b))
#define		MAX(a,b)	(((a)>(b))?(a):(b))

	struct	VMETA_T;
typedef	struct	VMETA_T	VMETA;

typedef	struct
{
/*	void	(*mapuse[2])	(VMETA *);	*/
	uint8_t	int_compat;
	uint8_t	int4_compat;
	uint8_t	int8_compat;
	uint8_t	byte_compat;
	uint8_t	pathname_compat;

	void	(*data)		(VMETA *);	/* dataaddr content update */
	void	(*fromtext)	(VMETA *);
	void	(*set)		(void);
	void	(*equal)	(void);
	void	(*add)		(void);
	void	(*sub)		(void);
	void	(*addadd)	(void);
	void	(*subsub)	(void);

	void	(*or)		(void);
	void	(*and)		(void);
	void	(*div)		(void);
	void	(*mod)		(void);

	void	(*mul)		(void);
	void	(*not)		(void);
	void	(*xor)		(void);

	void	(*shr)		(void);
	void	(*shl)		(void);
	void	(*rcr)		(void);
	void	(*rcl)		(void);

	void	(*at)		(void);
	void	(*query)	(void);

	void	(*equalequal)	(void);
	void	(*notequal)	(void);
	void	(*less)		(void);
	void	(*lessequal)	(void);
	void	(*more)		(void);
	void	(*moreequal)	(void);
/*	void	(*tell)		(VMETA **);	*/

	/* by sub var the host var value aft revision,
	   such as a.uid revised by a.uid.user, by node uid
	   to the revised value the node's uid can be updated. */
}	OPERATOR;

/*
Through the PLT/GOT
some operator addresses
are not conveyed
*/

typedef	struct
{	OPERATOR	ref		[1],	/* argot parameter var name */
			value		[1],	/* argot parmaeter value */
			vconst		[1],	/* argot parmaeter `text` */
			near		[1],	/* argot parameter 'label' */
			far		[1],	/* argot parameter "label" */

			ambit		[1],
			byte		[1],
			byteconst	[1],
			vchar		[1],	/* opchar */

			int4		[1],	/* 4-byte int */
			int8		[1],	/* 8-byte int */
			fix8		[1],	/* 8-byte fixed point */

			dub		[4],
			env		[1],
			kvp		[3],
			list		[4],
			nodelist	[1],

			para		[1],
			pathname	[2],
			ray		[2],
			rlimit		[2],
			rusage		[3],
			sig		[1],
			size		[1],
			stat		[1],
			statvfs		[1],
			tm		[1],
			trim		[5],
			view		[3];
}	COMMON_OP;

#define		opacfg			Gz.op.acfg
#define		opref			Gz.op.ref
#define		opvalue			Gz.op.value
#define		opconst			Gz.op.vconst
#define		opnear			Gz.op.near
#define		opfar			Gz.op.far
#define		opambit			Gz.op.ambit
#define		opbyte			Gz.op.byte
#define		opbyteconst		Gz.op.byteconst
#define		opchar			Gz.op.vchar

#define		opint4			Gz.op.int4
#define		opint8			Gz.op.int8
#define		opfix8			Gz.op.fix8

#define		opdub			Gz.op.dub
#define		openv			Gz.op.env
#define		opkvp			Gz.op.kvp
#define		oplist			Gz.op.list
#define		opnodelist		Gz.op.nodelist
#define		oppara			Gz.op.para
#define		oppathname		Gz.op.pathname
#define		opray			Gz.op.ray
#define		oprlimit		Gz.op.rlimit
#define		oprusage		Gz.op.rusage
#define		opsig			Gz.op.sig
#define		opsize			Gz.op.size
#define		opstat			Gz.op.stat
#define		opstatvfs		Gz.op.statvfs
#define		optm			Gz.op.tm
#define		optrim			Gz.op.trim
#define		opview			Gz.op.view

/*	By a gpg public key
	no less than 1864 bytes would be required.
	Thus a 2048 byte uint8_t array would suffice
	A bit large for argot information?
*/

/*
Depending upon compilation
in argot ELF libraries
at runtime
fstat might not resolve.
A segfault might result
The solution below is not good.
*/

/*
#ifdef	__NR_fstat64
#define	fstat(fd,buf)	syscall	(__NR_fstat64,fd,buf)
#define	stat(pn,buf)	syscall	(__NR_stat64,pn,buf)
#define	lstat(pn,buf)	syscall	(__NR_lstat64,pn,buf)
#else
#define	fstat(fd,buf)	syscall	(__NR_fstat,fd,buf)
#define	stat(pn,buf)	syscall	(__NR_stat,pn,buf)
#define	lstat(pn,buf)	syscall	(__NR_lstat,pn,buf)
#endif
*/
typedef	struct
{	CALIGN
	uint8_t		author		[0x40];	/* never changes */
	uint8_t		author_email	[0x40];	/* if author wants */
	uint8_t		contact		[0x40];	/* Bug report person */
	uint8_t		contact_email	[0x40];	/* bug report email address */
	uint8_t		homepage	[0x40];	/* gloat website page */
	uint8_t		create		[8];	/* creation date */
	uint8_t		official	[8];	/* official date */
	uint8_t		update		[8];	/* update   date */
	/*	A date would be like 20170922. */
	/*	If official then Kyle Sallee wrote it or
		maintainership was annexed.
	*/
}	ARGOT_INFO;

struct		ARGOT_T;
typedef	struct	ARGOT_T		ARGOT;

typedef	struct	ARGOT_T
{	__attribute__((aligned(0x20)))
	void			(*at)	(void);
	ARGOT			*fore;
	__attribute__((aligned(0x10)))
	uint8_t			name	[ARGOT_NAME_SIZE];
}	ARGOT;

#if	__BYTE_ORDER__	==	__ORDER_LITTLE_ENDIAN__
typedef	union
{	int32_t		l;
	int32_t		h;
}	ui4;
#else
typedef	union
{	int32_t		h;
	int32_t		l;
}	ui4;
#endif

typedef	union
{	int64_t		i;
	ui4		i4;
	uint8_t		t[8];
	void		*p;
	uint8_t		b;
}	VALUE;

/* ordered, grouped, sized, to maximize cache benefit */

typedef	struct	__attribute__((packed))
{	uint16_t	map;		/* descriptor backed map */
	uint16_t	log;		/* write descriptor */
	uint16_t	sip;		/* read  descriptor */
	uint8_t		flag;		/* use and unmap bits */
	uint8_t		success;	/* often errno copied; 0==success */
}	IO;

#define	textmapuse	0x1
#define	textmapunmap	0x2
#define	datamapuse	0x10
#define	datamapunmap	0x20

typedef	struct	VMETA_T
{	__attribute__((aligned(0x80)))
	VMETA		**vam;
	VMETA		*fore;		/* next var in same vam slot */
	OPERATOR	*op;
	uint8_t		*textaddr;
	uint32_t	textlen;	/* current byte amount */

	VALUE		value;		/* 64-bit int, double, or pointer */
	void		(*show)		(VMETA *);/* textaddr     populate */
	void		(*reval)	(VMETA *);/* value.i      adjust   */
	/* 62 bytes */

	void		(*revise)	(VMETA *);/* value.i  was adjusted */
	VMETA		*link_head;
	VMETA		*link_back;
	VMETA		*link_next;
	VMETA		*trash;
	IO		io;		/* 8 bytes */
	void		(*free)		(VMETA *);
	VMETA		*host;
	/* 64 bytes */

	uint8_t		*dataaddr;
	uint32_t	datalen;	/* current byte amount */
	uint32_t	datasize;	/* map size */
	uint32_t	textsize;	/* max capacity */
	uint8_t		len;		/* bytes in name */
	/* 21 bytes */

	__attribute__((aligned(0x20)))
	uint8_t		name		[VAR_NAME_SIZE];
	/* 32 bytes */

	__attribute__((aligned(0x20)))
	uint8_t		text[0x20];	/* 32 bytes */
	/* 32 bytes  */

}	VMETA;	/* 256 bytes */

typedef	struct	VLESS_T
{	__attribute__((aligned(0x10)))
	VMETA		**vam;
	VMETA		*fore;		/* next var in same vam slot */
	OPERATOR	*op;
	uint8_t		*textaddr;
	uint32_t	textlen;
	VALUE		value;		/* 64-bit int, double, or pointer */
	void		(*show)		(VMETA *);/* textaddr     populate */
	void		(*reval)	(VMETA *);/* value.i      adjust   */
}	VLESS;	/* 64 bytes */

/*
struct		PART_STRUCT;
typedef	struct	PART_STRUCT		PART;
*/

struct		PART_REFER_STRUCT;
typedef	struct	PART_REFER_STRUCT	PART_REFER;

typedef struct
{	void		(**head)	(void);
	uint8_t		*file_head;
	uint8_t		*file_name;
	uint32_t	 file_size;
}	ZYGOTE;

typedef	struct	PART_REFER_STRUCT
{	__attribute__((aligned(0x20)))
	uint8_t		name	[LABEL_SIZE];	/* 0x10 bytes */
	PART_REFER	*fore;			/* next in Gz.farm or Gz.nearm*/
	void		(**part)	(void);
}	PART_REFER;

typedef	struct
{	PALIGN
	uint8_t		exit	[0x400000];
	 int8_t		done	[0x400000];
	uint8_t		stop	[0x400000];
	void		(**pin	[0x400000])	(void);
	VMETA		*target	[0x400000];
	VMETA		*origin	[0x400000];

	int64_t		last;
	int		now;	/* progeny process count */
	uint8_t		skip;	/* if non zero then skip */
	uint8_t		miss;	/* when skipped then non zero */
}	PIDS;

typedef	struct
{	PALIGN
	uint8_t		p[2]	[PAGE];	/* argot path construnction area */
	void		*v;		/* loaded library handle */
	int		d[2];		/* argot load directory descriptor */
}	AP;				/* argot file path */

#define		MNV		0x80000-1

typedef	struct		ENDPART_S
{	VMETA			*to[2];	/* target and origin */
	void			(**L)	(void);
	struct	ENDPART_S	*F;
}	ENDPART;

typedef	struct
{	CALIGN	union
	{	uint32_t	w	[10000];
		uint8_t		b	[40000];
	}	full;

	CALIGN	union
	{	uint32_t	w	[10000];
		uint8_t		b	[40000];
	}	left;

	CALIGN	uint8_t		next	[10000];
}	DENT;

typedef	struct
{	PALIGN	uint32_t	left[0x10000];
		uint32_t	full[0x10000];
		uint32_t	Left[0x10000];
		uint32_t	Full[0x10000];
		uint8_t		next[0x10000];
}	HEXT;

typedef	struct
{	PALIGN
	void	(*bin4)		(VMETA *);
	void	(*bin8)		(VMETA *);
	void	(*den4)		(VMETA *);
	void	(*den8)		(VMETA *);
	void	(*fix8)		(VMETA *);
	void	(*dex4)		(VMETA *);
	void	(*Dex4)		(VMETA *);
	void	(*dex8)		(VMETA *);
	void	(*Dex8)		(VMETA *);
	void	(*oct2)		(VMETA *);
	void	(*oct4)		(VMETA *);
	void	(*oct8)		(VMETA *);
	void	(*nano)		(VMETA *);
	void	(*time)		(VMETA *);

	int8_t	(*asden)	(uint8_t *,uint64_t *);
/*	void	(*inbin)	(VMETA *);
	void	(*infix)	(VMETA *);
	void	(*index)	(VMETA *);
	void	(*inoct)	(VMETA *);
*/
	uint8_t	(*uden32)	(uint8_t *,uint32_t b);
}	DENF;

typedef	struct
{	PALIGN
	int8_t		xX[0x100];
	DENT		den;
	HEXT		hex;
	CALIGN
	uint32_t	oct[0x1000];
}	DHTABLE;

typedef	struct
{	VMETA		*a;	/* base */
	uint8_t		b;	/* available bytes */
	uint8_t		c;	/* if 1 already in use */
}	VMETA_POOL;

typedef	struct
{	uint8_t		index;	/* index value */
	uint8_t		done;	/* bit set when done */
}	VMETAM;

	struct	TAG_T;
typedef	struct	TAG_T	TAG;

typedef	struct	TAG_T
{	__attribute__((aligned(0x10)))
	uint8_t		name	[LABEL_SIZE*4];
}		TAG;

typedef	struct
{	uint8_t		**v;	/* for process argv */
	VMETA		*a;	/* VLESS map address */
	uint32_t	c;	/* for process argc */
}	ARG;

typedef	struct
{	void		*a;	/* next  page    address */
	uint32_t	b;	/* total bytes   remaining */
	uint8_t		c;	/* if not 0 mmap invoke */
}	PAGE_POOL;

typedef	struct
{	void	 (*adef0)	(void);
	int	 (*chdir)	(const char *);
	int	 (*chmod)	(const char *,mode_t);
	int	 (*chown)	(const char *,uid_t,gid_t);
	int	 (*close)	(int);
	int	 (*closedir)	(DIR *);
	int	 (*dup2)	(int,int);
	int	 (*fchdir)	(int);
	int	 (*fchmod)	(int,mode_t);
	int	 (*fchown)	(int,uid_t,gid_t);
	int	 (*fcntl)	(int,int,...);
	DIR	*(*fdopendir)	(int);
	int	 (*fstat)	(int,struct stat *);
	int	 (*ftruncate)	(int,off_t);
	uid_t	 (*geteuid)	(void);
	pid_t	 (*getpid)	(void);
	uid_t	 (*getuid)	(void);
	int	 (*ioctl)	(int,unsigned long,...);
	off_t	 (*lseek)	(int, off_t, int);
	int	 (*lstat)	(const char *,struct stat *);
	int	 (*madvise)	(void *,size_t,int);
	int	 (*memcmp)	(const void *,const void *, size_t);
	int	 (*mkdir)	(char const *,mode_t);
	void	*(*mmap)	(void *,size_t,int,int,int,off_t);
	int	 (*mprotect)	(void *,size_t,int);
	void	*(*mremap)	(void *,size_t,size_t,int,...);
	int	 (*munmap)	(void *,size_t);
	int	 (*open)	(char const *,int,...);
	int	 (*poll)	(struct pollfd *,nfds_t,int);
	ssize_t	 (*read)	(int,void const *,size_t);
	ssize_t	 (*recv)	(int,void const *,size_t,int);
	struct dirent
		*(*readdir)	(DIR *);
	int	 (*sigaction)	(int,struct sigaction const *,struct sigaction *);
	int	 (*sigqueue)	(pid_t,int,const union sigval);
	int	 (*snprintf)	(char *,size_t,char const *,...);
	int	 (*sprintf)	(char *,char const *,...);
	int	 (*stat)	(const char *,struct stat *);
	ssize_t	 (*write)	(int,void const *,size_t);
	ssize_t	 (*writeall)	(int,void const *,uint32_t);
	ssize_t	 (*send)	(int,void const *,size_t,int);
	ssize_t	 (*sendall)	(int,void const *,size_t,int);
	void	 (*text_adjust)	(VMETA *,uint32_t);
	void	*(*pps)		(uint32_t);
	void	*(*pp)		(void);
/*	long	 (*syscall)	(long,...);	*/
	void	 (*var_free)	(VMETA *);
/*	VMETA	*(*vmeta_new)	(void);		*/
	ZYGOTE	*(*zygote_init)	(uint8_t const *);
}	AIDE;

#define		chdir(...)		Gz.aide.chdir		(__VA_ARGS__)
#define		chmod(...)		Gz.aide.chmod		(__VA_ARGS__)
#define		chown(...)		Gz.aide.chown		(__VA_ARGS__)
#define		close(...)		Gz.aide.close		(__VA_ARGS__)
#define		closedir(...)		Gz.aide.closedir	(__VA_ARGS__)
#define		dup2(...)		Gz.aide.dup2		(__VA_ARGS__)
#define		fchdir(...)		Gz.aide.fchdir		(__VA_ARGS__)
#define		fchmod(...)		Gz.aide.fchmod		(__VA_ARGS__)
#define		fchown(...)		Gz.aide.fchown		(__VA_ARGS__)
#define		fcntl(...)		Gz.aide.fcntl		(__VA_ARGS__)
#define		fdopendir(...)		Gz.aide.fdopendir	(__VA_ARGS__)
/*
#define		fstat(...)		Gz.aide.fstat		(__VA_ARGS__)
*/
#define		ftruncate(...)		Gz.aide.ftruncate	(__VA_ARGS__)
#define		geteuid(...)		Gz.aide.geteuid		(__VA_ARGS__)
#define		getpid(...)		Gz.aide.getpid		(__VA_ARGS__)
#define		getuid(...)		Gz.aide.getuid		(__VA_ARGS__)
#define		ioctl(...)		Gz.aide.ioctl		(__VA_ARGS__)
#define		lseek(...)		Gz.aide.lseek		(__VA_ARGS__)
/*
#define		lstat(...)		Gz.aide.lstat		(__VA_ARGS__)
*/
#define		madvise(...)		Gz.aide.madvise		(__VA_ARGS__)
#define		memcmp(...)		Gz.aide.memcmp		(__VA_ARGS__)
#define		mkdir(...)		Gz.aide.mkdir		(__VA_ARGS__)
#define		mmap(...)		Gz.aide.mmap		(__VA_ARGS__)
#define		mprotect(...)		Gz.aide.mprotect	(__VA_ARGS__)
#define		mremap(...)		Gz.aide.mremap		(__VA_ARGS__)
#define		munmap(...)		Gz.aide.munmap		(__VA_ARGS__)
#define		open(...)		Gz.aide.open		(__VA_ARGS__)
#define		poll(...)		Gz.aide.poll		(__VA_ARGS__)
#define		read(...)		Gz.aide.read		(__VA_ARGS__)
#define		recv(...)		Gz.aide.recv		(__VA_ARGS__)
#define		readdir(...)		Gz.aide.readdir		(__VA_ARGS__)
/*
#define		snprintf(...)		Gz.aide.snprintf	(__VA_ARGS__)
#define		sprintf(...)		Gz.aide.sprintf		(__VA_ARGS__)
*/
#define		sigaction(...)		Gz.aide.sigaction	(__VA_ARGS__)
#define		sigqueue(...)		Gz.aide.sigqueue	(__VA_ARGS__)
/*
#define		stat(...)		Gz.aide.stat		(__VA_ARGS__)
*/
#define		write(...)		Gz.aide.write		(__VA_ARGS__)
#define		writeall(...)		Gz.aide.writeall	(__VA_ARGS__)
#define		send(...)		Gz.aide.send		(__VA_ARGS__)
#define		sendall(...)		Gz.aide.sendall		(__VA_ARGS__)

#define		text_adjust(...)	Gz.aide.text_adjust	(__VA_ARGS__)
#define		pp(...)			Gz.aide.pp		(__VA_ARGS__)
#define		pps(...)		Gz.aide.pps		(__VA_ARGS__)

/*
To a C library provided function syscall when resolved
what point exists in even wrapping it?
It is not a direct kernel invocation.
It will not be any faster!
*/

/*
#define		syscall(...)		Gz.aide.syscall		(__VA_ARGS__)
*/

#define		var_free(...)		Gz.aide.var_free	(__VA_ARGS__)
/*
#define		vmeta_new(...)		Gz.aide.vmeta_new	(__VA_ARGS__)
*/
#define		zygote_init(...)	Gz.aide.zygote_init	(__VA_ARGS__)
#define		adef0(...)		Gz.aide.adef0		(__VA_ARGS__)

typedef	struct
{	void			(*func		[PART_MAX])	(void);
	VLESS			*arga		[PART_MAX];
	VALUE			save		[PART_MAX];
	uint8_t			*from		[PART_MAX];
	farint			far		[PART_MAX];
	uint8_t			name		[PART_MAX]	[LABEL_SIZE];

	PART_REFER		pr		[PART_REFER_MAX];
	VMETA			vmeta		[VMETA_MAX];
	VLESS			vless		[VLESS_MAX];
/*	ARGOT			argot		[ARGOT_MAX];	*/
	uint8_t			data		[DATA_MAX];
	uint8_t			pool		[POOL_MAX];
	ZYGOTE			zygote		[ZYGOTE_MAX];
	uint8_t			scratch		[SCRATCH_MAX];
}	HEAP;

typedef	struct
{	void			(**part)	(void);
	VLESS			*vless;		/* next vless */
	VMETA			*vmeta;		/* next vmeta */
	VMETA			*vmeta_reuse;	/* next reusable vmeta */
	uint8_t			*data;		/* next data */
	PART_REFER		*pr;		/* next part referral */
	ZYGOTE			*zygote;	/* next zygote */
/*	ARGOT			*argot;	*/	/* next argot */
	PAGE_POOL		pool;		/* available address space */
	uint8_t			*scratch;	/* non stack scribble space */
	uint32_t		far;		/* next/total far groups */
}	NEXTP;

typedef	struct
{	ARGOT			*argot	[0x10000];	/* argot hash table */
	VMETA			*var	[0x10000];	/* var   hash table */
	PART_REFER		*near	[0x10000];	/* near  hash table */
	PART_REFER		*far	[0x10000];	/* far   hash table */
}	HASH;

typedef	struct
{	VMETA			*nodelist;	/* selected node list var */
	VMETA			*para;		/* selected para var */
	VMETA			*ray;		/* selected type ray var */
	VMETA			*sem;		/* selected semaphore var */
	VMETA			*view;		/* selected view var */
}	ACTIVE_VAR;

typedef	struct
{	uint8_t			name	[VAR_NAME_SIZE];
}	VAMFIT;

/*	In the structure GzT
	the global uninitialized data
	is stored.
*/

/* For page start the caching is terrible! */
typedef	struct
{	PALIGN
	DHTABLE			dh;		/* a file is mapped */
	DENF			out;		/* int show functions */

	CALIGN
	struct	sigaction	sa	[2];

	ENDPART			*endpart;	/* for argot far visit end */

	CALIGN
	void			(**at)	(void);	/* argot pointer pointer */
	VMETA			*to[2];		/* target origin */
	NEXTP			next;		/* next available areas */

	int			*err;		/* saved better than call */

	ACTIVE_VAR		active;		/* selected var */

	CALIGN
	AIDE			aide;		/* PLT/GOT circumvention */

	CALIGN
	TAG			tag;		/* label composite area */

	CALIGN
	struct stat		yn[2];		/* argot yay * stat buffers */
	ARG			arg;		/* process parameter storage */
	VMETA			*env;		/* environment var pointer */

	CALIGN
	VMETA			*target_keep[8];
	VMETA			*origin_keep[8];

	PALIGN
	AP			ap;		/* argot path */

	/* From name to address fast translation tables. */
	PALIGN
	HASH			hash;

	CALIGN
	void			*sig	[0x100];

	VMETA			*iov;		/* var: sip out err */

	CALIGN
	COMMON_OP		op;		/* Gz hosted operator types */

	/* progeny process information */
	PALIGN
	PIDS			pids;

	PALIGN
	HEAP			heap;		/* address space */
}	GzT;

#include	<stdnoreturn.h>

#pragma	GCC	optimize	("-O3")
#pragma	clang	optimize	on

/*	In file ascript-inline.h
	as static possibly inline functions
	small and frequently useful code
	is provided.
*/

#define		pids		Gz.pids
#define		errna		*Gz.err

#include	"common.h"
#endif
