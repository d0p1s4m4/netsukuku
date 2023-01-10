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
#ifndef NETSUKUKU_OPT_H
# define NETSUKUKU_OPT_H 1

#define OPT_IS_ARG(s, l) argv[_ntk_opt_index][1] == s || \
					 strcmp(argv[_ntk_opt_index] + 1, "-" l) == 0

#define OPT_IS_LONGARG(l) strcmp(argv[_ntk_opt_index] + 1, "-" l) == 0

#define OPT_GET_VALUE() impl_opt_get_value(argc, argv, &_ntk_opt_index)

#define OPT_GET_VALUE_OR_DEFAULT(x) impl_opt_get_value_or_default(argc, argv, &_ntk_opt_index, x)

#define OPT_INIT int _ntk_opt_index

#define OPT_LOOP() for (_ntk_opt_index = 1; _ntk_opt_index < argc; _ntk_opt_index++)


#endif /* !NETSUKUKU_OPT_H */
