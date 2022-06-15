#include <criterion/criterion.h>
#include <bsd/string.h>
#include "../libft.h"
#include <stdio.h>

Test(ft_strlcpy, size_0)
{
	char	dest1[6] = "abc";
	char	dest2[6] = "abc";
	char	src[6] = "defg";

	cr_assert(strlcpy(dest1, src, 0) == 4);
	cr_assert_str_eq(dest1, "abc");
	cr_assert(ft_strlcpy(dest2, src, 0) == 4);
	cr_assert_str_eq(dest2, "abc");
}

Test(ft_strlcpy, size_1)
{
	char	dest1[6] = "abc";
	char	dest2[6] = "abc";
	char	src[6] = "defg";

	cr_assert(strlcpy(dest1, src, 1) == 4);
	cr_assert_str_eq(dest1, "");
	cr_assert(ft_strlcpy(dest2, src, 1) == 4);
	cr_assert_str_eq(dest2, "");
}

Test(ft_strlcpy, size_2)
{
	char	dest1[6] = "abc";
	char	dest2[6] = "abc";
	char	src[6] = "defg";

	cr_assert(strlcpy(dest1, src, 2) == 4);
	cr_assert_str_eq(dest1, "d");
	cr_assert(ft_strlcpy(dest2, src, 2) == 4);
	cr_assert_str_eq(dest2, "d");
}

Test(ft_strlcpy, size_2_again)
{
	char	dest1[6] = "abc";
	char	dest2[6] = "abc";
	char	src[6] = "kou";

	cr_assert(strlcpy(dest1, src, 2) == 3);
	cr_assert_str_eq(dest1, "k");
	cr_assert(ft_strlcpy(dest2, src, 2) == 3);
	cr_assert_str_eq(dest2, "k");
}

Test(ft_strlcpy, size_3)
{
	char	dest1[6] = "abc";
	char	dest2[6] = "abc";
	char	src[6] = "defgh";

	cr_assert(strlcpy(dest1, src, 3) == 5);
	cr_assert_str_eq(dest1, "de");
	cr_assert(ft_strlcpy(dest2, src, 3) == 5);
	cr_assert_str_eq(dest2, "de");
}

Test(ft_strlcpy, size_4)
{
	char	dest1[6] = "abc";
	char	dest2[6] = "abc";
	char	src[6] = "defgh";

	cr_assert(strlcpy(dest1, src, 4) == 5);
	cr_assert_str_eq(dest1, "def");
	cr_assert(ft_strlcpy(dest2, src, 4) == 5);
	cr_assert_str_eq(dest2, "def");
}

Test(ft_strlcpy, size_bigger_than_src)
{
	char	dest1[8] = "abc";
	char	dest2[8] = "abc";
	char	src[6] = "defgh";

	cr_assert(strlcpy(dest1, src, 7) == 5);
	cr_assert_str_eq(dest1, "defgh");
	cr_assert(ft_strlcpy(dest2, src, 7) == 5);
	cr_assert_str_eq(dest2, "defgh");
}

Test(ft_strlcpy, huge_size)
{
	char	dest1[8] = "abc";
	char	dest2[8] = "abc";
	char	src[6] = "defgh";

	cr_assert(strlcpy(dest1, src, 100) == 5);
	cr_assert_str_eq(dest1, "defgh");
	cr_assert(ft_strlcpy(dest2, src, 100) == 5);
	cr_assert_str_eq(dest2, "defgh");
}
