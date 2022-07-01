#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
#include <unistd.h>
#include <string.h>
# include <assert.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <curses.h>
#include <term.h>

void	heredoc(char *stop)
{
	char	*line;
	int		fd;

	fd = open("", O_CREAT|O_WRONLY|O_TRUNC);
	while (1)
    {
		line = readline("> ");
		if (ft_strcmp(line, stop))
		{
			close(fd);
			break ;
		}
		else
		{
			write(1, line, strlen(line));
			write(1, "\n", 1);
		}
	}
}

// int main()
// {
//     heredoc("word");
// }