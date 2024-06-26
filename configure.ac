AC_PREREQ([2.71])
AC_INIT([Netsukuku], [0.1.0],
	[https://github.com/d0p1s4m4/netsukuku/issues],
	[netsukuku],
	[http://netsukuku.net/])
AC_COPYRIGHT([Copyright (C) 2024 d0p1])
AC_CONFIG_AUX_DIR([build-aux])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

AM_INIT_AUTOMAKE([foreign subdir-objects -Werror -Wall])

AM_SILENT_RULES([yes])

AC_LANG([C])
AC_PROG_CC
AC_PROG_CPP
AM_PROG_AR
AC_PROG_SED
AC_PROG_RANLIB
AC_PROG_INSTALL
AM_PROG_CC_C_O

AC_CONFIG_HEADERS([config.h])

dnl AM_GNU_GETTEXT([external])
dnl AM_GNU_GETTEXT_VERSION([0.21])

AC_HEADER_ASSERT
AC_C_CONST
AC_C_INLINE

PKG_CHECK_MODULES([MICROHTTPD], [libmicrohttpd])
PKG_CHECK_MODULES([SODIUM], [libsodium])
PKG_CHECK_MODULES([CONFIG], [libconfig])

AC_CHECK_HEADERS([libgen.h getopt.h])

AC_CHECK_TYPES([struct option], [], [],
[#ifdef HAVE_GETOPT_H
#include <getopt.h>
#endif])

AC_CHECK_FUNCS([getopt_long])

AX_PTHREAD()

AC_CONFIG_FILES([
	Makefile
	lib/Makefile
	libQSPN/Makefile
	libQSPN/tests/Makefile
	ntkd/Makefile
	doc/Doxyfile
])

LOCALSTATEDIR=`eval echo $localstatedir/netsukuku`
AC_SUBST(LOCALSTATEDIR)
CONFDIR=`eval echo $sysconfdir/netsukuku`
AC_SUBST(CONFDIR)

AC_OUTPUT

AC_MSG_RESULT([
	Netsukuku version:   $PACKAGE_NAME $VERSION
	Host OS:             ${host_os}

	C Compiler:          $CC

	State Directory:     
	Config Directory:    ${CONFDIR}

	Compiler Flags:      ${CFLAGS}
	Linker Flags:        ${LDFLAGS} ${LIBS}
])
