
#include <stddef.h>
#ifdef WIN32
# include <shlobj.h>
# include <winerror.h>
# include <winsock.h>
# include <minwindef.h>
#endif /* WIN32 */
#include "logger.h"

const char *
fs_get_datadir(void)
{
#ifdef WIN32
	static char path[MAX_PATH];
	PWSTR appdata = NULL;

	if (SHGetKnownFolderPath(&FOLDERID_RoamingAppData, KF_FLAG_CREATE, NULL, &appdata) != S_OK)
	{
		LOG_WARN("Can't retrieve appdata: %d", WSAGetLastError());
		return (NULL);
	}

	wcstombs(path, appdata, MAX_PATH);
	LOG_TRACE("App folder: %s", path);

	return (path);
#endif /* WIN32 */
	return (NULL);
}