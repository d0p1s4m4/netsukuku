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

#ifndef NTKCONSOLE_H
# define NTKCONSOLE_H

# include <json-c/json_object.h>
# include <time.h>

# define CONSOLE_VERSION_MAJOR 0
# define CONSOLE_VERSION_MINOR 3

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
