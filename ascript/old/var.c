/*	By Kyle Sallee from 2015 ... 2019 copyrighted.
	Used by ascript.c and argots
	by   var.c some functions are provided.
*/

#define		PROGRAM		1
#include	"ascript.h"
#include	"ascript-string.h"

__attribute__((noinline))
static	CALIGN	VMETA	*vp_new	(void)
{	return
	mmap			(NULL,PAGE,
				 PROT_READ|PROT_WRITE,
				 MAP_ANONYMOUS|MAP_PRIVATE,-1,0);
}

static	CALIGN	VMETA	*vp_new		(void);

	CALIGN	VMETA	*vmeta_new	(void)
{	VMETA		*A;
	VMETA_POOL	*vp=		Gz.vp+(Gz.vpc++!=0);

	if			yay	(vp->b!=0)
	{	vp->b=			(vp->b+1)%(PAGE/sizeof(VMETA));
		A=			 vp->a++;
	}
	else
	{	vp->b=			2;
		A=
		vp_new			()+1;
		vp->a=			A+1;
			/*	With page start data
				the CPU cache is crammed.
				Skip it!
				That's correct, per 4096 byte page
				for VMETA use
				the first 512 bytes will be
				WASTED!
			*/
	}
	Gz.vpc--;

	map_init			(A);
	A->free=			var_free;
	return				A;
}

/* To file ascript-inline.h the function vmeta_free was moved. */

	CALIGN	void	var_from_vless	(VMETA **A)
{	VLESS		*B=	(VLESS *)	*A;

	VMETA		*C=
	vmeta_new			();
	C->vam=				B->vam;

	memcpya				(C->name,B->map[0].addr,
					 C->len= B->map[0].len);
	vattach_fast			(C);
	*A=				C;
}

	CALIGN	void	mhub_var_be	(void)
{	VMETA		*A,**V;
	for				(V=Gz.mhub.v;*V;V++)
	{	A=	vmeta_new	();
		memcpya			(A->name,V[0]->map[0].addr,
					 A->len= V[0]->map[0].len);
		if			(V[0]->vam!=(void *)V[0]->free)
		A->vam=			 V[0]->vam;
		else
		A->vam=			&Gz.vam[bit128_to_bit16(A->name)];
		vattach_fast		(A);
		*V=			A;
	}
}

__attribute__((noinline))
	CALIGN	void	var_free	(VMETA *A)
{
/*	while				(A->box)
	var_free			(A->box);
*/

	MAP		*m=		A->map;

	if	nay	(m[0].unmap)	cede	(m[0].addr,m[0].size);
	if	nay	(m[1].unmap)	cede	(m[1].addr,m[1].size);
	if	nay	(m[2].unmap)	cede	(m[2].addr,m[2].size);
	if	nay	(m[3].unmap)	cede	(m[3].addr,m[3].size);

	vmeta_free			(A);
}
