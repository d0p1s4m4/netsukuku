bin_PROGRAMS = ntkd

if ENABLE_WEBUI
WEBUI = webui/webui.c
endif

ntkd_SOURCES = main.c config/opt.c $(WEBUI) network/server.c config/cfg.c
ntkd_LDADD = $(PTHREAD_LIBS) ../lib/libntk.a $(MICROHTTPD_LIBS) $(CONFIG_LIBS) -lws2_32 -lmswsock
ntkd_CFLAGS = $(MICROHTTPD_CFLAGS) $(PTHREAD_CFLAGS) $(CONFIG_CFLAGS)
ntkd_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/ntkd -I$(top_srcdir)/lib