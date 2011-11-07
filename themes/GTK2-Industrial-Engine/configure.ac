dnl Process this file with autoconf to produce a configure script.
AC_PREREQ(2.52)

AC_INIT(Industrial, 0.2.26)
AC_CONFIG_SRCDIR(config.h.in)
AC_COPYRIGHT([Copyright 2002 Ximian, Inc.])

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AM_CONFIG_HEADER(config.h)

AC_PROG_CC
AC_PROG_INSTALL
AM_PROG_LIBTOOL

GETTEXT_PACKAGE=ximian-artwork
AC_SUBST(GETTEXT_PACKAGE)

AM_PATH_GTK(1.2.9, , 
        AC_MSG_ERROR([*** GTK+-1.2.9 not installed - please install first ***]))
AC_CHECK_LIB(gtk, gtk_style_set_prop_experimental, :,
             AC_MSG_ERROR([*** gtk_style_set_prop_experimental() not found; perhaps you have an old CVS version of GTK+ ***]),
             $GTK_LIBS)

PKG_CHECK_MODULES(XIMART, gtk+-2.0)
AC_SUBST(XIMART_CFLAGS)
AC_SUBST(XIMART_LIBS)

GTK2_VERSION=`$PKG_CONFIG --variable=gtk_binary_version gtk+-2.0`
AC_SUBST(GTK2_VERSION)

AC_CONFIG_FILES([
Makefile
gtk1-engine/Makefile
gtk1-engine/gtk/Makefile
gtk2-engine/Makefile
gtk2-engine/gtk-2.0/Makefile
gtk2-engine/gtk-2.0/gtkrc
])

AC_OUTPUT

