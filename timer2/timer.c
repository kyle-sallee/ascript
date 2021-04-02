/*	By Kyle Sallee 2019 copyrighted.
	By the BASH builtin time command
	the purported real duration
	the purported sys  duration
	are incorrect.
	Thus this timer program
	instead can be used.

	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_GNU_SOURCE
#define		_GNU_SOURCE
#endif
#define		_POSIX_SOURCE
#define		_POSIX_C_SOURCE		199309L	/* for siginfo_t in sigaction */
#define		_XOPEN_SOURCE		700
#define		_XOPEN_SOURCE_EXTENDED
#define		__USE_XOPEN

#include	<err.h>
#include	<errno.h>
#include	<linux/perf_event.h>
#include	<linux/hw_breakpoint.h>
#include	<stdint.h>
#include	<string.h>
#include	<sys/mman.h>
#include	<sys/prctl.h>
#include	<sys/resource.h>
#include	<sys/syscall.h>
#include	<sys/time.h>
#include	<sys/types.h>
#include	<sys/wait.h>
#include	<time.h>
#include	<unistd.h>

typedef		struct
{	struct	timespec	T[2];
	struct	rusage		R;
}
TIMEDATA;

__attribute__((aligned(0x10000)))
static		TIMEDATA	TD;


#define		EXCLUDE_KERNEL

struct	perf_event_attr		pea[]=
{	{	.type=			PERF_TYPE_HARDWARE,
		.size=			sizeof(struct perf_event_attr),
		.config=		PERF_COUNT_HW_CACHE_REFERENCES,
		.exclude_hv=		1,
#ifdef		EXCLUDE_KERNEL
		.exclude_kernel=	1,
#endif
	},
	{	.type=			PERF_TYPE_HARDWARE,
		.size=			sizeof(struct perf_event_attr),
		.config=		PERF_COUNT_HW_CACHE_MISSES,
		.exclude_hv=		1,
#ifdef		EXCLUDE_KERNEL
		.exclude_kernel=	1,
#endif
	},
	{	.type=			PERF_TYPE_HARDWARE,
		.size=			sizeof(struct perf_event_attr),
		.config=		PERF_COUNT_HW_BRANCH_INSTRUCTIONS,
		.exclude_hv=		1,
#ifdef		EXCLUDE_KERNEL
		.exclude_kernel=	1,
#endif
	},
	{	.type=			PERF_TYPE_HARDWARE,
		.size=			sizeof(struct perf_event_attr),
		.config=		PERF_COUNT_HW_BRANCH_MISSES,
		.exclude_hv=		1,
#ifdef		EXCLUDE_KERNEL
		.exclude_kernel=	1,
#endif
	},
	{	.type=			PERF_TYPE_HARDWARE,
		.size=			sizeof(struct perf_event_attr),
		.config=		PERF_COUNT_HW_INSTRUCTIONS,
		.exclude_hv=		1,
#ifdef		EXCLUDE_KERNEL
		.exclude_kernel=	1,
#endif
	},
};


__attribute__((visibility("hidden")))
		char	main		(int argc,char *argv[])
{	mmap				(&TD,sizeof(TD),
					 PROT_READ|PROT_WRITE,
					 MAP_ANONYMOUS|MAP_FIXED|MAP_SHARED,-1,0);
	pid_t		p=
	fork				();
	if				(p==0)
	{/*	prctl			(PR_TASK_PERF_EVENTS_ENABLE);	*/
		clock_gettime		(CLOCK_MONOTONIC_RAW,TD.T);
		execvp			(argv[1],argv+1);
		return			1;
	}

	int		d[5];

	d[0]=
	syscall				(__NR_perf_event_open,pea  ,p,-1,-1  ,0);

	d[1]=
	syscall				(__NR_perf_event_open,pea+1,p,-1,d[0],0);

	d[2]=
	syscall				(__NR_perf_event_open,pea+2,p,-1,d[0],0);

	d[3]=
	syscall				(__NR_perf_event_open,pea+3,p,-1,d[0],0);

	d[4]=
	syscall				(__NR_perf_event_open,pea+4,p,-1,-1,0);

	siginfo_t			i;
	struct	rusage			r;

	int		ss;
	wait4				(p,&ss,0,&r);

	warnx				("user   %li.%09li",
					 r.ru_utime.tv_sec,
					 r.ru_utime.tv_usec*1000);
	warnx				("sys    %li.%09li",
					 r.ru_stime.tv_sec,
					 r.ru_stime.tv_usec*1000);



	clock_gettime			(CLOCK_MONOTONIC_RAW,TD.T+1);

	struct	rusage		R;

	getrusage			(RUSAGE_CHILDREN,&TD.R);
	warnx				("user   %li.%09li",
					 TD.R.ru_utime.tv_sec,
					 TD.R.ru_utime.tv_usec*1000);
	warnx				("sys    %li.%09li",
					 TD.R.ru_stime.tv_sec,
					 TD.R.ru_stime.tv_usec*1000);

	int64_t			s=	TD.T[1].tv_sec -TD.T[0].tv_sec;
	int64_t			n=	TD.T[1].tv_nsec-TD.T[0].tv_nsec;
	if				(0>n)
	{	n+=			0x3b9aca00;
		s--;
	}

	long long	a[5];
	memset				(a,0,sizeof(a));
	read				(d[0],a  ,sizeof(long long));
	read				(d[1],a+1,sizeof(long long));
	read				(d[2],a+2,sizeof(long long));
	read				(d[3],a+3,sizeof(long long));
	read				(d[4],a+4,sizeof(long long));

	float		f[2];
	f[0]=				(float)((a[0]-a[1])*100)/(float)a[0];
	f[1]=				(float)((a[2]-a[3])*100)/(float)a[2];

	warnx				("real   %li.%09li",s,n);
	warnx				("branch %.4f%%",f[1]);
	warnx				("cache  %.4f%%",f[0]);
	warnx				("opcode %lli"  ,a[4]);
	warnx				("minflt %i",TD.R.ru_minflt);
	warnx				("majflt %i",TD.R.ru_majflt);
	warnx				("maxrss %i",TD.R.ru_maxrss);
	write				(2,"\n",1);
	return				0;
}
