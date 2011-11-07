@SET_MAKE@

SUBDIRS = 	\
	themes	\
	src
	
distclean-local:
	rm -rf *.cache *~

EXTRA_DIST = autogen.sh gtk-xfce-engine-2.spec gtk-xfce-engine-2.spec.in

rpm : dist
	rpmbuild -ta $(PACKAGE)-$(VERSION).tar.gz
	@rm -f $(PACKAGE)-$(VERSION).tar.gz
