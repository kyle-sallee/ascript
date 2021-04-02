/*	By   Kyle  Sallee   in     2018  copyrighted.
	From other projects source code  was not        copied.
	In   the   ascript  manual page; the license is provided.
*/

#ifndef		_A_KLOG_H
#define		_A_KLOG_H
#include	<time.h>

typedef	struct
{	uint8_t		pathname[PAGE];
	struct	tm	tm;
	time_t		t;
	VMETA		*PN;
}	KLD;
#endif
