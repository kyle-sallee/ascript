/*	By   Kyle  Sallee   in     2018  copyrighted.
	From other projects source code  was not        copied.
	In   the   ascript  manual page; the license is provided.
*/

#ifndef		_A_SYS_LOG_H
#define		_A_SYS_LOG_H
#include	<syslog.h>
#include	<time.h>

typedef	struct
{	VMETA			message;
	VMETA			pathname;
	VMETA			self;
	VMETA			pipe;
/*	VMETA			pid;	*/
	OPERATOR		opsyslog[1];
	int			priority;
	int			p[4];		/* pipe */
	int			socket;
	int			mess_len;

	struct	sigaction	sa;
	struct	tm		tm;
	time_t			t;

	PALIGN
	uint8_t			selfname	[PAGE];
	uint8_t			logname		[PAGE];
	uint8_t			mess		[PAGE];

/*	uint8_t			huge[1][HUGE];
*/
}	SLD;

#endif
