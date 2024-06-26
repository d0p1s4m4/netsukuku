#ifndef NETSUKUKU_UTILS_H
# define NETSUKUKU_UTILS_H 1

# include <string.h>

# if defined(_WIN32) && defined(_MSC_VER)
#  define PATH_SEP '\\'
# else 
#  define PATH_SEP '/' 
# endif 

# ifndef HAVE_LIBGEN_H
static inline const char *
basename(const char *file)
{
	const char *bname;

	bname = strrchr(file, PATH_SEP);
	if (!bname)
	{
		bname = file;
	}
	else
	{
		bname = bname + 1;
	}

	return (bname);
}
# endif /* !HAVE_LIBGEN_H */

#endif /* !NETSUKUKU_UTILS_H */