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
#include "ntk_config.h"

#include <stdlib.h>

#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif /* HAVE_UNISTD_H */

#ifdef HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif /* HAVE_SYS_TYPES_H */

#include <netsukuku/log.h>

void
daemonize(void)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		error$("fork() failed...");
		exit(EXIT_FAILURE);
	}

	if (pid != 0)
	{
		/* parent */
		exit(EXIT_SUCCESS);
	}
	else
	{
		/* child */
		setsid();

		if (fork() != 0)
		{
			exit(EXIT_SUCCESS);
		}
	}
}
