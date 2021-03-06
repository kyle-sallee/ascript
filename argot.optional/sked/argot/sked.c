/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"byte.h"
#include	"int.h"
#include	"sked.h"

PALIGN
static	SKEDDATA	sd=
{	.give.name="sked.give",
	.give.len=9,
	.give.op=opint4,
	.give.value.i=	1,

	.nice.name="sked.nice",
	.nice.len=9,
	.nice.op=opint4,

	.pid.name="sked.pid",
	.pid.len=8,
	.pid.op=opint8,

	.policy.name="sked.policy",
	.policy.len=0xb,
	.policy.op=opbyte,
	.policy.text="other",
	.policy.textlen=5,

	.priority.name="sked.priority",
	.priority.len=0xd,
	.priority.op=opint4,

	.deadline.name="sked.deadline",
	.deadline.len=0xd,
	.deadline.op=opint8,

	.period.name="sked.period",
	.period.len=0xb,
	.period.op=opint8,

	.runtime.name="sked.runtime",
	.runtime.len=0xc,
	.runtime.op=opint8,

	.affinity[0]=
	{	0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,

		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
		0xff,	0xff,	0xff,	0xff,	0xff,	0xff	,0xff,	0xff,
	},
};

SCV	set				(void)
{	int64_t		b;
	if			yay	(sd.give.value.i)
	b=				0;
	else
	b=				SCHED_FLAG_RESET_ON_FORK;

	sd.attr.sched_flags=		b;

	int32_t		c;
	switch				(sd.policy.text[0])
	{	default:	c=	SCHED_OTHER;	break;
		case	'b':	c=	SCHED_BATCH;	break;
		case	'd':	c=	SCHED_DEADLINE;	break;
		case	'f':	c=	SCHED_FIFO;	break;
		case	'i':	c=	SCHED_IDLE;	break;
		case	'r':	c=	SCHED_RR;	break;
	}

	sd.attr.sched_policy=		c;
	sd.attr.sched_nice=		sd.nice.value.i;
	sd.attr.sched_priority=		sd.priority.value.i;
	sd.attr.sched_deadline=		sd.deadline.value.i;
	sd.attr.sched_period=		sd.period.value.i;
	sd.attr.sched_runtime=		sd.runtime.value.i;
	sd.attr.size=
	sizeof				(struct sched_attr);

	sched_getaffinity		((pid_t)	 sd.pid.value.i,
					sizeof		(sd.affinity[1]),
					(cpu_set_t *)	 sd.affinity[1]);

	sched_setaffinity		((pid_t)	 sd.pid.value.i,
					sizeof		(sd.affinity[0]),
					(cpu_set_t *)	 sd.affinity[0]);

	errna=				0;
	int		d=
	syscall				(SYS_sched_setattr,	(pid_t)
					  sd.pid.value.i,
					 &sd.attr,0);

	sched_setaffinity		((pid_t)	 sd.pid.value.i,
					sizeof		(sd.affinity[1]),
					(cpu_set_t *)	 sd.affinity[1]);

	*Gz.at=				set;
	argot_jump			(d==0);
}

typedef	struct
{	uint8_t		a[8],b;
}	PNAME;

SCV	get				(void)
{
static	const	PNAME	n[]=
	{	{"other",	5},
		{"batch",	5},
		{"dead",	4},
		{"fifo",	4},
		{"idle",	4},
		{"rr",		2},
	};

	sd.attr.size=
	sizeof				(struct sched_attr);

	errna=				0;

	int		b=
	syscall				(SYS_sched_getattr,	(pid_t)
					 sd.pid.value.i,
					&sd.attr,sd.attr.size,0);

	*Gz.at=				get;
	if			nay	(0>b)
	{	argot_next		();
		return;
	}

	sd.give.value.i=			(sd.attr.sched_flags&
					 SCHED_FLAG_RESET_ON_FORK)==0;

	uint8_t		c;

	switch				(sd.attr.sched_policy)
	{	default:		c=	0;	break;
		case	SCHED_BATCH:	c=	1;	break;
		case	SCHED_DEADLINE:	c=	2;	break;
		case	SCHED_FIFO:	c=	3;	break;
		case	SCHED_IDLE:	c=	4;	break;
		case	SCHED_RR:	c=	5;	break;
	}

	__builtin_memcpy		(sd.policy.text,n[c].a,8);
	sd.policy.textlen=		n[c].b;

	sd.nice.value.i=		sd.attr.sched_nice;
	sd.priority.value.i=		sd.attr.sched_priority;
	sd.deadline.value.i=		sd.attr.sched_deadline;
	sd.period.value.i=		sd.attr.sched_period;
	sd.runtime.value.i=		sd.attr.sched_runtime;

	argot_skip			();
}

static		void	sked	(void)
{	*Gz.at=		sked;
	argot_next	();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180505",
	.official=	"20180505",
	.update=	"20200820"
};

inline	__attribute__((always_inline))
SCV	var_init		(void)
{	map_init		(&sd.give);
	map_init		(&sd.nice);
	map_init		(&sd.pid);
	map_init		(&sd.policy);
	map_init		(&sd.priority);
	map_init		(&sd.deadline);
	map_init		(&sd.period);
	map_init		(&sd.runtime);

	sd.give.show=
	sd.nice.show=
	sd.pid.show=
	sd.priority.show=	Gz.out.den4;
	sd.deadline.show=
	sd.period.show=
	sd.runtime.show=	Gz.out.den8;

/*	int4init		(&sd.give);
	int4init		(&sd.nice);
	int4init		(&sd.pid);
	byteinit		(&sd.policy);
	int4init		(&sd.priority);
	int8init		(&sd.deadline);
	int8init		(&sd.period);
	int8init		(&sd.runtime);

	__builtin_memcpy	(sd.give.name,		"sked.give",	9);
	__builtin_memcpy	(sd.nice.name,		"sked.nice",	9);
	__builtin_memcpy	(sd.pid.name,		"sked.pid",	8);
	__builtin_memcpy	(sd.policy.name,	"sked.policy",	0xb);
	__builtin_memcpy	(sd.priority.name,	"sked.priority",0xd);
	__builtin_memcpy	(sd.deadline.name,	"sked.deadline",0xd);
	__builtin_memcpy	(sd.period.name,	"sked.period",	0xb);
	__builtin_memcpy	(sd.runtime.name,	"sked.runtime",	0xc);

	sd.give.len=		9;
	sd.nice.len=		9;
	sd.pid.len=		8;
	sd.policy.len=		0xb;
	sd.priority.len=	0xd;
	sd.deadline.len=	0xd;
	sd.period.len=		0xb;
	sd.runtime.len=		0xc;

	sd.give.value.i=	1;
	__builtin_memcpy	(sd.policy.text,"other",5);
	sd.policy.textlen=	5;

*/

	vattach_faster		(&sd.give,	"sked.give");
	vattach_faster		(&sd.nice,	"sked.nice");
	vattach_faster		(&sd.pid,	"sked.pid");
	vattach_faster		(&sd.policy,	"sked.policy");
	vattach_faster		(&sd.priority,	"sked.priority");
	vattach_faster		(&sd.deadline,	"sked.deadline");
	vattach_faster		(&sd.period,	"sked.period");
	vattach_faster		(&sd.runtime,	"sked.runtime");

/*	__builtin_memset	(sd.affinity[0],0xff,PAGE);
*/
}


__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(sked,	"sked");
	aa		(get,	"skedget");
	aa		(set,	"skedset");
	aa_fini		();
	var_init	();
};
