SUBDIRS = Theme
INCLUDES = $(GTK_CFLAGS)

enginedir = $(libdir)/gtk-2.0/$(GTK_VERSION)/engines

engine_LTLIBRARIES = libflat.la

libflat_la_SOURCES = \
	flat_rc_style.h    	\
	flat_style.h    	\
	flat_rc_style.c    	\
	flat_theme_draw.c	\
	flat_theme_main.c

libflat_la_LDFLAGS = -module -avoid-version
libflat_la_LIBADD = 
