#include <criterion/criterion.h>
#include <stdlib.h>
#include "../libft.h"

Test(ft_calloc, correct_inputs)
{
	size_t	nmemb = 20;
	size_t	size = 4;
	void	*result;

	result = calloc(nmemb, size);
	cr_assert(result != 0);
	free(result);
	result = ft_calloc(nmemb, size);
	cr_assert(result != 0);
	free(result);
}

/*Test(ft_calloc, integer_overflow)
{
	size_t	nmemb = 5000000;
	size_t	size = 50000;

	cr_assert(calloc(nmemb, size) == 0);
	cr_assert(ft_calloc(nmemb, size) == 0);
}*/
