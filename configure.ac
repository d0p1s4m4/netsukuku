AC_PREREQ([2.71])
AC_INIT([Netsukuku], m4_esyscmd([build-aux/git-version-gen .tarball-version]),
	[https://github.com/d0p1s4m4/netsukuku], [netsukuku])

AC_CONFIG_SRCDIR(src/ntkd/main.c)
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
	doc/Doxyfile
])

AM_INIT_AUTOMAKE([foreign subdir-objects -Werror -Wall])

AC_PROG_CC
AC_PROG_CPP
AC_CHECK_PROGS([pod2man], [pod2man])
AM_PROG_AR
AC_PROG_SED
AC_PROG_RANLIB
AC_PROG_INSTALL

AM_PROG_CC_C_O

AC_CANONICAL_HOST

AC_ARG_ENABLE(debug,
	AS_HELP_STRING(--enable-debug, [whether to include debug symbols (default is no)]))
AC_ARG_ENABLE(unittests,
	AS_HELP_STRING(--disable-unittests, [don't build unit tests for Netsukuku]))
AC_ARG_ENABLE(coverage,
	AS_HELP_STRING(--enable-coverage, [enable coverage support in the unit-test build]))
AC_ARG_ENABLE(ubsan,
	AS_HELP_STRING(--enable-ubsan, [enable undefined behavior sanitizer]))
AC_ARG_ENABLE(asan, 
	AS_HELP_STRING(--enable-asan, [enable address sanitizer]))
AC_ARG_ENABLE(msan,
	AS_HELP_STRING(--enable-msan, [enable memory sanitizer]))

# -----------------------------------------------------------------------------
#  Debug build
# -----------------------------------------------------------------------------

if test "x$enable_debug" = "xyes"; then
	changequote({,})
	CFLAGS=`echo "$CFLAGS" | $SED -e 's/-O[0-9s]*//g'`
	CFLAGS=`echo "$CFLAGS" | $SED -e 's/-g[0-9]*//g'`
	changequote([,])

	CFLAGS="$CFLAGS -g -ggdb -O0"
else
	CFLAGS="$CFLAGS -DNDEBUG"
fi

# -----------------------------------------------------------------------------
#  Sanitizer
# -----------------------------------------------------------------------------
if test "x$enable_asan" = "xyes" && test "x$enable_msan" = "xyes"; then
	AC_MSG_ERROR([address sanitizer is not allowed with memory memory])
fi

if test "x$enable_ubsan" = "xyes"; then
	CFLAGS="$CFLAGS -fsanitize=undefined -fno-omit-frame-pointer"
fi

if test "x$enable_asan" = "xyes"; then
	CFLAGS="$CFLAGS -fsanitize=address -fno-omit-frame-pointer"
fi

if test "x$enable_msan" = "xyes"; then
	CFLAGS="$CFLAGS -fsanitize=memory -fPIE -pie -fno-omit-frame-pointer"
fi

# -----------------------------------------------------------------------------
#  Syscheck
# -----------------------------------------------------------------------------
AC_CHECK_SIZEOF(pid_t)

AC_CHECK_HEADERS([ifaddrs.h])

# -----------------------------------------------------------------------------
#  External libs
# -----------------------------------------------------------------------------
PKG_CHECK_MODULES([JSON_C], [json-c])
PKG_CHECK_MODULES([READLINE], [readline])

# -----------------------------------------------------------------------------
#
# -----------------------------------------------------------------------------
LOCALSTATEDIR=`eval echo $localstatedir`
AC_SUBST(LOCALSTATEDIR)
CONFDIR=`eval echo $sysconfdir/netsukuku`
AC_SUBST(CONFDIR)

AC_OUTPUT
AC_MSG_RESULT([
	$PACKAGE_NAME $VERSION

	C Compiler:          $CC
	Debug:               ${enable_debug}
	Address Sanitizer:   ${enable_asan}
	Undefined Sanitizer: ${enable_ubsan}
	Memory Sanitizer:    ${enable_msan}
])
