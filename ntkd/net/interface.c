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

#include <string.h>
#include <ifaddrs.h>

#include <stdlib.h>
#include <errno.h>

#include <netsukuku/log.h>

#include "interface.h"

Interface *interfaces = NULL;

static Interface *
interface_new(const char *name)
{
	Interface *interface;

	interface = (Interface *)malloc(sizeof(Interface));
	if (interface == NULL)
	{
		return (NULL);
	}

	interface->name = strdup(name);

	return (interface);
}

static void
interface_push(Interface *interface)
{
	if (interface)
	{
		interface->next = interfaces;
		interfaces = interface;
	}
}

int
interface_scan(void)
{
	struct ifaddrs *addrs;
	struct ifaddrs *tmp;

	if (getifaddrs(&addrs) < 0)
	{
		error$("getifaddrs() failed with code: %d", errno);
		return (-1);
	}

	tmp = addrs;
	while (tmp != NULL)
	{
		debug$("Interface found: %s", tmp->ifa_name);
		interface_push(interface_new(tmp->ifa_name));
		tmp = tmp->ifa_next;
	}
	freeifaddrs(addrs);

	return (0);
}

int
interface_exist(const char *name)
{
	Interface *tmp;


	tmp = interfaces;
	while (tmp != NULL)
	{
		if (strcmp(name, tmp->name) == 0)
		{
			return (1);
		}
		tmp = tmp->next;
	}

	return (0);
}
