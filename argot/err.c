/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"byte.h"
#include	"errno.h"
#include	"int.h"
#include	"trek.h"

#define	ESUCCESS	0

#define	va(a)	{.name=#a,.len=strlen(#a),.value.i=a,.op=opint4,},

static	VMETA		EV[]=
{
va(ESUCCESS)

#ifdef	EPERM
	va(EPERM)
#endif
#ifdef	ENOENT
	va(ENOENT)
#endif
#ifdef	ESRCH
	va(ESRCH)
#endif
#ifdef	EINTR
	va(EINTR)
#endif
#ifdef	EIO
	va(EIO)
#endif
#ifdef	ENXIO
	va(ENXIO)
#endif
#ifdef	E2BIG
	va(E2BIG)
#endif
#ifdef	ENOEXEC
	va(ENOEXEC)
#endif
#ifdef	EBADF
	va(EBADF)
#endif
#ifdef	ECHILD
	va(ECHILD)
#endif
#ifdef	EAGAIN
	va(EAGAIN)
#endif
#ifdef	ENOMEM
	va(ENOMEM)
#endif
#ifdef	EACCES
	va(EACCES)
#endif
#ifdef	EFAULT
	va(EFAULT)
#endif
#ifdef	ENOTBLK
	va(ENOTBLK)
#endif
#ifdef	EBUSY
	va(EBUSY)
#endif
#ifdef	EEXIST
	va(EEXIST)
#endif
#ifdef	EXDEV
	va(EXDEV)
#endif
#ifdef	ENODEV
	va(ENODEV)
#endif
#ifdef	ENOTDIR
	va(ENOTDIR)
#endif
#ifdef	EISDIR
	va(EISDIR)
#endif
#ifdef	EINVAL
	va(EINVAL)
#endif
#ifdef	ENFILE
	va(ENFILE)
#endif
#ifdef	EMFILE
	va(EMFILE)
#endif
#ifdef	ENOTTY
	va(ENOTTY)
#endif
#ifdef	ETXTBSY
	va(ETXTBSY)
#endif
#ifdef	EFBIG
	va(EFBIG)
#endif
#ifdef	ENOSPC
	va(ENOSPC)
#endif
#ifdef	ESPIPE
	va(ESPIPE)
#endif
#ifdef	EROFS
	va(EROFS)
#endif
#ifdef	EMLINK
	va(EMLINK)
#endif
#ifdef	EPIPE
	va(EPIPE)
#endif
#ifdef	EDOM
	va(EDOM)
#endif
#ifdef	ERANGE
	va(ERANGE)
#endif
#ifdef	EDEADLK
	va(EDEADLK)
#endif
#ifdef	ENAMETOOLONG
	va(ENAMETOOLONG)
#endif
#ifdef	ENOLCK
	va(ENOLCK)
#endif
#ifdef	ENOSYS
	va(ENOSYS)
#endif
#ifdef	ENOTEMPTY
	va(ENOTEMPTY)
#endif
#ifdef	ELOOP
	va(ELOOP)
#endif
#ifdef	EWOULDBLOCK
	va(EWOULDBLOCK)
#endif
#ifdef	ENOMSG
	va(ENOMSG)
#endif
#ifdef	EIDRM
	va(EIDRM)
#endif
#ifdef	ECHRNG
	va(ECHRNG)
#endif
#ifdef	EL2NSYNC
	va(EL2NSYNC)
#endif
#ifdef	EL3HLT
	va(EL3HLT)
#endif
#ifdef	EL3RST
	va(EL3RST)
#endif
#ifdef	ELNRNG
	va(ELNRNG)
#endif
#ifdef	EUNATCH
	va(EUNATCH)
#endif
#ifdef	ENOCSI
	va(ENOCSI)
#endif
#ifdef	EL2HLT
	va(EL2HLT)
#endif
#ifdef	EBADE
	va(EBADE)
#endif
#ifdef	EBADR
	va(EBADR)
#endif
#ifdef	EXFULL
	va(EXFULL)
#endif
#ifdef	ENOANO
	va(ENOANO)
#endif
#ifdef	EBADRQC
	va(EBADRQC)
#endif
#ifdef	EBADSLT
	va(EBADSLT)
#endif
#ifdef	EDEADLOCK
	va(EDEADLOCK)
#endif
#ifdef	EBFONT
	va(EBFONT)
#endif
#ifdef	ENOSTR
	va(ENOSTR)
#endif
#ifdef	ENODATA
	va(ENODATA)
#endif
#ifdef	ETIME
	va(ETIME)
#endif
#ifdef	ENOSR
	va(ENOSR)
#endif
#ifdef	ENONET
	va(ENONET)
#endif
#ifdef	ENOPKG
	va(ENOPKG)
#endif
#ifdef	EREMOTE
	va(EREMOTE)
#endif
#ifdef	ENOLINK
	va(ENOLINK)
#endif
#ifdef	EADV
	va(EADV)
#endif
#ifdef	ESRMNT
	va(ESRMNT)
#endif
#ifdef	ECOMM
	va(ECOMM)
#endif
#ifdef	EPROTO
	va(EPROTO)
#endif
#ifdef	EMULTIHOP
	va(EMULTIHOP)
#endif
#ifdef	EDOTDOT
	va(EDOTDOT)
#endif
#ifdef	EBADMSG
	va(EBADMSG)
#endif
#ifdef	EOVERFLOW
	va(EOVERFLOW)
#endif
#ifdef	ENOTUNIQ
	va(ENOTUNIQ)
#endif
#ifdef	EBADFD
	va(EBADFD)
#endif
#ifdef	EREMCHG
	va(EREMCHG)
#endif
#ifdef	ELIBACC
	va(ELIBACC)
#endif
#ifdef	ELIBBAD
	va(ELIBBAD)
#endif
#ifdef	ELIBSCN
	va(ELIBSCN)
#endif
#ifdef	ELIBMAX
	va(ELIBMAX)
#endif
#ifdef	ELIBEXEC
	va(ELIBEXEC)
#endif
#ifdef	EILSEQ
	va(EILSEQ)
#endif
#ifdef	ERESTART
	va(ERESTART)
#endif
#ifdef	ESTRPIPE
	va(ESTRPIPE)
#endif
#ifdef	EUSERS
	va(EUSERS)
#endif
#ifdef	ENOTSOCK
	va(ENOTSOCK)
#endif
#ifdef	EDESTADDRREQ
	va(EDESTADDRREQ)
#endif
#ifdef	EMSGSIZE
	va(EMSGSIZE)
#endif
#ifdef	EPROTOTYPE
	va(EPROTOTYPE)
#endif
#ifdef	ENOPROTOOPT
	va(ENOPROTOOPT)
#endif
#ifdef	EPROTONOSUPPORT
	va(EPROTONOSUPPORT)
#endif
#ifdef	ESOCKTNOSUPPORT
	va(ESOCKTNOSUPPORT)
#endif
#ifdef	EPFNOSUPPORT
	va(EPFNOSUPPORT)
#endif
#ifdef	EAFNOSUPPORT
	va(EAFNOSUPPORT)
#endif
#ifdef	EADDRINUSE
	va(EADDRINUSE)
#endif
#ifdef	EADDRNOTAVAIL
	va(EADDRNOTAVAIL)
#endif
#ifdef	ENETDOWN
	va(ENETDOWN)
#endif
#ifdef	ENETUNREACH
	va(ENETUNREACH)
#endif
#ifdef	ENETRESET
	va(ENETRESET)
#endif
#ifdef	ECONNABORTED
	va(ECONNABORTED)
#endif
#ifdef	ECONNRESET
	va(ECONNRESET)
#endif
#ifdef	ENOBUFS
	va(ENOBUFS)
#endif
#ifdef	EISCONN
	va(EISCONN)
#endif
#ifdef	ESHUTDOWN
	va(ESHUTDOWN)
#endif
#ifdef	ETOOMANYREFS
	va(ETOOMANYREFS)
#endif
#ifdef	ETIMEDOUT
	va(ETIMEDOUT)
#endif
#ifdef	ECONNREFUSED
	va(ECONNREFUSED)
#endif
#ifdef	EHOSTDOWN
	va(EHOSTDOWN)
#endif
#ifdef	EHOSTUNREACH
	va(EHOSTUNREACH)
#endif
#ifdef	EALREADY
	va(EALREADY)
#endif
#ifdef	EINPROGRESS
	va(EINPROGRESS)
#endif
#ifdef	ESTALE
	va(ESTALE)
#endif
#ifdef	EUCLEAN
	va(EUCLEAN)
#endif
#ifdef	ENOTNAM
	va(ENOTNAM)
#endif
#ifdef	ENAVAIL
	va(ENAVAIL)
#endif
#ifdef	EISNAM
	va(EISNAM)
#endif
#ifdef	EREMOTEIO
	va(EREMOTEIO)
#endif
#ifdef	EDQUOT
	va(EDQUOT)
#endif
#ifdef	ENOMEDIUM
	va(ENOMEDIUM)
#endif
#ifdef	EMEDIUMTYPE
	va(EMEDIUMTYPE)
#endif
#ifdef	ECANCELED
	va(ECANCELED)
#endif
#ifdef	ENOKEY
	va(ENOKEY)
#endif
#ifdef	EKEYEXPIRED
	va(EKEYEXPIRED)
#endif
#ifdef	EKEYREVOKED
	va(EKEYREVOKED)
#endif
#ifdef	EKEYREJECTED
	va(EKEYREJECTED)
#endif
#ifdef	EOWNERDEAD
	va(EOWNERDEAD)
#endif
#ifdef	ENOTRECOVERABLE
	va(ENOTRECOVERABLE)
#endif
#ifdef	ERFKILL
	va(ERFKILL)
#endif
#ifdef	EHWPOISON
	va(EHWPOISON)
#endif
};

#define	vb(a)	map_init(A);A->show=Gz.out.den4;vattach_faster(A,#a);A++

static	void	errvar_		(void)	{argot_next();}

SCV	errvar			(void)
{	*Gz.at=			errvar_;

	VMETA		*A=	EV;
	vb(ESUCCESS);

#ifdef	EPERM
	vb(EPERM);
#endif
#ifdef	ENOENT
	vb(ENOENT);
#endif
#ifdef	ESRCH
	vb(ESRCH);
#endif
#ifdef	EINTR
	vb(EINTR);
#endif
#ifdef	EIO
	vb(EIO);
#endif
#ifdef	ENXIO
	vb(ENXIO);
#endif
#ifdef	E2BIG
	vb(E2BIG);
#endif
#ifdef	ENOEXEC
	vb(ENOEXEC);
#endif
#ifdef	EBADF
	vb(EBADF);
#endif
#ifdef	ECHILD
	vb(ECHILD);
#endif
#ifdef	EAGAIN
	vb(EAGAIN);
#endif
#ifdef	ENOMEM
	vb(ENOMEM);
#endif
#ifdef	EACCES
	vb(EACCES);
#endif
#ifdef	EFAULT
	vb(EFAULT);
#endif
#ifdef	ENOTBLK
	vb(ENOTBLK);
#endif
#ifdef	EBUSY
	vb(EBUSY);
#endif
#ifdef	EEXIST
	vb(EEXIST);
#endif
#ifdef	EXDEV
	vb(EXDEV);
#endif
#ifdef	ENODEV
	vb(ENODEV);
#endif
#ifdef	ENOTDIR
	vb(ENOTDIR);
#endif
#ifdef	EISDIR
	vb(EISDIR);
#endif
#ifdef	EINVAL
	vb(EINVAL);
#endif
#ifdef	ENFILE
	vb(ENFILE);
#endif
#ifdef	EMFILE
	vb(EMFILE);
#endif
#ifdef	ENOTTY
	vb(ENOTTY);
#endif
#ifdef	ETXTBSY
	vb(ETXTBSY);
#endif
#ifdef	EFBIG
	vb(EFBIG);
#endif
#ifdef	ENOSPC
	vb(ENOSPC);
#endif
#ifdef	ESPIPE
	vb(ESPIPE);
#endif
#ifdef	EROFS
	vb(EROFS);
#endif
#ifdef	EMLINK
	vb(EMLINK);
#endif
#ifdef	EPIPE
	vb(EPIPE);
#endif
#ifdef	EDOM
	vb(EDOM);
#endif
#ifdef	ERANGE
	vb(ERANGE);
#endif
#ifdef	EDEADLK
	vb(EDEADLK);
#endif
#ifdef	ENAMETOOLONG
	vb(ENAMETOOLONG);
#endif
#ifdef	ENOLCK
	vb(ENOLCK);
#endif
#ifdef	ENOSYS
	vb(ENOSYS);
#endif
#ifdef	ENOTEMPTY
	vb(ENOTEMPTY);
#endif
#ifdef	ELOOP
	vb(ELOOP);
#endif
#ifdef	EWOULDBLOCK
	vb(EWOULDBLOCK);
#endif
#ifdef	ENOMSG
	vb(ENOMSG);
#endif
#ifdef	EIDRM
	vb(EIDRM);
#endif
#ifdef	ECHRNG
	vb(ECHRNG);
#endif
#ifdef	EL2NSYNC
	vb(EL2NSYNC);
#endif
#ifdef	EL3HLT
	vb(EL3HLT);
#endif
#ifdef	EL3RST
	vb(EL3RST);
#endif
#ifdef	ELNRNG
	vb(ELNRNG);
#endif
#ifdef	EUNATCH
	vb(EUNATCH);
#endif
#ifdef	ENOCSI
	vb(ENOCSI);
#endif
#ifdef	EL2HLT
	vb(EL2HLT);
#endif
#ifdef	EBADE
	vb(EBADE);
#endif
#ifdef	EBADR
	vb(EBADR);
#endif
#ifdef	EXFULL
	vb(EXFULL);
#endif
#ifdef	ENOANO
	vb(ENOANO);
#endif
#ifdef	EBADRQC
	vb(EBADRQC);
#endif
#ifdef	EBADSLT
	vb(EBADSLT);
#endif
#ifdef	EDEADLOCK
	vb(EDEADLOCK);
#endif
#ifdef	EBFONT
	vb(EBFONT);
#endif
#ifdef	ENOSTR
	vb(ENOSTR);
#endif
#ifdef	ENODATA
	vb(ENODATA);
#endif
#ifdef	ETIME
	vb(ETIME);
#endif
#ifdef	ENOSR
	vb(ENOSR);
#endif
#ifdef	ENONET
	vb(ENONET);
#endif
#ifdef	ENOPKG
	vb(ENOPKG);
#endif
#ifdef	EREMOTE
	vb(EREMOTE);
#endif
#ifdef	ENOLINK
	vb(ENOLINK);
#endif
#ifdef	EADV
	vb(EADV);
#endif
#ifdef	ESRMNT
	vb(ESRMNT);
#endif
#ifdef	ECOMM
	vb(ECOMM);
#endif
#ifdef	EPROTO
	vb(EPROTO);
#endif
#ifdef	EMULTIHOP
	vb(EMULTIHOP);
#endif
#ifdef	EDOTDOT
	vb(EDOTDOT);
#endif
#ifdef	EBADMSG
	vb(EBADMSG);
#endif
#ifdef	EOVERFLOW
	vb(EOVERFLOW);
#endif
#ifdef	ENOTUNIQ
	vb(ENOTUNIQ);
#endif
#ifdef	EBADFD
	vb(EBADFD);
#endif
#ifdef	EREMCHG
	vb(EREMCHG);
#endif
#ifdef	ELIBACC
	vb(ELIBACC);
#endif
#ifdef	ELIBBAD
	vb(ELIBBAD);
#endif
#ifdef	ELIBSCN
	vb(ELIBSCN);
#endif
#ifdef	ELIBMAX
	vb(ELIBMAX);
#endif
#ifdef	ELIBEXEC
	vb(ELIBEXEC);
#endif
#ifdef	EILSEQ
	vb(EILSEQ);
#endif
#ifdef	ERESTART
	vb(ERESTART);
#endif
#ifdef	ESTRPIPE
	vb(ESTRPIPE);
#endif
#ifdef	EUSERS
	vb(EUSERS);
#endif
#ifdef	ENOTSOCK
	vb(ENOTSOCK);
#endif
#ifdef	EDESTADDRREQ
	vb(EDESTADDRREQ);
#endif
#ifdef	EMSGSIZE
	vb(EMSGSIZE);
#endif
#ifdef	EPROTOTYPE
	vb(EPROTOTYPE);
#endif
#ifdef	ENOPROTOOPT
	vb(ENOPROTOOPT);
#endif
#ifdef	EPROTONOSUPPORT
	vb(EPROTONOSUPPORT);
#endif
#ifdef	ESOCKTNOSUPPORT
	vb(ESOCKTNOSUPPORT);
#endif
#ifdef	EPFNOSUPPORT
	vb(EPFNOSUPPORT);
#endif
#ifdef	EAFNOSUPPORT
	vb(EAFNOSUPPORT);
#endif
#ifdef	EADDRINUSE
	vb(EADDRINUSE);
#endif
#ifdef	EADDRNOTAVAIL
	vb(EADDRNOTAVAIL);
#endif
#ifdef	ENETDOWN
	vb(ENETDOWN);
#endif
#ifdef	ENETUNREACH
	vb(ENETUNREACH);
#endif
#ifdef	ENETRESET
	vb(ENETRESET);
#endif
#ifdef	ECONNABORTED
	vb(ECONNABORTED);
#endif
#ifdef	ECONNRESET
	vb(ECONNRESET);
#endif
#ifdef	ENOBUFS
	vb(ENOBUFS);
#endif
#ifdef	EISCONN
	vb(EISCONN);
#endif
#ifdef	ESHUTDOWN
	vb(ESHUTDOWN);
#endif
#ifdef	ETOOMANYREFS
	vb(ETOOMANYREFS);
#endif
#ifdef	ETIMEDOUT
	vb(ETIMEDOUT);
#endif
#ifdef	ECONNREFUSED
	vb(ECONNREFUSED);
#endif
#ifdef	EHOSTDOWN
	vb(EHOSTDOWN);
#endif
#ifdef	EHOSTUNREACH
	vb(EHOSTUNREACH);
#endif
#ifdef	EALREADY
	vb(EALREADY);
#endif
#ifdef	EINPROGRESS
	vb(EINPROGRESS);
#endif
#ifdef	ESTALE
	vb(ESTALE);
#endif
#ifdef	EUCLEAN
	vb(EUCLEAN);
#endif
#ifdef	ENOTNAM
	vb(ENOTNAM);
#endif
#ifdef	ENAVAIL
	vb(ENAVAIL);
#endif
#ifdef	EISNAM
	vb(EISNAM);
#endif
#ifdef	EREMOTEIO
	vb(EREMOTEIO);
#endif
#ifdef	EDQUOT
	vb(EDQUOT);
#endif
#ifdef	ENOMEDIUM
	vb(ENOMEDIUM);
#endif
#ifdef	EMEDIUMTYPE
	vb(EMEDIUMTYPE);
#endif
#ifdef	ECANCELED
	vb(ECANCELED);
#endif
#ifdef	ENOKEY
	vb(ENOKEY);
#endif
#ifdef	EKEYEXPIRED
	vb(EKEYEXPIRED);
#endif
#ifdef	EKEYREVOKED
	vb(EKEYREVOKED);
#endif
#ifdef	EKEYREJECTED
	vb(EKEYREJECTED);
#endif
#ifdef	EOWNERDEAD
	vb(EOWNERDEAD);
#endif
#ifdef	ENOTRECOVERABLE
	vb(ENOTRECOVERABLE);
#endif
#ifdef	ERFKILL
	vb(ERFKILL);
#endif
#ifdef	EHWPOISON
	vb(EHWPOISON);
#endif
	argot_next		();
}


#define	vn(a)	[a]=	#a

static	CALIGN	const
uint8_t		en[][0x10]=
{
	vn(ESUCCESS),

#ifdef	EPERM
	vn(EPERM),
#endif
#ifdef	ENOENT
	vn(ENOENT),
#endif
#ifdef	ESRCH
	vn(ESRCH),
#endif
#ifdef	EINTR
	vn(EINTR),
#endif
#ifdef	EIO
	vn(EIO),
#endif
#ifdef	ENXIO
	vn(ENXIO),
#endif
#ifdef	E2BIG
	vn(E2BIG),
#endif
#ifdef	ENOEXEC
	vn(ENOEXEC),
#endif
#ifdef	EBADF
	vn(EBADF),
#endif
#ifdef	ECHILD
	vn(ECHILD),
#endif
#ifdef	EAGAIN
	vn(EAGAIN),
#endif
#ifdef	ENOMEM
	vn(ENOMEM),
#endif
#ifdef	EACCES
	vn(EACCES),
#endif
#ifdef	EFAULT
	vn(EFAULT),
#endif
#ifdef	ENOTBLK
	vn(ENOTBLK),
#endif
#ifdef	EBUSY
	vn(EBUSY),
#endif
#ifdef	EEXIST
	vn(EEXIST),
#endif
#ifdef	EXDEV
	vn(EXDEV),
#endif
#ifdef	ENODEV
	vn(ENODEV),
#endif
#ifdef	ENOTDIR
	vn(ENOTDIR),
#endif
#ifdef	EISDIR
	vn(EISDIR),
#endif
#ifdef	EINVAL
	vn(EINVAL),
#endif
#ifdef	ENFILE
	vn(ENFILE),
#endif
#ifdef	EMFILE
	vn(EMFILE),
#endif
#ifdef	ENOTTY
	vn(ENOTTY),
#endif
#ifdef	ETXTBSY
	vn(ETXTBSY),
#endif
#ifdef	EFBIG
	vn(EFBIG),
#endif
#ifdef	ENOSPC
	vn(ENOSPC),
#endif
#ifdef	ESPIPE
	vn(ESPIPE),
#endif
#ifdef	EROFS
	vn(EROFS),
#endif
#ifdef	EMLINK
	vn(EMLINK),
#endif
#ifdef	EPIPE
	vn(EPIPE),
#endif
#ifdef	EDOM
	vn(EDOM),
#endif
#ifdef	ERANGE
	vn(ERANGE),
#endif
#ifdef	EDEADLK
	vn(EDEADLK),
#endif
#ifdef	ENAMETOOLONG
	vn(ENAMETOOLONG),
#endif
#ifdef	ENOLCK
	vn(ENOLCK),
#endif
#ifdef	ENOSYS
	vn(ENOSYS),
#endif
#ifdef	ENOTEMPTY
	vn(ENOTEMPTY),
#endif
#ifdef	ELOOP
	vn(ELOOP),
#endif
#ifdef	EWOULDBLOCK
	vn(EWOULDBLOCK),
#endif
#ifdef	ENOMSG
	vn(ENOMSG),
#endif
#ifdef	EIDRM
	vn(EIDRM),
#endif
#ifdef	ECHRNG
	vn(ECHRNG),
#endif
#ifdef	EL2NSYNC
	vn(EL2NSYNC),
#endif
#ifdef	EL3HLT
	vn(EL3HLT),
#endif
#ifdef	EL3RST
	vn(EL3RST),
#endif
#ifdef	ELNRNG
	vn(ELNRNG),
#endif
#ifdef	EUNATCH
	vn(EUNATCH),
#endif
#ifdef	ENOCSI
	vn(ENOCSI),
#endif
#ifdef	EL2HLT
	vn(EL2HLT),
#endif
#ifdef	EBADE
	vn(EBADE),
#endif
#ifdef	EBADR
	vn(EBADR),
#endif
#ifdef	EXFULL
	vn(EXFULL),
#endif
#ifdef	ENOANO
	vn(ENOANO),
#endif
#ifdef	EBADRQC
	vn(EBADRQC),
#endif
#ifdef	EBADSLT
	vn(EBADSLT),
#endif
#ifdef	EDEADLOCK
	vn(EDEADLOCK),
#endif
#ifdef	EBFONT
	vn(EBFONT),
#endif
#ifdef	ENOSTR
	vn(ENOSTR),
#endif
#ifdef	ENODATA
	vn(ENODATA),
#endif
#ifdef	ETIME
	vn(ETIME),
#endif
#ifdef	ENOSR
	vn(ENOSR),
#endif
#ifdef	ENONET
	vn(ENONET),
#endif
#ifdef	ENOPKG
	vn(ENOPKG),
#endif
#ifdef	EREMOTE
	vn(EREMOTE),
#endif
#ifdef	ENOLINK
	vn(ENOLINK),
#endif
#ifdef	EADV
	vn(EADV),
#endif
#ifdef	ESRMNT
	vn(ESRMNT),
#endif
#ifdef	ECOMM
	vn(ECOMM),
#endif
#ifdef	EPROTO
	vn(EPROTO),
#endif
#ifdef	EMULTIHOP
	vn(EMULTIHOP),
#endif
#ifdef	EDOTDOT
	vn(EDOTDOT),
#endif
#ifdef	EBADMSG
	vn(EBADMSG),
#endif
#ifdef	EOVERFLOW
	vn(EOVERFLOW),
#endif
#ifdef	ENOTUNIQ
	vn(ENOTUNIQ),
#endif
#ifdef	EBADFD
	vn(EBADFD),
#endif
#ifdef	EREMCHG
	vn(EREMCHG),
#endif
#ifdef	ELIBACC
	vn(ELIBACC),
#endif
#ifdef	ELIBBAD
	vn(ELIBBAD),
#endif
#ifdef	ELIBSCN
	vn(ELIBSCN),
#endif
#ifdef	ELIBMAX
	vn(ELIBMAX),
#endif
#ifdef	ELIBEXEC
	vn(ELIBEXEC),
#endif
#ifdef	EILSEQ
	vn(EILSEQ),
#endif
#ifdef	ERESTART
	vn(ERESTART),
#endif
#ifdef	ESTRPIPE
	vn(ESTRPIPE),
#endif
#ifdef	EUSERS
	vn(EUSERS),
#endif
#ifdef	ENOTSOCK
	vn(ENOTSOCK),
#endif
#ifdef	EDESTADDRREQ
	vn(EDESTADDRREQ),
#endif
#ifdef	EMSGSIZE
	vn(EMSGSIZE),
#endif
#ifdef	EPROTOTYPE
	vn(EPROTOTYPE),
#endif
#ifdef	ENOPROTOOPT
	vn(ENOPROTOOPT),
#endif
#ifdef	EPROTONOSUPPORT
	vn(EPROTONOSUPPORT),
#endif
#ifdef	ESOCKTNOSUPPORT
	vn(ESOCKTNOSUPPORT),
#endif
#ifdef	EPFNOSUPPORT
	vn(EPFNOSUPPORT),
#endif
#ifdef	EAFNOSUPPORT
	vn(EAFNOSUPPORT),
#endif
#ifdef	EADDRINUSE
	vn(EADDRINUSE),
#endif
#ifdef	EADDRNOTAVAIL
	vn(EADDRNOTAVAIL),
#endif
#ifdef	ENETDOWN
	vn(ENETDOWN),
#endif
#ifdef	ENETUNREACH
	vn(ENETUNREACH),
#endif
#ifdef	ENETRESET
	vn(ENETRESET),
#endif
#ifdef	ECONNABORTED
	vn(ECONNABORTED),
#endif
#ifdef	ECONNRESET
	vn(ECONNRESET),
#endif
#ifdef	ENOBUFS
	vn(ENOBUFS),
#endif
#ifdef	EISCONN
	vn(EISCONN),
#endif
#ifdef	ESHUTDOWN
	vn(ESHUTDOWN),
#endif
#ifdef	ETOOMANYREFS
	vn(ETOOMANYREFS),
#endif
#ifdef	ETIMEDOUT
	vn(ETIMEDOUT),
#endif
#ifdef	ECONNREFUSED
	vn(ECONNREFUSED),
#endif
#ifdef	EHOSTDOWN
	vn(EHOSTDOWN),
#endif
#ifdef	EHOSTUNREACH
	vn(EHOSTUNREACH),
#endif
#ifdef	EALREADY
	vn(EALREADY),
#endif
#ifdef	EINPROGRESS
	vn(EINPROGRESS),
#endif
#ifdef	ESTALE
	vn(ESTALE),
#endif
#ifdef	EUCLEAN
	vn(EUCLEAN),
#endif
#ifdef	ENOTNAM
	vn(ENOTNAM),
#endif
#ifdef	ENAVAIL
	vn(ENAVAIL),
#endif
#ifdef	EISNAM
	vn(EISNAM),
#endif
#ifdef	EREMOTEIO
	vn(EREMOTEIO),
#endif
#ifdef	EDQUOT
	vn(EDQUOT),
#endif
#ifdef	ENOMEDIUM
	vn(ENOMEDIUM),
#endif
#ifdef	EMEDIUMTYPE
	vn(EMEDIUMTYPE),
#endif
#ifdef	ECANCELED
	vn(ECANCELED),
#endif
#ifdef	ENOKEY
	vn(ENOKEY),
#endif
#ifdef	EKEYEXPIRED
	vn(EKEYEXPIRED),
#endif
#ifdef	EKEYREVOKED
	vn(EKEYREVOKED),
#endif
#ifdef	EKEYREJECTED
	vn(EKEYREJECTED),
#endif
#ifdef	EOWNERDEAD
	vn(EOWNERDEAD),
#endif
#ifdef	ENOTRECOVERABLE
	vn(ENOTRECOVERABLE),
#endif
#ifdef	ERFKILL
	vn(ERFKILL),
#endif
#ifdef	EHWPOISON
	vn(EHWPOISON),
#endif
};


static	void	_errno_	(void)
{	errna=		0;
	argot_next	();
}

static	void	_errno	(void)	{(*Gz.at=_errno_)();}
static	void	_err_	(void)	{argot_next	();}
static	void	_err	(void)	{(*Gz.at=_err_)	();}

__attribute__((always_inline))
__attribute__((optimize("Os")))
static	inline	uint8_t	enl	(uint8_t const * const a)
{	uint8_t	const	*b;
	for			(b=a+2;*b;b++);
	return			b-a;
}

SCV	reval_errno	(VMETA *A)	{A->value.i=	errna;}
SCV	revise_errno	(VMETA *A)	{errna=		A->value.i;}

SCV	show_errtext		(VMETA *A)
{	A->value.i=		errna;
	char		*a=
	strerror		(A->value.i);
	A->textlen=
	strlena			(a);
	A->textaddr[
	A->textlen]=		0;
	memcpyb			(A->textaddr,a,A->textlen);
}

__attribute__((noinline))
SCV	(**errat(void))(void)
{	void		(**A)	(void)=
	nearfind_safe		(en[errna],partfar(NULL));
	if			(A!=NULL)
	return			A;

	return
	nearfind_safe		("EANY\0\0\0\0\0\0\0\0\0\0\0",partfar(NULL));
}

SCV	errgo			(void)
{	void	(**A)	(void)=
	errat			();
	*Gz.at=			errgo;
	if			(A==NULL)
	A=			Gz.at+1;
	(*(Gz.at=A))		();
}

SCV	errpin			(void)
{	void	(**L)	(void)=	Gz.at;

	void	(**A)	(void)=
	errat			();

	*Gz.at=			errpin;
	if		yay	(A!=NULL)
	(*(Gz.at=A  ))		();
	(*(Gz.at=L+1))		();
}

SCV	errwith_	(void)	{argot_jump		(errna!=0);}
SCV	errsans_	(void)	{argot_jump		(errna==0);}
SCV	errwith		(void)	{(*Gz.at=errwith_)	();}
SCV	errsans		(void)	{(*Gz.at=errsans_)	();}

__attribute__((noinline))
SCV	errnofromsuccess_	(void)
{	errna=			Gz.to[0]->io.success;
	argot_next		();
}

__attribute__((noinline))
SCV	successfromerrno_	(void)
{	Gz.to[0]->io.success=	errna;
	argot_next		();
}

static	void	errnofromsuccess	(void)	{(*Gz.at=errnofromsuccess_)();}
static	void	successfromerrno	(void)	{(*Gz.at=successfromerrno_)();}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180315",
	.official=	"20180315",
	.update=	"20200809"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(_err,			"err");
	aa		(errnofromsuccess,	"errnofromsuccess");
	aa		(successfromerrno,	"successfromerrno");
	aa		(errpin,		"errpin");
	aa		(errgo,			"errgo");
	aa		(_errno,		"errno");
	aa		(errvar,		"errvar");
	aa		(errwith,		"errwith");
	aa		(errsans,		"errsans");
	aa_fini		();
};

__attribute__((constructor))
SCV	init				(void)
{	static	VMETA	A[2]=
	{	[0].name="errno",	[0].len=5,	[0].op=opint4,
		[1].name="errtext",	[1].len=7,	[1].op=opbyte,
	};

	map_init		(A+0);
	map_init		(A+1);
	A[0].reval=		reval_errno;
	A[0].revise=		revise_errno;
	A[0].show=		Gz.out.den4;
	A[1].show=		show_errtext;

	vattach_faster		(A  ,"errno");
	vattach_faster		(A+1,"errtext");
}
