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

#include <stdlib.h>
#include <stdio.h>

#include "ntk_config.h"
#include <netsukuku/log.h>
#include "net/interface.h"
#include "opt.h"
#include <locale.h>
#include "gettext.h"

int
main(int argc, char *const *argv)
{
	Opt opt;

	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);

	log_initialize(argv[0]);
	log_set_output_fd(stdout);
#ifndef NDEBUG
	log_set_level(LOG_DEBUG);
#endif

	opt_fill_default(&opt);
	interface_scan();

	opt_parse(&opt, argc, argv);

	log_set_level(opt.log_level);

	return (EXIT_SUCCESS);
}
