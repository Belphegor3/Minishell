#include <criterion/criterion.h>
#include <string.h>
#include "../libft.h"

Test(ft_strrchr, first_character)
{
	char	*str = "Hello World!";

	cr_assert(strrchr(str, 'H') == str);
	cr_assert(ft_strrchr(str, 'H') == str);
}

Test(ft_strrchr, character_present)
{
	char	*str = "Hello World!";

	cr_assert(strrchr(str, 'l') == str + 9);
	cr_assert(ft_strrchr(str, 'l') == str + 9);
}

Test(ft_strrchr, character_absent)
{
	char	*str = "Hello World!";

	cr_assert(strrchr(str, 'x') == 0);
	cr_assert(ft_strrchr(str, 'x') == 0);
}
