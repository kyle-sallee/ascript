/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_SKED_H
#define		_A_SKED_H
#include	<sched.h>
#include	<linux/sched.h>

/*	By    the C         library
	until the kernel    provided function sched_setattr is supported
	the       structure must be defined
	and   the syscall   must be invoked.
*/

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
{	VMETA			give,
				nice,
				pid,
				policy,
				priority,
				deadline,
				period,
				runtime;

	struct	sched_attr	attr;
	uint8_t			affinity[2][PAGE];
}	SKEDDATA;
#endif
