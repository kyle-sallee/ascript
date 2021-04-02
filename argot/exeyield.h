/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_EXE_YIELD_H
#define		_A_EXE_YIELD_H
extern	char	**environ;

__attribute__((unused))
static		void	exeyield	(uint8_t **v)
{	errna=	0;
	execvpe	(v[0],(char **)v,environ);
	warn	("%-19s %-20s","execvpe",v[0]);
}
#endif
