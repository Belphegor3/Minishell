#include <criterion/criterion.h>
#include <ctype.h>
#include "../libft.h"

Test(ft_isdigit, not_a_digit)
{
	char c;

	c = 'a';
	cr_assert(isdigit((unsigned char) c) == 0);
	cr_assert(ft_isdigit((unsigned char) c) == 0);
}

Test(ft_isdigit, digit_0)
{
	char c;

	c = '0';
	cr_assert(isdigit((unsigned char) c) != 0);
	cr_assert(ft_isdigit((unsigned char) c) != 0);
}

Test(ft_isdigit, digit_9)
{
	char c;

	c = '9';
	cr_assert(isdigit((unsigned char) c) != 0);
	cr_assert(ft_isdigit((unsigned char) c) != 0);
}
