/* This file is part of Netsukuku
 * Copyright (c) 2022 d0p1
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

#ifndef NETSUKUKU_LOG_H
# define NETSUKUKU_LOG_H 1

# include <stdlib.h>
# include <stdio.h>
# include <syslog.h>

# define LOG_FILE (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

# define log$(level, ...) log_internal_impl(level, LOG_FILE, __func__, __LINE__, __VA_ARGS__)
# define debug$(...) log$(LOG_DEBUG,  __VA_ARGS__)
# define info$(...) log$(LOG_INFO,  __VA_ARGS__)
# define warn$(...) log$(LOG_WARNING, __VA_ARGS__)
# define error$(...) log$(LOG_ERR, __VA_ARGS__)
# define fatal$(...) do { \
							log$(LOG_EMERG, __VA_ARGS__); \
							exit(EXIT_FAILURE); \
						} while (0)

typedef struct
{
	char *name;
	int level;
	FILE *fd;
} LogConfig;

void log_initialize(char *);
void log_set_level(int);
void log_set_output_fd(FILE *);

void log_internal_impl(int, char const *, char const *, int, char const *, ...);

#endif /* !NETSUKUKU_LOG_H */
