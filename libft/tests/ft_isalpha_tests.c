#include <criterion/criterion.h>
#include <ctype.h>
#include "../libft.h"

Test(ft_isalpha, not_a_letter)
{
	char	c;

	c = ' ';
	cr_assert(isalpha((unsigned char) c) == 0);
	cr_assert(ft_isalpha((unsigned char) c) == 0);
}

Test(ft_isalpha, lowercase_letter_a)
{
	char	c;

	c = 'a';
	cr_assert(isalpha((unsigned char) c) != 0);
	cr_assert(ft_isalpha((unsigned char) c) != 0);
}

Test(ft_isalpha, lowercase_letter_z)
{
	char	c;

	c = 'z';
	cr_assert(isalpha((unsigned char) c) != 0);
	cr_assert(ft_isalpha((unsigned char) c) != 0);
}

Test(ft_isalpha, uppercase_letter_A)
{
	char	c;

	c = 'A';
	cr_assert(isalpha((unsigned char) c) != 0);
	cr_assert(ft_isalpha((unsigned char) c) != 0);
}

Test(ft_isalpha, uppercase_letter_Z)
{
	char	c;

	c = 'Z';
	cr_assert(isalpha((unsigned char) c) != 0);
	cr_assert(ft_isalpha((unsigned char) c) != 0);
}
