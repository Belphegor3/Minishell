#include <criterion/criterion.h>
#include <string.h>
#include "../libft.h"

Test(ft_memset, no_changes)
{
	char	s[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	char	s2[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	char	result[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

	cr_assert_arr_eq(memset(s, 0, 0), result, 20);
	cr_assert_arr_eq(ft_memset(s2, 0, 0), result, 20);
}

Test(ft_memset, test_1_byte)
{
	char	s[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	char	s2[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	char	result[20] = {0,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

	cr_assert_arr_eq(memset(s, 0, 1), result, 20);
	cr_assert_arr_eq(ft_memset(s2, 0, 1), result, 20);
}

Test(ft_memset, test_2_bytes)
{
	char	s[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	char	s2[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	char	result[20] = {0,0,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

	cr_assert_arr_eq(memset(s, 0, 2), result, 20);
	cr_assert_arr_eq(ft_memset(s2, 0, 2), result, 20);
}

Test(ft_memset, test_3_bytes)
{
	char	s[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	char	s2[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	char	result[20] = {0,0,0,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

	cr_assert_arr_eq(memset(s, 0, 3), result, 20);
	cr_assert_arr_eq(ft_memset(s2, 0, 3), result, 20);
}

Test(ft_memset, test_15_bytes)
{
	char	s[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	char	s2[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	char	result[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,17,18,19,20};

	cr_assert_arr_eq(memset(s, 0, 15), result, 20);
	cr_assert_arr_eq(ft_memset(s2, 0, 15), result, 20);
}

Test(ft_memset, test_15_bytes_with_different_values)
{
	char	s[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	char	s2[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	char	result[20] = {50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,16,17,18,19,20};

	cr_assert_arr_eq(memset(s, 50, 15), result, 20);
	cr_assert_arr_eq(ft_memset(s2, 50, 15), result, 20);
}
