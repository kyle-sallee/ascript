/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_PAM_H
#define		_A_PAM_H
#include	"byte.h"
#include	<security/pam_appl.h>
#include	<security/pam_misc.h>

typedef	struct
{	VALUE			pam_error;
	pam_handle_t		*handle;
/*	VMETA			*account,*service;	*/
	struct	pam_conv	conv;
}	PDATA;

typedef	struct
{	VMETA			account;
	VMETA			service;
	VMETA			error;
	PDATA			data;
}	PG;
#endif
