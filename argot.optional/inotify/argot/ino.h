/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_INO_H
#define		_A_INO_H
#include	<sys/inotify.h>

typedef	struct
{	struct	inotify_event	a;
	uint8_t			b[PAGE];
}	IEB;

typedef	struct
{	void		(**P_IN_ACCESS)		(void);
	void		(**P_IN_ATTRIB)		(void);
	void		(**P_IN_CLOSE_WRITE)	(void);
	void		(**P_IN_CLOSE_NOWRITE)	(void);
	void		(**P_IN_CREATE)		(void);
	void		(**P_IN_DELETE)		(void);
	void		(**P_IN_DELETE_SELF)	(void);
	void		(**P_IN_MODIFY)		(void);
	void		(**P_IN_MOVE_SELF)	(void);
	void		(**P_IN_MOVED_FROM)	(void);
	void		(**P_IN_MOVED_TO)	(void);
	void		(**P_IN_OPEN)		(void);

	VMETA		*to[2];
/*	uint32_t	m;	*/	/* the desired event mask */
	int		s;		/* the pathname length */
}	WATCH;

typedef	struct
{	int64_t			i,a,d,m,s;
	/*	i is the ino descriptor must be first.
		a is the available pathname count.
		d is the deleted   pathname count.
		m is the maximum   pathname count.
		s is the realtime  signal   number.
	*/

/*	VALUE			set_mask;	*/
/*	VALUE			set_use;	*/

/**
	VALUE			now_move;
	VALUE			now_mask;
	VALUE			now_loss;
**/

/*	VMETA			*set_cfg;	*/
/*	VMETA			*set_pin;	*/

/**	VMETA			*now_name;	**/
	VMETA			*to[2];

/**	uint8_t			**now_watch_addr;
	int64_t			*now_name_len;
	int64_t			*now_watch_len;
**/
/*	uint64_t		*set_watch_len;
	uint8_t			set_watch	[PAGE];
*/
	uint32_t		far;
	int32_t			use;
	IEB			ieb;
	WATCH			w;	/* temporary use */
}	INO;
#endif
