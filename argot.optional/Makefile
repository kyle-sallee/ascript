#	By Kyle Sallee in 2019
#	In the ascript manual page; the license is provided.

#export	CFLAGS	:=	$(filter-out -DSANS_GOT_GZ,$(CFLAGS))
mf		=	$(wildcard */*/Makefile)
sub		=	$(mf:/Makefile=)
.PHONY		:	all clean lib install	$(sub)

all		:	$(sub)

$(sub):
	$(MAKE) -C	$@

install:	all
	for dir in $(sub); do $(MAKE) -C $$dir install;	done

clean:
	for dir in $(sub); do $(MAKE) -C $$dir   clean;	done
