/*	By Kyle Sallee from 2015 ... 2019 copyrighted.
	Used by ascript.c and argots
	by argot.c some functions are provided.
*/

#define		PROGRAM		1

#include	"ascript.h"
#include	"argot.h"

__attribute__((constructor(105)))
static	CALIGN	void	ap_init	(void)
{	void		*v=
	dlopen			("libascript.so." MM,RTLD_LOCAL|RTLD_LAZY);
	dlinfo			(v,RTLD_DI_ORIGIN,Gz.ap.p[0]);
	dlclose			(v);

	int		b=
	open			(Gz.ap.p[0],O_NONBLOCK|O_PATH|O_RDONLY);
	Gz.ap.d[0]=
	fcntl			(b,F_DUPFD_CLOEXEC,FDHIGH);
	__builtin_memcpy	(Gz.ap.p[0],LP,strlen(LP));
	__builtin_memcpy	(Gz.ap.p[1],LP,strlen(LP));
	__builtin_memcpy	(Gz.ap.p[2],LP,strlen(LP));

	__builtin_memcpy	(Gz.ap.p[0]+   strlen(LP),"req/",4);
	__builtin_memcpy	(Gz.ap.p[2]+   strlen(LP),"alt/",4);

	close			(b);
}
