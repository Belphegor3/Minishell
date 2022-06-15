#include <criterion/criterion.h>
#include <bsd/string.h>
#include "../libft.h"
#include <stdio.h>

Test(ft_strlcat, correct_size_copy_0)
{
	char	dst[20] = "abcd";
	char	dst2[20] = "abcd";
	char	*src = "klmno";

	cr_assert(strlcat(dst, src, 5) == 9);
	cr_assert_str_eq(dst, "abcd");
	cr_assert(ft_strlcat(dst2, src, 5) == 9);
	cr_assert_str_eq(dst2, "abcd");
}

Test(ft_strlcat, correct_size_copy_1)
{
	char	dst[20] = "abcd";
	char	dst2[20] = "abcd";
	char	*src = "klmno";

	cr_assert(strlcat(dst, src, 6) == 9);
	cr_assert_str_eq(dst, "abcdk");
	cr_assert(ft_strlcat(dst2, src, 6) == 9);
	cr_assert_str_eq(dst2, "abcdk");
}

Test(ft_strlcat, correct_size_copy_2)
{
	char	dst[20] = "abcd";
	char	dst2[20] = "abcd";
	char	*src = "klmno";

	cr_assert(strlcat(dst, src, 7) == 9);
	cr_assert_str_eq(dst, "abcdkl");
	cr_assert(ft_strlcat(dst2, src, 7) == 9);
	cr_assert_str_eq(dst2, "abcdkl");
}

Test(ft_strlcat, size_bigger_than_strings)
{
	char	dst[20] = "abcd";
	char	dst2[20] = "abcd";
	char	*src = "klmno";

	cr_assert(strlcat(dst, src, 30) == 9);
	cr_assert_str_eq(dst, "abcdklmno");
	cr_assert(ft_strlcat(dst2, src, 30) == 9);
	cr_assert_str_eq(dst2, "abcdklmno");
}

Test(ft_strlcat, size_too_small)
{
	char	dst[20] = "abcd";
	char	dst2[20] = "abcd";
	char	*src = "klmno";

	cr_assert(strlcat(dst, src, 2) == 7);
	cr_assert_str_eq(dst, "abcd");
	cr_assert(ft_strlcat(dst2, src, 2) == 7);
	cr_assert_str_eq(dst2, "abcd");
}

Test(ft_strlcat, size_0)
{
	char	dst[20] = "abcd";
	char	dst2[20] = "abcd";
	char	*src = "klmno";

	cr_assert(strlcat(dst, src, 0) == 5);
	cr_assert_str_eq(dst, "abcd");
	cr_assert(ft_strlcat(dst2, src, 0) == 5);
	cr_assert_str_eq(dst2, "abcd");
}
