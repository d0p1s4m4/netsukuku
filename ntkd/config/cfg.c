#include <libconfig.h>
#include "opt.h"
#include "logger.h"

int
cfg_load_from(const char *file)
{
	config_t cfg;

	LOG_DEBUG("load config from: %s", file);

	config_init(&cfg);

	if (config_read_file(&cfg, file) != CONFIG_TRUE)
	{
		logger_log(LOG_ERROR, config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
		config_destroy(&cfg);
		return (-1);
	}

	config_lookup_bool(&cfg, "webui.enable", &g_opt_enable_webui);
	config_lookup_int(&cfg, "webui.port", &g_opt_webui_port);

	config_destroy(&cfg);
	return (0);
}