/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef	_A_MOUNT_H
#define	_A_MOUNT_H
#include	"byte.h"
#include	<sys/mount.h>

#define	mv_data		mv[0]
#define	mv_filesystem	mv[1]
#define	mv_partlabel	mv[2]
#define	mv_source	mv[3]
#define	mv_target	mv[4]

/*
typedef	struct
{	VMETA		data,
			filesystem,
			partlabel,
			source,
			target;
}	MNT_VAR;
*/

typedef	struct
{	VALUE		mflag,
			uflag;

	int		sys_class_block_len,
			proc_mounts_len;

	size_t		ibl,obl;
	char		*ib,*ob;

	PALIGN
	uint8_t		data_p		[PAGE];
	uint8_t		filesystem_p	[PAGE];
	uint8_t		partlabel_p	[PAGE];
	uint8_t		source_p	[PAGE];
	uint8_t		target_p	[PAGE];
	uint8_t		temp		[PAGE];

	uint8_t		sys_class_block	[HUGE];
	uint8_t		proc_mounts	[HUGE];
}	MNT_DATA;
#endif
