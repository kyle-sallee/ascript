#	By Kyle Sallee in 2018 copyrighted.
#	From other projects; source code was not copied.
#	In the ascript manual page; the license is provided.

above		=	../../../
include			$(above)make.rules

$(REQ)pcre2:
	@echo	-e	"byte\nint"	>	$(REQ)pcre2

$(LP)pcre2:	pcre2.c
	-$(CC)	$(CFLAGS) $(LDFLAGS) -lpcre2-8 -Wl,-soname,$(subst $(above)lib/,,$@) $< -o $@
	@if	! [ -f $(LP)pcre2 ];				\
	then							\
	echo	"libpcre2-8    could not be linked.";		\
	echo	"The pcre2 argot can   not be compiled";	\
	fi
