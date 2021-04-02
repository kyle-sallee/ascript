#	By Kyle Sallee in 2018 copyrighted.
#	From other projects; source code was not copied.
#	In the ascript manual page; the license is provided.

above		=	../../../
include			$(above)make.rules

$(REQ)readline:
	@echo		"byte"		>	$(REQ)readline

$(LP)readline:	readline.c
	-$(CC)	$(CFLAGS) $(LDFLAGS) -lhistory -lreadline -Wl,-soname,$(subst $(above)lib/,,$@) $< -o $@;	\
	if	! [ -f $(LP)readline ];					\
	then								\
	@echo	"libhistory         could not be linked or";		\
	@echo	"libreadline        could not be linked.";		\
	@echo	"The argot readline can   not be compiled";		\
	fi
