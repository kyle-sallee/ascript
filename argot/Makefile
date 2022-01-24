#	By Kyle Sallee in 2019 copyrighted.
#	From other projects source code was not copied.
#	In the ascript manual page; the license is provided.

above		=	../
include			$(above)make.rules
all		:	$(LP)	$(fast)	$(req)

clean		:
	rm	-f	$(above)lib

$(LP):
	mkdir	-p	$(LS)	$(REQ)

$(LP)a:	a.c
	$(CC)	$(CFLAGS) $(LDFLAGS) -Wl,-soname,$(subst $(above)lib/,,$@) $< -o $@
#	ln	-fs	../a	$(ALT)aname

$(REQ)amount:
	@echo		"int"		>	$(REQ)amount

$(REQ)as:
	@echo	-e	"dec\nint"	>	$(REQ)as

$(LP)as:	as.c
	$(CC)	$(CFLAGS) $(LDFLAGS) -lm -Wl,-soname,$(subst $(above)lib/,,$@) $< -o $@

$(REQ)cast:
	@echo		"int"		>	$(REQ)cast

$(REQ)char:
	@echo	-e	"byte\nint"	>	$(REQ)char

$(REQ)clock:
	@echo		"int"		>	$(REQ)clock

#$(LP)dec:	dec.c
#	$(CC)	$(CFLAGS) $(LDFLAGS) -Wl,-soname,$(subst $(above)lib/,,$@) $< -o $@
#	ln	-fs	../dec	$(ALT)dectmp

$(REQ)dir:
	@echo		"int"		>	$(REQ)dir

$(REQ)dub:
	@echo	-e	"byte\nint"	>	$(REQ)dub

$(REQ)duct:
	@echo		"int"		>	$(REQ)duct

$(REQ)dup:
	@echo		"int"		>	$(REQ)dup

$(REQ)env:
	@echo		"byte"		>	$(REQ)env

$(REQ)err:
	@echo	-e	"byte\nint"	>	$(REQ)err

$(REQ)exe:
	@echo	-e	"env\npara\nsire"	>	$(REQ)exe

$(REQ)exefast:
	@echo	-e	"sire"		>	$(REQ)exefast

$(REQ)format:
	@echo		"int"		>	$(REQ)format

$(REQ)fun:
	@echo		"int"		>	$(REQ)fun

$(REQ)id:
	@echo	-e	"byte\nint"	>	$(REQ)id

#$(LP)int:	int.c
#	$(CC)	$(CFLAGS) $(LDFLAGS) -Wl,-soname,$(subst $(above)lib/,,$@) $< -o $@
#	ln	-fs	../int	$(ALT)inttmp

$(REQ)intray:
	@echo		"int"		>	$(REQ)intray

$(REQ)io:
	@echo	-e	"byte\nint"	>	$(REQ)io

$(REQ)ipv4:
	@echo	-e	"byte\nint"	>	$(REQ)ipv4

$(REQ)ipv6:
	@echo	-e	"byte\nint"	>	$(REQ)ipv6

$(REQ)kvp:
	@echo		"byte"		>	$(REQ)kvp

$(REQ)line:
	@echo		"byte"		>	$(REQ)line

$(REQ)list:
	@echo	-e	"ambit\nbyte"	>	$(REQ)list

#$(REQ)loopvar:
#	@echo		"int"		>	$(REQ)loopvar

$(REQ)mdk:
	@echo		"int"		>	$(REQ)mdk

$(REQ)net:
	@echo	-e	"byte\nint"	>	$(REQ)net

$(REQ)node:
	@echo	-e	"byte\nint"	>	$(REQ)node

$(REQ)nodelist:
	@echo	-e	"byte\nint"	>	$(REQ)nodelist

$(REQ)nodesub:
	@echo	-e	"byte\nint"	>	$(REQ)nodesub

$(REQ)nodewant:
	@echo		"sire"		>	$(REQ)nodewant
#	@echo		"int"		>	$(REQ)nodewant

$(REQ)para:
	@echo		"byte"		>	$(REQ)para

$(REQ)part:
	@echo	-e	"ambit\nbyte\nint"	>	$(REQ)part

$(REQ)pathname:
	@echo		"byte"		>	$(REQ)pathname

$(LP)per_linux32:	per_linux32.c
	-$(CC)	$(CFLAGS) $(LDFLAGS) -Wl,-soname,$(subst $(above)lib/,,$@) $< -o $@

$(REQ)ray:
	@echo		"int"		>	$(REQ)ray

$(LP)ray:	ray.c
	$(CC)	$(CFLAGS) $(LDFLAGS) -Wl,-soname,$(subst $(above)lib/,,$@) $< -o $@
#	ln	-fs	../ray	$(ALT)rayset

$(REQ)realpath:
	@echo		"byte"		>	$(REQ)realpath

$(REQ)rlimit:
	@echo		"int"		>	$(REQ)rlimit

$(LP)rt:	rt.c
	$(CC)	$(CFLAGS) $(LDFLAGS) -lrt -Wl,-soname,$(subst $(above)lib/,,$@) $< -o $@

$(REQ)rusage:
	@echo		"int"		>	$(REQ)rusage

# By ascript -ldl is already provided.
#$(LP)segfault:	segfault.c
#	$(CC)	$(CFLAGS) $(LDFLAGS) -ldl -Wl,-soname,$(subst $(above)lib/,,$@) $< -o $@

$(REQ)self:
	@echo	-e	"byte\nint"		>	$(REQ)self

$(REQ)sem:
	@echo		"dub"			>	$(REQ)sem

$(LP)sem:	sem.c
	$(CC)	$(CFLAGS) $(LDFLAGS) -lpthread -Wl,-soname,$(subst $(above)lib/,,$@) $< -o $@

$(REQ)sig:
	@echo	-e	"int"			>	$(REQ)sig

$(REQ)sire:
	@echo		"int"			>	$(REQ)sire

$(REQ)size:
	@echo		"int"			>	$(REQ)size

$(REQ)sock:
	@echo		"int"			>	$(REQ)sock

$(REQ)softreq:
	@echo	-e	"byte\nsire"		>	$(REQ)softreq

$(LP)sortback:
	@echo	"$@ skip"

$(LP)sortinc:
	@echo	"$@ skip"

$(LP)sortbinc:
	@echo	"$@ skip"

$(LP)sortdec:
	@echo	"$@ skip"

$(LP)sortlong:
	@echo	"$@ skip"

$(LP)sortsame:
	@echo	"$@ skip"

$(LP)sorttiny:
	@echo	"$@ skip"

$(REQ)sort:
	@echo	-e	"byte\nsire"		>	$(REQ)sort

$(LP)sort:	sort.c			$(LS)sortback.o    $(LS)sortbinc.o    $(LS)sortinc.o     $(LS)sortdec.o    $(LS)sortlong.o    $(LS)sortsame.o    $(LS)sorttiny.o
	$(CC)	$(CFLAGS) $(LDFLAGS) -l:$(LS)sortback.o -l:$(LS)sortbinc.o -l:$(LS)sortinc.o  -l:$(LS)sortdec.o -l:$(LS)sortlong.o -l:$(LS)sortsame.o -l:$(LS)sorttiny.o -Wl,-soname,$(subst $(above)lib/,,$@) $< -o $@ -Wl,--allow-multiple-definition

$(REQ)stat:
	@echo	-e	"byte\nint"		>	$(REQ)stat

$(REQ)statvfs:
	@echo		"int"			>	$(REQ)statvfs

#$(REQ)sum:
#	@echo	-e	"byte\nint"		>	$(REQ)sum

$(REQ)timer:
	@echo	-e	"sig\nrt"		>	$(REQ)timer

$(REQ)tm:
	@echo	-e	"byte\nint"		>	$(REQ)tm

$(REQ)top:
	@echo	-e	"ambit\nbyte"		>	$(REQ)top

$(REQ)trim:
	@echo	-e	"byte"			>	$(REQ)trim

$(REQ)uname:
	@echo		"byte"			>	$(REQ)uname

$(REQ)utmpx:
	@echo	-e	"byte\nint"		>	$(REQ)utmpx

$(REQ)var:
	@echo	-e	"byte\nint"		>	$(REQ)var

$(REQ)view:
	@echo	-e	"byte\nint"		>	$(REQ)view

install		:	all
	cp	-at	$(DESTDIR)$(libdir)		$(LP)

all		:	$(library)
