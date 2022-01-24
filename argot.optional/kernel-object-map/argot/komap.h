/*	By Kyle Sallee in 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_KO_H
#define		_A_KO_H
#include	"futex.h"
#include	<dirent.h>
#include	<linux/sched.h>
#include	<sched.h>
#include	<signal.h>
#include	<sys/utsname.h>

#define		KO_MAX		0x40000
#define		KO_ALIAS_MAX	0x400000

extern	OPERATOR	varkoop[1];

typedef	struct
{	char		*addr;
	uint32_t	 from;
}	KOALIAS;

typedef	struct
{	char		*name		[KO_MAX];
	char		*modinfo_addr	[KO_MAX];
	void		*addr		[KO_MAX];
	uint32_t	 modinfo_size	[KO_MAX];
	uint32_t	 size		[KO_MAX];
	KOALIAS		 alias		[KO_ALIAS_MAX];
}	KODATA;

enum	KVE
{	ko_defy_omit,
	ko_uevent_major,
	ko_uevent_minor,
	ko_uevent_pid,

	ko_alias,
	ko_name,
	ko_info,
	ko_path_config,
	ko_path_dev,
	ko_path_log,
	ko_path_object,

	ko_uevent_action,
	ko_uevent_alias,
	ko_uevent_devname,
	ko_uevent_raw,
	ko_uevent_syspath,
	ko_uevent_subsys,
};

struct	sched_attr
{	uint32_t	size;
	uint32_t	sched_policy;
	uint64_t	sched_flags;
	int32_t		sched_nice;
	uint32_t	sched_priority;
	uint64_t	sched_runtime;
	uint64_t	sched_deadline;
	uint64_t	sched_period;
};

typedef	struct
{	PALIGN
	FUTEX					futex;

	PALIGN
	uint8_t		*	volatile	next_read;
	uint8_t		*	volatile	next_write;
	int					socket;
	pid_t					pid;
	struct	timespec			last[2];

	PALIGN
	uint8_t		data	[HUGE*4];	/* 16384 cached events */
}	UEVENT;

typedef	struct
{	uint32_t	index;		/* index for selected kernel object */
	void		(**pin)	(void);
	struct	utsname	uts;

	PALIGN
	uint8_t		para	[PAGE];		/* module parameters */

	UEVENT		uevent;

	/* pages for .alias .name .uevent.alias .uevent.syspath */
	PALIGN
	uint8_t		kovp	[PAGE*4];
}	MEMORY;
#endif
