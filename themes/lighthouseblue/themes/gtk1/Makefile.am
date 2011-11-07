SUBDIRS = gtk

INCLUDES = $(GTK_CFLAGS) 

enginedir = $(libdir)/gtk/themes/engines
engine_LTLIBRARIES = liblighthouseblue.la

liblighthouseblue_la_SOURCES =              \
        lighthouseblue_theme_main.c 	\
        lighthouseblue_theme_draw.c 	\
        lighthouseblue.h

liblighthouseblue_la_LDFLAGS = -module -avoid-version
liblighthouseblue_la_LIBADD =  $(GTK_LIBS)
