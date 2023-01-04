AC_PREREQ([2.71])
AC_INIT([Netsukuku], m4_esyscmd([build-aux/git-version-gen .tarball-version]),
	[https://github.com/d0p1s4m4/netsukuku], [netsukuku])

AC_CONFIG_AUX_DIR([build-aux])

AC_CONFIG_HEADERS([include/netsukuku/config.h])
AC_CONFIG_FILES([
	Makefile
	src/Makefile
	src/libntk/Makefile
	src/ntkconsole/Makefile
	src/ntkd/Makefile
	src/ntkresolv/Makefile
	man/Makefile
	conf/Makefile
	test/Makefile
])
AC_CONFIG_FILES([
	conf/netsukuku.conf
])

AM_INIT_AUTOMAKE([foreign subdir-objects -Werror -Wall])

AC_PROG_CC
AC_PROG_CPP
AM_PROG_AR
AC_PROG_SED
AC_PROG_RANLIB
AC_PROG_INSTALL

AC_ARG_ENABLE([debug],
	[AS_HELP_STRING([--enable-debug],
					[whether to include debug symbols (default is no)])],
	[enable_debug=$enableval],
	[enable_debug=no]
)

if test "x$enable_debug" = xno; then
	CFLAGS="$CFLAGS -DNDEBUG"
else
	changequote({,})
	CFLAGS=`echo "$CFLAGS" | $SED -e 's/-O[0-9s]*//g'`
	CFLAGS=`echo "$CFLAGS" | $SED -e 's/-g[0-9]*//g'`
	changequote([,])

	CFLAGS="$CFLAGS -g -ggdb -O0"
fi

AC_ARG_ENABLE([ubsan],
	[AS_HELP_STRING([--enable-ubsan],
					[])],
	[enable_ubsan=$enableval],
	[enable_ubsan=no]
)

if test "x$enable_ubsan" = xyes; then
	CFLAGS="$CFLAGS -fsanitize=undefined"
fi

AC_ARG_ENABLE([asan],
	[AS_HELP_STRING([--enable-asan],
					[])],
	[enable_asan=$enableval],
	[enable_asan=no]
)

if test "x$enable_asan" = xyes; then
	CFLAGS="$CFLAGS -fsanitize=address"
fi


PKG_CHECK_MODULES([JSON_C], [json-c])
PKG_CHECK_MODULES([READLINE], [readline])

LOCALSTATEDIR=`eval echo $localstatedir`
AC_SUBST(LOCALSTATEDIR)
CONFDIR=`eval echo $sysconfdir/netsukuku`
AC_SUBST(CONFDIR)

AC_OUTPUT
