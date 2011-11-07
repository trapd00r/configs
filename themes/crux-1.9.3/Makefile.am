SUBDIRS = src data Crux
#capplet

INCLUDES = @CRUX_CFLAGS@ -DDATADIR=\"$(datadir)\"

EXTRA_DIST =			\
	gtkrc.in		\
	make-gtkrc.pl		\
	test.glade		\
	crux.spec.in		\
	check-data.sh

dist-hook: spec-hook check-data
	
spec-hook : crux.spec
	cp $^ $(distdir)

check-data : check-data.sh
	$(SHELL) $<

noinst_PROGRAMS = test

test_LDADD = @CRUX_LIBS@
