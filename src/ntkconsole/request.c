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

#include <json-c/json_tokener.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <json-c/json_object.h>
#include <netsukuku/console.h>

#include "ntkconsole.h"

static json_object *
request_craft_rpc(char const *method)
{
	json_object *obj;

	obj = json_object_new_object();
	json_object_object_add(obj, "jsonrpc", json_object_new_string("1.0"));
	json_object_object_add(obj, "method", json_object_new_string(method));
	json_object_object_add(obj, "params", json_object_new_array());
	json_object_object_add(obj, "id", json_object_new_int(rand()));

	return (obj);
}

static json_object *
request_read(int sockfd)
{
	json_object *obj;
	json_object *obj_tmp;
	json_object *obj_res;
	char buffer[1024];
	ssize_t byte_read;

	if ((byte_read = recv(sockfd, buffer, 1024, 0)) < 0)
	{
		return (NULL);
	}

	buffer[byte_read] = '\0';
	obj = json_tokener_parse(buffer);

	obj_tmp = json_object_object_get(obj, "error");
	if (obj_tmp)
	{
		printf("Error: %s\n", json_object_get_string(obj_tmp));
	}

	obj_tmp = json_object_object_get(obj, "result");
	obj_res = NULL;
	json_object_deep_copy(obj_tmp, &obj_res, NULL);
	json_object_put(obj);

	return (obj_res);
}

json_object *
request_send(ConsoleContext *ctx, char const *method)
{
	int sockfd;
	json_object *obj;
	char *buff;
	struct sockaddr_un serv_addr;

	if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
	{
		perror("Socket creation failed");
		return (NULL);
	}
	memset(&serv_addr, 0, sizeof(struct sockaddr_un));
	serv_addr.sun_family = AF_UNIX;
	strcpy(serv_addr.sun_path, ctx->socket_path);

	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_un)) < 0)
	{
		perror("connect failed");
		return (NULL);
	}

	obj = request_craft_rpc(method);
	buff = (char *)json_object_to_json_string(obj);
	if (send(sockfd, buff,strlen(buff), 0) < 0)
	{
		perror("send() failed");
		return (NULL);
	}
	json_object_put(obj);
	obj = request_read(sockfd);
	close(sockfd);
	return (obj);
}
