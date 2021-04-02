/*	By Kyle Sallee in 2017 copyrighted.
	By initroot.c a minimal init process
	suitable for use on the rootFS is provided.
	When CAD, ctrl alt delete, is depressed
	SIGINT is received and /sbin/cad is invoked.
	/sbin/cad should acquire a virtual console,
	change to the virtual console and provide a menu
	Useful options could be log in, sleep, reboot, etc...
	In the ascript manual page; the license is provided.
*/


#define		_GNU_SOURCE
#define		_POSIX_C_SOURCE	200809L
#include	<err.h>
#include	<fcntl.h>
#include	<sched.h>
#include	<signal.h>
#include	<spawn.h>
#include	<sys/mount.h>
#include 	<sys/prctl.h>
#include	<sys/reboot.h>
#include	<sys/stat.h>
#include	<sys/types.h>
#include	<sys/wait.h>
#include	<unistd.h>

				extern		char		**environ;
__attribute__((aligned(0x40)))	static	struct	sigaction	sa;

__attribute__((aligned(0x40)))
static		void	cad	(int s)
{	pid_t		p;
	posix_spawn	(&p,
			 "/sbin/cad",NULL,NULL,(char * const [])
			{"/sbin/cad",NULL},environ);
}

static	inline	void	cad_init	(void)
{
/*	sigemptyset	(&sa.sa_mask);	*/
	sa.sa_flags=	SA_RESTART|SA_NODEFER;
	sa.sa_handler=	cad;
	sigaction	(SIGINT,&sa,NULL);
	reboot		(RB_DISABLE_CAD);
}

/*
The function fini is a fantastic idea.
When to run is not clear.
A realFS overlaying the rootFS was considered and rejected.
*/

__attribute__((unused))
static	void	fini	(void)
{	int	a=
	open		("/proc/sysrq-trigger",O_WRONLY);
	write		(a,"u",1);
	close		(a);
/* For all mounted filesystems a read only remount is attempted */
	execv		("/fini",(char * const[])
			{"/fini",NULL});
	warnx		("reboot(RB_POWER_OFF);");
	reboot		(RB_POWER_OFF);
}

__attribute__((noinline))
__attribute__((aligned(0x40)))
__attribute__((constructor))
static	void	setup	(void)
{	prctl		(PR_SET_NAME,"init");
	signal		(SIGCHLD,SIG_IGN);
	cad_init	();
}

__attribute__((aligned(0x40)))
		void	main	(int argc,char **argv)
{	while		(1)
	pause		();
}
