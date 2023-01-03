#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netsukuku/log.h>
#include <netsukuku/opt.h>
#include "net/interface.h"
#include "opt.h"

void
opt_fill_default(Opt *opt)
{
	memset(opt, 0, sizeof(Opt));

	opt->config_file = OPT_DEFAULT_CONFIG_FILE;
	opt->pid_file = OPT_DEFAULT_PID_FILE;

#ifndef NDEBUG
	opt->log_level = LOG_DEBUG;
	opt->daemonize = 0;
#else
	opt->log_level = LOG_WARNING;
	opt->daemonize = 1; /* daemonize by default */
#endif
}

static void
opt_show_help(char const *prg_name)
{
	printf("Usage: %s [option]\n", prg_name);
	printf("Flags:\n");
	printf("\t-h,--help\tDisplay this menu.\n");
	printf("\t-V,--version\tDisplay version number\n");
	printf("\t-D,--no-daemon\tRun in foreground\n");
	printf("\t-i,--interface\tNetwork card\n");
	printf("\t-v\tVerbose\n");
	printf("Options:\n");
	printf("\t-c,--config <file>\tSpecify a config file (default: %s)\n", OPT_DEFAULT_CONFIG_FILE);
	printf("\t--pid\tSpecify a pid file (default: %s)\n", OPT_DEFAULT_PID_FILE);
}

static char *
impl_opt_get_value(int argc, char * const*argv, int *_ntk_opt_index)
{
	*_ntk_opt_index = *_ntk_opt_index + 1;

    if (*_ntk_opt_index >= argc)
    {
		opt_show_help(argv[0]);
		exit(EXIT_FAILURE);
    }
	
	if (argv[*_ntk_opt_index][0] == '-')
    {
		opt_show_help(argv[0]);
		exit(EXIT_FAILURE);
	}

    return ((char *)argv[*_ntk_opt_index]);
}

void
opt_parse(Opt *opt, int argc, char *const *argv)
{
	const char *tmp;
	OPT_INIT;

	OPT_LOOP()
	{
		if (OPT_IS_ARG('h', "help"))
		{
			opt_show_help(argv[0]);
			exit(EXIT_SUCCESS);
		}
		else if (OPT_IS_ARG('V', "version"))
		{
			printf("%s %s\n", argv[0], VERSION);
			exit(EXIT_SUCCESS);
		}
		else if (OPT_IS_ARG('D', "no-daemon"))
		{
			opt->daemonize = 0;
		}
		else if (OPT_IS_ARG('i', "interface"))
		{
			tmp = OPT_GET_VALUE();
			if (!interface_exist(tmp))
			{
				error$("Interface %s not found", tmp);
			}
		}
	}
}
