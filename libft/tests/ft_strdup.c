#include <criterion/criterion.h>
#include <string.h>
#include "../libft.h"

Test(ft_strdup, empty_string)
{
	char	*s = "";
	char	*tmp;

	tmp = strdup(s);
	cr_assert_str_eq(tmp, "");
	free(tmp);
	tmp = ft_strdup(s);
	cr_assert_str_eq(tmp, "");
	free(tmp);
}

Test(ft_strdup, big_string)
{
	char	*s = "wuoifnasopnfpownfupivyusyfgwoiuhg872h87 9 2y9";
	char	*tmp;

	tmp = strdup(s);
	cr_assert_str_eq(tmp, s);
	free(tmp);
	tmp = ft_strdup(s);
	cr_assert_str_eq(tmp, s);
	free(tmp);
}
