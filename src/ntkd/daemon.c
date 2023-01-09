#include "ntk_config.h"

#include <stdlib.h>

#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif /* HAVE_UNISTD_H */

#ifdef HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif /* HAVE_SYS_TYPES_H */

#include <netsukuku/log.h>

void
daemonize(void)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		error$("fork() failed...");
		exit(EXIT_FAILURE);
	}

	if (pid != 0)
	{
		/* parent */
		exit(EXIT_SUCCESS);
	}
	else
	{
		/* child */
		setsid();

		if (fork() != 0)
		{
			exit(EXIT_SUCCESS);
		}
	}
}
