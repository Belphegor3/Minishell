#include <stdio.h>
#include <criterion/criterion.h>
#include "../libft.h"

Test(vecset, test_with_int)
{
	t_vector	v;
	int			nb;

	nb = 97;
	v = ft_veccreate(2, sizeof(int));
	v.length = 2;
	cr_assert(ft_vecset(v, 0, &nb) == 0);
	cr_assert(((int*)v.buffer)[0] == nb);
	nb = -13870;
	cr_assert(ft_vecset(v, 1, &nb) == 0);
	cr_assert(((int*)v.buffer)[1] == nb);
	cr_assert(ft_vecset(v, 2, &nb) == -1);
	ft_vecdestroy(&v);
	cr_assert(v.item_size == 0);
	cr_assert(v.length == 0);
	cr_assert(v.capacity == 0);
	cr_assert(v.buffer == NULL);
}
