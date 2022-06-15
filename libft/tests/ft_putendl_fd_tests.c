#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <uuid/uuid.h>

static char *file_out, *file_err;
static int save_out, save_err;

static int watch_start_fd(int fd, char **filepath)
{
	uuid_t bid;
	uuid_generate_random(bid);

	char uuid[37];
    uuid_unparse_lower(bid, uuid);
	
	char filebuf[256];
    sprintf(filebuf, "criterion.%s.log", uuid);

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

static char *watch_stop_fd(int fd, char *filepath, int save_fd)
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

static void cr_assert_ft_putendl_fd(char *s, int fd)
{
	char *out, *err;

	watch_start();
	ft_putendl_fd(s, fd);
	watch_stop(&out, &err);
	char *s2;
	s2 = calloc(strlen(s) + 2, sizeof(char));
	assert(s2 != NULL);
	strcat(s2, s);
	strcat(s2, "\n");

	if (fd == 1)
	{
		cr_assert_str_eq(out, s2);
		cr_assert_str_eq(err, "");
	}
	else if (fd == 2)
	{
		cr_assert_str_eq(out, "");
		cr_assert_str_eq(err, s2);
	}
	free(out);
	free(err);
	free(s2);
}

Test(ft_putendl_fd, empty_string)
{
	cr_assert_ft_putendl_fd("", 1);
}

Test(ft_putendl_fd, hello)
{
	cr_assert_ft_putendl_fd("Hello World!", 1);
}

Test(ft_putendl_fd, one_character)
{
	cr_assert_ft_putendl_fd("a", 1);
}

Test(ft_putendl_fd, hello_stderr)
{
	cr_assert_ft_putendl_fd("Hello World!", 2);
}

