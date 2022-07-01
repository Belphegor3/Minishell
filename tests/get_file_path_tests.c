#include <criterion/criterion.h>
#include "executor.h"

extern char	**environ;

Test(get_file_path, filepath_already_in_pathname)
{
	char	*pathname = "/usr/bin/ls";
	char	*filepath;

	filepath = get_filepath(pathname, environ);
	cr_assert_str_eq(filepath, "/usr/bin/ls");
	free(filepath);
}

Test(get_file_path, valid_pathname)
{
	char	*pathname = "ls";
	char	*filepath;

	filepath = get_filepath(pathname, environ);
	cr_assert_str_eq(filepath, "/usr/bin/ls");
	free(filepath);
}
