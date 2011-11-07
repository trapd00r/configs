@SET_MAKE@

INCLUDES = $(XFCE_CFLAGS)
libxfce_la_CFLAGS = $(XFCE_CFLAGS) $(CFLAGS)

enginedir = $(libdir)/gtk-2.0/$(GTK_VERSION)/engines

engine_LTLIBRARIES = libxfce.la

libxfce_la_SOURCES = \
	gradient_draw.c		\
	gradient_draw.h 	\
	xfce_theme_draw.c	\
	xfce_theme_main.c	\
	xfce_rc_style.c 	\
	xfce_rc_style.h 	\
	xfce_style.h

libxfce_la_LDFLAGS = -module -avoid-version

libxfce_la_LIBADD = $(XFCE_LIBS)
