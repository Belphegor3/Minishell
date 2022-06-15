#include <criterion/criterion.h>
#include <stdlib.h>
#include "../libft.h"

Test(ft_atoi, one_number)
{
	char	*nptr = "0";

	cr_assert(atoi(nptr) == 0);
	cr_assert(ft_atoi(nptr) == 0);
	nptr = "5";
	cr_assert(atoi(nptr) == 5);
	cr_assert(ft_atoi(nptr) == 5);
}

Test(ft_atoi, two_number)
{
	char	*nptr = "65";

	cr_assert(atoi(nptr) == 65);
	cr_assert(ft_atoi(nptr) == 65);
}

Test(ft_atoi, int_max)
{
	char	*nptr = "2147483647";

	cr_assert(atoi(nptr) == 2147483647);
	cr_assert(ft_atoi(nptr) == 2147483647);
}

Test(ft_atoi, negative_number)
{
	char	*nptr = "-3526";

	cr_assert(atoi(nptr) == -3526);
	cr_assert(ft_atoi(nptr) == -3526);
}

Test(ft_atoi, int_min)
{
	char	*nptr = "-2147483648";

	cr_assert(atoi(nptr) == -2147483648);
	cr_assert(ft_atoi(nptr) == -2147483648);
}

Test(ft_atoi, plus_sign)
{
	char	*nptr = "+967";

	cr_assert(atoi(nptr) == 967);
	cr_assert(ft_atoi(nptr) == 967);
}

Test(ft_atoi, non_numeric_values_at_the_end)
{
	char	*nptr = "+967abc";

	cr_assert(atoi(nptr) == 967);
	cr_assert(ft_atoi(nptr) == 967);
}

Test(ft_atoi, non_numeric_values_at_the_beginning)
{
	char	*nptr = "+r967abc";

	cr_assert(atoi(nptr) == 0);
	cr_assert(ft_atoi(nptr) == 0);
}
