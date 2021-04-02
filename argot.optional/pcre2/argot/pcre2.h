/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_PCRE2_H
#define		_A_PCRE2_H
#define		PCRE2_CODE_UNIT_WIDTH	8
#include	"byte.h"
#include	"int.h"
#include	<pcre2.h>

static	OPERATOR	oppcre2[1];


/*	map 2		PDATA	*/

typedef	struct
{	pcre2_code		*code;
	pcre2_match_data	*match_data;
/*	PCRE2_SIZE		start_offset;	*/
	PCRE2_SIZE		*ov;
	uint32_t		name_entry_size;
	uint32_t		name_count;
	PCRE2_SPTR		name_table;
	uint8_t			*name_table_end;

	int			match_count;
	int			error_code;
	PCRE2_SIZE		error_offset;

	VALUE			*errint;
	VALUE			*from;

	VMETA			*rx;
	VMETA			*input;
	VMETA			*output;
	VMETA			*refer;
	VMETA			*errtext;

	uint32_t		options_compile;
	uint32_t		options_compile_jit;
	uint32_t		options_match;

	PALIGN
	uint8_t			errtext_page[PAGE];
}	PDATA;

__attribute__((always_inline))
static	inline	 PDATA *	pdata	(VMETA *A)
{	return	(PDATA *)	A->dataaddr;
}

__attribute__((unused))
static	CALIGN	void	_pcre2free	(VMETA * const A)
{	PDATA		*P=
	pdata				(A);
	if				(P->code)
	pcre2_code_free			(P->code);

	if				(P->match_data)
	pcre2_match_data_free		(P->match_data);

	cede				(A->dataaddr,A->datasize);
	vmeta_free			(A);
}

__attribute__((always_inline))
static	inline	void	pcre2subnew	(VMETA *A)
{	A->op=			oppcre2;
	A->free=		_pcre2free;
	map_add			(A,0,sizeof(PDATA));
	PDATA		*P=
	pdata			(A);

	VMETA		*B=
	var_new_sub		(".errno",A);
	int4init		(B);
/*	B->val=			&P->errint;	*/
	P->errint=		&B->value;

	VMETA		*C=
	var_new_sub		(".errtext",A);
	byteinit		(C);
	C->textaddr=		(void *)	&P->errtext_page;
	C->textsize=		PAGE;
	P->errtext=		C;

	VMETA		*D=
	var_new_sub		(".rx",A);
	byteinit		(D);
	P->rx=			D;

	VMETA		*E=
	var_new_sub		(".input",A);
	byteinit		(E);
	P->input=		E;

	VMETA		*I=
	var_new_sub		(".output",A);
	byteinit		(I);
	P->output=		I;

	VMETA		*J=
	var_new_sub		(".from",A);
	int4init		(J);
/*	J->val=			&P->from;	*/
	P->from=		&J->value;

	VMETA		*K=
	var_new_sub		(".refer",A);
	int4init		(K);
	P->refer=		K;

	A->trash=		K->trash;
	K->trash=		NULL;
	B->trash=		K;
}
#endif
