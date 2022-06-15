#include <criterion/criterion.h>
#include <string.h>
#include "../libft.h"

Test(ft_memcmp, equal)
{
	char *s1 = "abcde";
	char *s2 = "abcde";

	cr_assert(memcmp(s1, s2, 3) == 0);
	cr_assert(ft_memcmp(s1, s2, 3) == 0);
}

Test(ft_memcmp, superior)
{
	char *s1 = "abdde";
	char *s2 = "abcde";

	cr_assert(memcmp(s1, s2, 3) > 0);
	cr_assert(ft_memcmp(s1, s2, 3) > 0);
}

Test(ft_memcmp, inferior)
{
	char *s1 = "abcde";
	char *s2 = "agcde";

	cr_assert(memcmp(s1, s2, 3) < 0);
	cr_assert(ft_memcmp(s1, s2, 3) < 0);
}

Test(ft_memcmp, n_is_zero)
{
	char *s1 = "abcde";
	char *s2 = "agcde";

	cr_assert(memcmp(s1, s2, 0) == 0);
	cr_assert(ft_memcmp(s1, s2, 0) == 0);
}
