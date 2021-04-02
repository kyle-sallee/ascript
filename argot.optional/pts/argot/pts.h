/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_PTS_H
#define		_A_PTS_H
#include	<pty.h>
#include	<termios.h>

/*	A's	maps.
	map	0	nothing
	map	1	PDATA
*/

typedef	struct
{	int		d[2];	/* original and dup descriptor values */
	struct	termios	T[2];	/* original and raw attributes */
	int		f;	/* original flag */
}	PSAVE;

typedef	struct
{	VALUE			*host0;
	VALUE			*host1;
	VALUE			*host2;
	VALUE			*host0log;
	VALUE			*host1log;
	VALUE			*host2log;
	VALUE			*fake0;
	VALUE			*fake1;
	VALUE			*fake2;
	PSAVE			save	[6];
	int			m	[2];	/* host descriptors */
	int			s	[3];	/* fake descriptors */
	int			sig;	/* the real-time signal number */
/*	struct	sigaction	a;	*/
	uint8_t			io	[HUGE];
}	PDATA;

__attribute__((always_inline))
static	inline	 PDATA *	pdata	(VMETA *A)
{	return	(PDATA *)	A->dataaddr;
}
#endif
