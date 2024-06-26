/*
 * Copyright (c) 2024 d0p1
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
#include "config/opt.h"
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif /* HAVE_CONFIG_H */
#ifdef HAVE_GETOPT_H
# include <getopt.h>
#endif /* HAVE_GETOPT_H */
#ifdef HAVE_LIBGEN_H
# include <libgen.h>
#endif /* HAVE_LIBGEN_H */
#include "logger.h"
#include "utils.h"
#include "network/server.h"
#include "webui/webui.h"
#include "config/cfg.h"

static const char *prg_name;

#ifdef HAVE_STRUCT_OPTION
static struct option long_options[] = {
	{"help", no_argument, 0, 'h'},
	{"version", no_argument, 0, 'V'},
	{"config", required_argument, 0, 'c'},
	{"foreground", no_argument, 0, 'F'},
	{0, 0, 0, 0}
};
#endif /* HAVE_STRUCT_OPTION */

static void
version(void)
{
	printf("%s (%s) %s\n", prg_name, PACKAGE_NAME, PACKAGE_VERSION);
	exit(0);
}

static void
usage(int retval)
{
	if (retval == EXIT_FAILURE)
	{
		fprintf(stderr, "Try '%s -h' for more information.\n", prg_name);
	}
	else
	{
		printf("Usage: %s [-hV]\n", prg_name);
	}
	exit(retval);
}

static void
sighandler(int sig)
{
	LOG_DEBUG("signal: %d", sig);
}

int
main(int argc, char **argv)
{
#if defined(HAVE_GETOPT_LONG) && defined(HAVE_STRUCT_OPTION) 
	int idx;
#endif
	int c;

	prg_name = basename(argv[0]);

	logger_init_default();

	/* load config */


	/* parse args */
#if defined(HAVE_GETOPT_LONG) && defined(HAVE_STRUCT_OPTION) 
	while ((c = getopt_long(argc, argv, "hVc:F", long_options, &idx)) != EOF)
#else
	while ((c = getopt(argc, argv, "hVc:F")) != EOF)
#endif /* HAVE_GETOPT_LONG && HAVE_STRUCT_OPTION */
	{
		switch(c)
		{
			case 'h':
				usage(EXIT_SUCCESS);
				break;
			case 'V':
				version();
				break;
			case 'c':
				if (cfg_load_from(optarg) != 0)
				{
					return (EXIT_FAILURE);
				}
				break;
			case 'F':
				g_opt_daemonize = 0;
				break;
			default:
				usage(EXIT_FAILURE);
				break;
		}
	}

	/* */
#ifdef SIGINT
	signal(SIGINT, sighandler);
#endif
#ifdef SIGTERM
	signal(SIGTERM, sighandler);
#endif
#ifdef SIGQUIT
	signal(SIGQUIT, sighandler);
#endif

	/* run */

	server_start();
	webui_start();

	/*getchar();*/

	webui_stop();
	server_stop();
	return (EXIT_SUCCESS);
}