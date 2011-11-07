#!/bin/sh

# script to check that all image files are listed in the correct
# Makefile.am

images=`grep \.png gtkrc.in | sed -e 's/^.*image *= *"\(.*\)".*$/\1/'`

missing=no

for f in $images; do
  fgrep $f data/Makefile.am >/dev/null \
      || { missing=yes; echo "data/Makefile.am is missing $f"; }
done

if [ $missing != no ]; then
  exit 1
else
  exit 0
fi
