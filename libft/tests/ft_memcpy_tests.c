#include <criterion/criterion.h>
#include <string.h>
#include "../libft.h"

Test(ft_memcpy, size_0)
{
	char	src[10] = {1,2,3,4,5,6,7,8,9,10};
	char	dest[10] = {11,12,13,14,15,16,17,18,19,20};
	char	dest2[10] = {11,12,13,14,15,16,17,18,19,20};
	char	expected_result[10] = {11,12,13,14,15,16,17,18,19,20};

	cr_assert_arr_eq(memcpy(dest, src, 0), expected_result, 10);
	cr_assert_arr_eq(ft_memcpy(dest2, src, 0), expected_result, 10);
}

Test(ft_memcpy, size_1)
{
	char	src[10] = {1,2,3,4,5,6,7,8,9,10};
	char	dest[10] = {11,12,13,14,15,16,17,18,19,20};
	char	dest2[10] = {11,12,13,14,15,16,17,18,19,20};
	char	expected_result[10] = {1,12,13,14,15,16,17,18,19,20};

	cr_assert_arr_eq(memcpy(dest, src, 1), expected_result, 10);
	cr_assert_arr_eq(ft_memcpy(dest2, src, 1), expected_result, 10);
}

Test(ft_memcpy, size_2)
{
	char	src[10] = {1,2,3,4,5,6,7,8,9,10};
	char	dest[10] = {11,12,13,14,15,16,17,18,19,20};
	char	dest2[10] = {11,12,13,14,15,16,17,18,19,20};
	char	expected_result[10] = {1,2,13,14,15,16,17,18,19,20};

	cr_assert_arr_eq(memcpy(dest, src, 2), expected_result, 10);
	cr_assert_arr_eq(ft_memcpy(dest2, src, 2), expected_result, 10);
}

Test(ft_memcpy, size_3)
{
	char	src[10] = {1,2,3,4,5,6,7,8,9,10};
	char	dest[10] = {11,12,13,14,15,16,17,18,19,20};
	char	dest2[10] = {11,12,13,14,15,16,17,18,19,20};
	char	expected_result[10] = {1,2,3,14,15,16,17,18,19,20};

	cr_assert_arr_eq(memcpy(dest, src, 3), expected_result, 10);
	cr_assert_arr_eq(ft_memcpy(dest2, src, 3), expected_result, 10);
}

Test(ft_memcpy, size_9)
{
	char	src[10] = {1,2,3,4,5,6,7,8,9,10};
	char	dest[10] = {11,12,13,14,15,16,17,18,19,20};
	char	dest2[10] = {11,12,13,14,15,16,17,18,19,20};
	char	expected_result[10] = {1,2,3,4,5,6,7,8,9,20};

	cr_assert_arr_eq(memcpy(dest, src, 9), expected_result, 10);
	cr_assert_arr_eq(ft_memcpy(dest2, src, 9), expected_result, 10);
}
