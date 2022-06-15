#include <criterion/criterion.h>
#include <ctype.h>
#include "../libft.h"

Test(ft_isascii, test_0)
{
	char	c;

	c = 0;
	cr_assert(isascii((unsigned char)c) != 0);
	cr_assert(ft_isascii((unsigned char)c) != 0);
}

Test(ft_isascii, test_127)
{
	char	c;

	c = 127;
	cr_assert(isascii((unsigned char)c) != 0);
	cr_assert(ft_isascii((unsigned char)c) != 0);
}

Test(ft_isascii, test_255)
{
	unsigned char	c;

	c = 255;
	cr_assert(isascii((unsigned char)c) != 1);
	cr_assert(ft_isascii((unsigned char)c) != 1);
}

Test(ft_isascii, test_128)
{
	unsigned char	c;

	c = 128;
	cr_assert(isascii((unsigned char)c) != 1);
	cr_assert(ft_isascii((unsigned char)c) != 1);
}

Test(ft_isascii, test_negative)
{
	char	c;

	c = -1;
	cr_assert(isascii((unsigned char)c) != 1);
	cr_assert(ft_isascii((unsigned char)c) != 1);
}
