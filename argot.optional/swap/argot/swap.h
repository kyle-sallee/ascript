/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_SWAP_H
#define		_A_SWAP_H
#include	<sys/swap.h>
#include	<unistd.h>

/*
static	OPERATOR	varswapop[1];
*/

struct	SWAP
{	uint8_t		reserve		[0x400];
	uint32_t	version;
	uint32_t	last_page;
	uint32_t	nr_badpages;
	uint8_t		uuid		[0x10];
	uint8_t		volname		[0x10];
	uint32_t	pad		[0x75];
	uint32_t	badpages	[1];
	uint8_t		empty		[0x9f2];
	uint8_t		sig		[0xa];
};

typedef	struct
{	VALUE		pad;
	VMETA		label;
	VMETA		pathname;
	VMETA		priority;
	VMETA		uuid;
	VMETA		size;

/*	VMETA		*swap,*label,*pathname,*priority,*uuid,*size;
*/
	int64_t		sv;
	int		prefer;
	struct	stat	b;
	PALIGN
	struct	SWAP	s;
}	SWAPDATA;
#endif
