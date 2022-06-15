#include <criterion/criterion.h>
#include "../libft.h"

static char	increment_by_index(unsigned int index, char c)
{
	return (c + index);
}

Test(ft_strmapi, empty_string)
{
	char	*s;

	s = ft_strmapi("", &increment_by_index);
	cr_assert_str_eq(s, ""); 
	free(s);
}

Test(ft_strmapi, regular_string)
{
	char	*s;

	s = ft_strmapi("Lorem", &increment_by_index);
	cr_assert_str_eq(s, "Lpthq"); 
	free(s);
	s = ft_strmapi("ipsum", &increment_by_index);
	cr_assert_str_eq(s, "iquxq"); 
	free(s);
}
