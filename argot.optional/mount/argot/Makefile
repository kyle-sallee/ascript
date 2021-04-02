#	By Kyle Sallee in 2018 copyrighted.
#	From other projects; source code was not copied.
#	In the ascript manual page; the license is provided.

above		=	../../../
include			$(above)make.rules

$(REQ)mount:
	@echo		"byte"		>	$(REQ)mount

$(LP)mount:	mount.c
	-$(CC)	$(CFLAGS) $(LDFLAGS) -Wl,-soname,$(subst $(above)lib/,,$@) $< -o $@
