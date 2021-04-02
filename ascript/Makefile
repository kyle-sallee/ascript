#	By Kyle Sallee in 2015 and 2016 copyrighted.
#	In the ascript manual page; the license is provided.

bindir		=	/bin$(SUFFIX)
executable	=	ascript
.PHONY		:	all clean install
CFLAGS		+=	-iquote../head -iquote../argot
STRIPPER	=	-Wl,-s
STRIPME		:=	$(filter $(STRIPPER),$(LDFLAGS))
LDFLAGS		:=	$(filter-out $(STRIPPER),$(LDFLAGS))
LDFLAGS		+=	-ldl
LDFLAGS		+=	-Wl,--export-dynamic
LP		=	../lib/

all		:	$(executable)	$(LP)libascript.so.$(major).$(minor)

$(LP)libascript.so.$(major).$(minor):
	$(CC)	-O0 -fpic -shared -nodefaultlibs -Wl,-soname,libascript.so.$(major) -o $@
#	ln	-fsv	$(@:../lib/=)	$(@:.$(minor)=)
#	ln	-fsv	$(@:../lib/=)	$(@:.$(major).$(minor)=)

# ../argot.compiled.in/*.c
ascript		:	*.c
	rm	-f	../head/ascript.h.gch
	$(CC)	$(CFLAGS) $(LDFLAGS) 	     $^ -o $@
#	$(CC)	$(CFLAGS) $(LDFLAGS) 	-lrt $^ -o $@
# shm_open if used -lrt is required, but in ascript shm_open is not used.
# -lrt on ascript is disgusting, but by librt considerable already loaded libs
# are linked.
# by argot full/int librt if linked
# for library loading a magnitude more opcodes must execute.
# dynamic linking is garbage.
# for most programs during runtime linking
# several hundred thousands opcodes probably execute.
# A simple argot to load
# more than 25 thousand opcodes must execute.

	if	[ -f ../make.enable/sans_got_gz ];	\
	then	nm -S ascript | sed "s|\([^ ]*\) [^ ]* B Gz|#define Gz	(*(GzT *)0x\1)|p;d" > ../head/ascript-sans-got-gz.h;	\
	fi
	if	[ -n "$(STRIPME)" ]; then strip ascript; fi

#	then	nm -S ascript | sed "s|\([^ ]*\) [^ ]* B Gz|#define Gz	(*(GzT *)0x\1)|p;d" > ../head/ascript-sans-got-gz.h;	\

clean		:
	rm -f		$(executable)

install		:	all
	install -vm  755 -d $(DESTDIR)$(bindir)/
	install -vm  755 -t $(DESTDIR)$(bindir) ascript
