#	By Kyle Sallee in 2018 copyrighted.
#	From other projects; source code was not copied.
#	In the ascript manual page; the license is provided.

above		=	../../../
include			$(above)make.rules

$(REQ)pam:
	@echo	-e	"byte"	>	$(REQ)pam

$(LP)pam:	pam.c
	-$(CC)	$(CFLAGS) $(LDFLAGS) -lpam -lpam_misc -Wl,-soname,$(subst $(above)lib/,,$@) $< -o $@;
	@if	! [ -f $(LP)pam ];				\
	then							\
	echo	"libpam        could not be linked or";		\
	echo	"libpam_misc   could not be linked.";		\
	echo	"The pam argot can   not be compiled";		\
	fi
