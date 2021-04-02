#	By Kyle Sallee in 2015 and 2016 copyrighted.
#	From other projects source code was not copied.
#	In the ascript manual page; the license is provided.

executable	=	timer
.PHONY		:	all clean install posix
CFLAGS		+=	-I../head

all		:	$(executable)
posix		:	all

timer		:	*.c
	$(CC)	$(CFLAGS) $(LDFLAGS) 	$^ -o $@

clean		:
	rm -f		$(executable)

install		:	;
