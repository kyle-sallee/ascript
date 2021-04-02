/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_CAP_H
#define		_A_CAP_H
#include	<linux/capability.h>

extern	OPERATOR	varcapop[1];

typedef	struct
{	int	(*check)	(long);
	int	(*lower)	(long);
	int	(*raise)	(long);
}	CAPF;

typedef	struct
{	cap_user_header_t	hdrp;
	cap_user_data_t		datap[2];
}	cap_head_data;

/*	maps:
	0	empty page
	1	empty page
	2	CAPF
*/

extern	int		capget	(cap_user_header_t,const cap_user_data_t);
extern	int		capset	(cap_user_header_t,      cap_user_data_t);
#endif
