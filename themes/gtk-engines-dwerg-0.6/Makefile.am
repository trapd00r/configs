SUBDIRS = Theme

INCLUDES = -Wall $(DWERG_CFLAGS)

enginedir = $(libdir)/gtk-2.0/$(GTK_VERSION)/engines

engine_LTLIBRARIES = libdwerg.la

libdwerg_la_SOURCES =	\
	dwerg_main.c		\
	dwerg_rc_style.c	\
	dwerg_rc_style.h	\
	dwerg_style.h	\
	dwerg_theme_draw.c	\
	dwerg_theme.h

libdwerg_la_LDFLAGS = -module -avoid-version

libdwerg_la_LIBADD = $(DWERG_LIBS)

EXTRA_DIST = autogen.sh
