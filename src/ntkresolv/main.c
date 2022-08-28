#include "opt.h"
#include <stdlib.h>

int
main(int argc, char *const *argv)
{
	Opt opt;

	opt_fill_default(&opt);
	opt_parse(&opt, argc, argv);
	return (EXIT_SUCCESS);
}
