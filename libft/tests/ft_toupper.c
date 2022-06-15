#include <criterion/criterion.h>
#include <ctype.h>
#include "../libft.h"

Test(ft_toupper, lowercase_letters)
{
	cr_assert(toupper('a') == 'A');
	cr_assert(ft_toupper('a') == 'A');
	cr_assert(toupper('z') == 'Z');
	cr_assert(ft_toupper('z') == 'Z');
}

Test(ft_toupper, uppercase_letters)
{
	cr_assert(toupper('A') == 'A');
	cr_assert(ft_toupper('A') == 'A');
	cr_assert(toupper('Z') == 'Z');
	cr_assert(ft_toupper('Z') == 'Z');
}
