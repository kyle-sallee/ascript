/*	By Kyle Sallee from 2015 ... 2020 copyrighted.
	In the ascript manual page; the license is provided.
*/

/*	Why AIDE?
	Forr every ELF library
	a symbol to address
	when first resolved
	many opcodes must execute.
	The C library provided function open
	in every ELF
	where invoked
	this cost becomes.
	Then function open
	when acessed
	a call and jmp combo execute.
	This is trash!
	A simple solution exists.
	When first accessed
	in Gz those opcode addresses
	are stored.
	Function open
	aft name to address resolution
	for invocation
	a single opcode, an indirect address call,
	executes.

	With the runtime linker
	as compared
	the dlsym invocations
	are slower.
	With any two runtime linker resolutions
	as compared
	one dlsym invocation
	is faster.
	Also for some frequently used opcode sequences
	the addresses are cached and included in ascript.
	That helps reduce argot size where an opcode call
	would definitely be unavoidable, such as with
	available memory acquisition.
	The runtime linker PLT/GOT use is a kick in the ....
	By aide a cup to hold those addresses is provided.

	The AIDE benefit overall is quite small.
	From a medium sized script execution
	100,000 to 250,000 opcode executions
	might be shaved.
	For new memory address acqusition
	a call/ret combo is added.
	The gains/losses are hard to notice.
	By any C library provided function invocation
	by any to Linux kernel syscall
	a massive opcode plethora executes.
	It's about as useful as pealing skin from a potato.
	But some ire about ELFs is circumvented.
*/

#define		PROGRAM		1

#ifndef		_GNU_SOURCE
#define		_GNU_SOURCE
#endif
#define		_POSIX_SOURCE
#define		_POSIX_C_SOURCE		199309L	/* for siginfo_t in sigaction */
#define		_XOPEN_SOURCE		700
#define		_XOPEN_SOURCE_EXTENDED
#define		__USE_XOPEN

#define		PROGRAM		1
#include	"ascript.h"
#include	"parse.h"
#include	<dlfcn.h>

#define	SC	__attribute__((unused))	static	CALIGN

SC	int	a_chdir			(const char *a)
{	return	(Gz.aide.chdir=dlsym	(RTLD_DEFAULT,"chdir"))	(a);
}

SC	int	a_chmod			(const char *a,mode_t b)
{	return	(Gz.aide.chmod=dlsym	(RTLD_DEFAULT,"chmod"))	(a,b);
}

SC	int	a_chown			(const char *a,uid_t b,gid_t c)
{	return	(Gz.aide.chown=dlsym	(RTLD_DEFAULT,"chown"))	(a,b,c);
}

__attribute__((unused))
SC	int	a_close			(int a)
{	return	(Gz.aide.close=dlsym	(RTLD_DEFAULT,"close"))	(a);
}

SC	int	a_closedir		(DIR *a)
{	return	(Gz.aide.closedir=dlsym	(RTLD_DEFAULT,"closedir"))	(a);
}

SC	int	a_dup2			(int a,int b)
{	return	(Gz.aide.dup2=dlsym	(RTLD_DEFAULT,"dup2"))	(a,b);
}

SC	int	a_fchdir		(int a)
{	return	(Gz.aide.fchdir=dlsym	(RTLD_DEFAULT,"fchdir"))	(a);
}

SC	int	a_fchmod		(int a,mode_t b)
{	return	(Gz.aide.fchmod=dlsym	(RTLD_DEFAULT,"fchmod"))	(a,b);
}

SC	int	a_fchown		(int a,uid_t b,gid_t c)
{	return	(Gz.aide.fchown=dlsym	(RTLD_DEFAULT,"fchown"))	(a,b,c);
}

SC	DIR	*a_fdopendir			(int a)
{	return	(Gz.aide.fdopendir=dlsym	(RTLD_DEFAULT,"fdopendir"))	(a);
}

SC	int	a_fstat			(int a,struct stat *b)
{	return	(Gz.aide.fstat=dlsym	(RTLD_DEFAULT,"fstat"))	(a,b);
}

SC	int	a_ftruncate		(int a,off_t b)
{	return	(Gz.aide.ftruncate=dlsym(RTLD_DEFAULT,"ftruncate"))	(a,b);
}

SC	uid_t	a_geteuid		(void)
{	return	(Gz.aide.geteuid=dlsym	(RTLD_DEFAULT,"geteuid"))	();
}

SC	pid_t	a_getpid		(void)
{	return	(Gz.aide.getpid=dlsym	(RTLD_DEFAULT,"getpid"))	();
}

SC	uid_t	a_getuid		(void)
{	return	(Gz.aide.getuid=dlsym	(RTLD_DEFAULT,"getuid"))	();
}

SC	off_t	a_lseek			(int a,off_t b,int c)
{	return	(Gz.aide.lseek=dlsym	(RTLD_DEFAULT,"lseek"))	(a,b,c);
}

SC	int	a_lstat			(const char *a,struct stat *b)
{	return	(Gz.aide.lstat=dlsym	(RTLD_DEFAULT,"lstat"))	(a,b);
}

SC	int	a_madvise		(void *a,size_t b,int c)
{	return	(Gz.aide.madvise=dlsym	(RTLD_DEFAULT,"madvise"))	(a,b,c);
}

SC	int	a_memcmp		(const void *a,const void *b,size_t c)
{	return	(Gz.aide.memcmp=dlsym	(RTLD_DEFAULT,"memcmp"))	(a,b,c);
}

SC	int	a_mkdir			(char const  *a,mode_t b)
{	return	(Gz.aide.mkdir=dlsym	(RTLD_DEFAULT,"mkdir"))	(a,b);
}

__attribute__((unused))
SC	void	*a_mmap		(void *a,size_t b,int c,int d,int e,off_t f)
{	return	(Gz.aide.mmap=	dlsym	(RTLD_DEFAULT,"mmap"))	(a,b,c,d,e,f);
}

SC	int	a_mprotect		(void *a,size_t b,int c)
{	return	(Gz.aide.mprotect=dlsym	(RTLD_DEFAULT,"mprotect"))	(a,b,c);
}

__attribute__((unused))
SC	int	a_munmap		(void *a,size_t b)
{	return	(Gz.aide.munmap=dlsym	(RTLD_DEFAULT,"munmap"))	(a,b);
}

SC	int	a_poll			(struct pollfd *a,nfds_t b,int c)
{	return	(Gz.aide.poll=dlsym	(RTLD_DEFAULT,"poll"))	(a,b,c);
}

__attribute__((unused))
SC	ssize_t	a_read			(int a,void const *b,size_t c)
{	return	(Gz.aide.read=dlsym	(RTLD_DEFAULT,"read"))	(a,b,c);
}

SC	ssize_t	a_recv			(int a,void const *b,size_t c,int d)
{	return	(Gz.aide.recv=dlsym	(RTLD_DEFAULT,"recv"))	(a,b,c,d);
}

SC	struct dirent	*a_readdir	(DIR *a)
{	return	(Gz.aide.readdir=dlsym	(RTLD_DEFAULT,"readdir"))	(a);
}

SC	int	a_sigaction		(int a,	struct sigaction const *b,
						struct sigaction *c)
{	return	(Gz.aide.sigaction=dlsym(RTLD_DEFAULT,"sigaction"))	(a,b,c);
}

SC	int	a_sigqueue		(pid_t a,int b,const union sigval c)
{	return	(Gz.aide.sigqueue=dlsym(RTLD_DEFAULT,"sigqueue"))	(a,b,c);
}

SC	int	a_stat			(const char *a,struct stat *b)
{	return	(Gz.aide.stat=dlsym	(RTLD_DEFAULT,"stat"))	(a,b);
}

SC	ssize_t	a_write			(int a,void const *b,size_t c)
{	return	(Gz.aide.write=dlsym	(RTLD_DEFAULT,"write"))	(a,b,c);
}

SC	ssize_t	a_send			(int a,void const *b,size_t c,int d)
{	return	(Gz.aide.send=dlsym	(RTLD_DEFAULT,"send"))	(a,b,c,d);
}

#include	<stdarg.h>

__attribute__((unused))
SC	void	*a_mremap		(void *a,size_t b,size_t c,int d,...)
{	va_list		f;
	va_start			(f,d);

	void		*e=
	va_arg				(f,void *);
	va_end				(f);

	return	(Gz.aide.mremap=
	dlsym	(RTLD_DEFAULT,"mremap"))(a,b,c,d,e);
}

__attribute__((unused))
SC	int	a_open			(char const *a,int b,...)
{	va_list		d;
	va_start			(d,b);

	mode_t		c=
	va_arg				(d,mode_t);
	va_end				(d);

	return	(Gz.aide.open=dlsym	(RTLD_DEFAULT,"open"))	(a,b,c);
}

__attribute__((unused))
SC	int	a_snprintf		(char *a,size_t b,char const *c,...)
{	int		(*f)		(char *, size_t,  char const *,...)=
	Gz.aide.snprintf=	dlsym	(RTLD_DEFAULT,"vsnprintf");

	va_list		d;
	va_start			(d,c);
	int		e=
	f				(a,b,c,d);
	va_end				(d);
	return				e;
}

__attribute__((unused))
SC	int	a_sprintf		(char *a,char const *b,...)
{	int		(*f)		(char *, char const *,...)=
	Gz.aide.sprintf=	dlsym	(RTLD_DEFAULT,"vsprintf");

	va_list		c;
	va_start			(c,b);
	int		d=
	f				(a,b,c);
	va_end				(c);
	return				d;
}

__attribute__((constructor(102)))
SC	void	aide_init		(void)
{	Gz.aide.chdir=			a_chdir;
	Gz.aide.chmod=			a_chmod;
	Gz.aide.chown=			a_chown;
/*	Gz.aide.close=			a_close;	*/
	Gz.aide.closedir=		a_closedir;
	Gz.aide.dup2=			a_dup2;
	Gz.aide.fchdir=			a_fchdir;
	Gz.aide.fchmod=			a_fchmod;
	Gz.aide.fchown=			a_fchown;
	Gz.aide.fdopendir=		a_fdopendir;
	Gz.aide.fstat=			a_fstat;
	Gz.aide.ftruncate=		a_ftruncate;
	Gz.aide.geteuid=		a_geteuid;
	Gz.aide.getpid=			a_getpid;
	Gz.aide.getuid=			a_getuid;
	Gz.aide.lseek=			a_lseek;
	Gz.aide.lstat=			a_lstat;
	Gz.aide.madvise=		a_madvise;
	Gz.aide.memcmp=			a_memcmp;
	Gz.aide.mkdir=			a_mkdir;
/*	Gz.aide.mmap=			a_mmap;	*/
	Gz.aide.mprotect=		a_mprotect;
/*	Gz.aide.mremap=			a_mremap;	*/
/*	Gz.aide.munmap=			a_munmap;	*/
/*	Gz.aide.open=			a_open;	*/
	Gz.aide.poll=			a_poll;
/*	Gz.aide.read=			a_read;	*/
	Gz.aide.recv=			a_recv;
	Gz.aide.readdir=		a_readdir;
	Gz.aide.sigaction=		a_sigaction;
	Gz.aide.sigqueue=		a_sigqueue;
/*	Gz.aide.snprintf=		a_snprintf;	*/
/*	Gz.aide.sprintf=		a_sprintf;	*/

	Gz.aide.stat=			a_stat;
	Gz.aide.send=			a_send;
	Gz.aide.write=			a_write;

	Gz.aide.adef0=			adef0_aide;
	Gz.aide.text_adjust=		text_adjust_aide;
	Gz.aide.pp=			pp_aide;
	Gz.aide.pps=			pps_aide;
	Gz.aide.var_free=		var_free_aide;
/*	Gz.aide.vmeta_new=		vmeta_new_aide;		*/
	Gz.aide.sendall=		sendall_aide;
	Gz.aide.writeall=		writeall_aide;
	Gz.aide.zygote_init=		zygote_init_aide;

	Gz.aide.close=
	dlsym				(RTLD_DEFAULT,"close");

	Gz.aide.fcntl=
	dlsym				(RTLD_DEFAULT,"fcntl");

	Gz.aide.ioctl=
	dlsym				(RTLD_DEFAULT,"ioctl");

	Gz.aide.mmap=
	dlsym				(RTLD_DEFAULT,"mmap");

	Gz.aide.mremap=
	dlsym				(RTLD_DEFAULT,"mremap");

	Gz.aide.munmap=
	dlsym				(RTLD_DEFAULT,"munmap");

	Gz.aide.open=
	dlsym				(RTLD_DEFAULT,"open");

	Gz.aide.read=
	dlsym				(RTLD_DEFAULT,"read");


/*	Gz.aide.syscall=
	dlsym				(RTLD_DEFAULT,"syscall");
*/
}
