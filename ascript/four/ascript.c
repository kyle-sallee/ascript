/*	By Kyle Sallee from 2015 ... 2019 copyrighted.
	ascript is fast, tiny script interpreter.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

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

__attribute__((visibility("hidden")))
	CALIGN	uint8_t	main	(int argc,uint8_t *argv[])
{	CALIGN
	ZONE		z;
	Gz.err=			&errno;
	Gz.argc=		argc;
	Gz.argv=		argv;
	zone_init		(&z,argv[1]);
	(Gz.aat=z.part)->func	();
	return			0;
}
