#include <criterion/criterion.h>
#include <ctype.h>
#include "../libft.h"

Test(ft_tolower, lowercase_letters)
{
	cr_assert(tolower('a') == 'a');
	cr_assert(ft_tolower('a') == 'a');
	cr_assert(tolower('z') == 'z');
	cr_assert(ft_tolower('z') == 'z');
}

Test(ft_tolower, uppercase_letters)
{
	cr_assert(tolower('A') == 'a');
	cr_assert(ft_tolower('A') == 'a');
	cr_assert(tolower('Z') == 'z');
	cr_assert(ft_tolower('Z') == 'z');
}
