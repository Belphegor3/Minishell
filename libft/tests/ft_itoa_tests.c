#include <criterion/criterion.h>
#include "../libft.h"

Test(ft_itoa, one_digit)
{
	char	*s;

	s = ft_itoa(0);
	cr_assert_str_eq(s, "0");
	free(s);
	s = ft_itoa(5);
	cr_assert_str_eq(s, "5");
	free(s);
}

Test(ft_itoa, multiple_digits)
{
	char *s;

	s = ft_itoa(26);
	cr_assert_str_eq(s, "26");
	free(s);
	s = ft_itoa(854);
	cr_assert_str_eq(s, "854");
	free(s);
	s = ft_itoa(44327);
	cr_assert_str_eq(s, "44327");
	free(s);
}

Test(ft_itoa, negative_numbers)
{
	char *s;

	s = ft_itoa(-7);
	cr_assert_str_eq(s, "-7");
	free(s);
	s = ft_itoa(-58);
	cr_assert_str_eq(s, "-58");
	free(s);
	s = ft_itoa(-5588);
	cr_assert_str_eq(s, "-5588");
	free(s);
}

Test(ft_itoa, int_max)
{
	char *s;

	s = ft_itoa(2147483647);
	cr_assert_str_eq(s, "2147483647");
	free(s);
}

Test(ft_itoa, int_min)
{
	char *s;

	s = ft_itoa(2147483647);
	cr_assert_str_eq(s, "2147483647");
	free(s);
}
