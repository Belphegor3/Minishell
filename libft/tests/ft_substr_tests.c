#include <criterion/criterion.h>
#include "../libft.h"

Test(ft_substr, regular_test)
{
	char	*s;

	s = ft_substr("abcdefg", 0, 3);
	cr_assert_str_eq(s, "abc");
	free(s);
	s = ft_substr("abcdefg", 2, 3);
	cr_assert_str_eq(s, "cde");
	free(s);
	s = ft_substr("abcdefg", 5, 4);
	cr_assert_str_eq(s, "fg");
	free(s);
	s = ft_substr("abcdefg", 5, 3);
	cr_assert_str_eq(s, "fg");
	free(s);
	s = ft_substr("abcdefg", 5, 2);
	cr_assert_str_eq(s, "fg");
	free(s);
	s = ft_substr("abcdefg", 5, 1);
	cr_assert_str_eq(s, "f");
	free(s);
	s = ft_substr("abcdefg", 5, 0);
	cr_assert_str_eq(s, "");
	free(s);
	s = ft_substr("abcdefg", 7, 3);
	cr_assert_str_eq(s, "");
	free(s);
	s = ft_substr("abcdefg", 12, 3);
	cr_assert_eq(s, 0);
	s = ft_substr("", 7, 3);
	cr_assert_eq(s, 0);
}

