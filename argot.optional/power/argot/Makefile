#	By Kyle Sallee in 2018 copyrighted.
#	From other projects; source code was not copied.
#	In the ascript manual page; the license is provided.

above		=	../../../
include			$(above)make.rules

$(REQ)power:
	@echo		"int"		>	$(REQ)power

$(LP)power:	power.c
	-$(CC)	$(CFLAGS) $(LDFLAGS) -Wl,-soname,$(subst $(above)lib/,,$@) $< -o $@
