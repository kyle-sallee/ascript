#	By Kyle Sallee in 2018 copyrighted.
#	From other projects; source code was not copied.
#	In the ascript manual page; the license is provided.

above		=	../../../
include			$(above)make.rules

$(REQ)ko:
	@echo	-e	"acfg\nbyte\nsire"	>	$(REQ)ko

$(LP)ko:	ko.c
	-$(CC)	$(CFLAGS) $(LDFLAGS) -Wl,-soname,$(subst $(above)lib/,,$@) $< -o $@
