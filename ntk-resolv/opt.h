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
 */

#ifndef NTKRESOLV_OPT_H
# define NTKRESOLV_OPT_H 1

# include <stdint.h>

typedef struct
{
	uint16_t port;
} Opt;

void opt_fill_default(Opt *opt);
void opt_parse(Opt *opt, int argc, char *const *argv);

#endif /* !NTKRESOLV_OPT_H */
