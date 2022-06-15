#include <criterion/criterion.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <stdarg.h>
#include <uuid/uuid.h>
#include <fcntl.h>
#include "../minishell.h"
#include "executor.h"

extern char	**environ;
char *file_out, *file_err;
int save_out, save_err;

static int	watch_start_fd(int fd, char **filepath)
{
	uuid_t bid;
	uuid_generate_random(bid);

	char uuid[37];
	uuid_unparse_lower(bid, uuid);

	char filebuf[256];
	sprintf(filebuf, "/tmp/criterion.%s.log", uuid);

	*filepath = strdup(filebuf);
	assert(*filepath != NULL);

	int new_fd = open(*filepath, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	assert(new_fd != -1);

	int save_fd = dup(fd);
	assert(save_fd != -1);

	int status = dup2(new_fd, fd);
	assert(status != -1);

	status = close(new_fd);
	assert(status != -1);

	return (save_fd);
}

static char	*watch_stop_fd(int fd, char *filepath, int save_fd)
{
	int file_fd;
	char *content;
	struct stat s;
	int status;

	status = stat(filepath, &s);
	assert(status != -1);

	content = malloc(s.st_size + 1);
	assert(content != NULL);
	content[s.st_size] = '\0';

	file_fd = open(filepath, O_RDONLY);
	assert(file_fd != -1);

	ssize_t read_size = read(file_fd, content, s.st_size);
	assert(read_size >= 0);
	assert(read_size == s.st_size);

	status = close(file_fd);
	assert(status != -1);

	status = dup2(save_fd, fd);
	assert(status != -1);

	status = close(save_fd);
	assert(status != -1);

	status = remove(filepath);
	assert(status != -1);

	free(filepath);

	return (content);
}

static void watch_start(void)
{
	save_out = watch_start_fd(STDOUT_FILENO, &file_out);
	save_err = watch_start_fd(STDERR_FILENO, &file_err);
}

static void watch_stop(char **out, char **err)
{
	*out = watch_stop_fd(STDOUT_FILENO, file_out, save_out);
	*err = watch_stop_fd(STDERR_FILENO, file_err, save_err);
}

static void	compare_files(char *pathname1, char *pathname2)
{
	FILE	*file1 = fopen(pathname1, "r");
	FILE	*file2 = fopen(pathname2, "r");
	int		size = 64;
	char	s1[64];
	char	s2[64];

	cr_assert(file1);
	cr_assert(file2);
	while (fgets(s1, size, file1) && fgets(s2, size, file2))
	{
		cr_assert_str_eq(s1, s2);
	}
	cr_assert_str_eq(s1, s2);
	fclose(file1);
	fclose(file2);
}

static void	cr_assert_executor(char *line, char *bashline)
{
	char *out, *err;
	char *out2, *err2;
	char	*argv[4];
	int		pid;
	int		status;

	watch_start();
	pid = fork();
	if (pid == 0)
	{
		if (!bashline)
			bashline = line;
		argv[0] = "bash";
		argv[1] = "-c";
		argv[2] = bashline;
		argv[3] = NULL;
		execve("/bin/bash", argv, environ);
	}
	else
	{
		wait(&status);
		watch_stop(&out, &err);

		watch_start();
		t_syntax_node	*node;
		t_tok_list		*tok_list;
		tok_list = lexer(line);
		node = parser(tok_list);
		executor(node, environ);
		watch_stop(&out2, &err2);
		cr_assert_str_eq(out2, out);
		cr_assert_str_eq(err2, err);
		delete_syntax_tree(node);
		ft_toklst_clear(&tok_list, free);
		free(out);
		free(err);
		free(out2);
		free(err2);
	}
}

Test(executor, simple_command_ls_noargument)
{
	cr_assert_executor("/bin/ls", NULL);
}

Test(executor, simple_command_ls_with_arguments)
{
	cr_assert_executor("/bin/ls -la", NULL);
}

Test(executor, simple_command_ls_with_arguments2)
{
	cr_assert_executor("/bin/ls -la .", NULL);
}

Test(executor, one_pipe)
{
	cr_assert_executor("ls -l | grep c", NULL);
}

Test(executor, one_pipe2)
{
	cr_assert_executor("ls | grep c", NULL);
}

Test(executor, multiple_pipes)
{
	cr_assert_executor("ls -l | grep c | cat -e", NULL);
}

Test(executor, redirection_great)
{
	cr_assert_executor("cat Makefile > tests/out.txt", "cat Makefile > tests/bash_out.txt");
	compare_files("tests/out.txt", "tests/bash_out.txt");
	cr_assert(remove("tests/out.txt") != -1);
	cr_assert(remove("tests/bash_out.txt") != -1);
}

Test(executor, redirection_less)
{
	cr_assert_executor("grep a < Makefile", NULL);
}

Test(executor, redirection_greatgreat)
{
	cr_assert_executor("cat Makefile >> tests/out2.txt", "cat Makefile >> tests/bash_out2.txt");
	compare_files("tests/out2.txt", "tests/bash_out2.txt");
	cr_assert_executor("cat Makefile >> tests/out2.txt", "cat Makefile >> tests/bash_out2.txt");
	compare_files("tests/out2.txt", "tests/bash_out2.txt");
	cr_assert(remove("tests/out2.txt") != -1);
	cr_assert(remove("tests/bash_out2.txt") != -1);
}

Test(executor_builtins, echo)
{
	cr_assert_executor("echo Hello", NULL);
	cr_assert_executor("echo Hello World !", NULL);
	cr_assert_executor("echo -n Hello World !", NULL);
}
