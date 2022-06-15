#include <criterion/criterion.h>
#include <ctype.h>
#include "../libft.h"

Test(ft_isprint, test_NULL)
{
	char	c;

	c = 0;
	cr_assert(isprint((unsigned char)c) == 0);
	cr_assert(ft_isprint((unsigned char)c) == 0);
}

Test(ft_isprint, test_32)
{
	char	c;

	c = 32;
	cr_assert(isprint((unsigned char)c) != 0);
	cr_assert(ft_isprint((unsigned char)c) != 0);
}

Test(ft_isprint, test_127)
{
	char	c;

	c = 127;
	cr_assert(isprint((unsigned char)c) == 0);
	cr_assert(ft_isprint((unsigned char)c) == 0);
}
