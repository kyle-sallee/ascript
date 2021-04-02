/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_TRACE_H
#define		_A_TRACE_H

extern	OPERATOR	vartraceop[1];

#define		TRACE_FILE	1<<0
#define		TRACE_LINE	1<<1
#define		TRACE_NAME	1<<2
#define		TRACE_ORIGIN	1<<3
#define		TRACE_PARA	1<<4
#define		TRACE_PART	1<<5
#define		TRACE_SKIP	1<<6
#define		TRACE_TARGET	1<<7
#define		TRACE_TIME	1<<8
#define		TRACE_TOLL	1<<9

/*	maps:
	map 0:	TRACEDATA
	map 2:	HUGE clone stack
*/

typedef	struct		tracedata
{	int64_t			t;	/* opcode toll */
	uint32_t		i;	/* desired information */
	int			d;	/* output descriptor */
	int			len;	/* text len */
	void			(**L)	(void);	/* script location */
	pid_t			p[2];	/* progenitor, progeny tracer */
	struct	timespec	T[2];	/* clock_gettime CLOCK_THREAD_CPUTIME_ID */
	struct	sigaction	sa[1];
	uint8_t	text		[HUGE]; /* trace output */
	uint8_t	stack		[HUGE];	/* clone stack */
}	TRACEDATA;
#endif
