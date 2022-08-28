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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <netsukuku/console.h>
#include <time.h>

#include "ntkconsole.h"

static int
parse_and_execute_commands(ConsoleContext *ctx, char const *buffer)
{
	int index;

	for (index = 0; COMMANDS[index].cmd != 0; index++)
	{
		if (strcmp(COMMANDS[index].cmd, buffer) == 0)
		{
			COMMANDS[index].cb(ctx);
			return (0);
		}
	}

	return (-1);
}

static int
console_context_initialize(ConsoleContext *ctx, int argc, char *const argv[])
{
	if (argc > 1)
	{
		ctx->socket_path = strdup(argv[1]);
	}
	else
	{
		ctx->socket_path = strdup(CONSOLE_DEFAULT_SOCKET_PATH);
	}
	return (0);
}

void
console_context_destroy(ConsoleContext *ctx)
{
	free(ctx->socket_path);
}

int
main(int argc, char *const argv[])
{
	char *buffer;
	ConsoleContext ctx;

	if (console_context_initialize(&ctx, argc, argv) != 0)
	{
		return (EXIT_FAILURE);
	}

	puts("This is the Netsukuku Console. Please type 'help' for more information.");
	while ((buffer = readline("> ")) != NULL)
	{
		if (strlen(buffer) > 0)
		{
			add_history(buffer);
			if (parse_and_execute_commands(&ctx, buffer) != 0)
			{
				printf("Error: Unknown command: '%s'\n", buffer);
			}
		}
		free(buffer);
	}
	console_context_destroy(&ctx);
	return (EXIT_SUCCESS);
}
