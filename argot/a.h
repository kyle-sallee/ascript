/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_A_H
#define		_A_A_H

#define	target_object_to_stack()				\
	VMETA		*tostack[2];				\
	__builtin_memcpy	(tostack,Gz.to,sizeof(Gz.to));

#define	target_object_from_stack()				\
	__builtin_memcpy	(Gz.to,tostack,sizeof(Gz.to));

#endif
