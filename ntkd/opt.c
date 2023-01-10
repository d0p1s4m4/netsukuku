/*
 * Copyright (c) 2023 d0p1
 *
 * This file is part of Netsukuku.
 *
 * Netsukuku is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation; either version 3 of the License,
 * or (at your option) any later version.
 *
 * Netsukuku is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License 
 * along with Netsukuku. If not, see <https://www.gnu.org/licenses/>
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <netsukuku/log.h>
#include <netsukuku/opt.h>
#include <sys/syslog.h>
#include <netsukuku/file/conf.h>
#include "net/interface.h"
#include "opt.h"
#include "ntk_config.h"

#define DEFAULT_CONFIG_FILE CONFDIR "/netsukuku.conf"

void
opt_fill_from_config(Opt *opt, const char *file)
{
	char *tmp;

	tmp = config_get("pid_file");
	if (tmp)
	{
		opt->pid_file = tmp;
	}
	config_parse_file(file);
}

void
opt_fill_default(Opt *opt)
{
	memset(opt, 0, sizeof(Opt));

	opt->pid_file = OPT_DEFAULT_PID_FILE;

#ifndef NDEBUG
	opt->log_level = LOG_DEBUG;
	opt->daemonize = 0;
#else
	opt->log_level = LOG_WARNING;
	opt->daemonize = 1; /* daemonize by default */
#endif

	opt_fill_from_config(opt, DEFAULT_CONFIG_FILE);
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
	printf("\t-c,--config <file>\tSpecify a config file (default: %s)\n",
				DEFAULT_CONFIG_FILE);
	printf("\t--pid\tSpecify a pid file (default: %s)\n",
				OPT_DEFAULT_PID_FILE);
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
			printf ("%s version %s\n", basename(argv[0]), VERSION);
			exit(EXIT_SUCCESS);
		}
		else if (OPT_IS_ARG('D', "no-daemon"))
		{
			opt->daemonize = 0;
		}
		else if (OPT_IS_ARG('v', "verbose"))
		{
			opt->log_level++;
			if (opt->log_level > LOG_DEBUG)
			{
				opt->log_level = LOG_DEBUG;
			}
		}
		else if (OPT_IS_ARG('i', "interface"))
		{
			tmp = OPT_GET_VALUE();
			if (!interface_exist(tmp))
			{
				fatal$("Interface %s not found", tmp);
			}
		}
		else if (OPT_IS_ARG('c', "config"))
		{
			tmp = OPT_GET_VALUE();
			if (tmp == NULL)
			{
				opt_show_help(argv[0]);
				exit(EXIT_FAILURE);
			}

			opt_fill_from_config(opt, tmp);
		}
	}
}
