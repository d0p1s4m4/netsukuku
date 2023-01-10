include $(srcdir)/../common.mk

bin_PROGRAMS = ntk-console
ntk_console_SOURCES = cmd.c main.c request.c
ntk_console_LDADD = ../lib/libntk.a $(JSON_C_LIBS) $(READLINE_LIBS)
ntk_console_CPPFLAGS = $(AM_CPPFLAGS) $(JSON_C_CFLAGS) $(READLINE_CFLAGS)
