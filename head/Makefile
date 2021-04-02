#	By Kyle Sallee in 2015 and 2016 copyrighted.
#	From other projects source code was not copied.
#	In the ascript manual page; the license is provided.

# For compilation
# gcc
# if not used the
# $(CC) $(CFLAGS) ascript.h
# can be commented out, because
# for clang precompiled header file generation
# a different method is used and
# for the appended to file name bytes .pch
# are used.
# For ascript.h a precompiled header file
# if used
# about 10% compile duration
# is shaved.
# Thus 1 second faster compilation
# might be achieved.

CFLAGS		+=	-fpic
incdir		=	$(prefix)/include$(SUFFIX)
libdir		=	$(prefix)/lib$(SUFFIX)
source		=	$(wildcard *.c)
object		=	$(source:.c=.o)
.PHONY		:	all install posix

ascript.h.gch	:	ascript.h	common.h	string.h
	$(CC) $(CFLAGS) ascript.h

all		:	ascript.h.gch
posix		:

install		:	all
#	install -vm  755 -d $(DESTDIR)$(incdir)/ascript/
#	install -vm  644 -t $(DESTDIR)$(incdir)/ascript/ *.h

#	Although ELFSO encapsulated
#	the argot
#	are not libraries
#	the header files
#	are not installed.
#	To ascript header files
#	the permission is DENIED!

#	In argot C files
#	the ascript header files
#	by
#	#include "" encapsulation
#	are loaded.
#	The paths such as /usr/include/
#	are not even searched.
#	To search /usr/include/
#	#include <> ecapsulation
#	is requierd.
#	Library header file names and
#	ascript header file names match.
#	Different ascript versions have different header file content.
#	If installed, all kinds of nasty problems
#	will plague compilation.
