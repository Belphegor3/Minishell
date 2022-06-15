#include <criterion/criterion.h>
#include <string.h>
#include "../libft.h"

Test(ft_strncmp, equal_0)
{
	char *s1 = "abcde";
	char *s2 = "abcde";

	cr_assert(strncmp(s1, s2, 3) == 0);
	cr_assert(ft_strncmp(s1, s2, 3) == 0);
}

Test(ft_strncmp, superior)
{
	char *s1 = "abdde";
	char *s2 = "abcde";

	cr_assert(strncmp(s1, s2, 3) > 0);
	cr_assert(ft_strncmp(s1, s2, 3) > 0);
}

Test(ft_strncmp, inferior)
{
	char *s1 = "abcde";
	char *s2 = "agcde";

	cr_assert(strncmp(s1, s2, 3) < 0);
	cr_assert(ft_strncmp(s1, s2, 3) < 0);
}

Test(ft_strncmp, n_too_big)
{
	char *s1 = "abcde";
	char *s2 = "abcde";

	cr_assert(strncmp(s1, s2, 99) == 0);
	cr_assert(ft_strncmp(s1, s2, 99) == 0);
}
