/*	By Kyle Sallee in 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_FUTEX_H
#define		_A_FUTEX_H
#ifdef		__linux__

#include	<linux/futex.h>
#include	<sys/time.h>

typedef	struct
{	__attribute__((aligned(4)))	_Atomic	volatile
	uint32_t	use;
	__attribute__((aligned(4)))	_Atomic	volatile
	uint32_t	wait;
}	FUTEX;

/* m is maximum concurrent use often 1 */

__attribute__((unused))
static	inline	void	futex_acquire	(FUTEX * const f,int const m)
{	uint32_t			e;
	int				b;

	while				(1)
	{	if	yay		(m>(e=f->use))
		{	b=
			__atomic_compare_exchange_n
					(&f->use,
					 &e,
					 e+1,
					 0,
					 __ATOMIC_SEQ_CST,
					 __ATOMIC_SEQ_CST);
			if		(b)
			return;
		}

		f->wait++;
		syscall			(SYS_futex,f,FUTEX_WAIT,e,NULL,NULL,0);
		f->wait--;
	}
}

/*	The futex if acquired    1 is returned.
	For futex    acquisition
	    rather   than   wait 0 is returned.
*/
__attribute__((unused))
static	inline	int	futex_request	(FUTEX * const f,int const m)
{	uint32_t			e;
	if				(m>(e=f->use))
	return
	__atomic_compare_exchange_n	(&f->use,&e,e+1,0,
					 __ATOMIC_SEQ_CST,
					 __ATOMIC_SEQ_CST);
	return				0;
}

/*	Rather than check
	rather than wait
	the futex is unconditionally acquired
*/

__attribute__((unused))
static	inline	void	futex_inc		(FUTEX * const f)
{	f->use++;
}

__attribute__((unused))
static	inline	void	futex_release		(FUTEX * const f)
{	f->use--;
	syscall			(SYS_futex,&f->use,FUTEX_WAKE,INT_MAX,NULL,NULL,0);
}

#endif
#endif
