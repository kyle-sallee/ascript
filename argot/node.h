/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_VIEW_H
#define		_VIEW_H
#include	"byte.h"
#include	"int.h"

typedef	struct
{	VMETA	*dub,*gid,*mode,*object,*origin,*rmajor,*rminor,*target,*uid;
}	NODEAT;

typedef	struct
{	ino_t	ino;
	dev_t	dev;
	uint8_t	*name;
}	LINK;

typedef	struct
{	PALIGN
	LINK		link_init	[0x400];
	PALIGN
	uint8_t		text_init	[HUGE];
	uint8_t		same		[HUGE*2];
	uint8_t		a		[PAGE*2];
	struct	stat	b		[2];

	VMETA		c		[4];
	int		d		[2];

	VMETA		g		[1];

	LINK		*link_addr;
	size_t		link_size;

	uint8_t		*text_next;
	uint8_t		*text_addr;
	size_t		text_size;

	NODEAT		at;
}	NODEGLOBAL;
#endif
