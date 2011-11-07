
INCLUDES = @CRUX_CFLAGS@ -DDATADIR=\"$(datadir)/eazel-engine\"

enginedir = $(libdir)/gtk-2.0/$(GTK_BINARY_VERSION)/engines

engine_LTLIBRARIES = libcrux-engine.la

libcrux_engine_la_SOURCES = 	\
	crux-common.h		\
	crux.h 			\
	crux-draw.c		\
	crux-draw.h		\
	crux-main.c		\
	crux-pixmaps.c		\
	crux-pixmaps.h		\
	crux-rc-parser.c	\
	crux-rc-parser.h	\
	crux-rc-style.c		\
	crux-rc-style.h		\
	crux-style.c		\
	crux-style.h		\
	debug.c			\
	debug.h			\
	crux-gradient.c		\
	crux-gradient.h		\
	eazel-theme.h		\
	eazel-theme-hacks.c

libcrux_engine_la_LDFLAGS = -module -avoid-version
libcrux_engine_la_LIBADD = @CRUX_LIBS@
