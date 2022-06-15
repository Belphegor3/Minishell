#include <criterion/criterion.h>
#include "../libft.h"

static void	increment_by_index(unsigned int index, char *c)
{
	*c = *c + index;
}

Test(ft_striteri, empty_string)
{
	char	*s = "";

	ft_striteri(s, &increment_by_index);
	cr_assert_str_eq(s, ""); 
}

Test(ft_striteri, regular_string)
{
	char	s1[] = "Lorem";
	char	s2[] = "ipsum";

	ft_striteri(s1, &increment_by_index);
	ft_striteri(s2, &increment_by_index);
	cr_assert_str_eq(s1, "Lpthq"); 
	cr_assert_str_eq(s2, "iquxq"); 
}
