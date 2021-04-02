#	By Kyle Sallee in 2019
#	In the ascript manual page; the license is provided.

#export	CFLAGS	:=	$(filter-out -DSANS_GOT_GZ,$(CFLAGS))
contrib_make	=	$(wildcard */*/Makefile)
contrib_sub	=	$(contrib_make:/Makefile=)
.PHONY		:	all clean lib install	$(contrib_sub)

all		:	$(contrib_sub)

$(contrib_sub):
	$(MAKE) -C	$@

install:	all
	for dir in $(contrib_sub); do $(MAKE) -C $$dir install;	done

clean:
	for dir in $(contrib_sub); do $(MAKE) -C $$dir   clean;	done
