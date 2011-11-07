INCLUDES = $(SMOOTH_GTK2_CFLAGS) -DG_LOG_DOMAIN=\"SmoothEngine\"

CFLAGS = $(SMOOTH_GTK2_CFLAGS) -DG_DISABLE_DEPRECATED -DGTK_DISABLE_DEPRECATED \
-DGDK_DISABLE_DEPRECATED -DGDK_PIXBUF_DISABLE_DEPRECATED

enginedir = $(SMOOTH_GTK2_ENGINE_DIR)
engine_LTLIBRARIES = libsmooth.la

libsmooth_la_SOURCES = \
	../utils/draw_fill.c	\
	../utils/draw_fill.h	\
	../utils/draw_grips.c	\
	../utils/draw_grips.h	\
	../utils/draw_arrows.c	\
	../utils/draw_arrows.h	\
        ../utils/misc_functions.c	\
        ../utils/misc_functions.h	\
	smooth_gtk2_engine.c	\
	../smooth_rc_style.c	\
	../smooth_rc_style.h	\
	../smooth_style.c	\
	../smooth_style.h
	
libsmooth_la_LDFLAGS= -module -avoid-version
libsmooth_la_LIBADD = $(SMOOTH_GTK2_LIBS)
