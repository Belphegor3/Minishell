#include <criterion/criterion.h>
#include <strings.h>
#include "../libft.h"

Test(ft_bzero, size_0)
{
	char	s[10] = {1,2,3,4,5,6,7,8,9,10};
	char	s2[10] = {1,2,3,4,5,6,7,8,9,10};
	char	result[10] = {1,2,3,4,5,6,7,8,9,10};

	bzero(s, (0));
	cr_assert_arr_eq(s, result, 10);
	ft_bzero(s2, 0);
	cr_assert_arr_eq(s2, result, 10);
}

Test(ft_bzero, size_1)
{
	char	s[10] = {1,2,3,4,5,6,7,8,9,10};
	char	s2[10] = {1,2,3,4,5,6,7,8,9,10};
	char	result[10] = {0,2,3,4,5,6,7,8,9,10};

	bzero(s, 1);
	cr_assert_arr_eq(s, result, 10);
	ft_bzero(s2, 1);
	cr_assert_arr_eq(s2, result, 10);
}

Test(ft_bzero, size_2)
{
	char	s[10] = {1,2,3,4,5,6,7,8,9,10};
	char	s2[10] = {1,2,3,4,5,6,7,8,9,10};
	char	result[10] = {0,0,3,4,5,6,7,8,9,10};

	bzero(s, 2);
	cr_assert_arr_eq(s, result, 10);
	ft_bzero(s2, 2);
	cr_assert_arr_eq(s2, result, 10);
}

Test(ft_bzero, size_3)
{
	char	s[10] = {1,2,3,4,5,6,7,8,9,10};
	char	s2[10] = {1,2,3,4,5,6,7,8,9,10};
	char	result[10] = {0,0,0,4,5,6,7,8,9,10};

	bzero(s, 3);
	cr_assert_arr_eq(s, result, 10);
	ft_bzero(s2, 3);
	cr_assert_arr_eq(s2, result, 10);
}

Test(ft_bzero, size_10)
{
	char	s[10] = {1,2,3,4,5,6,7,8,9,10};
	char	s2[10] = {1,2,3,4,5,6,7,8,9,10};
	char	result[10] = {0,0,0,0,0,0,0,0,0,0};

	bzero(s, 10);
	cr_assert_arr_eq(s, result, 10);
	ft_bzero(s2, 10);
	cr_assert_arr_eq(s2, result, 10);
}
