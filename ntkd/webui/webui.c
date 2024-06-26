#include <stddef.h>
#include <microhttpd.h>
#include <stdint.h>
#include "config/opt.h"
#include "logger.h"

static struct MHD_Daemon *httpd = NULL;

static enum MHD_Result
webui_handler(void *cls, struct MHD_Connection *conn,
					const char *url, const char *method,
					const char *version, const char *data,
					size_t *data_size, void **con_cls)
{
	struct MHD_Response *response;
	int ret;
	const char *page = "<html><body>hello</body></html>";

	(void)cls;
	(void)method;
	(void)url;
	(void)version;
	(void)data;
	(void)data_size;
	(void)con_cls;

	LOG_DEBUG("handle request: %s", url);

	response = MHD_create_response_from_buffer(strlen(page), (void *)page, MHD_RESPMEM_PERSISTENT);
	ret = MHD_queue_response(conn, MHD_HTTP_OK, response);

	MHD_destroy_response(response);

	return (ret);
}

int
webui_start(void)
{
	LOG_INFO("Starting webui on port %d", g_opt_webui_port);
	httpd = MHD_start_daemon(MHD_USE_INTERNAL_POLLING_THREAD, g_opt_webui_port,
							NULL, NULL, webui_handler, NULL, MHD_OPTION_END);
	if (httpd == NULL)
	{
		return (-1);
	}

	return (0);
}

void
webui_stop(void)
{
	LOG_INFO("Stopping webui...");
	MHD_stop_daemon(httpd);
}