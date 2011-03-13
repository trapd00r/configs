#!/bin/sh
# vim

sh configure --with-features=big --disable-gui --with-x=auto --disable-gpm \
             --with-global-runtime=/usr/share/vim --enable-multibyte       \
             --enable-perlinterp --disable-selinux --disable-darwin        \
             --disable-gtktest --disable-largefile --disable-acl           \
             --disable-sysmouse --with-compiledby="Magnus Woldrich"


# vim: set ts=2 expandtab sw=2:
