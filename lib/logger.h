#ifndef NETSUKUKU_LOGGER_H
# define NETSUKUKU_LOGGER_H 1

# include <stdint.h>
# include <stdio.h>
# include <stdarg.h>

enum logger_level {
	LOG_ERROR,
	LOG_WARN,
	LOG_INFO,
	LOG_TRACE,
	LOG_DEBUG,
};

struct logger {
	enum logger_level level;
	FILE *out;
};

void logger_init_default(void);
void logger_log(enum logger_level level, const char *file, int line,
					const char *msg, ...);
void logger_log_hexdump(enum logger_level level, const char *file, int line,
			const uint8_t *data, size_t size);

# define LOG_ERROR(...) logger_log(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
# define LOG_WARN(...)  logger_log(LOG_WARN, __FILE__, __LINE__, __VA_ARGS__)
# define LOG_INFO(...)  logger_log(LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)
# define LOG_TRACE(...) logger_log(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
# define LOG_DEBUG(...) logger_log(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)

# define LOG_HEXDUMP(data, size) \
				logger_log_hexdump(LOG_INFO, __FILE__, __LINE__, data, size)
# define LOG_DEBUG_HEXDUMP(data, size) \
				logger_log_hexdump(LOG_DEBUG, __FILE__, __LINE__, data, size)

#endif /* !NETSUKUKU_LOGGER_H */