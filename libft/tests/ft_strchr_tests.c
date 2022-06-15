#include <criterion/criterion.h>
#include <string.h>
#include "../libft.h"

Test(ft_strchr, first_character)
{
	char	*str = "Hello!";

	cr_assert(strchr(str, 'H') == str);
	cr_assert(ft_strchr(str, 'H') == str);
}

Test(ft_strchr, character_is_present)
{
	char	*str = "Hello!";

	cr_assert(strchr(str, 'l') == str + 2);
	cr_assert(ft_strchr(str, 'l') == str + 2);
}

Test(ft_strchr, character_is_absent)
{
	char	*str = "Hello!";

	cr_assert(strchr(str, 'r') == NULL);
	cr_assert(ft_strchr(str, 'r') == NULL);
}

Test(ft_strchr, character_is_null)
{
	char	*str = "Hello!";

	cr_assert(strchr(str, '\0') == str + 6);
	cr_assert(ft_strchr(str, '\0') == str + 6);
}
