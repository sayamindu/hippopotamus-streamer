#!/bin/sh
# Run this to generate all the initial makefiles, etc.

srcdir=`dirname $0`
test -z "$srcdir" && srcdir=.

PKG_NAME=hippopotamus

REQUIRED_AUTOMAKE_VERSION=1.9
export REQUIRED_AUTOMAKE_VERSION

if ! test -f $srcdir/src/hippo.c; then
  echo "**Error**: Directory '$srcdir' does not look like the hippo source directory"
  exit 1
fi

which gnome-autogen.sh || {
    echo "You need to install gnome-common from Gnome CVS"
    exit 1
}

USE_GNOME2_MACROS=1 . gnome-autogen.sh
