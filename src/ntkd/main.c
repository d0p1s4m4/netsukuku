/* This file is part of Netsukuku
 * (c) Copyright 2022 d0p1 <contact[AT]d0p1[DOT].eu>
 *
 * This source code is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * This source code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * Please refer to the GNU Public License for more details.
 *
 * You should have received a copy of the GNU Public License along with
 * this source code; if not, write to:
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include <stdlib.h>
#include <stdio.h>

#include <netsukuku/log.h>
#include "net/interface.h"
#include "opt.h"

int
main(int argc, char *const *argv)
{
	Opt opt;

	log_initialize(argv[0]);
	log_set_output_fd(stdout);
#ifndef NDEBUG
	log_set_level(LOG_DEBUG);
#endif

	interface_scan();

	opt_fill_default(&opt);
	opt_parse(&opt, argc, argv);

	log_set_level(opt.log_level);

	return (EXIT_SUCCESS);
}
