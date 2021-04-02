/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_SORT_H
#define		_A_SORT_H
#include	"byte.h"
#include	"int.h"

#define		LINEMAX		0x1000000*sizeof(SORT_INDEX)	/* 256m */
#define		BYTEMAX		0x40000000			/* 1g */

#include	"bsort.h"

extern	OPERATOR	varsortop[0xb];

typedef	struct
{	uint32_t	count;
/*	uint64_t	pad;	*/
	SORT_INDEX	*first;

	VMETA		*ambit;
	VALUE		free,pre,smp;
	uint8_t		amb;

/* new below */
	SORT_INDEX	*sort_index;
	uint32_t	 sort_index_size;
}	SORTMETA;

__attribute__((always_inline))
static	inline	 SORTMETA * sortmeta	(VMETA *A)
{	return	(SORTMETA *)	A->dataaddr;
}

__attribute__((always_inline))
static	inline	 SORT_INDEX * sort_index	(VMETA *A)
{	return	sortmeta(A)->sort_index;
/*	A->dataaddr;	*/
}

__attribute__((always_inline))
static	inline	 uint8_t * byte_index	(VMETA *A)
{	return	(uint8_t *)	A->textaddr;
}
#endif
