#include "tmp.h"



int	builtin_cd(const char *path)
{
	// ザツな実装
	int		errno;

	errno = 0;
	chdir(path);
	return (0);
}

int builtin_pwd()
{
   	char	cwd_name[MAX_PATHSIZE];
	int		errno;

	errno = 0;
	getcwd(cwd_name, MAX_PATHSIZE);
	printf("%s\n", cwd_name);
	return (errno == 0);
}
