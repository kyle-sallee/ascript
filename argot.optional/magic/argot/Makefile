#	By Kyle Sallee in 2018 copyrighted.
#	From other projects; source code was not copied.
#	In the ascript manual page; the license is provided.

above		=	../../../
include			$(above)make.rules

$(REQ)magic:
	@echo		"byte"	>	$(REQ)magic

$(LP)magic:	magic.c
	-$(CC)	$(CFLAGS) $(LDFLAGS) -lmagic -Wl,-soname,$(subst $(above)lib/,,$@) $< -o $@
