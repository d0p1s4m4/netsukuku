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

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syslog.h>
#include <syslog.h>

#include "log.h"

static LogConfig log_config = {
	.name = NULL,
	.level = LOG_DEBUG,
	.fd = NULL
};

void
log_initialize(char *name)
{
	log_config.name = name;

	openlog(name, LOG_PID, LOG_DAEMON);
}

void
log_set_level(int level)
{
	log_config.level = level;
}

void
log_set_output_fd(FILE *fd)
{
	log_config.fd = fd;
}

static void
log_print_level(int level)
{
	switch (level)
	{
		case LOG_EMERG:
			fprintf(log_config.fd, "[FATAL] ");
			break;
		case LOG_ERR:
			fprintf(log_config.fd, "[ERR] ");
			break;
		case LOG_WARNING:
			fprintf(log_config.fd, "[WARN] ");
			break;
		case LOG_INFO:
			fprintf(log_config.fd, "[INFO] ");
			break;
		case LOG_DEBUG:
			fprintf(log_config.fd, "[DEBUG] ");
			break;
		default:
			/* NOTHING */
			break;
	}
}

void
log_internal_impl(int level, char const *file, char const *fnc, int line, char const *format, ...)
{
	va_list vargs;

	if (level <= log_config.level && log_config.fd != NULL)
	{
		va_start(vargs, format);
		log_print_level(level);
		fprintf(log_config.fd, "(%s:%s:%d) ", file, fnc, line);
		vfprintf(log_config.fd, format, vargs);
		putchar('\n');
		va_end(vargs);
	}
	
	va_start(vargs, format);
	vsyslog(level, format, vargs);
	va_end(vargs);
}
