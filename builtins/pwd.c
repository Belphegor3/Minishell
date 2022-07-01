#include "../builtins.h"

void	pwd_not_found(void)
{
	write(2, "pwd: error retrieving current directory: getcwd: ", 50);
	write(2, "cannot access parent directories: No such file or ", 51);
	write(2, "directory\n", 11);
}

int	execute_builtin_pwd(void)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, PATH_MAX))
		return (ft_putendl_fd(buf, 1), EXIT_SUCCESS);
	// pwd_not_found();
	perror("pwd: error retrieving current directory");
	return (EXIT_FAILURE);
}
