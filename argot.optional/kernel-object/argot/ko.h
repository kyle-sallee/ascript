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

extern	OPERATOR	varkoop[1];

enum	KVE
{	ko_defy_modver,
	ko_defy_omit,
	ko_defy_vermagic,
	ko_uevent_major,
	ko_uevent_minor,
	ko_uevent_pid,

	ko_alias,
	ko_name,
	ko_info,
	ko_pathname,
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
{	uint8_t		*name;
	int		des;
}	RECALL;

typedef	struct
{	RECALL		*r;
	RECALL		R	[0x40];
	uint8_t		*name;
	uint8_t		*target;
}	KOFINDDATA;

typedef	struct
{	int		des;
	int		len;
	int		next;
	uint8_t		*name;
	DIR		*dir;
}	DIRDATA;

typedef	struct
{	DIRDATA		*d;
	DIRDATA		D	[0x40];
	uint8_t		reply	[PAGE];
	uint8_t		reply_len;
}	DIRWALKDATA;

typedef	struct	SPA
{	struct	SPA	*above;
	uint8_t		*name;
	int		len;
}	PATHABOVE;

typedef	struct
{	PATHABOVE	*pa;
	int		des;
	DIR		*dir;
}	DCD;

typedef	struct
{	DCD		*d;
	DCD		D	[0x40];
}	DIRCACHE;

typedef	struct	SOBJECT
{	struct	SOBJECT	*next;
	uint8_t		*name;
	PATHABOVE	*pathabove;
	uint8_t		*depend;
	uint8_t		*modinfo;
	int		 modinfo_len;
	uint8_t		name_len;
}	OBJECT;

typedef	struct	SMA
{	uint8_t		*alias;
	struct	SMA	*next;
	OBJECT		*object;
}	ALIAS;

typedef	struct
{	uint8_t		name		[0x100];	/* ko.name */
	uint8_t		pathname	[PAGE];		/* ko.pathname */
	uint8_t		para		[PAGE];		/* parameters */
	OBJECT		*object;
	int		name_len;			/* ko.name byte length*/
	int		flag;				/* finit_module flags */
	uint8_t		omit;				/* omit flag */
}	KOLOAD;

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
{	void		*avail;
	void		(**pin)	(void);

	struct	utsname	uts;

	UEVENT		uevent;

	PALIGN
	uint8_t		kovp[PAGE*5];	/* pages for .alias .name .pathname */

	ALIAS		*alias		[0x100];	/* first byte indexed */
	PALIGN
	OBJECT		*object	[8]	[0x10000];	/* len&8 16 bytes to 3*/
	PALIGN
	uint8_t		data		[0x4000000];	/* 64 megabytes */
}	MEMORY;
#endif
