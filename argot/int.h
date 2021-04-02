/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_INT_H
#define		_A_INT_H
ALIVE	int4init	(VMETA *A){A->op=opint4;	A->show=Gz.out.den4;}
ALIVE	int8init	(VMETA *A){A->op=opint8;	A->show=Gz.out.den8;}
ALIVE	fix8init	(VMETA *A){A->op=opfix8;	A->show=Gz.out.fix8;}
ALIVE	nanodata	(VMETA *A){A->textlen=9;}
ALIVE	dex4data	(VMETA *A){A->textlen=8;}
ALIVE	dex8data	(VMETA *A){A->textlen=0x10;}
ALIVE	oct2data	(VMETA *A){A->textlen=8;}
ALIVE	oct4data	(VMETA *A){A->textlen=0xc;}
ALIVE	oct8data	(VMETA *A){A->textlen=0x18;}
#endif
