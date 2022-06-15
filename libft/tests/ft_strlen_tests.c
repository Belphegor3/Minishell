#include <criterion/criterion.h>
#include <string.h>
#include "../libft.h"

Test(ft_strlen, empty_string)
{
	cr_assert(strlen("") == 0);
	cr_assert(ft_strlen("") == 0);
}

Test(ft_strlen, len_1)
{
	cr_assert(strlen("A") == 1);
	cr_assert(ft_strlen("A") == 1);
}

Test(ft_strlen, len_2)
{
	cr_assert(strlen("AB") == 2);
	cr_assert(ft_strlen("AB") == 2);
}

Test(ft_strlen, len_3)
{
	cr_assert(strlen("ABC") == 3);
	cr_assert(ft_strlen("ABC") == 3);
}

Test(ft_strlen, len_26)
{
	cr_assert(strlen("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == 26);
	cr_assert(ft_strlen("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == 26);
}
