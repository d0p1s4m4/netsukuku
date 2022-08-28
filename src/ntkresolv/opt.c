#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netsukuku/log.h>
#include <netsukuku/opt.h>
#include "opt.h"

void
opt_fill_default(Opt *opt)
{
	memset(opt, 0, sizeof(Opt));

	(void)opt;
}

static void
opt_show_help(char const *prg_name)
{
	printf("Usage: %s [option]\n", prg_name);
	printf("Flags:\n");
	printf("\t-h,--help\tDisplay this menu.\n");
	printf("\t-V,--version\tDisplay version number\n");
	printf("\t-v\tVerbose\n");
	printf("Options:\n");
}

void
opt_parse(Opt *opt, int argc, char *const *argv)
{
	OPT_INIT;

	(void)opt;
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
	}
}
