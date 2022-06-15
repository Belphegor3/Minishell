#include <criterion/criterion.h>
#include "../libft.h"

Test(ft_strjoin, empty_strings)
{
	char	*s;

	s = ft_strjoin("", "");
	cr_assert_str_eq(s, "");
	free(s);
	s = ft_strjoin("abc", "");
	cr_assert_str_eq(s, "abc");
	free(s);
	s = ft_strjoin("", "def");
	cr_assert_str_eq(s, "def");
	free(s);
}

Test(ft_strjoin, regular_strings)
{
	char	*s;

	s = ft_strjoin("wiobio", "pk");
	cr_assert_str_eq(s, "wiobiopk");
	free(s);
	s = ft_strjoin("pngubv", "ttt");
	cr_assert_str_eq(s, "pngubvttt");
	free(s);
}
