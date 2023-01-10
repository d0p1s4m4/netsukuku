AC_PREREQ([2.71])
AC_INIT([Netsukuku], m4_esyscmd([build-aux/git-version-gen .tarball-version]),
	[https://github.com/d0p1s4m4/netsukuku], [netsukuku])
AC_COPYRIGHT([Copyright (C) 2023 d0p1])

AC_CONFIG_SRCDIR(ntkd/main.c)
AC_CONFIG_AUX_DIR([build-aux])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

AC_CONFIG_HEADERS([ntk_config.h])
AC_CONFIG_FILES([
	Makefile
	lib/Makefile
	ntk-console/Makefile
	ntkd/Makefile
	ntk-resolv/Makefile
	man/Makefile
	conf/Makefile
	test/Makefile
	po/Makefile.in
])
AC_CONFIG_FILES([
	conf/netsukuku.conf
	doc/Doxyfile
])

AM_INIT_AUTOMAKE([foreign subdir-objects -Werror -Wall])

AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.21])

# -----------------------------------------------------------------------------
#  Compiler and tools
# -----------------------------------------------------------------------------
AC_LANG([C])
AC_PROG_CC
AC_PROG_CPP
AC_CHECK_PROGS([pod2man], [pod2man])
AM_PROG_AR
AC_PROG_SED
AC_PROG_RANLIB
AC_PROG_INSTALL
AM_PROG_CC_C_O

# -----------------------------------------------------------------------------
# 
# -----------------------------------------------------------------------------

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
#  Check keywords and standard types
# -----------------------------------------------------------------------------
AC_C_CONST

AC_CHECK_SIZEOF(pid_t)

AC_CHECK_HEADERS([ifaddrs.h])

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
#  External libs
# -----------------------------------------------------------------------------
PKG_CHECK_MODULES([JSON_C], [json-c])
PKG_CHECK_MODULES([READLINE], [readline])
PKG_CHECK_MODULES([SODIUM], [libsodium])

# -----------------------------------------------------------------------------
#
# -----------------------------------------------------------------------------
if test "$prefix" == NONE
then
	prefix=""
fi

LOCALSTATEDIR=`eval echo $localstatedir`
AC_SUBST(LOCALSTATEDIR)
CONFDIR=`eval echo \`echo ${sysconfdir}\`/netsukuku`
AC_SUBST(CONFDIR)
AH_TEMPLATE([CONFDIR],[netskuku's configuration directory])
AC_DEFINE_UNQUOTED(CONFDIR,"$CONFDIR")

AC_OUTPUT

AC_MSG_RESULT([
	Netsukuku version:   $PACKAGE_NAME $VERSION
	Host OS:             ${host_os}

	C Compiler:          $CC
	Debug:               ${enable_debug:-no}
	Address Sanitizer:   ${enable_asan:-no}
	Undefined Sanitizer: ${enable_ubsan:-no}
	Memory Sanitizer:    ${enable_msan:-no}

	State Directory:     
	Config Directory:    ${CONFDIR}

	Compiler Flags:      ${CFLAGS}
	Linker Flags:        ${LDFLAGS} ${LIBS}
])
