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

#include <ctype.h>
#include <stdio.h>
#include <netsukuku/log.h>
#include <netsukuku/file/conf.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char *key;

	size_t count;
	size_t idx;
	size_t capacity;

	char **values;
} ConfigItem;

typedef struct {
	size_t count;
	size_t capacity;

	ConfigItem *items;
} Config;

static Config config = {
	0, 0, NULL
};

static ConfigItem *
config_get_or_create_item(const char *key)
{
	ConfigItem *item;
	size_t idx;

	item = NULL;
	for (idx = 0; idx < config.count; idx++)
	{
		if (strcmp(config.items[idx].key, key) == 0)
		{
			return (&config.items[idx]);
		}
	}

	if (config.count >= config.capacity)
	{
		config.capacity += 4;
		config.items = (ConfigItem *)realloc(config.items,
			config.capacity * sizeof(ConfigItem));
		if (config.items == NULL)
		{
			fatal$("Can't allocate memory");
		}
	}

	item = &config.items[config.count++];
	item->key = strdup(key);
	item->count = 0;
	item->capacity = 0;
	item->idx = 0;
	item->values = NULL;

	return (item);
}

static void
config_push(char *key, char *value)
{
	ConfigItem *item;

	item = config_get_or_create_item(key);

	if (item->count >= item->capacity)
	{
		item->capacity += 4;
		item->values = realloc(item->values, item->capacity * sizeof(char *));
		if (item->values == NULL)
		{
			fatal$("Can't allocate memory");
		}
	}

	item->values[item->count++] = strdup(value);

	debug$("key(%s): value(%s)", key, value);
}

static char *
config_eat_whitespace(char *line)
{
	while (isspace(*line))
	{
		line++;
	}
	return (line);
}

static void
config_parse_line(char *line)
{
	char *value;
	char *tmp;

	line = config_eat_whitespace(line);

	if (*line == '#' || *line == '\0') /* ignore comment */
	{
		return;
	}

	value = strchr(line, '=');
	if (value == NULL)
	{
		return;
	}
	value++; /* skip '=' */

	value = config_eat_whitespace(value);
	if (*line == '\0')
	{
		return;
	}

	tmp = line;
	while (isspace(*tmp) == 0 && *tmp != '=')
	{
		tmp++;
	}
	*tmp = '\0';

	tmp = value;
	while (isspace(*tmp) == 0)
	{
		tmp++;
	}
	*tmp = '\0';

	config_push(line, value);
}

void
config_parse_file(const char *file)
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen(file, "r");
	if (fp == NULL)
	{
		fatal$("Can't open %s", file);
	}

	while ((read = getline(&line, &len, fp)) != -1)
	{
		config_parse_line(line);
	}

	if (line)
	{
		free(line);
	}
	fclose(fp);

	debug$("Config capacity: %d, element: %d", config.capacity, config.count);
}

char *
config_get(const char *key)
{
	size_t idx;

	for (idx = 0; idx < config.count; idx++)
	{
		if (strcmp(config.items[idx].key, key) == 0)
		{
			if (config.items[idx].idx >= config.items[idx].count)
			{
				return (NULL);
			}
			return (config.items[idx].values[config.items[idx].idx++]);
		}
	}
	return (NULL);
}

static void
config_cleanup_item(ConfigItem *item)
{
	size_t idx;

	for (idx = 0; idx < item->count; idx++)
	{
		free(item->values[idx]);
	}

	free(item->values);
	free(item->key);
}

void
config_cleanup(void)
{
	size_t idx;

	for (idx = 0; idx < config.count; idx++)
	{
		config_cleanup_item(&config.items[idx]);
	}

	free(config.items);
	config.items = NULL;
	config.capacity = 0;
	config.count = 0;
}
