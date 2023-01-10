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

#ifndef NTKD_OPT_H
# define NTKD_OPT_H 1

# include <stdint.h>

# define OPT_DEFAULT_CONFIG_FILE "netsukuku.conf"
# define OPT_DEFAULT_PID_FILE    "ntkd.pid"

typedef struct
{
	char *config_file;
	char *pid_file;

	int log_level;

	int8_t daemonize;
} Opt;

void opt_fill_default(Opt *opt);
void opt_parse(Opt *opt, int argc, char *const *argv);

#endif /* !NTKD_OPT_H */
