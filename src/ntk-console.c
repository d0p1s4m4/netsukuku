/* This file is part of Netsukuku
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>
#include <unistd.h>

#include "console.h"
#include "ntk-console.h"

static struct supported_commands commands[] = {
	{COMMAND_HELP, "help", "Shows console help", 0},
	{COMMAND_UPTIME, "uptime",
		"Returns the time when ntkd finished the hooking", 0},
	{COMMAND_KILL, "kill",
		"Kills the running instance of netsukuku with SIGINT", 0},
	{COMMAND_VERSION, "version",
		"Shows the running version of the ntk-console, and ntkd.", 0},
	{COMMAND_INETCONN, "inet_connected",
		"Query if Ntkd is connected to the internet", 0},
	{COMMAND_CURIFS, "cur_ifs", "Lists all of the interfaces in cur_ifs", 0},
	{COMMAND_CURIFSCT, "cur_ifs_n",
		"Lists the number of interfaces present in `cur_ifs`", 0},
	{COMMAND_CURQSPNID, "cur_qspn_id",
		"The current qspn_id we are processing. It is cur_qspn_id[levels] big", 0},
	{COMMAND_CURIP, "cur_ip", "Current IP address", 0},
	{COMMAND_CURNODE, "cur_node", "Current node", 0},
	{COMMAND_IFS, "ifs", "List all the interfaces in server_opt.ifs", 0},
	{COMMAND_IFSCT, "ifs_n",
			"List the number of interfaces present in server_opt.ifs", 0},
	{COMMAND_QUIT, "quit", "Exit the console", 0},
	{COMMAND_CONSUPTIME, "console_uptime", "Get the uptime of this console", 0}
};

static struct tm start_timeinfo;

static command_t
command_parse(char *request)
{
	size_t i;

	for (i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
		if (strncmp(request, commands[i].command, strlen(request) - 1) == 0) {
			return commands[i].id;
		}
	}

	printf("Incorrect or unreadable command, Please correct it.\n");
	return -1;
}

static void
request_receive(int sockfd)
{
	char buffer[BUFFSIZE];
	int read;

	while ((read = recv(sockfd, buffer, BUFFSIZE - 1, 0)) > 0) {
		buffer[read] = 0;
		printf("%s", buffer);
	}
	putchar('\n');

	if (read < 0) {
		perror("recv() failed");
		exit(-1);
	}
}

static int
opensocket(void)
{
	int sockfd;
	struct sockaddr_un serveraddr;

	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("socket creation failed");
		return -1;
	}

	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sun_family = AF_UNIX;
	strcpy(serveraddr.sun_path, CONSOLE_SOCKET_PATH);

	if (connect(sockfd, (struct sockaddr *) &serveraddr,
				 sizeof(serveraddr)) < 0) {
		perror("connect() failed");
		return -1;
	}
	return sockfd;
}

static void
closesocket(int sockfd)
{
	const int optVal = 1;
	const socklen_t optLen = sizeof(optVal);

	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (void *) &optVal, optLen);

	if (sockfd >= 0)
		close(sockfd);
}

/* Sends and receives to ntkd */
static void
ntkd_request(command_t command)
{
	int sockfd;
	cmd_packet_t packetOut;

	if ((sockfd = opensocket()) < 0) {
		printf("Unable to connect to ntk daemon console.\n");
		return;
	}

	packetOut.command = command;

	if (send(sockfd, &packetOut, sizeof(packetOut), 0) < 0) {
		perror("send() failed");
		exit(-1);
	}

	request_receive(sockfd);

	closesocket(sockfd);
}

static void
console_uptime(void) {
	time_t rawtime;
	struct tm *current_timeinfo;

	time(&rawtime);
	current_timeinfo = localtime(&rawtime);
	current_timeinfo->tm_sec -= start_timeinfo.tm_sec;
	current_timeinfo->tm_min -= start_timeinfo.tm_min;
	current_timeinfo->tm_hour -= start_timeinfo.tm_hour;
	current_timeinfo->tm_mday -= start_timeinfo.tm_mday;
	current_timeinfo->tm_mon -= start_timeinfo.tm_mon;
	current_timeinfo->tm_year -= start_timeinfo.tm_year;
	
	/* Checks if the date/time is negative,
	 * And makes it positive.
	 * e.g -11 is 1 because this is a signed variable
	 * at a modulus of 12. Thus after 12, It is -12
	 * which is zero, Every number after this is counting up
	 * to 12 again, Which is going to be 0 in this instance.
	 * -12 to 12 is 24 actual months.
	 * So -11 + 12 is 1, As it should be, And -12 + 12 is zero
	 * as it should be. The only difference is the modulus number,
	 * i.e: 12, 24, etc. */
	if(current_timeinfo->tm_mon < 0)
		current_timeinfo->tm_mon += 12;
	if(current_timeinfo->tm_mday < 0)
		current_timeinfo->tm_mday += 365;
	if(current_timeinfo->tm_hour < 0)
		current_timeinfo->tm_hour += 24;
	if(current_timeinfo->tm_min < 0)
		current_timeinfo->tm_min += 60;
	if(current_timeinfo->tm_sec < 0)
		current_timeinfo->tm_sec += 60;

	current_timeinfo->tm_mon %= 12;
	current_timeinfo->tm_mday %= 365;
	current_timeinfo->tm_hour %= 24;
	current_timeinfo->tm_min %= 60;
	current_timeinfo->tm_sec %= 60;

	printf("Total Uptime is: %i Year(s), %i Month(s), %i Day(s), "
		"%i Hour(s), %i Minute(s), %i Second(s)\n",
		current_timeinfo->tm_year, current_timeinfo->tm_mon,
		current_timeinfo->tm_mday, current_timeinfo->tm_hour,
		current_timeinfo->tm_min, current_timeinfo->tm_sec);
}

void
usage(void)
{
	size_t i;

	printf("Usage:\n");
	for (i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
		printf("  %16s - %s\n", commands[i].command, commands[i].help);
	}
}

void
console(char *request)
{
	command_t commandID;
	
	commandID = command_parse(request);

	switch (commandID) {
	case COMMAND_QUIT:
		exit(0);
		break;
	case COMMAND_UPTIME:
	case COMMAND_INETCONN:
	case COMMAND_CURIFS:
	case COMMAND_CURIFSCT:
	case COMMAND_CURQSPNID:
	case COMMAND_CURIP:
	case COMMAND_CURNODE:
	case COMMAND_IFS:
	case COMMAND_IFSCT:
		ntkd_request(commandID);
		break;
	case COMMAND_VERSION:
		printf("ntk-console version: %d.%d\n",
			   CONSOLE_VERSION_MAJOR, CONSOLE_VERSION_MINOR);
		ntkd_request(commandID);
		break;
	case COMMAND_CONSUPTIME:
		console_uptime();
		break;
	case COMMAND_KILL:
		system("ntkd -k");
		break;
	case COMMAND_HELP:
	default:
		usage();
	}
}

int
main(void)
{
	time_t rawtime;
	struct tm *temp_timeinfo;
	char *request;

	time(&rawtime);
	temp_timeinfo = localtime(&rawtime);
	memcpy(&start_timeinfo, temp_timeinfo, sizeof(struct tm));

	printf("This is the Netsukuku Console. Please type 'help' for more information.\n");
	for (;;) {
		request = (char *) malloc(CONSOLE_BUFFER_LENGTH);
		printf("\n> ");
		if (fgets(request, 16, stdin) == NULL)
		{
			free(request);
			return 0;
		}
		fflush(stdin);
		console(request);
		free(request);
	}

	return 0;
}
