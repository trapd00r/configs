SUBDIRS = @BUILD_SUBDIRS@ themes

EXTRA_DIST = autogen.sh gtk2-smooth-engine.spec gtk2-smooth-engine.spec.in

distclean-local:
	rm -rf *.cache *~

rpm : dist
	rpmbuild --nodeps -ta $(PACKAGE)-$(VERSION).tar.gz
	@rm -f $(PACKAGE)-$(VERSION).tar.gz
