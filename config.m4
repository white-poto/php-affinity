dnl $Id$
dnl config.m4 for extension affinity

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(affinity, for affinity support,
dnl Make sure that the comment is aligned:
dnl [  --with-affinity             Include affinity support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(affinity, whether to enable affinity support,
Make sure that the comment is aligned:
[  --enable-affinity           Enable affinity support])

if test "$PHP_AFFINITY" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-affinity -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/affinity.h"  # you most likely want to change this
  dnl if test -r $PHP_AFFINITY/$SEARCH_FOR; then # path given as parameter
  dnl   AFFINITY_DIR=$PHP_AFFINITY
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for affinity files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       AFFINITY_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$AFFINITY_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the affinity distribution])
  dnl fi

  dnl # --with-affinity -> add include path
  dnl PHP_ADD_INCLUDE($AFFINITY_DIR/include)

  dnl # --with-affinity -> check for lib and symbol presence
  dnl LIBNAME=affinity # you may want to change this
  dnl LIBSYMBOL=affinity # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $AFFINITY_DIR/$PHP_LIBDIR, AFFINITY_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_AFFINITYLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong affinity lib version or lib not found])
  dnl ],[
  dnl   -L$AFFINITY_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(AFFINITY_SHARED_LIBADD)

  PHP_NEW_EXTENSION(affinity, affinity.c, $ext_shared)
fi
