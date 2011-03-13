#!/bin/sh
# vim

sh configure --disable-selinux --disable-darwin --enable-luainterp=yes   \
             --enable-erlinterp=yes --enable-multibyte --disable-gtktest \
             --disable-largefile --disable-acl --disable-gpm             \
             --disable-sysmouse --with-compiledby="Magnus Woldrich"


# vim: set ts=2 expandtab sw=2:
