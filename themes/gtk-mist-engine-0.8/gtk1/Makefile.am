INCLUDES=$(GTK1_CFLAGS) -Wall
enginedir=$(libdir)/gtk/themes/engines

engine_LTLIBRARIES=libmist.la
libmist_la_SOURCES = \
	mist-style.c \
	mist-rc-style.c \
	mist-theme.h

libmist_la_LDFLAGS=-export-dynamic -avoid-version
libmist_la_LIBADD=$(GTK1_LIBS)
