@SET_MAKE@

SUBDIRS = Theme Theme_b5 Theme_basic Theme_funklor Theme_redmondxp Theme_light

INCLUDES = $(XFCE_CFLAGS)
CFLAGS = $(XFCE_CFLAGS) -DG_DISABLE_DEPRECATED -DGTK_DISABLE_DEPRECATED \
-DGDK_DISABLE_DEPRECATED -DGDK_PIXBUF_DISABLE_DEPRECATED

enginedir = $(libdir)/gtk-2.0/$(GTK_VERSION)/engines

engine_LTLIBRARIES = libxfce.la

libxfce_la_SOURCES = \
	xfce_theme_draw.c	\
	xfce_theme_main.c	\
	xfce_rc_style.c	\
	xfce_rc_style.h	\
	xfce_style.h

libxfce_la_LDFLAGS = -module -avoid-version

libxfce_la_LIBADD = $(XFCE_LIBS)

EXTRA_DIST = autogen.sh gtk-xfce-engine-2.spec gtk-xfce-engine-2.spec.in

rpm : dist
	rpm -ta $(PACKAGE)-$(VERSION).tar.gz
	@rm -f $(PACKAGE)-$(VERSION).tar.gz
