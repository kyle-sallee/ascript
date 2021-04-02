#	By Kyle Sallee in 2015 and 2016 copyrighted.
#	In the ascript manual page; the license is provided.

include			version.make
export	CC	?=	gcc
export	prefix	=	/usr

# Sans -foptimize-sibling-calls
# a    stack underflow
# is   more  probable;
# more opcodes must execute.

include			make.enable/*
export	CFLAGS	+=	-O
export	CFLAGS	+=	-pipe
export	CFLAGS	+=	-foptimize-sibling-calls
export	CFLAGS	+=	-foptimize-strlen
export	CFLAGS	+=	-fomit-frame-pointer
export	CFLAGS	+=	-fshrink-wrap


# Gz is a know address
# For the ascript executable position independent code if used
# not only does performance tank, but a segfault will result!
# Eat pie and barf!
export	CFLAGS	+=	-no-pie

# For memcpy for memset library functions if called
# many inane push/pop are emitted and
# the performance tanks!
# For memcpy for memset library functions why not deprecated
# can not be surmised!

export	CFLAGS	+=	-minline-all-stringops
export	CFLAGS	+=	-mstringop-strategy=rep_8byte
export	CFLAGS	+=	-mmemcpy-strategy=unrolled_loop:15:noalign,vector_loop:512:noalign,rep_8byte:-1:noalign
export	CFLAGS	+=	-mmemset-strategy=unrolled_loop:15:noalign,vector_loop:512:noalign,rep_8byte:-1:noalign

export	CFLAGS	+=	-fstrict-aliasing
export	CFLAGS	+=	-fstrict-overflow

export	CFLAGS	+=	-finline-functions
export	CFLAGS	+=	-finline-functions-called-once
export	CFLAGS	+=	-finline-small-functions
export	CFLAGS	+=	-fno-indirect-inlining
export	CFLAGS	+=	-fpartial-inlining

export	CFLAGS	+=	-fno-caller-saves
export	CFLAGS	+=	-fno-crossjumping

export	CFLAGS	+=	-fgcse-after-reload
export	CFLAGS	+=	-fpredictive-commoning
export	CFLAGS	+=	-fsplit-paths

export	CFLAGS	+=	-funsafe-loop-optimizations
export	CFLAGS	+=	-fno-expensive-optimizations
export	CFLAGS	+=	-freorder-blocks
export	CFLAGS	+=	-freorder-blocks-algorithm=stc

export	CFLAGS	+=	-fno-ipa-icf
export	CFLAGS	+=	-fno-ipa-icf-functions
export	CFLAGS	+=	-fno-reorder-functions
export	CFLAGS	+=	-fthread-jumps
export	CFLAGS	+=	-fno-tree-tail-merge
export	CFLAGS	+=	-ftree-vrp
export	CFLAGS	+=	-fdevirtualize
export	CFLAGS	+=	-fdevirtualize-speculatively

export	CFLAGS	+=	-fno-combine-stack-adjustments
export	CFLAGS	+=	-fno-defer-pop
export	CFLAGS	+=	-fno-guess-branch-probability

#export	CFLAGS	+=	-ftree-loop-vectorize
#export	CFLAGS	+=	-fvect-cost-model=unlimited
#export	CFLAGS	+=	-ftree-slp-vectorize
#export	CFLAGS	+=	-ftree-pre
#export	CFLAGS	+=	-ftree-partial-pre
#export	CFLAGS	+=	-funswitch-loops

export	CFLAGS	+=	-falign-loops=0
export	CFLAGS	+=	-falign-jumps=0
#export	CFLAGS	+=	-falign-functions=64

# The  functions
# when cache line size aligned
# the  cache usage
# is   improved.
# The  loop reiteration opcode
# the  jump target      opcode
# when cache line size aligned
# more RAM tends to be wasted and
# inefficient cache use becomes.

#export	CFLAGS	+=	-g
export	CFLAGS	+=	-Wunused
export	CFLAGS	+=	-Wsuggest-attribute=pure
export	CFLAGS	+=	-Wsuggest-attribute=const
export	CFLAGS	+=	-Wsuggest-attribute=noreturn
export	CFLAGS	+=	-DMAJOR=$(major)
export	CFLAGS	+=	-DMINOR=$(minor)
#export	CFLAGS	+=	-Winvalid-pch
export	LDFLAGS +=	-Wl,-O1 -Wl,-z,relro -Wl,-z,combreloc -Wl,-z,noexecstack

MAKEFLAGS	=	-j16
#MAKEFLAGS	=	-j1
sub		=	argot man
optional	=	$(wildcard argot.optional/*/*/Makefile)
sub		+=	$(optional:/Makefile=)

.PHONY		:	all clean lib install $(sub)
.PHONY		:	ascript
LP		=	lib/ascript.$(major).$(minor)/
REQ		=	lib/ascript.$(major).$(minor)/req/
#ALT		=	lib/ascript.$(major).$(minor)/alt/
#FAKE		=	lib.fake/
LS		=	lib.static/

all		:
#	mkdir	-p	$(FAKE)	$(LP)	$(LS)	$(REQ)	$(ALT)
#	mkdir	-p	$(LP)	$(LS)	$(REQ)	$(ALT)
	mkdir	-p	$(LP)	$(LS)	$(REQ)
	$(MAKE)	-C	ascript
	$(MAKE)	-C	head
	$(MAKE)	-C	argot
	$(MAKE)	-C	argot.optional
	$(MAKE)	-C	argot.contrib

install:
	$(MAKE)	-C	argot		install
	$(MAKE)	-C	argot.optional	install
	$(MAKE)	-C	man		install
	$(MAKE)	-C	argot.contrib	install
