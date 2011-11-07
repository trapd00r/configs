SUBDIRS=gtk

INCLUDES = $(GTK_CFLAGS)

enginedir = $(libdir)/gtk/themes/engines
engine_LTLIBRARIES = libindustrial.la

libindustrial_la_SOURCES =              	\
        industrial1_theme_main.c        	\
        industrial_style.c			\
	industrial_style_versioned_include.h	\
	industrial_style_versioned_code.h	\
        industrial1.h				\
	parse_rc_style.h

libindustrial_la_LDFLAGS = -module -avoid-version
libindustrial_la_LIBADD =  $(GTK_LIBS)

EXTRA_DIST=			\
	raleigh_dot.c		\
	checkbox-on.xpm		\
	checkbox-off.xpm	\
	checkbox-mixed.xpm	\
	radio-on.xpm		\
	radio-off.xpm		\
	radio-mixed.xpm		\
	table-checkbox-on.xpm	\
	table-checkbox-off.xpm	\
	table-checkbox-mixed.xpm\
	menu-checkbox-on.xpm	\
	menu-checkbox-off.xpm	\
	menu-checkbox-mixed.xpm	\
	menu-radio-on.xpm	\
	menu-radio-off.xpm	\
	menu-radio-mixed.xpm
