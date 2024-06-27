#ifdef WIN32
# include <winsock2.h>
#endif
#include <pthread.h>
#include "logger.h"

#define NTKD_PORT 269

static pthread_t udp_thread;
static pthread_t tcp_thread;

static void *
server_udp(void *argv)
{
	for (;;)
	{

	}
	return (NULL);
}

static int
server_udp_start(void)
{
	LOG_INFO("Starting udp listener on port: %d", NTKD_PORT);

	pthread_create(&udp_thread, NULL, server_udp, NULL);

	return (0);
}


static int
server_udp_stop(void)
{
	LOG_INFO("Stopping udp listener...");

	/*pthread_join(udp_thread, NULL);*/

	return (0);
}

static void *
server_tcp(void *argv)
{
	return (NULL);
}

static int
server_tcp_start(void)
{
	LOG_INFO("Starting tcp listener on port: %d\n", NTKD_PORT);

	pthread_create(&tcp_thread, NULL, server_tcp, NULL);

	return (0);
}

int
server_start(void)
{
#ifdef WIN32
	WSADATA wsadata;

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		LOG_ERROR("WSAStartup failed: %d\n", GetLastError());
		return (-1);
	}
#endif /* WIN32 */

	server_udp_start();
	server_tcp_start();

	return (0);	
}

void
server_stop()
{
	LOG_INFO("Stopping servers...");
	server_udp_stop();
	server_udp_stop();
}

