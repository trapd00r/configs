SUBDIRS=gtk-2.0

INCLUDES = $(GTK2_CFLAGS) -DG_LOG_DOMAIN=\"LighthouseBlueEngine\"

enginedir = $(libdir)/gtk-2.0/$(GTK2_VERSION)/engines
engine_LTLIBRARIES = liblighthouseblue.la

liblighthouseblue_la_SOURCES = 	\
	lighthouseblue_theme_main.c	\
	lighthouseblue_rc_style.c	\
	lighthouseblue_rc_style.h	\
	lighthouseblue_style.h	        \
	lighthouseblue_style.c

liblighthouseblue_la_LDFLAGS = -module -avoid-version
liblighthouseblue_la_LIBADD =  $(GTK2_LIBS)

