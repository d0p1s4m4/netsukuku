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
#include <time.h>
#include <json-c/json.h>
#include <json-c/json_object.h>

#include "ntkconsole.h"

static void
cmd_placeholder(ConsoleContext *ctx)
{
	(void)ctx;

	puts("TODO");
}

static void
cmd_help(ConsoleContext *ctx)
{
	int index;

	(void)ctx;
	puts("Usage:");
	for (index = 0; COMMANDS[index].cmd != NULL; index++)
	{
		printf("%16s - %s\n", COMMANDS[index].cmd, COMMANDS[index].help);
	}
}

static void
cmd_quit(ConsoleContext *ctx)
{
	char emoji[] = {0xF0, 0x9F, 0x98, 0x98, 0x0}; /* don't ask why */

	console_context_destroy(ctx);
	printf("bye bye %s\n", emoji);

	exit(EXIT_SUCCESS);
}

static void
cmd_shutdown(ConsoleContext *ctx)
{
	json_object *obj;
	(void)ctx;

	obj = request_send(ctx, "shutdown");
	if (obj)
	{
		if (json_object_get_boolean(obj) == 1)
		{
			puts("Shutting down ntkd");
		}
		json_object_put(obj);
	}
}

static void
cmd_uptime(ConsoleContext *ctx)
{
	json_object *obj;
	int seconds;
	int years;
	int months;
	int days;
	int hours;
	int minutes;

	(void)ctx;
	obj = request_send(ctx, "uptime");
	if (obj)
	{
		/* XXX: find a more elegant way to do this */
		seconds = json_object_get_int(obj);
		years = seconds / (60 * 60 * 24 * 30 * 12);
		seconds -= years * (60 * 60 * 24 * 30 * 12);
		months = seconds / (60 * 60 * 24 * 30);
		seconds -= months * (60 * 60 * 24 * 30);
		days = seconds / (60 * 60 * 24);
		seconds -= days * (60 * 60 * 24);
		hours = seconds / (60 * 60);
		seconds -= hours * (60 * 60);
		minutes = seconds / 60;
		seconds -= minutes * 60;
		printf("Total Uptime is: %i Year(s), %i Month(s), %i Day(s), "
				"%i Hour(s), %i Minute(s), %i Second(s)\n", years, months,
				days, hours, minutes, seconds);
		json_object_put(obj);
	}
}

static void
cmd_version(ConsoleContext *ctx)
{
	json_object *obj;

	(void)ctx;
	printf("ntk-console version: %d.%d\n",
		CONSOLE_VERSION_MAJOR, CONSOLE_VERSION_MINOR);
	
	obj = request_send(ctx, "version");
	if (obj != NULL)
	{
		printf("ntkd version: %s\n", json_object_get_string(obj));
		json_object_put(obj);
	}
}

const Command COMMANDS[] = {
	{"cur_ifs", "Lists all of the interfaces in cur_ifs", cmd_placeholder},
	{"cur_ifs_n", "Lists the number of interfaces present in `cur_ifs`", cmd_placeholder},
	{"cur_ip", "Current IP address", cmd_placeholder},
	{"cur_node", "Current node", cmd_placeholder},
	{"cur_qspn_id", "The current qspn_id we are processing. It is cur_qspn_id[levels] big", cmd_placeholder},
	{"help", "Shows console help", cmd_help},
	{"inet_connected", "Query if Ntkd is connected to the internet", cmd_placeholder},
	{"ifs", "List all the interfaces in server_opt.ifs", cmd_placeholder},
	{"ifs_n", "List the number of interfaces present in server_opt.ifs", cmd_placeholder},
	{"quit", "Exit the console", cmd_quit},
	{"shutdown", "shutdown ntkd instance", cmd_shutdown},
	{"uptime", "Returns the time when ntkd finished the hooking", cmd_uptime},
	{"version", "Shows the running version of the ntkconsole, and ntkd.", cmd_version},
	{NULL, NULL, NULL}
};
