#!/bin/sh

aclocal --verbose \
  && autoheader \
  && automake --add-missing --copy --include-deps --foreign --gnu --verbose \
  && autoconf \
  && ./configure $@
