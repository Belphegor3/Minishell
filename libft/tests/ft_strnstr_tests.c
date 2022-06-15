#include <criterion/criterion.h>
#include <bsd/string.h>
#include "../libft.h"

Test(ft_strnstr, little_not_in_big)
{
	char	*big = "abcabcdabc";
	char	*little = "m";
	size_t	len	= 3;

	cr_assert(strnstr(big, little, len) == 0);
	cr_assert(ft_strnstr(big, little, len) == 0);
}
	
Test(ft_strnstr, little_is_one_character_long)
{
	char	*big = "abcabcdabc";
	char	*little = "c";
	size_t	len	= 3;

	cr_assert(strnstr(big, little, len) == big + 2);
	cr_assert(ft_strnstr(big, little, len) == big + 2);
}

Test(ft_strnstr, little_is_two_characters_long)
{
	char	*big = "abcabcdabc";
	char	*little = "cd";
	size_t	len	= 8;

	cr_assert(strnstr(big, little, len) == big + 5);
	cr_assert(ft_strnstr(big, little, len) == big + 5);
}

Test(ft_strnstr, little_is_three_characters_long)
{
	char	*big = "abcabcdabc";
	char	*little = "bcd";
	size_t	len	= 9;

	cr_assert(strnstr(big, little, len) == big + 4);
	cr_assert(ft_strnstr(big, little, len) == big + 4);
}

Test(ft_strnstr, little_at_the_end_and_trimmed)
{
	char	*big = "abcabcdabc";
	char	*little = "bcd";
	size_t	len	= 6;

	cr_assert(strnstr(big, little, len) == 0);
	cr_assert(ft_strnstr(big, little, len) == 0);
}

Test(ft_strnstr, little_is_empty)
{
	char	*big = "abcabcdabc";
	char	*little = "";
	size_t	len	= 9;

	cr_assert(strnstr(big, little, len) == big);
	cr_assert(ft_strnstr(big, little, len) == big);
}

Test(ft_strnstr, len_equal_zero)
{
	char	*big = "abcabcdabc";
	char	*little = "bcd";
	size_t	len	= 0;

	cr_assert(strnstr(big, little, len) == 0);
	cr_assert(ft_strnstr(big, little, len) == 0);
}

Test(ft_strnstr, big_is_empty)
{
	char	*big = "";
	char	*little = "bcd";
	size_t	len	= 9;

	cr_assert(strnstr(big, little, len) == 0);
	cr_assert(ft_strnstr(big, little, len) == 0);
}
