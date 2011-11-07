
INCLUDES =\
	-Wall \
	-DG_LOG_DOMAIN=\"MagicChicken\" \
	$(MGICCHIKN_CFLAGS)

enginedir = $(libdir)/gtk-2.0/$(GTK_VERSION)/engines
engine_LTLIBRARIES = libmgicchikn.la

libmgicchikn_la_SOURCES = \
	main.c\
	checkradio-images.h\
	rc-style.h\
	rc-style.c\
	style.h\
	style.c\
	draw.h\
	draw.c\
	util.h\
	util.c\
	types.h

CLEANFILES=checkradio-images.h

libmgicchikn_la_LDFLAGS = \
	-module -avoid-version

libmgicchikn_la_LIBADD = 

rc-style.c: checkradio-images.h

$(srcdir)/checkradio-images.h: check.png uncheck.png incheck.png radio.png unradio.png inradio.png Makefile.am
	cd $(srcdir) && \
	echo -e "\n#include <gdk-pixbuf/gdk-pixdata.h>\n\n" > checkradio-images.h && \
	@GDK_PIXBUF_CSOURCE@ \
		--struct \
		--static \
		--name=check_img \
		check.png >> checkradio-images.h && \
	@GDK_PIXBUF_CSOURCE@ \
		--struct \
		--static \
		--name=uncheck_img \
		uncheck.png >> checkradio-images.h && \
	@GDK_PIXBUF_CSOURCE@ \
		--struct \
		--static \
		--name=incheck_img \
		incheck.png >> checkradio-images.h && \
	@GDK_PIXBUF_CSOURCE@ \
		--struct \
		--static \
		--name=radio_img \
		radio.png >> checkradio-images.h && \
	@GDK_PIXBUF_CSOURCE@ \
		--struct \
		--static \
		--name=unradio_img \
		unradio.png >> checkradio-images.h && \
	@GDK_PIXBUF_CSOURCE@ \
		--struct \
		--static \
		--name=inradio_img \
		inradio.png >> checkradio-images.h

EXTRA_DIST = check.png uncheck.png incheck.png radio.png unradio.png inradio.png
