#include <criterion/criterion.h>
#include "../libft.h"

void	free_splitted(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
}

Test(ft_split, empty_string)
{
	char	**splitted;

	splitted = ft_split("", 'a');
	cr_assert_eq(splitted[0], 0);
	free_splitted(splitted);
	free(splitted);
}

Test(ft_split, no_split_needed)
{
	char	**splitted;

	splitted = ft_split("Lorem", 'a');
	cr_assert_str_eq(splitted[0], "Lorem");
	cr_assert_eq(splitted[1], 0);
	free_splitted(splitted);
	free(splitted);
}

Test(ft_split, sep_is_null)
{
	char	**splitted;

	splitted = ft_split("Lorem", '\0');
	cr_assert_str_eq(splitted[0], "Lorem");
	cr_assert_eq(splitted[1], 0);
	free_splitted(splitted);
	free(splitted);
}

Test(ft_split, string_is_filled_with_sep)
{
	char	**splitted;

	splitted = ft_split(",,,,,", ',');
	cr_assert_eq(splitted[0], 0);
	free_splitted(splitted);
	free(splitted);
}

Test(ft_split, one_split)
{
	char	**splitted;

	splitted = ft_split("Lorem Ipsum Dolor", 'e');
	cr_assert_str_eq(splitted[0], "Lor");
	cr_assert_str_eq(splitted[1], "m Ipsum Dolor");
	cr_assert_eq(splitted[2], 0);
	free_splitted(splitted);
	free(splitted);

	splitted = ft_split("Lorem Ipsuuuum Dolor", 'u');
	cr_assert_str_eq(splitted[0], "Lorem Ips");
	cr_assert_str_eq(splitted[1], "m Dolor");
	cr_assert_eq(splitted[2], 0);
	free_splitted(splitted);
	free(splitted);
}

Test(ft_split, multiple_splits)
{
	char	**splitted;

	splitted = ft_split("Lorem Ipsum Dolor Sit Amet", ' ');
	cr_assert_str_eq(splitted[0], "Lorem");
	cr_assert_str_eq(splitted[1], "Ipsum");
	cr_assert_str_eq(splitted[2], "Dolor");
	cr_assert_str_eq(splitted[3], "Sit");
	cr_assert_str_eq(splitted[4], "Amet");
	cr_assert_eq(splitted[5], 0);
	free_splitted(splitted);
	free(splitted);
}

Test(ft_split, multiple_splits_before_and_after)
{
	char	**splitted;

	splitted = ft_split("  Lorem    Ipsum Dolor Sit Amet   ", ' ');
	cr_assert_str_eq(splitted[0], "Lorem");
	cr_assert_str_eq(splitted[1], "Ipsum");
	cr_assert_str_eq(splitted[2], "Dolor");
	cr_assert_str_eq(splitted[3], "Sit");
	cr_assert_str_eq(splitted[4], "Amet");
	cr_assert_eq(splitted[5], 0);
	free_splitted(splitted);
	free(splitted);
}

Test(ft_split, very_long_string)
{
	char	**splitted;

	splitted = ft_split("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.,", ',');
	cr_assert_str_eq(splitted[0], "Lorem ipsum dolor sit amet");
	cr_assert_str_eq(splitted[1], " consectetur adipiscing elit");
	cr_assert_str_eq(splitted[2], " sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam");
	cr_assert_str_eq(splitted[3], " quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident");
	cr_assert_str_eq(splitted[4], " sunt in culpa qui officia deserunt mollit anim id est laborum.");
	cr_assert_eq(splitted[5], 0);
	free_splitted(splitted);
	free(splitted);
}
