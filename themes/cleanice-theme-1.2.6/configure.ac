dnl Process this file with autoconf to produce a configure script.
AC_PREREQ(2.52)

AC_INIT(cleanice-theme, 1.2.6)
AC_CONFIG_SRCDIR(config.h.in)
AC_COPYRIGHT([Copyright 2002/2003 Elysium GNU/Linux])

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AM_CONFIG_HEADER(config.h)

AM_MAINTAINER_MODE
AC_DISABLE_STATIC

AC_ISC_POSIX
AC_PROG_CC
AC_STDC_HEADERS
AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL
AC_PROG_INTLTOOL

GETTEXT_PACKAGE="${PACKAGE}"
dnl Add the languages which your application supports here.
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$PACKAGE",
  [translation domain of this package])
AC_SUBST(GETTEXT_PACKAGE)

ALL_LINGUAS=""
AM_GLIB_GNU_GETTEXT

# AM_GLIB_GNU_GETTEXT above subst. $DATADIRNAME
# this is the directory where the *.{mo,gmo} files are installed
localedir='${prefix}/${DATADIRNAME}/locale'
AC_SUBST(localedir)

PKG_CHECK_MODULES(CLEANICE, gtk+-2.0 >= 2.0 gobject-2.0 >= 2.0,,
	 AC_MSG_ERROR([GTK+-2.0 is required]))

GTK_VERSION=`$PKG_CONFIG --variable=gtk_binary_version gtk+-2.0`

AC_SUBST(CLEANICE_CFLAGS)
AC_SUBST(CLEANICE_LIBS)

AC_SUBST(GTK_VERSION)

AC_CONFIG_FILES([
Makefile
Theme/Makefile
Theme/cleanice/Makefile
Theme/cleanice-dark/Makefile
po/Makefile.in
src/Makefile
])

AC_OUTPUT

