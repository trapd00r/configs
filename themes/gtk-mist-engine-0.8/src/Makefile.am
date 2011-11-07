INCLUDES = $(MIST_CFLAGS) -Wall

enginedir = $(libdir)/gtk-2.0/$(GTK_VERSION)/engines

engine_LTLIBRARIES = libmist.la

libmist_la_SOURCES = 	\
	mist.c	        \
	mist-rc-style.c	\
	mist-rc-style.h	\
	mist-style.c    \
	mist-style.h 

libmist_la_LDFLAGS = -module -avoid-version
libmist_la_LIBADD = $(MIST_LIBS)

