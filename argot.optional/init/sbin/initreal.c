/*	By Kyle Sallee in 2017 copyrighted.
	By initreal.c a minimal init process
	suitable for use on the realFS is provided.
	Unlike initroot.c
	for CAD depression
	a signal is not received.
	Thus initreal.c source is less complex.
	In the ascript manual page; the license is provided.
*/

#include	<signal.h>
#include 	<sys/prctl.h>
#include	<unistd.h>

__attribute__((constructor))
__attribute__((aligned(0x40)))
static	void	setup	(void)
{	prctl	(PR_SET_NAME,"init");
	signal	(SIGCHLD,SIG_IGN);
}
__attribute__((aligned(0x40)))
void	main	(void)
{	while	(1)
	pause	();
}
