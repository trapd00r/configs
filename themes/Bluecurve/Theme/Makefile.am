SUBDIRS = gtk-2.0

INCLUDES = $(GTK2_CFLAGS)

enginedir = $(libdir)/gtk-2.0/$(GTK2_VERSION)/engines
engine_LTLIBRARIES = libbluecurve.la

libbluecurve_la_SOURCES =              \
        bluecurve_rc_style.c   \
        bluecurve_rc_style.h   \
        bluecurve_style.c              \
        bluecurve_style.h              \
        bluecurve_theme_main.c

libbluecurve_la_LDFLAGS = -module -avoid-version
libbluecurve_la_LIBADD =  $(GTK2_LIBS)

EXTRA_DIST=bits.c
