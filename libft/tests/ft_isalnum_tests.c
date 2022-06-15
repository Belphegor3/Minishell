#include <criterion/criterion.h>
#include <ctype.h>
#include "../libft.h"

Test(ft_isalnum, non_alnum)
{
	char	c;

	c = ' ';
	cr_assert(isalnum((unsigned char)c) == 0);
	cr_assert(ft_isalnum((unsigned char)c) == 0);
}

Test(ft_isalnum, digit_0)
{
	char	c;

	c = '0';
	cr_assert(isalnum((unsigned char)c) != 0);
	cr_assert(ft_isalnum((unsigned char)c) != 0);
}

Test(ft_isalnum, digit_9)
{
	char	c;

	c = '9';
	cr_assert(isalnum((unsigned char)c) != 0);
	cr_assert(ft_isalnum((unsigned char)c) != 0);
}

Test(ft_isalnum, lowercase_a)
{
	char	c;

	c = 'a';
	cr_assert(isalnum((unsigned char)c) != 0);
	cr_assert(ft_isalnum((unsigned char)c) != 0);
}

Test(ft_isalnum, lowercase_z)
{
	char	c;

	c = 'z';
	cr_assert(isalnum((unsigned char)c) != 0);
	cr_assert(ft_isalnum((unsigned char)c) != 0);
}

Test(ft_isalnum, uppercase_A)
{
	char	c;

	c = 'A';
	cr_assert(isalnum((unsigned char)c) != 0);
	cr_assert(ft_isalnum((unsigned char)c) != 0);
}

Test(ft_isalnum, uppercase_Z)
{
	char	c;

	c = 'Z';
	cr_assert(isalnum((unsigned char)c) != 0);
	cr_assert(ft_isalnum((unsigned char)c) != 0);
}
