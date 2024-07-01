#include <stdlib.h>
#include <stdio.h>
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif /* HAVE_CONFIG_H */
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
#ifdef HAVE_GETOPT_H
# include <getopt.h>
#endif /* HAVE_GETOPT_H */
#ifdef HAVE_LIBGEN_H
# include <libgen.h>
#else
# include "utils.h"
#endif /* HAVE_LIBGEN_H */

static const char *prg_name;

#ifdef HAVE_STRUCT_OPTION
static struct option long_options[] = {
	{"help", no_argument, 0, 'h'},
	{"version", no_argument, 0, 'V'},
	{"socket", required_argument, 0, 's'},
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
		printf("Usage: %s [-hV] [-s <socket>]\n", prg_name);
	}
	exit(retval);
}

int
main(int argc, char **argv)
{
#if defined(HAVE_GETOPT_LONG) && defined(HAVE_STRUCT_OPTION) 
	int idx;
#endif
	int c;

	prg_name = basename(argv[0]);

	/* parse args */
#if defined(HAVE_GETOPT_LONG) && defined(HAVE_STRUCT_OPTION) 
	while ((c = getopt_long(argc, argv, "hVs:", long_options, &idx)) != EOF)
#else
	while ((c = getopt(argc, argv, "hVs:")) != EOF)
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
			case 's':
				/* increase log level */
				break;
			default:
				usage(EXIT_FAILURE);
				break;
		}
	}



	return (EXIT_SUCCESS);
}