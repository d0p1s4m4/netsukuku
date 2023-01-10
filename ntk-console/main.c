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
#include "ntk_config.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <netsukuku/console.h>
#include <time.h>
#include <locale.h>

#include "ntkconsole.h"
#include "gettext.h"

#define _(x) gettext(x)

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

	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);

	if (console_context_initialize(&ctx, argc, argv) != 0)
	{
		return (EXIT_FAILURE);
	}

	puts(_("This is the Netsukuku Console. Please type 'help' for more information."));
	while ((buffer = readline("> ")) != NULL)
	{
		if (strlen(buffer) > 0)
		{
			add_history(buffer);
			if (parse_and_execute_commands(&ctx, buffer) != 0)
			{
				printf(_("Error: Unknown command: '%s'\n"), buffer);
			}
		}
		free(buffer);
	}
	console_context_destroy(&ctx);
	return (EXIT_SUCCESS);
}
