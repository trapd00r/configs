THEME = LighthouseBlue
THEME_DIR = $(datadir)/themes
THEME_SUBDIR = metacity-1

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(THEME_DIR);					     \
	echo '-- Installing theme '$(THEME);					     \
	$(mkinstalldirs) $(DESTDIR)$(THEME_DIR)/$(THEME);			     \
	$(mkinstalldirs) $(DESTDIR)$(THEME_DIR)/$(THEME)/$(THEME_SUBDIR);	     \
	(installfiles=`find $(srcdir) -name "*.png" -o -name "*.xml"`;	     \
	 for i in $$installfiles; do						     \
		echo '-- Installing '$$i ;					     \
	    	$(INSTALL_DATA) $$i $(DESTDIR)$(THEME_DIR)/$(THEME)/$(THEME_SUBDIR) ; \
  	 done)									     \
