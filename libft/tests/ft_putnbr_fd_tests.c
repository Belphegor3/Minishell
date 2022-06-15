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

static void cr_assert_ft_putnbr_fd(int n, int fd)
{
	char *out, *err;

	watch_start();
	ft_putnbr_fd(n, fd);
	watch_stop(&out, &err);

	char *s;
	s = calloc(12, sizeof(char));
	assert(s != NULL);
	sprintf(s, "%d", n);

	if (fd == 1)
	{
		cr_assert_str_eq(out, s);
		cr_assert_str_eq(err, "");
	}
	else if (fd == 2)
	{
		cr_assert_str_eq(out, "");
		cr_assert_str_eq(err, s);
	}
	free(out);
	free(err);
	free(s);

}

Test(ft_putnbr_fd, one_digit)
{
	cr_assert_ft_putnbr_fd(0, 1);
	cr_assert_ft_putnbr_fd(5, 1);
}

Test(ft_putnbr_fd, two_digits)
{
	cr_assert_ft_putnbr_fd(70, 1);
	cr_assert_ft_putnbr_fd(84, 2);
}

Test(ft_putnbr_fd, multiple_digits)
{
	cr_assert_ft_putnbr_fd(834, 1);
	cr_assert_ft_putnbr_fd(284, 2);
	cr_assert_ft_putnbr_fd(8431765, 2);
}

Test(ft_putnbr_fd, int_max)
{
	cr_assert_ft_putnbr_fd(2147483647, 1);
}

Test(ft_putnbr_fd, negative)
{
	cr_assert_ft_putnbr_fd(-7, 1);
	cr_assert_ft_putnbr_fd(-758324, 2);
	cr_assert_ft_putnbr_fd(-1865, 1);
}

Test(ft_putnbr_fd, int_min)
{
	cr_assert_ft_putnbr_fd(-2147483648, 1);
}
