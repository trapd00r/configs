INCLUDES = \
	-DGTK_DISABLE_DEPRECATED \
	-DGDK_DISABLE_DEPRECATED \
	-DG_DISABLE_DEPRECATED \
	$(CLEANICE_CFLAGS)

enginedir = $(libdir)/gtk-2.0/$(GTK_VERSION)/engines
engine_LTLIBRARIES = libcleanice.la

libcleanice_la_SOURCES = \
	cleanice.c cleanice.h \
	cleanice-draw.c \
	cleanice-style.c cleanice-style.h

libcleanice_la_LDFLAGS = \
	-avoid-version -no-undefined -module	\
	$(CLEANICE_LIBS)

