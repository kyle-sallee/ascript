#	By Kyle Sallee in 2018 copyrighted.
#	From other projects; source code was not copied.
#	In the ascript manual page; the license is provided.

above		=	../../../
include			$(above)make.rules

$(REQ)pts:
	@echo		"int"		>	$(REQ)pts

$(LP)pts:	pts.c
	-$(CC)	$(CFLAGS) $(LDFLAGS) -Wl,-soname,$(subst $(above)lib/,,$@) $< -o $@;
#	-$(CC)	$(CFLAGS) $(LDFLAGS) -lutil -Wl,-soname,$(subst $(above)lib/,,$@) $< -o $@;
	@if	! [ -f $(LP)pts ];				\
	then							\
	echo	"libutil       could not be linked?";		\
	echo	"The pts argot can   not be compiled?";		\
	fi
