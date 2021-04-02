#	By Kyle Sallee in 2018 copyrighted.
#	From other projects; source code was not copied.
#	In the ascript manual page; the license is provided.

sbindir		=	/sbin$(SUFFIX)
source		=	$(wildcard *.c)
executable	=	initreal initroot
.PHONY		:	all clean install posix
CFLAGS		+=	-fPIC

all		:	$(executable)

posix		:	all
$(executable)	:	$(source)

%		:	%.c
	-$(CC)	$(CFLAGS) $(LDFLAGS) $< -o $@
clean		:
	rm -f		$(executable)
install		:	all
	install -vm  755 -d $(DESTDIR)$(sbindir)/
	install -vm  755 -t $(DESTDIR)$(sbindir) $(executable)
