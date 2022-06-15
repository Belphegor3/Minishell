#include <criterion/criterion.h>
#include <string.h>
#include "../libft.h"

Test(ft_memchr, c_is_absent)
{
	char	*s = "yujikuvb";

	cr_assert(memchr(s, 'x', 5) == 0);
	cr_assert(ft_memchr(s, 'x', 5) == 0);
}

Test(ft_memchr, c_is_present)
{
	char	*s = "yujikuvb";

	cr_assert(memchr(s, 'u', 5) == s + 1);
	cr_assert(ft_memchr(s, 'u', 5) == s + 1);
}

Test(ft_memchr, n_is_0)
{
	char	*s = "yujikuvb";

	cr_assert(memchr(s, 'u', 0) == 0);
	cr_assert(ft_memchr(s, 'u', 0) == 0);
}
