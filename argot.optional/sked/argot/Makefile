#	By Kyle Sallee in 2018 copyrighted.
#	From other projects; source code was not copied.
#	In the ascript manual page; the license is provided.

above		=	../../../
include			$(above)make.rules

clean		:
	rm	-f	$(LP)*

$(REQ)sked:
	@echo	-e	"byte\nint"	>	$(REQ)sked

$(LP)sked:	sked.c
	-$(CC)	$(CFLAGS) $(LDFLAGS) -Wl,-soname,$(subst $(above)lib/,,$@) $< -o $@
