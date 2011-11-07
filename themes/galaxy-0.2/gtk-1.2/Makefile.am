themedir = $(datadir)/themes/Galaxy/gtk
theme_DATA = gtkrc

INCLUDES = $(GTK_CFLAGS) $(GDK_PIXBUF_CFLAGS)

enginedir = $(libdir)/gtk/themes/engines

engine_LTLIBRARIES = libgalaxy.la

libgalaxy_la_SOURCES = \
	galaxy_theme_draw.c	\
	galaxy_theme_main.c	\
	galaxy.h

libgalaxy_la_LDFLAGS = -module -avoid-version

libgalaxy_la_LIBADD = $(GTK_LIBS) $(GDK_PIXBUF_LIBS)

EXTRA_DIST = $(theme_DATA)

