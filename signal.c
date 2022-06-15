#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

// void    handle_static_z(int sig_num)
// {
//     static int  count = 1;

//     printf("\n");
//     printf("[%d]+	Stopped                 %s\n", count++, "cat"/* il faut ecrire la commande donc passer par ex par le pointeur vers */);
// 	// exit(148);
// 	/* valeur de exit vaut 148 */
// 	/* faut pas exit mais revenir au prompt */
// }

void    handle_static_c(int sig_num)
{
    printf("\n");
	/* valeur de exit vaut 130 */
	/* revenir au prompt */
}

void    handle_static_backslash(int sig_num)
{
    printf("Quit (core dumped)\n");
	/* valeur de exit vaut 131 */
	/* revenir au prompt */
}

void	handle_interactive_sigint(int sig_num)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("");
	/* valeur de exit vaut 130 */
}

void	handle_interactive_sigquit(int sig_num)
{
	write(1, "\b\b  \b\b", 6);
	/* valeur de exit vaut 130 */
}

// void	handle_interactive_sigtstp(int sig_num)
// {
// 	exit(131);
// }

void    interactive_sig(int sig_num)
{
    if (sig_num == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
        signal(sig_num, SIG_IGN);
		/* valeur de exit vaut 0 */
	}
    // if (sig_num == SIGTSTP)
    //     signal(sig_num, &handle_interactive_sigtstp);
    if (sig_num == SIGINT)
        signal(sig_num, &handle_interactive_sigint);
}


int	main(int ac, char **av, char **env)
{
	int	pid;
	int	i;
	(void)av;

	i = ac - 1;
	while (i > 0)
	{
		ft_putstr_fd("minishell: export: '", 1);
		ft_putstr_fd(av[i--], 1);
		ft_putendl_fd("': not a valid identifier", 1);
		// return (0);
	}
	// if (i == 0)
	// 	exit(0);
	// return (0);
	// interactive_sig(SIGINT);
	// interactive_sig(SIGTSTP);
	// interactive_sig(SIGQUIT);
	signal(SIGQUIT, &handle_interactive_sigquit);
	signal(SIGINT, &handle_interactive_sigint);
	// pid = fork();
	// if (pid != 0)
	// {
		// execve("/bin/bash", "", env);
		// execve();

	// }
	// write(1, "\b\b\b\b\b\b      \b\b\b\b\b\b\n", 19);
	// kill(0, SIGKILL);
	// write(1, "\b\b\b\b\b\b      \b\b\b\b\b\b\n", 19);
    // signal(SIGQUIT, &handle_static_backslash);
    // signal(SIGTSTP, &handle_static_z);
    // signal(SIGINT, &handle_static_c);
	while (1)
		// waitpid(pid);
		;
	return (0);
}