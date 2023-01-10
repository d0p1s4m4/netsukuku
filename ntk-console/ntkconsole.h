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

#ifndef NTKCONSOLE_H
# define NTKCONSOLE_H

# include <json-c/json_object.h>
# include <time.h>

# define CONSOLE_VERSION_MAJOR 0
# define CONSOLE_VERSION_MINOR 3
# define CONSOLE_VERSION_PATCH 0

typedef struct {
	char *socket_path;
} ConsoleContext;

typedef void (*Callback)(ConsoleContext *);

typedef struct {
	char *cmd;
	char *help;
	Callback cb;
} Command;

json_object *request_send(ConsoleContext *, char const *);
void console_context_destroy(ConsoleContext *ctx);

extern const Command COMMANDS[];

#endif /* !NTKCONSOLE_H */
