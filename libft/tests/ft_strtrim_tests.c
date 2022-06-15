#include <criterion/criterion.h>
#include "../libft.h"

Test(ft_strtrim, empty_set)
{
	char	*s;

	s = ft_strtrim("abcd", "");
	cr_assert_str_eq(s, "abcd");
	free(s);
}

Test(ft_strtrim, one_character_set)
{
	char	*s;

	s = ft_strtrim("abcd", "a");
	cr_assert_str_eq(s, "bcd");
	free(s);
	s = ft_strtrim("aaaabcd", "a");
	cr_assert_str_eq(s, "bcd");
	free(s);
	s = ft_strtrim("aaaabcdaaa", "a");
	cr_assert_str_eq(s, "bcd");
	free(s);
}

Test(ft_strtrim, multiple_characters_set)
{
	char	*s;

	s = ft_strtrim("abcd", "ab");
	cr_assert_str_eq(s, "cd");
	free(s);
	s = ft_strtrim("aacabcd", "ac");
	cr_assert_str_eq(s, "bcd");
	free(s);
	s = ft_strtrim("cbcacaabcdaacbcbcab", "cb");
	cr_assert_str_eq(s, "acaabcdaacbcbca");
	free(s);
}

Test(ft_strtrim, empty_string)
{
	char	*s;

	s = ft_strtrim("", "ab");
	cr_assert_str_eq(s, "");
	free(s);
	s = ft_strtrim("", "");
	cr_assert_str_eq(s, "");
	free(s);
}
