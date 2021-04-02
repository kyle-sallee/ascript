/*	By Kyle Sallee 2019 copyrighted.
*/

#define		PROGRAM		1
#include	"ascript.h"

__attribute__((destructor(101)))
static	CALIGN	void	theend		(void)
{	ENDPART		*E;
	if			nay	(  Gz.endpart!=NULL)
	for				(E=Gz.endpart,
					   Gz.endpart= NULL;E;E=E->F)
	{	memcpy			(&Gz.mhub,E->M,
					(E->M->a-Gz.mhub.v+2)*sizeof(void *));
		(Gz.aat=E->L)->func	();
	}
}
