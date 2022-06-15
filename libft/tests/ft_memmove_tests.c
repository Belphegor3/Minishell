#include <criterion/criterion.h>
#include <string.h>
#include "../libft.h"

Test(ft_memmove, size_0)
{
	char	s1[10] = {1,2,3,4,5,6,7,8,9,10};
	char	s2[10] = {1,2,3,4,5,6,7,8,9,10};
	char	expected_result[10] = {1,2,3,4,5,6,7,8,9,10};

	cr_assert_arr_eq(memmove(s1, s1, 0), expected_result, 10);
	cr_assert_arr_eq(ft_memmove(s2, s2, 0), expected_result, 10);
}

Test(ft_memmove, size_1)
{
	char	s1[10] = {1,2,3,4,5,6,7,8,9,10};
	char	s2[10] = {1,2,3,4,5,6,7,8,9,10};
	char	expected_result[10] = {6,2,3,4,5,6,7,8,9,10};

	cr_assert_arr_eq(memmove(s1, &(s1[5]), 1), expected_result, 10);
	cr_assert_arr_eq(ft_memmove(s2, &(s2[5]), 1), expected_result, 10);
}

Test(ft_memmove, size_2)
{
	char	s1[10] = {1,2,3,4,5,6,7,8,9,10};
	char	s2[10] = {1,2,3,4,5,6,7,8,9,10};
	char	expected_result[10] = {6,7,3,4,5,6,7,8,9,10};

	cr_assert_arr_eq(memmove(s1, &(s1[5]), 2), expected_result, 10);
	cr_assert_arr_eq(ft_memmove(s2, &(s2[5]), 2), expected_result, 10);
}

Test(ft_memmove, size_3)
{
	char	s1[10] = {1,2,3,4,5,6,7,8,9,10};
	char	s2[10] = {1,2,3,4,5,6,7,8,9,10};
	char	expected_result[10] = {6,7,8,4,5,6,7,8,9,10};

	cr_assert_arr_eq(memmove(s1, &(s1[5]), 3), expected_result, 10);
	cr_assert_arr_eq(ft_memmove(s2, &(s2[5]), 3), expected_result, 10);
}

Test(ft_memmove, size_4_forward_overlap)
{
	char	s1[10] = {1,2,3,4,5,6,7,8,9,10};
	char	s2[10] = {1,2,3,4,5,6,7,8,9,10};
	char	expected_result[10] = {3,4,5,6,5,6,7,8,9,10};

	cr_assert_arr_eq(memmove(s1, &(s1[2]), 4), expected_result, 10);
	cr_assert_arr_eq(ft_memmove(s2, &(s2[2]), 4), expected_result, 10);
}

Test(ft_memmove, size_4_backward_overlap)
{
	char	s1[10] = {1,2,3,4,5,6,7,8,9,10};
	char	s2[10] = {1,2,3,4,5,6,7,8,9,10};
	char	expected_result[8] = {1,2,3,4,7,8,9,10};

	cr_assert_arr_eq(memmove(&(s1[2]), s1, 4), expected_result, 8);
	cr_assert_arr_eq(ft_memmove(&(s2[2]), s2, 4), expected_result, 8);
}

Test(ft_memmove, size_4_complete_overlap)
{
	char	s1[10] = {1,2,3,4,5,6,7,8,9,10};
	char	s2[10] = {1,2,3,4,5,6,7,8,9,10};
	char	expected_result[10] = {1,2,3,4,5,6,7,8,9,10};

	cr_assert_arr_eq(memmove(s1, s1, 4), expected_result, 10);
	cr_assert_arr_eq(ft_memmove(s2, s2, 4), expected_result, 10);
}
